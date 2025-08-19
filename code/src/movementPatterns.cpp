#include "movementPatterns.hpp"
//TODO: trees and other large items block visibility

//raw inertia value
int getInertia(std::pair<int,int> coord, Direction direction) {

}

uint16_t calcInertia(float objectInertia, std::pair<int,int> coord) {
    return static_cast<int>(objectInertia * tileInertias[tileTypes[tileIndices(coord)]]);
}

std::pair<int, int> getMoveTimeAndTileIndex(Direction direction) {
	switch (direction) {
                case Direction::Up:  //up
                    return {adjacentTilesCost[index].up, adjacentTilesIndices[index].up};
                case Direction::Down:  //down
                    return {adjacentTilesCost[index].down, adjacentTilesIndices[index].down};
                case Direction::Left:  //left
                    return {adjacentTilesCost[index].left, adjacentTilesIndices[index].left};
                case Direction::Right:  //right
                    return {adjacentTilesCost[index].right, adjacentTilesIndices[index].right};
            }
	return {-1,-1};
}


//TODO: factor in hunger
//TODO: add to-do to go put away items to have necessary space for tools or items etc, when pawn goes to grab items
void movePawns() {
    //TODO: reverse order every tick, so interactions are balanced
    for (int i = 0; i < currentCoords.size(); i++) {
        if (movingStatus[i] == MovingStatus::Idle || movingStatus[i] == MovingStatus::Sleeping)  continue;
        else if (inertias[i] > 0) {
            inertias[i]--;
            continue;
        } else if (movingStatus[i] == MovingStatus::Wander) {
                directions[i] = getRandomAdjDirection(directions[i]);
                moveInDirection(i, false);
                inertias[i] = calcInertia(minSpeedPawn, currentCoords[i]);
        } else if (movingStatus[i] == MovingStatus::Prowl || movingStatus[i] == MovingStatus::CheckProwl) { //TODO: ProwlTile
                    if (rint(0,50) < 50) directions[i] = getRandomAdjDirection(directions[i]);
                    moveInDirection(i, false);
                    //check surroundings, if target is now seen
                    Object obj = currentTarget[i];
                    if (movingStatus[i] = MovingStatus::CheckProwl) ran = true;
                    if (isItem(obj)) itemCheck(pawn, directions[i], ran);
                    else if (isPlant(obj)) searchPlantCheck(pawn, directions[i], ran);
                    else if (isScavengeable(obj)) scavengeableCheck(pawn, directions[i], ran);
                    //TODO:: Fruit
                    //TODO:: animal
                    else if (isTools(obj)) toolCheck(pawn);
                inertias[i] = calcSpeed(midSpeedPawn, currentCoords[i]);
        } else if (movingStatus[i] == MovingStatus::ApproachPlant || movingStatus[i] == MovingStatus::ApproachTile || movingStatus[i] == MovingStatus::ApproachTool || movingStatus[i] == MovingStatus::ApproachItem) {
                std::pair<Direction, bool> next = nextDirectionToTarget(i);
                currentDirection[i] = next.first;
                if (next.second) {
                    moveInDirection(i, false);
                    inertias[i] = calcSpeed(minSpeedPawn, currentCoords[i]);
                } else {
                    if (movingStatus[i] == MovingStatus::ApproachItem) takeItem(i, currentCoords[i]);
                    else if (movingStatus[i] == MovingStatus::ApproachPlant) harvestPlant(i, currentCoords[i]);
                    else if (movingStatus[i] == MovingStatus::ApproachTile) harvestTile(i, currentCoords[i]);
                    else if (movingStatus[i] == MovingStatus::ApproachScavengeable) harvestScavengeable(i, currentCoords[i]);
                    else if (movingStatus[i] == MovingStatus::ApproachTool) takeTool(i, currentCoords[i]);
                    movingStatus[i] = MovingStatus::Idle;
                    decideTask(i);
                }
            } else if (movingStatus[i] == MovingStatus::GetTool || movingStatus[i] == MovingStatus::GetItem) {
                std::pair<Direction, bool> next = nextDirectionToTarget(i);
                currentDirection[i] = next.first;
                if (next.second) {
                    moveInDirection(i, false);
                    inertias[i] = calcSpeed(midSpeedPawn, currentCoords[i]);
                //promised versions, while approach is non-promise
                    if (movingStatus[i] == MovingStatus::GetItem) takeItem(i, currentCoords[i]);
                    else takeTool(i, currentCoords[i]);
                    movingStatus[i] = MovingStatus::Idle;
                    findPromise.set();
            } else if (movingStatus[i] == MovingStatus::Pursuit || movingStatus[i] == MovingStatus::AnimalPursuit) {
                std::pair<Direction, bool> next = nextDirectionToMovingTarget(i);
                currentDirection[i] = next.first;
                if (next.second) moveInDirection(i, false);
                else {
                    if (movingStatus[i] == MovingStatus::Pursuit) {
                        //TODO: get new military target
                        if (attack(i, currentDest[i], false, false)) getNewTarget();
                    }
                    //TODO: do this
                 if (movingStatus[i] == MovingStatus::AnimalPursuit) if (attack(i, currentDest[i], false, true)) dealWithGame();
                }
                inertias[i] = calcSpeed(maxSpeedPawn, currentCoords[i]);
        }
    }
}



void moveAnimals() {
    for (int i = 0; i < animalCoords.size(); i++) {
        if (animalMovingStatus[i] == MovingStatus::Idle || animalMovingStatus[i] == MovingStatus::Sleeping) continue;
         else if (inertias[i] > 0) {
            inertias--;
            continue;
        } else if (animalMovingStatus[i] == MovingStatus::Wander) {
                //NOTE: makes it stop a lot
                if (rint(0,3) < 3) continue;
                directions[i] = getRandomAdjDirection(directions[i]);
                moveInDirection(i, true);
                inertias[i] = calcInertia(minSpeed[animals[i]], currentCoords[i]);
                if (animalHunger[i] < maxHungerThreshold[animals[i]]) animalMovingStatus[i] = MovingStatus::CheckProwl;
        } else if (animalMovingStatus[i] == MovingStatus::Prowl || animalMovingStatus[i] == MovingStatus::CheckProwl) { //TODO: ProwlTile
                    if (rint(0,50) < 50) directions[i] = getRandomAdjDirection(directions[i]);
                    moveInDirection(i, directions[i], true);
                    //check surroundings, if target is now seen
                    Object obj = currentTarget[i];
                    if (animalMovingStatus[i] = MovingStatus::CheckProwl) ran = true;
                    switch (diets[animals[i]]) {
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
                    inertias[i] = calcSpeed(midSpeed[animals[i]], currentCoords[i]);
     else if (animalMovingStatus[i] == MovingStatus::ApproachPlant || animalMovingStatus[i] == MovingStatus::ApproachTile || animalMovingStatus[i] == MovingStatus::ApproachGrass  || animalMovingStatus[i] == MovingStatus::ApproachFruit) {
                std::pair<Direction, bool> next = nextDirectionToTarget(i);
                currentDirection[i] = next.first;
                if (next.second) {
                    moveInDirection(i, false);
                    inertias[i] = calcSpeed(minSpeedPawn, currentCoords[i]);
                } else {
                    if (movingStatus[i] == MovingStatus::ApproachPlant) eatPlant(i, currentCoords[i]);
                    else if (movingStatus[i] == MovingStatus::ApproachFruit) eatFruit(i, currentCoords[i]);
                    else if (movingStatus[i] == MovingStatus::ApproachGrass) eatGrass(i, currentCoords[i]);
                    else if (movingStatus[i] == MovingStatus::ApproachTile) animalDecideMovement(i);
                }
    } else if (movingStatus[i] == MovingStatus::AnimalPursuit) {
                std::pair<Direction, bool> next = nextDirectionToMovingTarget(i);
                currentDirection[i] = next.first;
                if (next.second) moveInDirection(i, true);
                else {
                    //TODO: do this
                    if (movingStatus[i] == MovingStatus::AnimalPursuit) if (attack(i, currentDest[i], false, true)) eatCorpse(i);
                }
                inertias[i] = calcSpeed(maxSpeedPawn, currentCoords[i]);
        }
    }
}

