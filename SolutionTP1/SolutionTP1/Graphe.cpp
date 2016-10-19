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
		arcs_.clear();
		for (auto i = listeDarcs.begin(); i != listeDarcs.end(); i++) {
			vector<string> arc = split(*i, ',');
			Sommet* sommet1 = trouverSommet(arc[0]);
			Sommet* sommet2 = trouverSommet(arc[1]);
			int distance = stoi(arc[2]);
			Arc* newArc = new Arc(sommet1, sommet2, distance);
			arcs_.push_back(newArc);
		}

		fichier.close();
		lireGraphe();
	}
}


void Graphe::lireGraphe() {

}

void Graphe::extractionGraphe() {

}

void Graphe::plusCourtChemin() {

}

Sommet* Graphe::trouverSommet(string identifiant) const {
	for (auto i = sommets_.begin(); i != sommets_.end(); i++) {
		if ((*i)->getIdentifiant() == identifiant) {
			return *i;
		}
	}
}