#include <core/math.hpp>
#include "enum.hpp"
#include <array>
#include <math.h>
#include <cstdint>

// Constants
const uint16_t WIDTH_CHUNKS = 5000;
const uint16_t HEIGHT_CHUNKS = 5000;
const uint32_t CHUNK_AMOUNT = WIDTH_CHUNKS * HEIGHT_CHUNKS;

constexpr int CHUNK_LENGTH = 64;
constexpr int CHUNK_SIZE = CHUNK_LENGTH * CHUNK_LENGTH;
constexpr uint16_t SENTINEL = 65535;
constexpr uint16_t AVERAGE_MOVE_COST = 5;
constexpr uint16_t TILE_AMOUNT = CHUNK_AMOUNT * CHUNK_SIZE;

enum ChunkFlags : uint8_t {
  ACTIVE = 1 << 0,
  PLAYER = 1 << 1,
  BUSY = 1 << 2, 
};

struct Chunks {
  std::array<uint16_t, CHUNK_AMOUNT> gridX;
  std::array<uint16_t, CHUNK_AMOUNT> gridY;
  std::array<ChunkFlags, CHUNK_AMOUNT> flags;
};
  


inline constexpr LookupTable<Tile> tileMoveCost = [] {
  LookupTable<Tile> lt{};
  
  return lt;
 }();

struct Tiles {
  std::array<Tile, TILE_AMOUNT> tiles;
};


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

