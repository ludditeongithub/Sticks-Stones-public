#pragma once
#include "data.hpp"

Time current_time = 0;
constexpr Time hour_length = 300;
constexpr Time day_length = hour_length * 24;
constexpr Time season_length = day_length * 7;
constexpr Time year_length = season_length * 4;
