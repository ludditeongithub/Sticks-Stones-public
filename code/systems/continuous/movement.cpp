#include "movement.hpp"

bool checkTileMovement(EntityID i, Array<FrameData>& frameDatas)
{
const ActState actState = frameDatas[i].get<ActState>();
switch (actState) {
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

void queueReadyActions(std::vector<EntityID>& buffer, Array<Time>& inertias)
{
		buffer.reserve(inertias.size);
		for (size_t i = 0; i < inertias.size; i++)
			if (inertias[i]-- <= 0)
					{
							buffer.emplace_back(i);							
					}
	buffer.shrink_to_fit();
}

// TODO: factor in hunger
// TODO: add to-do to go put away items to have necessary space for tools or
// items etc, when pawn goes to grab items
ActionEventDispatchBuffer& markActingEntities(std::vector<EntityID> &indices, Array<Animal>* animals, Array<Coord> &coords, Array<size_t>& targets, Array<Action>& actions, Array<FrameData>& frameDatas)
{		 
		bool ifAnimals = animals == nullptr;
		ActionEventDispatchBuffer buffer = ActionEventDispatchBuffer(indices.size(), ifAnimals);
	
	for (int j = 0; j < indices.size(); j++)
			{
					EntityID i = indices[j];
					const Action action = actions[i];
					if (action == Action::Idle || action == Action::Sleep) continue;
					if (action == Action::Prowl || action == Action::CheckProwl) buffer.checkNearTargets.push_back(i);
					if (action == Action::Prowl || action == Action::CheckProwl || action == Action::Wander) {						buffer.movingTiles.push_back(i);											
					} else if (action > Action::APPROACH_MIN && action < Action::APPROACH_MAX) {
							buffer.approachs.push_back(i);				   	} else if (action > Action::UNIT_MIN, Action::UNIT_MAX) {	
							buffer.units.push_back(i);	}       										    			 						
		}
	}
}	

	void moveAnimals()
	{
		for (int i = 0; i < animalCoords.size(); i++)
		{
			if (animalAction[i] == Action::Idle ||
			    animalAction[i] == Action::Sleep)
				continue;
			else if (inertias[i] > 0)
			{
				inertias--;
				continue;
			}
			else if (animalAction[i] == Action::Wander)
			{
				// NOTE: makes it stop a lot
				if (rint(0, 3) < 3)
					continue;
				directions[i] = getRandomAdjDirection(directions[i]);
				moveInDirection(i, true);
				inertias[i] = calcInertia(minSpeed[animals[i]], coords[i]);
				if (animalHunger[i] < maxHungerThreshold[animals[i]])
					animalAction[i] = Action::CheckProwl;
			}
			else if (animalAction[i] == Action::Prowl ||
				 animalAction[i] == Action::CheckProwl)
			{ // TODO: ProwlTile
				if (rint(0, 50) < 50)
					directions[i] = getRandomAdjDirection(directions[i]);
				moveInDirection(i, directions[i], true);
				// check surroundings, if target is now seen
				Object obj = currentTarget[i];
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
					inertias[i] = calcSpeed(maxSpeedPawn, coords[i]);
				}
			}
		}

		}			

void triggerMovements(std::vector<EntityID>& indices, Array<Coord>& coords, Array<FrameData>& frameDatas, Array<Animal>* animals)
{
		for (EntityID i = 0; i < indices.size(); i++) {
				coords[i].move(frameDatas[i].get<Direction>());
				
        }
}
