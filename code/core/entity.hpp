#pragma once
#include <cstdint>
#include "data.hpp"
#include <optional>
#include <variant>
#include <world/chunk/data.hpp>
#include <world/animal/enum.hpp>
#include <world/unit/enum.hpp>
#include <world/plant/enum.hpp>
#include <world/item/enum.hpp>
#include <world/buildable/enum.hpp>
#include <world/unit/enum.hpp>


// using Entity = PackedEnum4_32<Role, 8, Animal, 6, Plant, 6, Item, 10>;

using Entity = std::variant<Role, Animal, Plant, Item, Buildable>;

struct OptionalEntitySearchData
{
	std::optional<size_t> index;
	Coord position;
};	

//TODO: make it possible for these to be variant or null
struct EntitySearchData {
   size_t index;
   Coord position;
};

struct AnimalRenderData {
  size_t index;
  Coord position;
  Animal animal;
};

struct PlantRenderData {
  size_t index;
  Coord position;
	Plant plant;
};

struct ItemRenderData {
  size_t index;
  Coord position;
  Item item;
};

struct BuildableRenderData {
	size_t index;
	Coord position;
	Buildable buildable;
};

struct UnitRenderData {
  size_t index;
  Coord position;
	Unit unit;
};

using EntityRenderData = std::variant<PlantRenderData, AnimalRenderData, UnitRenderData, BuildableRenderData, ItemRenderData>;

  struct EntityRenderBuffer {
    size_t plant_amount;
    std::array<PlantRenderData, chunk_size> plants;
    size_t animal_amount;
    std::array<AnimalRenderData, chunk_size> animals;
    size_t unit_amount;
    std::array<UnitRenderData, chunk_size> units;
    size_t item_amount;
    std::array<ItemRenderData, chunk_size> items;
    size_t buildable_amount;
    std::array<BuildableRenderData, chunk_size> buildables;
  };

