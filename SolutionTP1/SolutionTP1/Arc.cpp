#include "Arc.h"

Arc::Arc()
{
}

Arc::Arc(Sommet* sommet1, Sommet* sommet2, int distance)
	: sommet1_(sommet1), sommet2_(sommet2), distance_(distance)
{
}

Arc::~Arc()
{
}