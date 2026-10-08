#include <data/run/plant_database.hpp>
#include <core/position_check.hpp>

Time random_plant_age(Plant plant)
{
		return MAX_AGES[plant] * random_bool->next();
}

void get_random_plant_starting_tile_water() {}

// Plants are those farmable by player, but do not regrow over multiple seasons
uint32_t plant::Database::get_plant_index()
{
	if (next_plant_index.empty())
		return size;
	return next_plant_index.pop();
}

bool plant::Database::viable_harvest(int plant_index)
{
		Plant plant = plants[plant_index];
		if (growths[plant_index] < FULL_MATURITY_AGES[plant] * MAX_AGES[plant])
				return true;
		return false;
}

void plant::Database::excrete_seed(animal::Database& database, int animal_index, tile::Database& tiles, Plant plant)
{
	Coord coords = database.coords[animal_index];
	spawn_seed(plant, tiles.get_nearest_empty_tile(coords));
}
