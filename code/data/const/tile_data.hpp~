 #pragma once
#include "enum.hpp"
#include <world/world.hpp>
#include <cstdint>
#include <math.h>
#include <core/containers.hpp>
#include <core/tables.hpp>
#include <core/data.hpp>

constexpr uint16_t AVERAGE_MOVE_COST = 5;

inline uint32_t World::get_tile_index_from_coord(Coord c) { return (c.y * WORLD_TILE_LENGTH) + c.x; }

inline Coord World::get_tile_coord_from_index(uint32_t i) {
	return {i % WORLD_TILE_LENGTH, i / WORLD_TILE_LENGTH};
}

inline uint32_t World::get_tile_index_chunk_relative(uint32_t i) { return {i % CHUNK_SIZE}; }

inline uint32_t World::get_tile_index_chunk_relative(Coord c) {
	return {get_tile_index_from_coord(c) % CHUNK_SIZE};
}
