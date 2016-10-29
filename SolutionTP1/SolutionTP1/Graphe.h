#pragma once
#include <string>
#include <vector>

#include "Sommet.h"
#include "Vehicule.h"

using namespace std;

class Graphe
{
public:
	Graphe();
	~Graphe();
	void detruireSommets();

	void creerGraphe(string fileName, bool afficher);
	void lireGraphe();
	vector<Sommet*> extractionGraphe(Sommet* sommetDepart, const Vehicule& vehicule) const;
	void plusCourtChemin(Sommet* sommetDepart, Sommet* sommetDestination, Vehicule& vehicule);
	Sommet* trouverSommet(string identifiant) const;

	bool informationsEnregistrees() const;

private:
	string fileName_;
	vector<Sommet*> sommets_;

	int positionDuPlusPetitSommetEncoreDisponible(vector<Sommet*>& disponibles, vector<pair<Sommet*, pair<int, Sommet*>>>& vecteur) const;
	int trouverPositionSommet(vector<pair<Sommet*, pair<int, Sommet*>>>& vecteur, string identifiant) const;
	int trouverPositionSommet(vector<Sommet*>& vecteur, string identifiant) const;
	vector<Sommet*> extraireTrajet(vector<pair<Sommet*, pair<int, Sommet*>>>& vecteur, Sommet* sommetDepart, Sommet* sommetDestination) const;
	void afficherTrajet(vector<Sommet*>& vecteur) const;
	int calculerAutonomieRestante(const Vehicule& vehicule, vector<pair<Sommet*, pair<int, Sommet*>>>& vecteur, Sommet* sommetDepart, Sommet* sommetDestination) const;

	vector<pair<Sommet*, int>> extraireVoisinsDeSommet(Sommet* sommet, Vehicule vehicule) const;
};
