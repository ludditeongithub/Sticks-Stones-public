#include "movement.hpp"
#include "data/types/aliases.hpp"
#include <optional>

bool check_tile_movement(EntityID i, Array<FrameData>& frame_datas)
{
const ActState act_state = frame_datas[i].get<ActState>();
switch (act_state) {
case ActState::Walk:
       	
       	break;
case ActState::Run:
       	
	    break;
case ActState::Act:
       	
       	break;
case ActState::NewPath:
       	
	    break;
default:
        
}
}

	void move_animals()
	{
	
				
				else if (animal_action[i] == Action::ApproachPlant ||
					 animal_action[i] == Action::ApproachTile ||
					 animal_action[i] == Action::ApproachGrass ||
					 animal_action[i] == Action::ApproachFruit)
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
						if (actions[i] == Action::ApproachPlant)
							eat_plant(i, coords[i]);
						else if (actions[i] ==
							 Action::ApproachFruit)
							eat_fruit(i, coords[i]);
						else if (actions[i] ==
							 Action::ApproachGrass)
							eat_grass(i, coords[i]);
						else if (actions[i] ==
							 Action::ApproachTile)
							animal_decide_movement(i);
					}
				}
				else if (actions[i] == Action::AnimalPursuit)
				{
					std::pair<Direction, bool> next =
					    next_direction_to_moving_target(i);
					direction[i] = next.first;
					if (next.second)
						move_in_direction(i, true);
					else
					{
						// TODO: do this
						if (actions[i] == Action::AnimalPursuit)
							if (attack(i, current_dest[i], false, true))
								eat_corpse(i);
					}
				}
        }

template <typename T>                                
void trigger_movements(Array<T>& types, std::vector<EntityID>& indices, Array<Coord>& coords, Array<FrameData>& frame_datas)
{
	for (EntityID i = 0; i < indices.size(); i++)
	{
          Direction direction = frame_datas[i].get<Direction>();
          g_Search->move_entity(types[i], {indices[i], std::make_optional<Coord>(coords[i]), direction});	coords[i].move(direction);                
	}        
}

