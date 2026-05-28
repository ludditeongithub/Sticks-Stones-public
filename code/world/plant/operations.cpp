#include "entity.hpp"
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
	if (growthAmt[plantIndex] < maturityThreshold[static_cast<int>(plants[plantIndex])])
		return true;
}

void PlantDatabase::excreteSeed(AnimalDatabase& database, TileDatabase& tiles, int animalIndex, Plant plant)
{
	Coord coords = database.coords[animalIndex];
	spawnSeed(plant, tiles.getNearestEmptyTile(coords));
}

void PlantDatabase::plant(int unitIndex, Plant plant)
{
	std::pair<int, int> coords = currentCoords[animalIndex];
	addPlant(plant, findNearestAdjacentEmptyTile(coords));
}
