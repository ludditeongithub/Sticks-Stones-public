#pragma once
#include "enum.hpp"
#include "tables.hpp"
#include "defaults.hpp"
#include <core/data.hpp>
#include <core/containers.hpp>
#include <world/world.hpp>
#include <world/tile/database.hpp>

namespace buildable {
struct Database
{
  	// @codegen:begin database_generation
// =========================
// BASE DATABASE MEMBERS
// =========================

constexpr static uint16_t entity_size = sizeof(Buildable) +
+ sizeof(bool)
  
 +  sizeof(Buildable) 
 +  sizeof(Health) 
 +  sizeof(Coord) 
;

size_t capacity;
    size_t size;
    Stack<size_t> free_slots;
    Array<bool> alives;
  tile::Database& tiles;

    // =========================
    // ENTITY-SPECIFIC MEMBERS
    // =========================
    Array<Buildable> buildables;
    Array<Health> health;
    Array<Coord> coord;

struct Main {
    Array<Health> health;
    Array<Coord> coord;
};


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

  inline Buildable& buildables(size_t index) {
return buildables[index];
  }
  inline Health& health(size_t index) {
return health[index];
  }
  inline Coord& coord(size_t index) {
return coord[index];
  }

    inline Health& health(size_t index) {    
return main[index].health;
    }
    inline Coord& coord(size_t index) {    
return main[index].coord;
    }

  // =========================
  // SPAWN
  // =========================

 
  bool attempt_spawn(Buildable buildable, bool newborn, Coord coord  )
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
            buildables(i) = buildable;
            health(i) = buildable::maxHealths[buildable] * INFANT_HEALTH_MODIFIER;
            coord(i) = coord;
        }
        else
        {
        Time age = random_bool->next();
            buildables(i) = buildable;
            health(i) = getMaxHealth(buildable, age);
            coord(i) = coord;
        }
        return true;
          }
          
          bool spawn(Buildable buildable, bool newborn, Coord origin) {
          Coord spawn_point = tiles.get_nearest_empty_tile(origin);
          while (!attempt_spawn(buildable, newborn, spawn_point)) free_unused_entity();                 
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
   

        buildables.save(archive);
        health.save(archive);
        coord.save(archive);
    }

    template <class Archive>
    void load(Archive &archive)
    {
        archive(capacity);
        archive(size);
        archive(free_slots);
        archive(alives);
        
        buildables.load(archive);
        health.load(archive);
        coord.load(archive);
    }

// @codegen:end database_generation
};

}
