#pragma once
#include <string>

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

};
