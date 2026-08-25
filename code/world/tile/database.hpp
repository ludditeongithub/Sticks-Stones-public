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

namespace tile {
// TODO: whenever a tile is interacted with, notify all 
// TODO: enforce occupied on other databses
class Database
{
      public:
	World& world;
  	// @codegen:begin database_generation
// =========================
// BASE DATABASE MEMBERS
// =========================

constexpr static uint16_t entity_size = sizeof(Tile_data) +
  
 +  sizeof(Tile_data) 
 +  sizeof(Alt) 
 +  sizeof(Liquid) 
 +  sizeof(TileStatus) 
 +  sizeof(Entity) 
;

size_t capacity;

    // =========================
    // ENTITY-SPECIFIC MEMBERS
    // =========================
    Array<Tile_data> tile_datas;
    Array<Alt> altitude;
    Array<Liquid> water;
    Array<TileStatus> tile_status;
    Array<Entity> entity;



// =========================
// CONSTRUCTOR
// =========================

Database(Arena *arena, size_t capacity
  , World& world
 
) :
  world(world),
{
this->capacity = capacity;



 tile_datas = arena_make_array<Tile_data>(capacity);
 altitude = arena_make_array<Alt>(capacity);
 water = arena_make_array<Liquid>(capacity);
 tile_status = arena_make_array<TileStatus>(capacity);
 entity = arena_make_array<Entity>(capacity);

}

// =========================
// GETTERS
// =========================

  inline Tile_data& tile_datas(const EntityID index) {
return tile_datas[index];
  }
  inline Alt& altitude(const EntityID index) {
return altitude[index];
  }
  inline Liquid& water(const EntityID index) {
return water[index];
  }
  inline TileStatus& tile_status(const EntityID index) {
return tile_status[index];
  }
  inline Entity& entity(const EntityID index) {
return entity[index];
  }


    

    


    // =========================
    // SERIALIZATION
    // =========================

  // genreal serialization

    template <class Archive>
    void save(Archive &archive) const
    {
    archive(capacity);
   

        tile_datas.save(archive);
        altitude.save(archive);
        water.save(archive);
        tile_status.save(archive);
        entity.save(archive);
    }

    template <class Archive>
    void load(Archive &archive)
    {
        archive(capacity);
        
        tile_datas.load(archive);
        altitude.load(archive);
        water.load(archive);
        tile_status.load(archive);
        entity.load(archive);
    }

// @codegen:end database_generation
	
	Coord get_nearest_empty_tile(Coord coord);
		Coord get_nearest_empty_tile_block(Coord coord, size_t length, size_t width = 1);
  inline size_t get_index(const Coord coord){return (coord.y * world.height_chunks) + (coord.x * world.length_chunks);}
  inline Coord get_coord(const size_t index){return {(index % world.length_chunks), (index / world.height_chunks)};}
  inline Frame calc_inertia(const Coord coord, bool running);
		inline Frame calc_inertia(Frame entity_base_frames, const Coord coord);
};
}
