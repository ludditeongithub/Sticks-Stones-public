#pragma once
#include "tables.hpp"
#include "world/animal/enum.hpp"
#include <core/data.hpp>
#include <core/random.hpp>
// ANIMAL UNIQUES

constexpr float INFANT_HUNGER_MODIFIER = 0.2;

constexpr float INFANT_HEALTH_MODIFIER = 0.2;

inline Time randomAge(Animal animal)
{
		return maxAges[animal] * random_chance->next();
}
