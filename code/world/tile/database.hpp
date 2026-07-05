#pragma once
#include "enum.hpp"
#include "world/chunk/data.hpp"
#include "world/tile/data.hpp"
#include <core/containers.hpp>
#include <core/data.hpp>
#include <queue>
#include <simulation/world_gen.hpp>
#include <vector>
#include <world/world.hpp>

// TODO: enforce occupied on other databses
class TileDatabase
{
      public:
  
  	// @codegen:begin database_generation
    // =========================
    // BASE DATABASE MEMBERS
    // =========================

constexpr static uint16_t ENTITY_SIZE = sizeof(Tiledata) +
  

 +  sizeof(Alt) 

 +  sizeof(Liquid) 

 +  sizeof(TileStatus) 

;

size_t capacity;
Array<Tiledata> tiles;




    // =========================
    // ENTITY-SPECIFIC MEMBERS
    // =========================

    Array<Alt> altitudes;

    Array<Liquid> waters;

    Array<TileStatus> tileStatuses;
    

    

    


      
    // =========================
    // SERIALIZATION
    // =========================

    template <class Archive>
    void save(Archive &archive) const
    {
    archive(capacity);
   


        altitudes.save(archive);

        waters.save(archive);

        tileStatuses.save(archive);

    }

    template <class Archive>
    void load(Archive &archive)
    {
        archive(capacity);

        

        altitudes.load(archive);

        waters.load(archive);

        tileStatuses.load(archive);

    }

    // =========================
    // CONSTRUCTOR
    // =========================

TileDatabase(Arena *arena, size_t capacity

  , World& world


)
    {
this->capacity = capacity;
        
    }

// @codegen:end database_generation
	
	Coord getNearestEmptyTile(Coord coord);
	
};
