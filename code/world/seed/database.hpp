#pragma once
#include <core/containers.hpp>
#include "../plant/enum.hpp"
#include "macros/database.hpp"
#include <core/data.hpp>

struct SeedDatabase {
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
    size_t size;
    Stack<size_t> free_slots;
    Array<bool> alives;
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

SeedDatabase(Arena *arena, size_t capacity
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
  // SPAWN
  // =========================

 
  bool attempt_spawn(Plant plant, bool newborn, Coord coord, )
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

        free_slots.push(i);
        alives[i] = false;
        return true;
  }

  void free_unused_entity()
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

// @codegen:end database_generation
};
