#pragma once

#include "data/run/animal_database.hpp"
#include "data/run/plant_database.hpp"
#include "data/run/unit_database.hpp"
#include "logic/generic/movement/movement.hpp"
#include <logic/simulation/game.hpp>
#include <logic/gameplay/action/action.hpp>
void process_simulation(Time passed)
{
	unit::Database &ud = g_game->unit_database;
	plant::Database &pd = g_game->plant_database;
	animal::Database &ad = g_game->animal_database;

	//process_combat(chances, weapons, stats, positions, healths, targets, actions);
		
	process_actions();
	
	process_movement();

	mark_unassigned_and_no_inertia_entities(ud);
	assign_unassigned_units(ud);
	assign_tasks(ud.no_inertia_buffer, );

	mark_unassigned_and_no_inertia_entities(ad);
	// check if assigning unassigned animals is necessary
	assign_animal_tasks(ad.animals, ad.frame_datas, ad.coords, ad.hungers);
	
	pd.update_plants(*g_world, passed);
}

void on_player_order()
{
	// change this: does not need to be so hot
	update_task_job_priorities(hm, pq, pt);
}
