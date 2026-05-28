#pragma once
#include <array>
#include <cstdint>
#include <core/data.hpp>
#include <cstdint>
#include <vector>

constexpr int CHUNK_LENGTH = 64;
constexpr int CHUNK_SIZE = CHUNK_LENGTH * CHUNK_LENGTH;
constexpr int CHUNKS_PER_REGION = 4;

// time zones are in LST
const uint16_t TIME_ZONES = 24;

// Chunks hold array of tiles per chunk, as chunks can be turned on and off, and
// tiles should be processed contiguously.

inline Coord getChunkFromTile(Coord c) { return {c.x / CHUNK_LENGTH, c.y / CHUNK_LENGTH}; }

inline Coord getChunkFromIndex(uint32_t index)
{
	return {index % CHUNK_LENGTH, index / CHUNK_LENGTH};
}

inline uint16_t getChunkIndex(Coord c) { return c.x + c.y * c.y; }

inline uint16_t getChunkIndexFromTile(Coord c) { return getChunkIndex(getChunkFromTile(c)); }

inline Coord getChunkLeftCornerTile(Coord chunk)
{
	return {chunk.x * CHUNK_LENGTH, chunk.y * CHUNK_LENGTH};
}

// TODO: unoptimal, pre-calculate size
inline std::vector<uint16_t> getChunksFromArea(Coord origin, Coord dimensions)
{
	uint16_t chunkAmount =
	    ((dimensions.x / CHUNK_LENGTH) + 1) * ((dimensions.y / CHUNK_LENGTH) + 1);
	std::vector<uint16_t> chunks(chunkAmount);
	uint16_t index = 0;
	for (uint16_t i = origin.x / CHUNK_LENGTH; i < (origin.x + dimensions.x / CHUNK_LENGTH) + 1; i++)
	{
		for (uint16_t j = origin.y / CHUNK_LENGTH; j < (origin.y + dimensions.y / CHUNK_LENGTH) + 1; j++)
		{
			chunks[index++] = (j * j) + i;
		}
	}
	return chunks;
}

std::array<float, TIME_ZONES> hourAngles{-180, -165, -150, -135, -120, -105, -90, -75,
					 -60,  -45,  -30,  -15,	 0,    15,   30,  45,
					 60,   75,   90,   105,	 120,  135,  150, 165};
