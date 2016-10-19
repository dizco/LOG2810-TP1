#include "Sommet.h"

Sommet::Sommet() 
{
}

Sommet::Sommet(string identifiant, string type)
	: identifiant_(identifiant), carburant_(type)
{
}

Sommet::~Sommet()
{
}

string Sommet::getIdentifiant() const {
	return identifiant_;
}