
inline void TileDatabase::update_total_revealed_box() 
{
	uint32_t highest_x, highest_y = std::numeric_limits<uint32_t>::min();
	uint32_t lowest_x, lowest_y = std::numeric_limits<uint32_t>::max();
	for (size_t i = 0; i < tiles.size(); i++) {
		if (vision_statuses[i] == VisionStatus::Hidden)
			continue;
		Coord current = world->get_tile_coord_from_index(index);
		if (current.x < lowest_x)
			lowest_x = current.x;
		else if (current.x > highest_x) highest_x = current.x;
		
		if (current.y < lowest_y)
			lowest_y = current.y;
		else if (current.y > highest_y) highest_y = current.y;
	}
	total_revealed_box_top_left_corner = {lowest_x, lowest_y};
	total_revealed_box_dimensions = {highest_x - lowest_x, highest_y - lowest_y};
}

inline void Game::update_player_scrollable_borders() {
	
}
