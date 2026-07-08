#pragma once

#include "world/buildable/enum.hpp"
#include "tables.hpp"
constexpr float INFANT_HEALTH_MODIFIER = 1.0;

Health getMaxHealth(Buildable buildable, Time age)
{
		return buildable::maxHealths[buildable];
}
