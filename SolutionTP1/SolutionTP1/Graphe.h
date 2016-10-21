#pragma once
#include <string>
#include <vector>

#include "Sommet.h"
//#include "Arc.h"

using namespace std;

class Graphe
{
public:
	Graphe();
	~Graphe();

	void creerGraphe(string fileName);
	void lireGraphe();
	void extractionGraphe();
	void plusCourtChemin(Sommet* sommetDepart, Sommet* sommetDestination);

private:
	Sommet* trouverSommet(string identifiant) const;

	vector<Sommet*> sommets_;
};
