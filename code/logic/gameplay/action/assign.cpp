#include "action.hpp"
#include "logic/simulation/game_time.hpp"
#include "data/types/action.hpp"
#include "data/run/animal_database.hpp"
#include "data/run/unit_database.hpp"
#include "world/unit/roles_commodities.hpp"

// =========================
// HELPERS
// =========================

void assign_task(Commodity commodity, size_t amount, Role role, Action action)
{
		ActionClass action_class = get_action_class(action);
		switch (action_class) {
		case ActionClass::Resource:
       			
                  break;
		case ActionClass::Production:
       			
                  break;
		case ActionClass::Support:
       			
                  break;
		case ActionClass:::
       			
                  break;
		default:
				
		}
}

inline Role get_action_role(unit::Database& database, size_t i, Commodity c)
{
	Skills skill = database.skill(i);
        std::array<Role, static_cast<size_t>(Role::MAX)>& roles = role_list(i);
	for (int j = 0; j < roles.size(); j++)
			{
			const Role& role = roles[j];			
                        uint8_t cs = get_commodity_score(role, c, skill); // returns 0 if invalid
			if (cs > get_commodity_score_req[c])
				return role;
                        //NOTE: this returns first valid role, NOT best
                        }		 
		 return Role::NONE;
	}

// =========================
// MAIN FUNCTIONS
// =========================

template <typename DB>
void mark_unassigned_and_no_inertia_entities(DB& database)
{
	database.unassigned_buffer.clear();
        database.no_inertia_buffer.clear();
  for (size_t i = 0; i < database.size; i++)
  {
    if (database.inertias(i) <= 0) database.no_inertia_buffer.emplace_back(i);
    if (database.actions(i) == Action::Assign) database.unassigned_buffer.emplace_back(i);
  }
}

// TODO: make certain tasks pausable and resumable, change to iterating over
// tasks per pawn rather than other way around (when pawns stats are
// implemented)-- timers will skip most pawns repeatedly, maybe need bool for
// whether job has just started
// only send alive and timer up units
void assign_unassigned_units(unit::Database& database)
{
  if (g_task_priority_queue->empty()) return;
  for (size_t i = 0; i < database.unassigned_buffer.size(); i++) {
    #if !SHIPPING_BUILD
    assert(database.actions[i] == Action::Assign || database.actions[i] == Action::Idle);
    #endif						
			// get valid task for selected pawn
			Role role = Role::NONE;
			PlayerTaskJobData td = g_task_priority_queue->top();
            Commodity c = td.commodity;
			size_t amount = 0;
			while (role == Role::NONE && !g_task_priority_queue.next_empty())
			{				
				amount = td.amount;
				if (amount <= 0)
					continue;
				role = get_action_role(database, i, c);
				td = g_task_priority_queue.next();
			}
			g_task_priority_queue.snapback();
			if (role == Role::NONE) database.action(i) = Action::Idle;
			else assign_task(c, amount, role, action(i)); //TODO	 
  }
}

// only for idle animals
void animal::Database::assign_unassigned_animals()
{
        using enum ActState;
	for (int i = 0; i < animals.size; i++)
	{          
		if (action(i) == Action::Assign)
		{
			Animal a = animal(i);

			// assign hungry animals to hunt/search for food
			if (hunger(i) <= hunger_search_threshold[a])
			{
				action(i) = Action::AnimalFoodSearch;
				continue;
			}

			// TODO: assign thirsty animals to drink
			// assign animals that need to breed to find mate
			uint16_t season_time = season_time(time, get_chunk_index_from_tile(position(i)));

			if (season_time <= breeding_season_start[a] &&
			    season_time >= breeding_season_end[a])
			{
                          action(i) = Action::AnimalBreedSearch;
			}
			else if (season_time <= migration_season_start[a] &&
				 season_time >= breeding_season_end[a])
			{
                          action(i) = Action::AnimalMigration;
			}
			else
			{
                          // TODO: special actions (migrate, search for pack, build nests/structures, hoard)
			// else wander/TODO: rejoin pack
                          action(i) = Action::AnimalFollowPack;
                        }			
		}
	}
}

// TODO: factor in hunger
// TODO: add to-do to go put away items to have necessary space for tools or
// items etc, when pawn goes to grab items
// may only be
template <typename DB>
MovingStateDispatchBuffer mark_entities_moving_state(DB& database)
{
  std::vector<size_t>& indices = database.no_inertia_buffer;
		bool if_animals = typeof(database) == animal::Database;
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
							buffer.units.push_back(i);	} // TODO: add more actions, breed
			}
	return buffer;
}

inline void start_timed_task(Time& inertia, const Task task, const Skills& skill)
{
	inertia = get_task_timer(task, skill);
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

void handle_animal_actions() {}

void handle_unit_actions() {}

void handle_actions()
	{
		unit::Database& unit_database = g_Game->unit_database;
        Array<Time>& inertias = unit_database.inertias;
		std::vector<EntityID> ready_actors = get_ready_actors(inertias);
		ActionInProgressDispatchBuffer action_event_buffer = mark_acting_entities(ready_actors, nullptr, unit_database.coords, unit_database.targets,
																		 unit_database.actions, unit_database.frame_datas);
	}

