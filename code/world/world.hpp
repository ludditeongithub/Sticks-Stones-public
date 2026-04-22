#pragma once
#include "core/random.hpp"
#include <cstdint>

#include <core/FastNoiseLite.h>
#include <core/containers.hpp>
#include <core/memory.hpp>
#include <core/nanoflann.hpp>
#include <simulation/world_gen.hpp>
#include <world/tile/data.hpp>

// Time Data
constexpr uint16_t HOUR_LENGTH = 300;
constexpr uint16_t DAY_LENGTH = HOUR_LENGTH * 24;
constexpr uint16_t SEASON_LENGTH = DAY_LENGTH * 7;
constexpr uint16_t YEAR_LENGTH = SEASON_LENGTH * 4;

constexpr uint16_t LATITUDE_TOTAL = 180;
constexpr int LATITUDE_MIN = -90;
constexpr int LATITUDE_MAX = 90;
constexpr float MAX_CLOUD_FACTOR = 3.2;

// Terain and Climate
constexpr uint8_t MAX_ALTITUDE = 120;	     // TODO: check
constexpr uint8_t MAX_HUMIDITY = 120;	     // TODO: check
constexpr uint8_t MAX_OCEAN_AFFECT_DIST = 4; // TODO: check

constexpr float WINTER_SOLSTICE = SEASON_LENGTH / 2;
constexpr float SPRING_EQUINOX = SEASON_LENGTH / 2 + SEASON_LENGTH;
constexpr float SUMMER_SOLSTICE = SEASON_LENGTH / 2 + SEASON_LENGTH * 2;
constexpr float FALL_EQUINOX = SEASON_LENGTH / 2 + SEASON_LENGTH * 3;

constexpr float SPRING_MULT = 1.10;
constexpr float AUTUMN_MULT = 0.98;
constexpr float SUMMER_MULT = 1.45;
constexpr float WINTER_MULT = 0.74;

// temp range between -70 C to 57 C, -70 = 0, 57 = 127
constexpr float TEMP_OFFSET = 70;

// diurnal temperature variation influenced mostly by aridity, then latitude, then proximity to
// large water bodies
constexpr float MAX_DIURNAL_VAR = 20.2;

// seasonal temperature variation influenced mostly by latitude, then proximity to large water
// bodies, then elevation
constexpr float MAX_SEASONAL_VAR = 42.1;

constexpr Time CORPSE_ROT_TIME = DAY_LENGTH * 3;

struct World
{
	static const uint16_t ENTITY_SIZE = sizeof(uint8_t) * 3;
	const uint16_t LENGTH_CHUNKS;
	const uint16_t HEIGHT_CHUNKS;
	const uint16_t CHUNK_AMOUNT;
	const uint16_t CHUNK_LATITUDE_HEIGHT =
	    HEIGHT_CHUNKS / LATITUDE_TOTAL; // amount of chunks per latitude

	const uint32_t WORLD_TILE_AMOUNT = CHUNK_AMOUNT * CHUNK_SIZE;
	const uint32_t WORLD_TILE_LENGTH = sqrt(WORLD_TILE_AMOUNT);

	Array<uint8_t> humidities;
	Array<int8_t> temperatures;
	Array<uint8_t> altitudes;

	World(Arena *arena, int width, int height)
	    : LENGTH_CHUNKS(width), HEIGHT_CHUNKS(height), CHUNK_AMOUNT(width * height)
	{
		humidities = arena_make_array<uint8_t>(arena, width * height);
		temperatures = arena_make_array<int8_t>(arena, width * height);
		altitudes = arena_make_array<uint8_t>(arena, width * height);
	}

	inline uint16_t getChunkHeight(int i) { return i / HEIGHT_CHUNKS; }

	inline uint16_t getChunkWidth(int i) { return i % HEIGHT_CHUNKS; }

	inline int16_t getChunkLatitude(int i)
	{
		return (getChunkHeight(i) / CHUNK_LATITUDE_HEIGHT) - (LATITUDE_TOTAL / 2);
	}

	inline uint16_t getChunkTimeZone(uint32_t chunkIndex);

	inline uint32_t getTileIndexFromCoord(Coord c);
	inline Coord getTileCoordFromIndex(uint32_t i);
	inline uint32_t getTileIndexChunkRelative(uint32_t i);
	inline uint32_t getTileIndexChunkRelative(Coord c);

	Coord getRandomPlayerStart()
	{	return{ static_cast<uint16_t>(random_chance->next() * LENGTH_CHUNKS) , static_cast<uint16_t>(random_chance->next() * HEIGHT_CHUNKS)};
	}		

	void loadChunkData(WorldSpawner &ws)
	{
		ws.moveRegionsToChunks(humidities, temperatures, altitudes);
	}
};

/*
 * Need to ensure that if a block of tile generates, that some of those tiles aren't actually river
 * tiles,  but haven't been generated as such because neighboring ungenerated tiles which should
 * have river sources on them have not been generated. Thus, need to check if generated cells are
 * river ends of any sort, or lakes, and then for each of those recursively check if there are river
 * continues, following up the chain, until I find the original river sources/lakes, and then
 * recursively generate rivers all the way down, even if those tiles haven't been generated.
 *
 */
