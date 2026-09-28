#pragma once
#include "data/const/unit_data.hpp"
#include <cmath>
#include <core/random.hpp>
#include <data/run/world.hpp>
#include <data/types/unit.hpp>

inline float generate_skin_warmth(float parent1, float parent2)
{
	float crossed_value = std::lerp(parent1, parent2, 0.5);
	return std::lerp(crossed_value, random_chance->next(), 0.08);
}

inline float generate_skin_warmth(World &world, Coord coord)
{
  uint16_t chunk = get_chunk_index_from_tile(coord);
	uint16_t longitude = world.get_chunk_time_zone(chunk);
	return std::lerp(longitude, random_chance->next(), 0.3);
}

inline float generate_melanin(World& world, Coord coord) {
    uint16_t chunk = get_chunk_index_from_tile(coord);
	uint16_t latitude = world.get_chunk_time_zone(chunk);
	return std::lerp(latitude, random_chance->next(), 0.3);
}

inline float generate_melanin(float parent1, float parent2) {
        float crossed_value = std::lerp(parent1, parent2, 0.5);
	return std::lerp(crossed_value, random_chance->next(), 0.08);
}

inline UnitStage get_unit_stage(Time age)
{
	if (age < MATURITY_AGE) return UnitStage::Child;
	else if (age < ELDER_AGE)
			return UnitStage::Adult;
	else return UnitStage::Elder;
}
