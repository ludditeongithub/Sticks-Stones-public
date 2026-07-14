#pragma once
#include "data.hpp"

Time current_time = 0;
constexpr Time HOUR_LENGTH = 300;
constexpr Time DAY_LENGTH = HOUR_LENGTH * 24;
constexpr Time SEASON_LENGTH = DAY_LENGTH * 7;
constexpr Time YEAR_LENGTH = SEASON_LENGTH * 4;
