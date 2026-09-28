#pragma once
#include "data/types/stats.hpp"
#include <cstddef>
#include <cstdint>
#include <data/types/item.hpp>
#include <data/types/time.hpp>
#include <unordered_map>
#include <vector>
#include <data/types/container.hpp>

using OverflowHashMap = std::unordered_map<uint32_t, std::vector<HoldableSlot>>;
using OverflowContainerMap = std::unordered_map<uint16_t, std::vector<Container>>;

OverflowHashMap g_overflow_hash_map;
OverflowContainerMap g_overflow_container_map;

namespace unit
{
		constexpr float INFANT_HEALTH_MODIFIER = 0.2;
		constexpr float INFANT_HUNGER_MODIFIER = 0.2;
}

constexpr uint16_t UNIT_CAP = 1000;
constexpr size_t MATURITY_AGE = 16;
constexpr size_t ELDER_AGE = 62;

// the total volume of each bulk category hands can maximally carry.
// where 0.1 is 100mL
// NOTE: idea: consider doing left and right

// mas weights pawns can carry
constexpr uint16_t STARTING_SKILL_MAX = 15;
constexpr Health MAX_HEALTH = 1000;
constexpr Hunger MAX_HUNGER = 1000;
constexpr uint8_t STAT_MIN = 0;
constexpr uint8_t STAT_MAX = 100;
constexpr uint8_t INITIAL_STAT_MAX = 60;
constexpr uint8_t STARTING_ROLE_MANA = 10;

constexpr uint16_t MAX_ROLES_PER_TASK = 6;
constexpr uint16_t ACTION_TOOLS_AMOUNT = 100; // NOTE: likely wrong
constexpr uint16_t ACTION_MAX_REQUIREMENTS = 7; // NOTE: likely wrong
constexpr size_t MAX_ROLES = 6;

// the total volume of each bulk category hands can maximally carry.
// where 0.1 is 100mL
// NOTE: idea: consider doing left and right
constexpr float FINE_BULK_MAX = 0.3;
constexpr float LOOSE_BULK_MULT = 5.5; // multiplies mid bulk
constexpr float SOFT_BULK_MULT = 2.5;  // mulitiplies mid bulk
constexpr float SOLID_BULK_MULT = 1.0; // mulitiplies mid bulk
constexpr float MID_BULK_MAX = 35.0;
constexpr float SINGLE_BULK_MAX = 60.0;

// mas weights pawns can carry
constexpr float MAX_CARRY = 250.0;

constexpr uint8_t MAX_SIGHT = 100;
constexpr uint16_t NEAR_GATHER_RANGE = MAX_SIGHT; // the farthest a pawn will  go to fetch an item
constexpr uint16_t MID_GATHER_RANGE = MAX_SIGHT * 2;

float sunburn_level1_threshold = 0.3;
float sunburn_level2_threshold = 0.75;

// Fine means that only fine objects can be carried, mid means that loose, soft, or solid objects
// can be carried, single means that only single objects can be carried

constexpr Frame BASE_WALKING_FRAMES = 8;
constexpr Frame BASE_RUNNING_FRAMES = 8;
