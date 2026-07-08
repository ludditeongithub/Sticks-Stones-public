#pragma once
#include "enum.hpp"
#include <core/data.hpp>
#include <core/tables.hpp>

inline constexpr LookupTable<Tile, Frame> tileMoveCost = []
{
	LookupTable<Tile, Frame> lt{};

	return lt;
}();


inline constexpr LookupTable<Tile ,float> tileFrameMultiplier = [] {
		LookupTable<Tile ,float> lt{};
		using enum Tile;
		
		return lt;
}();
