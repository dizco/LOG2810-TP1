#pragma once
#include <string>
#include <vector>

//#include "Voisin.h"

using namespace std;

class Sommet
{
public:
	Sommet();
	Sommet(string identifiant, string type);
	~Sommet();

	string getIdentifiant() const;
	string getType() const;
	void addVoisin(Sommet* sommetVoisin, int distance);
	string printVoisins() const;
	bool peutRecharger(string type) const;

	/*void setVoisinsPossiblesExtraits(const bool valeur);
	bool voisinsPossiblesExtraits() const;*/

	void setVoisins(const vector<pair<Sommet*, int>>& vecteur);
	vector<pair<Sommet*, int>> getVoisins() const;
	vector<Sommet*> getVoisinsSansDistance() const;
	vector<pair<Sommet*, int>> getVoisinsPossibles(int distance) const;

private:
	vector<pair<Sommet*,int>> voisins_;
	string identifiant_;
	string carburant_;
	//bool voisinsPossiblesExtraits_;

};

