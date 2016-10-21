#include <iostream>
#include <string>

#include "Graphe.h"
#include "Vehicule.h"

using namespace std;

enum OptionsDisponibles { Invalide, CaracteristiquesVehicule, MettreAJourCarte, DeterminerChemin, Quitter };
void afficherMenu();
OptionsDisponibles lireOptionChoisie();
Vehicule demanderCaracteristiquesDuVehicule();

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
				graphe.creerGraphe(fileName);
			}
			break;
			case DeterminerChemin: //c
				cout << "Determiner le plus court chemin.";
				break;
		}
	} while (option != Quitter);

	return 1;
}

void afficherMenu() {
	cout << "(a) Demander les caracteristiques du vehicule." << endl
		<< "(b) Mettre a jour la carte." << endl
		<< "(c) Determiner le plus court chemin." << endl
		<< "(d) Quitter." << endl;
}

OptionsDisponibles lireOptionChoisie() {
	std::string optionChoisie = "";
	cin >> optionChoisie;

	//TODO: prendre (a) comme paramètre plutot que a
	if (optionChoisie.length() != 1 || !(optionChoisie[0] >= 'a' && optionChoisie[0] <= 'd')) {
		return OptionsDisponibles::Invalide;
	}
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