#pragma once
#include "core/containers.hpp"
#include "world/tile/data.hpp"
#include <world/unit/entity.hpp>
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
	uint16_t highestX, lowestX, lowestY, highestY;
	for (size_t i = 0; i < tiles.size(); i++) {
		
	}
}
