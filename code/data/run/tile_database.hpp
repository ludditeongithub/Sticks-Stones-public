#pragma once
#include <data/types/tile.hpp>
#include "data/const/chunk_data.hpp"
#include "data/const/tile_data.hpp"
#include <data/types/entity.hpp>
#include <vector>
#include <logic/simulation/world_gen.hpp>
#include <data/run/world.hpp>

namespace tile {
// TODO: whenever a tile is interacted with, notify all 
// TODO: enforce occupied on other databses
class Database
{
  	// @codegen:begin database_generation
public:
// =========================
// BASE DATABASE MEMBERS
// =========================

constexpr static uint16_t ENTITY_SIZE = sizeof(TileData) +
  
 +  sizeof(TileData) 
 +  sizeof(Alt) 
 +  sizeof(Liquid) 
 +  sizeof(TileStatus) 
 +  sizeof(Entity) 
;

size_t capacity;

    // =========================
    // ENTITY-SPECIFIC MEMBERS
    // =========================
    Array<TileData> tileDatas;
    Array<Alt> altitudes;
    Array<Liquid> waters;
    Array<TileStatus> tile_statuss;
    Array<Entity> entitys;



// =========================
// CONSTRUCTOR
// =========================

  Database(Arena* arena, size_t capacity
) 
  
{
this->capacity = capacity;

 
  tileDatas = arena_make_array<TileData>(arena, capacity);
 
  altitudes = arena_make_array<Alt>(arena, capacity);
 
  waters = arena_make_array<Liquid>(arena, capacity);
 
  tile_statuss = arena_make_array<TileStatus>(arena, capacity);
 
  entitys = arena_make_array<Entity>(arena, capacity);
 

}
    // =========================
    // SERIALIZATION
    // =========================

      template <class Archive>
    void serialize(Archive &archive) const
  {
         archive(tileDatas,
altitudes,
waters,
tile_statuss,
entitys);
    }


// =========================
// GETTERS
// =========================

  inline TileData& tileData(const EntityID index) {
return tileDatas[index];
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


    

    


// @codegen:end database_generation
	
	Coord get_nearest_empty_tile(Coord coord, Adjacency adjacency = Adjacency::Any);
    Coord get_nearest_empty_tile_block(Coord coord, size_t length, size_t width = 1);
  size_t get_index(const Coord coord){return (coord.y * g_world->height_chunks) + (coord.x * g_world->length_chunks);}
	Coord get_coord(const size_t index){return Coord({static_cast<uint32_t>(index % g_world->length_chunks), static_cast<uint32_t>(index / g_world->height_chunks)});}
  Frame calc_inertia(const Coord coord, bool running);
   Frame calc_inertia(Frame entity_base_frames, const Coord coord);
};
}
