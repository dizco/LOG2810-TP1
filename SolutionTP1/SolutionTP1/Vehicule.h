#pragma once

#include <string>

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

	friend ostream& operator<< (ostream& stream, const Vehicule& vehicule);

private:
	int autonomieActuelle_;
	int autonomieMax_;
	string carburant_;
};

