#pragma once

#include "game.hpp"
#include "world/world.hpp"

uint16_t Game::getDay() { return (absoluteTime % YEAR_LENGTH) / DAY_LENGTH; }
