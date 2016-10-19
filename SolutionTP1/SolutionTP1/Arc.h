#pragma once

#include "Sommet.h"

class Arc
{
public:
	Arc();
	Arc(Sommet* sommet1, Sommet* sommet2, int distance);
	~Arc();

private:
	int distance_;
	Sommet* sommet1_;
	Sommet* sommet2_;

};

