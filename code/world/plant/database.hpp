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

constexpr static uint16_t ENTITY_SIZE = sizeof(Plant) +
+ sizeof(bool)
  
 +  sizeof(Plant) 
 +  sizeof(Coord) 
 +  sizeof(Time) 
;

size_t capacity;
    size_t size;
    Stack<size_t> freeSlots;
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

  void addPlants(WorldSpawner::PlantSpawnBuffer& spawnBuffer)
{
	for (size_t i = 0; i < spawnBuffer.size; i++)
	  if (spawn(spawnBuffer.plants[i], spawnBuffer.coords[i], false)) {}
	  else
	    {
	      //TODO: error
	    }
}
 
  bool attemptSpawn(Plant plant, bool newborn, Coord coord, )
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
          Coord spawnPoint = tiles.getNearestEmptyTile(origin);
          while (!attemptSpawn(plant, newborn, spawnPoint)) freeUnusedEntity();                 
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

inline bool transferPlant(size_t i, PlantDatabase &oldDB, PlantDatabase &newDB)
  {
  if (newDB.size >= newDB.capacity) return false;
  int index;  
  if (newDB.freeSlots.empty())
  {
  index = ++size;
	}
	else
	{
		index = newDB.freeSlots.top();
		newDB.freeSlots.pop();			
  }
    newDB.plants[index] = oldDB.plants[i];
    newDB.coords[index] = oldDB.coords[i];
    newDB.ages[index] = oldDB.ages[i];
  newDB.alives[index] = true;
  oldDB.freeSlots.push(i);
  oldDB.alives[index] = false;
  return true;
  }
// @codegen:end database_generation

	inline bool viableHarvest(int plantIndex);
	inline void setGerminationTime(int seedIndex);
	inline void germinate(int seedIndex, bool randomGrowth, SearchGrid &searchGrid);
	inline void spawnSeed(Plant plant, Coord position);
	inline void prepareSeedDropping(int animalIndex, int plantIndex, bool regrowth);
	inline void attemptPlantGrowth(int plant, int time, int biomeIndex);
		inline void excreteSeed(AnimalDatabase& database, int animalIndex, TileDatabase& tiles, Plant plant);
	inline void plant(int unitIndex, Plant plant);
	inline void killTree(int plantIndex);
	inline void killPlant(int plantIndex);

	void updatePlants(World& world, Time timePassed);
};

struct RegrowthPlantDatabase
{
	PlantDatabase plantDatabase;
	Array<Time> regrowths;
	Array<Time> ages;
	Array<uint16_t> produces;
	
	inline void germinate(int seedIndex, bool randomGrowth, SearchGrid &searchGrid);
	inline void attemptPlantGrowth(int plant, int time, int biomeIndex);
	
};

