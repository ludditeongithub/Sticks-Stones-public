#pragma once
#include <cstdint>
#include <data/types/aliases.hpp>
#include <data/types/buildable.hpp>
#include <data/const/buildable_tables.hpp>

namespace buildable {
constexpr float INFANT_HEALTH_MODIFIER = 1.0;

constexpr uint8_t MAX_WORK_DIST = 4;

Health get_max_health(Buildable buildable, Time age) { return MAX_HEALTHS[buildable]; }
}
