#include <iostream>
#include <string>

#include "Graphe.h"
#include "Vehicule.h"

using namespace std;

enum OptionsDisponibles { Invalide, CaracteristiquesVehicule, MettreAJourCarte, DeterminerChemin, Quitter, Testing, AutomaticTests };
void afficherMenu();
OptionsDisponibles lireOptionChoisie();
Vehicule demanderCaracteristiquesDuVehicule();
void executerPlusCourtChemin(Graphe& graphe, Vehicule& vehicule);

int main()
{
	Graphe graphe;
	Vehicule vehicule;
	OptionsDisponibles option;
	do {
		afficherMenu();
		option = lireOptionChoisie();
		switch (option) {
			case Invalide:
				cout << "Option invalide. Veuillez reessayer." << endl;
				break;
			case CaracteristiquesVehicule: //a
				vehicule = demanderCaracteristiquesDuVehicule();
				break;
			case MettreAJourCarte: //b
			{
				string fileName = "";
				cout << "Entrez le nom du nouveau fichier : ";
				cin >> fileName;
				graphe.creerGraphe(fileName, true);
			}
			break;
			case DeterminerChemin: //c
				executerPlusCourtChemin(graphe, vehicule);
				break;
			case Testing:
				vehicule = Vehicule();
				vehicule.setCarburant("essence");
				vehicule.setAutonomieMax(5);
				vehicule.setAutonomieActuelle(5);

				graphe.creerGraphe("graphe1.txt", true);
				executerPlusCourtChemin(graphe, vehicule);
				break;
			case AutomaticTests:
				vehicule = Vehicule();
				vehicule.setCarburant("essence");
				vehicule.setAutonomieMax(20);
				vehicule.setAutonomieActuelle(2);

				graphe.creerGraphe("graphe1.txt", true);
				break;
		}
	} while (option != Quitter);

	return 1;
}

void afficherMenu() {
	cout << endl << "(a) Demander les caracteristiques du vehicule." << endl
		<< "(b) Mettre a jour la carte." << endl
		<< "(c) Determiner le plus court chemin." << endl
		<< "(d) Quitter." << endl;
}

OptionsDisponibles lireOptionChoisie() {
	std::string optionChoisie = "";
	cin >> optionChoisie;

	//TODO: prendre (a) comme paramètre plutot que a
	//TODO: Enlever option testing
	/*if (optionChoisie.length() != 1 || !(optionChoisie[0] >= 'a' && optionChoisie[0] <= 'd')) {
		return OptionsDisponibles::Invalide;
	}*/
	char lettre = optionChoisie[0];
	if (lettre == 'a') {
		return OptionsDisponibles::CaracteristiquesVehicule;
	}
	else if (lettre == 'b') {
		return OptionsDisponibles::MettreAJourCarte;
	}
	else if (lettre == 'c') {
		return OptionsDisponibles::DeterminerChemin;
	}
	else if (lettre == 'd') {
		return OptionsDisponibles::Quitter;
	}
	else if (lettre == 't') {
		return OptionsDisponibles::Testing;
	}
	else if (lettre == 'w') {
		return OptionsDisponibles::AutomaticTests;
	}
}

Vehicule demanderCaracteristiquesDuVehicule() {
	Vehicule vehicule;

	//cout << "Choisir caractéristiques du véhicule." << endl;

	bool energieValide = false;
	while (!energieValide) {
		string typeEnergie = "";
		cout << "Quelle est la source d'energie du vehicule? Les valeurs acceptees sont: electrique, hybride ou essence" << endl;
		cin >> typeEnergie;
		if (typeEnergie == "electrique" || typeEnergie == "hybride" || typeEnergie == "essence") {
			energieValide = true;
			vehicule.setCarburant(typeEnergie);
		}
		else {
			cout << "Vous devez entrer des valeurs valides. Les types d'energie acceptees sont: electrique, hybride ou essence" << endl;
		}
	}

	bool autonomieMaxValide = false;
	while (!autonomieMaxValide) {
		int autonomieMax = 0;
		cout << "Quelle est l'autonomie maximale du vehicule en km (1 a 999 999)?" << endl;
		cin >> autonomieMax;
		if ((autonomieMax > 0) && (autonomieMax < 100000)) {
			autonomieMaxValide = true;
			vehicule.setAutonomieMax(autonomieMax);
		}
		else {
			cout << "L'autonomie du vehicule doit etre superieure a 0" << endl;
		}
	}

	bool autonomieRestanteValide = false;
	while (!autonomieRestanteValide) {
		int autonomieRestante = 0;
		cout << "Quelle est l'autonomie actuelle du vehicule en km?" << endl;
		cin >> autonomieRestante;
		if ((autonomieRestante > 0) && (autonomieRestante <= vehicule.getAutonomieMax())) {
			autonomieRestanteValide = true;
			vehicule.setAutonomieActuelle(autonomieRestante);
		}
		else {
			cout << "L'autonomie restante du vehicule doit etre superieure a 0, et inferieure ou egale a l'autonomie maximale." << endl;
		}
	}

	cout << "Vehicule enregistre : " << vehicule << endl;

	return vehicule;
}

void executerPlusCourtChemin(Graphe& graphe, Vehicule& vehicule) {
	string idSommetDepart = "";
	cout << "Identifiant du sommet de depart : ";
	cin >> idSommetDepart;
	string idSommetDestination = "";
	cout << "Identifiant du sommet de destination : ";
	cin >> idSommetDestination;

	Sommet* sommetDepart;
	Sommet* sommetDestination;
	try {
		sommetDepart = graphe.trouverSommet(idSommetDepart);
		sommetDestination = graphe.trouverSommet(idSommetDestination);

		graphe.plusCourtChemin(sommetDepart, sommetDestination, vehicule);
	}
	catch (const invalid_argument& e) {
		cout << "Ce sommet n'existe pas. Veuillez reessayer." << endl;
	}
}

void testerPlusCourtChemin(Graphe& graphe, Vehicule& vehicule, string depart, string destination) {
	Sommet* sommetDepart;
	Sommet* sommetDestination;
	try {
		sommetDepart = graphe.trouverSommet(depart);
		sommetDestination = graphe.trouverSommet(destination);

		graphe.plusCourtChemin(sommetDepart, sommetDestination, vehicule);
	}
	catch (const exception& e) {
		cout << "Exception : " << e.what() << endl;
	}
}