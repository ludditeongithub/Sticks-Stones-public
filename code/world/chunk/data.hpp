#include "world/world.hpp"
#include <cstdint>
#include <array>

constexpr uint16_t LATITUDE_TOTAL = 180;
const uint16_t LENGTH_CHUNKS = LATITUDE_TOTAL * 2;
const uint16_t HEIGHT_CHUNKS = LATITUDE_TOTAL * 2;
const uint16_t CHUNK_AMOUNT = LENGTH_CHUNKS * HEIGHT_CHUNKS;

constexpr int CHUNK_LENGTH = 64;
constexpr int CHUNK_SIZE = CHUNK_LENGTH * CHUNK_LENGTH;
const uint16_t CHUNK_LATITUDE_HEIGHT =
    HEIGHT_CHUNKS / LATITUDE_TOTAL; // amount of chunks per latitude

// time zones are in LST
const uint16_t TIME_ZONES = 24;

// Chunks hold array of tiles per chunk, as chunks can be turned on and off, and
// tiles should be processed contiguously.


inline Coord getChunkFromTile(Coord c) {
  return {c.x / CHUNK_LENGTH, c.y / CHUNK_LENGTH};
}

inline Coord getChunkFromIndex(uint32_t index) {
  return {index % CHUNK_LENGTH, index / CHUNK_LENGTH};
}  

inline uint16_t getChunkIndex(Coord c) { return c.x + c.y * c.y; }

inline uint16_t getChunkIndexFromTile(Coord c) { return getChunkIndex(getChunkFromTile(c)); }

inline uint16_t getChunkHeight(int i) { return i / HEIGHT_CHUNKS; }

inline uint16_t getChunkWidth(int i) {
  return i % HEIGHT_CHUNKS;
}

inline int16_t getChunkLatitude(int i) {
  return (getChunkHeight(i) / CHUNK_LATITUDE_HEIGHT) - (LATITUDE_TOTAL / 2);
}

inline int16_t getChunkTimeZone(int i) {
  return getChunkWidth(i) / TIME_ZONES;
}

std::array<float, TIME_ZONES> hourAngles{
    -180, -165, -150, -135, -120, -105, -90, -75,
    -60, -45, -30, -15, 0, 15, 30, 45,
    60, 75, 90, 105, 120, 135, 150, 165
};
