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
  

 +  sizeof(Coord) 

 +  sizeof(Time) 

;

size_t capacity;
Array<Plant> seeds;

    size_t size;
    Stack<size_t> freeSlots;
    Array<bool> alives;
  



    // =========================
    // ENTITY-SPECIFIC MEMBERS
    // =========================

    Array<Coord> coords;

    Array<Time> ages;
    


  // =========================
  // SPAWN
  // =========================
  
  bool spawn(Seed entity, bool newborn, Coord coord)
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

        search.deleteEntity();

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

SeedDatabase(Arena *arena, size_t capacity

  , World& world


)
    {
this->capacity = capacity;

  this->size = 0;
        
    }

// @codegen:end database_generation
};
