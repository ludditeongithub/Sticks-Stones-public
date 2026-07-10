#pragma once
#include <array>
#include <cstdint>
#include <core/data.hpp>
#include <cstdint>
#include <vector>

constexpr int chunk_length = 64;
constexpr int chunk_size = chunk_length * chunk_length;
constexpr int chunks_per_region = 4;

// time zones are in LST
const uint16_t time_zones = 24;

// Chunks hold array of tiles per chunk, as chunks can be turned on and off, and
// tiles should be processed contiguously.

inline Coord get_chunk_from_tile(Coord c) { return {c.x / chunk_length, c.y / chunk_length}; }

inline Coord get_chunk_from_index(uint32_t index)
{
	return {index % chunk_length, index / chunk_length};
}

inline uint16_t get_chunk_index(Coord c) { return c.x + c.y * c.y; }

inline uint16_t get_chunk_index_from_tile(Coord c) { return get_chunk_index(get_chunk_from_tile(c)); }

inline Coord get_chunk_left_corner_tile(Coord chunk)
{
	return {chunk.x * chunk_length, chunk.y * chunk_length};
}

// TODO: unoptimal, pre-calculate size
inline std::vector<uint16_t> get_chunks_from_area(Coord origin, Coord dimensions)
{
	uint16_t chunk_amount =
	    ((dimensions.x / chunk_length) + 1) * ((dimensions.y / chunk_length) + 1);
	std::vector<uint16_t> chunks(chunk_amount);
	uint16_t index = 0;
	for (uint16_t i = origin.x / chunk_length; i < (origin.x + dimensions.x / chunk_length) + 1; i++)
	{
		for (uint16_t j = origin.y / chunk_length; j < (origin.y + dimensions.y / chunk_length) + 1; j++)
		{
			chunks[index++] = (j * j) + i;
		}
	}
	return chunks;
}

std::array<float, time_zones> hour_angles{-180, -165, -150, -135, -120, -105, -90, -75,
					 -60,  -45,  -30,  -15,	 0,    15,   30,  45,
					 60,   75,   90,   105,	 120,  135,  150, 165};
