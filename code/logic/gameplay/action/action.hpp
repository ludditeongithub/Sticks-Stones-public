#pragma once
#include <queue>
#include <core/containers.hpp>
#include <vector>
#include <data/types/action.hpp>
#include <data/types/animal.hpp>
#include <data/run/unit_database.hpp>
#include <data/types/category.hpp>

// =========================
// TASK (tasks are the wider context over actions. some tasks may be made up of several actions or just one)
// =========================

struct PlayerTaskJobData
{
  Commodity commodity;
  uint8_t amount = 1;
};

std::priority_queue<PlayerTaskJobData>* g_task_priority_queue;

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

template<typename DB>
void  mark_unassigned_and_no_inertia_entities(DB& database);
void assign_unassigned_units(unit::Database& database);
template <typename DB>
MovingStateDispatchBuffer mark_entities_moving_state(std::vector<EntityID> &indices, DB& database);
inline Role get_valid_action_role(unit::Database& database, size_t i, Commodity c);
void assign_tasks(std::vector<EntityID> &indices, std::priority_queue<PlayerTaskJobData> &pq, unit::Database &database);
void assign_animal_tasks(Array<Animal> &animals, Array<FrameData> &frame_datas, Array<Coord> &positions, Array<Hunger> hungers);
std::vector<EntityID> get_ready_actors();

// =========================
// ATTEMPT
// =========================

void decide_task(EntityID pawn_index, unit::Database& database);

// =========================
// RESOURCE
// =========================

// =========================
// PRODUCT
// =========================

// =========================
// SUPPORT
// =========================

// =========================
// MAIN
// =========================

void process_actions();
