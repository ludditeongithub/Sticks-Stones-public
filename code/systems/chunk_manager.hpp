#ifndef CHUNK_MANAGER_HPP
#define CHUNK_MANAGER_HPP
#include <core/containers.hpp>
#include <core/data.hpp>
#include <cstdint>

struct ChunkManager
{
	uint16_t count;
	Array<Temp> temperatures;
	Array<Hum> humidities;

	ChunkManager(uint16_t count) : count(count), temperatures(count), humidities(count) {}
	Temp getChunkTemperature(uint16_t index) { return temperatures[index]; }
};

#endif
