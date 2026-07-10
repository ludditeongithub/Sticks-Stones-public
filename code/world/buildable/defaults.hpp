#pragma once

#include "world/buildable/enum.hpp"
#include "tables.hpp"
constexpr float infant_health_modifier = 1.0;

Health get_max_health(Buildable buildable, Time age)
{
		return buildable::maxHealths[buildable];
}
