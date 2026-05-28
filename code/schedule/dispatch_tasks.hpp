#include <core/containers.hpp>
#include <core/data.hpp>
#include <world/item/enum.hpp>
#include <world/unit/roles_and_actions.hpp>
#include <world/progression/enum.hpp>
#include <variant>
#include <array>
#include <queue>

enum class ProductionSubTasks
{
	PickUp,
	StartProduction
};

struct RolePriorityList
{
	
};	

struct Task
{
	
	std::array<std::pair<Role, Priority>, MAX_ROLES_PER_TASK> roles;
//in terms of items for items, # of units for support/research/military	
};

// TASK Dispatch
void createTaskPriorityBoard(Array<Coord> destinations, Array<Task> tasks, Array<uint16_t> resourceUnits,
		   Array<uint16_t> productionUnits, Array<uint16_t>)
{
	for (int i = 0; i < tasks.size(); i++)
	{
		Task task = tasks[i];
		for (size_t j = 0; j < task.roles.size(); j++) {
			Role role = task.roles[j];
		}
	}
}


// RESOURCES PAWN MANAGEMENT
//  change to assumming that the pawn is valid --> invalid pawns should never have been given this
//  task in the first place gets resource at certain tile, when pawn is adjacent to it, by
//  confirming action.
void collectResource(Item item)
{
	if (item < Item::RESOURCEMAX)
		return;
	Source resource = resources[item];
	// find available pawns who can perform actions (On^3)
	bool foundPawn = false;
	int pawnIndex;
	int actionIndex;
	Role role;
	for (int i = 0; i < roles.size(); i++)
	{ // check each pawn
		if (!checkOccuppied(i))
		{
			for (int j = 0; j < roles[i].size(); j++)
			{
				for (int k = 0; k < resources.action.size(); k++)
				{
					if (actionToRoles[resources.action[k]] == roles[i][j])
					{
						pawnIndex = i;
						actionIndex = k;
						role = roles[i][j];
						foundPawn = true;
					}
					if (foundPawn)
						break;
				}
				if (foundPawn)
					break;
			}
			if (foundPawn)
				break;
		}
		// get compatible SourceVariant (Tile, Plant, Animal, Scavengeable, or Item)
		SourceVariant source = resource.source[actionIndex];
		std::pair<int, int> coords = findNearestSource(source);
		// SHORTEST PATH ALGORITHM
	}
}

