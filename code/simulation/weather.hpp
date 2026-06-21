#pragma once

/* precipitation
*/

#include <world/plant/database.hpp>
#include "core/data.hpp"
#include "world/chunk/data.hpp"
#include "world/tile/database.hpp"

void World::updateWeather()
{
	for (size_t i = 0; i < CHUNK_AMOUNT; i++)
	{
		cloudValues[i] += nextCloudChanges.next();
		precipitationValues[i] += nextPrecipitationChanges.next();
	}
}

inline void applyHeavyCloudEffects(uint16_t chunk)
{
	//TODO: rendering
}

inline void applyLightCloudEffects(uint16_t chunk)
{
	//TODO: rendering
}

inline void World::applyPrecipitation(TileDatabase* tileDB, uint16_t chunk, bool heavy)
{
	Array<Liquid> &waters = tileDB->waters;
	Liquid amount = (precipitationCores[chunk] + (precipitationCores[chunk] * precipitationVariance.next() * PRECIPITATION_VARIANCE_FACTOR)) * MM_PER_PRECIPITATION;
	if (heavy) amount *= HEAVY_PRECIPITATION_FACTOR;
	for (size_t i = chunk * CHUNK_SIZE; i < chunk * CHUNK_SIZE + CHUNK_SIZE; i++) waters[i] += amount;	
}	

void World::applyWeather(TileDatabase* tileDB)
{
	for (size_t i = 0; i < CHUNK_AMOUNT; i++) {
		if (cloudValues[i] > MIN_HEAVY_CLOUDS)
		{
			applyHeavyCloudEffects(i);
					if (precipitationValues[i] > PRECIPITATION_MIN) applyPrecipitation(tileDB, i, true);
					
		}
		else if (cloudValues[i] > MIN_LIGHT_CLOUDS)
		{
			applyLightCloudEffects(i);
			if (precipitationValues[i] > PRECIPITATION_MIN) applyPrecipitation(tileDB, i, true);
		}

	}
}	
