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

std::vector<EntityID> markNewPathEntities(std::vector<EntityID>& actingEntities, Array<FrameData>& frameDatas)
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
PathsBuffer getNewPaths(std::vector<EntityID>& pathDispatchBuffer, Array<Coord>& coords, Array<Target>& targets)
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

static uint32_t currentSearchID = 0;


static void initializeNode(NodeData& node)
{
	node.gCost = FLT_MAX;
	node.fCost = FLT_MAX;
	node.closedFlag = false;
}


static Direction directionFromTo(size_t from, size_t to)
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


static PathData reconstructPath(
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


PathData aStar(Coord start, Coord goal)
{
	currentSearchID++;


	const size_t width =
		g_World->WORLD_TILE_LENGTH;

	const size_t height =
		g_World->WORLD_TILE_LENGTH;

	const size_t startIndex =
		g_World->getTileIndexFromCoord(start);

	const size_t goalIndex =
		g_World->getTileIndexFromCoord(goal);

	std::priority_queue<
		OpenNode,
		std::vector<OpenNode>,
		std::greater<OpenNode>
	> openSet;


	NodeData& startNode =
		nodeData[startIndex];


	startNode.searchID = currentSearchID;
	initializeNode(startNode);


	startNode.gCost = 0;

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
		size_t currentIndex = openSet.top().index;
			
		openSet.pop();

		NodeData& currentNode =
			nodeData[currentIndex];

		if (currentNode.closedFlag)
			continue;

		if (currentIndex == goalIndex)
		{
			return reconstructPath(
				startIndex,
				goalIndex
			);
		}



		currentNode.closedFlag = true;



		size_t x = currentIndex % width;
		size_t y = currentIndex / width;



		const size_t neighbors[4] =
		{
			(y > 0)
				? currentIndex - width
				: currentIndex,

			(y + 1 < height)
				? currentIndex + width
				: currentIndex,

			(x > 0)
				? currentIndex - 1
				: currentIndex,

			(x + 1 < width)
				? currentIndex + 1
				: currentIndex
		};



		for (size_t neighbor : neighbors)
		{
			if (neighbor == currentIndex)continue;
			NodeData& neighborNode = nodeData[neighbor];

			if (neighborNode.searchID != currentSearchID)
			{
				neighborNode.searchID = currentSearchID;
				initializeNode(neighborNode);
			}

			if (neighborNode.closedFlag)
				continue;kxs
			float tentativeG = currentNode.gCost + tileMoveCosts[neighbor];

			if (tentativeG < neighborNode.gCost)
			{
				neighborNode.gCost =
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
