#pragma once
#include "enum.hpp"
#include "tables.hpp"
#include "defaults.hpp"
#include <core/data.hpp>
#include <core/containers.hpp>
#include <world/world.hpp>
#include <world/tile/database.hpp>

struct BuildableDatabase
{
  	// @codegen:begin database_generation
    // =========================
    // BASE DATABASE MEMBERS
    // =========================

constexpr static uint16_t ENTITY_SIZE = sizeof(Buildable) +
+ sizeof(bool)
  
 +  sizeof(Buildable) 
 +  sizeof(Health) 
 +  sizeof(Coord) 
;

size_t capacity;
    size_t size;
    Stack<size_t> freeSlots;
    Array<bool> alives;
  World& world;
  TileDatabase& tiles;

    // =========================
    // ENTITY-SPECIFIC MEMBERS
    // =========================
    Array<Buildable> buildables;
    Array<Health> healths;
    Array<Coord> coords;
    

// =========================
    // CONSTRUCTOR
    // =========================

BuildableDatabase(Arena *arena, size_t capacity
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

 
  bool attemptSpawn(Buildable buildable, bool newborn, Coord coord, )
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
            buildables[i] = buildable;
            healths[i] = buildable::maxHealths[buildable] * INFANT_HEALTH_MODIFIER;
            coords[i] = coord;
        }
        else
        {
        Time age = random_bool->next();
            buildables[i] = buildable;
            healths[i] = getMaxHealth(buildable, age);
            coords[i] = coord;
        }
        return true;
          }
          bool spawn(Buildable buildable, bool newborn, Coord origin) {
          Coord spawnPoint = tiles.getNearestEmptyTile(origin);
          while (!attemptSpawn(buildable, newborn, spawnPoint)) freeUnusedEntity();                 
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
        return true;
  }

  void freeUnusedEntity()
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
   

        buildables.save(archive);
        healths.save(archive);
        coords.save(archive);
    }

    template <class Archive>
    void load(Archive &archive)
    {
        archive(capacity);
        archive(size);
        archive(freeSlots);
        archive(alives);
        
        buildables.load(archive);
        healths.load(archive);
        coords.load(archive);
    }

// @codegen:end database_generation
};
