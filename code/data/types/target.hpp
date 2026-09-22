#pragma once
#include <cstdint>

enum class TargetType : uint8_t
{
	NONE,
	Animal,
	Plant,
	Item,
	Unit,
	Tile,
	Buildable
};

struct Target
{
	TargetType type;
	std::size_t index;
};
