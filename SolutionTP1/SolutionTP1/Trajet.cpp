
#include "Trajet.h"

Trajet::Trajet()
	: distanceTotale_(0)
{
}

Trajet::~Trajet()
{
}

void Trajet::ajouterSommet(Sommet* sommet, int distance) {
	sommets_.push_back(sommet);
	distanceTotale_ += distance;
}

vector<Sommet*> Trajet::getSommets() const {
	return sommets_;
}

int Trajet::getDistance() const {
	return distanceTotale_;
}