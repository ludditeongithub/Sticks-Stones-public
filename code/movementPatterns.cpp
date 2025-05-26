#include "movementPatterns.hpp"

int calcIntertia();

void moveInDirection(&std::pair<int,int> coord, Direction direction) {
    if (direction == Direction::North) coord.second += 1;
    else if (direction == Direction::South) coord.second -= 1;
    if (direction == Direction::East) coord.first += 1;
    else if (direction == Direction::West) coord.second -= 1;
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

    for (int i = -radius; i <= radius; ++i) {
        if (direction == Direction::Right) {
            int x = cx + radius - std::abs(i);
            int y = cy + i;
            edge.emplace_back(x, y);
        } else if (direction == Direction::Left) {
            int x = cx - radius + std::abs(i);
            int y = cy + i;
            edge.emplace_back(x, y);
        } else if (direction == Direction::Up) {
            int y = cy + radius - std::abs(i);
            int x = cx + i;
            edge.emplace_back(x, y);
        } else if (direction == Direction::Down) {
            int y = cy - radius + std::abs(i);
            int x = cx + i;
            edge.emplace_back(x, y);
        }
    }
    return edge;
}

//NOTE: maybe change this to be able to work for both males and females
void breedCheck(Animal animal, int maleIndex, int currentSight, Direction direction) {
    if (direction == Direction::NONE) std::vector<std::pair<int, int> de = getNewDiamond(x, y, currentSight);
    else std::vector<std::pair<int, int> de = getNewDiamondEdge(x, y, currentSight, direction);
    for (int x = 0; x < de.size(); x++) {
        if (animalIndices.find(de[x]) != animalIndices.end()) {
            int femaleIndex = animalIndices(de[x]);
            if (animals[femaleIndex] == animal && !animalSex[femaleIndex]) breed(maleIndex, femaleIndex);
        }
    }
}

//NOTE: consider corpse for animals
void huntCheck(Animal& huntList[], int pawnIndex, int currentSight, Direction direction, bool animal) {
    if (direction == Direction::NONE)
    std::vector<std::pair<int, int> de = getNewDiamondEdge(x, y, currentSight, direction);
    for (int x = 0; x < de.size(); x++) {
        for (int i = 0; i < huntList.size(); i++) {
            if (animalIndices.find(de[x]) != animalIndices.end()) {
                int animalIndex = animalIndices(de[x]);
            if (animals[animalIndex] == huntList[i]) {
                if (animal) {
                    attemptKill(pawnIndex, animalIndex, true, true);
                    animalMovingStatus[pawnIndex] = MovingStatus::Pursuit;
                } else {
                    meet(pawnIndex, animalIndices(de[x]), false, true, DelayedEvent::Hunting);
                    movingStatus[pawnIndex] = MovingStatus::Pursuit;
                }
            }
        }
    }
    }
}

void attack(int attackerIndex, int targetIndex, bool hunterAnimal, bool targetAnimal) {
    //move to target until adjacent
    //give up if slower, if no ranged weapon with ammo
    if (hunterAnimal) {
        animalHealth[targetIndex] -= getDamage[animals[attackerIndex]].damage;
    } else {
        if (targetAnimal) animalHealth[targetIndex] -= getDamage[attack[attackerIndex]].damage;
        health[targetIndex] -= getDamage[attack[attackerIndex]].damage;
    }
}

void movePawns() {
    for (int i = 0; i < currentCoords.size(); i++) {
        if (movingStatux[pawnIndex] == MovingStatus::Idle) {
            return;
        } else if (movingStatus[pawnIndex] == MovingStatus::Wander) {
            if (inertias[i] == 0) {
                directions[i] = getRandomAdjDirection(directions[i]);
                moveInDirection(directions[i]);
                inertias[i] = calcInertia(i);
            } else inertias[i]--;
        } else if (movingStatus[i] == MovingStatus::Prowl) {
            if (inertias[i] == 0) {
                if (rint(0,20) < 20) {
                    Direction temp = directions[i];
                    directions[i] = getRandomAdjDirection(directions[i]);
                    moveInDirection(directions[i]);
                }
                moveInDirection(directions[i]);
            } else inertias[i]--;
        }
    }
}
