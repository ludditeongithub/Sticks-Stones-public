#include "coord.hpp"
#include <optional>

namespace coord
  {
      

std::optional<Coord> get_nearest_empty_tile(uint32_t start_index)
{
	std::queue<uint32_t> q;
	std::unordered_set<uint32_t> visited;

	q.push(start_index);
	visited.insert(start_index);

	while (!q.empty())
	{
		uint32_t current = q.front();
		q.pop();

		std::array<uint32_t, 4> neighbors = get_adjacent_tiles_indices(current);

		for (uint32_t neighbor : neighbors)
		{
			if (neighbor < 0 || visited.count(neighbor))
				continue;

			if (check_empty_tile(current, neighbor))
			{
				return tile_coords[neighbor]; 
			}

			visited.insert(neighbor);
			q.push(neighbor);
		}
	}
        return std::nullopt;
}

//TODO: consider stride
inline Coord get_pos(Direction direction, Coord coord, uint8_t stride = 1)
{  
  Coord new_pos;
  switch (direction) {
  case Direction::North:
    new_pos = {coord.x, coord.y - stride};
    break;
  case Direction::South:
    new_pos = {coord.x, coord.y + stride};
    break;
  case Direction::East:
    new_pos = {coord.x + stride, coord.y};
    break;
  case Direction::West:
    new_pos = {coord.x - stride, coord.y};
    break;
  default:
  // TODO: error
    break;
  }

  assert(!out_of_bounds(coord) && !out_of_bounds(new_pos));

  return new_pos;
}


}
