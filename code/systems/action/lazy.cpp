#pragma once
#include <core/data.hpp>
#include <world/unit/database.hpp>

void UnitDatabase::set_new_action(EntityID i)
{
		if (health(i) <= 0) action(i) = Action::Dead;

		if (action(i) == Action::Assign)
		{
			// get best role for pawn to inhabit
			float highest = std::numeric_limits<float>::min();
			auto ji = INVALID;
			for (int j = 0; j < rd[i].size(); j++)
			{
				// TODO: precompute all scores for all roles
				float t = get_job_score(rd[i][j]);
				if (t > highest)
				{
					highest = t;
					ji = j;
				}
			}
			action(i) = role_to_action[rd[i][ji]];
		}
}

// COMMAND
// The authority (you), oligarchy, or democratic state commands what the pawns produce, and you own all goods.
// Large Order (Satisfaction) decrease and production decrease. Resource
// estimates are terrible and especially if order is low

// MIXED COMMAND
// The authority (you) also sends mandatory quotas of goods pawns must produce,
// which they produce first, but after that pawns switch roles and produce
// whatever they like to produce, and also keep their goods. Pawns receive a
// large a small bonus and a small Order (Satisfaction) bonus, and are somewhat
// more likely to produce high quality items. You can buy goods from your pawns.
// Resource estimates are poor

// MARKET
// You can buy goods from your pawns, and also tax them, but cannot set quotas.
// Money is crucial in this run. Pawns receive a medium bonus and a medium Order
// (Satisfaction) bonus, and are quite more likely to produce high quality
// items. Resource estimates are great. True bureaucratic recording is expensive

// ANARCHY
// Pawns switch roles and produce whatever they like to produce, and also keep
// their goods. Only minimum taxes can be set, and only certain types. However,
// they receive a large production bonus and a large Order (Satisfaction) bonus,
// and are more likely to produce high quality items. You only control truly
// control the government and military pawns. You can buy and sell goods from
// your pawns, as well as hire mercenaries that form among your pawns. Pawns buy
// and sell goods among each other. Resource Estimates are decent, but true
// bureaucratic recording is impossible

inline bool attempt_resource_assignment(EntityID pawn_index, size_t task_priority_queue_index, Role role) {
					for (int k = 0;
					     k < resourcer_resources[(role)].size;
					     k++)
					{
						if (resourcer_resources[(role)]
								      [k] ==
						    resource_priority_queue[task_priority_queue_index].first)
						{
								attempt_resource(pawn_index, role);
								return true;
						}
					}
				return false;
}

inline bool attempt_products_assignment(EntityID pawn_index, TaskPriorityQueue& pq, size_t task_priority_queue_index, Role role)
{
					// PRODUCTS
					for (int k = 0;
					     k < producer_products[(role)].size;
					     k++)
							if (producer_products[(role)][k] == static_cast<Item>(pq[task_priority_queue_index].task)) attempt_production(pawn_index);					
}

/* Get jobs from  */
// NOTE: can implement jump table. this is for authority command structure
void decide_task(EntityID pawn_index, UnitDatabase& database)
{
	int task_index = -1;
	TaskType type = TaskType::NONE;
	Role role;
	for (size_t i = 0; i < g_TaskPriorityQueue.size; i++)
	{
		// TODO: check if role is producer vs resource vs etc on lookup table
		if (g_TaskPriorityQueue[i].priority < highest)
		{
			for (EntityID j = 0; j < roles[pawn_index].size; j++)
			{
				Role t_role = g_TaskPriorityQueue[i].role;

				if (t_role < Role::RESOURCEMAX && t_role > Role::SUPPORTMAX)
				{
					
				}
				else if (t_role < Role::PRODUCTSMAX && t_role > Role::RESOURCEMAX)
				{

				}
			}
		}
	}

	if (highest == 1)
	{
		attempt_production(pawn_index, producer_products[static_cast<int>(t_role)][task_index]);
		return;
	}
}
}

for (int i = 0; i < support_priority_queue.size; i++)
{
	if (support_priority_queue[i].second < highest)
	{
		for (int j = 0; j < roles[pawn_index].size; j++)
		{
			Role t_role = roles[pawn_index][j];
			if (t_role == support_priority_queue[i])
				(producer_products[static_cast<int>(t_role)][k] ==
				 products_priority_queue[i].first)
				{
					type = TaskType::Suppot highest =
					    products_priority_queue[i].second;
					task_index = i;
				}
		}
	}
}
if (highest == 1)
{
	attempt_product(pawn_index, role);
	return;
}
}
}

if (moving_status[pawn_index] != MovingStatus::Production)
{
	attempt_production(pawn_index, producer_products[static_cast<int>(roles[pawn_index[i]])]);
}
}
