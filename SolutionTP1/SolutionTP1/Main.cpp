#include <iostream>
#include <string>

#include "Graphe.h"

using namespace std;

enum OptionsDisponibles { Invalide, CaracteristiquesVehicule, MettreAJourCarte, DeterminerChemin, Quitter };
void afficherMenu();
OptionsDisponibles lireOptionChoisie();

int main() 
{
	Graphe graphe;
	OptionsDisponibles option;
	do {
		afficherMenu();
		option = lireOptionChoisie();
		switch (option) {
			case Invalide:
				cout << "Option invalide. Veuillez réessayer." << endl;
				break;
			case CaracteristiquesVehicule:  //a
				cout << "Choisir caractéristiques du véhicule." << endl;
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
				cout << "Déterminer le plus court chemin.";
				break;
		}
	} while (option != Quitter);

	return 1;
}

void afficherMenu() {
	cout << "(a) Demander les caractéristiques du véhicule." << endl
		<< "(b) Mettre à jour la carte." << endl
		<< "(c) Déterminer le plus court chemin." << endl
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
	if (lettre == 'a'){
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
