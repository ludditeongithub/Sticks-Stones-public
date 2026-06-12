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
	std::vector<bool> occupieds;
	Array<VisionStatus> visionStatuses;

	World *world;

	Coord totalRevealedBoxTopLeftCorner;
	Coord totalRevealedBoxDimensions;
	Arena* edgeBufferArena = new Arena(1500 * sizeof(Coord));
	Array<Coord> edgeBuffer = arena_make_array<Coord>(edgeBufferArena, 1500);

		TileDatabase(Arena *arena, TileSpawnBuffer &tsb, World *world);

	
		
	Coord getNearestEmptyTile(Coord coord);
	
};
