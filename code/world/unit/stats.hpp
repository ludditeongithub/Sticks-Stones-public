#include "world/unit/database.hpp"
#include <basic/random.hpp>
#include <cstdint>
#include <array>

constexpr uint8_t STAT_MIN = 0;
constexpr uint8_t STAT_MAX = 100;
constexpr uint8_t INITIAL_STAT_MAX = 60;

// TODO: normal about a mean random
using Strength = uint8_t;
using Dexterity = uint8_t;
using Perception = uint8_t;

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

uint8_t humanSight;
uint16_t nearGatherRange = humanSight; // the farthest a pawn will  go to fetch an item
uint16_t midGatherRange = humanSight * 2;

// Fine means that only fine objects can be carried, mid means that loose, soft, or solid objects
// can be carried, single means that only single objects can be carried
enum class BulkStatus
{
	NONE,
	Fine,
	Mid,
	Single
};

float currentMaxBulk(BulkStatus bs, Strength str)
{
	int s = str.strength;
	switch (bs)
	{
	case BulkStatus::Fine:
		return FINE_BULK_MAX * s / STAT_MAX;
	case BulkStatus::Mid:
		return MID_BULK_MAX * s / STAT_MAX;
	case BulkStatus::Single:
		return SINGLE_BULK_MAX * s / STAT_MAX;
	}
	return 0.0;
}

float maxWeight(Strength str) { return str / STAT_MAX * MAX_CARRY; }

std::array<uint16_t, 10> sightRanges; // based on perception

inline uint16_t getSightRange(Perception perception) {
	return 10 + (perception / 3);
}


