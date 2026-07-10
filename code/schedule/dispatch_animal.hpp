#pragma once
#include "dispatch.hpp"
#include <core/containers.hpp>
#include <core/data.hpp>
#include <systems/destinations.hpp>
#include <systems/pathfinding.hpp>
#include <world/animal/enum.hpp>
#include <world/unit/rolesAndActions.hpp>

// Dispatch relies on updateAnimalTasks which gives all unassigned animals a target and
// updatePositions, which gives animals who

struct AnimalDispatcher
{

	struct DispatchCollection
	{
		PathDispatchData newPathDispatch;
		DispatchData assignDispatch;
		DispatchData hungryDispatch;
		DispatchData thirstyDispatch;
		DispatchData breedingDispatch;
		DispatchData rejoinPackDispatch;
		DispatchData migrationDispatch;
	};

	DispatchCollection getDispatchCollection(Array<Animal> &animals, Array<Coord> &positions,
						 Array<Coord> &destinations,
						 Array<ActionDecisionStatus> &actions)
	{
		BucketCounts bc = getBucketCounts(actions);
		DispatchCollection dc;
		dc.newPathDispatch = PathDispatchData(bc.newPathCount);
		dc.assignDispatch = DispatchData(bc.assignCount);
		dc.hungryDispatch = DispatchData(bc.hungryCount);
		dc.thirstyDispatch = DispatchData(bc.thirstyCount);
		dc.breedingDispatch = DispatchData(bc.breedingCount);
		dc.rejoinPackDispatch = DispatchData(bc.rejoinPackCount);
		dc.migrationDispatch = DispatchData(bc.migrationCount);

		uint16_t newPathCount;
		uint16_t assignCount;
		uint16_t hungryCount;
		uint16_t thirstyCount;
		uint16_t breedingCount;
		uint16_t rejoinPackCount;
		uint16_t migrationCount;
		for (uint16_t i = 0; i < animals.size(); i++)
		{
			switch (actions[i])
			{
			case ActionDecisionStatus::Assign:
				dc.assignDispatch.setData(assignCount, i);
				break;
			case ActionDecisionStatus::AnimalFoodSearch:
				dc.hungryDispatch.setData(hungryCount, i);
				break;
			case ActionDecisionStatus::AnimalDrinkSearch:
				dc.thirstyDispatch.setData(thirstyCount, i);
				break;
			case ActionDecisionStatus::AnimalBreedSearch:
				dc.breedingDispatch.setData(breedingCount, i);
				break;
			case ActionDecisionStatus::AnimalMigration:
				dc.migrationDispatch.setData(migrationCount, i);
				break;
			case ActionDecisionStatus::AnimalRejoinPack:
				dc.rejoinPackDispatch.setData(rejoinPackCount, i);
				break;
			default:
				// TODO: error
			}
		}
		return dc;
	}

	void dispatchAnimals(Array<Animal> &animals, Array<Coord> &positions,
			     Array<Coord> &destinations, Array<ActionDecisionStatus> &actions)
	{
		DispatchCollection dc =
		    getDispatchCollection(animals, positions, destinations, actions);

		setNewPaths(dc.newPathDispatch);
		setHungryDestinations(dc.hungryDispatch);
		setThirstyDestinations(dc.thirstyDispatch);
		setMigrationDestinations(dc.migrationDispatch);
	}
}

