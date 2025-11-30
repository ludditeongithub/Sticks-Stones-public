#include "../include/basic.hpp"
#include "../include/categories.hpp"
#include "../include/unit.hpp"

//NOTE: may not work
Direction checkIfAdjTarget(int pawn) {
    std::pair<int,int> coords = coords[pawn];
    Object obj;
    for (int i = 0; i < 4; i++) {
        switch (i) {
            case 0:
                obj = tileObject[tileIndices[{coords.x+1, coords.y}]];
                d = Direction::East;
                break;
            case 1:
                obj = tileObject[tileIndices[{coords.x-1, coords.y}]];
                d = Direction::West;
                break;
            case 2:
                obj = tileObject[tileIndices[{coords.x, coords.y+1}]];
                d = Direction::North;
                break;
            case 3:
                obj = tileObject[tileIndices[{coords.x, coords.y-1}]];
                d = Direction::South;
        }
    std::visit(
    [](const auto& left, const auto& right) {
        return left == right;
    },
    currentTarget[index], obj) {
        return d;
    }
    }
    return Direction::NONE;
}

void moveInDirection(int pawn, bool animal) {
    Direction direction = currentDirection[pawn];
    if (animal) {
        Animal entity = animals[pawn];
        deleteObject(entity, animalCoords[pawn].first, animalCoords[pawn].second);
        if (direction == Direction::North) animalCoords[pawn].second += 1;
        else if (direction == Direction::South) animalCoords[pawn].second -= 1;
        if (direction == Direction::East) animalCoords[pawn].first += 1;
        else if (direction == Direction::West) animalCoords[pawn].first -= 1;
        insertObject(entity, animalCoords[pawn].first, animalCoords[pawn].second);
    } else {
        if (direction == Direction::North) coords[pawn].second += 1;
        else if (direction == Direction::South) coords[pawn].second -= 1;
        if (direction == Direction::East) coords[pawn].first += 1;
        else if (direction == Direction::West) coords[pawn].first -= 1;
        currentIndices[coords[pawn]] = pawn;
    }
}

//NOTE: this is brute force greedy move. change if becomes to inefficient to mix of shortest path, but only as far as animal could realistically calculate and see
//
//right now, tells you direction and if you should move (if you have reached target)
// for when dest is tile
std::pair<Direction, bool> nextDirectionToTarget(int pawnIndex) {
    if (adjCheckTile(coords[pawnIndex], dest[pawnIndex]) != Direction::NONE) return {adjCheckTile(coords[pawnIndex], dest[pawnIndex]), false};
    Direction direction = Direction::NONE;
    int dx = tileCoords[dest[pawnIndex]].first - coords[pawnIndex].first;
    int dy = tileCoords[dest[pawnIndex]].second - coords[pawnIndex].second;
    if (dx > 0) {
        direction = Direction::West;
    } else {
        direction = Direction::East;
    } else if (dy > 0) {
        if (getInertia(coords, Direcion::North)  < getInertia(coords, direction))
        direction = Direction::North;
    } else {
        if (getInertia(coords, Direcion::South)  < getInertia(coords, direction))
        direction = Direction::South;
    }
    return {direction, true};
}

//for when dest is animal or human
std::pair<Direction, bool> nextDirectionToMovingTarget(int pawnIndex, bool animal) {
    if (animal) {
        int targetIndex = tileIndices[animalCoords[dest[i]]];
    } else int targetIndex = tileIndices[coords[dest[i]]];

    if (adjCheckTile(coords[pawnIndex], targetIndex) != Direction::NONE) return {adjCheckTile(coords[pawnIndex], targetIndex), false};

      Direction direction = Direction::NONE;
    int dx = dest[pawnIndex].first - coords[pawnIndex].first;
    int dy = dest[pawnIndex].second - coords[pawnIndex].second;
    if (dx > 0) {
        direction = Direction::West;
    } else {
        direction = Direction::East;
    } else if (dy > 0) {
        if (getInertia(coords, Direcion::North)  < getInertia(coords, direction))
        direction = Direction::North;
    } else {
        if (getInertia(coords, Direcion::South)  < getInertia(coords, direction))
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
                    dest[pawnIndex] = animalIndex;
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
        int index = tileIndices(de[x]);
        if !(isPlant(tileObject[index])) continue;
        for (int i = 0; i < herbivoreDiet.size(); i++) {
            if (tileObject[index] == herbivoreDiet[i]) {
                animalDest[animalIndex] = index;
                animalMovingStatus[animalIndex] = MovingStatus::ApproachPlant;
            }
        }
    }
}

void fruitCheck(int animalIndex, Direction direction, bool total) {
    if (total) std::vector<std::pair<int, int> de = getDiamond(x, y,, direction);
     std::vector<std::pair<int, int> de = getNewDiamondEdge(x, y, sightRanges[animals[animalIndex]], direction);
    for (int x = 0; x < de.size(); x++) {
        int index = tileIndices(de[x]);
        if !(isFruit(tileObject[index])) continue;
        for (int i = 0; i < static_cast<int>(Fruit::MAX); i++) {
            if (tileObject[index] == static_cast<Fruit>(i)) {
                animalDest[animalIndex] = index;
                animalMovingStatus[animalIndex] = MovingStatus::ApproachFruit;
            }
        }
    }
}

//TODO: need to finish this
void searchPlantCheck(int pawn, Direction direction, bool total) {
    if (total) std::vector<std::pair<int, int> de = getDiamond(x, y, humanSight, direction);
     std::vector<std::pair<int, int> de = getNewDiamondEdge(x, y, humanSight, direction);

    for (int x = 0; x < de.size(); x++) {
        int index = tileIndices(de[x]);
        if !(isPlant(tileObject[index])) continue;
        for (int i = 0; i < .size(); i++) {
            if (tileObject[index] == herbivoreDiet[i]) {
                dest[pawn] = index;
                movingStatus[pawn] = MovingStatus::ApproachPlant;
            }
        }
    }
}

//NOTE: this might not work if objects cannot be compared; maybe should have differnt one for approachitem
void itemCheck(int pawn, Direction direction, bool total) {
    if (total) std::vector<std::pair<int, int> de = getDiamond(x, y, humanSight, direction);
    std::vector<std::pair<int, int> de = getNewDiamondEdge(x, y, humanSight, direction);
    for (int x = 0; x < de.size(); x++) {
        int index = tileIndices(de[x]);
        if (tileObject[index] == currentTarget[pawn]) {
            dest[pawn] = index;
            movingStatus[pawn] = MovingStatus::GetItem;
        }
    }
}

void scavengeableCheck(int pawn, Direction direction, bool total) {
    if (total) std::vector<std::pair<int, int> de = getDiamond(x, y, humanSight, direction);
    std::vector<std::pair<int, int> de = getNewDiamondEdge(x, y, humanSight, direction);
    for (int x = 0; x < de.size(); x++) {
        int index = tileIndices(de[x]);
        if (tileObject[index] == currentTarget[pawn]) {
            dest[pawn] = index;
            movingStatus[pawn] = MovingStatus::ApproachScavengeable;
        }
    }
}
