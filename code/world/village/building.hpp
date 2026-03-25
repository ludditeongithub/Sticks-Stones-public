#include "buildings.h"

struct Building
{
	Buildable wallMaterial;
	Buildable roofMaterial;
	vector<std : pair<int, int>> tiles;
}

struct Workshop : Building
{
	WorkFunction function;
	Buildable table;
}

struct House : Building
{
	Buildable beds;
	int numBeds;
	vector<Container> container;
	vector<Decor> decors;
}

struct Tent : House
{
	wallMaterial = Buildable::TentSticks;
	roofMaterial = Buildable::TentCover;
}

struct MainTent : AncientTent
{
}
