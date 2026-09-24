#include "world.hpp"


inline uint32_t World::get_tile_index_from_coord(Coord c) { return (c.y * world_tile_length) + c.x; }

inline Coord World::get_tile_coord_from_index(uint32_t i) {
	return {i % world_tile_length, i / world_tile_length};
}

inline uint32_t World::get_tile_index_chunk_relative(uint32_t i) { return {i % CHUNK_SIZE}; }

inline uint32_t World::get_tile_index_chunk_relative(Coord c) {
	return {get_tile_index_from_coord(c) % CHUNK_SIZE};
}
