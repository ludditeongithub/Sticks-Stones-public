#include "actions.hpp"
#include "simulation/game_time.hpp"
#include "world/action/enum.hpp"
#include "world/animal/database.hpp"
#include "world/unit/database.hpp"
#include "world/unit/roles_commodities.hpp"


// TODO: factor in hunger
// TODO: add to-do to go put away items to have necessary space for tools or
// items etc, when pawn goes to grab items
// may only be
template <typename DB>
ActionEventDispatchBuffer mark_acting_entities(std::vector<EntityID> &indices, DB& database)
{
		bool if_animals = typeof(database) == AnimalDatabase;
		ActionEventDispatchBuffer buffer = ActionEventDispatchBuffer(indices.size(), if_animals);
	
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

inline Role get_valid_action_role(UnitDatabase& database, size_t i, Commodity c)
{
	Skills skill = database.skill(i);
	Commodity& commodity = database.commoditys(i);
	for (int j = 0; j < database.roleData(i).size(); j++)
			{
			const Role& role = roleData(i)[j];
			auto &commodity_list = rolesToCommodities[role];
					for (auto x: commodityList) {					
					// TODO: precompute all scores for all roles
					uint8_t cs =
					    getCommodityScore(x, skill); // returns 0 if invalid
					if (cs > commodityData[x].skillReq)
					{
						
						commodity = c;																	
						return role;
					}
					}
		 }
					// TODO: set action
		 return Role::NONE;
	}

inline void start_timed_task(Time& inertia, const Task task, const Skills& skill)
{
	inertia = getTaskTimer(task, skill);
}

void assign_action(Role role, Action action)
{
		ActionClass action_class = getActionClass(action);		
		switch (action_class) {
		case ActionClass::Resource:
       			attemptResourceAssignment();
       			break;
		case ActionClass::Product:
       			attemptProductsAssignment();
				break;
		case ActionClass::Support:
       			
       			break;
		case ActionClass::Researcher:
       			
				break;
		default:
				
		}
}

void assign_task(Commodity commodity, size_t amount, Role role, Action action)
{
		ActionClass action_class = getActionClass(action);
		switch (action_class) {
		case ActionClass::Resource:
       			
       			break;
		case ActionClass::Production:
       			
				break;
		case ActionClass:::
       			
       			break;
		case case-4:
       			
				break;
		default:
				
		}

}

// TODO: make certain tasks pausable and resumable, change to iterating over
// tasks per pawn rather than other way around (when pawns stats are
// implemented)-- timers will skip most pawns repeatedly, maybe need bool for
// whether job has just started
// only send alive and timer up units
void assign_actions(std::vector<EntityID> &indices, PriorityQueue<PlayerTaskJobData> &pq, UnitDatabase& database)
{
		if (pq.empty()) return;
		for (int i = 0; i < indices.size(); i++)
		{						
			if (database.action(i) != Action::Assign || database.action(i) != Action::Idle) continue;
			// get valid task for selected pawn
			Role role = Role::NONE;
			PlayerTaskJobData td = pq.top();
			size_t amount = 0;
			while (role == Role::NONE && !pq.nextEmpty())
			{
				Commodity c = td.commodity;
				amount = td.amount;
				if (amount <= 0)
					continue;
				role = (database, i, c);
				td = pq.next();
			}
			pq.snapback();
			if (role == Role::NONE)
					database.action(i) = Action::Idle;
			else assignTask(c, amount); //TODO
	 }
}

// only for idle animals
void assign_animal_tasks(Array<Animal> &animals, Array<ActionDecisionStatus> &actions,
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
			uint16_t season_time =
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

void handle_actions_and_movement()
	{
		UnitDatabase& unit_database = g_Game->unitDatabase;
        Array<Time>& inertias = unitDatabase.inertias;
		std::vector<EntityID> ready_actors = getReadyActors(inertias);
		ActionEventDispatchBuffer action_event_buffer = markActingEntities(
		    readyActors, nullptr, unitDatabase.coords, unitDatabase.targets,
																		 unitDatabase.actions, unitDatabase.frameDatas);

		handleMovements();
	}

std::vector<EntityID> get_ready_actors()
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
