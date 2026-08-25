#pragma once

#include "enum.hpp"
#include "defaults.hpp"
#include "world/tile/database.hpp"
#include <core/containers.hpp>
#include <cereal/types/stack.hpp>
#include <stack>
#include <stdint.h>

#include <world/plant/tables.hpp>
#include <world/animal/database.hpp>
#include <simulation/world_gen.hpp>
#include <simulation/game_time.hpp>

namespace plant {
struct Database
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
    size_t size = 1; // 0 is placeholder
    Stack<size_t> free_slots;
    Array<bool> alives;
  SearchGrid& search;
  World& world;
  
  std::vector<EntityID>& no_inertia_buffer; // size is amount of no inertias this loop
  
  std::vector<EntityID>& unassigned_buffer; // size is amount of unassigned this loop
  tile::Database& tiles;

    // =========================
    // ENTITY-SPECIFIC MEMBERS
    // =========================
    Array<Plant> plants;
    Array<Coord> coord;
    Array<Time> age;



// =========================
// CONSTRUCTOR
// =========================

Database(Arena *arena, size_t capacity
  , World& world
 
  , SearchGrid& search
  , tile::Database& tiles
) :
  world(world),
  tiles(tiles),
search(search),
{
this->capacity = capacity;

  this->size = 0;


 plants = arena_make_array<Plant>(capacity);
 coord = arena_make_array<Coord>(capacity);
 age = arena_make_array<Time>(capacity);

}

// =========================
// GETTERS
// =========================

  inline Plant& plants(const EntityID index) {
return plants[index];
  }
  inline Coord& coord(const EntityID index) {
return coord[index];
  }
  inline Time& age(const EntityID index) {
return age[index];
  }


  
  // =========================
  // SPAWN
  // =========================

  void add_plants(WorldSpawner::PlantSpawnBuffer& spawn_buffer)
{
	for (size_t i = 0; i < spawn_buffer.size; i++)
	  if (spawn(spawn_buffer.plant(i), spawn_buffer.coord(i), false)) {}
	  else
	    {
	      //TODO: error
	    }
}

bool attempt_spawn(Plant plant, bool newborn, Coord coord  , bool insert_search = true
)
  {       
        if (size + 1 > capacity)
            return 0;
        size_t i;
        if (free_slots.empty())
        {
            i = size;
            size++;
        }
        else
        {
            i = free_slots.top();
            free_slots.pop();
        }
        alives[i] = true;
        if (newborn)
        {
            plants(i) = plant;
            coord(i) = coord;
            age(i) = 0;
        }
        else
        {
        Time age = random_bool->next();
            plants(i) = plant;
            coord(i) = coord;
            age(i) = age;
        }
            if (insert_search) search.insert_entity(plant, {i, coord(i)});
        return i;
          }
          
        

size_t spawn(const Plant plant, const bool newborn, const Coord origin
const bool insert_search = true) {
Coord spawn_point = tiles.get_nearest_empty_tile(origin);
size_t result = 0;
while (result == 0) {
result = attempt_spawn(plant, newborn, spawn_point
, insert_search);
if (result == 0) free_unused_entity();
}
}        
    

  // =========================
  // REMOVE
  // =========================
  
  inline bool remove(const EntityID i)
  {
        if (!alive(i))
            return false;

        free_slots.push(i);
        alive(i) = false;
        Plant plant = plant(i);
            search.remove_entity(plant, {i, coord(i)});
        return true;
  }

  inline void free_unused_entity()
  {
    for (size_t i = 0; i < coords.size; i++) {
    if (tiles.tile_status(i).get<VisionStatus>() == VisionStatus::Hidden) remove(i);
    }
  }
    


    // =========================
    // SERIALIZATION
    // =========================

  // genreal serialization

    template <class Archive>
    void save(Archive &archive) const
    {
    archive(capacity);
        archive(size);
        archive(free_slots);
        archive(alives);
   

        plants.save(archive);
        coord.save(archive);
        age.save(archive);
    }

    template <class Archive>
    void load(Archive &archive)
    {
        archive(capacity);
        archive(size);
        archive(free_slots);
        archive(alives);
        
        plants.load(archive);
        coord.load(archive);
        age.load(archive);
    }


// =========================
// TRANSFER
// =========================


inline bool transfer(size_t i, plant::Database &old_db)
  {
  #if !SHIPPING_BUILD
  assert(i < size);
  #endif
  
  if (size >= capacity) return false;
  int index;  
  if (free_slots.empty())
  {
  index = ++size;
	}
	else
	{
		index = free_slots.top();
		free_slots.pop();			
  }
    plants(index) = old_db.plants(i);
    coord(index) = old_db.coord(i);
    age(index) = old_db.age(i);
  alive(index) = true;

  old_db.free_slots.push(i);
  old_db.alive(index) = false;
  return true;
  }
// @codegen:end database_generation

	inline bool viable_harvest(int plant_index);
	inline void set_germination_time(int seed_index);
	inline void germinate(int seed_index, bool random_growth, SearchGrid &search_grid);
	inline void spawn_seed(Plant plant, Coord position);
	inline void prepare_seed_dropping(int animal_index, int plant_index, bool regrowth);
	inline void attempt_plant_growth(int plant, int time, int biome_index);
        inline void excrete_seed(animal::Database& database, int animal_index, tile::Database& tiles, Plant plant);
	inline void plant(int unit_index, Plant plant);
	inline void kill_tree(int plant_index);
	inline void kill_plant(int plant_index);

	void update_plants(World& world, Time time_passed);
};


  struct RegrowthDatabase
{
	plant::Database plant_database;
	Array<Time> regrowths;
	Array<Time> ages;
	Array<uint16_t> produces;
	
	inline void germinate(int seed_index, bool random_growth, SearchGrid &search_grid);
	inline void attempt_plant_growth(int plant, int time, int biome_index);	
};

}
