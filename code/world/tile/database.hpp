#pragma once
#include "enum.hpp"
#include "data.hpp"
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
	static constexpr uint32_t ENTITY_SIZE = sizeof(TileData) + sizeof(Alt);
	uint32_t size;
	Array<TileData> tiles;
	Array<Alt> altitudes;
	Array<Liquid> waters;
        Array<TileStatus> tileStatuses;

	World& world;

	Coord totalRevealedBoxTopLeftCorner;
	Coord totalRevealedBoxDimensions;
	Arena* edgeBufferArena = new Arena(1500 * sizeof(Coord));
	Array<Coord> edgeBuffer = arena_make_array<Coord>(edgeBufferArena, 1500);

  
  	// @codegen:begin database_generation

    // =========================
    // BASE DATABASE MEMBERS
    // =========================

size_t capacity;
Array<Tile> tiles;




    // =========================
    // ENTITY-SPECIFIC MEMBERS
    // =========================
    

    

    


      
    // =========================
    // SERIALIZATION
    // =========================

    template <class Archive>
    void save(Archive &archive) const
    {
    archive(capacity);
   


    }

    template <class Archive>
    void load(Archive &archive)
    {
        archive(capacity);

        

    }

    // =========================
    // CONSTRUCTOR
    // =========================

TileDatabase(Arena *arena, size_t capacity

  World& world,


)
    {
this->capacity = capacity;
        
    }

// @codegen:end database_generation
	
	Coord getNearestEmptyTile(Coord coord);
	
};
