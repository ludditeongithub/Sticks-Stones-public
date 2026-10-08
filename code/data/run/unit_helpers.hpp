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

inline float generate_skin_warmth(Coord coord)
{
  uint16_t chunk = tile_to_chunk_index(coord);
	uint16_t longitude = g_world->get_chunk_time_zone(chunk);
	return std::lerp(longitude, random_chance->next(), 0.3);
}

inline float generate_melanin(Coord coord) {
        uint16_t chunk = tile_to_chunk_index(coord);
	uint16_t latitude = g_world->get_chunk_time_zone(chunk);
	return std::lerp(latitude, random_chance->next(), 0.3);
}

inline float generate_melanin(float parent1, float parent2) {
        float crossed_value = std::lerp(parent1, parent2, 0.5);
	return std::lerp(crossed_value, random_chance->next(), 0.08);
}

namespace unit {
inline UnitStage get_stage(Time age)
{
	if (age < MATURITY_AGE) return UnitStage::Child;
	else if (age < ELDER_AGE)
			return UnitStage::Adult;
	else return UnitStage::Elder;
}

inline Health get_max_health(Unit unit, Time age)
{
	if (age < MATURITY_AGE)
			{
					float p = age / MATURITY_AGE;
					float mod = lerp(INFANT_HEALTH_MODIFIER, 1.0, p);
					return MAX_HEALTH * mod;
			} else if (age < ELDER_AGE)
			{
					return MAX_HEALTH;
					}
					else
							{
					float p = age / MATURITY_AGE;
					float mod = lerp(ELDER_HEALTH_MODIFIER, 1.0, p);
					return MAX_HEALTH * mod;									
							}
}
inline Hunger get_max_hunger(Unit unit, Time age)
{
	if (age < MATURITY_AGE)
			{
					float p = age / MATURITY_AGE;
					float mod = lerp(INFANT_HUNGER_MODIFIER, 1.0, p);
					return MAX_HUNGER * mod;
			} else if (age < ELDER_AGE)
			{
					return MAX_HUNGER;
					}
					else
							{
					float p = age / MATURITY_AGE;
					float mod = lerp(ELDER_HUNGER_MODIFIER, 1.0, p);
					return MAX_HUNGER * mod;									
							}
}
};
