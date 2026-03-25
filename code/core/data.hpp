#pragma once
#include <cmath>
#include <cstdint>

struct Coord
{
	uint32_t x;
	uint32_t y;
};

struct SCoord
{
	int x;
	int y;
};

bool adjacentCoords(Coord first, Coord second)
{
	return (std::abs(static_cast<int>(first.x - second.x)) <= 1 &&
		std::abs(static_cast<int>(first.y - second.y)) <= 1);
}

enum class Direction : uint8_t
{
	North = 0,
	South = 1,
	East = 2,
	West = 3
};

using Time = uint32_t;
using Frame = uint8_t;

// geography
using Hum = uint16_t;
using Temp = uint16_t;
using Alt = uint8_t;

// unit stats
using Health = float;
using Speed = float;
using Hunger = uint16_t;
using Sex = bool;

enum class TargetType : uint8_t
{
	NONE,
	Animal,
	Plant,
	Item,
	Unit,
	Tile,
	Structure,
	Station
};

struct Target
{
	TargetType type;
	uint32_t index;
};
