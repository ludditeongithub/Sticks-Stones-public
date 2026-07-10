#pragma once

#include "enum.hpp"
#include "defaults.hpp"
#include "world/tile/database.hpp"
#include <core/containers.hpp>
#include <extern/cereal/types/stack.hpp>
#include <stack>
#include <stdint.h>
#include <systems/find_nearest.hpp>
#include <world/plant/tables.hpp>
#include <world/animal/database.hpp>
#include <simulation/world_gen.hpp>
#include <simulation/game_time.hpp>


struct PlantDatabase
{
	// @codegen:begin database_generation
    // =========================
    // BASE DATABASE MEMBERS
    // =========================

constexpr static uint16_t entity_size = sizeof(Plant) +
+ sizeof(bool)
  
 +  sizeof(Plant) 
 +  sizeof(Coord) 
 +  sizeof(Time) 
;

size_t capacity;
    size_t size;
    Stack<size_t> free_slots;
    Array<bool> alives;
  SearchGrid& search;
  World& world;
  TileDatabase& tiles;

    // =========================
    // ENTITY-SPECIFIC MEMBERS
    // =========================
    Array<Plant> plants;
    Array<Coord> coords;
    Array<Time> ages;
    

// =========================
    // CONSTRUCTOR
    // =========================

PlantDatabase(Arena *arena, size_t capacity
  , World& world
 
  , SearchGrid& search
  , TileDatabase& tiles
) :
  world(world),
  tiles(tiles),
search(search),
{
this->capacity = capacity;
  this->size = 0;

}

  // =========================
  // SPAWN
  // =========================

  void add_plants(WorldSpawner::PlantSpawnBuffer& spawn_buffer)
{
	for (size_t i = 0; i < spawn_buffer.size; i++)
	  if (spawn(spawn_buffer.plants[i], spawn_buffer.coords[i], false)) {}
	  else
	    {
	      //TODO: error
	    }
}
 
  bool attempt_spawn(Plant plant, bool newborn, Coord coord )
  {       
        if (size + 1 > capacity)
            return false;
        size_t i;
        if (freeSlots.empty())
        {
            i = size;
            size++;
        }
        else
        {
            i = freeSlots.top();
            freeSlots.pop();
        }
        alives[i] = true;
        if (newborn)
        {
            plants[i] = plant;
            coords[i] = coord;
            ages[i] = 0;
        }
        else
        {
        Time age = random_bool->next();
            plants[i] = plant;
            coords[i] = coord;
            ages[i] = age;
        }
            search.insertEntity(plant, {i, coords[i]});
        return true;
          }
          bool spawn(Plant plant, bool newborn, Coord origin) {
          Coord spawn_point = tiles.get_nearest_empty_tile(origin);
          while (!attempt_spawn(plant, newborn, spawn_point)) free_unused_entity();                 
          }        
    

  // =========================
  // REMOVE
  // =========================
  
  bool remove(size_t i)
  {
        if (!alives[i])
            return false;

        freeSlots.push(i);
        alives[i] = false;
        Plant plant = plants[i];
            search.removeEntity(plant, {i, coords[i]});
        return true;
  }

  void free_unused_entity()
  {
    for (size_t i = 0; i < coords.size; i++) {
    if (tiles.tileStatuses[i].get<VisionStatus>() == VisionStatus::Hidden) remove(i);
    }
  }
    

      
    // =========================
    // SERIALIZATION
    // =========================

    template <class Archive>
    void save(Archive &archive) const
    {
    archive(capacity);
        archive(size);
        archive(freeSlots);
        archive(alives);
   

        plants.save(archive);
        coords.save(archive);
        ages.save(archive);
    }

    template <class Archive>
    void load(Archive &archive)
    {
        archive(capacity);
        archive(size);
        archive(freeSlots);
        archive(alives);
        
        plants.load(archive);
        coords.load(archive);
        ages.load(archive);
    }


// =========================
// TRANSFER
// =========================

inline bool transfer_plant(size_t i, PlantDatabase &old_db, PlantDatabase &new_db)
  {
  if (new_db.size >= new_db.capacity) return false;
  int index;  
  if (new_db.freeSlots.empty())
  {
  index = ++size;
	}
	else
	{
		index = new_db.freeSlots.top();
		new_db.freeSlots.pop();			
  }
    new_db.plants[index] = old_db.plants[i];
    new_db.coords[index] = old_db.coords[i];
    new_db.ages[index] = old_db.ages[i];
  new_db.alives[index] = true;
  old_db.freeSlots.push(i);
  old_db.alives[index] = false;
  return true;
  }
// @codegen:end database_generation

	inline bool viable_harvest(int plant_index);
	inline void set_germination_time(int seed_index);
	inline void germinate(int seed_index, bool random_growth, SearchGrid &search_grid);
	inline void spawn_seed(Plant plant, Coord position);
	inline void prepare_seed_dropping(int animal_index, int plant_index, bool regrowth);
	inline void attempt_plant_growth(int plant, int time, int biome_index);
		inline void excrete_seed(AnimalDatabase& database, int animal_index, TileDatabase& tiles, Plant plant);
	inline void plant(int unit_index, Plant plant);
	inline void kill_tree(int plant_index);
	inline void kill_plant(int plant_index);

	void update_plants(World& world, Time time_passed);
};

struct RegrowthPlantDatabase
{
	PlantDatabase plant_database;
	Array<Time> regrowths;
	Array<Time> ages;
	Array<uint16_t> produces;
	
	inline void germinate(int seed_index, bool random_growth, SearchGrid &search_grid);
	inline void attempt_plant_growth(int plant, int time, int biome_index);
	
};

