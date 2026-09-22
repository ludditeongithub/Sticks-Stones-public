#include "core/tables.hpp"
#include "movement.hpp"
#include <world/tile/tables.hpp>
#include <world/unit/defaults.hpp>
#include "data/run/animal_database.hpp"
#include "world/animal/tables.hpp"
// raw inertia value
inline Frame tile::Database::calc_inertia(Frame entity_base_frames, const Coord coord)
{
	return static_cast<Frame>(entity_base_frames * tile_frame_multiplier[tile_datas[get_index(coord)]]);
}

inline Frame tile::Database::calc_inertia(const Coord coord, bool running)
{
		Frame base;
		running ? base = BASE_RUNNING_FRAMES : base = BASE_WALKING_FRAMES;
		return static_cast<Frame>( * tile_frame_multiplier[tile_datas[get_index(coord)].get<Tile>()]);
}

template <typename DB>
inline void move(DB& database, EntityID i, const Direction direction)
{
  Coord& coord = database.coords[i];
  coord.move(direction);  
}

template <typename DB>
inline void set_next_move_inertia(DB& database, tile::Database& tiles, EntityID i, const Coord coord, bool running)
{
if (typeid(database) == animal::Database)
		{
	LookupTable<Animal, Frame> frame_per_tiles_table = animal::get_frame_per_tiles_table(running);
		  
    Animal animal = database.animals[i];
    database.inertias[i] = tiles.calc_inertia(frame_per_tiles_table[animal], coord);
  }
  else
		  database.inertias[i] = tiles.calc_inertia(coord, running);
  // TODO: speed for different units
}

void set_next_movement_inertia() {}

else if (actions[i] == Action::Prowl ||
			 actions[i] == Action::CheckProwl)
		{ // TODO: ProwlTile
			if (rint(0, 50) < 50)
				directions[i] = get_random_adj_direction(directions[i]);
			move_in_direction(i, false);
			// check surroundings, if target is now seen
			Object obj = current_target[i];
			if (actions[i] = Action::CheckProwl)
				ran = true;
			if (is_item(obj))
				item_check(pawn, directions[i], ran);
			else if (is_plant(obj))
				search_plant_check(pawn, directions[i], ran);
			else if (is_scavengeable(obj))
				scavengeable_check(pawn, directions[i], ran);
			// TODO:: Fruit
			// TODO:: animal
			else if (is_tools(obj))
				tool_check(pawn);
			inertias[i] = calc_speed(mid_speed_pawn, coords[i]);
		}
		else if (actions[i] == Action::ApproachPlant ||
			 actions[i] == Action::ApproachTile ||
			 actions[i] == Action::ApproachTool ||
			 actions[i] == Action::ApproachItem)
		{
			std::pair<Direction, bool> next = next_direction_to_target(i);
			direction[i] = next.first;
			if (next.second)
			{
				move_in_direction(i, false);
				inertias[i] = calc_speed(min_speed_pawn, coords[i]);
			}
			else
			{
				if (actions[i] == Action::ApproachItem)
					take_item(i, coords[i]);
				else if (actions[i] == Action::ApproachPlant)
					harvest_plant(i, coords[i]);
				else if (actions[i] == Action::ApproachTile)
					harvest_tile(i, coords[i]);
				else if (actions[i] == Action::ApproachScavengeable)
					harvest_scavengeable(i, coords[i]);
				else if (actions[i] == Action::ApproachTool)
					take_tool(i, coords[i]);
				actions[i] = Action::Idle;
				decide_task(i);
			}
		} else if (actions[i] == Action::GetTool ||
			 actions[i] == Action::GetItem)
		{
			std::pair<Direction, bool> next = next_direction_to_target(i);
			direction[i] = next.first;
			if (next.second)
			{
				move_in_direction(i, false);
				inertias[i] = calc_speed(mid_speed_pawn, coords[i]);
				// promised versions, while approach is non-promise
				if (actions[i] == Action::GetItem)
					take_item(i, coords[i]);
				else
					take_tool(i, coords[i]);
				actions[i] = Action::Idle;
				find_promise.set();
			}
			else if (actions[i] == Action::Pursuit ||
				 actions[i] == Action::AnimalPursuit)
			{
				std::pair<Direction, bool> next = next_direction_to_moving_target(i);
				direction[i] = next.first;
				if (next.second)
					move_in_direction(i, false);
				else
				{
					if (actions[i] == Action::Pursuit)
					{
						// TODO: get new military target
						if (attack(i, current_dest[i], false, false))
							get_new_target();
					}
					// TODO: do this
					if (actions[i] == Action::AnimalPursuit)
						if (attack(i, current_dest[i], false, true))
							deal_with_game();
				}
				inertias[i] = calc_speed(max_speed_pawn, coords[i]);
			}
		}
