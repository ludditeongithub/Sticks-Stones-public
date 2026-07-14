#include "database.hpp"
#include "world/plant/tables.hpp"
#include <core/position_check.hpp>

// Plants are those farmable by player, but do not regrow over multiple seasons
uint32_t PlantDatabase::get_plant_index()
{
	if (nextPlantIndex.empty())
		return size;
	return nextPlantIndex.pop();
}

bool PlantDatabase::viable_harvest(int plantIndex)
{
		Plant plant = plants[plantIndex];
		if (growths[plantIndex] < fullMaturityAges[plant] * maxAges[plant])
				return true;
		return false;
}

void PlantDatabase::excrete_seed(AnimalDatabase& database, int animalIndex, TileDatabase& tiles, Plant plant)
{
	Coord coords = database.coords[animalIndex];
	spawnSeed(plant, tiles.getNearestEmptyTile(coords));
}
