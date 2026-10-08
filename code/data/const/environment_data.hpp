#pragma once
#include <data/const/time_data.hpp>

constexpr float MAX_CLOUD_FACTOR = 3.2;

constexpr uint8_t MAX_ALTITUDE = 120;	     // TODO: check
constexpr uint8_t MAX_HUMIDITY = 120;	     // TODO: check
constexpr uint8_t MAX_OCEAN_AFFECT_DIST = 4; // TODO: check

constexpr float WINTER_SOLSTICE = SEASON_LENGTH / 2;
constexpr float SPRING_EQUINOX = SEASON_LENGTH / 2 + SEASON_LENGTH;
constexpr float SUMMER_SOLSTICE = SEASON_LENGTH / 2 + SEASON_LENGTH * 2;
constexpr float FALL_EQUINOX = SEASON_LENGTH / 2 + SEASON_LENGTH * 3;

constexpr float SPRING_MULT = 1.10;
constexpr float AUTUMN_MULT = 0.98;
constexpr float SUMMER_MULT = 1.45;
constexpr float WINTER_MULT = 0.74;

// temp range between -70 C to 57 C, -70 = 0, 57 = 127
constexpr float TEMP_OFFSET = 70;

// diurnal temperature variation influenced mostly by aridity, then latitude, then proximity to
// large water bodies
constexpr float MAX_DIURNAL_VAR = 20.2;

// seasonal temperature variation influenced mostly by latitude, then proximity to large water
// bodies, then elevation
constexpr float MAX_SEASONAL_VAR = 42.1;
