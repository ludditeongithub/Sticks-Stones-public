#include "world/animal/enum.hpp"
#include <core/containers.hpp>
#include <cstdint>
#include <queue>
#include <world/animal/database.hpp>
#include <world/animal/tables.hpp>
#include <world/chunk/data.hpp>
#include <world/unit/database.hpp>

// TODO: make certain tasks pausable and resumable, change to iterating over
// tasks per pawn rather than other way around (when pawns stats are
// implemented)-- timers will skip most pawns repeatedly, maybe need bool for
// whether job has just started
// only send alive and timer up units
void assignActions(std::priority_queue < std::pair < uint8_t, PlayerTaskJobData &pq,
		   Pool<float> &healths, Pool<uint16_t> &timers, Pool<Action> &actions,
		   Pool<Skills> &skills, Pool<ActionDecisionStatus> &actions)
{
	int i = 0;
	for (int i = 0; i < timers.size(); i++)
	{
		if (timers[i] > 0)
			continue;
		if (healths[i] <= 0.0)
		{
			actions[i] = Action::Dead;
			continue;
		}
		if (actions[i] == Action::Assign)
		{
			// get valid task for selected pawn
			bool v = false;
			PlayerTaskJobData td = pq.top();
			while (v == false)
			{
				Task t = td.task;
				uint32_t &a = td.amount;
				if (a <= 0)
					continue;
				for (int j = 0; j < rd[i].size(); j++)
				{
					// TODO: precompute all scores for all roles
					uint8_t ts =
					    getTaskScore(t, skills[i]); // returns 0 if invalid
					if (ts > taskData[t].skillReq)
					{
						tasks[i] = t;
						v = true;
						a -= getTaskMinimumOutput[t];
						timers[i] = getTaskTimer(task, skills[i]);
					}
					// TODO: set action
					break;
				}
				td = pq.next();
			}
		}
		if (!v)
			actions[i] = Action::Idle;
	}
}
}

// only for idle animals
void assignAnimalTasks(Array<Animal> &animals, Array<ActionDecisionStatus> &actions,
		       Array<Coord> &positions, Array<Hunger> hungers)
{
	using enum ActionDecisionStatus;
	for (int i = 0; i < animals.size; i++)
	{
		if (actions[i] == ActionDecisionStatus::Assign)
		{
			Animal a = animals[i];
			// assign hungry animals to hunt/search for food
			if (hungers[i] <= hungerSearchThreshold[a])
			{
				actions[i] = AnimalFoodSearch;
				continue;
				;
			}
			// TODO: assign thirsty animals to drink
			// assign animals that need to breed to find mate
			uint16_t seasonTime =
			    getSeasonTime(time, getChunkIndexFromTile(positions[i]));
			if (seasonTime <= breedingSeasonStart[a] &&
			    seasonTime >= breedingSeasonEnd[a])
			{
				actions[i] = AnimalBreedSearch;
			}
			else if (seasonTime <= migrationSeasonStart[a] &&
				 seasonTime >= breedingSeasonEnd[a])
				actions[i] = AnimalMigration;

			// TODO: special actions (migrate, search for pack, build
			// nests/structures, hoard)

			// else wander/TODO: follow pack
			actions[i] = AnimalRejoinPack;
		}
	}
}
