#include "../include/basic.hpp"
#include "timers.cpp"
#include "../include/categories.hpp"
#include "../include/tile.hpp"
#include "../include/plant.hpp"
#include "../include/event.hpp"
#include "worldgen.cpp"
#include "pathfinding.cpp"
#include <variant>

/*  GUIDELINES FOR SPAWNING
 *   all natural entities must roughly spawn as often as they die in nature to ensure that they are not eliminated or grow too much as the game progresses.
 *
 *   ergo, the formula for annual plant spawning is to just have them spawn with the same formula they used before, since all of the annuals will die in the winter, so an equal chance amount of annuals should spawn next spring, as seeds.
 *
 *   perrenials or multi-year plants should spawn at a randomized growth amount. the formula for their respawns should be their total growth amount (period from ), divided by the respawn period, spread throughout every instance in which plants are able to spawn.
 *
 *   A determinstic plant score is given for each cell, which represents how well the plant grows in that area. This is so that it is generally always the most competitive plants which grow in an area, so that natural-looking clusters form.
 *   */

//TODO: have seed in seeds vector become none upon pick up or consuming animals or pawns

void spawnEnemies() {

}

void spawnDisasters() {

}
