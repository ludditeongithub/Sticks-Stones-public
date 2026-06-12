#pragma once
#include "unit/enum.hpp"
#include <core/data.hpp>
#include <core/random.hpp>

namespace defaults
{

// ANIMATED ENTITIES
		
constexpr Target TARGET = Target{TargetType::NONE, std::numeric_limits<uint16_t>::max()};

inline FrameData FRAME_DATA() { return FrameData{ActState::NewPath, random_direction->next(), 0}; }

constexpr Hunger ANIMAL_INFANT_MAX = maxHungers[animal] * random_chance->next();		

// UNIT UNIQUES

constexpr uint8_t SKILL_MAX = 50;
constexpr uint8_t STARTING_SKILL_MAX = 25;		
		
constexpr RoleMana STARTING_ROLE_MANA = 10;
constexpr Health MAX_HEALTH = 100;
constexpr Health INFANT_STARTING_HEALTH_MAX = 50;
constexpr Health INFANT_STARTING_HEALTH_MIN = 38;
constexpr Hunger INFANT_HUNGER_MAX = 850;		

inline Health UNIT_HEALTH()
{
		return random_chance->next() *
        (INFANT_STARTING_HEALTH_MAX -
         INFANT_STARTING_HEALTH_MIN);
}
		
}
