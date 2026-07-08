
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
