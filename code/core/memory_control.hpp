#include "memory.hpp"

// dynamic sized pools are divided into chunked databases, which are initialized as being a finite
// size, and linked together.
constexpr uint16_t animal_database_cap = 500;
constexpr uint16_t player_unit_database_cap =
    2000; // should be relatively small, as each faction may have their own.
constexpr uint16_t plant_database_cap = 4000; // attempt to allocate all that a world needs.

constexpr uint16_t npc_unit_database_cap = 40000;
