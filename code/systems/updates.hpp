//#include <sleef.h>
#include <world/world.hpp>
#include <world/plant/tables.hpp>

// every 15 frames
void updatePlants(Arena<float>& nextGrowth, Array<Plant> &plantList, Array<Coord> &coords,
                  Array<float> &chunkTemps, Array<float>& tileWater,
                  Array<float>& lastFullyWatered,
                  Arena2D<float> &dailyInsolations, Arena<float> &cloudCovers,
                  Arena<bool>& dead);

// every tick, possibly change to just dispatching (no time check, no health check)
void updateTasks(std::priority_queue<std::pair<uint8_t, PlayerTaskJobData>>& pq, Pool<float>& healths,
                 Pool<uint16_t>& timers, Pool<Task>& tasks, Pool<Skills>& skills, Pool<Action>& actions);

// every 30 ticks
void updateAnimalTasks(Array<Animal>& animals, Array<Action>& actions, Array<Coord>& positions);

// every tick, possibly change to just dispatching (no time check, no health check)
void updatePositions(PathsData &rpd, Array<Coord>& positions,
                     Array<float>& timers, Array<Action>& actions,
                     Array<uint32_t>& requireNewPathIndices);


