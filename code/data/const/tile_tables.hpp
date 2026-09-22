#pragma once
#include <data/types/tile.hpp>
#include <core/tables.hpp>

inline constexpr LookupTable<Tile, Frame> tile_move_cost = []
{
	LookupTable<Tile, Frame> lt{};

	return lt;
}();

inline constexpr LookupTable<Tile ,float> tile_frame_multiplier = [] {
		LookupTable<Tile ,float> lt{};
		using enum Tile;
		
		return lt;
}();
