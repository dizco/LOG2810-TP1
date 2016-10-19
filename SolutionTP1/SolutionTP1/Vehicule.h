#pragma once

#include <string>

using namespace std;

class Vehicule
{
public:
	Vehicule();
	~Vehicule();

private:
	int autonomie_;
	string carburant_;
};

