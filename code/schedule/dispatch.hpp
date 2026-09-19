#pragma once
#include <core/containers.hpp>
#include <core/coord.hpp>
#include <cstdint>
#include <world/animal/enum.hpp>

struct DispatchData
{
	Array<uint16_t> indices;
	Array<Animal> animals;
	Array<Coord> positions;
	Array<Coord> destinations;

	DispatchData(uint16_t count)
	{
		indices = Array<uint16_t>(count);
		animals = Array<Animal>(count);
		positions = Array<Coord>(count);
		destinations = Array<Coord>(count);
	}

	inline void set_data(uint16_t j, uint16_t i)
	{
		indices[j] = i;
		animals[j] = animals[i];
		positions[j] = positions[i];
		destinations[j] = destinations[i];
	}
};

struct PathDispatchData
{
	Array<uint16_t> indices;
	Array<Coord> positions;
	Array<Coord> destinations;

	PathDispatchData(uint16_t count)
	{
		indices = Array<uint16_t>(count);
		positions = Array<Coord>(count);
		destinations = Array<Coord>(count);
	}

	inline void set_data(uint16_t j, uint16_t i)
	{
		indices[j] = i;
		positions[j] = positions[i];
		destinations[j] = destinations[i];
	}
};
