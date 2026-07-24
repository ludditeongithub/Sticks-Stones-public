#include "database.hpp"
#include "world/plant/tables.hpp"
#include <core/position_check.hpp>

// Plants are those farmable by player, but do not regrow over multiple seasons
uint32_t PlantDatabase::get_plant_index()
{
	if (next_plant_index.empty())
		return size;
	return next_plant_index.pop();
}

bool PlantDatabase::viable_harvest(int plant_index)
{
		Plant plant = plants[plant_index];
		if (growths[plant_index] < full_maturity_ages[plant] * max_ages[plant])
				return true;
		return false;
}

void PlantDatabase::excrete_seed(AnimalDatabase& database, int animal_index, TileDatabase& tiles, Plant plant)
{
	Coord coords = database.coords[animal_index];
	spawn_seed(plant, tiles.get_nearest_empty_tile(coords));
}
