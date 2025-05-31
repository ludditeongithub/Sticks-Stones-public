#include "objectLocation.hpp"
/*NOTE: all items stored in containers are also given as if they are not stored in a container. pawns will check whether there
 *is a container or not */

// hash grid
int cellSize = 25;

std::pair<int,int> getGridCell(int x, int y) {
    return std::floor(x / cellSize), std::floor(x / cellSize);
}

std::pair<int,int> getCenterPointInGridCell(int x, int y) {
    return {x * cellSize, y * cellSize};
}

//TODO: be sure this is not x and y inverse
std::pair<int, int> getNthNearestGridCell(int x, int y, uint16_t n, int cellSize) {
    int gx = x / cellSize;
    int gy = y / cellSize;

    if (n == 0) return {gx, gy};

    int ring = 1;
    int count = 0;

    while (true) {
        int cx = gx - ring;
        int cy = gy - ring;

        // go right
        for (int i = 0; i < 2 * ring; ++i) {
            if (++count == n) return {cx + i, cy};
        }
        // go down
        for (int i = 1; i <= 2 * ring; ++i) {
            if (++count == n) return {cx + 2 * ring, cy + i};
        }
        // go left
        for (int i = 1; i <= 2 * ring; ++i) {
            if (++count == n) return {cx + 2 * ring - i, cy + 2 * ring};
        }
        // go up
        for (int i = 1; i < 2 * ring; ++i) {
            if (++count == n) return {cx, cy + 2 * ring - i};
        }
        ++ring;
    }
}



using std::variant<Object, Plant, Animal, Pawn> Entity;
std::vector<std::vector<absl::flat_hash_map<Entity, absl::flat_hash_set<std::pair<int,int>>>>> globalMap;

void preallocateSpace() {
    for (int x = 0; x < GRIDCELLNUM; x++) {
        for (int y = 0; y < GRIDCELLNUM; y++) {
            // 0 if out of discovery range
            // more or less for certain biomes
            // much more if player has moved there, and has more than certain number of pawns there. resize when pawn amount is above threshold
            globalMap[x][y].reserve(100);
        }
    }
}

void insertEntity(Entity entity, int x, int y, int i) {
    std::pair<int,int> gc = getGridCell(x, y);
    //TODO: consider checks
    globalMap[gc.first][gc.second][entity].insert({x,y,i});
}

void deleteEntity(Entity entity, int x, int y, int i) {
    std::pair<int,int> gc = getGridCell(x, y);
    globalMap[gc.first][gc.second][entity].erase({x,y,i});

}

bool checkEmptyTile(int tileIndex, int adjacentTileIndex) {

}

std::pair<int,int> findNthNearestEntity(Entity entity, int x, int y, uint8_t n) {
    //TODO: entity count table for different entity types, return false if entity count is 0
    for (int i = 0; i < GRIDCELLCOUNT; i++) {
            std::pair<int,int> gc = getNthNearestGridCell();
            auto& cellSet = globalMap[gc.first][gc.second][entity];
    uint16_t closest = 999999999;
    int nearCoord = {-1,-1};
    for (const auto& coord : cellSet) {
        uint16_t temp = manDist(x, y, coord.get<0>, coord.get<1>);
        if (temp < closest) {
            closest = temp;
            nearCoord = {coord.get<0>, coord.get<1>};
        }
    }
    if (nearCoord != {-1, -1}) return nearCoord;
    }
    return {-1, -1};
}

std::pair<int,int> findNearestEntity(Entity entity, int x, int y) {
    //TODO: producedInWorld counters, skip if = 0
    for (int i = 0; i < GRIDCELLCOUNT; i++) {
    std::pair<int,int> gc = getNearestGridCell(x, y);
    auto& cellSet = globalMap[gc.first][gc.second][entity];
    uint16_t closest = 999999999;
    int nearCoord = {-1,-1};
    for (const auto& coord : cellSet) {
        uint16_t temp = manDist(x, y, coord.get<0>, coord.get<1>);
        if (temp < closest) {
            closest = temp;
            nearCoord = {coord.get<0>, coord.get<1>};
        }
    }
    if (nearCoord != {-1, -1}) return nearCoord;
    }
    return {-1, -1};
}

std::pair<int,int> findNthNearestEntity(Entity entity, int x, int y, int n) {
    for (int i = 0; i < GRIDCELLCOUNT; i++) {
    std::pair<int,int> gc = getNearestGridCell(x, y);
    auto& cellSet = globalMap[gc.first][gc.second][entity];
    uint16_t closest = 999999999;
    int nearCoord = {-1,-1};
    for (const auto& coord : cellSet) {
        uint16_t temp = manDist(x, y, coord.get<0>, coord.get<1>);
        if (temp < closest) {
            closest = temp;
            nearCoord = {coord.get<0>, coord.get<1>};
        }
    }
    if (nearCoord != {-1, -1}) return nearCoord;
    }
    return {-1, -1};
}

int findNearestEntityIndex(Entity entity, int x, int y) {
    for (int i = 0; i < GRIDCELLCOUNT; i++) {
    std::pair<int,int> gc = getNearestGridCell(x, y);

    auto& cellSet = globalMap[gc.first][gc.second][entity];
    uint16_t closest = MAX;
    int index = -1;
    for (const auto& coord : cellSet) {
        uint16_t temp = manDist(x, y, coord.get<0>, coord.get<1>);
        if (temp < closest) {
            closest = temp;
            index = coord.get<2>;
        }
    }
    }
    if (index != -1) return index;
    return -1;
}

std::tuple<int,int> findNearestEntityIndexCoord(Entity entity, int x, int y) {
    for (int i = 0; i < GRIDCELLCOUNT; i++) {
    std::pair<int,int> gc = getNearestGridCell(x, y);

    auto& cellSet = globalMap[gc.first][gc.second][entity];
    uint16_t closest = MAX;
    std::tuple<int,int,int> nearCoord = {-1,-1,-1};
    for (const auto& coord : cellSet) {
        uint16_t temp = manDist(x, y, coord.get<0>, coord.get<1>);
        if (temp < closest) {
            closest = temp;
            nearCoord = coord;
        }
    }
    }
    if (closest != MAX) return nearCoord;
    return {-1, -1};
}

std::pair<int,int> findNearestLiquidContainer(int x, int y) {
    std::pair<int,int> subject = {x,y};
    std::pair<int,int> closest = findNearestEntity(Container::Pot, x, y);
    if (manDist(subject, closest) < manDist(findNearestEntity(subject, Container::Bucket, x, y))) closest = findNearestEntity(subject, Container::Bucket, x, y);
    if (manDist(subject, closest) < manDist(findNearestEntity(subject, Container::LargePot, x, y))) closest = findNearestEntity(subject, Container::LargePot, x, y);
    if (manDist(subject, closest) < manDist(findNearestEntity(subject, Container::Kettle, x, y))) closest = findNearestEntity(subject, Container::Kettle, x, y);
    if (manDist(subject, closest) < manDist(findNearestEntity(subject, Container::Keg, x, y))) closest = findNearestEntity(subject, Container::Keg, x, y);
    if (manDist(subject, closest) < manDist(findNearestEntity(subject, Container::Jar, x, y))) closest = findNearestEntity(subject, Container::Jar, x, y);
    return closest;
}

        //bool is whether still processing or not. only counts ones filled with actual liquid
std::unordered_map[std::pair<int,int>, std::pair<bool, Item>] filledLiquidContainers();

void findNeccessaryTools(Action action, int pawn) {
    for (int i = 0; i < actionToTools[static_cast<size_t>(action)]; i++) {
        std:pair<int,int> dest = findNearestEntity(actionToTools[static_cast<size_t>(action)][i], currentCoords[pawn].first, currentCoords[pawn].second);
        if (manDist(currentCoords[pawn], dest) > midGatherRange) {
            currentDests[pawn] = tileIndices[dest];
            movingStatus[pawn] = MovingStatus::ApproachTool;
            std::promise<Tool> neededTool;
            std::future<Tool> toolPicked = neededTool.get_future();
        }
}
