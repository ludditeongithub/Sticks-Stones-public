#include "task_scheduing.hpp"
#include <systems/movement.hpp>



void tick() {
  for (int i = 0; i < timers.size(); i++) timers[i]--;

  //these are hot loops, fix if necessary
  updatePositions(rpd, positions, timers, actions);
  updateTasks(pq, timers, tasks, skills);
  updateAnimalTasks();
  updateAttack(chances, weapons, stats, positions, healths, targets, actions);
  updatePlants(nextGrowth, plantList, coords, chunkTemps, tileWater, lastFullyWatered, dailyInsolations, cloudCovers, dead);
}

void onPlayerOrder() {
  //change this: does not need to be so hot
    updateTaskJobPriorities(hm, pq, pt);
}
