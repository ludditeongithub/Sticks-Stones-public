#pragma once

#include "world/buildable/enum.hpp"
#include "tables.hpp"
namespace buildable {

constexpr float INFANT_HEALTH_MODIFIER = 1.0;

constexpr uint8_t MAX_WORK_DIST = 4;

}
Health get_max_health(Buildable buildable, Time age)
{
		return buildable::MAX_HEALTHS[buildable];
}
