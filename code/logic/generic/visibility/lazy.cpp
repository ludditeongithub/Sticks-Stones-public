#pragma once
#include "core/containers.hpp"
#include "data/const/tile_data.hpp"
#include <limits>
#include <data/run/unit_database.hpp>
#include <core/position_check.hpp>
#include <logic/simulation/game.hpp>
#include <data/run/tile_database.hpp>

inline void tile::Database::manage_fog_per_movement(World* world, unit::Database* units, Coord destination, bool explorer)
{
	if (within(destination, total_revealed_box_top_left_corner, total_revealed_box_dimensions))
	{
	}
	else
	{
		get_new_diamond_edge(edge_buffer, destination.x, destination.y,
				  get_sight_range(units->skills.perception), );
		for (size_t i = 0; i < edge_buffer.size(); i++)
		{
			uint32_t index = world->get_tile_index_from_coord(edge_buffer[i]);
			VisionStatus& vs = vision_statuses[index];
			if (explorer)
			{				
				if (vs == VisionStatus::Hidden || vs == VisionStatus::Revealed) vs = VisionStatus::Explored;
			} else if (vs == VisionStatus::Hidden) vs = VisionStatus::Revealed;
		}
	}		
}
