#include <core/coord.hpp>
#include <data/run/tile_database.hpp>

Coord tile::Database::get_nearest_empty_tile_block(Coord coord, size_t length, size_t width = 1)
{
		bool found_width = 0;
		bool found = false;
		Coord last = coord;
		Coord top_left_corner;
		while (found_width < width) {
			Coord start = get_nearest_empty_tile(last);
			if (found_width = 0) top_left_corner = start;
			Coord next = get_nearest_empty_tile(start, Adjacency::Horizontal);
			if (adjacent(start, next, Adjacency::Horizontal)) found_width++;
					// TODO: currently wrong. will error if near border
			else {
					last = get_nearest_empty_tile(next);
					found_width = 0;
			}
		}
		return top_left_corner;
}

Coord tile::Database::get_nearest_empty_tile(Coord coord, Adjacency adjacency = Adjacency::Any)
	{
		int index = world.get_tile_index_from_coord(coord);
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
				if (tile_statuses[tile_to_chunk_index(candidate)].get<OccupiedStatus>() == OccupiedStatus::Vacant) return candidate;
				else queue.push(candidate);
			}
		}
	}		
