
#include "Vehicule.h"

Vehicule::Vehicule()
{
}

Vehicule::~Vehicule()
{
}

void Vehicule::setAutonomieActuelle(int autonomie) {
	autonomieActuelle_ = autonomie;
}
void Vehicule::setAutonomieMax(int autonomie) {
	autonomieMax_ = autonomie;
}
void Vehicule::setCarburant(string carburant) {
	carburant_ = carburant;
}

int Vehicule::getAutonomieActuelle() const {
	return autonomieActuelle_;
}
int Vehicule::getAutonomieMax() const {
	return autonomieMax_;
}
string Vehicule::getCarburant() const {
	return carburant_;
}

void Vehicule::recharger() {
	autonomieActuelle_ = autonomieMax_;
}

bool Vehicule::informationsEnregistrees() const {
	return !(autonomieActuelle_ > autonomieMax_ || autonomieMax_ == 0 || carburant_ == "");
}

ostream& operator<< (ostream& stream, const Vehicule& vehicule) {
	stream << "Carburant : " << vehicule.carburant_
		<< ". Autonomie actuelle : " << vehicule.autonomieActuelle_
		<< ". Autonomie max : " << vehicule.autonomieMax_ << endl;
	return stream;
}