#pragma once
#include "tables.hpp"
#include "world/animal/enum.hpp"
#include <core/data.hpp>
#include <core/random.hpp>
// ANIMAL UNIQUES

constexpr float infant_hunger_modifier = 0.2;

constexpr float infant_health_modifier = 0.2;

inline Time random_age(Animal animal) { return animal::maxAges[animal] * random_chance->next(); }

inline Health get_max_health(Animal animal, Time age)
{
	return animal::maxHealths[animal] * (age / animal::fertilityAges[animal]);
}

inline Hunger get_max_hunger(Animal animal, Time age)
{
	return animal::maxHungers[animal] * (age / animal::fertilityAges[animal]);
}

inline float get_conception_roll()
{

}
