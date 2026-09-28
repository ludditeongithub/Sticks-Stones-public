#pragma once
#include <data/types/tile.hpp>
#include <core/tables.hpp>

inline constexpr LookupTable<Tile, Frame> TILE_MOVE_COST = []
{
	LookupTable<Tile, Frame> lt{};

	return lt;
}();

inline constexpr LookupTable<Tile ,float> TILE_FRAME_MULTIPLIER = [] {
		LookupTable<Tile ,float> lt{};
		using enum Tile;
		
		return lt;
}();
