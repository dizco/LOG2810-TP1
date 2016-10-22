#pragma once

#include <vector>

#include "Sommet.h"

class Trajet
{
public:
	Trajet();
	~Trajet();

	void ajouterSommet(Sommet* sommet, int distance);

	vector<Sommet*> getSommets() const;
	int getDistance() const;

private:
	vector<Sommet*> sommets_;
	int distanceTotale_;
};
