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
			case CaracteristiquesVehicule: { //a
				string typeEnergie = "";
				bool energieValide = false;
				int autonomieMax = 0;
				bool autonomieMaxValide = false;
				int autonomieRestante = 0;
				bool autonomieRestanteValide = false;

				cout << "Choisir caractéristiques du véhicule." << endl;

				while (!energieValide) {
				cout << "Quelle est la source d'énergie du véhicule? Les valeurs acceptées sont: electrique, hybride ou essence" << endl;
				cin >> typeEnergie;
				if (typeEnergie == "electrique" || typeEnergie == "hybride" || typeEnergie == "essence") {
					energieValide = true;
					//on ajoute dans le parametre de la classe vehicule qui correspond avec le setter.

				}else {
					cout << "Vous devez entrer des valeurs valides. Les types d'énergie acceptées sont: electrique, hybride ou essence" << endl;
					}
			}

				while (!autonomieMax) {
					cout << "Quelle est l'autonomie maximale du véhicule en km?" << endl;
					cin >> autonomieMax;
					if ((autonomieMax > 0)&&(autonomieMax<999999)) {
						autonomieMaxValide = true;
					}
					else{
						cout << "L'autonomie du véhicule doit être supérieure à 0" << endl;
					}
				}

				while (!autonomieRestante) {
					cout << "quelle est l'autonomie actuelle du véhicule en km?" << endl;
					cin >> autonomieRestante;
					if ((autonomieRestante > 0) && (autonomieRestante <= autonomieMax)) {
						autonomieRestanteValide = true;
					}
					else {
						cout << "L'autonomie restante du véhicule doit etre supérieure à 0, et inférieure ou égale à l'autonomie maximale." << endl;
					}
				}




				//cout << "Confirmez que vous avez un véhicule " << typeEnergie << " km avec une autonomie maximale de: " << autonomieMax << " km mais une autonomie actuelle de: " << autonomieRestante << endl;
				


			}
										   
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
