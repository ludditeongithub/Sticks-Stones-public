#pragma once
#include <core/containers.hpp>
#include "../plant/enum.hpp"
#include "macros/database.hpp"
#include <core/data.hpp>
namespace seed {
struct Database {
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
 
  , tile::Database& tiles
) :
  world(world),
  tiles(tiles),
{
this->capacity = capacity;

  this->size = 0;

}

// =========================
// GETTERS
// =========================

  inline Plant& plants(size_t index) {
return plants[index];
  }
  inline Coord& coord(size_t index) {
return coord[index];
  }
  inline Time& age(size_t index) {
return age[index];
  }


  // =========================
  // SPAWN
  // =========================

 
  bool attempt_spawn(Plant plant, bool newborn, Coord coord  )
  {       
        if (size + 1 > capacity)
            return false;
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
        if (!alive(i))
            return false;

        free_slots.push(i);
        alive(i) = false;
        return true;
  }

  void free_unused_entity()
  {
    for (size_t i = 0; i < coords.size; i++) {
    if (tiles.tile_status(i).get<VisionStatus>() == VisionStatus::Hidden) remove(i);
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

// @codegen:end database_generation
};

}
