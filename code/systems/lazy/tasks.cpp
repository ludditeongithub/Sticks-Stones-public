#pragma once
#include <core/data.hpp>
#include <world/unit/database.hpp>

void UnitDatabase::setNewAction(EntityID i)
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
				float t = getJobScore(rd[i][j]);
				if (t > highest)
				{
					highest = t;
					ji = j;
				}
			}
			action(i) = roleToAction[rd[i][ji]];
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

inline bool determineResourceAssignment(EntityID pawnIndex, size_t taskPriorityQueueIndex, Role role) {
					for (int k = 0;
					     k < resourcerResources[(role)].size;
					     k++)
					{
						if (resourcerResources[(role)]
								      [k] ==
						    resourcePriorityQueue[taskPriorityQueueIndex].first)
						{
								attemptResource(pawnIndex, role);
								return true;
						}
					}
				return false;
}

inline bool determineProductsAssignment(EntityID pawnIndex, size_t taskPriorityQueueIndex, Role role)
{
					// PRODUCTS
					for (int k = 0;
					     k < producerProducts[(role)].size;
					     k++)
					{
						if (producerProducts[(role)][k] ==
						    static_cast<Item>(g_TaskPriorityQueue[taskPriorityQueueIndex].task))
						{
						}
					}
}

/* Get jobs from  */
// NOTE: can implement jump table. this is for authority command structure
void decideTask(EntityID pawnIndex)
{
	int taskIndex = -1;
	TaskType type = TaskType::NONE;
	Role role;
	for (size_t i = 0; i < g_TaskPriorityQueue.size; i++)
	{
		// TODO: check if role is producer vs resource vs etc on lookup table
		if (g_TaskPriorityQueue[i].priority < highest)
		{
			for (EntityID j = 0; j < roles[pawnIndex].size; j++)
			{
				Role tRole = g_TaskPriorityQueue[i].role;

				if (tRole < Role::RESOURCEMAX && tRole > Role::SUPPORTMAX)
				{
					
				}
				else if (tRole < Role::PRODUCTSMAX && tRole > Role::RESOURCEMAX)
				{

				}
			}
		}
	}

	if (highest == 1)
	{
		attemptProduction(pawnIndex, producerProducts[static_cast<int>(tRole)][taskIndex]);
		return;
	}
}
}

for (int i = 0; i < supportPriorityQueue.size; i++)
{
	if (supportPriorityQueue[i].second < highest)
	{
		for (int j = 0; j < roles[pawnIndex].size; j++)
		{
			Role tRole = roles[pawnIndex][j];
			if (tRole == supportPriorityQueue[i])
				(producerProducts[static_cast<int>(tRole)][k] ==
				 productsPriorityQueue[i].first)
				{
					type = TaskType::Suppot highest =
					    productsPriorityQueue[i].second;
					taskIndex = i;
				}
		}
	}
}
if (highest == 1)
{
	attemptProduct(pawnIndex, role);
	return;
}
}
}

if (movingStatus[pawnIndex] != MovingStatus::Production)
{
	attemptProduction(pawnIndex, producerProducts[static_cast<int>(roles[pawnIndex[i]])]);
}
}
