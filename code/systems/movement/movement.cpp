#include "movement.hpp"


template<typename DB>
void handlePathsfindingAndMovement(DB& database, std::vector<EntityID> &actingEntities)
{
	std::vector<EntityID> newPathEntities =
			markNewPathEntities(actingEntities, database.frameDatas);
	setNewPaths(newPathEntities, database.coords, database.targets);
}

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

	void moveAnimals()
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

void triggerMovements(std::vector<EntityID>& indices, Array<Coord>& coords, Array<FrameData>& frameDatas)
{
		for (EntityID i = 0; i < indices.size(); i++) coords[i].move(frameDatas[i].get<Direction>());				        
}

