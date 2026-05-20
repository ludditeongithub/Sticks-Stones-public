#pragma once
#include "enum.hpp"
#include "world/chunk/data.hpp"
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
	Array<TileData> tiles;
	Array<Alt> altitudes;
	Array<Liquid> waters;
	std::vector<bool> occupieds;
	World *world;

	TileDatabase(Arena *arena, TileSpawnBuffer &tsb, World *world);

	Coord getNearestEmptyTile(Coord coord);	
};
