#pragma once

#include "systems/find_nearest.hpp"
#include "world/world.hpp"
#include <core/random.hpp>
#include <cstdint>
#include <vector>
#include <core/containers.hpp>
#include <world/animal/enum.hpp>
#include <world/plant/enum.hpp>
#include <world/chunk/data.hpp>
#include <world/tile/enum.hpp>
#include <world/scavengeable/enum.hpp>


float rangePenalty(float originalValue, float minValue, float maxValue, float adjustedValue);

class WorldSpawner
{
      public:
	RandomMachine<int> r1To5 = RandomMachine<int>(1, 5);
	RandomMachine<int> r1To2 = RandomMachine<int>(1, 2);
	RandomMachine<int> r1To4 = RandomMachine<int>(1, 4);
	RandomMachine<int> r1To3 = RandomMachine<int>(1, 4);
	RandomMachine<int> rcx;
	RandomMachine<int> rcy;

	RandomChanceMachine rchance;

	const Hum MAX_HUMIDITY = 500;
	
	const float coastThreshold = -0.2f;
	const float landThreshold = -25.0f;
	const float lowlandsThreshold = 9.0f;
	const float midlandsThreshold = 14.0f;

	const int depressionThreshold = 15;
	const float lowlandsToHighlandsChance =
	    0.01f;				  // chance of const lowlands becoming highlands
	const float lowlandsToLakeChance = 0.04f; // additional threshold const to become lake
	const float highlandsChance = 0.20f;
	const float coastalRangeChance = 0.005f;
	const float riverFromMountainChance = 0.5f;
	const float riverFromHighlandChance = 0.2f;
	const float riverFromGroundwaterChance = 0.3f;
	const float riverEndChance = 0.50f;
	const float lakeFromRiverChance = 0.60f;
	const float lakeFromLowlandsChance = 0.05f;
	const float lakeFromMidlandsChance = 0.01f;
	const float lakeExpansionChance = 0.60f;
	const float riverFromLakeChance = 0.40f;
	const float groundWaterThreshold =
	    80.0f; // how high humidity needs to be for a chance of substantial groundwater to form
	const float humidityMult = 2.2f;
	const float lakeTileChance =
	    0.07f; // chance that lake tile does NOT happen (smaller sizes mean larger lakes)

	// BIOMES AMOUNT
	using alt = uint16_t;

	// in biomes
	const int WIDTH;
	const int HEIGHT;
	const int BORDER_WIDTH = 3;
	const int BORDER_HEIGHT = 3;
	const int AMOUNT = WIDTH * HEIGHT;
	const int REGION_SIZE = 100; // average WIDTH and HEIGHT of each region
	const int EQUATOR = HEIGHT / 2;
	// IN TILES
	const int WORLD_WIDTH = WIDTH * REGION_SIZE;
	const int WORLD_HEIGHT = HEIGHT * REGION_SIZE;

	// New variables to store the size of the map with borders
	const int WIDTH_WITH_BORDER = WIDTH + BORDER_WIDTH * 2;
	const int HEIGHT_WITH_BORDER = HEIGHT + BORDER_HEIGHT * 2;

	struct SeedCloud
	{
		std::vector<std::pair<float, float>> seeds; // Using std::std::pair<float, float>

		// Must return the dimensionality of points (2D case: x, y)
		inline uint16_t kdtree_get_point_count() const { return seeds.size(); }

		// Return the dimension (0 = x, 1 = y) of a given index
		inline float kdtree_get_pt(const uint16_t idx, const uint16_t dim) const
		{
			return (dim == 0) ? seeds[idx].first : seeds[idx].second;
		}

		// Optional: Bounding box, not required
		template <class BBOX> bool kdtree_get_bbox(BBOX & /*bb*/) const { return false; }
	};

	std::vector<std::vector<Alt>> altitudeMap;
	std::vector<std::vector<Temp>> temperatureMap;
	std::vector<std::vector<Hum>> humidityMap;
	std::vector<std::vector<Biome>> biomeMap;
	std::vector<std::vector<int>> oceanMap;
	std::vector<std::vector<int>> landsMap;
	std::vector<std::vector<int>> waterMap;
	std::vector<std::vector<int>> potentialHumidityMap;
	std::vector<std::vector<int>> createdHumidityMap;
	std::vector<std::vector<bool>> instantiatedWaterMap;
	std::vector<std::vector<int>> oceanDistance;

	std::vector<std::vector<bool>> rVisited; // holds visited rivers

	const uint32_t TILE_AMOUNT;


struct TileSpawnBuffer
{
	size_t size;
	std::vector<Tile> tiles;
	std::vector<Grass> grasses;
	std::vector<Alt> altitudes;
  std::vector<bool> occupieds;

  TileSpawnBuffer(size_t capacity)
	{
		tiles.reserve(capacity);
		grasses.reserve(capacity);
		altitudes.reserve(capacity);
                size = capacity;
        }

inline void add(WorldSpawner& worldSpawner, Grass grass, Coord coord)
  {
    size_t i = worldSpawner.getTileIndexFromCoord(coord);
          grasses[i] = grass;
	}
};

  // @codegen:begin spawn_buffer_animal
struct AnimalSpawnBuffer {
  std::vector<Animal> animals;
	std::vector<Coord> coords; 
	size_t size;
AnimalSpawnBuffer(size_t capacity) 
	{
		reserve(capacity);                
        }
  void reserve(size_t cap) {
    animals.reserve(cap);
    coords.reserve(cap);
  }
  inline void add(WorldSpawner& worldSpawner, TileSpawnBuffer& tileSpawnBuffer, Animal animal, Coord coord)
	{
		animals[size++] = animal;
		coords[size] = coord;                   tileSpawnBuffer.occupieds[worldSpawner.getTileIndexFromCoord(coord)] = true;
	}
  void shrink_to_size()
	{
		animals.resize(size);
                coords.resize(size);
		animals.shrink_to_fit();
                coords.shrink_to_fit();
        }
};
// @codegen:end spawn_buffer_animal

  // @codegen:begin spawn_buffer_plant
struct PlantSpawnBuffer {
  std::vector<Plant> plants;
	std::vector<Coord> coords; 
	size_t size;
PlantSpawnBuffer(size_t capacity) 
	{
		reserve(capacity);                
        }
  void reserve(size_t cap) {
    plants.reserve(cap);
    coords.reserve(cap);
  }
  inline void add(WorldSpawner& worldSpawner, TileSpawnBuffer& tileSpawnBuffer, Plant plant, Coord coord)
	{
		plants[size++] = plant;
		coords[size] = coord;                   tileSpawnBuffer.occupieds[worldSpawner.getTileIndexFromCoord(coord)] = true;
	}
  void shrink_to_size()
	{
		plants.resize(size);
                coords.resize(size);
		plants.shrink_to_fit();
                coords.shrink_to_fit();
        }
};
// @codegen:end spawn_buffer_plant

  // @codegen:begin spawn_buffer_scavengeable
struct ScavengeableSpawnBuffer {
  std::vector<Scavengeable> scavengeables;
	std::vector<Coord> coords; 
	size_t size;
ScavengeableSpawnBuffer(size_t capacity) 
	{
		reserve(capacity);                
        }
  void reserve(size_t cap) {
    scavengeables.reserve(cap);
    coords.reserve(cap);
  }
  inline void add(WorldSpawner& worldSpawner, TileSpawnBuffer& tileSpawnBuffer, Scavengeable scavengeable, Coord coord)
	{
		scavengeables[size++] = scavengeable;
		coords[size] = coord;                   tileSpawnBuffer.occupieds[worldSpawner.getTileIndexFromCoord(coord)] = true;
	}
  void shrink_to_size()
	{
		scavengeables.resize(size);
                coords.resize(size);
		scavengeables.shrink_to_fit();
                coords.shrink_to_fit();
        }
};
// @codegen:end spawn_buffer_scavengeable


	TileSpawnBuffer tileSpawnBuffer;
	PlantSpawnBuffer plantSpawnBuffer;
        ScavengeableSpawnBuffer scavengeableSpawnBuffer;
	AnimalSpawnBuffer animalSpawnBuffer;

	template <typename T>
	void mapReserveRows(int width, int height, std::vector<std::vector<T>> &map)
	{
		map.reserve(height);
		for (int i = 0; i < width; i++)
			map[i].reserve(height);
	}

	WorldSpawner(int width, int height)
	    : WIDTH(width), HEIGHT(height),
	      TILE_AMOUNT(width * height * CHUNK_SIZE * CHUNKS_PER_REGION)
	{
		rcx = RandomMachine<int>(WIDTH / 8, 7 * WIDTH / 8);
		rcy = RandomMachine<int>(HEIGHT / 8, 7 * HEIGHT / 8);
		mapReserveRows(width, height, altitudeMap);
		mapReserveRows(width, height, temperatureMap);
		mapReserveRows(width, height, humidityMap);
		mapReserveRows(width, height, biomeMap);
		mapReserveRows(width, height, oceanMap);
		mapReserveRows(width, height, landsMap);
		mapReserveRows(width, height, waterMap);
		mapReserveRows(width, height, potentialHumidityMap);
		mapReserveRows(width, height, createdHumidityMap);
		mapReserveRows(width, height, instantiatedWaterMap);
		mapReserveRows(width, height, oceanDistance);
		mapReserveRows(width, height, rVisited);
                tileSpawnBuffer = TileSpawnBuffer(width * height);
		plantSpawnBuffer = PlantSpawnBuffer(width * height);
                scavengeableSpawnBuffer = ScavengeableSpawnBuffer(width * height);
                animalSpawnBuffer = AnimalSpawnBuffer(width * height);
	}

	void generateWorld();
  
	// helpers
	void recursiveLower();
	void recursiveFill();
	void printMap();
        void moveRegionsToChunks(Array<Hum> humidities, Array<Temp> temperatures,
				 Array<Alt> altitudes);
	void printInfo();
	Coord getTileCoordFromIndex(size_t i);
        size_t getTileIndexFromCoord(Coord c);

  // world generation
	void generateOceansOnMaps();
	void markCoasts();
	void applyExtraHighlandsAndMountains();
	void generateLandsMap();
	void extendRiversFromSource(uint16_t riverLength, int x, int y);
	void markRiverEnds();
	void generateWaterMap();
	void generateTemperatureMap();
	void generateHumidityMap();
	void factorWetlandsJunglesAndForests();
	void generateBiomes();
	void generateAltitudeMap();
	void getRiversFromGroundwater();
	void cleanAltitudeMap();	
std::vector<std::tuple<float, bool, bool>>
humidityAndRainShadowEffects(int y, int x, int water, bool biomes);
	void addDepressions();
	void applyRiverTiles();
	std::vector<std::vector<int>>
	calculateOceanDistance(std::vector<std::vector<int>> &waterMap, bool lake, bool river);
	std::vector<Coord> generateVoronoiSites();
	void generateTileTypes(std::vector<float> &chances, std::vector<Coord> &voronoiSites,
			       std::vector<Tile> &rTiles, Array<Alt> &rAltitudes);
	std::vector<float> generateTileChances();

  // spawners
  void spawnGrassAndFirstPlants();
  void spawnScavengeables();
  void spawnAnimals();

        inline void rollGrassSpawn(Coord coord, Biome biome, Tile tile, int temperature, int humidity);
        inline void rollPlantSpawn(Coord coord, Biome biome, Tile tile, int temperature, int humidity);
        inline void rollAnimalSpawn(Coord coord, Biome biome, Tile tile, int temperature, int humidity);
      inline void rollScavengeableSpawn(Coord coord, Biome biome, Tile tile, int temperature, int humidity);
	// Constants
	// IN CELLS
	int currentXMin = 0;
	int currentXMax = 0;
	int currentYMin = 0;
	int currentYMax = 0;
};
