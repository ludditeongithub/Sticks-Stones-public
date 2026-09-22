#include "task_scheduing.hpp"
#include <systems/movement.hpp>

void tick()
{
	for (int i = 0; i < timers.size(); i++)
		timers[i]--;

	// these are hot loops, fix if necessary
	update_positions(rpd, positions, timers, actions);
	animal_actions();
	assign_tasks(pq, timers, tasks, skills);
	assign_animal_tasks(animals, actions, positions, hungers);
	update_attack(chances, weapons, stats, positions, healths, targets, actions);
	update_plants(next_growth, plant_list, coords, chunk_temps, tile_water, last_fully_watered,
		     daily_insolations, cloud_covers, dead);
}

void on_player_order()
{
	// change this: does not need to be so hot
	update_task_job_priorities(hm, pq, pt);
}
