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
	std::optional<uint16_t> index;
	Coord position;
};	

//TODO: make it possible for these to be variant or null
struct EntitySearchData {
   uint16_t index;
   Coord position;
};

struct AnimalRenderData {
  uint16_t index;
  Coord position;
  Animal animal;
};

struct PlantRenderData {
  uint16_t index;
  Coord position;
	Plant plant;
};

struct ItemRenderData {
  uint16_t index;
  Coord position;
  Item item;
};

struct BuildableRenderData {
	uint16_t index;
	Coord position;
	Buildable buildable;
};

struct UnitRenderData {
  uint16_t index;
  Coord position;
	Unit unit;
};

using EntityRenderData = std::variant<PlantRenderData, AnimalRenderData, UnitRenderData, BuildableRenderData, ItemRenderData>;

  struct EntityRenderBuffer {
    uint16_t plantAmount;
    std::array<PlantRenderData, CHUNK_SIZE> plants;
    uint16_t animalAmount;
    std::array<AnimalRenderData, CHUNK_SIZE> animals;
    uint16_t unitAmount;
    std::array<UnitRenderData, CHUNK_SIZE> units;
    uint16_t itemAmount;
    std::array<ItemRenderData, CHUNK_SIZE> items;
    uint16_t buildableAmount;
    std::array<BuildableRenderData, CHUNK_SIZE> buildables;
  };

