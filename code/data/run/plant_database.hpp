#pragma once
#include "data/run/tile_database.hpp"
#include <core/containers.hpp>
#include <cereal/types/stack.hpp>
#include <stack>
#include <stdint.h>

#include <world/plant/tables.hpp>
#include <data/run/animal_database.hpp>
#include <logic/simulation/world_gen.hpp>
#include <logic/simulation/game_time.hpp>

namespace plant {
class Database
{
	// @codegen:begin database_generation
// =========================
// BASE DATABASE MEMBERS
// =========================

constexpr static uint16_t ENTITY_SIZE = sizeof(Plant) +
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
  
  std::vector<EntityID>& no_inertia_buffer; // size is amount of no inertias this loop
  
  std::vector<EntityID>& unassigned_buffer; // size is amount of unassigned this loop
  World& world;
  tile::Database& tiles;

    // =========================
    // ENTITY-SPECIFIC MEMBERS
    // =========================
    Array<Plant> plants;
    Array<Coord> coords;
    Array<Time> ages;



// =========================
// CONSTRUCTOR
// =========================

Database(Arena* arena, size_t capacity
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


 
 plants = arena_make_array<Plant>(arena, capacity); 
 
 coords = arena_make_array<Coord>(arena, capacity); 
 
 ages = arena_make_array<Time>(arena, capacity); 
 

}

// =========================
// GETTERS
// =========================

  inline Plant& plant(const EntityID index) {
return plants[index];
  }
  inline Coord& coord(const EntityID index) {
return coords[index];
  }
  inline Time& age(const EntityID index) {
return ages[index];
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

bool attempt_spawn(const Plant plant, const bool newborn, const Coord coord  , const bool insert_search = true
)
{
#if !SHIPPING_BUILD
assert(plant != Plant::NONE && plant != Plant::MAX && "Tried to spawn plant as NONE or MAX.");
#endif


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
            this->plant(i) = plant;
            this->coord(i) = coord;
            this->age(i) = 0;
        }
        else
        {
        Time age = random_bool->next();
            this->plant(i) = plant;
            this->coord(i) = coord;
            this->age(i) = age;
        }
            if (insert_search) search.insert_entity(plant, {i, this->coord(i)});
        return i;
          }
          
        

size_t spawn(const Plant plant, const bool newborn, const Coord origin
, const bool insert_search = true) {
Coord spawn_point = tiles.get_nearest_empty_tile(origin);
size_t result = 0;
while (result == 0) {
result = attempt_spawn(plant, newborn, spawn_point
, insert_search  
);
if (result == 0) free_unused_entity();
}
}        
    

  // =========================
  // REMOVE
  // =========================
  
  inline bool remove(const EntityID i)
  {
        if (!alives[i])
            return false;

        free_slots.push(i);
        alives[i] = false;
        Plant plant = this->plant(i);
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
        coords.save(archive);
        ages.save(archive);
    }

    template <class Archive>
    void load(Archive &archive)
    {
        archive(capacity);
        archive(size);
        archive(free_slots);
        archive(alives);
        
        plants.load(archive);
        coords.load(archive);
        ages.load(archive);
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
    plant(index) = old_db.plant(i);
    coord(index) = old_db.coord(i);
    age(index) = old_db.age(i);
  alives[index] = true;

  old_db.free_slots.push(i);
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
