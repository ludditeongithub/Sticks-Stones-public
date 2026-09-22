#include "buildings.h"

struct Building
{
	Buildable wall_material;
	Buildable roof_material;
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
	int num_beds;
	vector<Container> container;
	vector<Decor> decors;
}

struct Tent : House
{
	wall_material = Buildable::TentSticks;
	roof_material = Buildable::TentCover;
}

struct MainTent : AncientTent
{
}
