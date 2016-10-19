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
				cout << "Option invalide. Veuillez r�essayer." << endl;
				break;
			case CaracteristiquesVehicule: { //a
				string typeEnergie = "";
				bool energieValide = false;
				int autonomieMax = 0;
				bool autonomieMaxValide = false;
				int autonomieRestante = 0;
				bool autonomieRestanteValide = false;

				cout << "Choisir caract�ristiques du v�hicule." << endl;

				while (!energieValide) {
				cout << "Quelle est la source d'�nergie du v�hicule? Les valeurs accept�es sont: electrique, hybride ou essence" << endl;
				cin >> typeEnergie;
				if (typeEnergie == "electrique" || typeEnergie == "hybride" || typeEnergie == "essence") {
					energieValide = true;
					//on ajoute dans le parametre de la classe vehicule qui correspond avec le setter.

				}else {
					cout << "Vous devez entrer des valeurs valides. Les types d'�nergie accept�es sont: electrique, hybride ou essence" << endl;
					}
			}

				while (!autonomieMax) {
					cout << "Quelle est l'autonomie maximale du v�hicule en km?" << endl;
					cin >> autonomieMax;
					if ((autonomieMax > 0)&&(autonomieMax<999999)) {
						autonomieMaxValide = true;
					}
					else{
						cout << "L'autonomie du v�hicule doit �tre sup�rieure � 0" << endl;
					}
				}

				while (!autonomieRestante) {
					cout << "quelle est l'autonomie actuelle du v�hicule en km?" << endl;
					cin >> autonomieRestante;
					if ((autonomieRestante > 0) && (autonomieRestante <= autonomieMax)) {
						autonomieRestanteValide = true;
					}
					else {
						cout << "L'autonomie restante du v�hicule doit etre sup�rieure � 0, et inf�rieure ou �gale � l'autonomie maximale." << endl;
					}
				}




				//cout << "Confirmez que vous avez un v�hicule " << typeEnergie << " km avec une autonomie maximale de: " << autonomieMax << " km mais une autonomie actuelle de: " << autonomieRestante << endl;
				


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
				cout << "D�terminer le plus court chemin.";
				break;
		}
	} while (option != Quitter);

	return 1;
}

void afficherMenu() {
	cout << "(a) Demander les caract�ristiques du v�hicule." << endl
		<< "(b) Mettre � jour la carte." << endl
		<< "(c) D�terminer le plus court chemin." << endl
		<< "(d) Quitter." << endl;
}

OptionsDisponibles lireOptionChoisie() {
	std::string optionChoisie = "";
	cin >> optionChoisie;
	
	//TODO: prendre (a) comme param�tre plutot que a
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
