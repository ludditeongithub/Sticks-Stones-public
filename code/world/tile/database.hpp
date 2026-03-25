#pragma once
#include "enum.hpp"
#include <core/containers.hpp>
#include <core/data.hpp>
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
	std::vector<bool> occupieds;

	TileDatabase(Arena *arena, TileSpawnBuffer &tsb, World &w)
	{
		tiles = arena_make_array<TileData>(arena, w.WORLD_TILE_AMOUNT);
		altitudes = arena_make_array<Alt>(arena, w.WORLD_TILE_AMOUNT);
		occupieds = std::vector<bool>(w.WORLD_TILE_AMOUNT);

		for (uint32_t i = 0; i < w.WORLD_TILE_AMOUNT; i++)
		{
			TileData &td = tiles[i];
			tiles[i].first() = tsb.tiles[i];
			tiles[i].second() = tsb.grass[i];
			altitudes[i] = tsb.altitudes[i];
		}
	}
};
