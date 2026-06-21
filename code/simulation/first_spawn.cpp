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

#include "first_spawn.hpp"
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

// @codegen:begin grass_spawn


inline Grass rollGrassSpawn(Biome biome, Tile tile, int temperature, int humidity)
{
float highestRoll = 0.0;
Grass grass = Grass::NONE;

  for (size_t i = 0; i < static_cast<size_t>(Grass::MAX); i++) { //2
  Grass selectedGrass = static_cast<Grass>(i);

float rawRoll = random_chance->next() * 0.4;
for (size_t j = 0; j < static_cast<size_t>(Tile::MAX); j++) { //3
if (tile == static_cast<Tile>(j)) { //4
float multipliedRoll = grass::tileSpawnMultipliers[grass][static_cast<Tile>(j)] * rawRoll;

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

  if (highestRoll > grass::minimumRoll[biome]) tileSpawnBuffer.grasses = grass;



}

// @codegen:end grass_spawn

// @codegen:begin plant_spawn


inline Plant rollPlantSpawn(Biome biome, Tile tile, int temperature, int humidity)
{
float highestRoll = 0.0;
Plant plant = Plant::NONE;



  for (size_t i = 0; i < static_cast<size_t>(PlantCategory::MAX); i++) { // 1
  float categoryRoll = random_chance->next();
  if (categoryRoll < plant::categorySpawnChances[static_cast<PlantCategory>(i)][biome]) for (size_t j = 0; j < plant::categories[static_cast<PlantCategory>(i)].size(); j++) { //2
  Plant selectedPlant = plant::categories[static_cast<PlantCategory>(i)][static_cast<Plant>(j)];

float rawRoll = random_chance->next() * 0.4;
for (size_t j = 0; j < static_cast<size_t>(Tile::MAX); j++) { //3
if (tile == static_cast<Tile>(j)) { //4
float multipliedRoll = plant::tileSpawnMultipliers[plant][static_cast<Tile>(j)] * rawRoll;

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

  plantSpawnBuffer.plants = plant;



  } // 1
  
}

// @codegen:end plant_spawn

// @codegen:begin animal_spawn


inline Animal rollAnimalSpawn(Biome biome, Tile tile, int temperature, int humidity)
{
float highestRoll = 0.0;
Animal animal = Animal::NONE;



  for (size_t i = 0; i < static_cast<size_t>(Animal::MAX); i++) { //2
  Animal selectedAnimal = static_cast<Animal>(i);

float rawRoll = random_chance->next() * 0.4;
for (size_t j = 0; j < static_cast<size_t>(Tile::MAX); j++) { //3
if (tile == static_cast<Tile>(j)) { //4
float multipliedRoll = animal::tileSpawnMultipliers[animal][static_cast<Tile>(j)] * rawRoll;

const Coord tpr = animal::temperaturePenaltyRanges[animal];
float adjTempRoll = rangePenalty(temperature, tpr.x, tpr.y, multipliedRoll);
const Coord hpr = animal::humidityPenaltyRanges[animal];
float adjFinalRoll = rangePenalty(humidity, hpr.x, hpr.y, adjTempRoll);
if (adjFinalRoll > highestRoll) { //5
highestRoll = adjFinalRoll;
animal = selectedAnimal;
} //5
} //4
} //3
} //2

if (animal != Animal::NONE)

  animalSpawnBuffer.animals = animal;



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


// TODO: shrink by making lookuptables of spawn chances based on tiles
void WorldSpawner::spawnGrassAndFirstPlants()
{
	bool regrowthPlant = false;
	float chances = 0;
	float p = 0;
	constexpr std::array<Plant, 4> trees = {Plant::DeciduousTree, Plant::EvergreenTree,
							Plant::PioneerTree, Plant::TropicalTree};

	for (int i = 0; i < tileSpawnBuffer.tiles.size(); i++)
	{
          Tile tile = tileSpawnBuffer.tiles[i];
		switch (tile)
		{
		case Tile::Ice:
			continue;
			break;
		case Tile::FrozenSoil:
			continue;
			break;
		case Tile::Gravel:
			continue;
			break;
		case Tile::Stone:
			continue;
			break;
		case Tile::ShallowWater:
			continue;
			break;
		case Tile::FlowingWater:
			continue;
			break;
		case Tile::DeepWater:
			continue;
			break;
		case Tile::Sand:
			continue;
			break;
		case Tile::Snow:
			continue;
			break;
		default:
		}

		// TODO: separate mechanism for plants that stay in the same place and
		// those who do not
		//  mechanism to only work on some tsb.tiles for subsequent spawns.
		Coord coord = getTileCoordFromIndex(i);
		Biome biome = biomeMap[i / CHUNK_LENGTH][i % CHUNK_LENGTH];
		int temperature = temperatureMap[i / CHUNK_LENGTH][i % CHUNK_LENGTH];
		int humidity = humidityMap[i / CHUNK_LENGTH][i % CHUNK_LENGTH];

		// PLANT CATEGORY RARITIES - chance of each plant type spawning in each
		// biome, on a tile, not adjusted for other checks (trees have higher raw
		// spawn rate due to not being able to spawn next to other trees) the
		// threshold that the random generated number needs to pass to ensure that
		// the plant species even has a chance of competing.

		//% of much non-grass plants appear on tsb.tiles and grass plants
		// respectively

		float plantCoverage = plantCoverages[biome];
		float grassCoverage = grassCoverages[biome];

		LookupTable<Plant, float> &lt = getPlantChanceTable(biome);

		// SPAWN ALL PLANTS
		rollGrassSpawn(biome, tile, temperature, humidity);
        }
}

// TODO: move data into lookup table. possibly spawn animals per chunk instead
// of per tile!
//  APPLY ANIMAL SPAWNS
AnimalSpawnBuffer WorldSpawner::spawnAnimals(SearchGrid &sg)
{
	AnimalSpawnBuffer asb;
	asb.types.reserve(TILE_AMOUNT);
	asb.coords.reserve(TILE_AMOUNT);

	for (int i = 0; i < TILE_AMOUNT; i++)
	{
		// TODO: water animals
	 if (isWater(tsb.tiles[i]) continue;
         if (sg.isOccupied(i)) continue;
         Coord coord = getTileCoordFromIndex(i);
         Coord chunkCoord = getChunkFromTile(coord);
	 // skip if within player chunk bounds -- animals within player bounds managed separately         
	 if (chunkCoord.x >= playerChunkBorderWest && chunkCoord.x <= playerChunkBorderEast && chunkCoord.y >= playerChunkBorderNorth && chunkCoord.y <= playerChunkBorderSouth) continue;
         int biome = biomeChunk[chunkCoord.first][chunkCoord.second];

	 float currentChance = 0;
         float random = nextRandomPropFrac();

         asb.size++; // size is subtracted at the end if no animal added.
                  
	 //make more efficient by adding up total chance of all anial spawns, just skipping if less than that chance         
if (random < currentChance + pigChance) {
			asb.types.emplace_back(Animal::Pig);
			asb.coords.emplace_back(coord);
}
else if (random < (currentChance += pigChance) + cowChance) {
			asb.types.emplace_back(Animal::Cow);
			asb.coords.emplace_back(coord);
}
else if (random < (currentChance += cowChance) + chickenChance) {
			asb.types.emplace_back(Animal::Chicken);
			asb.coords.emplace_back(coord);
}
else if (random < (currentChance += chickenChance) + duckChance) {
			asb.types.emplace_back(Animal::Duck);
			asb.coords.emplace_back(coord);
}
else if (random < (currentChance += duckChance) + sheepChance) {
			asb.types.emplace_back(Animal::Sheep);
			asb.coords.emplace_back(coord);
}
else if (random < (currentChance += sheepChance) + goatChance) {
			asb.types.emplace_back(Animal::Goat);
			asb.coords.emplace_back(coord);
}
else if (random < (currentChance += goatChance) + horseChance) {
			asb.types.emplace_back(Animal::Horse);
			asb.coords.emplace_back(coord);
}
else if (random < (currentChance += horseChance) + oxChance) {
			asb.types.emplace_back(Animal::Ox);
			asb.coords.emplace_back(coord);
}
else if (random < (currentChance += oxChance) + donkeyChance) {
			asb.types.emplace_back(Animal::Donkey);
			asb.coords.emplace_back(coord);
}
else if (random < (currentChance += donkeyChance) + camelChance) {
			asb.types.emplace_back(Animal::Camel);
			asb.coords.emplace_back(coord);
}
else if (random < (currentChance += camelChance) + waterBuffaloChance) {
			asb.types.emplace_back(Animal::WaterBuffalo);
			asb.coords.emplace_back(coord);
}
else if (random < (currentChance += waterBuffaloChance) + rabbitChance) {
			asb.types.emplace_back(Animal::Rabbit);
			asb.coords.emplace_back(coord);
}
else if (random < (currentChance += rabbitChance) + antelopeChance) {
			asb.types.emplace_back(Animal::Antelope);
			asb.coords.emplace_back(coord);
}
else if (random < (currentChance += antelopeChance) + deerChance) {
			asb.types.emplace_back(Animal::Deer);
			asb.coords.emplace_back(coord);
}
else if (random < (currentChance += deerChance) + mooseChance) {
			asb.types.emplace_back(Animal::Moose);
			asb.coords.emplace_back(coord);
}
else if (random < (currentChance += mooseChance) + capybaraChance) {
			asb.types.emplace_back(Animal::Capybara);
			asb.coords.emplace_back(coord);
}
else if (random < (currentChance += capybaraChance) + turtleChance) {
			asb.types.emplace_back(Animal::Turtle);
			asb.coords.emplace_back(coord);
}
else if (random < (currentChance += turtleChance) + elephantChance) {
			asb.types.emplace_back(Animal::Elephant);
			asb.coords.emplace_back(coord);
}
else if (random < (currentChance += elephantChance) + bisonChance) {
			asb.types.emplace_back(Animal::Bison);
			asb.coords.emplace_back(coord);
}
else if (random < (currentChance += bisonChance) + wolfChance) {
			asb.types.emplace_back(Animal::Wolf);
			asb.coords.emplace_back(coord);
}
else if (random < (currentChance += wolfChance) + bearChance) {
			asb.types.emplace_back(Animal::Bear);
			asb.coords.emplace_back(coord);
}
else if (random < (currentChance += bearChance) + caribouChance) {
			asb.types.emplace_back(Animal::Caribou);
			asb.coords.emplace_back(coord);
} else asb.size--;
	}
	asb.types.shrink_to_fit(asb.size);
	asb.coords.shrink_to_fit(asb.size);
	return asb;
}

void WorldSpawner::spawnScavengeables(std::vector<bool> &tileWater, vector<bool> &tileOccupied,
				      ScavengeableDatabase &sd)
{
	float dominant = 0.009;
	float abundant = 0.003;
	float common = 0.001;
	float semicommon = 0.0005;
	float uncommon = 0.00025;
	float rare = 0.000125;
	float veryrare = 0.000066;
	float legendary = 0.000033;
	float never = 0.0;
	for (int i = 0; i < rAdIndex.size(); i++)
	{
		if (static_cast<int>(rAdObject[i]) != 0)
			continue;
		uint32_t chunk = rAdChunkIndex[i];
		std::pair<int, int> chunkCoord = rMapsLink[chunk];
		int biome = biomeMap[chunkCoord.first][chunkCoord.second];
		Scavengeable scavengeable;
		float logChance = 0.0;
		float pebbleChance = 0.0;
		float rockChance = 0.0;
		float largeRockChance = 0.0;
		float boulderChance = 0.0;
		float flintChance = 0.0;
		float oreChance = 0.0;
		float beehiveChance = 0.0;
		float stickChance = 0.0;

		// hot desert
		if (biome == 1)
			logChance = legendary;
		pebbleChance = abundant;
		rockChance = common;
		largeRockChance = semicommon;
		boulderChance = rare;
		flintChance = rare;
		oreChance = veryrare;
		beehiveChance = legendary;
		stickChance = uncommon;
	}
	// plains
	if (biome == 2)
	{
		logChance = rare;
		pebbleChance = common;
		rockChance = semicommon;
		largeRockChance = uncommon;
		boulderChance = rare;
		flintChance = veryrare;
		oreChance = veryrare;
		beehiveChance = uncommon;
		stickChance = common;
	}
	// savannah
	if (biome == 3)
	{
		logChanceChance = semicommon;
		pebbleChance = common;
		rockChance = common;
		largeRockChance = semicommon;
		boulderChance = uncommon;
		flintChance = rare;
		oreChance = veryrare;
		beehiveChance = semicommon;
		stickChance = abundant;
	}
	// wetlands
	if (biome == 4)
	{
		logChance = common;
		pebbleChance = uncommon;
		rockChance = rare;
		largeRockChance = veryrare;
		boulderChance = legendary;
		flintChance = veryrare;
		oreChance = veryrare;
		beehiveChance = uncommon;
		stickChance = abundant;
	}
	// forests
	if (biome == 5)
	{
		logChance = abundant;
		pebbleChance = common;
		rockChance = common;
		largeRockChance = semicommon;
		boulderChance = uncommon;
		flintChance = rare;
		oreChance = veryrare;
		beehiveChance = semicommon;
		stickChance = dominant;
	}
	// taiga
	if (biome == 6)
	{
		logChance = abundant;
		pebbleChance = common;
		rockChance = common;
		largeRockChance = semicommon;
		boulderChance = uncommon;
		flintChance = rare;
		oreChance = veryrare;
		beehiveChance = rare;
		stickChance = dominant;
	}
	// rainforest
	if (biome == 7)
	{
		logChance = abundant;
		pebbleChance = uncommon;
		rockChance = uncommon;
		largeRockChance = veryrare;
		boulderChance = veryrare;
		flintChance = veryrare;
		oreChance = legendary;
		beehiveChance = semicommon;
		stickChance = dominant;
	}
	// rocky
	if (biome == 8)
	{
		logChance = veryrare;
		pebbleChance = dominant;
		rockChance = abundant;
		largeRockChance = semicommon;
		boulderChance = uncommon;
		flintChance = uncommon;
		oreChance = rare;
		beehiveChance = veryrare;
		stickChance = rare;
	}
	// tundra
	if (biome == 9)
	{
		logChance = veryrare;
		pebbleChance = abundant;
		rockChance = common;
		largeRockChance = uncommon;
		boulderChance = veryrare;
		flintChance = rear;
		oreChance = legendary;
		beehiveChance = veryrare;
		stickChance = uncommon;
	}
	// cold desert
	if (biome == 10)
	{
		logChance = legendary;
		pebbleChance = dominant;
		rockChance = abundant;
		largeRockChance = common;
		boulderChance = semicommon;
		flintChance = rare;
		oreChance = veryrare;
		beehiveChance = legendary;
		stickChance = rare;
	}

	float random = rand() / (float)RAND_MAX;
	if (random < currentChance + logChance)
	{
		scavengeable = Scavengeable::Log;
	}
	else if (random < currentChance + pebbleChance)
	{
		scavengeable = Scavengeable::Pebble;
	}
	else if (random < currentChance + rockChance)
	{
		scavengeable = Scavengeable::Rock;
	}
	else if (random < currentChance + largeRockChance)
	{
		scavengeable = Scavengeable::LargeRock;
	}
	else if (random < currentChance + boulderChance)
	{
		scavengeable = Scavengeable::Boulder;
	}
	else if (random < currentChance + flintChance)
	{
		scavengeable = Scavengeable::Flint;
	}
	else if (random < currentChance + oreChance)
	{
		scavengeable = Scavengeable::Ore;
	}
	else if (random < currentChance + beehiveChance)
	{
		scavengeable = Scavengeable::Beehive;
	}
	else if (random < currentChance + stickChance)
	{
		scavengeable = Scavengeable::Stick;
	}
	// log must take up multiple ads, and depends on tree type, which is randomly
	// generated
	if (scavengeable == Scavengeable::Log)
	{
	}
}

Coord World::getRandomPlayerStart()
{
	return {random_chance.next() * CHUNK_LATITUDE_WIDTH,
		random_chance.next() * CHUNK_LATITUDE_HEIGHT};
};
