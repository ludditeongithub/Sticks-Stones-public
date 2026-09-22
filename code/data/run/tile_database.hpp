#pragma once
#include <data/types/tile.hpp>
#include "data/const/chunk_data.hpp"
#include "data/const/tile_data.hpp"
#include <data/types/entity.hpp>
#include <core/containers.hpp>
#include <data/types/aliases.hpp>
#include <queue>
#include <logic/simulation/world_gen.hpp>
#include <vector>
#include <data/run/world.hpp>

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

constexpr static uint16_t entity_size = sizeof(Tiledata) +
  
 +  sizeof(Tiledata) 
 +  sizeof(Alt) 
 +  sizeof(Liquid) 
 +  sizeof(TileStatus) 
 +  sizeof(Entity) 
;

size_t capacity;

    // =========================
    // ENTITY-SPECIFIC MEMBERS
    // =========================
    Array<Tiledata> tiledatas;
    Array<Alt> altitudes;
    Array<Liquid> waters;
    Array<TileStatus> tile_statuss;
    Array<Entity> entitys;



// =========================
// CONSTRUCTOR
// =========================

Database(Arena& arena, size_t capacity
  , World& world
 
) :
  world(world),
{
this->capacity = capacity;



 
 tiledatas = arena_make_array<Tiledata>(arena, capacity); 
 
 altitudes = arena_make_array<Alt>(arena, capacity); 
 
 waters = arena_make_array<Liquid>(arena, capacity); 
 
 tile_statuss = arena_make_array<TileStatus>(arena, capacity); 
 
 entitys = arena_make_array<Entity>(arena, capacity); 
 

}

// =========================
// GETTERS
// =========================

  inline Tiledata& tiledata(const EntityID index) {
return tiledatas[index];
  }
  inline Alt& altitude(const EntityID index) {
return altitudes[index];
  }
  inline Liquid& water(const EntityID index) {
return waters[index];
  }
  inline TileStatus& tile_status(const EntityID index) {
return tile_statuss[index];
  }
  inline Entity& entity(const EntityID index) {
return entitys[index];
  }


    

    


    // =========================
    // SERIALIZATION
    // =========================

  // genreal serialization

    template <class Archive>
    void save(Archive &archive) const
    {
    archive(capacity);
   

        tiledatas.save(archive);
        altitudes.save(archive);
        waters.save(archive);
        tile_statuss.save(archive);
        entitys.save(archive);
    }

    template <class Archive>
    void load(Archive &archive)
    {
        archive(capacity);
        
        tiledatas.load(archive);
        altitudes.load(archive);
        waters.load(archive);
        tile_statuss.load(archive);
        entitys.load(archive);
    }

// @codegen:end database_generation
	
	Coord get_nearest_empty_tile(Coord coord);
		Coord get_nearest_empty_tile_block(Coord coord, size_t length, size_t width = 1);
  inline size_t get_index(const Coord coord){return (coord.y * world.height_chunks) + (coord.x * world.length_chunks);}
		inline Coord get_coord(const size_t index){return {static_cast<uint32_t>(index % world.length_chunks) , static_cast<uint32_t>(index / world.height_chunks)};}
  inline Frame calc_inertia(const Coord coord, bool running);
		inline Frame calc_inertia(Frame entity_base_frames, const Coord coord);
};
}
