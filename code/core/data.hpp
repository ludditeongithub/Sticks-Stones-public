#pragma once
#include <cstdint>
#include <cmath>

struct Coord {
  uint32_t x;
  uint32_t y;
};

bool adjacentCoords(Coord first, Coord second) {
  return (std::abs(static_cast<int>(first.x - second.x)) <= 1 && std::abs(static_cast<int>(first.y - second.y)) <= 1);
}

enum class Direction { North, South, East, West };

using Time = uint32_t;

// geography
using Hum = uint16_t;
using Temp = uint16_t;

// unit stats
using Health = float;
using Speed = float;
using Hunger = uint16_t;

enum class TargetType : uint8_t {
  NONE,
  Animal,
  Plant,
  Item,  
  Unit,
  Tile,
  Structure,
  Station
};

struct Target {
  TargetType type;
  uint32_t index;
};

