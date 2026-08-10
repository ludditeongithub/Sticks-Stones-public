// NOTE: old file. contains many checks for certain entities at bottom, which are outdated, but may be useful. as well as adjacency checks.

// NOTE: may not work
/*

// NOTE: this is brute force greedy move. change if becomes to inefficient to mix of shortest path,
// but only as far as animal could realistically calculate and see
//
// right now, tells you direction and if you should move (if you have reached target)
//  for when dest is tile
/*
std::pair<Direction, bool> next_direction_to_target(int pawn_index)
{
	if (adj_check_tile(coords[pawn_index], dest[pawn_index]) != Direction::NONE)
		return {adj_check_tile(coords[pawn_index], dest[pawn_index]), false};
	Direction direction = Direction::NONE;
	int dx = tile_coords[dest[pawn_index]].first - coords[pawn_index].first;
	int dy = tile_coords[dest[pawn_index]].second - coords[pawn_index].second;
	if (dx > 0)
	{
		direction = Direction::West;
	}
	else
	{
		direction = Direction::East;
	}
	else if (dy > 0)
	{
		if (get_inertia(coords, Direcion::North) < get_inertia(coords, direction))
			direction = Direction::North;
	}
	else
	{
		if (get_inertia(coords, Direcion::South) < get_inertia(coords, direction))
			direction = Direction::South;
	}
	return {direction, true};
}
 */

/*
// for when dest is animal or human
std::pair<Direction, bool> next_direction_to_moving_target(int pawn_index, bool animal)
{
	if (animal)
	{
		int target_index = tile_indices[animal_coords[dest[i]]];
	}
	else
		int target_index = tile_indices[coords[dest[i]]];

	if (adj_check_tile(coords[pawn_index], target_index) != Direction::NONE)
		return {adj_check_tile(coords[pawn_index], target_index), false};

	Direction direction = Direction::NONE;
	int dx = dest[pawn_index].first - coords[pawn_index].first;
	int dy = dest[pawn_index].second - coords[pawn_index].second;
	if (dx > 0)
	{
		direction = Direction::West;
	}
	else
	{
		direction = Direction::East;
	}
	else if (dy > 0)
	{
		if (get_inertia(coords, Direcion::North) < get_inertia(coords, direction))
			direction = Direction::North;
	}
	else
	{
		if (get_inertia(coords, Direcion::South) < get_inertia(coords, direction))
			direction = Direction::South;
	}
	return {direction, true};
}
*/
