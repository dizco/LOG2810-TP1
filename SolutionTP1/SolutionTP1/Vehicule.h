#pragma once

#include <string>

//#include "Sommet.h"

using namespace std;

class Vehicule
{
public:
	Vehicule();
	~Vehicule();

	void setAutonomieActuelle(int autonomie);
	void setAutonomieMax(int autonomie);
	void setCarburant(string carburant);

	int getAutonomieActuelle() const;
	int getAutonomieMax() const;
	string getCarburant() const;

	void recharger();
	bool informationsEnregistrees() const;

	friend ostream& operator<< (ostream& stream, const Vehicule& vehicule);

private:
	int autonomieActuelle_;
	int autonomieMax_;
	string carburant_;
};

