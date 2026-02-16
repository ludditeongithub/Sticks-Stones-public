#pragma once
#include <cstdint>
#include "data.hpp"
#include <core/packed_enum.hpp>
#include <core/containers.hpp>
#include <world/animal/enum.hpp>
#include <world/unit/enum.hpp>
#include <world/plant/enum.hpp>
#include <world/item/enum.hpp>


using Entity = PackedEnum4_32<Role, 8, Animal, 6, Plant, 6, Item, 10>;

struct EntitySearchData {
  size_t index;
  Coord position;
};
