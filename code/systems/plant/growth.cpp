#include "updates.hpp"
#include "core/containers.hpp"
#include "core/data.hpp"
#include "core/random.hpp"
#include "pathfinding.hpp"
#include "world/animal/enum.hpp"
#include "world/chunk/data.hpp"
#include "world/plant/tables.hpp"
#include <cstddef>
#include <world/plant/database.hpp>
#include "world/world.hpp"
#include <world/item/database.hpp>
#include <optional>

// TODO: eval water
	// Water
		// float wr = waterRequired[p];
		// uint16_t wd = waterDeath[p];
		// if (tileWater[i] > wr) {
		//   lastFullyWatered[i] = time;
		// } else if (time - lastFullyWatered[i] > wd) {
		//   alive[i] = true;
		//   continue;
		// } else nextGrowth *= LOW_WATER_MULT;
		

inline void evalTemperature(World& world, int chunkIndex, Plant p, float& nextGrowth, auto&& alive, bool regrowth = false)
{
	float dmin = tempDeathMin[p];
		Temp dmax = tempDeathMax[p];
		Temp ngmin = tempGrowthMin[p];
		Temp ngmax = tempGrowthMax[p];
		Temp omin = tempOptimalMin[p];
		Temp omax = tempOptimalMax[p];

		Temp temp = world.temperatures[chunkIndex];		
		
		if (temp < omax && temp > omin)
		{
		}
		else if (temp > ngmin && temp < ngmax)
		{
			nextGrowth = 0.0;
			if (regrowth) nextGrowth = -1.0;
		}
		else if (temp < dmin || temp > dmax)
		{
			alive = false;			
		}
		else
		{
			nextGrowth *= UNOPTIMAL_TEMP_MULT;
		}
}

inline void evalSunlight(World& world, int chunkIndex, float& nextGrowth, Array2D<float>& dailyInsolations, Array<float>& cloudCovers, Plant p, bool regrowth = false)
{
		uint16_t latitude = world.getChunkLatitude(chunkIndex);
		uint16_t timeZone = world.getChunkTimeZone(chunkIndex);
		float is = dailyInsolations[latitude][timeZone];
		float psun = perfectSunlight[p];
		// sunlight (from 0.0 to 1.0)
		if (is <= 0.0)
		{
			nextGrowth = 0.0; 
		}
		else
		{
			// factor cloud cover
			float ccf = cloudCovers[chunkIndex] * MAX_CLOUD_FACTOR;
			float sunlight = is / (1 + ccf);
			float sf = 1.0;
			if (sunlight < psun)
				sf = normalize(sunlight, 0, psun);
			nextGrowth *= sf;
		}
}

// OPTI: have plant temp values be precalcuated so chunk temps is accessed
// faster
void PlantDatabase::updatePlants(World& world, Array2D<float> &dailyInsolations, Array<float> &cloudCovers, Time timePassed)
{
	for (uint32_t i = 0; i < plantList.size(); i++)
	{
		Plant p = plantList[i];		
		
		if (plantList[i] == Plant::NONE)
			continue;
		float nextGrowth = 1.0;
		const Coord pos = coords[i];
		uint32_t chunkIndex = getChunkIndexFromTile(pos);
		evalSunlight(world, chunkIndex, nextGrowth, world.dailyInsolations, world.cloudCovers, p);
		evalTemperature(world, chunkIndex, p, nextGrowth, alive[i]);
		if (!alive[i]) continue;		

		growths[i] += nextGrowth * timePassed;
	}
}

void RegrowthPlantDatabase::updateRegrowthPlants(ItemDatabase& itemDatabase, World& world, Array<float> &tileWater, Time timePassed)
{
	Array<Plant> &plantList = plantDatabase.plantList;
	
		for (uint32_t i = 0; i < plantList.size(); i++)
	{
		Plant p = plantList[i];		
		
		if (plantList[i] == Plant::NONE) continue;
		float nextGrowth = 1.0;
		const Coord pos = plantDatabase.coords[i];
		uint32_t chunkIndex = getChunkIndexFromTile(pos);

		evalSunlight(world, chunkIndex, nextGrowth, world.dailyInsolations, world.cloudCovers, p);
		// sunlight must come before temp, because temp sets nextGrowth to negative
		// sometimes for regrowth
		evalTemperature(world, chunkIndex, p, nextGrowth, plantDatabase.alive[i], true);
		if (!plantDatabase.alive[i]) continue;

		Time& growth = plantDatabase.growths[i];
		growth += std::fmin(nextGrowth * timePassed, 0);
		if (growth > maxAge[p]) plantDatabase.alive[i] = false;
		else if (growth > regrowthStartAge[p]) {
			Time &regrowth = regrowths[i];
		if (regrowth <= regrowthMax[p])
			regrowth += nextGrowth * timePassed;
		uint16_t produceTarget = getProduceCurrentTarget(p, regrowths[i], ages[i]);
		uint16_t currentProduce = produces[i];
		if (produceTarget < currentProduce)
		{
			if (fruitsFall[p])
				itemDatabase.dropFruit(p, pos, currentProduce - produceTarget);
			regrowths[i] -= regrowths[i] *  static_cast<float>(static_cast<int>(produces[i] - produceTarget) / produceTarget);
		}		
		produces[i] = produceTarget;
		}
	}						
}

void updateAlivePlants(PlantDatabase& database)
{
	for (size_t i = 0; i < database.alive.size(); i++) {
		
	}
}	
