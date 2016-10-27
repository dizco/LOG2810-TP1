#include "Graphe.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <limits>

using namespace std;

Graphe::Graphe()
{
}

Graphe::~Graphe()
{
}


/*
http://stackoverflow.com/a/236803/6316091
*/
void split(const std::string &s, char delim, std::vector<std::string> &elems) {
	std::stringstream ss;
	ss.str(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
}

/*
http://stackoverflow.com/a/236803/6316091
*/
std::vector<std::string> split(const std::string &s, char delim) {
	std::vector<std::string> elems;
	split(s, delim, elems);
	return elems;
}

void Graphe::creerGraphe(string fileName, bool afficher) {
	ifstream fichier(fileName, ios::in);

	if (fichier.fail()) {
		cerr << "L'ouverture du fichier a échoué." << endl;		
	}
	else {
		fileName_ = fileName;
		string ligne1;
		getline(fichier, ligne1);

		vector<string> listeDeSommets = split(ligne1, ';');
		sommets_.clear();
		for (auto i = listeDeSommets.begin(); i != listeDeSommets.end(); i++) {
			vector<string> sommet = split(*i, ',');
			Sommet* newSommet = new Sommet(sommet[0], sommet[1]);
			sommets_.push_back(newSommet);
		}

		string ligne2;
		getline(fichier, ligne2); 
		vector<string> listeDarcs = split(ligne2, ';');
		for (auto i = listeDarcs.begin(); i != listeDarcs.end(); i++) {
			vector<string> arc = split(*i, ',');

			Sommet* sommetOrigine;
			Sommet* sommetDestination;
			try {
				sommetOrigine = trouverSommet(arc[0]);
				sommetDestination = trouverSommet(arc[1]);
			}
			catch (const invalid_argument& e) {
				cout << "Erreur lors de la lecture du fichier de graphe. Un sommet inexistant est utilise." << endl;
				break;
			}
			int distance = stoi(arc[2]);

			sommetOrigine->addVoisin(sommetDestination, distance);
		}

		fichier.close();
		if (afficher)
			lireGraphe();
	}
}


void Graphe::lireGraphe() {
	for (auto i = sommets_.begin(); i != sommets_.end(); i++) {
		cout << "(Station " << (*i)->getIdentifiant() << ", " << (*i)->getType() << ", "
			<< (*i)->printVoisins()
			<< ")" << endl;
	}
}

vector<Sommet*> Graphe::extractionGraphe(Sommet* sommetDepart, const Vehicule& vehicule) const {
	//extraire uniquement les chemins possibles avec l'autonomie actuelle (ou max?) du véhicule

	vector<pair<Sommet*, int>> voisinExtrait = extraireVoisinsDeSommet(sommetDepart, vehicule);
	sommetDepart->setVoisins(voisinExtrait);
	return sommets_;
}

vector<pair<Sommet*, int>> Graphe::extraireVoisinsDeSommet(Sommet* sommet, Vehicule vehicule) const {
	if (sommet->peutRecharger(vehicule.getCarburant()))
		vehicule.recharger();

	int autonomieActuelle = vehicule.getAutonomieActuelle();
	vector<pair<Sommet*, int>> voisinsPossibles = sommet->getVoisinsPossibles(autonomieActuelle);
	for (auto i = voisinsPossibles.begin(); i != voisinsPossibles.end(); i++) {
		vehicule.setAutonomieActuelle(autonomieActuelle - (*i).second);
		
		vector<pair<Sommet*, int>> voisinExtrait = extraireVoisinsDeSommet((*i).first, vehicule);
		(*i).first->setVoisins(voisinExtrait);
	}
	return voisinsPossibles;
}

void Graphe::plusCourtChemin(Sommet* sommetDepart, Sommet* sommetDestination, Vehicule& vehicule) {
	//détermine le plus court chemin entre 2 sommets

	vector<Sommet*> sommetsDisponibles = extractionGraphe(sommetDepart, vehicule);
	vector<pair<Sommet*, pair<int, Sommet*>>> sommetsEtPoids; //<pair<sommetActuel, pair<poidsDuSommetActuel, sommetPrécédent>>
	vector<Sommet*> trajet;

	for (auto i = sommetsDisponibles.begin(); i != sommetsDisponibles.end(); i++) {
		int initialDistance = numeric_limits<int>::max(); //on initialise tous les sommets à poids infini
		if ((*i)->getIdentifiant() == sommetDepart->getIdentifiant())
			initialDistance = 0; //le sommet de départ est à 0
		sommetsEtPoids.push_back(make_pair((*i), make_pair(initialDistance, nullptr)));
	}

	while (sommetsDisponibles.size() != 0) { //on continue tant qu'il nous reste des sommets non testés
		int positionPlusPetitDisponible = positionDuPlusPetitSommetEncoreDisponible(sommetsDisponibles, sommetsEtPoids);
		Sommet* sommetPlusPetitDisponible = sommetsEtPoids[positionPlusPetitDisponible].first;
		int offsetDansListeSommetsDisponibles = trouverPositionSommet(sommetsDisponibles, sommetPlusPetitDisponible->getIdentifiant());
		sommetsDisponibles.erase(sommetsDisponibles.begin() + offsetDansListeSommetsDisponibles); //le sommet est retiré de la liste des sommets possibles
		if (sommetPlusPetitDisponible->getIdentifiant() == sommetDestination->getIdentifiant()
			|| sommetsEtPoids[positionPlusPetitDisponible].second.first >= numeric_limits<int>::max()) { //poids infini, le noeud est inaccessible
			continue;
		}

		vector<pair<Sommet*, int>> voisinsDuPlusPetitDisponible = sommetPlusPetitDisponible->getVoisins();
		for (auto i = voisinsDuPlusPetitDisponible.begin(); i != voisinsDuPlusPetitDisponible.end(); i++) {
			//TODO: Verifier que q contient le voisin en question
			int positionVoisinDansVecteur = trouverPositionSommet(sommetsEtPoids, (*i).first->getIdentifiant());
			int poidsVoisinCourant = sommetsEtPoids[positionPlusPetitDisponible].second.first + (*i).second;
			if (poidsVoisinCourant < sommetsEtPoids[positionVoisinDansVecteur].second.first) {
				//on a trouvé un chemin moins long pour se rendre au voisin en question (*i)
				sommetsEtPoids[positionVoisinDansVecteur].second.first = poidsVoisinCourant; //on change le poids du noeud
				sommetsEtPoids[positionVoisinDansVecteur].second.second = sommetPlusPetitDisponible; //on enregistre son élément précédent
			}
		}
	}

	pair<Sommet*, pair<int, Sommet*>> poidsFinal = sommetsEtPoids[trouverPositionSommet(sommetsEtPoids, sommetDestination->getIdentifiant())];
	if (poidsFinal.second.first < numeric_limits<int>::max()) {
		vector<Sommet*> trajet = extraireTrajet(sommetsEtPoids, sommetDepart, sommetDestination);
		afficherTrajet(trajet);
		vehicule.setAutonomieActuelle(calculerAutonomieRestante(vehicule, sommetsEtPoids, sommetDepart, sommetDestination));
		cout << "Distance parcourue : " << poidsFinal.second.first << "km" << endl;
		cout << "Autonomie restante : " << vehicule.getAutonomieActuelle() << "km" << endl;
	}
	else {
		cerr << "Il n'existe pas de chemin entre les sommets " << sommetDepart->getIdentifiant() 
			<< " et " << sommetDestination->getIdentifiant() << endl;
	}

	creerGraphe(fileName_, false);
}

int Graphe::positionDuPlusPetitSommetEncoreDisponible(vector<Sommet*>& disponibles, vector<pair<Sommet*, pair<int, Sommet*>>>& vecteur) const {
	int positionDuPlusPetit = -1;
	for (int i = 0; i < vecteur.size(); i++) {
		if (find(disponibles.begin(), disponibles.end(), vecteur[i].first) == disponibles.end())
			continue;
		if (positionDuPlusPetit == -1 || vecteur[i].second.first < vecteur[positionDuPlusPetit].second.first) {
			positionDuPlusPetit = i;
		}
	}
	return positionDuPlusPetit;
}

int Graphe::trouverPositionSommet(vector<pair<Sommet*, pair<int, Sommet*>>>& vecteur, string identifiant) const {
	for (int i = 0; i < vecteur.size(); i++) {
		if (vecteur[i].first->getIdentifiant() == identifiant) {
			return i;
		}
	}
	throw invalid_argument("Impossible de trouver le sommet.");
}

int Graphe::trouverPositionSommet(vector<Sommet*>& vecteur, string identifiant) const {
	for (int i = 0; i < vecteur.size(); i++) {
		if (vecteur[i]->getIdentifiant() == identifiant) {
			return i;
		}
	}
	throw invalid_argument("Impossible de trouver le sommet.");
}

Sommet* Graphe::trouverSommet(string identifiant) const {
	for (auto i = sommets_.begin(); i != sommets_.end(); i++) {
		if ((*i)->getIdentifiant() == identifiant) {
			return *i;
		}
	}
	throw invalid_argument("Impossible de trouver le sommet.");
}

vector<Sommet*> Graphe::extraireTrajet(vector<pair<Sommet*, pair<int, Sommet*>>>& vecteur, Sommet* sommetDepart, Sommet* sommetDestination) const {
	bool sommetDepartTrouve = false;
	Sommet* sommet = sommetDestination; //on part de la destination jusqu'au départ
	vector<Sommet*> trajet;
	do {
		//on part du sommet de destination et on retrace le trajet
		trajet.push_back(sommet);
		if (sommet->getIdentifiant() == sommetDepart->getIdentifiant())
			sommetDepartTrouve = true;
		else {
			pair<Sommet*, pair<int, Sommet*>> current = vecteur[trouverPositionSommet(vecteur, sommet->getIdentifiant())];
			sommet = current.second.second; //on va chercher l'élément précédent au current
		}		
	} while (!sommetDepartTrouve);
	
	reverse(trajet.begin(), trajet.end()); //on a extrait la liste à l'envers

	return trajet;
}

void Graphe::afficherTrajet(vector<Sommet*>& vecteur) const {
	cout << "Le vehicule emprunte les sommets suivants : ";
	string trajet = "";
	bool isFirst = true;
	for (auto i = vecteur.begin(); i != vecteur.end(); i++) {
		//on affiche chaque sommet 
		if (!isFirst)
			trajet += ", ";
		trajet += (*i)->getIdentifiant();
		 isFirst = false;
	}
	cout << trajet << endl;
}

int Graphe::calculerAutonomieRestante(const Vehicule& vehicule, vector<pair<Sommet*, pair<int, Sommet*>>>& vecteur, Sommet* sommetDepart, Sommet* sommetDestination) const {
	int autonomieDepart = vehicule.getAutonomieActuelle();
	int distanceTotale = vecteur[trouverPositionSommet(vecteur, sommetDestination->getIdentifiant())].second.first;
	bool sommetDepartTrouve = false;
	Sommet* sommet = sommetDestination; //on part de la destination jusqu'au départ
	do {
		if (sommet->getIdentifiant() == sommetDepart->getIdentifiant())
			sommetDepartTrouve = true;
		else {
			pair<Sommet*, pair<int, Sommet*>> current = vecteur[trouverPositionSommet(vecteur, sommet->getIdentifiant())];
			if (current.first->peutRecharger(vehicule.getCarburant())) { 
				//on a trouvé le point de recharge le plus proche de la destination (où le véhicule a fait le plein la dernière fois)
				return vehicule.getAutonomieMax() - (distanceTotale - current.second.first);
			}
			else {
				sommet = current.second.second; //on va chercher l'élément précédent au current
			}
		}
	} while (!sommetDepartTrouve);
	return autonomieDepart - distanceTotale;
}