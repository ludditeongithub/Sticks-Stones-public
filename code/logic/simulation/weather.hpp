#pragma once

/* precipitation
*/

#include <data/run/plant_database.hpp>

#include "data/const/chunk_data.hpp"
#include "data/run/tile_database.hpp"

void World::update_weather()
{
	for (size_t i = 0; i < chunk_amount; i++)
	{
		cloud_values[i] += next_cloud_changes.next();
		precipitation_values[i] += next_precipitation_changes.next();
	}
}

inline void apply_heavy_cloud_effects(uint16_t chunk)
{
	//TODO: rendering
}

inline void apply_light_cloud_effects(uint16_t chunk)
{
	//TODO: rendering
}

inline void World::apply_precipitation(tile::Database* tile_db, uint16_t chunk, bool heavy)
{
	Array<Liquid> &waters = tile_db->waters;
	Liquid amount = (precipitation_cores[chunk] + (precipitation_cores[chunk] * precipitation_variance.next() * PRECIPITATION_VARIANCE_FACTOR)) * MM_PER_PRECIPITATION;
	if (heavy) amount *= HEAVY_PRECIPITATION_FACTOR;
	for (size_t i = chunk * chunk_size; i < chunk * chunk_size + chunk_size; i++) waters[i] += amount;	
}	

void World::apply_weather(tile::Database* tile_db)
{
	for (size_t i = 0; i < chunk_amount; i++) {
		if (cloud_values[i] > MIN_HEAVY_CLOUDS)
		{
			apply_heavy_cloud_effects(i);
					if (precipitation_values[i] > PRECIPITATION_MIN) apply_precipitation(tile_db, i, true);
					
		}
		else if (cloud_values[i] > MIN_LIGHT_CLOUDS)
		{
			apply_light_cloud_effects(i);
			if (precipitation_values[i] > PRECIPITATION_MIN) apply_precipitation(tile_db, i, true);
		}

	}
}	
