 #pragma once
#include "enum.hpp"
#include <world/world.hpp>
#include <cstdint>
#include <math.h>
#include <core/containers.hpp>
#include <core/tables.hpp>
#include <core/data.hpp>

constexpr uint16_t average_move_cost = 5;

inline uint32_t World::getTileIndexFromCoord(Coord c) { return (c.y * WORLD_TILE_LENGTH) + c.x; }

inline Coord World::getTileCoordFromIndex(uint32_t i) {
	return {i % WORLD_TILE_LENGTH, i / WORLD_TILE_LENGTH};
}

inline uint32_t World::getTileIndexChunkRelative(uint32_t i) { return {i % CHUNK_SIZE}; }

inline uint32_t World::getTileIndexChunkRelative(Coord c) {
	return {getTileIndexFromCoord(c) % CHUNK_SIZE};
}
