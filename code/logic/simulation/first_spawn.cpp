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


#include "world_gen.hpp"
#include "core/tables.hpp"
#include "data/const/tile_data.hpp"
#include "data/run/world.hpp"
#include <core/random.hpp>
#include <data/types/animal.hpp>
#include <data/run/animal_database.hpp>
#include <world/animal/spawn_tables.hpp>
#include <data/types/plant.hpp>
#include <world/plant/spawn_tables.hpp>
#include <world/tile/grass.hpp>
#include <data/types/tile.hpp>
#include <world/item/scavengeable.hpp>


// @codegen:begin grass_spawn

// THIS IS a Test
inline void WorldSpawner::roll_grass_spawn(Coord coord, Biome biome, Tile tile, int temperature, int humidity)
{
float highest_roll = 0.0;
Grass grass = Grass::NONE;


  for (size_t i = 0; i < static_cast<size_t>(Grass::MAX); i++) { //2
  Grass selected_grass = static_cast<Grass>(i);

float roll = random_chance->next() * 0.4;
for (size_t j = 0; j < static_cast<size_t>(Tile::MAX); j++) { //3
if (tile == static_cast<Tile>(j)) { //4
float multiplied_roll = grass::tile_spawn_multipliers[grass][static_cast<Tile>(j)] * roll;

const Coord tpr = grass::temperature_penalty_ranges[grass];
float adj_temp_roll = range_penalty(temperature, tpr.x, tpr.y, multiplied_roll);
const Coord hpr = grass::humidity_penalty_ranges[grass];
float adj_final_roll = range_penalty(humidity, hpr.x, hpr.y, adj_temp_roll);
  

if (adj_final_roll > highest_roll) { //5
highest_roll = adj_final_roll;
grass = selected_grass;
} //5
  } //4
} //3
} //2

if (grass != Grass::NONE)
  if (highest_roll > grass::minimum_roll[biome]) tile_spawn_buffer.add(*this, grass, coord);
}

// @codegen:end grass_spawn

// @codegen:begin plant_spawn

// THIS IS  a Test
inline void WorldSpawner::roll_plant_spawn(Coord coord, Biome biome, Tile tile, int temperature, int humidity)
{
float highest_roll = 0.0;
Plant plant = Plant::NONE;


  for (size_t i = 0; i < static_cast<size_t>(PlantCategory::MAX); i++) { // 1
  float category_roll = random_chance->next();
  if (category_roll < plant::category_spawn_chances[static_cast<PlantCategory>(i)][biome]) for (size_t j = 0; j < plant::categories[static_cast<PlantCategory>(i)].size(); j++) { //2
  Plant selected_plant = plant::categories[static_cast<PlantCategory>(i)][static_cast<Plant>(j)];

float roll = random_chance->next() * 0.4;
for (size_t j = 0; j < static_cast<size_t>(Tile::MAX); j++) { //3
if (tile == static_cast<Tile>(j)) { //4
float multiplied_roll = plant::tile_spawn_multipliers[plant][static_cast<Tile>(j)] * roll;

const Coord tpr = plant::temperature_penalty_ranges[plant];
float adj_temp_roll = range_penalty(temperature, tpr.x, tpr.y, multiplied_roll);
const Coord hpr = plant::humidity_penalty_ranges[plant];
float adj_final_roll = range_penalty(humidity, hpr.x, hpr.y, adj_temp_roll);
  

if (adj_final_roll > highest_roll) { //5
highest_roll = adj_final_roll;
plant = selected_plant;
} //5
  } //4
} //3
} //2

if (plant != Plant::NONE)
  plant_spawn_buffer.add(*this, plant, coord);

  } // 1
}

// @codegen:end plant_spawn

// @codegen:begin scavengeable_spawn

// THIS IS  a Test
inline void WorldSpawner::roll_scavengeable_spawn(Coord coord, Biome biome, Tile tile, int temperature, int humidity)
{
float highest_roll = 0.0;
Scavengeable scavengeable = Scavengeable::NONE;


  for (size_t i = 0; i < static_cast<size_t>(Scavengeable::MAX); i++) { //2
  Scavengeable selected_scavengeable = static_cast<Scavengeable>(i);

float multiplied_roll = scavengeable::biome_spawn_chances[biome][scavengeable];

float adj_final_roll = multiplied_roll;
  

if (adj_final_roll > highest_roll) { //5
highest_roll = adj_final_roll;
scavengeable = selected_scavengeable;
} //5
} //2

if (scavengeable != Scavengeable::NONE)
  scavengeable_spawn_buffer.add(*this, scavengeable, coord);

}

// @codegen:end scavengeable_spawn


// @codegen:begin animal_spawn

// THIS IS  a Test
inline void WorldSpawner::roll_animal_spawn(Coord coord, Biome biome, Tile tile, int temperature, int humidity)
{
float highest_roll = 0.0;
Animal animal = Animal::NONE;


  for (size_t i = 0; i < static_cast<size_t>(Animal::MAX); i++) { //2
  Animal selected_animal = static_cast<Animal>(i);

float multiplied_roll = animal::biome_spawn_chances[biome][animal];

const Coord tpr = animal::temperature_penalty_ranges[animal];
float adj_temp_roll = range_penalty(temperature, tpr.x, tpr.y, multiplied_roll);
const Coord hpr = animal::humidity_penalty_ranges[animal];
float adj_final_roll = range_penalty(humidity, hpr.x, hpr.y, adj_temp_roll);
  

if (adj_final_roll > highest_roll) { //5
highest_roll = adj_final_roll;
animal = selected_animal;
} //5
} //2

if (animal != Animal::NONE)
  animal_spawn_buffer.add(*this, animal, coord);

}

// @codegen:end animal_spawn

// puts into relevant buffer for each
void WorldSpawner::spawn_entities()
{
	// spawn grass and plants
	spawn_grass_and_first_plants();
	// spawn scavengeables
	spawn_scavengeables();
	// spawn animals

	// spawn tribes
}

inline bool skip_unplantable_tiles(Tile tile)
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
void WorldSpawner::spawn_grass_and_first_plants()
{
	plant_spawn_buffer.reserve(TILE_AMOUNT);
        
	bool regrowth_plant = false;
	float chances = 0;
	float p = 0;
	constexpr std::array<Plant, 4> TREES = {Plant::DeciduousTree, Plant::EvergreenTree,
							Plant::PioneerTree, Plant::TropicalTree};

	for (int i = 0; i < tile_spawn_buffer.tiles.size(); i++)
	{
          Tile tile = tile_spawn_buffer.tiles[i];
          skip_unplantable_tiles(tile);

		// TODO: separate mechanism for plants that stay in the same place and
		// those who do not
		//  mechanism to only work on some tsb.tiles for subsequent spawns.
		Coord coord = get_tile_coord_from_index(i);
		Biome biome = biome_map[i / CHUNK_LENGTH][i % CHUNK_LENGTH];
		int temperature = temperature_map[i / CHUNK_LENGTH][i % CHUNK_LENGTH];
		int humidity = humidity_map[i / CHUNK_LENGTH][i % CHUNK_LENGTH];

		float plant_coverage = plant::coverages[biome];
		float grass_coverage = grass::coverages[biome];

		if (random_chance->next() < grass_coverage)
		{
                  roll_grass_spawn(coord, biome, tile, temperature, humidity);                        
                }
		if (random_chance->next() < plant_coverage)
		{
                  roll_plant_spawn(coord, biome, tile, temperature, humidity);
                }
	}
        plant_spawn_buffer.shrink_to_size();
}

// TODO: move data into lookup table. possibly spawn animals per chunk instead
// of per tile!
//  APPLY ANIMAL SPAWNS
void WorldSpawner::spawn_animals()
{
	animal_spawn_buffer.reserve(TILE_AMOUNT);

	for (int i = 0; i < TILE_AMOUNT; i++)
	{
          Tile tile = tile_spawn_buffer.tiles[i];
		// TODO: water animals
            if (is_water(tile)) continue;
		    Coord coord = get_tile_coord_from_index(i);
		    Coord chunk_coord = get_chunk_from_tile(coord);
		    Biome biome = biome_map[chunk_coord.x][chunk_coord.y];
		    Temp temperature = temperature_map[chunk_coord.x][chunk_coord.y];
                    Hum humidity = humidity_map[chunk_coord.x][chunk_coord.y];
        roll_animal_spawn(coord, biome, tile, temperature, humidity);
         }
          animal_spawn_buffer.shrink_to_size();
}

void WorldSpawner::spawn_scavengeables()
{	
  for (int i = 0; i < TILE_AMOUNT; i++)
	{
		Tile tile = tile_spawn_buffer.tiles[i];
                // TODO: seaweed, lilipads etc
		Coord coord = get_tile_coord_from_index(i);
                Coord chunk_coord = get_chunk_from_tile(coord);
		Biome biome = biome_map[chunk_coord.x][chunk_coord.y];
		Temp temperature = temperature_map[chunk_coord.x][chunk_coord.y];
                Hum humidity = humidity_map[chunk_coord.x][chunk_coord.y];
		roll_scavengeable_spawn(coord, biome, tile, temperature, humidity);
	
	}
}

