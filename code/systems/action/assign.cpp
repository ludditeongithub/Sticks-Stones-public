#include "actions.hpp"
#include "simulation/game_time.hpp"
#include "world/animal/database.hpp"
#include "world/unit/database.hpp"


// TODO: factor in hunger
// TODO: add to-do to go put away items to have necessary space for tools or
// items etc, when pawn goes to grab items
// may only be
template <typename DB>
ActionEventDispatchBuffer markActingEntities(std::vector<EntityID> &indices, DB& database)
{
		bool ifAnimals = typeof(database) == AnimalDatabase;
		ActionEventDispatchBuffer buffer = ActionEventDispatchBuffer(indices.size(), ifAnimals);
	
	for (int j = 0; j < indices.size(); j++)
			{
					EntityID i = indices[j];
					const Action action = database.action(i);
					if (action == Action::Idle || action == Action::Sleep) continue;
					if (action == Action::Prowl || action == Action::CheckProwl)
							buffer.checkNearTargets.push_back(i);
					if (action == Action::Wander) {						buffer.movingTiles.push_back(i);											
					} else if (action > Action::APPROACH_MIN && action < Action::APPROACH_MAX) {
						buffer.approachs.push_back(i);
					}
					else if (action > Action::UNIT_MIN &&
						 action < Action::UNIT_MAX)
							{
							#if !SHIPPING_BUILD

                            #endif
							buffer.units.push_back(i);	}       										    			 				// TODO: add more actions, breed
			}
	return buffer;
	}


// TODO: make certain tasks pausable and resumable, change to iterating over
// tasks per pawn rather than other way around (when pawns stats are
// implemented)-- timers will skip most pawns repeatedly, maybe need bool for
// whether job has just started
// only send alive and timer up units

void assignActions(std::vector<EntityID> &indices, std::priority_queue<std::pair<uint8_t, PlayerTaskJobData>> &pq, UnitDatabase& database)
{
		for (int i = 0; i < indices.size(); i++)
			{
			if (database.action(i) == Action::Assign) {
			// get valid task for selected pawn
			bool v = false;
			PlayerTaskJobData td = pq.top();
			while (v == false)
			{
				Task t = td.task;
				uint32_t &a = td.amount;
				if (a <= 0)
					continue;
				for (int j = 0; j < database.roleData(i).size(); j++)
				{
						Skills skill = database.skill(i);
					// TODO: precompute all scores for all roles
					uint8_t ts =
					    getTaskScore(t, skill); // returns 0 if invalid
					if (ts > taskData[t].skillReq)
					{
						database.task(i) = t;
						v = true;
						a -= getTaskMinimumOutput[t];
						inertia(i) = getTaskTimer(database.task(i), skill);
					}
					// TODO: set action
					break;
				}
				td = pq.next();
			}
		}
		if (!v)
			database.action(i) = Action::Idle;
	}
}

// only for idle animals
void assignAnimalTasks(Array<Animal> &animals, Array<ActionDecisionStatus> &actions,
		       Array<Coord> &positions, Array<Hunger> hungers)
{
	using enum ActionDecisionStatus;
	for (int i = 0; i < animals.size; i++)
	{
		if (actionDecisionStatus(i) == ActionDecisionStatus::Assign)
		{
			Animal a = animal(i);

			// assign hungry animals to hunt/search for food
			if (hunger(i) <= hungerSearchThreshold[a])
			{
				actionDecisionStatus(i) = AnimalFoodSearch;
				continue;
			}

			// TODO: assign thirsty animals to drink
			// assign animals that need to breed to find mate
			uint16_t seasonTime =
			    getSeasonTime(time, getChunkIndexFromTile(position(i)));

			if (seasonTime <= breedingSeasonStart[a] &&
			    seasonTime >= breedingSeasonEnd[a])
			{
				actionDecisionStatus(i) = AnimalBreedSearch;
			}
			else if (seasonTime <= migrationSeasonStart[a] &&
				 seasonTime >= breedingSeasonEnd[a])
			{
				actionDecisionStatus(i) = AnimalMigration;
			}

			// TODO: special actions (migrate, search for pack, build
			// nests/structures, hoard)

			// else wander/TODO: follow pack
			actionDecisionStatus(i) = AnimalRejoinPack;
		}
	}
}

void handleActionsAndMovement()
	{
		UnitDatabase& unitDatabase = g_Game->unitDatabase;
        Array<Time>& inertias = unitDatabase.inertias;
		std::vector<EntityID> readyActors = getReadyActors(inertias);
		ActionEventDispatchBuffer actionEventBuffer = markActingEntities(
		    readyActors, nullptr, unitDatabase.coords, unitDatabase.targets,
																		 unitDatabase.actions, unitDatabase.frameDatas);

		handleMovements();
	}

std::vector<EntityID> getReadyActors()
{
		size_t size = ;
		// OPTI
		std::vector<EntityID> buffer(size);
		for (size_t i = 0; i < size; i++)
			if (inertia(i)-- <= 0)
					{
							buffer.emplace_back(i);							
					}
		buffer.shrink_to_fit();
		return buffer;
}
