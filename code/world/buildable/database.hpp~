#pragma once
#include "enum.hpp"
#include "tables.hpp"
#include <macros/database.hpp>
#include <core/data.hpp>
#include <core/containers.hpp>

struct BuildableDatabase
{
#define BUILDABLE_RUNTIME_ARRAYS(X) \
  X(Buildable, buildables, buildable, buildable)		\
  X(Coord, coords, coord, coord)					\
  X(Health, healths, maxHealths[buildable], maxHealths[buildable])
  
#define BUILDABLE_STD_CONTAINERS(X) \

#define BUILDABLE_INDEPENDENT_MEMBERS(X) \

  DEFAULT_DATABASE_CREATION(Buildable, buildable, BUILDABLE);
};
