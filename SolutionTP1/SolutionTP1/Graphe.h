#pragma once
#include <string>
#include <vector>

#include "Sommet.h"
#include "Vehicule.h"
#include "Trajet.h"
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
	void plusCourtChemin(Sommet* sommetDepart, Sommet* sommetDestination, Vehicule& vehicule);
	Sommet* trouverSommet(string identifiant) const;

private:
	vector<Sommet*> sommets_;
};
