// Stores hot arrays of sprite data (positions, sizes, colors, texture IDs), handles batching logic
#pragma once
#include <world/item/enum.hpp>
#include <world/buildable/enum.hpp>
#include <world/animal/enum.hpp>
#include <world/plant/enum.hpp>
#include <world/unit/enum.hpp>
#include <world/tile/enum.hpp>
#include <core/data.hpp>
#include <variant>
#include <ui/components/button.hpp>

using Sprite = std::variant<Item, Buildable, Animal, Plant, Tile, Unit, Grass, Button>;

struct SpriteData
{
    Sprite sprite;
    SCoord position;
    SCoord dimensions;
};
