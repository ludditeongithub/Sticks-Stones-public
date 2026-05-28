#include "task_scheduing.hpp"
#include <systems/movement.hpp>

void tick()
{
	for (int i = 0; i < timers.size(); i++)
		timers[i]--;

	// these are hot loops, fix if necessary
	updatePositions(rpd, positions, timers, actions);
	animalActions();
	assignTasks(pq, timers, tasks, skills);
	assignAnimalTasks(animals, actions, positions, hungers);
	updateAttack(chances, weapons, stats, positions, healths, targets, actions);
	updatePlants(nextGrowth, plantList, coords, chunkTemps, tileWater, lastFullyWatered,
		     dailyInsolations, cloudCovers, dead);
}

void onPlayerOrder()
{
	// change this: does not need to be so hot
	updateTaskJobPriorities(hm, pq, pt);
}
