#include "action.hpp"
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
MovingStateDispatchBuffer mark_entities_moving_state(std::vector<EntityID> &indices, DB& database)
{
		bool if_animals = typeof(database) == AnimalDatabase;
		MovingStateDispatchBuffer buffer = MovingStateDispatchBuffer(indices.size(), if_animals);
	
	for (int j = 0; j < indices.size(); j++)
			{
					EntityID i = indices[j];
					const Action action = database.action(i);
					if (action == Action::Idle || action == Action::Sleep) continue;
					if (action == Action::Prowl || action == Action::CheckProwl)
							buffer.check_near_targets.push_back(i);
					if (action == Action::Wander) {						buffer.moving_tiles.push_back(i);											
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
	for (int j = 0; j < database.role_data(i).size(); j++)
			{
			const Role& role = role_data(i)[j];
			auto &commodity_list = roles_to_commodities[role];
					for (auto x: commodity_list) {					
					// TODO: precompute all scores for all roles
					uint8_t cs =
					    get_commodity_score(x, skill); // returns 0 if invalid
					if (cs > commodity_data[x].skill_req)
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
	inertia = get_task_timer(task, skill);
}

void assign_task(Commodity commodity, size_t amount, Role role, Action action)
{
		ActionClass action_class = get_action_class(action);
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
void assign_tasks(std::vector<EntityID> &indices, UnitDatabase& database)
{
		if (g_task_priority_queue.empty()) return;
		for (int i = 0; i < indices.size(); i++)
		{						
			if (database.action(i) != Action::Assign || database.action(i) != Action::Idle) continue;
			// get valid task for selected pawn
			Role role = Role::NONE;
			PlayerTaskJobData td = g_task_priority_queue.top();
			size_t amount = 0;
			while (role == Role::NONE && !g_task_priority_queue.next_empty())
			{
				Commodity c = td.commodity;
				amount = td.amount;
				if (amount <= 0)
					continue;
				role = (database, i, c);
				td = g_task_priority_queue.next();
			}
			g_task_priority_queue.snapback();
			if (role == Role::NONE)
					database.action(i) = Action::Idle;
			else assign_task(c, amount); //TODO
	 }
}

// only for idle animals
void assign_animal_tasks(Array<Animal> &animals, Array<ActState> &actions,
		       Array<Coord> &positions, Array<Hunger> hungers)
{
	using enum ActState;
	for (int i = 0; i < animals.size; i++)
	{
		if (action_decision_status(i) == ActState::Assign)
		{
			Animal a = animal(i);

			// assign hungry animals to hunt/search for food
			if (hunger(i) <= hunger_search_threshold[a])
			{
				action_decision_status(i) = AnimalFoodSearch;
				continue;
			}

			// TODO: assign thirsty animals to drink
			// assign animals that need to breed to find mate
			uint16_t season_time =
			    get_season_time(time, get_chunk_index_from_tile(position(i)));

			if (season_time <= breeding_season_start[a] &&
			    season_time >= breeding_season_end[a])
			{
				action_decision_status(i) = AnimalBreedSearch;
			}
			else if (season_time <= migration_season_start[a] &&
				 season_time >= breeding_season_end[a])
			{
				action_decision_status(i) = AnimalMigration;
			}

			// TODO: special actions (migrate, search for pack, build
			// nests/structures, hoard)

			// else wander/TODO: follow pack
			action_decision_status(i) = AnimalRejoinPack;
		}
	}
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

void handle_actions_and_movement()
	{
		UnitDatabase& unit_database = g_Game->unit_database;
        Array<Time>& inertias = unit_database.inertias;
		std::vector<EntityID> ready_actors = get_ready_actors(inertias);
		ActionInProgressDispatchBuffer action_event_buffer = mark_acting_entities(ready_actors, nullptr, unit_database.coords, unit_database.targets,
																		 unit_database.actions, unit_database.frame_datas);

		handle_movements();
	}

