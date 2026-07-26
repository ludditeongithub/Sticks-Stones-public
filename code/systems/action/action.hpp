#pragma once
#include <world/unit/roles_commodities.hpp>
#include <core/data.hpp>
#include <core/containers.hpp>
#include <vector>
#include <world/action/enum.hpp>
#include <world/animal/enum.hpp>
#include <world/unit/database.hpp>

// =========================
// TASK (tasks are the wider context over actions. some tasks may be made up of several actions or just one)
// =========================

struct PlayerTaskJobData
{
  Commodity commodity;
  uint8_t amount = 1;
};

PriorityQueue<PlayerTaskJobData>* g_task_priority_queue;

struct MovingStateDispatchBuffer
{
		bool animals;
		std::vector<EntityID> moving_tiles;
		std::vector<EntityID> check_near_targets;
		std::vector<EntityID> approachs;
		std::vector<EntityID> units;

		MovingStateDispatchBuffer(size_t size, bool animals) : animals(animals)
		{
			if (animals)
			{
                          
                        }
                        else
                          {
                            units.reserve(size);
                          }
			moving_tiles.reserve(size);
			check_near_targets.reserve(size);
			approachs.reserve(size);
		}

		void shrink_to_fit()
		{
			if (animals)
					{
					}
					else
							{
									units.shrink_to_fit();
							}
			moving_tiles.shrink_to_fit();
			check_near_targets.shrink_to_fit();
			approachs.shrink_to_fit();
		}
};

// =========================
// ASSIGN
// =========================

void assign_unassigned_entities();
template <typename DB>
MovingStateDispatchBuffer mark_entities_moving_state(std::vector<EntityID> &indices, DB& database);
inline Role get_valid_action_role(UnitDatabase& database, size_t i, Commodity c);
void assign_tasks(std::vector<EntityID> &indices, PriorityQueue<PlayerTaskJobData> &pq,
		  UnitDatabase &database);

void assign_animal_tasks(Array<Animal> &animals, Array<ActState> &actions, Array<Coord> &positions, Array<Hunger> hungers);
void handle_actions_and_movement();
std::vector<EntityID> get_ready_actors();

// =========================
// ATTEMPT
// =========================

void decide_task(EntityID pawn_index, UnitDatabase& database);

// =========================
// RESOURCE
// =========================

// =========================
// PRODUCT
// =========================

// =========================
// SUPPORT
// =========================
