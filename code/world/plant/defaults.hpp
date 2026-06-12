#include "enum.hpp"
#include "tables.hpp"
#include <core/data.hpp>

Time RANDOM_PLANT_AGE(Plant plant)
{
		return maxAges[plant] * random_bool->next();
}

void getRandomPlantStartingTileWater()
{
		
}
