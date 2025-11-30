#include "objectData.hpp"
/*NOTE: all items stored in containers are also given as if they are not stored in a container. pawns will check whether there
 *is a container or not */

// hash grid
int cellSize = 25;

std::pair<int,int> ObjectDatabase::getGridCell(int x, int y) {
    return std::floor(x / cellSize), std::floor(x / cellSize);
}

std::pair<int,int> ObjectDatabase::getCenterPointInGridCell(int x, int y) {
    return {x * cellSize, y * cellSize};
}

//TODO: be sure this is not x and y inverse
std::pair<int, int> ObjectDatabase::getNthNearestGridCell(int x, int y, uint16_t n, int cellSize) {
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

void ObjectDatabase::preallocateSpace() {
    for (int x = 0; x < GRIDCELLNUM; x++) {
        for (int y = 0; y < GRIDCELLNUM; y++) {
            // 0 if out of discovery range
            // more or less for certain biomes
            // much more if player has moved there, and has more than certain number of pawns there. resize when pawn amount is above threshold
            globalMap[x][y].reserve(100);
        }
    }
}

void ObjectDatabase::addObject(Object object, int x, int y) {
    std::pair<int,int> gc = getGridCell(x, y);
    //TODO: consider checks
    globalMap[gc.first][gc.second][object].insert({x,y});
}

void ObjectDatabase::addObject(uint16_t objectIndex, ObjectType type, int x, int y) {
  
}

void ObjectDatabase::deleteObject(Object object, int x, int y) {
    std::pair<int,int> gc = getGridCell(x, y);
    globalMap[gc.first][gc.second][object].erase({x,y});

}

bool ObjectDatabase::checkEmptyTile(int tileIndex, int adjacentTileIndex) {

}

std::pair<int,int> ObjectDatabase::findNthNearestObject(Object object, int x, int y, uint8_t n) {
    //TODO: object count table for different object types, return false if object count is 0
    for (int i = 0; i < GRIDCELLCOUNT; i++) {
            std::pair<int,int> gc = getNthNearestGridCell();
            auto& cellSet = globalMap[gc.first][gc.second][object];
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

std::pair<int,int> ObjectDatabase::findNearestObject(Object object, int x, int y) {
    //TODO: producedInWorld counters, skip if = 0
    for (int i = 0; i < GRIDCELLCOUNT; i++) {
    std::pair<int,int> gc = getNearestGridCell(x, y);
    auto& cellSet = globalMap[gc.first][gc.second][object];
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

std::pair<int,int> ObjectDatabase::findNthNearestObject(Object object, int x, int y, int n) {
    for (int i = 0; i < GRIDCELLCOUNT; i++) {
    std::pair<int,int> gc = getNearestGridCell(x, y);
    auto& cellSet = globalMap[gc.first][gc.second][object];
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

// int findNearestObjectIndex(Object object, int x, int y) {
//     for (int i = 0; i < GRIDCELLCOUNT; i++) {
//     std::pair<int,int> gc = getNearestGridCell(x, y);

//     auto& cellSet = globalMap[gc.first][gc.second][object];
//     uint16_t closest = MAX;
//     int index = -1;
//     for (const auto& coord : cellSet) {
//         uint16_t temp = manDist(x, y, coord.get<0>, coord.get<1>);
//         if (temp < closest) {
//             closest = temp;
//             index = coord.get<2>;
//         }
//     }
//     }
//     if (index != -1) return index;
//     return -1;
// }

// std::tuple<int,int> findNearestObjectIndexCoord(Object object, int x, int y) {
//     for (int i = 0; i < GRIDCELLCOUNT; i++) {
//     std::pair<int,int> gc = getNearestGridCell(x, y);

//     auto& cellSet = globalMap[gc.first][gc.second][object];
//     uint16_t closest = MAX;
//     std::tuple<int,int,int> nearCoord = {-1,-1,-1};
//     for (const auto& coord : cellSet) {
//         uint16_t temp = manDist(x, y, coord.get<0>, coord.get<1>);
//         if (temp < closest) {
//             closest = temp;
//             nearCoord = coord;
//         }
//     }
//     }
//     if (closest != MAX) return nearCoord;
//     return {-1, -1};
// }

std::pair<int,int> ObjectDatabase::findNearestLiquidContainer(int x, int y) {
    std::pair<int,int> subject = {x,y};
    std::pair<int,int> closest = findNearestObject(Container::Pot, x, y);
    if (manDist(subject, closest) < manDist(findNearestObject(subject, Container::Bucket, x, y))) closest = findNearestObject(subject, Container::Bucket, x, y);
    if (manDist(subject, closest) < manDist(findNearestObject(subject, Container::LargePot, x, y))) closest = findNearestObject(subject, Container::LargePot, x, y);
    if (manDist(subject, closest) < manDist(findNearestObject(subject, Container::Kettle, x, y))) closest = findNearestObject(subject, Container::Kettle, x, y);
    if (manDist(subject, closest) < manDist(findNearestObject(subject, Container::Keg, x, y))) closest = findNearestObject(subject, Container::Keg, x, y);
    if (manDist(subject, closest) < manDist(findNearestObject(subject, Container::Jar, x, y))) closest = findNearestObject(subject, Container::Jar, x, y);
    return closest;
}

//NOTE: maybe prowl version, too
//TODO: needs work to ensure async functionality really works
void ObjectDatabase::findNecessaryTools(Action action, int pawn) {
    vector<int> foundToolReplaceables;
    for (int i = 0; i < actionToTools[static_cast<size_t>(action)].size(); i++) {
        //skip if pawn already has tool, replaceable equivalent has already been found, or tool is optional
        for (int j = 0; j < foundToolReplaceables.size(); j++)   if (foundToolReplaceables[j] == actionToTools[static_cast<size_t>(action)][i]) continue;

        for (int j = 0; j < tools[pawn].size(); j++)
            if (tools[pawn][j] == actionToTools[static_cast<size_t>(action)][i]) { foundToolsReplaceables.push_back(actionToToolsReplaceables[static_cast<size_t>(action)][i]);
                continue;
            }

        if (actionToTools[static_cast<size_t>(action)][i] < 0) continue;


        std:pair<int,int> dest = findNearestObject(actionToTools[static_cast<size_t>(action)][i], coords[pawn].first, coords[pawn].second);
        if (manDist(coords[pawn], dest) > midGatherRange) {
            dests[pawn] = tileIndices[dest];
            movingStatus[pawn] = MovingStatus::ApproachTool;
            //NOTE:: async
            findPromise[pawn] = std::promise<void>();
            findFuture[pawn] = findPromise[pawn].get_future();
        } else {
            //TODO:: "search home function", which checks if a pawn's home contains the necessary tools, giving user warning if not
            nextRole(pawn);
        }
    }
}

void ObjectDatabase::findNecessaryItems() {

}

