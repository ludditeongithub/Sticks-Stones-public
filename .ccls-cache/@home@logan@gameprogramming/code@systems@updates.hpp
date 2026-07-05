// #include <sleef.h>
#include <world/plant/database.hpp>
#include <world/plant/tables.hpp>
#include <world/world.hpp>

// every 15 frames
void PlantDatabase::updatePlants(Array<Temp> &chunkTemps, Array2D<float> &dailyInsolations, Array<float> &cloudCovers);

// every tick, possibly change to just dispatching (no time check, no health check)
void updatePositions(PathsData &rpd, Array<Coord> &positions, Array<float> &timers,
		     Array<Action> &actions, Array<uint32_t> &requireNewPathIndices);
