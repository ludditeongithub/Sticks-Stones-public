#pragma once
#include "animal_tables.hpp"
#include "data/types/animal.hpp"

#include <core/random.hpp>
// ANIMAL UNIQUES

namespace animal {
constexpr float INFANT_HUNGER_MODIFIER = 0.2;

constexpr float INFANT_HEALTH_MODIFIER = 0.2;

inline Time random_age(Animal animal) { return animal::MAX_AGES[animal] * random_chance->next(); }

inline Health get_max_health(Animal animal, Time age)
{
	return animal::MAX_HEALTHS[animal] * (age / animal::FERTILITY_AGES[animal]);
}

inline Hunger get_max_hunger(Animal animal, Time age)
{
	return animal::MAX_HUNGERS[animal] * (age / animal::FERTILITY_AGES[animal]);
}

inline float get_conception_roll()
{

}
}
