#pragma once

/* precipitation
*/

#include <world/plant/database.hpp>
#include "core/data.hpp"
#include "world/chunk/data.hpp"
#include "world/tile/database.hpp"

void World::update_weather()
{
	for (size_t i = 0; i < CHUNK_AMOUNT; i++)
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

inline void World::apply_precipitation(TileDatabase* tile_db, uint16_t chunk, bool heavy)
{
	Array<Liquid> &waters = tile_db->waters;
	Liquid amount = (precipitation_cores[chunk] + (precipitation_cores[chunk] * precipitation_variance.next() * PRECIPITATION_VARIANCE_FACTOR)) * MM_PER_PRECIPITATION;
	if (heavy) amount *= HEAVY_PRECIPITATION_FACTOR;
	for (size_t i = chunk * CHUNK_SIZE; i < chunk * CHUNK_SIZE + CHUNK_SIZE; i++) waters[i] += amount;	
}	

void World::apply_weather(TileDatabase* tile_db)
{
	for (size_t i = 0; i < CHUNK_AMOUNT; i++) {
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
