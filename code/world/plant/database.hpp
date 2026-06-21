#pragma once

#include "enum.hpp"
#include "seed_database.hpp"
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
	static constexpr uint32_t ENTITY_SIZE =
	    sizeof(Plant) + sizeof(float) + sizeof(Coord) + sizeof(float) + sizeof(Time);

	// @codegen:begin database_generation
    // =========================
    // BASE DATABASE MEMBERS
    // =========================

constexpr static uint16_t ENTITY_SIZE = sizeof(bool)

 +  sizeof(Coord) 

 +  sizeof(Time) 

;

size_t capacity;
Array<Plant> plants;

    size_t size;
    Stack<size_t> freeSlots;
    Array<bool> alives;
  

  SearchGrid& search;



    // =========================
    // ENTITY-SPECIFIC MEMBERS
    // =========================

    Array<Coord> coords;

    Array<Time> ages;
    


  // =========================
  // SPAWN
  // =========================
  
  bool spawn(Plant entity, bool newborn, Coord coord)
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
      
            coords[i] = coord;
	  
            ages[i] = 0;
	  
        }
        else
        {
        Time age = random_bool->next();
	  
            coords[i] = coord;
	  
            ages[i] = age;
	  
        }
	  
  
          

        return true;
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

        search.deleteEntity;

        return true;
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

        

        coords.load(archive);

        ages.load(archive);

    }

    // =========================
    // CONSTRUCTOR
    // =========================

PlantDatabase(Arena *arena, size_t capacity

  , World& world


  , SearchGrid& search

)
    {
this->capacity = capacity;

  this->size = 0;
        
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

