#include "../include/basic.hpp"
#include "../include/categories.hpp"
#include "../include/unit.hpp"
#include "core/data.hpp"
#include <core/containers.hpp>

// NOTE: old file. contains many checks for certain entities at bottom, which are outdated, but may be useful. as well as adjacency checks.

// NOTE: may not work
/*
Direction check_if_adj_target(int pawn)
{
	std::pair<int, int> coords = coords[pawn];
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


void move_in_direction(int pawn, bool animal)
{
	Direction direction = current_direction[pawn];
	if (animal)
	{
		Animal entity = animals[pawn];
		delete_object(entity, animal_coords[pawn].first, animal_coords[pawn].second);
		if (direction == Direction::North)
			animal_coords[pawn].second += 1;
		else if (direction == Direction::South)
			animal_coords[pawn].second -= 1;
		if (direction == Direction::East)
			animal_coords[pawn].first += 1;
		else if (direction == Direction::West)
			animal_coords[pawn].first -= 1;
		insert_object(entity, animal_coords[pawn].first, animal_coords[pawn].second);
	}
	else
	{
		if (direction == Direction::North)
			coords[pawn].second += 1;
		else if (direction == Direction::South)
			coords[pawn].second -= 1;
		if (direction == Direction::East)
			coords[pawn].first += 1;
		else if (direction == Direction::West)
			coords[pawn].first -= 1;
		current_indices[coords[pawn]] = pawn;
	}
}
 */

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
std::vector<std::pair<int, int>> get_diamond(int cx, int cy, int radius)
{
	std::vector<std::pair<int, int>> result;

	for (int dx = -radius; dx <= radius; ++dx)
	{
		int max_dy = radius - std::abs(dx);
		for (int dy = -max_dy; dy <= max_dy; ++dy)
		{
			int x = cx + dx;
			int y = cy + dy;
			result.emplace_back(x, y);
		}
	}

	return result;
}

//returns size of edge_buffer
inline int get_new_diamond_edge(Array<Coord>& edge_buffer, uint32_t cx, uint32_t cy, int radius, Direction direction)
{
		int edge = 0;
	// LAYER 1 to LAYER 2
	for (int l = 0; l < 2; l++)
	{
		for (int i = -radius; i <= radius; ++i)
		{
			uint32_t x, y;
			switch (direction) {
			case Direction::East:
				x = cx + radius - std::abs(i - l);
				y = cy + i;
				break;
			case Direction::West:
				x = cx - radius + std::abs(i - l);
				y = cy + i;
				break;
			case Direction::South:
				y = cy + radius - std::abs(i - l);
				x = cx + i;
				break;
			case Direction::North:
				y = cy - radius + std::abs(i - l);
				x = cx + i;
				break;
			default:
				break;
			}
			edge_buffer[i] = {x, y};
			edge++;
		}
	}
	return edge;
}

// NOTE: maybe change this to be able to work for both males and females
void breed_check(Animal animal, int male_index, Direction direction, bool total)
{
	if (total)
		std::vector < std::pair<int, int> de = get_diamond(x, y, , direction);
	else
		std::vector < std::pair<int, int> de =
		    get_new_diamond_edge(x, y, sight_ranges[animal], direction);
	for (int x = 0; x < de.size(); x++)
	{
		if (animal_indices.find(de[x]) != animal_indices.end())
		{
			int female_index = animal_indices(de[x]);
			if (animals[female_index] == animal && !animal_sex[female_index])
			{
				animal_dest[male_index] = female_index;
				animal_moving_status[pawn_index] = MovingStatus::BreedPursuit;
			}
		}
	}
}

// NOTE: consider corpse for animals
void hunt_check(Animal &hunt_list[], int pawn_index, Direction direction, bool animal, bool total)
{
	if (animal)
		int sight_range = sight_ranges[Animal[pawn_index]];
	else
		int sight_range = human_sight;
	if (total)
		std::vector < std::pair<int, int> de = get_diamond(x, y, , direction);
	else
		std::vector < std::pair<int, int> de = get_new_diamond_edge(x, y, , direction);
	for (int x = 0; x < de.size(); x++)
	{
		for (int i = 0; i < hunt_list.size(); i++)
		{
			if (animal_indices.find(de[x]) != animal_indices.end())
			{
				int animal_index = animal_indices(de[x]);
				if (animals[animal_index] == hunt_list[i])
				{
					if (animal)
					{
						animal_dest[pawn_index] = animal_index;
						animal_moving_status[pawn_index] =
						    MovingStatus::AnimalPursuit;
					}
					else
					{
						dest[pawn_index] = animal_index;
						moving_status[pawn_index] =
						    MovingStatus::AnimalPursuit;
					}
				}
			}
		}
	}
}

void edible_plant_check(int animal_index, Direction direction, bool total)
{
	if (total)
		std::vector < std::pair<int, int> de = get_diamond(x, y, , direction);
	std::vector < std::pair<int, int> de =
	    get_new_diamond_edge(x, y, sight_ranges[animals[animal_index]], direction);
	for (int x = 0; x < de.size(); x++)
	{
		int index = tile_indices(de[x]);
		if !(is_plant(tile_object[index]))
			continue;
		for (int i = 0; i < herbivore_diet.size(); i++)
		{
			if (tile_object[index] == herbivore_diet[i])
			{
				animal_dest[animal_index] = index;
				animal_moving_status[animal_index] = MovingStatus::ApproachPlant;
			}
		}
	}
}

void fruit_check(int animal_index, Direction direction, bool total)
{
	if (total)
		std::vector < std::pair<int, int> de = get_diamond(x, y, , direction);
	std::vector < std::pair<int, int> de =
	    get_new_diamond_edge(x, y, sight_ranges[animals[animal_index]], direction);
	for (int x = 0; x < de.size(); x++)
	{
		int index = tile_indices(de[x]);
		if !(is_fruit(tile_object[index]))
			continue;
		for (int i = 0; i < static_cast<int>(Fruit::MAX); i++)
		{
			if (tile_object[index] == static_cast<Fruit>(i))
			{
				animal_dest[animal_index] = index;
				animal_moving_status[animal_index] = MovingStatus::ApproachFruit;
			}
		}
	}
}

// TODO: need to finish this
void search_plant_check(int pawn, Direction direction, bool total)
{
	if (total)
		std::vector < std::pair<int, int> de = get_diamond(x, y, human_sight, direction);
	std::vector < std::pair<int, int> de = get_new_diamond_edge(x, y, human_sight, direction);

	for (int x = 0; x < de.size(); x++)
	{
		int index = tile_indices(de[x]);
		if !(is_plant(tile_object[index]))
			continue;
		for (int i = 0; i <.size(); i++)
		{
			if (tile_object[index] == herbivore_diet[i])
			{
				dest[pawn] = index;
				moving_status[pawn] = MovingStatus::ApproachPlant;
			}
		}
	}
}

// NOTE: this might not work if objects cannot be compared; maybe should have differnt one for
// approachitem
void item_check(int pawn, Direction direction, bool total)
{
	if (total)
		std::vector < std::pair<int, int> de = get_diamond(x, y, human_sight, direction);
	std::vector < std::pair<int, int> de = get_new_diamond_edge(x, y, human_sight, direction);
	for (int x = 0; x < de.size(); x++)
	{
		int index = tile_indices(de[x]);
		if (tile_object[index] == current_target[pawn])
		{
			dest[pawn] = index;
			moving_status[pawn] = MovingStatus::GetItem;
		}
	}
}

void scavengeable_check(int pawn, Direction direction, bool total)
{
	if (total)
		std::vector < std::pair<int, int> de = get_diamond(x, y, human_sight, direction);
	std::vector < std::pair<int, int> de = get_new_diamond_edge(x, y, human_sight, direction);
	for (int x = 0; x < de.size(); x++)
	{
		int index = tile_indices(de[x]);
		if (tile_object[index] == current_target[pawn])
		{
			dest[pawn] = index;
			moving_status[pawn] = MovingStatus::ApproachScavengeable;
		}
	}
}
