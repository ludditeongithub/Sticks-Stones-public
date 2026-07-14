#include <core/data.hpp>
#include "pathfinding.hpp"
#include "core/containers.hpp"
#include "schedule/dispatch.hpp"
#include "world/action/enum.hpp"
#include "world/world.hpp"
#include <queue>
#include <vector>
#include <algorithm>
#include <limits>

std::vector<EntityID> mark_new_path_entities(std::vector<EntityID>& actingEntities, Array<FrameData>& frameDatas)
{
		std::vector<EntityID> indices;
		indices.reserve(actingEntities.size());		
		for (int i = 0; i < actingEntities.size(); i++) {
				EntityID j = actingEntities[i];
				if (frameDatas[j].get<ActState>() == ActState::NewPath) indices.emplace_back();
		}
		indices.shrink_to_fit();
		return indices;
}

// sets start and end, inputted from all types of jobs, of only entity indices that have been chosen
// to need new paths
PathsBuffer get_new_paths(std::vector<EntityID>& pathDispatchBuffer, Array<Coord>& coords, Array<Target>& targets)
{	
		PathsBuffer pb = PathsBuffer();
		for (size_t i = 0; i < pathDispatchBuffer.size(); i++)
		{
				EntityID j = pathDispatchBuffer[i];
						
						#if !SHIPPING_BUILD
						assert(targets[j].type == TargetType::Tile);
						#endif
						
		Coord dest = g_Tiles->getCoordFromIndex(targets[j].index);
		PathData pd = aStar(coords[j], dest);
		pb.currents[i] = 0;
		pb.ends[i] = pd.end;
		pb.datas[i] = pd.data;
		pb.destinations[i] = pathDispatchBuffer.destinations[i];
	}
}

struct OpenNode
{
	size_t index;
	float fCost;

	bool operator>(const OpenNode& other) const
	{
		return fCost > other.fCost;
	}
};

static uint32_t current_search_id = 0;


static void initialize_node(NodeData& node)
{
	node.gCost = FLT_MAX;
	node.fCost = FLT_MAX;
	node.closedFlag = false;
}


static Direction direction_from_to(size_t from, size_t to)
{
	const size_t width = g_World->WORLD_TILE_LENGTH;

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
	size_t startIndex,
	size_t goalIndex)
{
	PathData path;

	path.start =
		g_World->getTileCoordFromIndex(startIndex);

	path.end =
		g_World->getTileCoordFromIndex(goalIndex);


	size_t current = goalIndex;


	while (current != startIndex)
	{
		Direction dir =
			nodeData[current].cameDirection;


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
		g_World->WORLD_TILE_LENGTH;

	const size_t height =
		g_World->WORLD_TILE_LENGTH;

	const size_t start_index =
		g_World->getTileIndexFromCoord(start);

	const size_t goal_index =
		g_World->getTileIndexFromCoord(goal);

	std::priority_queue<
		OpenNode,
		std::vector<OpenNode>,
		std::greater<OpenNode>
	> openSet;


	NodeData& start_node =
		nodeData[start_index];


	start_node.searchID = current_search_id;
	initialize_node(start_node);


	start_node.gCost = 0;

	startNode.fCost =
		heuristic(start, goal);


	openSet.push(
		{
			startIndex,
			startNode.fCost
		}
	);



	while (!openSet.empty())
	{
		size_t current_index = openSet.top().index;
			
		openSet.pop();

		NodeData& current_node =
			nodeData[current_index];

		if (current_node.closedFlag)
			continue;

		if (current_index == goal_index)
		{
			return reconstruct_path(
				start_index,
				goal_index
			);
		}



		current_node.closedFlag = true;



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
			NodeData& neighbor_node = nodeData[neighbor];

			if (neighbor_node.searchID != current_search_id)
			{
				neighbor_node.searchID = current_search_id;
				initialize_node(neighbor_node);
			}

			if (neighbor_node.closedFlag)
				continue;kxs
			float tentative_g = current_node.gCost + tileMoveCosts[neighbor];

			if (tentativeG < neighbor_node.gCost)
			{
				neighbor_node.gCost =
					tentativeG;

				neighborNode.fCost =
					tentativeG +
					heuristic(
						g_World->getTileCoordFromIndex(neighbor),
						goal
					);

				neighborNode.cameDirection =
					directionFromTo(
						currentIndex,
						neighbor
					);

				openSet.push(
					{
						neighbor,
						neighborNode.fCost
					}
				);
			}
		}
	}


	return {};
}
