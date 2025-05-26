#include "basic.hpp"
#include "tile.hpp"
#include "categories.hpp"
#include "animal.hpp"

float maxAltChange = 2.0;

enum class Direction {
    NONE, North, South, West, East,
};

std::vector<std::pair<int, int>> directions = {
    {-1, 0}, {1, 0}, {0, -1}, {0, 1}
};

template <typename T>
bool isInPath(const T& map, std::pair<int,int> start, std::pair<int,int> end, const int obstacle) {
    int dx = abs(end.second - start.second);
    int dy = abs(end.first - start.first);
    int sx = start.second < end.second ? 1 : -1;
    int sy = start.first < end.first ? 1 : -1;
    int err = dx - dy;

    int x = start.second;
    int y = start.first;

    while (true) {
        // Check if the current tile matches the condition (e.g., is blocked)
        if (map[y][x] == obstacle) {
            return true; // Blocked tile found in the path
        }

        if (x == end.second && y == end.first) {
            break; // Reached the end tile
        }

        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x += sx;
        }
        if (e2 < dx) {
            err += dx;
            y += sy;
        }
    }

    return false; // No blocked tiles in the path
}

bool coordsInPath(std::pair<int,int> start, std::pair<int,int> end, std::pair<int,int> between) {
    int dx = abs(end.second - start.second);
    int dy = abs(end.first - start.first);
    int sx = start.second < end.second ? 1 : -1;
    int sy = start.first < end.first ? 1 : -1;
    int err = dx - dy;

    int x = start.second;
    int y = start.first;

    while (true) {
        if (y == between.first && x == between.second) {
            return true; // Blocked tile found in the path
        }

        if (x == end.second && y == end.first) {
            break; // Reached the end tile
        }

        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x += sx;
        }
        if (e2 < dx) {
            err += dx;
            y += sy;
        }
    }

    return false; // No blocked tiles in the path
}


/* HELPER FUNCTIONS */
bool adjCheck(vector<vector<int>> map, int y, int x, int check, int range) {
    int rows = map.size();          // height
    int cols = map[0].size();       // width

    for (int r = -range; r <= range; r++) {
        for (int c = -range; c <= range; c++) {
            if (r == 0 && c == 0) continue;

            int nx = x + c;
            int ny = y + r;

            if (abs(r) + abs(c) <= range && nx >= 0 && nx < cols && ny >= 0 && ny < rows) {
                if (map[ny][nx] == check) {
                    return true;
                }
            }
        }
    }
    return false;
}

template <typename L, typename M, typename T>
bool adjCheck(L& referenceMap, M& map, int y, int x, T check, int range) {
    for (int r = -range; r <= range; r++) {
        for (int c = -range; c <= range; c++) {
            if (r == 0 && c == 0) continue;

            int nx = x + c;
            int ny = y + r;
            if (referenceMap.find({ny, nx}) != referenceMap.end()) {
                int index = referenceMap.at({ny, nx});
                auto item = map[index];

                if (abs(r) + abs(c) <= range && nx >= 0) {
                    if (item == check) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

bool adjCheckEntity(int firstIndex, int secondIndex, bool firstAnimal, bool secondAnimal) {
    if (firstAnimal) std::pair<int,int> fc = animalCoords[firstIndex];
    else std::pair<int,int> fc = currentCoords[firstIndex];
    if (secondAnimal) std::pair<int,int> sc = animalCoords[secondIndex];
    else std::pair<int,int> fc = currentCoords[firstIndex];
    if ((abs(fc.first - sc.first) == 1 || abs(fc.first - sc.first) == 0) && (abs(fc.second - sc.second) == 0 || abs(fc.second - sc.second) == 1)) return true;
    return false;
}

template <typename L, typename M, typename Container>
bool adjCheckList(L& referenceMap, M& map, int y, int x, const Container& check, int range) {
    for (int r = -range; r <= range; r++) {
        for (int c = -range; c <= range; c++) {
            if (r == 0 && c == 0) continue;

            int nx = x + c;
            int ny = y + r;
            if (referenceMap.find({ny, nx}) != referenceMap.end()) {
                int index = referenceMap.at({ny, nx});
                auto item = map[index];

                if (abs(r) + abs(c) <= range && nx >= 0) {
                    for (const auto& checkItem : check) {
                        if (item == checkItem) {
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

template <typename L, typename M, typename Container>
int adjCheckListCount(L& referenceMap, M& map, int y, int x, const Container& check, int range) {
    int count = 0;
    for (int r = -range; r <= range; r++) {
        for (int c = -range; c <= range; c++) {
            if (r == 0 && c == 0) continue; // Skip the center tile

            int nx = x + c;
            int ny = y + r;
            if (referenceMap.find({ny, nx}) != referenceMap.end()) {
                int index = referenceMap.at({ny, nx});
                auto item = map[index];

                if (abs(r) + abs(c) <= range && nx >= 0) {
                    for (const auto& checkItem : check) {
                        if (item == checkItem) {
                            count++;
                        }
                    }
                }
            }
        }
    }
    return count;
}

// returns the closest adjacent tile of check type
std::pair<int,int> adjGet(vector<vector<int>>& map, int y, int x, int check, int range) {
    int rows = map.size();
    int cols = map[0].size();
    std::pair<int,int> adj = {x,y}; // return original coords if none in range

    for (int r = -range; r <= range; r++) {
        for (int c = -range; c <= range; c++) {
            if (r == 0 && c == 0) continue; // Skip the center tile

            int nx = x + c;
            int ny = y + r;

            // Ensure we're checking only directly adjacent tiles within the range
            if (abs(r) + abs(c) <= range && nx >= 0 && nx < rows && ny >= 0 && ny < cols) {
                if (map[ny][nx] == check) {
                    //cout << adj.first << "," << adj.second << ";";
                    adj = {ny, nx};
                    return adj;
                }
            }
        }
    }
    return adj;
}

//checking any tile parameter
template <typename T, typename C>
std::pair<int,int> adjGetTileOfType(vector<T>& tileVector, int tileIndex, C type, int range) {
    std::pair<int,int> adj = tileIndices(tileIndex);
        // Ensure we're checking only directly adjacent tiles within the range
        if (abs(r) + abs(c) <= range && nx >= 0 && nx < rows && ny >= 0 && ny < cols) {
            if (tileVector[index] == type) {
                    adj = tileIndices(tileIndex);
                    return adj;
            }
        }
    return adj;
}



int adjRange(std::vector<std::vector<int>>& map, int y, int x, int check) {
    int rows = map.size(), cols = map[0].size();
    std::vector<std::pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    std::queue<std::pair<int, int>> q;
    std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));
    q.push({y, x});
    visited[y][x] = true;

    while (!q.empty()) {
        int currentX = q.front().second, currentY = q.front().first;
        q.pop();
        for (const auto& dir : directions) {
            int nx = currentX + dir.second, ny = currentY + dir.first;
            if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && !visited[ny][nx]) {
                visited[ny][nx] = true;
                if (map[ny][nx] == check)
                    return abs(ny - y) + abs(nx - x);
                q.push({ny, nx});
            }
        }
    }
    return -1;
}

// returns all adjacent tiles of type, and distance
std::vector<std::tuple<int,int, int>> adjGetAll(vector<vector<int>>& map, int y, int x, int check, int range) {
    int rows = map.size();
    int cols = map[0].size();
    std::vector<std::tuple<int,int,int>> tiles;

    for (int r = -range; r <= range; r++) {
        for (int c = -range; c <= range; c++) {
            if (r == 0 && c == 0) continue; // Skip the center tile

            int nx = x + c;
            int ny = y + r;

            // Ensure we're checking only directly adjacent tiles within the range
            if (abs(r) + abs(c) <= range && nx >= 0 && nx < rows && ny >= 0 && ny < cols) {
                if (map[ny][nx] == check) {
                    //cout << adj.first << "," << adj.second << ";";
                    tiles.push_back({ny, nx, chebyshev(y, x, ny, nx)});
                }
            }
        }
    }
    return tiles;
}



//adds corner adjacent tiles to adjCheck
bool diagAdjCheck(vector<vector<int>>& map, int y, int x, int check, int range) {
    int rows = map.size();
    int cols = map[0].size();

    for (int r = -range; r <= range; r++) {
        for (int c = -range; c <= range; c++) {
            if (r == 0 && c == 0) continue; // Skip the center tile

            int nx = x + r;
            int ny = y + c;

            // Ensuring only diagonal or directly adjacent tiles are checked
            if (fmax(abs(r), abs(c)) <= range && nx >= 0 && nx < rows && ny >= 0 && ny < cols) {
                if (map[ny][nx] == check) {
                    return true;
                }
            }
        }
    }
    return false;
}

//gets adjacent tile with lowest value
std::pair<int, int> getLowestAdj(vector<vector<int>>& map, int y, int x) {
    int dx[] = {-1, 0, 1, 0};  // x-direction for up/down
    int dy[] = {0, 1, 0, -1};  // y-direction for left/right
    int lowest = RAND_MAX;
    std::pair<int, int> ret;

    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        // Check if within bounds
        if (nx >= 0 && nx < map.size() && ny >= 0 && ny < map[0].size()) {
            if (map[ny][nx] < lowest) {
                lowest = map[ny][nx];
                ret = {ny, nx};
            }
        }
    }
    return ret;
}

//gets adjacent tile with highest value
std::pair<int, int> getHighestAdj(vector<vector<int>>& map, int y, int x) {
    int dx[] = {-1, 0, 1, 0};  // x-direction for up/down
    int dy[] = {0, 1, 0, -1};  // y-direction for left/right
    int highest = -9999999;
    std::pair<int, int> ret;

    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        // Check if within bounds
        if (nx >= 0 && nx < map.size() && ny >= 0 && ny < map[0].size()) {
            if (map[ny][nx] > highest) {
                highest = map[ny][nx];
                ret = {ny, nx};
            }
        }
    }
    return ret;
}

int getLowestAdjValue(vector<vector<int>>& map, int y, int x) {
    int dx[] = {-1, 0, 1, 0};  // x-direction for up/down
    int dy[] = {0, 1, 0, -1};  // y-direction for left/right
    int lowest = RAND_MAX;

    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        // Check if within bounds
        if (nx >= 0 && nx < map.size() && ny >= 0 && ny < map[0].size()) {
            if (map[ny][nx] < lowest) {
                lowest = map[ny][nx];
            }
        }
    }
    return lowest;
}

int getHighestAdjValue(vector<vector<int>>& map, int y, int x) {
    int dx[] = {-1, 0, 1, 0};  // x-direction for up/down
    int dy[] = {0, 1, 0, -1};  // y-direction for left/right
    int highest = -9999999;

    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        // Check if within bounds
        if (nx >= 0 && nx < map.size() && ny >= 0 && ny < map[0].size()) {
            if (map[ny][nx] > highest) {
                highest = map[ny][nx];
            }
        }
    }
    return highest;
}

 template <typename T>
 void transformAdj(T& map, int y, int x, int transform, float chance) {
                 int dx = -1; int dy = 0;
                 if (rand() / (float)RAND_MAX < chance) {
                    map[x + dx][y + dy] = transform;
                 }
                 dx = 1;
                 if (rand() / (float)RAND_MAX < chance) {
                    map[x + dx][y + dy] = transform;
                 }
                 dy = -1; dx = 0;
                 if (rand() / (float)RAND_MAX < chance) {
                    map[x + dx][y + dy] = transform;
                 }
                 dy = -1;
                 if (rand() / (float)RAND_MAX < chance) {
                    map[x + dx][y + dy] = transform;
                 }
}

 template <typename T>
 void adjustAdj(T& map, int y, int x, int adjustment) {
                 int dx = -1; int dy = 0;
                    map[x + dx][y + dy] += adjustment;
                 dx = 1;
                    map[x + dx][y + dy] = adjustment;
                 dy = -1; dx = 0;
                    map[x + dx][y + dy] = adjustment;
                 dy = -1;
                    map[x + dx][y + dy] = adjustment;
}


bool checkEmptyTile(int tileIndex, int adjacentTileIndex) {
   if (tileWater[tileIndex]) return false;
   if (tileAlt[tileIndex] > tileAlt[adjacentTileIndex] + maxAltChange || tileAlt[tileIndex] < tileAlt[adjacentTileIndex] - maxAltChange) return false;
   if (Plant* pPtr = std::get_if<Plant>(&tileObject[tileIndex]))
       if (*pPtr != Plant::NONE) return false;
   if (Scavengeable* sPtr = std::get_if<Scavengeable>(&tileObject[tileIndex]))
       if (*sPtr != Scavengeable::NONE) return false;
   if (Item* iPtr = std::get_if<Item>(&tileObject[tileIndex]))
       if (*iPtr != Item::NONE) return false;
   if (Buildable* bPtr = std::get_if<Buildable>(&tileObject[tileIndex]))
       if (*bPtr != Buildable::NONE) return false;
   if (Animal *aPtr = std::get_if<Animal>(&tileObject[tileIndex]))
       if (*aPtr != Animal::NONE) return false;
   if (Vehicle *vPtr = std::get_if<Vehicle>(&tileObject[tileIndex]))
       if (*vPtr != Vehicle::NONE) return false;
   if (objectToInt(tileObject[tileIndex]) != 0) return false;
}

std::pair<int, int> getAdjacentTile(int tileIndex, Direction direction) {
    adjacentTilesIndices[tileIndex];
    if (direction == Direction::North) return
    if (direction == Direction::South)
    if (direction == Direction::West)
    if (direction == Direction::East)
}

Direction getRandomAdjDirection(Direction direction) {
    if (direction == Direction::North) {
      if (rbool()) return Direction::East;
      return Direction::West;
    } if (direction == Direction::South) {
      if (rbool()) return Direction::East;
      return Direction::West;
    }
    if (direction == Direction::West) {
        if (rbool()) return Direction::North;
      return Direction::South;
    }
    if (rbool()) return Direction::North;
      return Direction::South;
}

void moveInDirection(&std::pair<int,int> coord, Direction direction) {
    if (direction == Direction::North) coord.second += 1;
    else if (direction == Direction::South) coord.second -= 1;
    if (direction == Direction::East) coord.first += 1;
    else if (direction == Direction::West) coord.second -= 1;
}

std::pair<int, int> getNearestEmptyTile(int startIndex) {
    std::queue<int> q;
    std::unordered_set<int> visited;

    q.push(startIndex);
    visited.insert(startIndex);

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        auto [above, right, below, left] = adjacentTilesIndices[current];
        std::array<int, 4> neighbors = {above, right, below, left};

        for (int neighbor : neighbors) {
            if (neighbor < 0 || visited.count(neighbor)) continue;

            if (checkEmptyTile(current, neighbor)) {
                return tileCoords[neighbor]; // Found nearest empty tile
            }

            visited.insert(neighbor);
            q.push(neighbor);
        }
    }

    return {-1, -1}; // No empty tile found
}

int getNearestAdjacentEmptyTileIndex(int startIndex) {
    std::queue<int> q;
    std::unordered_set<int> visited;

    q.push(startIndex);
    visited.insert(startIndex);

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        auto [above, right, below, left] = adjacentTilesIndices[current];
        std::array<int, 4> neighbors = {above, right, below, left};

        for (int neighbor : neighbors) {
            if (neighbor < 0 || visited.count(neighbor)) continue;

            if (checkEmptyTile(current, neighbor)) {
                return neighbor// Found nearest empty tile
            }

            visited.insert(neighbor);
            q.push(neighbor);
        }
    }

    return -1; // No empty tile found
}

struct TileBlock() {
    std::pair<int,int> startTile;
    uint8_t blockSize;
    Direction direction;
}

TileBlock getNearestAdjacentEmptyTileBlock(int startIndex, uint8_t blockSize) {
    std::queue<int> q;
    std::unordered_set<int> visited;
    Direction direction;

    q.push(startIndex);
    visited.insert(startIndex);

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        auto [above, right, below, left] = adjacentTilesIndices[current];
        std::array<int, 4> neighbors = {above, right, below, left};

        for (int neighbor : neighbors) {
            if (neighbor < 0 || visited.count(neighbor)) continue;

            if (checkEmptyTile(current, neighbor)) {
                // Found an empty tile, now check for a block of adjacent empty tiles
                int count = 1; // Start with the current empty tile
                // Check horizontal and vertical directions for contiguous empty tiles

                // Check to the right
                int temp = neighbor;
                while (checkEmptyTile(current, temp) && visited.count(temp) == 0) {
                    count++;
                    visited.insert(temp);
                    temp = right; // move right
                    direction = west;
                }

                // Check to the left
                temp = neighbor;
                while (checkEmptyTile(current, temp) && visited.count(temp) == 0) {
                    count++;
                    visited.insert(temp);
                    temp = left; // Move left
                    direction = east;
                }

                // Check above
                temp = neighbor;
                while (checkEmptyTile(current, temp) && visited.count(temp) == 0) {
                    count++;
                    visited.insert(temp);
                    temp = above; // Move above
                    direction = north;
                }

                // Check below
                temp = neighbor;
                while (checkEmptyTile(current, temp) && visited.count(temp) == 0) {
                    count++;
                    visited.insert(temp);
                    temp = below; // Move below
                    direction = south;
                }

                // If count meets or exceeds required count of adjacent empty tiles
                if (count >= blockSize) {
                    return {tileCoords[neighbor], blockSize, direction};
                }
            }
            visited.insert(neighbor);
            q.push(neighbor);
        }
    }
    return {-1, -1}; // No empty tile block found
}

int getSpeed(Animal animal) {
    switch (animal) {
        Pig, Cow, Chicken, Duck, Sheep, Goat, Horse, Ox, Donkey, Camel, WaterBuffalo, Rabbit, Antelope, Deer, Moose, Capybara, Turtle, Elephant, Bison, Wolf, Bear, Caribou, Fish,
    }
}

int getSeedIndex(int y, int x, int length) {
    return y * length + x;
}

int calculateDistance(int y, int x, const std::pair<int,int>& target) {
    return std::abs(x - target.first) + std::abs(y - target.second);
}

struct Node {
    int index;
    uint8_t moveCost;  // The cost of moving to this node
    uint8_t fCost;     // fCost = gCost + heuristic
    Node* parent;      // Parent node for path reconstruction

    Node(int index, uint8_t moveCost, uint8_t fCost, Node* parent = nullptr)
        : index(index), moveCost(moveCost), fCost(fCost), parent(parent) {}

    bool operator>(const Node& other) const {
        return fCost > other.fCost;
    }
};

uint16_t manDist(int x1, int y1, int x2, int y2) {
    return std::abs(x1 - x2) + std::abs(y1 - y2);
}



// returns pair of index, cost to new path vector
std::vector<std::pair<int, int>> greedyPath(int startIndex, int endIndex) {
    int startX = tileCoords[startIndex].first;
    int startY = tileCoords[startIndex].second;

    int goalX = tileCoords[endIndex].first;
    int goalY = tileCoords[endIndex].second;
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> openSet;
    std::unordered_map<int, bool> visited;

    // Start with the initial node, no parent (null)
    openSet.push(Node(startX, startY, 0, manDistance(startX, startY, goalX, goalY), nullptr));

    std::vector<std::pair<std::pair<int, int>, int>> path;

    while (!openSet.empty()) {
        Node current = openSet.top();
        openSet.pop();

        int index = current.index;
        int cost = current.moveCost;

        if (tileCoords[index].first == goalX && tileCoords[index].second == goalY) {
            // reconstruct the path by backtracking from goal to start
            while (current.parent != nullptr) {
                path.push_back(index, cost);
                current = *current.parent;
                index = current.index
            }
            path.push_back(index, 0);
            std::reverse(path.begin(), path.end()); // Reverse the path to get the correct order
            break;
        }

        if (visited(index)) continue;
        visited(index) = true;

        for (int i = 0; i < 4; ++i) {;
            if (i == 0) std::pair<int,int> mt = getMoveTimeAndTileIndex(Direction::Up);
            if (i == 1) std::pair<int,int> mt = getMoveTimeAndTileIndex(Direction::Down);
            if (i == 2) std::pair<int,int> mt = getMoveTimeAndTileIndex(Direction::Left);
            if (i == 3) std::pair<int,int> mt = getMoveTimeAndTileIndex(Direction::Right);

            uint8_t moveCost = mt.first;
            int newIndex = mt.second;

            if (newIndex == -1) continue;
            if (visited(newIndex)) continue;
            uint8_t newManDist = manDist(tileCoords[index].first, tileCoords[index].second, goalX, goalY);
            openSet.push(Node(newIndex, moveCost, moveCost + newManDist, &current));
        }
    }
    return path;
}

//use to estimate when entity will arrive at target
int timeToDestEstimator(bool min, int subjectIndex, int targetIndex, bool subjectAnimal, bool targetAnimal) {
        if (targetAnimal) {
        std::pair<int,int> targetCoord = animalCoords[targetIndex];
    } else std::pair<int,int> targetCoord = currentCoords[targetIndex];

    if (subjectAnimal) {
        std::pair<int,int> subjectCoord = animalCoords[subjectIndex];
        Animal animal = animals[subjectIndex];
    } else std::pair<int,int> subjectCoord = currentCoords[targetIndex];

    int dist = manDist(subjectCoord.first, subjectCoord.second, targetCoord.first, targetCoord.second);
    if (subjectAnimal) dist *= getSpeed(animal);
    return dist;
}

void moveAnimal(vector<std::pair<int,int> path, int animalIndex) {
 	std::pair<int,int>& subjectCoords = animalCoords[animalIndex];
    Animal animal = animals[animalIndex];

    int nextTileMoveTime = 0;
    for (int i = 0; i < path.size(); i++) {
        nextTileMoveTime += path[i].second * getSpeed(animal);
        addEvent(nextTileMoveTime, EventType::AnimalMoveTile, animalIndex, path[i].first);
    }
}

void movePawn(vector<std::pair<int,int> path, int pawnIndex) {
 	std::pair<int,int>& subjectCoords = currentCoords[pawnIndex];
    int nextTileMoveTime = 0;
    for (int i = 0; i < path.size(); i++) {
        nextTileMoveTime += path[i].second;
        addEvent(nextTileMoveTime, EventType::PawnMoveTile, pawnIndex, path[i].first);
    }
}

void moveAnimal(int entityIndex, int destCoordIndex) {
    std::pair<int, int> ec = animalCoords[entityIndex];
    vector<std::pair<std::pair<int,int>, int>> path = greedyPath(ec, destCoordIndex);
    moveAnimal(path, entityIndex);
}

void movePawn(int entityIndex, int destCoordIndex) {
    std::pair<int, int> ec = animalCoords[entityIndex];
    std::pair<int, int> ec = currentCoords[entityIndex];

    vector<std::pair<std::pair<int,int>, int>> path = greedyPath(ec, destCoordIndex);
    movePawn(path, entityIndex);
}

//TODO: consider making the move tile events directional
void moveAnimal(int entityIndex, int destCoordIndex, DelayedEvent event) {
    std::pair<int, int> ec = animalCoords[entityIndex];
    vector<std::pair<std::pair<int,int>, int>> path = greedyPath(ec, destCoordIndex);
    Animal animal = animals[animalIndex];

    int nextTileMoveTime = 0;
    for (int i = 0; i < path.size(); i++) {
        nextTileMoveTime += path[i].second * getSpeed(animal);
        addEvent(nextTileMoveTime, EventType::AnimalMoveTile, entityIndex, path[i].first);
    }
    addEvent(nextTileMoveTime + 1, event, entityIndex);
}

void movePawn(int entityIndex, int destCoordIndex, DelayedEvent event) {
    std::pair<int, int> ec = animalCoords[entityIndex];
    vector<std::pair<std::pair<int,int>, int>> path = greedyPath(ec, destCoordIndex);

    int nextTileMoveTime = 0;
    for (int i = 0; i < path.size(); i++) {
        nextTileMoveTime += path[i].second;
        addEvent(nextTileMoveTime, EventType::PawnMoveTile, entityIndex, path[i].first);
    }
    addEvent(nextTileMoveTime + 1, event, entityIndex);
}

//moves a certain entity until it is adjacent with another entity and facing it.
void meet(int finderIndex, int targetIndex, bool finderAnimal, bool targetAnimal, DelayedEvent meetType) {
    if (finderAnimal) std::pair<int, int> fc = animalCoords[finderIndex];
    else std::pair<int, int> fc = currentCoords[finderIndex];
    if (targetAnimal) std::pair<int, int> tc = animalCoords[targetIndex];
    else std::pair<int, int> tc = currentCoords[targetIndex];

    //TODO: if hunting, give up if animal is faster and not asleep or injured

    vector<std::pair<std::pair<int,int>, int>> path = greedyPath(tileIndices(fc), tileIndices(tc));
    if (finderAnimal) moveAnimal(path, animalIndex);
    else movePawn(path, pawnIndex);

    int time = timeToDestEstimator(finderIndex, targetIndex, finderAnimal, targetAnimal);
    if (finderAnimal) {
        if (targetAnimal) {
            addEvent(time, EventType::CheckIfAdjacentAnimals, static_cast<int>(meetType), finderIndex, targetIndex);
        } else addEvent(time, EventType::CheckIfAdjacentAnimalToPawn, static_cast<int>(meetType), finderIndex, targetIndex);
    } else {
        if (targetAnimal) {
            addEvent(time, EventType::CheckIfAdjacentPawnToAnimal, static_cast<int>(meetType),finderIndex, targetIndex);
        } else addEvent(time, EventType::CheckIfAdjacentPawns, static_cast<int>(meetType), finderIndex, targetIndex);
    }
    //TODO:fix and face entities
}
