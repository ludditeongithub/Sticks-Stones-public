 #pragma once
#include <data/run/world.hpp>
#include <data/const/chunk_data.hpp>
#include <cstdint>
#include <math.h>
#include <core/containers.hpp>
#include <core/tables.hpp>
#include <data/types/aliases.hpp>

constexpr uint16_t AVERAGE_MOVE_COST = 5;

inline uint32_t World::get_tile_index_from_coord(Coord c) { return (c.y * world_tile_length) + c.x; }

inline Coord World::get_tile_coord_from_index(uint32_t i) {
	return {i % world_tile_length, i / world_tile_length};
}

inline uint32_t World::get_tile_index_chunk_relative(uint32_t i) { return {i % CHUNK_SIZE}; }

inline uint32_t World::get_tile_index_chunk_relative(Coord c) {
	return {get_tile_index_from_coord(c) % CHUNK_SIZE};
}
