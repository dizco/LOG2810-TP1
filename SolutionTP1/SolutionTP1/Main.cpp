#include <iostream>
#include <string>

#include "Graphe.h"
#include "Vehicule.h"

using namespace std;

enum OptionsDisponibles { Invalide, CaracteristiquesVehicule, MettreAJourCarte, DeterminerChemin, Quitter };
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
				cout << "Option invalide. Veuillez reessayer. Assurez-vous d'inscrire l'option sous le format \"(x)\"." << endl;
				break;
			case CaracteristiquesVehicule: //(a)
				vehicule = demanderCaracteristiquesDuVehicule();
				break;
			case MettreAJourCarte: //(b)
			{
				string fileName = "";
				cout << "Entrez le nom du nouveau fichier : ";
				cin >> fileName;
				graphe.creerGraphe(fileName, true);
			}
			break;
			case DeterminerChemin: //(c)
				executerPlusCourtChemin(graphe, vehicule);
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
	string optionChoisie = "";
	cin >> optionChoisie;

	if (optionChoisie.length() != 3 || !(optionChoisie[1] >= 'a' && optionChoisie[1] <= 'd')) {
		return OptionsDisponibles::Invalide;
	}
	char lettre = optionChoisie[1];
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
}

/*
Demande les caracteristiques du vehicule et les enregistre.
*/
Vehicule demanderCaracteristiquesDuVehicule() {
	Vehicule vehicule;
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
			cout << "Vous devez entrer des valeurs valides. Les types d'energie acceptees sont: electrique, hybride ou essence." << endl;
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
			cout << "L'autonomie du vehicule doit etre superieure a 0 et inferieure a 100000." << endl;
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

/*
Demande les informations de départ et de destination puis effectue l'algorithme.
*/
void executerPlusCourtChemin(Graphe& graphe, Vehicule& vehicule) {
	if (!vehicule.informationsEnregistrees()) {
		cout << "Veuillez entrer les informations du vehicule avant d'executer le plus court chemin." << endl;
		return;
	}
	if (!graphe.informationsEnregistrees()) {
		cout << "Veuillez entrer un graphe avant d'executer le plus court chemin." << endl;
		return;
	}

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
