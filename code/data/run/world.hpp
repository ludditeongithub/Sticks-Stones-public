#pragma once
#include <data/types/geography.hpp>
#include "core/random.hpp"
#include <cstdint>
#include <core/containers.hpp>
#include <core/memory.hpp>
#include <data/const/chunk_data.hpp>

namespace tile {
class Database;
};

struct WorldSpawner;

struct World
{
	static constexpr CloudKey MIN_LIGHT_CLOUDS = 50;
	static constexpr CloudKey MIN_HEAVY_CLOUDS = 150;
	static constexpr PrecipitationKey PRECIPITATION_MIN = 160;
	static constexpr float PRECIPITATION_VARIANCE_FACTOR = 0.45;
	static constexpr float HEAVY_PRECIPITATION_FACTOR = 1.85;
	static constexpr float MM_PER_PRECIPITATION = 8;

	Array<Hum> humidities;
	Array<Temp> temperatures;
	Array<Alt> altitudes;

	Array<CloudKey> cloud_values;
	Array<PrecipitationKey> precipitation_values;
	Array<Precipitation> precipitation_cores; //base amount of precipitation that chunk produces, based on biome, water bodies, etc
	RandomMachine<int8_t> next_cloud_changes = RandomMachine<int8_t>(-5, 5);
	RandomMachine<int8_t> next_precipitation_changes = RandomMachine<int8_t>(-5, 5);
	RandomChanceMachine precipitation_variance = RandomChanceMachine();
	
        Array2D<float> daily_insolations;
	Array<float> seasonal_insolations;
	Array<float> cloud_covers;

  struct ChunkTempData
{
    

    ChunkTempData(World* world)
    {
        min_temps.reserve(world->chunk_amount);
        diurnal_temp_variances.reserve(world->chunk_amount);
        seasonal_temp_variances.reserve(world->chunk_amount);
    }
};
	ChunkTempData chunk_temp_data;

  World(Arena* arena, size_t width, size_t height)
	    : coord::length_chunks(width), coord::height_chunks(height),
	      equator(height / 2),
      chunk_amount(width * height),      
      chunk_temp_data(this) 
{
  humidities = arena_make_array<Hum>(arena, width * height);
  temperatures = arena_make_array<Temp>( arena, width * height);
  altitudes = arena_make_array<Alt>(arena, width * height);
  daily_insolations = arena_make_2d_array<float>(arena, width, height);
  seasonal_insolations = arena_make_array<float>(arena, width * height);
  cloud_covers = arena_make_array<float>(arena, width * height);
}

	uint16_t get_chunk_height(int i) { return i / height_chunks; }

	uint16_t get_chunk_width(int i) { return i % height_chunks; }

	uint16_t get_chunk_latitude(int i)
	{
		return (get_chunk_height(i) / chunk_latitude_height) - (LATITUDE_TOTAL / 2);
	}

	uint16_t get_chunk_time_zone(uint32_t chunk_index);
        uint16_t get_chunk_index_from_coord(Coord c);
	uint32_t get_tile_index_from_coord(Coord c);
	Coord get_tile_coord_from_index(uint32_t i);
	uint32_t get_tile_index_chunk_relative(uint32_t i);
	uint32_t get_tile_index_chunk_relative(Coord c);

	Coord get_random_player_start();

	void load_chunk_data(WorldSpawner &ws);

	void update_daily_insolations(uint16_t day365);

	void calculate_chunk_temperature_inputs(Array<int8_t> &water_bodies_dists);

	void update_chunk_temperature();

	void update_weather();

	void apply_weather(tile::Database* tile_db);

	void apply_precipitation(tile::Database* tile_db, uint16_t chunk, bool heavy);
	
};

extern World* g_world;
/*
 * Need to ensure that if a block of tile generates, that some of those tiles aren't actually river
 * tiles,  but haven't been generated as such because neighboring ungenerated tiles which should
 * have river sources on them have not been generated. Thus, need to check if generated cells are
 * river ends of any sort, or lakes, and then for each of those recursively check if there are river
 * continues, following up the chain, until I find the original river sources/lakes, and then
 * recursively generate rivers all the way down, even if those tiles haven't been generated.
 *
 */
