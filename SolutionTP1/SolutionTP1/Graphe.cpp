#include "Graphe.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

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

void Graphe::creerGraphe(string fileName) {
	ifstream fichier(fileName, ios::in);

	if (fichier.fail()) {
		cerr << "L'ouverture du fichier a échoué." << endl;		
	}
	else {
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
			}
			int distance = stoi(arc[2]);

			sommetOrigine->addVoisin(sommetDestination, distance);
		}

		fichier.close();
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

void Graphe::extractionGraphe() {
	//extraire uniquement les chemins possibles avec l'autonomie actuelle (ou max?) du véhicule

}

void Graphe::plusCourtChemin(Sommet* sommetDepart, Sommet* sommetDestination, Vehicule& vehicule) {
	//détermine le plus court chemin entre 2 sommets
	vector<Trajet> result;
	vector<pair<Sommet*, int>> voisinsDuDepart = sommetDepart->getVoisinsPossibles(vehicule.getAutonomieActuelle());
	for (auto i = voisinsDuDepart.begin(); i != voisinsDuDepart.end(); i++) {
		int autonomieRestante = vehicule.getAutonomieActuelle() - (*i).second;
		if ((*i).first->getIdentifiant() == sommetDestination->getIdentifiant()) {
			Trajet trajet;
			trajet.ajouterSommet((*i).first, (*i).second);
			result.push_back(trajet);
		}
		else if ((*i).first->getVoisinsPossibles(autonomieRestante).size() > 0) {
			//TODO: Dig continuellement tous les niveaux
			vector<pair<Sommet*, int>> voisinsDuNiveau = (*i).first->getVoisinsPossibles(autonomieRestante);
			for (auto j = voisinsDuNiveau.begin(); j != voisinsDuNiveau.end(); j++) {
				int autonomieRestante2 = autonomieRestante - (*j).second;
				if ((*j).first->getIdentifiant() == sommetDestination->getIdentifiant()) {
					Trajet trajet;
					trajet.ajouterSommet((*j).first, (*j).second);
					result.push_back(trajet);
				}
			}
		}

	}

	for (auto i = result.begin(); i != result.end(); i++) {
		vector<Sommet*> sommets = (*i).getSommets();
		string listeDeSommets = "";
		bool isFirst = true;
		for (auto j = sommets.begin(); j != sommets.end(); j++) {
			if (!isFirst)
				listeDeSommets += ", ";
			listeDeSommets = (*j)->getIdentifiant();
		}
		cout << "Trajet : " << listeDeSommets << ". Distance : " << (*i).getDistance() << endl;
	}
}



Sommet* Graphe::trouverSommet(string identifiant) const {
	for (auto i = sommets_.begin(); i != sommets_.end(); i++) {
		if ((*i)->getIdentifiant() == identifiant) {
			return *i;
		}
	}
	throw invalid_argument("Impossible de trouver le sommet.");
}