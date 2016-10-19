#pragma once
#include <string>
#include <vector>

#include "Sommet.h"
#include "Arc.h"

class Graphe
{
public:
	Graphe();
	~Graphe();

	void creerGraphe(std::string fileName);
	void lireGraphe();
	void extractionGraphe();
	void plusCourtChemin();

private:
	Sommet* trouverSommet(string identifiant) const;

	vector<Sommet*> sommets_;
	vector<Arc*> arcs_;
};
