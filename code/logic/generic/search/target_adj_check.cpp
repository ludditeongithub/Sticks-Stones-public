Direction check_if_adj_target(int pawn)
{
	Coord coords = coords[pawn];
	Object obj;
	for (int i = 0; i < 4; i++)
	{
		switch (i)
		{
		case 0:
			obj = tile_object[tile_indices[{coords.x + 1, coords.y}]];
			d = Direction::East;
			break;
		case 1:
			obj = tile_object[tile_indices[{coords.x - 1, coords.y}]];
			d = Direction::West;
			break;
		case 2:
			obj = tile_object[tile_indices[{coords.x, coords.y + 1}]];
			d = Direction::North;
			break;
		case 3:
			obj = tile_object[tile_indices[{coords.x, coords.y - 1}]];
			d = Direction::South;
		}
		std::visit([](const auto &left, const auto &right) { return left == right; },
			   current_target[index], obj)
		{
			return d;
		}
	}
	return Direction::NONE;
}
