#include "entity.hpp"
#include "world/plant/tables.hpp"
#include <core/position_check.hpp>

// Plants are those farmable by player, but do not regrow over multiple seasons
uint32_t PlantDatabase::getPlantIndex()
{
	if (nextPlantIndex.empty())
		return size;
	return nextPlantIndex.pop();
}

bool PlantDatabase::viableHarvest(int plantIndex)
{
		Plant plant = plants[plantIndex];
		if (growths[plantIndex] < fullMaturityAges[plant] * maxAges[plant])
				return true;
		return false;
}

void PlantDatabase::excreteSeed(AnimalDatabase& database, int animalIndex, TileDatabase& tiles, Plant plant)
{
	Coord coords = database.coords[animalIndex];
	spawnSeed(plant, tiles.getNearestEmptyTile(coords));
}
