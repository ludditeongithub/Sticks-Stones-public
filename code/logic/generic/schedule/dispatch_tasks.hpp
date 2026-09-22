#include <core/containers.hpp>
#include <data/types/aliases.hpp>
#include <data/types/item.hpp>
#include <world/unit/roles_and_actions.hpp>
#include <data/types/progression.hpp>
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
void create_task_priority_board(Array<Coord> destinations, Array<Task> tasks, Array<uint16_t> resource_units,
		   Array<uint16_t> production_units, Array<uint16_t>)
{
	for (int i = 0; i < tasks.size(); i++)
	{
		Task task = tasks[i];
		for (size_t j = 0; j < task.roles.size(); j++) {
			Role role = task.roles[j];
		}
	}
}

