#pragma once
#include <cstdint>
#include <core/coord.hpp>
#include <optional>
#include <variant>
#include <data/const/chunk_data.hpp>
#include <data/types/animal.hpp>
#include <data/types/unit.hpp>
#include <data/types/plant.hpp>
#include <data/types/item.hpp>
#include <data/types/buildable.hpp>
// using Entity = PackedEnum4_32<Role, 8, Animal, 6, Plant, 6, Item, 10>;
enum class NullEntity : uint8_t {
Null
};

using Entity = std::variant<Unit, Animal, Plant, Item, Buildable, NullEntity>;

using EntityID = std::size_t;

struct EntitySearchData {
   size_t index;
   std::optional<Coord> position;
};
