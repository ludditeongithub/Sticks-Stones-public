#include "world.hpp"
#include <logic/simulation/world_gen.hpp>

void World::load_chunk_data(WorldSpawner &ws)
	{
		ws.move_regions_to_chunks(humidities, temperatures, altitudes);
	}

Coord World::get_random_player_start()
	{	return{ static_cast<uint32_t>(random_chance->next() * coord::length_chunks) , static_cast<uint32_t>(random_chance->next() * coord::height_chunks)};
	}

uint32_t World::get_tile_index_from_coord(Coord c) { return (c.y * world_tile_length) + c.x; }

Coord World::get_tile_coord_from_index(uint32_t i) {
	return {i % world_tile_length, i / world_tile_length};
}

uint32_t World::get_tile_index_chunk_relative(uint32_t i) { return {i % CHUNK_SIZE}; }

uint32_t World::get_tile_index_chunk_relative(Coord c) {
	return {get_tile_index_from_coord(c) % CHUNK_SIZE};
}
