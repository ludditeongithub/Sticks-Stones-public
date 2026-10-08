#pragma once
#include <cstdint>
#include <data/types/time.hpp>

constexpr uint16_t HOUR_LENGTH = 300;
constexpr uint16_t DAY_LENGTH = HOUR_LENGTH * 24;
constexpr uint16_t SEASON_LENGTH = DAY_LENGTH * 7;
constexpr uint16_t YEAR_LENGTH = (uint16_t)SEASON_LENGTH * (uint16_t)4;

constexpr Time CORPSE_ROT_TIME = DAY_LENGTH * 3;
constexpr Time TIME_PER_FRAME = HOUR_LENGTH / 360;
