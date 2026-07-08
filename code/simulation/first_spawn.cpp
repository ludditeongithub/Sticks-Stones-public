/*  GUIDELINES FOR SPAWNING
 *   all natural entities must roughly spawn as often as they die in nature to
 * ensure that they are not eliminated or grow too much as the game progresses.
 *
 *   ergo, the formula for annual plant spawning is to just have them spawn with
 * the same formula they used before, since all of the annuals will die in the
 * winter, so an equal chance amount of annuals should spawn next spring, as
 * seeds.
 *
 *   perrenials or multi-year plants should spawn at a randomized growth amount.
 * the formula for their respawns should be their total growth amount (period
 * from ), divided by the respawn period, spread throughout every instance in
 * which plants are able to spawn.
 *
 *   A deterministic plant score is given for each cell, which represents how
 * well the plant grows in that area. This is so that it is generally always the
 * most competitive plants which grow in an area, so that natural-looking
 * clusters form.
 *   */

// TODO: have seed in seeds vector become none upon pick up or consuming animals
// or pawns

// TODO: take data from this method into lookup table. make sure it is
// array-based

// APPLY PLANT SPAWNS - get random value from noise generation
// based on factors:
// biome type
// soil type
// temperature
// humidity
// neighboring plants

#include "core/data.hpp"
#include "world_gen.hpp"
#include "core/tables.hpp"
#include "world/tile/data.hpp"
#include "world/world.hpp"
#include <core/random.hpp>
#include <world/animal/enum.hpp>
#include <world/animal/database.hpp>
#include <world/animal/spawn_tables.hpp>
#include <world/plant/enum.hpp>
#include <world/plant/spawn_tables.hpp>
#include <world/tile/grass.hpp>
#include <world/tile/enum.hpp>
#include <world/item/scavengeable.hpp>


// @codegen:begin grass_spawn

// THIS IS  a Test
inline void WorldSpawner::rollGrassSpawn(Coord coord, Biome biome, Tile tile, int temperature, int humidity)
{
float highestRoll = 0.0;
Grass grass = Grass::NONE;


  for (size_t i = 0; i < static_cast<size_t>(Grass::MAX); i++) { //2
  Grass selectedGrass = static_cast<Grass>(i);

float roll = random_chance->next() * 0.4;
for (size_t j = 0; j < static_cast<size_t>(Tile::MAX); j++) { //3
if (tile == static_cast<Tile>(j)) { //4
float multipliedRoll = grass::tileSpawnMultipliers[grass][static_cast<Tile>(j)] * roll;

const Coord tpr = grass::temperaturePenaltyRanges[grass];
float adjTempRoll = rangePenalty(temperature, tpr.x, tpr.y, multipliedRoll);
const Coord hpr = grass::humidityPenaltyRanges[grass];
float adjFinalRoll = rangePenalty(humidity, hpr.x, hpr.y, adjTempRoll);
  

if (adjFinalRoll > highestRoll) { //5
highestRoll = adjFinalRoll;
grass = selectedGrass;
} //5
  } //4
} //3
} //2

if (grass != Grass::NONE)
  if (highestRoll > grass::minimumRoll[biome]) tileSpawnBuffer.add(*this, grass, coord);

}

// @codegen:end grass_spawn

// @codegen:begin plant_spawn

// THIS IS  a Test
inline void WorldSpawner::rollPlantSpawn(Coord coord, Biome biome, Tile tile, int temperature, int humidity)
{
float highestRoll = 0.0;
Plant plant = Plant::NONE;


  for (size_t i = 0; i < static_cast<size_t>(PlantCategory::MAX); i++) { // 1
  float categoryRoll = random_chance->next();
  if (categoryRoll < plant::categorySpawnChances[static_cast<PlantCategory>(i)][biome]) for (size_t j = 0; j < plant::categories[static_cast<PlantCategory>(i)].size(); j++) { //2
  Plant selectedPlant = plant::categories[static_cast<PlantCategory>(i)][static_cast<Plant>(j)];

float roll = random_chance->next() * 0.4;
for (size_t j = 0; j < static_cast<size_t>(Tile::MAX); j++) { //3
if (tile == static_cast<Tile>(j)) { //4
float multipliedRoll = plant::tileSpawnMultipliers[plant][static_cast<Tile>(j)] * roll;

const Coord tpr = plant::temperaturePenaltyRanges[plant];
float adjTempRoll = rangePenalty(temperature, tpr.x, tpr.y, multipliedRoll);
const Coord hpr = plant::humidityPenaltyRanges[plant];
float adjFinalRoll = rangePenalty(humidity, hpr.x, hpr.y, adjTempRoll);
  

if (adjFinalRoll > highestRoll) { //5
highestRoll = adjFinalRoll;
plant = selectedPlant;
} //5
  } //4
} //3
} //2

if (plant != Plant::NONE)
  plantSpawnBuffer.add(*this, plant, coord);

  } // 1
}

// @codegen:end plant_spawn

// @codegen:begin scavengeable_spawn

// THIS IS  a Test
inline void WorldSpawner::rollScavengeableSpawn(Coord coord, Biome biome, Tile tile, int temperature, int humidity)
{
float highestRoll = 0.0;
Scavengeable scavengeable = Scavengeable::NONE;


  for (size_t i = 0; i < static_cast<size_t>(Scavengeable::MAX); i++) { //2
  Scavengeable selectedScavengeable = static_cast<Scavengeable>(i);

float multipliedRoll = scavengeable::biomeSpawnChances[biome][scavengeable];

float adjFinalRoll = multipliedRoll;
  

if (adjFinalRoll > highestRoll) { //5
highestRoll = adjFinalRoll;
scavengeable = selectedScavengeable;
} //5
} //2

if (scavengeable != Scavengeable::NONE)
  scavengeableSpawnBuffer.add(*this, scavengeable, coord);

}

// @codegen:end scavengeable_spawn


// @codegen:begin animal_spawn

// THIS IS  a Test
inline void WorldSpawner::rollAnimalSpawn(Coord coord, Biome biome, Tile tile, int temperature, int humidity)
{
float highestRoll = 0.0;
Animal animal = Animal::NONE;


  for (size_t i = 0; i < static_cast<size_t>(Animal::MAX); i++) { //2
  Animal selectedAnimal = static_cast<Animal>(i);

float multipliedRoll = animal::biomeSpawnChances[biome][animal];

const Coord tpr = animal::temperaturePenaltyRanges[animal];
float adjTempRoll = rangePenalty(temperature, tpr.x, tpr.y, multipliedRoll);
const Coord hpr = animal::humidityPenaltyRanges[animal];
float adjFinalRoll = rangePenalty(humidity, hpr.x, hpr.y, adjTempRoll);
  

if (adjFinalRoll > highestRoll) { //5
highestRoll = adjFinalRoll;
animal = selectedAnimal;
} //5
} //2

if (animal != Animal::NONE)
  animalSpawnBuffer.add(*this, animal, coord);

}

// @codegen:end animal_spawn

// puts into relevant buffer for each
void WorldSpawner::spawnEntities()
{
	// spawn grass and plants
	spawnGrassAndFirstPlants();
	// spawn scavengeables
	spawnScavengeables();
	// spawn animals

	// spawn tribes
}

inline bool skipUnplantableTiles(Tile tile)
{
  switch (tile)
		{
		case Tile::Ice:
			return true;
			break;
		case Tile::FrozenSoil:
			return true;
			break;
		case Tile::Gravel:
			return true;
			break;
		case Tile::Stone:
			return true;
			break;
		case Tile::ShallowWater:
			return true;
			break;
		case Tile::FlowingWater:
			return true;
			break;
		case Tile::DeepWater:
			return true;
			break;
		case Tile::Sand:
			return true;
			break;
		case Tile::Snow:
			return true;
			break;
		default:
                  return false;
                  break;
		}
}

// TODO: shrink by making lookuptables of spawn chances based on tiles
void WorldSpawner::spawnGrassAndFirstPlants()
{
	plantSpawnBuffer.reserve(TILE_AMOUNT);
        
	bool regrowthPlant = false;
	float chances = 0;
	float p = 0;
	constexpr std::array<Plant, 4> trees = {Plant::DeciduousTree, Plant::EvergreenTree,
							Plant::PioneerTree, Plant::TropicalTree};

	for (int i = 0; i < tileSpawnBuffer.tiles.size(); i++)
	{
          Tile tile = tileSpawnBuffer.tiles[i];
          skipUnplantableTiles(tile);

		// TODO: separate mechanism for plants that stay in the same place and
		// those who do not
		//  mechanism to only work on some tsb.tiles for subsequent spawns.
		Coord coord = getTileCoordFromIndex(i);
		Biome biome = biomeMap[i / CHUNK_LENGTH][i % CHUNK_LENGTH];
		int temperature = temperatureMap[i / CHUNK_LENGTH][i % CHUNK_LENGTH];
		int humidity = humidityMap[i / CHUNK_LENGTH][i % CHUNK_LENGTH];

		float plantCoverage = plant::coverages[biome];
		float grassCoverage = grass::coverages[biome];

		if (random_chance->next() < grassCoverage)
		{
                  rollGrassSpawn(coord, biome, tile, temperature, humidity);                        
                }
		if (random_chance->next() < plantCoverage)
		{
                  rollPlantSpawn(coord, biome, tile, temperature, humidity);
                }
	}
        plantSpawnBuffer.shrink_to_size();
}

// TODO: move data into lookup table. possibly spawn animals per chunk instead
// of per tile!
//  APPLY ANIMAL SPAWNS
void WorldSpawner::spawnAnimals()
{
	animalSpawnBuffer.reserve(TILE_AMOUNT);

	for (int i = 0; i < TILE_AMOUNT; i++)
	{
          Tile tile = tileSpawnBuffer.tiles[i];
		// TODO: water animals
            if (isWater(tile)) continue;
		    Coord coord = getTileCoordFromIndex(i);
		    Coord chunkCoord = getChunkFromTile(coord);
		    Biome biome = biomeMap[chunkCoord.x][chunkCoord.y];
		    Temp temperature = temperatureMap[chunkCoord.x][chunkCoord.y];
                    Hum humidity = humidityMap[chunkCoord.x][chunkCoord.y];
        rollAnimalSpawn(coord, biome, tile, temperature, humidity);
         }
          animalSpawnBuffer.shrink_to_size();
}

void WorldSpawner::spawnScavengeables()
{	
  for (int i = 0; i < TILE_AMOUNT; i++)
	{
		Tile tile = tileSpawnBuffer.tiles[i];
                // TODO: seaweed, lilipads etc
		Coord coord = getTileCoordFromIndex(i);
                Coord chunkCoord = getChunkFromTile(coord);
		Biome biome = biomeMap[chunkCoord.x][chunkCoord.y];
		Temp temperature = temperatureMap[chunkCoord.x][chunkCoord.y];
                Hum humidity = humidityMap[chunkCoord.x][chunkCoord.y];
		rollScavengeableSpawn(coord, biome, tile, temperature, humidity);
	
	}
}

