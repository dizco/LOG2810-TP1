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
	detruireSommets();
}

void Graphe::detruireSommets() {
	for (auto i = sommets_.begin(); i != sommets_.end(); i++) {
		delete (*i);
		(*i) = nullptr;
	}
	sommets_.clear();
}


/*
Permet de s�parer un string selon un caract�re d�limitant
Tir� de : http://stackoverflow.com/a/236803/6316091
*/
void split(const string &s, char delim, vector<string> &elems) {
	stringstream ss;
	ss.str(s);
	string item;
	while (getline(ss, item, delim)) {
		elems.push_back(item);
	}
}
/*
Tir� de : http://stackoverflow.com/a/236803/6316091
*/
vector<string> split(const string &s, char delim) {
	vector<string> elems;
	split(s, delim, elems);
	return elems;
}

/*
* C1. Cr�e le graphe � partir d'un fichier
*/
void Graphe::creerGraphe(string fileName, bool afficher) {
	ifstream fichier(fileName, ios::in);

	if (fichier.fail()) {
		cerr << "L'ouverture du fichier a echoue." << endl;	
		return;
	}
	else {
		string ligne1;
		getline(fichier, ligne1);

		vector<string> listeDeSommets = split(ligne1, ';');
		detruireSommets();
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
				fichier.close();
				detruireSommets();
				fileName_ = "";
				return;
			}
			int distance = stoi(arc[2]);

			try {
				trouverPositionSommet(sommetDestination->getVoisinsSansDistance(), sommetOrigine->getIdentifiant());
				cout << "Erreur lors de l'enregistrement du graphe. Le systeme ne peut pas gerer les liens bidirectionnels. Voir rapport pour explications." << endl;
				fichier.close();
				detruireSommets();
				fileName_ = "";
				return;
			}
			catch (const invalid_argument& e) {
			}

			sommetOrigine->addVoisin(sommetDestination, distance);
		}

		fileName_ = fileName;
		fichier.close();
		if (afficher)
			lireGraphe();
	}
}

/*
* C2. Affiche la carte
*/
void Graphe::lireGraphe() {
	for (auto i = sommets_.begin(); i != sommets_.end(); i++) {
		cout << "(Station " << (*i)->getIdentifiant() << ", " << (*i)->getType() << ", "
			<< (*i)->printVoisins()
			<< ")" << endl;
	}
}

/*
* C3. Extraire le graphe des points accessibles � un v�hicule
*/
vector<Sommet*> Graphe::extractionGraphe(Sommet* sommetDepart, const Vehicule& vehicule) const {
	//extraire uniquement les chemins possibles avec l'autonomie actuelle (ou max?) du v�hicule

	vector<pair<Sommet*, int>> voisinExtrait = extraireVoisinsDeSommet(sommetDepart, vehicule);
	sommetDepart->setVoisins(voisinExtrait);
	return sommets_;
}

/*
* C3 (suite). Fonction r�cursive qui extrait le graphe disponible au v�hicule
*/
vector<pair<Sommet*, int>> Graphe::extraireVoisinsDeSommet(Sommet* sommet, Vehicule vehicule) const {
	if (sommet->peutRecharger(vehicule.getCarburant())) //on recharge le v�hicule partout o� c'est possible
		vehicule.recharger();

	int autonomieActuelle = vehicule.getAutonomieActuelle();
	vector<pair<Sommet*, int>> voisinsPossibles = sommet->getVoisinsPossibles(autonomieActuelle); //extrait les voisins accessibles avec l'autonomie
	for (auto i = voisinsPossibles.begin(); i != voisinsPossibles.end(); i++) {
		//if (!(*i).first->voisinsPossiblesExtraits()) { //voir rapport difficult�s rencontr�es
			vehicule.setAutonomieActuelle(autonomieActuelle - (*i).second);
			//(*i).first->setVoisinsPossiblesExtraits(true);
			vector<pair<Sommet*, int>> voisinExtrait = extraireVoisinsDeSommet((*i).first, vehicule); //on appelle r�cursivement
			(*i).first->setVoisins(voisinExtrait);
		//}
	}
	return voisinsPossibles;
}

/*
* C4. D�termine le plus court chemin pour faire le trajet du d�part � la destination
* Impl�mente l'algorithme de Dijkstra, inspir� de : https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm?oldformat=true#Pseudocode
*/
void Graphe::plusCourtChemin(Sommet* sommetDepart, Sommet* sommetDestination, Vehicule& vehicule) {
	vector<Sommet*> sommetsDisponibles = extractionGraphe(sommetDepart, vehicule); 
	vector<pair<Sommet*, pair<int, Sommet*>>> sommetsEtPoids; //format : <pair<sommetActuel, pair<poidsDuSommetActuel, sommetPr�c�dent>>

	for (auto i = sommetsDisponibles.begin(); i != sommetsDisponibles.end(); i++) {
		int initialDistance = numeric_limits<int>::max(); //on initialise tous les sommets � poids infini
		if ((*i)->getIdentifiant() == sommetDepart->getIdentifiant())
			initialDistance = 0; //le sommet de d�part est � 0
		sommetsEtPoids.push_back(make_pair((*i), make_pair(initialDistance, nullptr)));
	}

	while (sommetsDisponibles.size() != 0) { //on continue tant qu'il nous reste des sommets non test�s
		int positionPlusPetitDisponible = positionDuPlusPetitSommetEncoreDisponible(sommetsDisponibles, sommetsEtPoids);
		Sommet* sommetPlusPetitDisponible = sommetsEtPoids[positionPlusPetitDisponible].first;
		int offsetDansListeSommetsDisponibles = trouverPositionSommet(sommetsDisponibles, sommetPlusPetitDisponible->getIdentifiant());
		sommetsDisponibles.erase(sommetsDisponibles.begin() + offsetDansListeSommetsDisponibles); //le sommet est retir� de la liste des sommets possibles
		if (sommetPlusPetitDisponible->getIdentifiant() == sommetDestination->getIdentifiant()
			|| sommetsEtPoids[positionPlusPetitDisponible].second.first >= numeric_limits<int>::max()) { //poids infini, le noeud est inaccessible
			continue;
		}

		vector<pair<Sommet*, int>> voisinsDuPlusPetitDisponible = sommetPlusPetitDisponible->getVoisins();
		//on it�re sur la liste de voisins du plus petit noeud
		for (auto i = voisinsDuPlusPetitDisponible.begin(); i != voisinsDuPlusPetitDisponible.end(); i++) { 		
			int positionVoisinDansVecteur = trouverPositionSommet(sommetsEtPoids, (*i).first->getIdentifiant());
			int poidsVoisinCourant = sommetsEtPoids[positionPlusPetitDisponible].second.first + (*i).second; //le poids du sommetPlusPetitDisponible + la distance vers le voisin actuel
			if (poidsVoisinCourant < sommetsEtPoids[positionVoisinDansVecteur].second.first) {
				//on a trouv� un chemin moins long pour se rendre au voisin en question (*i)
				sommetsEtPoids[positionVoisinDansVecteur].second.first = poidsVoisinCourant; //on change le poids du noeud
				sommetsEtPoids[positionVoisinDansVecteur].second.second = sommetPlusPetitDisponible; //on enregistre son �l�ment pr�c�dent
			}
		}
	}

	pair<Sommet*, pair<int, Sommet*>> poidsFinal = sommetsEtPoids[trouverPositionSommet(sommetsEtPoids, sommetDestination->getIdentifiant())];
	if (poidsFinal.second.first < numeric_limits<int>::max()) {
		//on a trouv� un chemin vers le sommet de destination
		vector<Sommet*> trajet = extraireTrajet(sommetsEtPoids, sommetDepart, sommetDestination);
		afficherTrajet(trajet);
		vehicule.setAutonomieActuelle(calculerAutonomieRestante(vehicule, sommetsEtPoids, sommetDepart, sommetDestination));
		cout << "Distance parcourue : " << poidsFinal.second.first << "km" << endl;
		cout << "Autonomie restante : " << vehicule.getAutonomieActuelle() << "km" << endl;
	}
	else {
		//il n'existe pas de chemin entre le depart et la destination
		cerr << "Il n'existe pas de chemin entre les sommets " << sommetDepart->getIdentifiant() 
			<< " et " << sommetDestination->getIdentifiant() 
			<< " avec une autonomie actuelle de " << vehicule.getAutonomieActuelle() << "km." << endl;
	}

	creerGraphe(fileName_, false);
}

//Trouve le sommet avec le plus petit poids, qui se trouve dans le vecteur de sommets disponibles
int Graphe::positionDuPlusPetitSommetEncoreDisponible(vector<Sommet*>& disponibles, vector<pair<Sommet*, pair<int, Sommet*>>>& vecteur) const {
	int positionDuPlusPetit = -1;
	for (int i = 0; i < vecteur.size(); i++) {
		if (find(disponibles.begin(), disponibles.end(), vecteur[i].first) == disponibles.end())
			continue; //le sommet n'est pas dans la liste des disponibles, on l'ignore
		if (positionDuPlusPetit == -1 || vecteur[i].second.first < vecteur[positionDuPlusPetit].second.first) {
			positionDuPlusPetit = i;
		}
	}
	return positionDuPlusPetit;
}

//Trouve un sommet dans un vecteur pair<Sommet*, pair<int, Sommet*>> pass� en param�tre
int Graphe::trouverPositionSommet(vector<pair<Sommet*, pair<int, Sommet*>>>& vecteur, string identifiant) const {
	for (int i = 0; i < vecteur.size(); i++) {
		if (vecteur[i].first->getIdentifiant() == identifiant) {
			return i;
		}
	}
	throw invalid_argument("Impossible de trouver le sommet.");
}

//Trouve un sommet dans un vecteur de Sommet* pass� en param�tre
int Graphe::trouverPositionSommet(vector<Sommet*>& vecteur, string identifiant) const {
	for (int i = 0; i < vecteur.size(); i++) {
		if (vecteur[i]->getIdentifiant() == identifiant) {
			return i;
		}
	}
	throw invalid_argument("Impossible de trouver le sommet.");
}

//Trouve un sommet dans le vecteur sommets_
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
	Sommet* sommet = sommetDestination; //on part de la destination jusqu'au d�part
	vector<Sommet*> trajet;
	do {
		//on part du sommet de destination et on retrace le trajet
		trajet.push_back(sommet);
		if (sommet->getIdentifiant() == sommetDepart->getIdentifiant())
			sommetDepartTrouve = true;
		else {
			pair<Sommet*, pair<int, Sommet*>> current = vecteur[trouverPositionSommet(vecteur, sommet->getIdentifiant())];
			sommet = current.second.second; //on va chercher l'�l�ment pr�c�dent au current
		}		
	} while (!sommetDepartTrouve);
	
	reverse(trajet.begin(), trajet.end()); //on a extrait la liste � l'envers

	return trajet;
}

void Graphe::afficherTrajet(vector<Sommet*>& vecteur) const {
	cout << "Le vehicule emprunte les sommets suivants : ";
	string trajet = "";
	bool isFirst = true;
	for (auto i = vecteur.begin(); i != vecteur.end(); i++) {
		//on affiche chaque sommet 
		if (!isFirst)
			trajet += " -> ";
		trajet += (*i)->getIdentifiant();
		 isFirst = false;
	}
	cout << trajet << endl;
}

int Graphe::calculerAutonomieRestante(const Vehicule& vehicule, vector<pair<Sommet*, pair<int, Sommet*>>>& vecteur, Sommet* sommetDepart, Sommet* sommetDestination) const {
	int autonomieDepart = vehicule.getAutonomieActuelle();
	int distanceTotale = vecteur[trouverPositionSommet(vecteur, sommetDestination->getIdentifiant())].second.first;
	bool sommetDepartTrouve = false;
	Sommet* sommet = sommetDestination; //on part de la destination jusqu'au d�part
	do {
		if (sommet->getIdentifiant() == sommetDepart->getIdentifiant())
			sommetDepartTrouve = true;

		pair<Sommet*, pair<int, Sommet*>> current = vecteur[trouverPositionSommet(vecteur, sommet->getIdentifiant())];
		if (current.first->peutRecharger(vehicule.getCarburant())) { 
			//on a trouv� le point de recharge le plus proche de la destination (o� le v�hicule a fait le plein la derni�re fois)
			return vehicule.getAutonomieMax() - (distanceTotale - current.second.first);
		}
		else {
			sommet = current.second.second; //on va chercher l'�l�ment pr�c�dent au current
		}
		
	} while (!sommetDepartTrouve);
	return autonomieDepart - distanceTotale; //le v�hicule n'a tout simplement pas recharg� durant son trajet
}

bool Graphe::informationsEnregistrees() const {
	return (sommets_.size() > 0 && fileName_ != "");
}