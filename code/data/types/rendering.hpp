#pragma once
#include <cstdint>
#include <core/coord.hpp>
#include <data/types/animal.hpp>
#include <data/types/plant.hpp>
#include <data/types/item.hpp>
#include <data/types/buildable.hpp>
#include <data/types/unit.hpp>
#include <data/const/chunk_data.hpp>
#include <data/types/action.hpp>

//TODO: ensure Frame can be properly packed
using FrameData = PackedEnum<Field<ActState, 2>, Field<Direction, 2>, Field<Frame, 12>>;

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

// this creates a buffer where the written positions are NOT relative to some camera view, but absolute in the world.
struct ChunkRenderBuffer
{
    size_t plant_amount;
    std::array<PlantRenderData, CHUNK_SIZE> plants; 
      size_t item_amount;
    std::array<ItemRenderData, CHUNK_SIZE> items;
    size_t buildable_amount;
    std::array<BuildableRenderData, CHUNK_SIZE> buildables;
};

struct MovablesRenderBuffer
{
      size_t animal_amount;
    std::array<AnimalRenderData, CHUNK_SIZE> animals;
      size_t unit_amount;
    std::array<UnitRenderData, CHUNK_SIZE> units;
};
