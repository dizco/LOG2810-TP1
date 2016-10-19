#pragma once
#include <string>
#include <vector>

using namespace std;

class Sommet
{
public:
	Sommet();
	Sommet(string identifiant, string type);
	~Sommet();

	string getIdentifiant() const;

private:
	//vector<Arc*> voisins_;
	string identifiant_;
	string carburant_;

};

