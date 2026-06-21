#pragma once
#include <core/containers.hpp>
#include "enum.hpp"
#include "macros/database.hpp"
#include <core/data.hpp>

struct SeedDatabase {
#define SEED_INDEPENDENT_MEMBERS(X)

#define SEED_STD_CONTAINERS(X)
		
#define SEED_RUNTIME_ARRAYS(X) \
X(Plant, seeds, plant, plant) \
X(Coord, coords, coord, coord) \
X(Time, ages)

DEFAULT_DATABASE_CREATION(Seed, seed, SEED);	
};
