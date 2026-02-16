#pragma once
#include <core/data.hpp>
#include <core/math.hpp>
#include <core/containers.hpp>
#include "enum.hpp"
#include "world/world.hpp"
#include <array>
#include <math.h>
#include <cstdint>

// Constants
constexpr uint16_t AVERAGE_MOVE_COST = 5;
constexpr uint16_t TILE_AMOUNT = CHUNK_AMOUNT * CHUNK_SIZE;
constexpr uint16_t TILE_WIDTH = sqrt(TILE_AMOUNT);

size_t getTileIndexFromCoord(Coord c) {
  return (c.y * CHUNK_LENGTH) + c.x;
}

Coord getTileCoordFromIndex(size_t i) {
  return {i % TILE_WIDTH, i / TILE_WIDTH};
}

size_t getTileIndexChunkRelative(size_t i) {
  return {i % CHUNK_SIZE};
}

size_t getTileIndexChunkRelative(Coord c) {
  return {getTileIndexFromCoord(c) % CHUNK_SIZE};
}

inline constexpr LookupTable<Tile, time> tileMoveCost = [] {
  LookupTable<Tile, time> lt{};
  
  return lt;
 }();


  std::array<uint16_t, 4> getNeighbors(uint16_t i) {
  std::array<uint16_t, 4> a;
  int x = i % CHUNK_SIZE;
  int y = y / CHUNK_SIZE;  
    // NORTH
  y > 0 ? a[0] = getIndex(x, y - 1) : a[0] = SENTINEL;
  // EAST
  x < CHUNK_SIZE - 1 ? a[1] = getIndex(x + 1, y) : a[1] = SENTINEL;
  // SOUTH
   y < CHUNK_SIZE - 1 ? a[2] = getIndex(x, y + 1) : a[2] = SENTINEL; 
    // WEST
    x > 0 ? a[3] = getIndex(x - 1, y) : a[3] = SENTINEL;
  return 
};

