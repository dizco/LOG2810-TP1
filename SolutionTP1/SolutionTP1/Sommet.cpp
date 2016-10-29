#include "Sommet.h"

Sommet::Sommet() 
{
}

Sommet::Sommet(string identifiant, string type)
	: identifiant_(identifiant), carburant_(type)//, voisinsPossiblesExtraits_(false)
{
}

Sommet::~Sommet()
{
}

string Sommet::getIdentifiant() const {
	return identifiant_;
}

string Sommet::getType() const {
	return carburant_;
}

void Sommet::addVoisin(Sommet* sommetVoisin, int distance) {
	voisins_.push_back(make_pair(sommetVoisin, distance));
}

string Sommet::printVoisins() const {
	string result = "(";
	bool isFirst = true;
	for (auto i = voisins_.begin(); i != voisins_.end(); i++) {
		if (!isFirst)
			result += ", ";
		result += (*i).first->getIdentifiant();
		isFirst = false;
	}
	return result += ")";
}

bool Sommet::peutRecharger(string type) const {
	return ((carburant_ == "essence" && (type == "essence" || type == "hybrid"))
		|| (carburant_ == "hybrid" && (type == "essence" || type == "hybride" || type == "electrique"))
		|| (carburant_ == "electrique" && (type == "hybride" || type == "electrique")));
}

/*void Sommet::setVoisinsPossiblesExtraits(const bool valeur) {
	voisinsPossiblesExtraits_ = valeur;
}
bool Sommet::voisinsPossiblesExtraits() const {
	return false;
}*/

void Sommet::setVoisins(const vector<pair<Sommet*, int>>& vecteur) {
	voisins_ = vecteur;
}

vector<pair<Sommet*, int>> Sommet::getVoisins() const {
	return voisins_;
}

vector<Sommet*> Sommet::getVoisinsSansDistance() const {
	vector<Sommet*> resultat;
	for (auto i = voisins_.begin(); i != voisins_.end(); i++) {
		resultat.push_back((*i).first);
	}
	return resultat;
}

vector<pair<Sommet*, int>> Sommet::getVoisinsPossibles(int distance) const {
	vector<pair<Sommet*, int>> voisinsDisponibles;
	for (auto i = voisins_.begin(); i != voisins_.end(); i++) {
		if ((*i).second <= distance) {
			voisinsDisponibles.push_back(*i);
		}
	}
	return voisinsDisponibles;
}