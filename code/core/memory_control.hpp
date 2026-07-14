#include "memory.hpp"

// dynamic sized pools are divided into chunked databases, which are initialized as being a finite
// size, and linked together.
constexpr uint16_t ANIMAL_DATABASE_CAP = 500;
constexpr uint16_t PLAYER_UNIT_DATABASE_CAP =
    2000; // should be relatively small, as each faction may have their own.
constexpr uint16_t PLANT_DATABASE_CAP = 4000; // attempt to allocate all that a world needs.

constexpr uint16_t NPC_UNIT_DATABASE_CAP = 40000;
