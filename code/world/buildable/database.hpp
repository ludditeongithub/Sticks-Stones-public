#pragma once
#include "enum.hpp"
#include "tables.hpp"
#include <core/data.hpp>
#include <core/containers.hpp>

struct BuildableDatabase
{
  	// @codegen:begin database_generation
    // =========================
    // BASE DATABASE MEMBERS
    // =========================

constexpr static uint16_t ENTITY_SIZE = sizeof(bool)

 +  sizeof(Health) 

 +  sizeof(Coord) 

;

size_t capacity;
Array<Buildable> buildables;

    size_t size;
    Stack<size_t> freeSlots;
    Array<bool> alives;
  



    // =========================
    // ENTITY-SPECIFIC MEMBERS
    // =========================

    Array<Health> healths;

    Array<Coord> coords;
    


  // =========================
  // SPAWN
  // =========================
  
  bool spawn(Buildable entity, bool newborn, Coord coord)
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
      
            healths[i] = maxHealths[{{ entity_name }}] * INFANT_HEALTH_MODIFIER;
	  
            coords[i] = coord;
	  
        }
        else
        {
        Time age = random_bool->next();
	  
            healths[i] = getMaxHealth(age);
	  
            coords[i] = coord;
	  
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

        

        healths.load(archive);

        coords.load(archive);

    }

    // =========================
    // CONSTRUCTOR
    // =========================

BuildableDatabase(Arena *arena, size_t capacity

  , World& world


)
    {
this->capacity = capacity;

  this->size = 0;
        
    }

// @codegen:end database_generation
};
