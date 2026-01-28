#include "../include/worldSpawn.hpp"
#include "../include/tile.hpp"
#include "pathfinding.cpp"
#include "world/world.hpp"
#include <map>


//TO-DO: refactor all code to use adjacent tiles based on nearest Voronoi seeds, not square cells

// 1. Generate Ocean on altitude, land, and ocean maps
void WorldSpawner::generateOceansOnMaps() {
    for (int x = 0; x < WIDTH; ++x) {
        for (int y = 0; y < HEIGHT; ++y) {
            if (altitudeMap[y][x] > landThreshold) {
                oceanMap[y][x] = 1;  // Land
                landsMap[y][x] = 2; //Land
            } else {
                oceanMap[y][x] = 0;  // Ocean
                landsMap[y][x] = 0; //Ocean
                altitudeMap[y][x] = 0;
            }
        }
    }
}

//Function to mark adjacent tiles to coast as lowlands
void WorldSpawner::markCoasts() {
    for (int x = 0; x < WIDTH; ++x) {
        for (int y = 0; y < HEIGHT; ++y) {
            if (oceanMap[y][x] == 1) {  // If it's Land
                if (adjCheck(oceanMap, y, x, 0, 1)) {
                    landsMap[y][x] = 1; //Coast
                }
            }
        }
    }
}



// Function to apply user-defined chances for unlikely transitions
void WorldSpawner::applyExtraHighlandsAndMountains() {
    // Step 1: Transition one tile to other tile
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            int lowest = getLowestAdjValue(landsMap, x, y);
            float threshold;
            switch (lowest) {
                case 5:
                    threshold = 0.4f;
                    break;
                case 4:
                    threshold = 0.10f;
                    break;
                case 3:
                    threshold = 0.04f;
                    break;
                case 2:
                    threshold = 0.003f;
                    break;
                default:
                    threshold = -1.0f;
            }
            float randVal = rand() / (float)RAND_MAX;
            if (randVal < threshold) {
                landsMap[y][x] = 5;  // Mountains
            }
        }
    }

    // Step 2: Apply highlands, mountains swaths
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            if (landsMap[y][x] == 5) {
                int success;
                int backup;
                float chance;
                int l;
                int s;

                if (landsMap[y][x] == 5) {
                    success = 5;
                    int highest = getHighestAdjValue(landsMap, y, x);
                    int lowest = getLowestAdjValue(landsMap, y, x);
                    backup = highest;
                    switch (lowest) {
                        case 5:
                            chance = 0.6f;
                            break;
                        case 4:
                            chance = 0.2f;
                            break;
                        case 3:
                            chance = 0.03f;
                            break;
                        case 2:
                            chance = 0.005f;
                            break;
                        default:
                            chance = 0.0f;
                    }
                    l = rint(1,5);
                    s = rint(1,2);
                } else {
                    success = 4;
                    backup = 3;
                    chance = 0.3;
                    l = rint(1,4);
                    s = rint(1,3);
                }
                pair<int,int> change = getHighestAdj(landsMap, y, x);
                int nx = change.second;
                int ny = change.first;

                // Random chance which determines if highlands range is deleted or expanded
                if (rand() / (float)RAND_MAX < chance) {
                    for (int i = 0; i < l; i++) {
                        for (int j = 0; j < s; j++) {
                            if (nx >= 0 && nx < WIDTH && ny >= 0 && ny < HEIGHT) {
                                // Bounds check
                                if ((rand() / (float)RAND_MAX) > 0.8) landsMap[nx][ny] = success;
                            }
                        }
                    }
                } else {
                    landsMap[ny][nx] = backup;
                }
            }
        }
    }

    //Step 3: Apply coastal mountains chance
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; x++) {
            if (landsMap[y][x] != 0 && landsMap[y][x] != 1) {
                pair<int,int> near = adjGet(landsMap, y, x, 1, 3);
                pair<int,int> current = {y,x};
                if (near != current) {
                    if (rfloat(0,1.0) < coastalRangeChance) {
                        landsMap[y][x] = 5; //Mountain
                        int size = rint(3,7);
                        for (int i = 0; i < size; i++) {
                            //get nearest lowlands
                            pair<int,int> near2 = adjGet(landsMap, y, x, 2, 1);
                            int nx = near2.second; int ny = near2.first;
                            //check to ensure new lowlands tile is close to coast
                            if (adjCheck(landsMap, ny, nx, 1, 3) == true && landsMap[nx][ny] != 0 && landsMap[nx][ny] != 1)
                                landsMap[ny][nx] = 5; //Mountain
                            y = ny; x = nx;
                        }

                    }
                }
                // increase mt altitude
                if (landsMap[y][x] == 5) {
                    if (!adjCheck(landsMap,y,x,1,1) && !adjCheck(landsMap,y,x,1,2) && !adjCheck(landsMap,y,x,1,3)) {
                        altitudeMap[y][x] = 30 + (rand() / (float) RAND_MAX) * 30;
                    } else {
                        altitudeMap[y][x] = 20 + (rand() / (float) RAND_MAX) * 20;
                    }
                }
            }
        }
    }
}

void WorldSpawner::generateLandsMap() {
    markCoasts(landsMap, oceanMap);
    for (int x = 0; x < WIDTH; ++x) {
        for (int y = 0; y < HEIGHT; ++y) {
            if (oceanMap[y][x] == 1 && landsMap[y][x] != 1) {
                if (altitudeMap[y][x] < lowlandsThreshold) {
                    landsMap[y][x] = 2;
                } else if (altitudeMap[y][x] < midlandsThreshold) {
                    landsMap[y][x] = 3;
                } else  {
                    landsMap[y][x] = 4;
                }
            }
        }
    }
    applyExtraHighlandsAndMountains(landsMap, oceanMap);
}

//TODO: make river 
void WorldSpawner::extendRiversFromSource(std::vector<riverData> rd, int x, int y, std::vector<bool>& rVisited) {
    // Base case 1: Hits the edge of the map
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) {
        return;  // Stop recursion if out of bounds
    }

    // Base case 2: Tile is rVisited
    if (rVisited[y][x]) {
        return;
    }

    rVisited[y][x] = true;

    // Base case 3: Hits an ocean tile
    if (waterMap[y][x] == 0 || waterMap[y][x] == 4) {
        waterMap[y][x] = 4;
        return;
    }

    // Base case 4: Chance of stopping if lake condition is met
    if (getLowestAdjValue(altitudeMap, y, x) > altitudeMap[y][x]) {
        waterMap[y][x] = 5;  // Mark as Lake
        float random = rand() % 100;
         // 60% chance of stopping when adjacent tiles are not lower, and 20% of no lake
        if ((random < 70)) return;
        else if ((random < 80)) {
            waterMap[y][x] = 7; //Mark as groundwater river end
            return;
        }
    }

    // Base case 5: stops if natural river end
     if (waterMap[y][x] == 7) {
        return;
    }

    int dx[] = {-1, 0, 1, 0}; 
    int dy[] = {0, 1, 0, -1};

    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (nx >= 0 && nx < WIDTH && ny >= 0 && ny < HEIGHT) {
            // change current tile to river continues
            if (waterMap[ny][nx] == 3 || waterMap[ny][nx] == 6 || waterMap[ny][nx] == 2 || waterMap[ny][nx] == 5 )  {
                 // Check river continuation conditions
            if (waterMap[y][x] != 2 && waterMap[y][x] != 6 && waterMap[y][x] != 5 && landsMap[y][x] != 5) {
            if (altitudeMap[y][x] < altitudeMap[ny][nx] ) {
              waterMap[y][x] = 3; // Continue river
	      rd.length++;
                }
            }
            } extendRiversFromSource(riverLength, ny, nx, rVisited);
        }
    }
}

void WorldSpawner::markRiverEnds() {
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
                // Check if any adjacent tile is a river
                int dx[] = {-1, 0, 1, 0};
                int dy[] = {0, 1, 0, -1};
                for (int i = 0; i < 4; ++i) {
                    int nx = x + dx[i];
                    int ny = y + dy[i];
                    if (nx >= 0 && nx < WIDTH && ny >= 0 && ny < HEIGHT) {
                        if (waterMap[ny][nx] == 3) {
                            if (oceanMap[y][x] == 0) {
                                 waterMap[y][x] = 4; // River mouth at ocean
                                 break;
                            }
                            if ((getLowestAdjValue(altitudeMap, y, x) > altitudeMap[y][x]) && waterMap[y][x] != 5) {
                                    waterMap[y][x] = 7;
                                    break;
                            }
                        }
                    }
                }
        }
    }
}


void WorldSpawner::generateWaterMap() {
    waterMap = oceanMap;

    // generate river sources
    for (int y = 1; y < HEIGHT + 1; y++) {
        for (int x = 1; x < WIDTH + 1; x++) {  // Start from 1 to avoid borders
            // from 1 to avoid borders
            if (landsMap[y][x] != 0 && landsMap[y][x] != 1) {
                // source spawn in high altitude
                if ((landsMap[y][x] == 4) && waterMap[y][x] != 3 && waterMap[y][x] != 4) {
                    if (rand() / float(RAND_MAX) < riverFromHighlandChance) {
                        waterMap[y][x] = 2; // River Source from highland or mountain
                        continue;
                    }
                }
                //source spawn from mountain side
                if ((adjCheck(waterMap, y, x, 5, 1)) && waterMap[y][x] != 3 && waterMap[y][x] != 4 && waterMap[y][x] != 5 && landsMap[y][x] != 1) {
                    if (rand() / float(RAND_MAX) < riverFromMountainChance) {
                        waterMap[y][x] = 2; // River Source from highland or mountain
                        continue;
                    }
                }
            }

                        //check for lake spawns on land
                        if (landsMap[y][x] == 2 && rand() / float(RAND_MAX) < lakeFromLowlandsChance) {
                            waterMap[y][x] = 5;
                        }
                        if (landsMap[y][x] == 3 && rand() / float(RAND_MAX) < lakeFromMidlandsChance) {
                            waterMap[y][x] = 5;
                        }
                         // generate river extensions from sources
                        // check for river extensions
                        std::fill(rVisited.begin(), rVisited.end(), std::vector<bool>(HEIGHT + 1, false));
                        if (waterMap[y][x] == 2) extendRiversFromSource(waterMap, landsMap, altitudeMap, y,x,rVisited);
                    }
                }

     for (int y = 1; y < HEIGHT + 1; y++) {
        for (int x = 1; x < WIDTH + 1; x++) {
            //generate rivers from lakes
            std::fill(rVisited.begin(), rVisited.end(), std::vector<bool>(HEIGHT + 1, false));
            if (waterMap[y][x] == 5 && rand() / (float) RAND_MAX < riverFromLakeChance) extendRiversFromSource(waterMap, landsMap, altitudeMap, y, x, rVisited);
        }
     }
}

// BFS function to calculate the distance from the ocean
std::vector<std::vector<int>> calculateOceanDistance(vector<vector<int>>& waterMap, bool lake, bool river) {
    std::vector<std::vector<int>> distanceMap(HEIGHT, std::vector<int>(WIDTH, WIDTH * HEIGHT));  // Initialize with large values

    int water = lake ? 5 : 0;
    water = river ? 3 : water;

    std::queue<pair<int, int>> q;

    // Initialize distances and queue
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            if (waterMap[y][x] == water) {  // Check waterMap, not landsMap
                distanceMap[y][x] = 0;
                q.push({y, x});
            }
        }
    }

    // BFS to calculate distances
    while (!q.empty()) {
        auto [cy, cx] = q.front();
        q.pop();

        for (auto [dy, dx] : directions) {
            int ny = cy + dy, nx = cx + dx;
            if (ny >= 0 && ny < HEIGHT && nx >= 0 && nx < WIDTH) {
                if (distanceMap[ny][nx] > distanceMap[cy][cx] + 1) {
                    distanceMap[ny][nx] = distanceMap[cy][cx] + 1;
                    q.push({ny, nx});
                }
            }
        }
    }
    return distanceMap;
}

vector<vector<int>> generateWBDistances(std::vector<std::vector<int>>& waterMap) {
    vector<vector<int>> oceanDistance = calculateOceanDistance(waterMap, false, false);
    return oceanDistance;
}

void WorldSpawner::generateTemperatureMap() {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (oceanMap[y][x] == 0) continue;
            int edist = std::abs(y - EQUATOR);
            int odist = oceanDistance[y][x];
            int temperature = 90;
            // affect temp by latitude
            temperature -= (pow(edist,1.05) * 94 / HEIGHT);
            //affect temp by altitude
            temperature -= std::min(12, static_cast<int>(altitudeMap[y][x] / 3.2f));
            // mountain tiles affect temp relative to the ocean
            int range = adjRange(landsMap, y, x, 5); //find mountain
            if (range < 4 && landsMap[y][x] != 5) {
                pair ag = adjGet(landsMap, y, x, 5, range+1);
                int nx = ag.second; int ny = ag.first;
                // get and see if mountain is between current tile and coast
                if (adjRange(landsMap, ny, nx, 0) < 3 && adjRange(landsMap, ny, nx, 0) < range) {
                    temperature -= rint(2,7);
                    altitudeMap[y][x] -= rint(3,6);
                    // check if tile is between mountain and coast
                } if (adjRange(landsMap, y, x, 0) < adjRange(landsMap, ny, nx, 0) && range < 3) {
                    temperature += rint(2,7);
                }
            }
            //ocean moderates temp, but less near equator
            int otemp = 80 - (edist / (HEIGHT * 1.3f / HEIGHT));

            if (temperature > 70 && odist >= 1) {
                temperature -= (temperature - otemp) * 1.6 / std::max(odist, 1);
            }

            if (temperature < 45 && odist >= 1) {
                temperature += (temperature - otemp) * 1.6 / std::max(odist, 1);
            }
            temperatureMap[y][x] = temperature;
        }
    }
}

std::vector<std::tuple<float, bool, bool>> humidityAndRainShadowEffects(vector<vector<int>>& waterMap, vector<vector<int>>& landsMap, int y, int x, int water, bool biomes) {
    std::vector<std::tuple<float,bool,bool>> ret;
    bool leewardEffect = false;  bool windwardEffect = false;
    float min; float power; int wdistance; float hincrease; int dist;
    // make vector with all nearby tiles of water body type
    std::vector<std::tuple<int, int, int>> ocoords;
    //adjust exponential decrease of humidity gain based on water body type
    if (!biomes) {
        if (water == 0) { //ocean
            min = 8.6;
            power = 1.3;
            dist = 7;
        }
        if (water == 5) { //lake
            min = 4.8;
            power = 1.9;
            dist = 5;
        }
        if (water == 3) { //river
            min = 2.8;
            power = 2.5;
            dist = 3;
        }
        ocoords = adjGetAll(waterMap, y, x, water, dist);
    } else {
        if (water == 4) { //wetlands
            min = 3.2;
            power = 1.7;
            dist = 3;
        }
        if (water == 5) { //forest
            min = 1.7;
            power = 3.5;
            dist = 2;
        }
        if (water == 7) { //jungle
            min = 2.6;
            power = 1.9;
            dist = 3;
        }

        ocoords = adjGetAll(biomeMap, y, x, water, dist);
    }
    // //eliminate ocean tiles not adjacent to coasts
    for (int i = 0; i < (int)ocoords.size(); i++) {
        std::tuple<int, int, int> t = ocoords[i];
        pair<int, int> waterBody = {get<0>(t), get<1>(t)};

        if (water == 0) {
            if (!adjCheck(landsMap, waterBody.first, waterBody.second,1,1)){
                continue;
            }
        }
        //for all found tiles, calculate added humidity to current tile
        //and if mountain is blocking
        wdistance = std::get<2>(t);
        pair<int,int> current = {y, x};
        // increase humidity by distance from water body
        hincrease = fmax(0.0, (min+1.0 - pow(wdistance, power)));
        // check if mountain is between current tile and water body
        if (isInPath(landsMap, current, waterBody, 5)) leewardEffect = true;

        // get windward effect
        // get all mountains near water body
        vector<std::tuple<int, int, int>> mcoords = adjGetAll(landsMap, waterBody.first, waterBody.second, 5, 4);
        for (int i = 0; i < (int)mcoords.size(); i++) {
            std::tuple<int, int, int> t = mcoords[i];
            pair<int, int> mount ={std::get<0>(t), std::get<1>(t)};
            // check if current tile is between waterbody and mountain
            bool result = coordsInPath(mount, waterBody, current);
            if (result) windwardEffect = true;
        }
        //add data to vector
        ret.push_back({hincrease, leewardEffect, windwardEffect});
    }
    return ret;
}

float totalCreatedHumidity(vector<vector<int>>& landsMap, int y, int x) {
    float createdhumidity = 0.0; int waterBody;
    for (int c = 0; c < 3; c++) {
        if (c == 0) waterBody = 0;
        if (c == 1) waterBody = 5;
        if (c == 2) waterBody = 3;
        std::vector<std::tuple<float,bool,bool>> waterBodies = humidityAndRainShadowEffects(landsMap, y,x,waterBody,false);
        for (int i = 0; i < (int)waterBodies.size(); i++) {
            std::tuple<float,bool,bool> t = waterBodies[i];
            float ah = std::get<0>(t);
            bool leeward = std::get<1>(t);
            bool windward = std::get<2>(t);
            if (leeward) ah *= 0.3;
            if (windward) ah *= 1.5;
            createdhumidity += ah;
        }
    }
    return createdhumidity;
}

// generate the humidity map based on distance to ocean and altitude
void WorldSpawner::generateHumidityMap() {
    for (int x = 0; x < WIDTH; ++x) {
        for (int y = 0; y < HEIGHT; ++y) {
            if (oceanMap[y][x] == 0) {  // Ocean
                humidityMap[y][x] = 0;
            } else {

                float potentialhumidity = 0.0;
                int humidity;

                //latitudinal humidity effects
                //make measurements relative, no matter HEIGHT
                float adjustedHEIGHT = 1.0;
                float adjustedLat = float(x) / HEIGHT;
                float equator = 0.5;
                float latitude = std::abs(adjustedLat - equator);
                float latEffect = 0.0;

                // simulate hadley effect, which lowers humidity at 30 and 90, raises at 0 and 60
                if (latitude <= (1.0 / 3.0)) {  // Roughly between 0 and 30
                    latEffect = cos((latitude / (1.0 / 3.0)) * M_PI) * 1.6;  // Peak at 30
                } else if (latitude <= (2.0 / 3.0)) {  // Roughly between 30 and 60
                    latEffect = cos(((latitude - (1.0 / 3.0)) / (1.0 / 3.0)) * M_PI) * 1.6;  // Peak at 30
                } else {  // Roughly between 60 and 90
                    latEffect = cos(((latitude - (2.0 / 3.0)) / (1.0 / 3.0)) * M_PI) * 0.6;  // Peak at 90
                }

// Safeguard against extreme values
                latEffect = std::max(1.0f, std::min(latEffect, 2.0f));
                //
                //calculate created humidity based on nearby water bodies and rain shadow effect
                float evap = ((pow(temperatureMap[y][x]/ 22, 1.1)) + (altitudeMap[y][x] / 12)) / 6;
                float createdHumidity = ((humidityMult * totalCreatedHumidity(landsMap, y, x)) * evap);
                //potentialhumidity += fmax(3,((0.6 * (pow((temperatureMap[y][x] / 2.4), 1.5) - pow(landsMap[x][y],2.1))) - 30));

                humidityMap[y][x] = fmax(1, fmin(MAX_HUMIDITY, createdHumidity - latEffect));
                //potentialHumidityMap[y][x] = potentialhumidity;
                //humidityMap[y][x] = fmax(1, fmin(100, fmin(createdhumidity, potentialhumidity)));
            }
        }
        cout << endl;
    }
}

void WorldSpawner::factorWetlandsJunglesAndForests() {
    for (int x = s; x < WIDTH; x+=5) {
        for (int y = s; y < HEIGHT; y++) {
            if (oceanMap[y][x] == 0) continue;
            float createdhumidity = 0.0; int biome;
            for (int c = 0; c < 3; c++) {
                if (c == 0) biome = 4;
                if (c == 1) biome = 5;
                if (c == 2) biome = 7;
                std::vector<std::tuple<float,bool,bool>> biomes = humidityAndRainShadowEffects(waterMap, landsMap, y,x,biome,true);
                for (int i = 0; i < (int)biomes.size(); i++) {
                    std::tuple<float,bool,bool> t = biomes[i];
                    float ah = std::get<0>(t);
                    bool leeward = std::get<1>(t);
                    bool windward = std::get<2>(t);
                    if (leeward) ah *= 0.3;
                    if (windward) ah *= 1.4;
                    createdhumidity += ah;
                    float evap = ((pow(temperatureMap[y][x]/ 24, 1.8)) + (altitudeMap[y][x] / 12)) / 5;
                    humidityMap[y][x] += fmax(0,(humidityMult * createdhumidity * evap));
                    if (humidityMap[y][x] > MAX_HUMIDITY) humidityMap[y][x] = MAX_HUMIDITY;
                }
            }
        }
    }
}

// 4. Generate Biomes
// 1. Hot Desert
// 2. Plain/Grassland
// 3. Savannah
// 4. Wetlands
// 5. Temperate Forest
// 6. Boreal Forest
// 7. Rainforest/Jungle
// 8. Rocky/Badlands
// 9. Tundra
// 10. Cold Desert
void WorldSpawner::generateBiomes() {
    //load data of each biome
    std::tuple<int, int, int, float, float, float, float> biomeData[11];
    int size = 11;
    // humidity, altitude, temp, humidity flexibility, altitude flexibility, temp flexibility, spread chance/size
    biomeData[1] =  {10 ,7 ,90,1,4,2,0.6};   // Hot Desert
    biomeData[2] =  {25,5 ,65,1.5,2,2.5,0.85};    // Grassland
    biomeData[3] =  {35,3 ,78,2.5,2,2.5,0.7};   // Savanna
    biomeData[4] =  {100,2 ,60,1,1.5,3,0.1};    // Wetland
    biomeData[5] =  {66,6,60,2.5,2,2.5,0.8};   // Forest
    biomeData[6] =  {50,8,43,3,3,2,0.7};   // Taiga
    biomeData[7] =  {90,4 ,88,1.5,2,2,0.65};    // Jungle
    biomeData[8] =  {15,25,52,1,3,1.4,0.4}; // Rocky
    biomeData[9] =  {5,31,20,4,6.0,1,0.7}; // Tundra
    biomeData[10] = {10, 8 ,40,0.4,1,0.6,0.5};   // Cold Desert

    for (int s = 0; s < 5; s++) {
        for (int x = s; x < WIDTH; x+=5) {
            for (int y = s; y < HEIGHT; y++) {
                if (biomeMap[x][y] != 0) continue;
                if (oceanMap[x][y] == 0) continue;
                int humidity = humidityMap[x][y];
                int altitude = altitudeMap[x][y];
                int temp = temperatureMap[x][y];
                float lowestScore = RAND_MAX;
                int biome = 0;

                for (int i = 1; i < size; i++) {
                    // get how far away stats are from each biomeType
                    float humDistance = abs(humidity - get<0>(biomeData[i])) / get<3>(biomeData[i]);
                    float altDistance = abs(altitude - get<1>(biomeData[i])) * 2.3 / get<4>(biomeData[i]);
                    float tempDistance = abs(temp - get<2>(biomeData[i])) /  get<5>(biomeData[i]);
                    if (humDistance + altDistance + tempDistance < lowestScore) {
                        lowestScore = humDistance + altDistance + tempDistance;
                        biome = i;
                    }
                    biomeMap[x][y] = biome;
                }
            }
        }
        factorWetlandsJunglesAndForests(temperatureMap, oceanMap, landsMap, altitudeMap, humidityMap, waterMap, s);
    }
}


void WorldSpawner::generateAltitudeMap() {
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            // Generate noise value in range [-1, 1]
            float noiseValue = rNoise.GetNoise((float)y, (float)x);
            // Map the noise value to a HEIGHT range (e.g., 0 to 255)
            int altitude = static_cast<int>(pow((noiseValue * 23), 1.2)); // Converts from [-1, 1] to [-100, 100]
            altitudeMap[y][x] = altitude;
        }
    }
}

void WorldSpawner::getRiversFromGroundwater() {
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            //skip tiles that already have water
            if (waterMap[y][x] != 1) continue;
            if (oceanMap[y][x] == 0) continue;
            if (humidityMap[y][x] > groundWaterThreshold) {
                if (rand() / (float) RAND_MAX > riverFromGroundwaterChance) {
                    waterMap[y][x] = 6; //river source from groundwater
                     std::fill(rVisited.begin(), rVisited.end(), std::vector<bool>(HEIGHT + 1, false));
                     extendRiversFromSource(waterMap, landsMap, altitudeMap, y,x,rVisited);
                }
            }
        }
    }
}

void WorldSpawner::cleanAltitudeMap() {
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            if (altitudeMap[y][x] < landThreshold) {
                altitudeMap[y][x] = 0;
            }
        }
    }
}

void WorldSpawner::addDepressions() {
    FastNoiseLite noiseGenerator;
    noiseGenerator.SetSeed(43543);
    noiseGenerator.SetNoiseType(FastNoiseLite::NoiseType_Perlin);

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            float noiseValue = noiseGenerator.GetNoise((float)y, (float)x);
            float altitude = static_cast<int>((noiseValue) * 100); // Converts from [-1, 1] to [-100, 100]
            if (altitude < depressionThreshold && altitude > 0 && oceanMap[x][y] == 1) {
                altitudeMap[y][x] = fmax(1, (lerp((float)altitude, (float)altitudeMap[y][x], 0.2)));
            }
        }
    }
}

// MAKE MICRO MAP

// Assign each tile to the nearest Voronoi site
// int getCellIDForTile(int x, int y) {
//     float minDist = (float)RAND_MAX;
//     int closestSite = 0;

//     for (int i = 0; i < (int)voronoiSites.size(); i++) {
//         float dist = std::hypot(y - voronoiSites[i].first, x - voronoiSites[i].second);
//         if (dist < minDist) {
//             minDist = dist;
//             closestSite = i;
//         }
//     }
//     return closestSite;
// }

struct SeedCloud {
    std::vector<std::pair<float, float>> seeds; // Using std::pair<float, float>

    // Must return the dimensionality of points (2D case: x, y)
    inline size_t kdtree_get_point_count() const { return seeds.size(); }

    // Return the dimension (0 = x, 1 = y) of a given index
    inline float kdtree_get_pt(const size_t idx, const size_t dim) const {
        return (dim == 0) ? seeds[idx].first : seeds[idx].second;
    }

    // Optional: Bounding box, not required
    template <class BBOX>
    bool kdtree_get_bbox(BBOX& /*bb*/) const { return false; }
};

// Function to find the next tile to flow to (either towards target (lake or river end) or lowest elevation)
void WorldSpawner::applyRiverTiles() {
    int index = rTileIndex[{y,x}];
    // base case: reached target
    if (y == target.first && x == target.second) {
        return;
    }
    // base case: reached lake or ocean tile
    if (rTileType[index] == Tile::ShallowWater) {
        return;
    }
    int minElevation = rTileAlt[index];
    int currentElevation = minElevation;
    int minDist = calculateDistance(y, x, target);
    std::pair<int,int> nextTile = {y, x};

    // Find the lowest elevation neighboring tile
    std::vector<std::pair<int,int>> lowElevTiles;  // To store ties for lowest elevation
    for (const auto& dir : directions) {
        int nx = x + dir.second;
        int ny = y + dir.first;

            int distToTarget = calculateDistance(ny, nx, target);
            int newIndex = rTileIndex[{ny,nx}];
            if (tileAlt[newIndex] < minElevation) {
                minElevation = tileAlt[newIndex];
                minDist = distToTarget;
                nextTile = {nx, ny};
                lowElevTiles.clear();
                lowElevTiles.push_back(nextTile);
            }
            else if (tileAlt[newIndex] == minElevation) {
                lowElevTiles.push_back({nx, ny}); // Tie in elevation
            }
        }

    // If there are ties in the lowest elevation, randomly choose one of the tiles
    if (lowElevTiles.size() > 1) {
        nextTile = lowElevTiles[rand() % lowElevTiles.size()];
    }

    // If nearby elevation is equal to current tile's elevation, prioritize moving towards target
    if (minElevation == currentElevation) {
        // Check distance to target, if closer to the target, move that way
        for (const auto& dir : directions) {
            int nx = x + dir.second;
            int ny = y + dir.first;

                int distToTarget = calculateDistance(ny, nx, target);
                if (distToTarget < minDist) {
                    nextTile = {ny, nx};
                    minDist = distToTarget;
                }
        }
    }
    int ty = nextTile.first; int tx = nextTile.second;
    //apply nextTile as riverTile
    int nextIndex = rTileIndex[{ty,tx}];
    rTileType[nextIndex] = Tile::FlowingWater;
    rTileAlt[nextIndex] -= 1;
    applyRiverTiles(rTileAlt, rTileType, rTileIndex, ty, tx, target);
}


void WorldSpawner::recursiveLower() {
    if (decreaseAmount < 0) {
        return; // Stop recursion if altitude is not decreasing (coast of lake has been reached)
    }

    // Generate a random chance and decide whether to lower the decreaseAmount
    if ((rand() / (float) RAND_MAX) > lakeTileChance) {
        decreaseAmount -= 1;
    }

    // Lower the elevation by the decrease amount
    int index = rTileIndex[{y,x}];
    rTileAlt[index] -= decreaseAmount;

    // Recursively lower neighboring cells
    for (const auto& delta : std::vector<std::pair<int, int>>{{-1, 0}, {1, 0}, {0, -1}, {0, 1}}) {
        int nx = x + delta.first;
        int ny = y + delta.second;
        if (nx >= 0 && ny >= 0 && nx < WORLD_WIDTH && ny < WORLD_HEIGHT) {
            recursiveLower(nx, ny, decreaseAmount);
        }
    }
}

void WorldSpawner::recursiveFill() {
    int index = rTileIndex[{y,x}];
    if (tileAlt[index] > altThreshold) {
        return;
    }
    //fill with water
    rTileType[index] = Tile::ShallowWater;
    rTileWater[index] = true;

    // Recursively lower neighboring cells
    for (const auto& delta : std::vector<std::pair<int, int>>{{-1, 0}, {1, 0}, {0, -1}, {0, 1}}) {
        int nx = x + delta.first;
        int ny = y + delta.second;
        if (nx >= 0 && ny >= 0 && nx < WORLD_WIDTH && ny < WORLD_HEIGHT) {
            recursiveLower(nx, ny, altThreshold);
        }
    }
}

// generates starting tiles based on amount of cells fully generated (loaded into memory)

             //generate water bodies
        // for (int i = 0; i < (int)rTileCellIndex.size(); i++) {
        //         uint32_t index = rTileCellIndex[i];
        //         std::pair mapCoord = mapsLink[index];
        //         //get seed of cell
        //         std::pair seed = voronoiSites[index];
        //         // add river source tiles for those near mountain cells (due to snowmelt)
        //             if (waterMap[mapCoord.first][mapCoord.second] == 2) {
        //             // goal: put sources close to mountian tiles
        //             // 1. get closest adj mountain tile

        //             const size_t numResults = 5;
        //             std::vector<float> queryPoint = {seed.first, seed.second};
        //             uint32_t retIndex[numResults]; // nearest neighbor index
        //             float outDistSqr[numResults]; //distance between nn and current
        //             tree.knnSearch(&queryPoint[0], numResults, &retIndex[0], &outDistSqr[0]);
        //             bool foundMountain = false;
        //             for (int i = 0; i < numResults; i++) {
        //                 int cellIndex = (int)retIndex[0];
        //                 std::pair nearCellCoord = mapsLink[cellIndex];
        //                 // if found nearby point is a mountain
        //                 if (landsMap[nearCellCoord.first][nearCellCoord.second] == 5) {
        //                     foundMountain = true;
        //                     //find good source tiles in between mountain seed tile and current seed tile
        //                     std::pair mountainSeed = voronoiSites[cellIndex];
        //                     std::pair<int,int> sourceTile = {lerp((int) mountainSeed.first, (int)seed.first, 0.6), lerp((int)mountainSeed.second,(int) seed.second, 0.6)};
        //                     // int width = rint(3,10);
        //                     // int length = rint(3,10);
        //                     // for (int w = 0; w < width; w++) {
        //                     //      for (int l = 0; l < length; l++) {
        //                     //          int ti = rTileIndex[{sourceTile.first+w,sourceTile.second+l}];
        //                     if (rTileIndex.find({sourceTile.first,sourceTile.second}) != rTileIndex.end()) {
        //                          int ti = rTileIndex[{sourceTile.first, sourceTile.second}];
        //                     rTileWater[ti] = true;
        //                              rTileType[ti] = Tile::RiverSource;
        //                              riverSources.push_back(sourceTile);
        //                     }
        //                     //     }
        //                     // }
        //                 }
        //                 if (foundMountain == true) break;
        //             }
        //         }
        //         if (waterMap[mapCoord.first][mapCoord.second] == 6) {
        //             // put sources from highlands or groundwater in random spot in cell
        //             std::pair<int,int> random = {(int)seed.first + rint((-CELL_SIZE/2)+10,(CELL_SIZE/2)-10),seed.second + rint((-CELL_SIZE/2)+10,(CELL_SIZE/2)-10)};
        //             if (rTileIndex.find({random.first,random.second}) != rTileIndex.end()) {
        //                         int ti = rTileIndex[{random.first,random.second}];
        //                         rTileWater[ti] = true;
        //                         rTileAlt[ti] -= 2;
        //                         rTileType[ti] = Tile::RiverSource;
        //                         riverSources.push_back(random);
        //                     }
        //         }
        //         // add lakes
        //         if (waterMap[mapCoord.first][mapCoord.second] == 5) {
        //             //check if lake takes up more than one cell
        //             // std::vector<std::tuple<int,int,int>> lakePieces = adjGetAll(waterMap,mapCoord.first,mapCoord.second,5,1);
        //             // while (int i = 0 < lakePieces.size()) {
        //             //     lakePieces[i];
        //             //     i++;
        //             // }
        //             // create altitude depressions to fill lakes with
        //              std::pair<int,int> depressionCenter = {seed.first + rint((-CELL_SIZE/2)+10,(CELL_SIZE/2)-10),seed.second + rint((-CELL_SIZE/2)+10,(CELL_SIZE/2)-10)};
        //              if (rTileIndex.find({depressionCenter.first,depressionCenter.second}) != rTileIndex.end()) {
        //              int ti = rTileIndex[{depressionCenter.first,depressionCenter.second}];
        //              //add depressionCenter to lake centers
        //              riverEnds.push_back(depressionCenter);
        //              lakeOrEnd[{depressionCenter.first, depressionCenter.second}] = true;
        //              int altThreshold = rTileAlt[ti];
        //              recursiveLower(depressionCenter.first, depressionCenter.second,rint(1,4));
        //              // fill all tiles with water that are lower than the original center tile of the new lake
        //              recursiveFill(depressionCenter.first, depressionCenter.second,altThreshold);
        //              }
        //         }
        //         // add river ends
        //         if (waterMap[mapCoord.first][mapCoord.second] == 4) { // at ocean
        //              riverEnds.push_back(seed);
        //             lakeOrEnd[{seed.first, seed.second}] = false;
        //         }
        //           if (waterMap[mapCoord.first][mapCoord.second] == 7) { // inland
        //                 std::pair<int,int> center = {(int)seed.first + rint((-CELL_SIZE/2)+10,(CELL_SIZE/2)-10), (int)seed.second + rint((-CELL_SIZE/2)+8,(CELL_SIZE/2)-8)};
        //              riverEnds.push_back(center);
        //              lakeOrEnd[{center.first, center.second}] = false;
        //         }
        //     }
        // // create nearest neighbor lookup for lakes centers
        // SeedCloud riverEndsCloud;
        // riverEndsCloud.seeds = riverEnds;

        // using my_kd_tree_t = nanoflann::KDTreeSingleIndexAdaptor<
        //     nanoflann::L2_Simple_Adaptor<float, SeedCloud>,
        //     SeedCloud, /* Our dataset */
        //     2 /* 2D space */
        //     >;

        // my_kd_tree_t riverEndsTree(2 /*dim*/, riverEndsCloud, {10} /* max leaf size */);
        // riverEndsTree.buildIndex();
        // // generate river flow tiles, from source to nearest riverEnd
        // for (int i = 0; i < riverSources.size(); i++) {
        //         //get seed of cell
        //         std::pair<float,float> source = riverSources[i];
        //          std::vector<float> queryPoint = {source.first, source.second};
        //         const size_t numResults = 1;
        //         uint32_t retIndex[numResults]; // nearest neighbor index
        //         float outDistSqr[numResults]; //distance between nn and current
        //         riverEndsTree.knnSearch(&queryPoint[0], numResults, &retIndex[0], &outDistSqr[0]);
        //         // flow from source to nearest river end
        //         applyRiverTiles(source.first, source.second,riverEnds[retIndex[0]]);
        // }


float rangePenalty(float originalValue, float minValue, float maxValue, float adjustedValue) {
    if (originalValue >= minValue && originalValue <= maxValue) {
        return adjustedValue;
    } else {
        float distance = 0.0f;

        if (originalValue < minValue) {
            distance = minValue - originalValue;
        } else if (originalValue > maxValue) {
            distance = originalValue - maxValue;
        }

        float penalty = exp(0.5 * distance);  // Adjust the factor for more or less penalty
        return adjustedValue - penalty;
    }
}


    template<typename T>
        void WorldSpawner::printMap() {
        for (int x = 0; x < WIDTH; ++x) {
            for (int y = 0; y < HEIGHT; ++y) {
                cout << map[x][y] << " ";
            }
            cout << endl;
        }
    }



std::array<float, TILE_AMOUNT> generateTileChances() {
  std::array<float, TILE_AMOUNT> chances;
//generate Voronoi Noise
        FastNoiseLite noise;
        noise.SetNoiseType(FastNoiseLite::NoiseType_Cellular);
        noise.SetFrequency(0.02f);  // Adjust scale
        noise.SetCellularJitter(1.0f);  // Controls cell shape variation
        noise.SetCellularDistanceFunction(FastNoiseLite::CellularDistanceFunction_Euclidean);
        noise.SetCellularReturnType(FastNoiseLite::CellularReturnType_CellValue);
// secondary Noise for tile generation
        FastNoiseLite pnoise;
        pnoise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
        pnoise.SetFrequency(0.02f);

	std::array<float, TILE_AMOUNT> chances;
        int index = 0;

	for (int i = 0; i < TILE_AMOUNT; i++) {
	  float chance = (pnoise.GetNoise((float)y, (float)x) + 1.0) * 0.5;
	  chances[index] = chance;
	}         			 
	return chances;
}

// Function to generate Voronoi sites, and each biome, altitude, avg temperature generated before will be assigned to a voronoi site
std::array<Coord, BIOME_AMOUNT> WorldSpawner::generateVoronoiSites() {
    FastNoiseLite noise;
    noise.SetNoiseType(FastNoiseLite::NoiseType_Cellular);
    std::array<Coord, BIOME_AMOUNT> voronoiSites;
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            float vx = (rand() % WORLD_WIDTH);
            float vy = (rand() % WORLD_HEIGHT);
            voronoiSites[i] = {vy, vx};
        }
    }
    return voronoiSites;
}


Tile getTileType(int biome, float chance) {
    switch (biome) {
        case 1: //desert
            if (chance < 0.70) {
                return Tile::Sand;
            } else if (chance < 0.75) {
                return Tile::SandySoil;
            } else if (chance < 0.83) {
                return Tile::AridSoil;
            } else if (chance < 0.90) {
                return Tile::Hardpan;
            } else return Tile::Gravel;
            break;
        case 2: //Grasslands
            if (chance < 0.80) {
                return Tile::LoamSoil;
            } else if (chance < 0.90) {
            } else return Tile::Gravel;
            break;
        case 3: //Savanna
            if (chance < 0.10) return Tile::AridSoil;
            if (chance < 0.55) return Tile::SandySoil;
            if (chance < 0.85) {
                return Tile::LoamSoil;
            } else {
                return Tile::ClaySoil;
            }
            break;
        case 4: //Wetlands
            if (chance < 0.50) {
                return Tile::PeatSoil;
            }
            if (chance < 0.70) {
                return Tile::Gleysol;
            }
            if (chance < 0.85) {
                return Tile::SiltySoil;
            } else return Tile::ClaySoil;
            break;
        case 5: //Forest
            if (chance < 0.05) return Tile::Podzol;
            if (chance < 0.75)  {
                return Tile::LoamSoil;
            } if (chance < 0.90) {
                return Tile::ClaySoil;
            } else return Tile::SiltySoil;
            break;
        case 6: //Taiga
            if (chance < 0.60) return Tile::Podzol;
            if (chance < 0.65) {
                return Tile::LoamSoil;
            }
            if (chance < 0.75) {
                return Tile::Gleysol;
            } else {
                return Tile::PeatSoil;
            }
            break;
        case 7: //Jungle
            if (chance < 0.70) {
                return Tile::Oxisol;
            }
            if (chance < 0.85) {
                return Tile::LoamSoil;
            } else return Tile::Gleysol;
            break;
        case 8: //Rocky
            if (chance < 0.80) {
                return Tile::Stone;
            } else if (chance < 0.85) {
                return Tile::RockySoil;
            } else return Tile::Gravel;
            break;
        case 9: //tundra
            if (chance < 0.85) {
                return Tile::FrozenSoil;
            } else if (chance < 0.96) {
                return Tile::Ice;
            } else return Tile::PeatSoil;
            break;
        case 10: //cold desert
            if (chance < 0.75) {
                return Tile::Sand;
            } else if (chance < 0.80) {
                return Tile::AridSoil;
            } else if (chance < 0.95) {
                return Tile::FrozenSoil;
            } else return Tile::Gravel;
            break;
        default:
            return Tile::DeepWater;
    }
    return Tile::DeepWater;
}


void generateTileTypes(std::array<float, TILE_AMOUNT> chances, const std::array<Coord, BIOME_AMOUNT>& voronoiSites) {
        SeedCloud cloud;

        cloud.seeds = voronoiSites;

        using my_kd_tree_t = nanoflann::KDTreeSingleIndexAdaptor<
            nanoflann::L2_Simple_Adaptor<float, SeedCloud>,
            SeedCloud, /* Our dataset */
            2 /* 2D space */
            >;

        my_kd_tree_t tree(2 /*dim*/, cloud, {10} /* max leaf size */);
        tree.buildIndex();

// CREATE ALL TILES FOR STARTING CELLS
        int tiles = 0; 

// zoom into tile
        int cx = rint(WIDTH / 8, 7 * WIDTH / 8);
        int cy = rint(HEIGHT / 8, 7 * HEIGHT / 8);
// select cell as randomized spawn point
        bool selected = false;
        while (!selected){
 ;           if (biomeMap[cy][cx] == 0) {
                cx = rint(WIDTH / 7, 6 * WIDTH / 7);
                cy = rint(HEIGHT / 7, 6 * HEIGHT / 7);
            } else selected = true;
        }

        uint32_t seedIndex = cy * HEIGHT + cx;
        std::pair<float, float> sVSeed = voronoiSites[seedIndex];

//generate tiles near to randomized spawn point
        currentXMin = sVSeed.second - STARTING_MAP_WIDTH / 2;
        currentXMax = sVSeed.second + STARTING_MAP_WIDTH / 2;
        currentYMin = sVSeed.first - STARTING_MAP_HEIGHT / 2;
        currentYMax = sVSeed.first + STARTING_MAP_HEIGHT / 2;

        for (int y = currentYMin; y < currentYMax; y++) {
            for (int x = currentXMin; x < currentXMax; x++) {
                //store index of tile linked to coords for future linking
                rTileIndex[{y,x}] = index++;
                tileCoords[index] = {y,x};
                std::vector<float> queryPoint = {(float)y, (float)x};
                // Perform the nearest neighbor search, numResults is # of neighbors
                const size_t numResults = 5;
                uint32_t retIndex[numResults]; // nearest neighbor index
                float outDistSqr[numResults]; //distance between nn and current

                tree.knnSearch(&queryPoint[0], numResults, &retIndex[0], &outDistSqr[0]);
// check if tile is still part of current cell
                    int ti = rTileIndex[{y,x}];

		    //TODO: optimize this part
                    // calculate altitude based on weighted average
                    float currentAlt = 0;
                    float strengths[numResults];
                    float denominator = 0.0000000001;

		    
                    for (int i = 0; i < numResults; i++) {
                        int index = (int)retIndex[i];
                        if (index >= 0 && index < rMapsLink.size()) {
                            std::pair<float,float> select = rMapsLink[index];
                        // get inversed distances for strengths
                        strengths[i] = 1 / (outDistSqr[i] + CELL_SIZE / 2);
                        float rTileAlt = altitudeMap[select.first][select.second];
                        currentAlt += strengths[i] * rTileAlt;
                        denominator += strengths[i];
                        }
                    }
		    
                    int calcAlt = (int) currentAlt / denominator;
                    rTileAlt.push_back(calcAlt);

                    std::pair<float,float> cell = rMapsLink[retIndex[0]];
                     // set tile's owner Cell index
                    rTileCellIndex.push_back(retIndex[0]);
                    cout << " Inserting Tile Cell: " << rTileCellIndex.back();
                    cout << " Tile Cell Size: " << rTileCellIndex.size();
                    cout << " Tile Index: " << index;
                    // set rTileType based on chance from most common tiles of two closest seeds' biomes
                    if (cell.first >= 0 && cell.first < HEIGHT && cell.second >= 0 && cell.second < WIDTH) {
                        int biome = biomeMap[cell.first][cell.second];
                        //int secondBiome = biomeMap[secondCell.first][secondCell.second];
			tileTypes[index] = getTileType(biome, chance);
                    }
            }
	}
}

void moveRegionsToChunks(std::vector< std::vector<uint16_t> > & temperatureMap, std::vector< std::vector<uint16_t >  > & humidityMap, Array2D& humidityTable, Array2D& minTemperatureTable) {
  for (int i = 0; i < LENGTH_CHUNKS; i++) {
    for (int j = 0; j < HEIGHT_CHUNKS; j++) {
        // for each chunk, count tiles per region slot
        std::unordered_map<uint16_t, uint16_t> regionCounts;
	int totalCount = 0;
      for (int k = 0; k < CHUNK_SIZE; k++) {
        uint16_t region =
            tileRegionSlot[(j * CHUNK_LENGTH) + (k / CHUNK_LENGTH)]
	  [(i * CHUNK_LENGTH) + (k % CHUNK_LENGTH)];
        regionCounts[region]++;
	totalCount++;
      }
      // calculate values of each chunk based on region counts
      for (const auto& pair : regionCounts) {
	auto key = pair.first;
        auto value = pair.second;

        humidityTable[i][j] += static_cast<float>(humidityMap[key / CHUNK_LENGTH][key % CHUNK_LENGTH] *
            (value / totalCount));

        temperatureTable[i][j] += static_cast<float>(
            temperatureMap[key / CHUNK_LENGTH][key % CHUNK_LENGTH] *
            (value / totalCount));	
      }      	
      }      
    }
}

void calculateChunkPrecipitationEquilibriums() {


}


    int main() {
        FastNoiseLite noiseLayer;
        noiseLayer.SetSeed(1434933);
        noiseLayer.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
        noiseLayer.SetFrequency(0.05f);
        noiseLayer.SetFractalType(FastNoiseLite::FractalType_FBm);
        noiseLayer.SetFractalLacunarity(1.8f); //chaos
        noiseLayer.SetFractalOctaves(7); //more detail, extremes appear in cells

        // MAPS
        WorldSpawner world = new WorldSpawner();
        world.generateAltitudeMap(noiseLayer);
        world.generateOceansOnMaps(oceanMap, altitudeMap, landsMap, landThreshold);
        world.cleanAltitudeMap();
        world.generateLandsMap()
        world.generateWaterMap();
        world.generateWBDistances();
        world.generateTemperatureMap();
        world.generateHumidityMap();
        world.generateBiomes();
        world.getRiversFromGroundwater();
        // cout << "Ocean" << endl;
        //printMap(oceanMap);
        cout << "Lands" << endl;
        printMap();
        cout << "Altitude" << endl;
        printMap();
        cout << "Water Bodies" << endl;
        printMap();
        cout << "Temperature" << endl;
        printMap();
        cout << "Humidity" << endl;
        printMap();
        cout << "Biomes" << endl;
        printMap();
        generateTiles();
        spawnFirstPlants();
        cout << "PLANTS SPAWNED" << endl;
        spawnAnimals();
        cout << "TILE AMOUNT:" << rTileIndex.size() << endl;
        int cell = rTileCellIndex[5];
        cout << " Cell: " << cell;
        spawnScavengeables();
        return 0;
    }
