#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <stdint.h>

namespace regrowth
{
struct Age
{
	uint32_t age;
};

struct YieldMisses
{
	uint16_t yieldMisses;
};
struct CollectedWater
{
	float collectedWater;
};
// TODO: check on this, perhaps combine with above into water data.
struct LastFullyWatered
{
	float lastFullyWatered;
};

struct Position
{
	int x;
	int y;
};

struct Regrowth
{
	uint16_t regrowth;
};

struct Produce
{
	uint16_t produce;
};

struct FullyGrownCount
{
	uint16_t count;
};

} // namespace regrowth

#endif
