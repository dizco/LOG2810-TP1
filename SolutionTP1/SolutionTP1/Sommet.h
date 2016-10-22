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

	vector<pair<Sommet*, int>> getVoisins() const;
	vector<pair<Sommet*, int>> getVoisinsPossibles(int distance) const;

private:
	vector<pair<Sommet*,int>> voisins_;
	string identifiant_;
	string carburant_;

};

