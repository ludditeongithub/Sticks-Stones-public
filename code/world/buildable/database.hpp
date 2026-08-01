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
    size_t size = 1; // 0 is placeholder
    Stack<size_t> free_slots;
    Array<bool> alives;
  TileDatabase& tiles;

    // =========================
    // ENTITY-SPECIFIC MEMBERS
    // =========================
    Array<Buildable> buildables;
    Array<Health> healths;
    Array<Coord> coords;

    struct main {
    
    
    }


// =========================
// CONSTRUCTOR
// =========================

Database(Arena *arena, size_t capacity
  , World& world
 
  , TileDatabase& tiles
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
return buildabless[index];
  }
  inline Health& healths(size_t index) {
return healthss[index];
  }
  inline Coord& coords(size_t index) {
return coordss[index];
  }

    inline Health& healths(size_t index) {    
return main[index].healths;
    }
    inline Coord& coords(size_t index) {    
return main[index].coords;
    }

  // =========================
  // SPAWN
  // =========================


// returns 0 if failed
  size_t attempt_spawn(Buildable buildable, bool newborn, Coord coord  )
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
            buildables(i) = buildable;
            healths(i) = buildable::maxHealths[buildable] * INFANT_HEALTH_MODIFIER;
            coords(i) = coord;
        }
        else
        {
        Time age = random_bool->next();
            buildables(i) = buildable;
            healths(i) = getMaxHealth(buildable, age);
            coords(i) = coord;
        }
        return i;
          }
          
          size_t spawn(Buildable buildable, bool newborn, Coord origin
bool insert_search = true) {
Coord spawn_point = tiles.get_nearest_empty_tile(origin);
size_t result = 0;
while (result == 0) {
result = attempt_spawn(buildable, newborn, spawn_point
, insert_search);
if (result == 0) free_unused_entity();
}
}        
    

  // =========================
  // REMOVE
  // =========================
  
  inline bool remove(size_t i)
  {
        if (!alives[i])
            return false;

        free_slots.push(i);
        alives[i] = false;
        return true;
  }

  inline void free_unused_entity()
  {
    for (size_t i = 0; i < coords.size; i++) {
    if (tiles.tile_statuses[i].get<VisionStatus>() == VisionStatus::Hidden) remove(i);
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
        healths.save(archive);
        coords.save(archive);
    }

    template <class Archive>
    void load(Archive &archive)
    {
        archive(capacity);
        archive(size);
        archive(free_slots);
        archive(alives);
        
        buildables.load(archive);
        healths.load(archive);
        coords.load(archive);
    }

// @codegen:end database_generation
};

}
