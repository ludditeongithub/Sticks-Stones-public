#pragma once
#include "dispatch.hpp"
#include <core/containers.hpp>
#include <core/data.hpp>
#include <systems/destinations.hpp>
#include <systems/pathfinding.hpp>
#include <world/animal/enum.hpp>
#include <world/unit/roles_and_actions.hpp>

// Dispatch relies on update_animal_tasks which gives all unassigned animals a target and
// update_positions, which gives animals who

struct AnimalDispatcher
{

	struct DispatchCollection
	{
		PathDispatchData new_path_dispatch;
		DispatchData assign_dispatch;
		DispatchData hungry_dispatch;
		DispatchData thirsty_dispatch;
		DispatchData breeding_dispatch;
		DispatchData rejoin_pack_dispatch;
		DispatchData migration_dispatch;
	};

	DispatchCollection get_dispatch_collection(Array<Animal> &animals, Array<Coord> &positions,
						 Array<Coord> &destinations,
						 Array<ActState> &actions)
	{
		BucketCounts bc = get_bucket_counts(actions);
		DispatchCollection dc;
		dc.new_path_dispatch = PathDispatchData(bc.new_path_count);
		dc.assign_dispatch = DispatchData(bc.assign_count);
		dc.hungry_dispatch = DispatchData(bc.hungry_count);
		dc.thirsty_dispatch = DispatchData(bc.thirsty_count);
		dc.breeding_dispatch = DispatchData(bc.breeding_count);
		dc.rejoin_pack_dispatch = DispatchData(bc.rejoin_pack_count);
		dc.migration_dispatch = DispatchData(bc.migration_count);

		uint16_t new_path_count;
		uint16_t assign_count;
		uint16_t hungry_count;
		uint16_t thirsty_count;
		uint16_t breeding_count;
		uint16_t rejoin_pack_count;
		uint16_t migration_count;
		for (uint16_t i = 0; i < animals.size(); i++)
		{
			switch (actions[i])
			{
			case ActState::Assign:
				dc.assign_dispatch.set_data(assign_count, i);
				break;
			case ActState::AnimalFoodSearch:
				dc.hungry_dispatch.set_data(hungry_count, i);
				break;
			case ActState::AnimalDrinkSearch:
				dc.thirsty_dispatch.set_data(thirsty_count, i);
				break;
			case ActState::AnimalBreedSearch:
				dc.breeding_dispatch.set_data(breeding_count, i);
				break;
			case ActState::AnimalMigration:
				dc.migration_dispatch.set_data(migration_count, i);
				break;
			case ActState::AnimalRejoinPack:
				dc.rejoin_pack_dispatch.set_data(rejoin_pack_count, i);
				break;
			default:
				// TODO: error
			}
		}
		return dc;
	}

	void dispatch_animals(Array<Animal> &animals, Array<Coord> &positions,
			     Array<Coord> &destinations, Array<ActState> &actions)
	{
		DispatchCollection dc =
		    get_dispatch_collection(animals, positions, destinations, actions);

		set_new_paths(dc.new_path_dispatch);
		set_hungry_destinations(dc.hungry_dispatch);
		set_thirsty_destinations(dc.thirsty_dispatch);
		set_migration_destinations(dc.migration_dispatch);
	}
}

