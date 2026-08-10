#include <core/data.hpp>
#include "pathfinding.hpp"
#include "core/containers.hpp"
#include "schedule/dispatch.hpp"
#include "world/action/enum.hpp"
#include "world/tile/database.hpp"
#include "world/world.hpp"
#include <queue>
#include <vector>
#include <algorithm>
#include <limits>

std::vector<EntityID> mark_new_path_entities(std::vector<EntityID>& acting_entities, Array<FrameData>& frame_datas)
{
		std::vector<EntityID> indices;
		indices.reserve(acting_entities.size());		
		for (int i = 0; i < acting_entities.size(); i++) {
				EntityID j = acting_entities[i];
				if (frame_datas[j].get<ActState>() == ActState::NewPath) indices.emplace_back();
		}
		indices.shrink_to_fit();
		return indices;
}

template<typename DB>
void PathsBuffer::get_new_paths(DB& database, std::vector<EntityID>& no_inertia_entities, tile::Database& tiles)
{
	std::vector<EntityID> new_path_entities =
	    mark_new_path_entities(no_inertia_entities, database.frame_datas);
        	
		for (size_t i = 0; i < new_path_entities.size(); i++)
		{
                EntityID j = new_path_entities[i];
						
		Coord dest = tiles.get_coord(database.targets[j].index);
		PathData pd = a_star(database.coord(j), dest);
		currents[i] = 0;
		ends[i] = pd.end;
		directions[i] = pd.directions;
	}
}


struct OpenNode
{
	size_t index;
	float f_cost;

	bool operator>(const OpenNode& other) const
	{
		return f_cost > other.f_cost;
	}
};

static uint32_t current_search_id = 0;


static void initialize_node(NodeData& node)
{
	node.g_cost = FLT_MAX;
	node.f_cost = FLT_MAX;
	node.closed_flag = false;
}


static Direction direction_from_to(size_t from, size_t to)
{
	const size_t width = g_world->world_tile_length;

	int diff =
		static_cast<int>(to) -
		static_cast<int>(from);

	if (diff == -static_cast<int>(width))
		return Direction::North;

	if (diff == static_cast<int>(width))
		return Direction::South;

	if (diff == -1)
		return Direction::West;

	return Direction::East;
}


static PathData reconstruct_path(
	size_t start_index,
	size_t goal_index)
{
	PathData path;

	path.start =
		g_world->get_tile_coord_from_index(start_index);

	path.end =
		g_world->get_tile_coord_from_index(goal_index);


	size_t current = goal_index;


	while (current != start_index)
	{
		Direction dir =
			node_data[current].came_direction;


		path.directions.push_back(dir);


		switch (dir)
		{
			case Direction::North:
				current += g_World->WORLD_TILE_LENGTH;
				break;

			case Direction::South:
				current -= g_World->WORLD_TILE_LENGTH;
				break;

			case Direction::West:
				current += 1;
				break;

			case Direction::East:
				current -= 1;
				break;
		}
	}


	std::reverse(
		path.directions.begin(),
		path.directions.end()
	);


	return path;
}


PathData a_star(Coord start, Coord goal)
{
	current_search_id++;

	const size_t width =
		g_world->world_tile_length;

	const size_t height =
		g_world->world_tile_length;

	const size_t start_index =
		g_world->get_tile_index_from_coord(start);

	const size_t goal_index =
		g_world->get_tile_index_from_coord(goal);

	std::priority_queue<
		OpenNode,
		std::vector<OpenNode>,
		std::greater<OpenNode>
	> open_set;


	NodeData& start_node =
		node_data[start_index];


	start_node.search_id = current_search_id;
	initialize_node(start_node);


	start_node.g_cost = 0;

	start_node.f_cost =
		heuristic(start, goal);


	open_set.push(
		{
			start_index,
			start_node.f_cost
		}
	);

	while (!open_set.empty())
	{
		size_t current_index = open_set.top().index;
			
		open_set.pop();

		NodeData& current_node =
			node_data[current_index];

		if (current_node.closed_flag)
			continue;

		if (current_index == goal_index)
		{
			return reconstruct_path(
				start_index,
				goal_index
			);
		}



		current_node.closed_flag = true;



		size_t x = current_index % width;
		size_t y = current_index / width;



		const size_t neighbors[4] =
		{
			(y > 0)
				? current_index - width
				: current_index,

			(y + 1 < height)
				? current_index + width
				: current_index,

			(x > 0)
				? current_index - 1
				: current_index,

			(x + 1 < width)
				? current_index + 1
				: current_index
		};



		for (size_t neighbor : neighbors)
		{
			if (neighbor == current_index)continue;
			NodeData& neighbor_node = node_data[neighbor];

			if (neighbor_node.search_id != current_search_id)
			{
				neighbor_node.search_id = current_search_id;
				initialize_node(neighbor_node);
			}

			if (neighbor_node.closed_flag) continue;
			float tentative_g = current_node.g_cost + tile_move_costs[neighbor];

			if (tentative_g < neighbor_node.g_cost)
			{
				neighbor_node.g_cost =
					tentative_g;

				neighbor_node.f_cost =
					tentative_g +
					heuristic(
						g_World->get_tile_coord_from_index(neighbor),
						goal
					);

				neighbor_node.came_direction =
					direction_from_to(
						current_index,
						neighbor
					);

				open_set.push(
					{
						neighbor,
						neighbor_node.f_cost
					}
				);
			}
		}
	}
	return {};
}
