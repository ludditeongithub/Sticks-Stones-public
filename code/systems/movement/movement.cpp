#include "movement.hpp"
#include "core/data.hpp"
#include <optional>


template<typename DB>
void handle_pathsfinding_and_movement(DB& database, std::vector<EntityID> &actingEntities)
{
	std::vector<EntityID> newPathEntities =
			markNewPathEntities(actingEntities, database.frameDatas);
	setNewPaths(newPathEntities, database.coords, database.targets);
}

bool check_tile_movement(EntityID i, Array<FrameData>& frameDatas)
{
const ActState act_state = frameDatas[i].get<ActState>();
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
	
				if (animalAction[i] = Action::CheckProwl)
					ran = true;
				switch (diets[animals[i]])
				{
				case Diet::Herbivore:
				case Diet::Omnivore:
					ediblePlantCheck(i, directions[i], ran);
					fruitCheck(i, directions[i], ran);
				case Diet::Herbivore:
					break;
				case Diet::Scavenger:
					corpseCheck(i, directions[i], ran);
				case Diet::Carnivore:
					huntCheck(i, directions[i], ran);
				}
				inertias[i] = calcSpeed(midSpeed[animals[i]], coords[i]);
				else if (animalAction[i] == Action::ApproachPlant ||
					 animalAction[i] == Action::ApproachTile ||
					 animalAction[i] == Action::ApproachGrass ||
					 animalAction[i] == Action::ApproachFruit)
				{
					std::pair<Direction, bool> next = nextDirectionToTarget(i);
					direction[i] = next.first;
					if (next.second)
					{
						moveInDirection(i, false);
						inertias[i] = calcSpeed(minSpeedPawn, coords[i]);
					}
					else
					{
						if (actions[i] == Action::ApproachPlant)
							eatPlant(i, coords[i]);
						else if (actions[i] ==
							 Action::ApproachFruit)
							eatFruit(i, coords[i]);
						else if (actions[i] ==
							 Action::ApproachGrass)
							eatGrass(i, coords[i]);
						else if (actions[i] ==
							 Action::ApproachTile)
							animalDecideMovement(i);
					}
				}
				else if (actions[i] == Action::AnimalPursuit)
				{
					std::pair<Direction, bool> next =
					    nextDirectionToMovingTarget(i);
					direction[i] = next.first;
					if (next.second)
						moveInDirection(i, true);
					else
					{
						// TODO: do this
						if (actions[i] == Action::AnimalPursuit)
							if (attack(i, currentDest[i], false, true))
								eatCorpse(i);
					}
				}
        }

template <typename T>                                
void trigger_movements(Array<T>& types, std::vector<EntityID>& indices, Array<Coord>& coords, Array<FrameData>& frameDatas)
{
	for (EntityID i = 0; i < indices.size(); i++)
	{
          Direction direction = frameDatas[i].get<Direction>();
          g_Search->moveEntity(types[i], {indices[i], std::make_optional<Coord>(coords[i]), direction});	coords[i].move(direction);                
	}        
}

