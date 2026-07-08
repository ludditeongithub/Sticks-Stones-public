#include "database.hpp"
#include "world/tile/enum.hpp"

Coord TileDatabase::getNearestEmptyTileBlock(Coord coord, size_t length, size_t width = 1)
{
		bool foundWidth = 0;
		bool found = false;
		Coord last = coord;
		Coord topLeftCorner;
		while (foundWidth < width) {
			Coord start = getNearestEmptyTile(last);
			if (foundWidth = 0) topLeftCorner = start;
			Coord next = getNearestEmptyTile(start, Adjacency::Horizontal);
			if (adjacent(start, next, Adjacency::Horizontal)) foundWidth++;
					// TODO: currently wrong. will error if near border
			else {
					last = getNearestEmptyTile(next);
					foundWidth = 0;
			}
		}
		return topLeftCorner;
}

enum class Adjacency {
		Any,
		Horizontal,
		Vertical
};

bool TileDatabase::adjacent(Coord start, Coord next, Adjacency adjacency = Adjacency::Any) {
		switch (adjacency) {
		case Adjacency::Horizontal:
       			if (std::abs(start.x - next.x) == 1 && std::abs(start.y - next.y) == 0) return true;
				break;
		case Adjacency::Vertical:
       			if (std::abs(start.y - next.y) == 1 && std::abs(start.x - next.x) == 0) return true;
       			break;
		default:
			if ((std::abs(start.y - next.y) <= 1 && std::abs(start.x - next.x) == 0) || (std::abs(start.x - next.x) == 1 && std::abs(start.y - next.y) == 0) return true;
		}
		return false;
}

Coord TileDatabase::getNearestEmptyTile(Coord coord, Adjacency adjacency = Adjacency::Any)
	{
		int index = world.getTileIndexFromCoord(coord);
		if (adjacency == Adjacency::Any) SCoord vectors[4] = {{0, 1}, {1, 0}, {-1, 0}, {1, 0}};
		else if (adjacency == Adjacency::Horizontal) SCoord vectors[2] = {{1, 0}, {-1, 0}};
		else SCoord vectors[2] = vectors[2] = {{0, 1}, {0, -1}};

		bool found = false;
		std::queue<Coord> queue;
		queue.push(coord);
		while (!found)
		{
			Coord target = queue.front();
			queue.pop();
			for (size_t i = 0; i < 4; i++) {
				Coord candidate = {std::min(world.WORLD_TILE_LENGTH, target.x + vectors[i].x), std::min(world.WORLD_TILE_LENGTH, target.y + vectors[i].y)};
				if (tileStatuses[getChunkIndexFromTile(candidate)].get<OccupiedStatus>() == OccupiedStatus::Vacant) return candidate;
				else queue.push(candidate);
			}
		}
	}		
