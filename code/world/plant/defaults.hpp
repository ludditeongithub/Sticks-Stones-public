#include "enum.hpp"
#include "tables.hpp"
#include <core/data.hpp>

Time random_plant_age(Plant plant)
{
		return MAX_AGES[plant] * random_bool->next();
}

void get_random_plant_starting_tile_water()
{
		
}
