#pragma once
#include "core/containers.hpp"
#include "world/tile/data.hpp"
#include <limits>
#include <world/unit/database.hpp>
#include <core/position_check.hpp>
#include <simulation/game.hpp>
#include <world/tile/database.hpp>

inline void TileDatabase::manageFogPerMovement(World* world, UnitDatabase* units, Coord destination, bool explorer)
{
	if (within(destination, totalRevealedBoxTopLeftCorner, totalRevealedBoxDimensions))
	{
	}
	else
	{
		getNewDiamondEdge(edgeBuffer, destination.x, destination.y,
				  getSightRange(units->skills.perception), );
		for (size_t i = 0; i < edgeBuffer.size(); i++)
		{
			uint32_t index = world->getTileIndexFromCoord(edgeBuffer[i]);
			VisionStatus& vs = visionStatuses[index];
			if (explorer)
			{				
				if (vs == VisionStatus::Hidden || vs == VisionStatus::Revealed) vs = VisionStatus::Explored;
			} else if (vs == VisionStatus::Hidden) vs = VisionStatus::Revealed;
		}
	}		
}

inline void TileDatabase::updateTotalRevealedBox() 
{
	uint32_t highestX, highestY = std::numeric_limits<uint32_t>::min();
	uint32_t lowestX, lowestY = std::numeric_limits<uint32_t>::max();
	for (size_t i = 0; i < tiles.size(); i++) {
		if (visionStatuses[i] == VisionStatus::Hidden)
			continue;
		Coord current = world->getTileCoordFromIndex(index);
		if (current.x < lowestX)
			lowestX = current.x;
		else if (current.x > highestX) highestX = current.x;
		
		if (current.y < lowestY)
			lowestY = current.y;
		else if (current.y > highestY) highestY = current.y;
	}
	totalRevealedBoxTopLeftCorner = {lowestX, lowestY};
	totalRevealedBoxDimensions = {highestX - lowestX, highestY - lowestY};
}

inline void Game::updatePlayerScrollableBorders() {
	
}
