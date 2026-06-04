#pragma once
#include <stack>
#include <cstdint>
#include <core/containers.hpp>
#include "enum.hpp"
#include <core/data.hpp>

struct SeedDatabase {
	std::stack<uint16_t> nextSeedIndex;
	int seedSize = 0;
	Array<Plant> seeds;
	Array<Coord> seedCoords;

	SeedDatabase
};
