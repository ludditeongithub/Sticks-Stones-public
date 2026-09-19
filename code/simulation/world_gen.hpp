#pragma once
#include <core/random.hpp>
#include <cstdint>
#include <vector>
#include <core/containers.hpp>
#include <world/animal/enum.hpp>
#include <world/plant/enum.hpp>
#include <world/chunk/data.hpp>
#include <world/tile/enum.hpp>
#include <world/item/scavengeable.hpp>


float range_penalty(float original_value, float min_value, float max_value, float adjusted_value);

class WorldSpawner
{
      public:
	RandomMachine<int> r1_to5 = RandomMachine<int>(1, 5);
	RandomMachine<int> r1_to2 = RandomMachine<int>(1, 2);
	RandomMachine<int> r1_to4 = RandomMachine<int>(1, 4);
	RandomMachine<int> r1_to3 = RandomMachine<int>(1, 4);
	RandomMachine<int> rcx;
	RandomMachine<int> rcy;

	RandomChanceMachine rchance;

	const Hum max_humidity = 500;
	
	const float coast_threshold = -0.2f;
	const float land_threshold = -25.0f;
	const float lowlands_threshold = 9.0f;
	const float midlands_threshold = 14.0f;

	const int depression_threshold = 15;
	const float lowlands_to_highlands_chance =
	    0.01f;				  // chance of const lowlands becoming highlands
	const float lowlands_to_lake_chance = 0.04f; // additional threshold const to become lake
	const float highlands_chance = 0.20f;
	const float coastal_range_chance = 0.005f;
	const float river_from_mountain_chance = 0.5f;
	const float river_from_highland_chance = 0.2f;
	const float river_from_groundwater_chance = 0.3f;
	const float river_end_chance = 0.50f;
	const float lake_from_river_chance = 0.60f;
	const float lake_from_lowlands_chance = 0.05f;
	const float lake_from_midlands_chance = 0.01f;
	const float lake_expansion_chance = 0.60f;
	const float river_from_lake_chance = 0.40f;
	const float ground_water_threshold =
	    80.0f; // how high humidity needs to be for a chance of substantial groundwater to form
	const float humidity_mult = 2.2f;
	const float lake_tile_chance =
	    0.07f; // chance that lake tile does NOT happen (smaller sizes mean larger lakes)

	// BIOMES AMOUNT
	using alt = uint16_t;

	// in biomes
	const int width;
	const int height;
	const int border_width = 3;
	const int border_height = 3;
	const int amount = width * height;
	const int region_size = 100; // average WIDTH and HEIGHT of each region
	const int equator = height / 2;
	// IN TILES
	const int world_width = width * region_size;
	const int world_height = height * region_size;

	// New variables to store the size of the map with borders
	const int width_with_border = width + border_width * 2;
	const int height_with_border = height + border_height * 2;

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

	std::vector<std::vector<Alt>> altitude_map;
	std::vector<std::vector<Temp>> temperature_map;
	std::vector<std::vector<Hum>> humidity_map;
	std::vector<std::vector<Biome>> biome_map;
	std::vector<std::vector<int>> ocean_map;
	std::vector<std::vector<int>> lands_map;
	std::vector<std::vector<int>> water_map;
	std::vector<std::vector<int>> potential_humidity_map;
	std::vector<std::vector<int>> created_humidity_map;
	std::vector<std::vector<bool>> instantiated_water_map;
	std::vector<std::vector<int>> ocean_distance;

	std::vector<std::vector<bool>> r_visited; // holds visited rivers

	const uint32_t tile_amount;


struct TileSpawnBuffer
{
	size_t size;
	std::vector<TileData> tiles;
	std::vector<Alt> altitudes;
  std::vector<bool> occupieds;

  TileSpawnBuffer(size_t capacity)
	{
		tiles.reserve(capacity);
		altitudes.reserve(capacity);
                size = capacity;
        }

inline void add(WorldSpawner& world_spawner, Grass grass, Coord coord)
  {
    size_t i = world_spawner.get_tile_index_from_coord(coord);
    tiles[i].set<Grass>(grass);
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
  inline void add(WorldSpawner& world_spawner, TileSpawnBuffer& tile_spawn_buffer, Animal animal, Coord coord)
	{
		animals[size++] = animal;
		coords[size] = coord;                   tile_spawn_buffer.occupieds[world_spawner.get_tile_index_from_coord(coord)] = true;
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
  inline void add(WorldSpawner& world_spawner, TileSpawnBuffer& tile_spawn_buffer, Plant plant, Coord coord)
	{
		plants[size++] = plant;
		coords[size] = coord;                   tile_spawn_buffer.occupieds[world_spawner.get_tile_index_from_coord(coord)] = true;
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
  inline void add(WorldSpawner& world_spawner, TileSpawnBuffer& tile_spawn_buffer, Scavengeable scavengeable, Coord coord)
	{
		scavengeables[size++] = scavengeable;
		coords[size] = coord;                   tile_spawn_buffer.occupieds[world_spawner.get_tile_index_from_coord(coord)] = true;
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


	TileSpawnBuffer tile_spawn_buffer;
	PlantSpawnBuffer plant_spawn_buffer;
        ScavengeableSpawnBuffer scavengeable_spawn_buffer;
	AnimalSpawnBuffer animal_spawn_buffer;

	template <typename T>
	void map_reserve_rows(int width, int height, std::vector<std::vector<T>> &map)
	{
		map.reserve(height);
		for (int i = 0; i < width; i++)
			map[i].reserve(height);
	}

	WorldSpawner(int width, int height)
	    : width(width), height(height),
	      tile_amount(width * height * CHUNK_SIZE * CHUNKS_PER_REGION)
	{
		rcx = RandomMachine<int>(height / 8, 7 * width / 8);
		rcy = RandomMachine<int>(height / 8, 7 * width / 8);
		map_reserve_rows(width, height, altitude_map);
		map_reserve_rows(width, height, temperature_map);
		map_reserve_rows(width, height, humidity_map);
		map_reserve_rows(width, height, biome_map);
		map_reserve_rows(width, height, ocean_map);
		map_reserve_rows(width, height, lands_map);
		map_reserve_rows(width, height, water_map);
		map_reserve_rows(width, height, potential_humidity_map);
		map_reserve_rows(width, height, created_humidity_map);
		map_reserve_rows(width, height, instantiated_water_map);
		map_reserve_rows(width, height, ocean_distance);
		map_reserve_rows(width, height, r_visited);
                tile_spawn_buffer = TileSpawnBuffer(width * height);
		plant_spawn_buffer = PlantSpawnBuffer(width * height);
                scavengeable_spawn_buffer = ScavengeableSpawnBuffer(width * height);
                animal_spawn_buffer = AnimalSpawnBuffer(width * height);
	}

	void generate_world();
  
	// helpers
	void recursive_lower();
	void recursive_fill();
	void print_map();
        void move_regions_to_chunks(Array<Hum> humidities, Array<Temp> temperatures,
				 Array<Alt> altitudes);
	void print_info();
	Coord get_tile_coord_from_index(size_t i);
        size_t get_tile_index_from_coord(Coord c);

  // world generation
	void generate_oceans_on_maps();
	void mark_coasts();
	void apply_extra_highlands_and_mountains();
	void generate_lands_map();
	void extend_rivers_from_source(uint16_t river_length, int x, int y);
	void mark_river_ends();
	void generate_water_map();
	void generate_temperature_map();
	void generate_humidity_map();
	void factor_wetlands_jungles_and_forests();
	void generate_biomes();
	void generate_altitude_map();
	void get_rivers_from_groundwater();
	void clean_altitude_map();	
std::vector<std::tuple<float, bool, bool>>
humidity_and_rain_shadow_effects(int y, int x, int water, bool biomes);
	void add_depressions();
	void apply_river_tiles();
	std::vector<std::vector<int>>
	calculate_ocean_distance(std::vector<std::vector<int>> &water_map, bool lake, bool river);
	std::vector<Coord> generate_voronoi_sites();
	void generate_tile_types(std::vector<float> &chances, std::vector<Coord> &voronoi_sites,
			       std::vector<Tile> &r_tiles, Array<Alt> &r_altitudes);
	std::vector<float> generate_tile_chances();

  // spawners
  void spawn_grass_and_first_plants();
  void spawn_scavengeables();
  void spawn_animals();

        inline void roll_grass_spawn(Coord coord, Biome biome, Tile tile, int temperature, int humidity);
        inline void roll_plant_spawn(Coord coord, Biome biome, Tile tile, int temperature, int humidity);
        inline void roll_animal_spawn(Coord coord, Biome biome, Tile tile, int temperature, int humidity);
      inline void roll_scavengeable_spawn(Coord coord, Biome biome, Tile tile, int temperature, int humidity);
	// Constants
	// IN CELLS
	int current_x_min = 0;
	int current_x_max = 0;
	int current_y_min = 0;
	int current_y_max = 0;
};
