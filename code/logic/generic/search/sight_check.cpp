#include "search.hpp"
void get_diamond(std::vector<Coord>& result_buffer, Coord c, size_t radius)
{
  #if !SHIPPING_BUILD
  int test = 0;
  #endif
	for (size_t dx = -radius; dx <= radius; ++dx)
	{
		size_t max_dy = radius - std::abs(dx);
		for (size_t dy = -max_dy; dy <= max_dy; ++dy)
		{
			uint32_t x = c.x + dx;
			uint32_t y = c.y + dy;                        
                        #if !SHIPPING_BUILD
			test++;
                        assert(test <= DIAMOND_SCAN_MAX_SIZE);
                        #endif
			result_buffer.emplace_back(Coord{x, y});
		}
	}
}

//returns size of edge_buffer
inline int get_new_diamond_edge(std::vector<Coord>& edge_buffer, Coord c, int radius, Direction direction)
{
           #if !SHIPPING_BUILD
  int edge_size = 0;
        #endif
        
	// LAYER 1 to LAYER 2
	for (int l = 0; l < 2; l++)
	{
		for (int i = -radius; i <= radius; ++i)
		{
			uint32_t x, y;
			switch (direction) {
			case Direction::East:
				x = c.x + radius - unsigned_abs_diff(i , l);
				y = c.y + i;
				break;
			case Direction::West:
				x = c.x - radius + unsigned_abs_diff(i , l);
				y = c.y + i;
				break;
			case Direction::South:
				y = c.y + radius - unsigned_abs_diff(i , l);
				x = c.x + i;
				break;
			case Direction::North:
				y = c.y - radius + unsigned_abs_diff(i , l);
				x = c.x + i;
				break;
			default:
				break;
			}
			edge_buffer[i] = {x, y};
                        #if !SHIPPING_BUILD
                        assert(++edge_size < DIAMOND_EDGE_SCAN_MAX_SIZE);
                        #endif			
		}
	}
}

// NOTE: maybe change this to be able to work for both males and females
void breed_check(Animal animal, int male_index, Direction direction, bool total)
{
	if (total)
		std::vector < Coord de = get_diamond(x, y, , direction);
	else
		std::vector < Coord de =
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
		std::vector < Coord de = get_diamond(x, y, , direction);
	else
		std::vector < Coord de = get_new_diamond_edge(x, y, , direction);
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
		std::vector < Coord de = get_diamond(x, y, , direction);
	std::vector < Coord de =
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
		std::vector < Coord de = get_diamond(x, y, , direction);
	std::vector < Coord de =
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
