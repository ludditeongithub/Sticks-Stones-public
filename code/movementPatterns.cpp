#include "movementPatterns.hpp"

//raw inertia value
int getInertia(std::pair<int,int> coord, Direction direction) {

}

uint16_t calcInertia(float entityInertia, std::pair<int,int> coord) {
    return static_cast<int>(entityInertia * tileInertias[tileTypes[tileIndices(coord)]]);
}

// true if killed, false if not
bool attack(int attackerIndex, int targetIndex, bool hunterAnimal, bool targetAnimal) {
    if (hunterAnimal) {
        animalHealth[targetIndex] -= getDamage[animals[attackerIndex]].damage;
    } else {
        if (targetAnimal) animalHealth[targetIndex] -= getDamage[damage[attackerIndex]].damage;
        health[targetIndex] -= getDamage[damage[attackerIndex]].damage;
    }
}

void eatPlant(int animalIndex, int plantIndex) {
    Plant& plant = plantCoords[plantIndex];
    animalHunger[animalIndex] -= plantHunger[plant];
    animalMovingStatus[animalIndex] = MovingStatus::Idle;
    addEvent(plantEatTime[plant], EventType::MoveStart, 0, static_cast<int>(MovingStatus::Wander));
}


void moveInDirection(&std::pair<int,int> coord, Direction direction) {
    if (direction == Direction::North) coord.second += 1;
    else if (direction == Direction::South) coord.second -= 1;
    if (direction == Direction::East) coord.first += 1;
    else if (direction == Direction::West) coord.first -= 1;
}

//NOTE: this is very brute force greedy move. change if becomes to inefficient to mix of shortest path, but only as far as animal could realistically calculate and see
//
//right now, tells you direction and if you should move
std::pair<Direction, bool> nextDirectionToTarget(int pawnIndex) {
    if (adjCheckTile(currentCoords[pawnIndex], currentDest[pawnIndex]) != Direction::NONE) return {adjCheckTile(currentCoords[pawnIndex], currentDest[pawnIndex]), false};
    Direction direction;
    int dx = currentDest[pawnIndex].first - currentCoords[pawnIndex].first;
    int dy = currentDest[pawnIndex].second - currentCoords[pawnIndex].second;
    if (dx > 0) {
        direction = Direction::West;
    } else {
        direction = Direction::East;
    } else if (dy > 0) {
        if (getInertia(currentCoords, Direcion::North)  < getInertia(currentCoords, direction))
        direction = Direction::North;
    } else {
        if (getInertia(currentCoords, Direcion::South)  < getInertia(currentCoords, direction))
        direction = Direction::South;
    }
    return {direction, true};
}

std::vector<std::pair<int, int>> getDiamond(int cx, int cy, int radius) {
    std::vector<std::pair<int, int>> result;

    for (int dx = -radius; dx <= radius; ++dx) {
        int maxDy = radius - std::abs(dx);
        for (int dy = -maxDy; dy <= maxDy; ++dy) {
            int x = cx + dx;
            int y = cy + dy;
            result.emplace_back(x, y);
        }
    }

    return result;
}

std::vector<std::pair<int, int>> getNewDiamondEdge(int cx, int cy, int radius, Direction direction) {
    std::vector<std::pair<int, int>> edge;

    //LAYER 1 to LAYER 2
    for (int l = 0; l < 2; l++) {
    for (int i = -radius; i <= radius; ++i) {
        if (direction == Direction::Right) {
            int x = cx + radius - std::abs(i - l);
            int y = cy + i;
            edge.emplace_back(x, y);
        } else if (direction == Direction::Left) {
            int x = cx - radius + std::abs(i - l);
            int y = cy + i;
            edge.emplace_back(x, y);
        } else if (direction == Direction::Up) {
            int y = cy + radius - std::abs(i - l);
            int x = cx + i;
            edge.emplace_back(x, y);
        } else if (direction == Direction::Down) {
            int y = cy - radius + std::abs(i - l);
            int x = cx + i;
            edge.emplace_back(x, y);
        }
    }
}
    return edge;
}

//NOTE: maybe change this to be able to work for both males and females
void breedCheck(Animal animal, int maleIndex,  Direction direction, bool total) {
    if (total) std::vector<std::pair<int, int> de = getDiamond(x, y,, direction);
    else std::vector<std::pair<int, int> de = getNewDiamondEdge(x, y, sightRanges[animal], direction);
    for (int x = 0; x < de.size(); x++) {
        if (animalIndices.find(de[x]) != animalIndices.end()) {
            int femaleIndex = animalIndices(de[x]);
            if (animals[femaleIndex] == animal && !animalSex[femaleIndex]) {
                animalDest[maleIndex] = femaleIndex;
            animalMovingStatus[pawnIndex] = MovingStatus::BreedPursuit;
            }
        }
    }
}

//NOTE: consider corpse for animals
void huntCheck(Animal& huntList[], int pawnIndex, Direction direction, bool animal, bool total) {
    if (animal) int sightRange =  sightRanges[Animal[pawnIndex]];
    else int sightRange = humanSight;
    if (total) std::vector<std::pair<int, int> de = getDiamond(x, y,, direction);
    else std::vector<std::pair<int, int> de = getNewDiamondEdge(x, y,, direction);
    for (int x = 0; x < de.size(); x++) {
        for (int i = 0; i < huntList.size(); i++) {
            if (animalIndices.find(de[x]) != animalIndices.end()) {
                int animalIndex = animalIndices(de[x]);
            if (animals[animalIndex] == huntList[i]) {
                if (animal) {
                animalDest[pawnIndex] = animalIndex;
                 animalMovingStatus[pawnIndex] = MovingStatus::AnimalPursuit;
                } else {
                    currentDest[pawnIndex] = animalIndex;
                    movingStatus[pawnIndex] = MovingStatus::AnimalPursuit;
                }
            }
        }
    }
    }
}

void ediblePlantCheck(int animalIndex, Direction direction, bool total) {
    if (total) std::vector<std::pair<int, int> de = getDiamond(x, y,, direction);
     std::vector<std::pair<int, int> de = getNewDiamondEdge(x, y, sightRanges[animals[animalIndex]], direction);
    for (int x = 0; x < de.size(); x++) {
        for (int i = 0; i < herbivoreDiet.size(); i++) {
            int index = tileIndices(de[x]);
            if (tileObject[index] == herbivoreDiet[i]) {
                animalDest[animalIndex] = index;
                animalMovingStatus[animalIndex] = MovingStatus::PlantApproach;
            }
        }
    }
}

void takeTool(int unit, std::pair<int,int> coord) {
    tools[]
}

//TODO: factor in hunger
//TODO: add to-do to go put away items to have necessary space for tools or items etc, when pawn goes to grab items
void movePawns() {
    for (int i = 0; i < currentCoords.size(); i++) {
        if (movingStatus[pawnIndex] == MovingStatus::Idle || movingStatus[pawnIndex] == MovingStatus::Sleeping) {
            return;
        } else if (movingStatus[pawnIndex] == MovingStatus::Wander) {
            if (inertias[i] == 0) {
                directions[i] = getRandomAdjDirection(directions[i]);
                moveInDirection(directions[i]);
                inertias[i] = calcInertia(minSpeed[animals[i]], currentCoords[i]);
            } else inertias[i]--;
        } else if (movingStatus[i] == MovingStatus::Prowl) {
            if (inertias[i] == 0) {
                if (rint(0,20) < 20) {
                    Direction temp = directions[i];
                    directions[i] = getRandomAdjDirection(directions[i]);
                    moveInDirection(directions[i]);
                    }
                moveInDirection(directions[i]);
                if (animalHunger[i] < maxHungerThreshold[animals[i]]) {
                    switch (diets[animals[i]]) {
                        case Diet::Herbivore:
                        case Diet::Omnivore:
                            ediblePlantCheck(i, directions[i], false);
                        case Diet::Herbivore:
                            break;
                        case Diet::Carnivore:
                            huntCheck(i, directions[i], false);
                    }
                }
                inertias[i] = calcSpeed(midSpeedPawn, currentCoords[i]);
            } else inertias[i]--;
        } else if (movingStatus[i] == MovingStatus::Sprint) {
            if (inertias[i] == 0) {

            }
        } else if (movingStatus[i] == MovingStatus::ApproachPlant || movingStatus[i] == MovingStatus::ApproachTile || movingStatus[i] == MovingStatus::ApproachTool || movingStatus[i] == MovingStatus::) {
            if (inertias[i] == 0) {
                std::pair<Direction, bool> next = nextDirectionToTarget(currentCoords[i], currentDests[i]);
                currentDirection[i] = next.first;
                if (next.second) {
                    moveInDirection[currentDirection[i]];
                    inertias[i] = calcSpeed(midSpeedPawn, currentCoords[i]);
                } else {
                    //TODO: ensure plants are fully grown when this moving status is given
                    if (movingStatus[i] == MovingStatus::ApproachPlant) harvestPlant(currentCoords[i]);
                    else if (movingStatus[i] == MovingStatus::ApproachTile) harvestTile(currentCoords[i]);
                    else if (movingStatus[i] == MovingStatus::ApproachScavengeable) harvestScavengeable(currentCoords[i]);
                    else if (movingStatus[i] == MovingStatus::ApproachTool) takeTool(currentCoords[i]);
            } else inertias[i]--;
            } else if (movingStatus[i] == MovingStatus::Pursuit || movingStatus[i] == MovingStatus::AnimalPursuit) {
            if (inertias[i] == 0) {
                std::pair<Direction, bool> next = nextDirectionToTarget(currentCoords[i], currentDest[i]);
                currentDirection[i] = next.first;
                if (next.second) moveInDirection[currentDirection[i]];
                else {
                    if (movingStatus[i] == MovingStatus::Pursuit) {
                        //TODO: get new military target
                        if (attack(i, currentDest[i], false, false)) getNewTarget();
                    }
                    //TODO: do this
                 if (movingStatus[i] == MovingStatus::AnimalPursuit) if (attack(i, currentDest[i], false, true)) dealWithGame();
                }
                inertias[i] = calcSpeed(maxSpeedPawn, currentCoords[i]);
            } else inertias[i]--;
        }
    }
}
