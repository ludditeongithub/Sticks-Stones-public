#pragma once

#include "game.hpp"
#include "world/world.hpp"

namespace game {

  inline uint16_t getDay() { return (absoluteTime % YEAR_LENGTH) / DAY_LENGTH; }
  inline Time currentTimeAdjYear() { return absoluteTime % YEAR_lENGTH; }

}
