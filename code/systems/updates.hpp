// #include <sleef.h>
#include <world/plant/tables.hpp>
#include <world/world.hpp>

struct Animal
{
};

// every 15 frames
void updatePlants(Arena<float> &nextGrowth, Array<Plant> &plantList, Array<Coord> &coords,
		  Array<float> &chunkTemps, Array<float> &tileWater, Array<float> &lastFullyWatered,
		  Arena2D<float> &dailyInsolations, Arena<float> &cloudCovers, Arena<bool> &dead);

// every tick, possibly change to just dispatching (no time check, no health check)
void updatePositions(PathsData &rpd, Array<Coord> &positions, Array<float> &timers,
		     Array<Action> &actions, Array<uint32_t> &requireNewPathIndices);
