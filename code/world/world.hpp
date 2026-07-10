#pragma once
#include "core/data.hpp"
#include "core/random.hpp"
#include <cstdint>

#include <extern/FastNoiseLite.h>
#include <core/containers.hpp>
#include <core/memory.hpp>
#include <extern/nanoflann.hpp>
#include <simulation/world_gen.hpp>

#include <world/tile/database.hpp>

// Weather

enum class Weather : uint8_t
{
	Clear,
	LightClouds,
	HeavyClouds,
	LightPrecipitation,
	MediumPrecipitation,
	HeavyPrecipitation,
	Heatwave,
};

// Time Data
constexpr uint16_t hour_length = 300;
constexpr uint16_t day_length = hour_length * 24;
constexpr uint16_t season_length = day_length * 7;
constexpr uint16_t year_length = season_length * 4;

constexpr uint16_t latitude_total = 180;
constexpr int latitude_min = -90;
constexpr int latitude_max = 90;
constexpr uint16_t longitude_total = 180;
constexpr float max_cloud_factor = 3.2;

// Terain and Climate
constexpr uint8_t max_altitude = 120;	     // TODO: check
constexpr uint8_t max_humidity = 120;	     // TODO: check
constexpr uint8_t max_ocean_affect_dist = 4; // TODO: check

constexpr float winter_solstice = season_length / 2;
constexpr float spring_equinox = season_length / 2 + season_length;
constexpr float summer_solstice = season_length / 2 + season_length * 2;
constexpr float fall_equinox = season_length / 2 + season_length * 3;

constexpr float spring_mult = 1.10;
constexpr float autumn_mult = 0.98;
constexpr float summer_mult = 1.45;
constexpr float winter_mult = 0.74;

// temp range between -70 C to 57 C, -70 = 0, 57 = 127
constexpr float temp_offset = 70;

// diurnal temperature variation influenced mostly by aridity, then latitude, then proximity to
// large water bodies
constexpr float max_diurnal_var = 20.2;

// seasonal temperature variation influenced mostly by latitude, then proximity to large water
// bodies, then elevation
constexpr float max_seasonal_var = 42.1;

constexpr Time corpse_rot_time = day_length * 3;



struct World
{
	static const uint16_t entity_size = sizeof(uint8_t) * 3;
	const uint16_t length_chunks;
	const uint16_t height_chunks;
	const uint16_t equator;
	const uint16_t chunk_amount;
	const uint16_t chunk_latitude_height = height_chunks / latitude_total; // amount of chunks per latitude
  const uint16_t chunk_longitude_width = length_chunks / longitude_total;
	const uint32_t world_tile_amount = chunk_amount * chunk_size;
	const uint32_t world_tile_length = sqrt(world_tile_amount);

	const CloudKey min_light_clouds = 50;
	const CloudKey min_heavy_clouds = 150;
	const PrecipitationKey precipitation_min = 160;
	const float precipitation_variance_factor = 0.45;
	const float heavy_precipitation_factor = 1.85;
	const float mm_per_precipitation = 8;

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
    std::vector<float> min_temps;
    std::vector<float> diurnal_temp_variances;
	std::vector<float> seasonal_temp_variances;

    ChunkTempData(World* world)
    {
        minTemps.reserve(world->CHUNK_AMOUNT);
        diurnalTempVariances.reserve(world->CHUNK_AMOUNT);
        seasonalTempVariances.reserve(world->CHUNK_AMOUNT);
    }
};
	ChunkTempData chunk_temp_data;

	World(Arena& arena, int width, int height)
	    : length_chunks(width), height_chunks(height),
	      equator(height / 2),
      chunk_amount(width * height),      
      chunkTempData(this) 
{
    humidities = arena_make_array<Hum>(arena, width * height);
    temperatures = arena_make_array<Temp>(arena, width * height);
    altitudes = arena_make_array<Alt>(arena, width * height);
    dailyInsolations = arena_make_2d_array<float>(arena, width, height);
    seasonalInsolations = arena_make_array<float>(arena, width * height);
    cloudCovers = arena_make_array<float>(arena, width * height);
}

	inline uint16_t get_chunk_height(int i) { return i / height_chunks; }

	inline uint16_t get_chunk_width(int i) { return i % height_chunks; }

	inline uint16_t get_chunk_latitude(int i)
	{
		return (get_chunk_height(i) / chunk_latitude_height) - (latitude_total / 2);
	}

	inline uint16_t get_chunk_time_zone(uint32_t chunk_index);
        inline uint16_t get_chunk_index_from_coord(Coord c);
	inline uint32_t get_tile_index_from_coord(Coord c);
	inline Coord get_tile_coord_from_index(uint32_t i);
	inline uint32_t get_tile_index_chunk_relative(uint32_t i);
	inline uint32_t get_tile_index_chunk_relative(Coord c);

	Coord get_random_player_start()
	{	return{ static_cast<uint32_t>(random_chance->next() * length_chunks) , static_cast<uint32_t>(random_chance->next() * height_chunks)};
	}		

	void load_chunk_data(WorldSpawner &ws)
	{
		ws.move_regions_to_chunks(humidities, temperatures, altitudes);
	}

	void update_daily_insolations(uint16_t day365);

	void calculate_chunk_temperature_inputs(Array<int8_t> &water_bodies_dists);

	void update_chunk_temperature();

	void update_weather();

	void apply_weather(TileDatabase* tile_db);

	void apply_precipitation(TileDatabase *tile_db, uint16_t chunk, bool heavy);
	
};

World* g_world;
/*
 * Need to ensure that if a block of tile generates, that some of those tiles aren't actually river
 * tiles,  but haven't been generated as such because neighboring ungenerated tiles which should
 * have river sources on them have not been generated. Thus, need to check if generated cells are
 * river ends of any sort, or lakes, and then for each of those recursively check if there are river
 * continues, following up the chain, until I find the original river sources/lakes, and then
 * recursively generate rivers all the way down, even if those tiles haven't been generated.
 *
 */
