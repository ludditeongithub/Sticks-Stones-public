#include "search.hpp"
#include <vector>

// TODO: need to finish this
template<typename DB, typename E>
void SearchGrid::scan_for_entity_list(DB& database, size_t index, Direction direction, size_t sight_range, SearchType type, std::vector<E>& entity_list, std::vector<Coord>& edge_buffer, std::vector<Coord>& diamond_buffer)
{
        Coord c = database.coord(index);
	if (total) get_diamond(diamond_buffer, c, sight_range);
	std::vector <Coord> de = get_new_diamond_edge(edge_buffer, c, sight_range, direction);
              
		for (int i = 0; i < entity_list.size(); i++)
		{
                  
                  if (tile_object(index) == herbivore_diet[i])
			{
				database.target(index) = tile_index;
                                database.target_type(index) = TargetType::Tile;
                                moving_status(index) = MovingStatus::ApproachPlant;
			}
		}
}

// NOTE: this might not work if objects cannot be compared; maybe should have differnt one for
// approachitem
void scan_item(int pawn, Direction direction, bool total)
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

void scan_scavengeable(int pawn, Direction direction, bool total)
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
