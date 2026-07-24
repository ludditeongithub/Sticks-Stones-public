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
	World& world;
  	// @codegen:begin database_generation
    // =========================
    // BASE DATABASE MEMBERS
    // =========================

constexpr static uint16_t ENTITY_SIZE = sizeof(Tiledata) +
  
 +  sizeof(Tiledata) 
 +  sizeof(Alt) 
 +  sizeof(Liquid) 
 +  sizeof(TileStatus) 
;

size_t capacity;
  World& world;

    // =========================
    // ENTITY-SPECIFIC MEMBERS
    // =========================
    Array<Tiledata> tiledatas;
    Array<Alt> altitudes;
    Array<Liquid> waters;
    Array<TileStatus> tile_statuses;
    

// =========================
    // CONSTRUCTOR
    // =========================

TileDatabase(Arena *arena, size_t capacity
  , World& world
 
) :
  world(world),
{
this->capacity = capacity;

}

    

    

      
    // =========================
    // SERIALIZATION
    // =========================

    template <class Archive>
    void save(Archive &archive) const
    {
    archive(capacity);
   

        tiledatas.save(archive);
        altitudes.save(archive);
        waters.save(archive);
        tile_statuses.save(archive);
    }

    template <class Archive>
    void load(Archive &archive)
    {
        archive(capacity);
        
        tiledatas.load(archive);
        altitudes.load(archive);
        waters.load(archive);
        tile_statuses.load(archive);
    }

// @codegen:end database_generation
	
	Coord get_nearest_empty_tile(Coord coord);
		Coord get_nearest_empty_tile_block(Coord coord, size_t length, size_t width = 1);
		inline size_t get_index(const Coord coord)
		{
return coord.y * 
		}
		inline Frame calc_inertia(const Coord coord, bool running);
		inline Frame calc_inertia(Frame entity_base_frames, const Coord coord);
};
