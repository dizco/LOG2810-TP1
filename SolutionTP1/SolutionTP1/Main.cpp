#include <iostream>
#include <string>

using namespace std;

enum OptionsDisponibles { Invalide, CaracteristiquesVehicule, MettreAJourCarte, DeterminerChemin, Quitter };
void afficherMenu();
OptionsDisponibles lireOptionChoisie();

int main() 
{
	OptionsDisponibles option;
	do {
		afficherMenu();
		option = lireOptionChoisie();
		switch (option) {
			case Invalide:
				cout << "Option invalide. Veuillez r�essayer." << endl;
				break;
			case CaracteristiquesVehicule:
				cout << "Choisir caract�ristiques du v�hicule." << endl;
				break;
			case MettreAJourCarte:
				cout << "Mettre � jour la carte." << endl;
				break;
			case DeterminerChemin:
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
	
	//TODO: prendre (a) comme paramatre plutot que a
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