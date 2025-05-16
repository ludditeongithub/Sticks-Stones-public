#include "worldgen.hpp"

//TO-DO: refactor all code to use adjacent tiles based on nearest Voronoi seeds, not square cells

// 1. Generate Ocean and Land
void generateOceanMap() {
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
void markCoasts() {
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
void applyExtraHighlandsAndMountains() {
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

void generateLandsMap() {
    markCoasts();
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
    applyExtraHighlandsAndMountains();
}


void extendRiversFromSource(int y, int x, std::vector<std::vector<bool>>& visited) {
    // Base case 1: Hits the edge of the map
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) {
        return;  // Stop recursion if out of bounds
    }

    // Base case 2: Tile is visited
    if (visited[y][x]) {
        return;
    }

    visited[y][x] = true;

    // Base case 3: Hits an ocean tile
    if (oceanMap[y][x] == 0) {
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


    // Move in four directions
    int dx[] = {-1, 0, 1, 0};  // x-direction (left, right)
    int dy[] = {0, 1, 0, -1};  // y-direction (up, down)

    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        // Ensure neighbors are within bounds
        if (nx >= 0 && nx < WIDTH && ny >= 0 && ny < HEIGHT) {
            // change current tile to river continues
            if (waterMap[ny][nx] == 3 || waterMap[ny][nx] == 6 || waterMap[ny][nx] == 2 || waterMap[ny][nx] == 5 )  {
                 // Check river continuation conditions
            if (waterMap[y][x] != 2 && waterMap[y][x] != 6 && waterMap[y][x] != 5 && landsMap[y][x] != 5) {
            if (altitudeMap[y][x] < altitudeMap[ny][nx] ) {
                    waterMap[y][x] = 3;  // Continue river
                }
            }
            } extendRiversFromSource(ny, nx, visited);
        }
    }
}

void markRiverEnds() {
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


void generateWaterMap() {
    waterMap = oceanMap;

    // generate river sources
    for (int y = 1; y < HEIGHT + 1; y++) {
        for (int x = 1; x < WIDTH + 1; x++) {  // Start from 1 to avoid borders
            // Start from 1 to avoid borders
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
                        std::fill(visited.begin(), visited.end(), std::vector<bool>(HEIGHT + 1, false));
                        if (waterMap[y][x] == 2) extendRiversFromSource(y,x,visited);
                    }
                }

     for (int y = 1; y < HEIGHT + 1; y++) {
        for (int x = 1; x < WIDTH + 1; x++) {
            //generate rivers from lakes
            std::fill(visited.begin(), visited.end(), std::vector<bool>(HEIGHT + 1, false));
            if (waterMap[y][x] == 5 && rand() / (float) RAND_MAX < riverFromLakeChance) extendRiversFromSource(y,x,visited);
        }
     }
}

// BFS function to calculate the distance from the ocean
std::vector<std::vector<int>> calculateOceanDistance(bool lake, bool river) {
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

std::vector<std::vector<int>> oceanDistance(HEIGHT, std::vector<int>(WIDTH, WIDTH * HEIGHT));

void generateWBDistances() {
    oceanDistance = calculateOceanDistance(false, false);
}

void generateTemperatureMap() {
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

std::vector<std::tuple<float, bool, bool>> humidityAndRainShadowEffects(int y, int x, int water, bool biomes) {
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

float totalCreatedHumidity(int y, int x) {
    float createdhumidity = 0.0; int waterBody;
    for (int c = 0; c < 3; c++) {
        if (c == 0) waterBody = 0;
        if (c == 1) waterBody = 5;
        if (c == 2) waterBody = 3;
        std::vector<std::tuple<float,bool,bool>> waterBodies = humidityAndRainShadowEffects(y,x,waterBody,false);
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

// Function to generate the humidity map based on distance to ocean and altitude
void generateHumidityMap() {
    // Create a distance map to store the distance from the nearest ocean
    // Get maps for the ocean and lake distances using BFS
    // Set the humidity values based on altitude and distance from the ocean
    for (int x = 0; x < WIDTH; ++x) {
        for (int y = 0; y < HEIGHT; ++y) {
            if (oceanMap[y][x] == 0) {  // Ocean
                humidityMap[y][x] = 0;
            } else {
                // Humidity will be influenced by distance to the ocean and elevation
                float potentialhumidity = 0.0;
                int humidity;

                //latitudinal humidity effects
                //make measurements relative, no matter HEIGHT
                float adjustedHEIGHT = 1.0;
                float adjustedLat = float(x) / HEIGHT;
                float equator = 0.5;
                float latitude = std::abs(adjustedLat - equator);
                float latEffect = 0.0;

                // Simulate Hadley Effect, which lowers humidity at 30 and 90, raises at 0 and 60
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
                float createdHumidity = ((humidityMult * totalCreatedHumidity(y, x)) * evap);
                //potentialhumidity += fmax(3,((0.6 * (pow((temperatureMap[y][x] / 2.4), 1.5) - pow(landsMap[x][y],2.1))) - 30));

                humidityMap[y][x] = fmax(1, fmin(120, createdHumidity - latEffect));
                //potentialHumidityMap[y][x] = potentialhumidity;
                //humidityMap[y][x] = fmax(1, fmin(100, fmin(createdhumidity, potentialhumidity)));
            }
        }
        cout << endl;
    }
}

void factorWetlandsJunglesAndForests(int s) {
    for (int x = s; x < WIDTH; x+=5) {
        for (int y = s; y < HEIGHT; y++) {
            if (oceanMap[y][x] == 0) continue;
            float createdhumidity = 0.0; int biome;
            for (int c = 0; c < 3; c++) {
                if (c == 0) biome = 4;
                if (c == 1) biome = 5;
                if (c == 2) biome = 7;
                std::vector<std::tuple<float,bool,bool>> biomes = humidityAndRainShadowEffects(y,x,biome,true);
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
                    if (humidityMap[y][x] > 120) humidityMap[y][x] = 120;
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
void generateBiomes() {
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
        factorWetlandsJunglesAndForests(s);
    }
}


void generateAltitudeMap(FastNoiseLite noise) {
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            // Generate noise value in range [-1, 1]
            float noiseValue = noise.GetNoise((float)y, (float)x);
            // Map the noise value to a HEIGHT range (e.g., 0 to 255)
            int altitude = static_cast<int>(pow((noiseValue * 23), 1.2)); // Converts from [-1, 1] to [-100, 100]
            altitudeMap[y][x] = altitude;
        }
    }
}

void getRiversFromGroundwater() {
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            //skip tiles that already have water
            if (waterMap[y][x] != 1) continue;
            if (oceanMap[y][x] == 0) continue;
            if (humidityMap[y][x] > groundWaterThreshold) {
                if (rand() / (float) RAND_MAX > riverFromGroundwaterChance) {
                    waterMap[y][x] = 6; //river source from groundwater
                     std::fill(visited.begin(), visited.end(), std::vector<bool>(HEIGHT + 1, false));
                     extendRiversFromSource(y,x,visited);
                }
            }
            }
        }
    // mark river ends
    markRiverEnds();
}


void cleanAltitudeMap() {
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            if (altitudeMap[y][x] < landThreshold) {
                altitudeMap[y][x] = 0;
            }
        }
    }
}

void addDepressions() {
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
// Function to generate Voronoi sites, and each biome, altitude, avg temperature generated before will be assigned to a voronoi site
void generateVoronoiSites() {
    FastNoiseLite noise;
    noise.SetNoiseType(FastNoiseLite::NoiseType_Cellular);
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            float vx = (rand() % WORLD_WIDTH);
            float vy = (rand() % WORLD_HEIGHT);
            voronoiSites.push_back({vy, vx});
            mapsLink[y*HEIGHT+x] = {y,x};
        }
    }
}

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

// Generate a cell using the precomputed Voronoi sites
void generateCell(int cellX, int cellY) {
    for (int localX = 0; localX < CELL_SIZE; localX++) {
        for (int localY = 0; localY < CELL_SIZE; localY++) {
            int worldX = cellX * CELL_SIZE + localX;
            int worldY = cellY * CELL_SIZE + localY;

        }
    }
}

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
void applyRiverTiles(int y, int x, const std::pair<int,int> target) {
    int index = tileIndex[{y,x}];
    // base case: reached target
    if (y == target.first && x == target.second) {
        return;
    }
    // base case: reached lake or ocean tile
    if (tileType[index] == Tile::ShallowWater) {
        return;
    }
    int minElevation = tileAlt[index];
    int currentElevation = minElevation;
    int minDist = calculateDistance(y, x, target);
    std::pair<int,int> nextTile = {y, x};

    // Find the lowest elevation neighboring tile
    std::vector<std::pair<int,int>> lowElevTiles;  // To store ties for lowest elevation
    for (const auto& dir : directions) {
        int nx = x + dir.second;
        int ny = y + dir.first;

            int distToTarget = calculateDistance(ny, nx, target);
            int newIndex = tileIndex[{ny,nx}];
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
    int nextIndex = tileIndex[{ty,tx}];
    tileType[nextIndex] = Tile::FlowingWater;
    tileAlt[nextIndex] -= 1;
    applyRiverTiles(ty, tx, target);
}

Tile getTile(int biome, float chance) {
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


void recursiveLower(int y, int x, double decreaseAmount) {
    if (decreaseAmount < 0) {
        return; // Stop recursion if altitude is not decreasing (coast of lake has been reached)
    }

    // Generate a random chance and decide whether to lower the decreaseAmount
    if ((rand() / (float) RAND_MAX) > lakeTileChance) {
        decreaseAmount -= 1;
    }

    // Lower the elevation by the decrease amount
    int index = tileIndex[{y,x}];
    tileAlt[index] -= decreaseAmount;

    // Recursively lower neighboring cells
    for (const auto& delta : std::vector<std::pair<int, int>>{{-1, 0}, {1, 0}, {0, -1}, {0, 1}}) {
        int nx = x + delta.first;
        int ny = y + delta.second;
        if (nx >= 0 && ny >= 0 && nx < WORLD_WIDTH && ny < WORLD_HEIGHT) {
            recursiveLower(nx, ny, decreaseAmount);
        }
    }
}

void recursiveFill(int y, int x, int altThreshold) {
    int index = tileIndex[{y,x}];
    if (tileAlt[index] > altThreshold) {
        return;
    }
    //fill with water
    tileType[index] = Tile::ShallowWater;
    tileWater[index] = true;

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
void generateTiles() {
        cout << "Tiles" << endl;
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

// generate Voronoi sites
        generateVoronoiSites();
// Set up kd-tree to search for nearest site when creating new tiles
        // Create a KD-tree index from the points
        SeedCloud cloud;
        //insert generated Voronoi seeds into cloud
        cloud.seeds = voronoiSites;

        using my_kd_tree_t = nanoflann::KDTreeSingleIndexAdaptor<
            nanoflann::L2_Simple_Adaptor<float, SeedCloud>,
            SeedCloud, /* Our dataset */
            2 /* 2D space */
            >;

        my_kd_tree_t tree(2 /*dim*/, cloud, {10} /* max leaf size */);
        tree.buildIndex();

// CREATE ALL TILES FOR STARTING CELLS
        int tiles = 0; // the number of tiles which have been generated
// get random cell away from edges as starting point

// zoom into tile
        int cx = rint(WIDTH / 8, 7 * WIDTH / 8);
        int cy = rint(HEIGHT / 8, 7 * HEIGHT / 8);
// select cell as randomized spawn point
        bool selected = false;
        while (!selected){
            if (biomeMap[cy][cx] == 0) {
                cx = rint(WIDTH / 7, 6 * WIDTH / 7);
                cy = rint(HEIGHT / 7, 6 * HEIGHT / 7);
            } else selected = true;
        }

        uint32_t seedIndex = cy * HEIGHT + cx;
        std::pair<float,float> sVSeed = voronoiSites[seedIndex];
//generate tiles near to randomized spawn point
        currentXMin = sVSeed.second - STARTING_MAP_WIDTH / 2;
        currentXMax = sVSeed.second + STARTING_MAP_WIDTH / 2;
        currentYMin = sVSeed.first - STARTING_MAP_HEIGHT / 2;
        currentYMax = sVSeed.first + STARTING_MAP_HEIGHT / 2;
        cout << currentXMin << "," << currentXMax << "," << currentYMin << "," << currentYMax << endl;
        int index = 0;
        for (int y = currentYMin; y < currentYMax; y++) {
            for (int x = currentXMin; x < currentXMax; x++) {
                //store index of tile linked to coords for future linking
                tileIndex[{y,x}] = index++;
                tileCoords[index] = {y,x};
                std::vector<float> queryPoint = {(float)y, (float)x};
                // Perform the nearest neighbor search, numResults is # of neighbors
                const size_t numResults = 5;
                uint32_t retIndex[numResults]; // nearest neighbor index
                float outDistSqr[numResults]; //distance between nn and current

                tree.knnSearch(&queryPoint[0], numResults, &retIndex[0], &outDistSqr[0]);
// check if tile is still part of current cell
                    int ti = tileIndex[{y,x}];

                    // calculate altitude based on weighted average
                    float currentAlt = 0;
                    float strengths[numResults];
                    float denominator = 0.0000000001;
                    for (int i = 0; i < numResults; i++) {
                        int index = (int)retIndex[i];
                        if (index >= 0 && index < mapsLink.size()) {
                            std::pair<float,float> select = mapsLink[index];
                        // get inversed distances for strengths
                        strengths[i] = 1 / (outDistSqr[i] + CELL_SIZE / 2);
                        float tileAlt = altitudeMap[select.first][select.second];
                        currentAlt += strengths[i] * tileAlt;
                        denominator += strengths[i];
                        }
                    }
                    int calcAlt = (int) currentAlt / denominator;
                    tileAlt.push_back(calcAlt);

                    std::pair<float,float> cell = mapsLink[retIndex[0]];
                    std::pair<float,float> secondCell = mapsLink[retIndex[1]];
                     // set tile's owner Cell index
                    tileCellIndex.push_back(retIndex[0]);
                    cout << " Inserting Tile Cell: " << tileCellIndex.back();
                    cout << " Tile Cell Size: " << tileCellIndex.size();
                    cout << " Tile Index: " << index;
                    // set tileType based on chance from most common tiles of two closest seeds' biomes
                    if (cell.first >= 0 && cell.first < HEIGHT && cell.second >= 0 && cell.second < WIDTH) {
                        int biome = biomeMap[cell.first][cell.second];
                         int secondBiome = biomeMap[secondCell.first][secondCell.second];
                    float chance = (pnoise.GetNoise((float)y,(float)x) + 1.0) * 0.5;
                    if (rand() / (float)RAND_MAX < 0.8 || biome == 0) { // always water if ocean
                         tileType[ti] = getTile(biome, chance); //closest
                    } else {
                        tileType[ti] = getTile(secondBiome,chance); //second closest
                    }
                    }
                }
            }
             //generate water bodies
        // for (int i = 0; i < (int)tileCellIndex.size(); i++) {
        //         uint32_t index = tileCellIndex[i];
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
        //                     //          int ti = tileIndex[{sourceTile.first+w,sourceTile.second+l}];
        //                     if (tileIndex.find({sourceTile.first,sourceTile.second}) != tileIndex.end()) {
        //                          int ti = tileIndex[{sourceTile.first, sourceTile.second}];
        //                     tileWater[ti] = true;
        //                              tileType[ti] = Tile::RiverSource;
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
        //             if (tileIndex.find({random.first,random.second}) != tileIndex.end()) {
        //                         int ti = tileIndex[{random.first,random.second}];
        //                         tileWater[ti] = true;
        //                         tileAlt[ti] -= 2;
        //                         tileType[ti] = Tile::RiverSource;
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
        //              if (tileIndex.find({depressionCenter.first,depressionCenter.second}) != tileIndex.end()) {
        //              int ti = tileIndex[{depressionCenter.first,depressionCenter.second}];
        //              //add depressionCenter to lake centers
        //              riverEnds.push_back(depressionCenter);
        //              lakeOrEnd[{depressionCenter.first, depressionCenter.second}] = true;
        //              int altThreshold = tileAlt[ti];
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
    }

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


// APPLY PLANT SPAWNS - get random value from noise generation
// based on factors:
// biome type
// soil type
// temperature
// humidity
// neighboring plants
void spawnPlants() {
    //TEST
     for (int i = 0; i < (int)tileIndex.size(); i++) {
         std::pair<int,int> tile = tileCoords[i];
         float threshold = 0.0; // amount plant must pass to be planted
         float temp = 0.0;

         float optimal = 0.55;
         float great = 0.4;
         float good = 0.25;
         float poorly = 0.05;
         float rarely = 0.01;

         Tile type = tileType[i];
         Plant plant = Plant::Null;
         Grass grass = Grass::Null;
         // invalid tiles
         if (type == Tile::Ice) continue;
         if (type == Tile::FrozenSoil) continue;
         if (type == Tile::Gravel) continue;
         if (type == Tile::Stone) continue;
         if (type == Tile::ShallowWater) continue;
         if (type == Tile::FlowingWater) continue;
         if (type == Tile::DeepWater) continue;
         if (type == Tile::Sand) continue;
         if (type == Tile::Snow) continue;
         uint32_t cell = tileCellIndex[i];
         cout << " Cell: " << cell;
         std::pair<float,float> cellCoord = mapsLink[cell];
         cout << " Cell Coords: " << cellCoord.first << "," << cellCoord.second << endl;
         int biome = biomeMap[(int)cellCoord.first][(int)cellCoord.second];
         int temperature = temperatureMap[(int)cellCoord.first][(int)cellCoord.second];
         int humidity = humidityMap[(int)cellCoord.first][(int)cellCoord.second];

// PLANT CATEGORY RARITIES - chance of each plant type spawning in each biome, on a tile, not adjusted for other checks (trees have higher raw spawn rate due to not being able to spawn next to other trees)
// the threshold that the random generated number needs to pass to ensure that the plant species even has a chance of competing.

    //% of much non-grass plants appear on tiles and grass plants respectively
    float treesChance = 0.0;
    float citrusChance = 0.0;
    float stoneChance = 0.0;
    float pomeChance = 0.0;
    float oliveChance = 0.0;
    float mossChance = 0.0;
        float fernChance = 0.0;
        float bushChance = 0.0;
        float succulentChance = 0.0;
        float berryShrubChance = 0.0;
        float floweringChance = 0.0;
        float fruitVeggieChance = 0.0;
        float leafyChance = 0.0;
        float rootChance = 0.0;
        float reedChance = 0.0;
        float tuberChance = 0.0;
        float bulbChance = 0.0;
        float grainChance = 0.0;
        float grapevineChance = 0.0;
        float herbChance = 0.0;
        float textileChance = 0.0;
    float plantCoverage = 0.0;
    float grassCoverage = 0.0;

    if (biome == 1) {
        treesChance = 0.04; // acacia
        citrusChance = 0.0;
        stoneChance = 0.0;
        pomeChance = 0.0;
        oliveChance = 0.06;
        mossChance = 0.0;
        fernChance = 0.0;
        bushChance = 0.45;
        succulentChance = 0.7;
        berryShrubChance = 0.0;
        leafyChance = 0.00;
        rootChance = 0.0;
        tuberChance = 0.0;
        bulbChance = 0.06;
        grainChance = 0.0;
        grapevineChance = 0.0;
        herbChance = 0.075;
        textileChance = 0.02;

        plantCoverage = 0.15;
        grassCoverage = 0.03;
    }
    if (biome == 2) {
        treesChance = 0.2;
        citrusChance = 0.0;
        stoneChance = 0.0;
     pomeChance = 0.0;
     oliveChance = 0.0;
     mossChance = 0.2;
     fernChance = 0.2;
     bushChance = 0.3;
     succulentChance = 0.06;
     berryShrubChance = 0.2;
     leafyChance = 0.2;
     rootChance = 0.1;
     reedChance = 0.0;
     tuberChance = 0.04;
     bulbChance = 0.06;
     grainChance = 0.35;
     grapevineChance = 0.0;
     herbChance = 0.25;
     textileChance = 0.06;

     plantCoverage = 0.2;
     grassCoverage = 0.97;
    }
    if (biome == 3) {
    treesChance = 0.80;
    citrusChance = 0.08;
    stoneChance = 0.08;
    pomeChance = 0.0;
    oliveChance = 0.08;
    mossChance = 0.04;
    fernChance = 0.08;
    bushChance = 0.6;
    succulentChance = 0.16;
    berryShrubChance = 0.12;
    leafyChance = 0.08;
    rootChance = 0.1;
    tuberChance = 0.08;
    bulbChance = 0.12;
    grainChance = 0.2;
    grapevineChance = 0.0;
    herbChance = 0.2;
    textileChance = 0.04;

    plantCoverage = 0.25;
    grassCoverage = 0.75;
}
if (biome == 4) {
    treesChance = 0.3;
    citrusChance = 0.0;
    stoneChance = 0.0;
    pomeChance = 0.0;
    oliveChance = 0.0;
    mossChance = 0.15;
    fernChance = 0.3;
    bushChance = 0.3;
    reedChance = 0.4;
    succulentChance = 0.06;
    berryShrubChance = 0.09;
    leafyChance = 0.0; // increase when adding duckweed and other water plants
    rootChance = 0.0; // increase when adding wetland root plants
    tuberChance = 0.0; // increase when adding water tubers
    bulbChance = 0.0;
    grainChance = 0.3;
    grapevineChance = 0.0;
     herbChance = 0.3;
    textileChance = 0.02;

    plantCoverage = 0.55;
    grassCoverage = 0.35;
}
if (biome == 5) {
    treesChance = 0.92;
    citrusChance = 0.02;
    stoneChance = 0.02;
    pomeChance = 0.0;
    oliveChance = 0.0;
    mossChance = 0.25;
    fernChance = 0.35;
    bushChance = 0.2;
    reedChance = 0.05;
    succulentChance = 0.04;
    berryShrubChance = 0.1;
    leafyChance = 0.1;
    rootChance = 0.1;
    tuberChance = 0.08;
    bulbChance = 0.07;
    grainChance = 0.1;
    grapevineChance = 0.04;
    herbChance = 0.18;
    textileChance = 0.02;

    plantCoverage = 0.93;
    grassCoverage = 0.08;
}
if (biome == 6) {
    treesChance = 0.85;
    citrusChance = 0.0;
    stoneChance = 0.0;
    pomeChance = 0.0;
    oliveChance = 0.0;
    mossChance = 0.2;
    fernChance = 0.14;
    bushChance = 0.2;
    succulentChance = 0.02;
    berryShrubChance = 0.2;
    leafyChance = 0.08;
    rootChance = 0.08;
    tuberChance = 0.02;
    bulbChance = 0.04;
    grainChance = 0.06;
    grapevineChance = 0.0;
     herbChance = 0.08;
    textileChance = 0.02;

    plantCoverage = 0.94;
    grassCoverage = 0.05;
}
if (biome == 7) {
    treesChance = 0.85;
    citrusChance = 0.02;
    stoneChance = 0.02;
    pomeChance = 0.0;
    oliveChance = 0.0;
    mossChance = 0.2;
    fernChance = 0.3;
    bushChance = 0.2;
    reedChance = 0.02;
    succulentChance = 0.0;
    berryShrubChance = 0.2;
    leafyChance = 0.05; //add more later
    rootChance = 0.06;
    tuberChance = 0.05;
    bulbChance = 0.04;
    grainChance = 0.07;
    grapevineChance = 0.04;
     herbChance = 0.18;
    textileChance = 0.02;

    plantCoverage = 0.96;
    grassCoverage = 0.04;
}
if (biome == 8) {
    treesChance = 0.25;
    citrusChance = 0.0;
    stoneChance = 0.0;
    pomeChance = 0.0;
    oliveChance = 0.0;
    mossChance = 0.5;
    fernChance = 0.4;
    bushChance = 0.5;
    succulentChance = 0.3;
    berryShrubChance = 0.1;
    leafyChance = 0.3;
    rootChance = 0.2;
    tuberChance = 0.2;
    bulbChance = 0.15;
    grainChance = 0.04;
    herbChance = 0.05;
    grapevineChance = 0.05;
    textileChance = 0.01;

    plantCoverage = 0.2;
    grassCoverage = 0.1;
}
if (biome == 9) {
    treesChance = 0.0;
    citrusChance = 0.0;
    stoneChance = 0.0;
    pomeChance = 0.0;
    oliveChance = 0.0;
    mossChance = 0.6;
    fernChance = 0.06;
    bushChance = 0.4;
    succulentChance = 0.07;
    berryShrubChance = 0.0;
    leafyChance = 0.2;
    rootChance = 0.2;
    tuberChance = 0.0;
    bulbChance = 0.0;
    grainChance = 0.0;
    grapevineChance = 0.0;
    herbChance = 0.02;
    textileChance = 0.0;

    plantCoverage = 0.15;
    grassCoverage = 0.075;
}
if (biome == 10) {
    treesChance = 0.0; // make trees later
    citrusChance = 0.0;
    stoneChance = 0.0;
    pomeChance = 0.0;
    oliveChance = 0.0;
    mossChance = 0.2;
    fernChance = 0.05;
    bushChance = 0.3;
    succulentChance = 0.2;
    berryShrubChance = 0.05;
    leafyChance = 0.15;
    rootChance = 0.15;
    tuberChance = 0.05;
    bulbChance = 0.05;
    grainChance = 0.0;
    grapevineChance = 0.0;
    herbChance = 0.02;
    textileChance = 0.03;

    plantCoverage = 0.1;
    grassCoverage = 0.04;
}
constexpr std::array<Plant, 4> trees = {
    Plant::DeciduousTree,
    Plant::EvergreenTree,
    Plant::PioneerTree,
    Plant::TropicalTree
};

// SPAWN ALL PLANTS
if (rand() / (float) RAND_MAX < plantCoverage) {
if (rand() / (float) RAND_MAX < treesChance) {
if (adjCheckList(tileIndex, tilePlant, (int)tile.first, (int)tile.second, trees, 1))  {
     // TREES
         //if tree is adjacent, skip trees
         // Deciduous
temp = 0;
    if (type == Tile::Podzol) temp += poorly;
         if (type == Tile::LoamSoil) temp += optimal;
         if (type == Tile::PeatSoil) temp += poorly;
         if (type == Tile::SandySoil) temp += poorly;
         if (type == Tile::ClaySoil) temp += poorly;
         if (type == Tile::SiltySoil) temp += optimal;
         if (type == Tile::RockySoil) temp = 0;
         if (type == Tile::AridSoil) temp += poorly;
         if (type == Tile::Oxisol) temp += poorly;
         if (type == Tile::Gleysol) temp += rarely;
         rangePenalty(temperature,64,77,temp);
         rangePenalty(humidity,52,78,temp);
         if (temp > threshold) {
             threshold = temp;
             plant = Plant::DeciduousTree;
         }

         // Evergreen
temp = 0;
         if (type == Tile::Podzol) temp += good;
if (type == Tile::LoamSoil) temp += good;
if (type == Tile::PeatSoil) temp += poorly;
if (type == Tile::SandySoil) temp += good;
if (type == Tile::ClaySoil) temp += poorly;
if (type == Tile::SiltySoil) temp += good;
if (type == Tile::RockySoil) temp += poorly;
if (type == Tile::AridSoil) temp += rarely;
if (type == Tile::Oxisol) temp += poorly;
if (type == Tile::Gleysol) temp += poorly;
 rangePenalty(temperature,46,68,temp);
  rangePenalty(humidity,60,87,temp);
if (temp > threshold) {
             threshold = temp;
             plant = Plant::EvergreenTree;
         }

         // Pioneer
temp = 0;
if (type == Tile::Podzol) temp += rarely;
if (type == Tile::LoamSoil) temp += optimal;
if (type == Tile::PeatSoil) temp += great;
if (type == Tile::SandySoil) temp += good;
if (type == Tile::ClaySoil) temp += poorly;
if (type == Tile::SiltySoil) temp += optimal;
if (type == Tile::RockySoil) temp += rarely;
if (type == Tile::AridSoil) temp += poorly;
if (type == Tile::Oxisol) temp += poorly;
if (type == Tile::Gleysol) temp += great;
 rangePenalty(temperature,55,86,temp);
 rangePenalty(humidity,50,80,temp);
 if (temp > threshold && plant != Plant::EvergreenTree && plant != Plant::DeciduousTree) {
             threshold = temp;
             plant = Plant::PioneerTree;
         }
         // Tropical
temp = 0;
if (type == Tile::Podzol) temp += poorly;
if (type == Tile::LoamSoil) temp += optimal;
if (type == Tile::PeatSoil) temp += optimal;
if (type == Tile::SandySoil) temp += good;
if (type == Tile::ClaySoil) temp += poorly;
if (type == Tile::SiltySoil) temp += good;
if (type == Tile::RockySoil) temp = 0;
if (type == Tile::AridSoil) temp += poorly;
if (type == Tile::Oxisol) temp += optimal;
if (type == Tile::Gleysol) temp += optimal;
 rangePenalty(temperature,73,87,temp);
 rangePenalty(humidity,80,120,temp);
 if (temp > threshold) {
             threshold = temp;
             plant = Plant::TropicalTree;
         }
}
}

if (rand() / (float) RAND_MAX < mossChance) {
    // Moss
temp = 0;
    if (type == Tile::Podzol) temp += great;
if (type == Tile::LoamSoil) temp += great;
if (type == Tile::PeatSoil) temp += optimal;
if (type == Tile::SandySoil) temp += good;
if (type == Tile::ClaySoil) temp += good;
if (type == Tile::SiltySoil) temp += great;
if (type == Tile::RockySoil) temp += great;
if (type == Tile::AridSoil) temp = 0;
if (type == Tile::Oxisol) temp += poorly;
if (type == Tile::Gleysol) temp += optimal;
rangePenalty(temperature,40,75,temp);
         rangePenalty(humidity,85,120,temp);
if (temp > threshold) {
        threshold = temp;
        plant = Plant::Moss;
}
}
if (rand() / (float) RAND_MAX < bushChance) {
         // BUSHES
if (type == Tile::Podzol) temp += optimal;
if (type == Tile::LoamSoil) temp += optimal;
if (type == Tile::PeatSoil) temp += great;
if (type == Tile::SandySoil) temp += good;
if (type == Tile::ClaySoil) temp += good;
if (type == Tile::SiltySoil) temp += great;
if (type == Tile::RockySoil) temp += poorly;
if (type == Tile::AridSoil) temp += rarely;
if (type == Tile::Oxisol) temp += great;
if (type == Tile::Gleysol) temp += great;
 rangePenalty(temperature,45,86,temp);
 rangePenalty(humidity,60,87,temp);
 if (temp > threshold) {
             threshold = temp;
             plant = Plant::Bush;
         }
}
if (rand() / (float) RAND_MAX < succulentChance) {
//Cacti
temp = 0;
    if (type == Tile::Podzol) temp += rarely;
if (type == Tile::LoamSoil) temp += great;
if (type == Tile::PeatSoil) temp += poorly;
if (type == Tile::SandySoil) temp += optimal;
if (type == Tile::ClaySoil) temp += good;
if (type == Tile::SiltySoil) temp += great;
if (type == Tile::RockySoil) temp += good;
if (type == Tile::AridSoil) temp += optimal;
if (type == Tile::Oxisol) temp += great;
if (type == Tile::Gleysol) temp += rarely;
rangePenalty(temperature, 45, 86, temp);
rangePenalty(humidity, 1, 30, temp);
if (temp > threshold) {
             threshold = temp;
             plant = Plant::Cactus;
         }
}

// FRUIT TREES
if (rand() / (float) RAND_MAX < citrusChance) {
// Citrus
temp = 0;
    if (type == Tile::Podzol) temp += poorly;
if (type == Tile::LoamSoil) temp += optimal;
if (type == Tile::PeatSoil) temp += good;
if (type == Tile::SandySoil) temp += great;
if (type == Tile::ClaySoil) temp += poorly;
if (type == Tile::SiltySoil) temp += great;
if (type == Tile::RockySoil) temp += rarely;
if (type == Tile::AridSoil) temp += rarely;
if (type == Tile::Oxisol) temp += poorly;
if (type == Tile::Gleysol) temp += poorly;
rangePenalty(temperature, 70, 80, temp);
rangePenalty(humidity, 60, 75, temp);
if (temp > threshold) {
             threshold = temp;
             int ran = rint(0,2);
             if (ran == 0) plant = Plant::OrangeTree;
             if (ran == 1) plant = Plant::LemonTree;
             if (ran == 2) plant = Plant::LimeTree;
         }
}
if (rand() / (float) RAND_MAX < stoneChance) {
// Stone/Drupe
temp = 0;
    if (type == Tile::Podzol) temp += poorly;
if (type == Tile::LoamSoil) temp += optimal;
if (type == Tile::PeatSoil) temp += good;
if (type == Tile::SandySoil) temp += great;
if (type == Tile::ClaySoil) temp += poorly;
if (type == Tile::SiltySoil) temp += great;
if (type == Tile::RockySoil) temp += rarely;
if (type == Tile::AridSoil) temp += rarely;
if (type == Tile::Oxisol) temp += poorly;
if (type == Tile::Gleysol) temp += poorly;
rangePenalty(temperature, 60, 75, temp);
rangePenalty(humidity, 45, 68, temp);
if (temp > threshold) {
             threshold = temp;
             int ran = rint(0,3);
             if (ran == 0) plant = Plant::PeachTree;
             if (ran == 1) plant = Plant::PlumTree;
             if (ran == 2) plant = Plant::CherryTree;
             if (ran == 3) plant = Plant::ApricotTree;
         }
}
if (rand() / (float) RAND_MAX < pomeChance) {
// Pome
temp = 0;
    if (type == Tile::Podzol) temp += poorly;
if (type == Tile::LoamSoil) temp += optimal;
if (type == Tile::PeatSoil) temp += good;
if (type == Tile::SandySoil) temp += great;
if (type == Tile::ClaySoil) temp += poorly;
if (type == Tile::SiltySoil) temp += great;
if (type == Tile::RockySoil)temp += rarely;
if (type == Tile::AridSoil)temp += rarely;
if (type == Tile::Oxisol)temp += poorly;
if (type == Tile::Gleysol)temp += poorly;
rangePenalty(temperature, 55, 72, temp);
rangePenalty(humidity, 55, 75, temp);
if (temp > threshold) {
             threshold = temp;
             int ran = rint(0,1);
             if (ran == 0) plant = Plant::AppleTree;
             if (ran == 1) plant = Plant::PearTree;
     }
}
if (rand() / (float) RAND_MAX < oliveChance) {
// Olive Trees
temp = 0;
    if (type == Tile::Podzol) temp += rarely;
if (type == Tile::LoamSoil) temp += great;
if (type == Tile::PeatSoil) temp += rarely;
if (type == Tile::SandySoil) temp += optimal;
if (type == Tile::ClaySoil) temp += rarely;
if (type == Tile::SiltySoil) temp += great;
if (type == Tile::RockySoil) temp += good;
if (type == Tile::AridSoil) temp += optimal;
if (type == Tile::Oxisol) temp += poorly;
if (type == Tile::Gleysol) temp += rarely;
rangePenalty(temperature, 61, 80, temp);
rangePenalty(humidity, 33, 58, temp);
if (temp > threshold) {
             threshold = temp;
             plant = Plant::OliveTree;
     }
}

if (rand() / (float) RAND_MAX < berryShrubChance) {
// Berry Shrubs
temp = 0;
if (type == Tile::Podzol) temp += good;
if (type == Tile::LoamSoil) temp += optimal;
if (type == Tile::PeatSoil) temp += great;
if (type == Tile::SandySoil) temp += good;
if (type == Tile::ClaySoil) temp += poorly;
if (type == Tile::SiltySoil) temp += great;
if (type == Tile::RockySoil) temp += rarely;
if (type == Tile::AridSoil) temp += rarely;
if (type == Tile::Oxisol) temp += poorly;
if (type == Tile::Gleysol) temp += good;
rangePenalty(temperature, 61, 75, temp);
rangePenalty(humidity, 65, 90, temp);
if (temp > threshold) {
             threshold = temp;
             int ran = rint(0,3);
             if (ran == 0) plant = Plant::BlueberryShrub;
             if (ran == 1) plant = Plant::StrawberryShrub;
         }
}
if (rand() / (float) RAND_MAX < grapevineChance) {
// Grapevines
temp = 0;
if (type == Tile::Podzol) temp += rarely;
if (type == Tile::LoamSoil) temp += optimal;
if (type == Tile::PeatSoil) temp += good;
if (type == Tile::SandySoil) temp += great;
if (type == Tile::ClaySoil) temp += poorly;
if (type == Tile::SiltySoil) temp += great;
if (type == Tile::RockySoil) temp += good;
if (type == Tile::AridSoil) temp += good;
if (type == Tile::Oxisol) temp += poorly;
if (type == Tile::Gleysol) temp += rarely;
rangePenalty(temperature, 61, 80, temp);
rangePenalty(humidity, 45, 68, temp);
if (temp > threshold) {
             threshold = temp;
             plant = Plant::Grapevine;
       }
}
if (rand() / (float) RAND_MAX < grainChance) {
//GRAINS
// Wheat
temp = 0;
if (type == Tile::Podzol) temp += poorly;
if (type == Tile::LoamSoil) temp += optimal;
if (type == Tile::PeatSoil) temp += good;
if (type == Tile::SandySoil) temp += good;
if (type == Tile::ClaySoil) temp += good;
if (type == Tile::SiltySoil) temp += good;
if (type == Tile::RockySoil) temp += poorly;
if (type == Tile::AridSoil) temp += poorly;
if (type == Tile::Oxisol) temp += poorly;
if (type == Tile::Gleysol) temp += rarely;

rangePenalty(temperature, 58, 75, temp);
rangePenalty(humidity, 45, 70, temp);

if (temp > threshold) {
    threshold = temp;
    plant = Plant::Wheat;
}

// Rice
temp = 0;
if (type == Tile::Podzol) temp += poorly;
if (type == Tile::LoamSoil) temp += good;
if (type == Tile::PeatSoil) temp += great;
if (type == Tile::SandySoil) temp += poorly;
if (type == Tile::ClaySoil) temp += optimal;
if (type == Tile::SiltySoil) temp += optimal;
if (type == Tile::RockySoil) temp += poorly;
if (type == Tile::AridSoil) temp += poorly;
if (type == Tile::Oxisol) temp += poorly;
if (type == Tile::Gleysol) temp += great;

rangePenalty(temperature, 75, 92, temp);
rangePenalty(humidity, 75, 100, temp);
if (temp > threshold) {
    threshold = temp;
    plant = Plant::Rice;
}
// Oat
temp = 0;
if (type == Tile::Podzol) temp += rarely;
if (type == Tile::LoamSoil) temp += optimal;
if (type == Tile::PeatSoil) temp += good;
if (type == Tile::SandySoil) temp += great;
if (type == Tile::ClaySoil) temp += poorly;
if (type == Tile::SiltySoil) temp += good;
if (type == Tile::RockySoil) temp += good;
if (type == Tile::AridSoil) temp += good;
if (type == Tile::Oxisol) temp += poorly;
if (type == Tile::Gleysol) temp += rarely;

rangePenalty(temperature, 61, 80, temp);
rangePenalty(humidity, 45, 68, temp);

if (temp > threshold) {
    threshold = temp;
    plant = Plant::Oat;
}
}

// VEGETABLES
if (rand() / (float) RAND_MAX < leafyChance) {
temp = 0;
// Leafy Vegetables
if (type == Tile::Podzol) temp += good;
if (type == Tile::LoamSoil) temp += optimal;
if (type == Tile::PeatSoil) temp += great;
if (type == Tile::SandySoil) temp += poorly;
if (type == Tile::ClaySoil) temp += good;
if (type == Tile::SiltySoil) temp += optimal;
if (type == Tile::RockySoil) temp += rarely;
if (type == Tile::AridSoil) temp += rarely;
if (type == Tile::Oxisol) temp += poorly;
if (type == Tile::Gleysol) temp += great;
rangePenalty(temperature, 50, 72, temp);
rangePenalty(humidity, 65, 88, temp);
if (temp > threshold) {
             threshold = temp;
             int ran = rint(0,1);
             if (ran == 0) plant = Plant::Lettuce;
             if (ran == 1) plant = Plant::Kale;
       }
}
if (rand() / (float) RAND_MAX < rootChance) {
    temp = 0;
    // Root Vegetables
if (type == Tile::Podzol) temp += good;
if (type == Tile::LoamSoil) temp += optimal;
if (type == Tile::PeatSoil) temp += poorly;
if (type == Tile::SandySoil) temp += great;
if (type == Tile::ClaySoil) temp += poorly;
if (type == Tile::SiltySoil) temp += good;
if (type == Tile::RockySoil) temp += rarely;
if (type == Tile::AridSoil) temp += rarely;
if (type == Tile::Oxisol) temp += poorly;
if (type == Tile::Gleysol) temp += rarely;
rangePenalty(temperature, 56, 69, temp);
rangePenalty(humidity, 55, 78, temp);
if (temp > threshold) {
             threshold = temp;
             int ran = rint(0,1);
             if (ran == 0) plant = Plant::Carrot;
             if (ran == 1) plant = Plant::Beets;
       }
}
if (rand() / (float) RAND_MAX < tuberChance) {
    temp = 0;
// Tubers
if (type == Tile::Podzol) temp += good;
if (type == Tile::LoamSoil) temp += great;
if (type == Tile::PeatSoil) temp += poorly;
if (type == Tile::SandySoil) temp += optimal;
if (type == Tile::ClaySoil) temp += poorly;
if (type == Tile::SiltySoil) temp += good;
if (type == Tile::RockySoil) temp += rarely;
if (type == Tile::AridSoil) temp += rarely;
if (type == Tile::Oxisol) temp += poorly;
if (type == Tile::Gleysol) temp += rarely;
rangePenalty(temperature, 60, 67, temp);
rangePenalty(humidity, 65, 88, temp);
if (temp > threshold) {
             threshold = temp;
             plant = Plant::Potatoes;
       }
}
if (rand() / (float) RAND_MAX < bulbChance) {
    // Bulbs
if (type == Tile::Podzol) temp += good;
if (type == Tile::LoamSoil) temp += optimal;
if (type == Tile::PeatSoil) temp += poorly;
if (type == Tile::SandySoil) temp += great;
if (type == Tile::ClaySoil) temp += poorly;
if (type == Tile::SiltySoil) temp += good;
if (type == Tile::RockySoil) temp += rarely;
if (type == Tile::AridSoil) temp += rarely;
if (type == Tile::Oxisol) temp += poorly;
if (type == Tile::Gleysol) temp += rarely;
rangePenalty(temperature, 60, 70, temp);
rangePenalty(humidity, 55, 77, temp);
if (temp > threshold) {
             threshold = temp;
             int ran = rint(0,1);
             if (ran == 0) plant = Plant::Onion;
             if (ran == 1) plant = Plant::Garlic;
       }
}
if (rand() / (float) RAND_MAX < floweringChance) {
    // Flowering Vegetables
if (type == Tile::Podzol) temp += good;
if (type == Tile::LoamSoil) temp += optimal;
if (type == Tile::PeatSoil) temp += poorly;
if (type == Tile::SandySoil) temp += good;
if (type == Tile::ClaySoil) temp += poorly;
if (type == Tile::SiltySoil) temp += great;
if (type == Tile::RockySoil) temp += rarely;
if (type == Tile::AridSoil) temp += rarely;
if (type == Tile::Oxisol) temp += poorly;
if (type == Tile::Gleysol) temp += rarely;
rangePenalty(temperature, 56, 67, temp);
rangePenalty(humidity, 65, 88, temp);
if (temp > threshold) {
             threshold = temp;
             int ran = rint(0,1);
             if (ran == 0) plant = Plant::Cabbage;
             if (ran == 1) plant = Plant::Broccoli;
       }
}
if (rand() / (float) RAND_MAX < fruitVeggieChance) {
   // Fruit Vegetables
if (type == Tile::Podzol) temp += good;
if (type == Tile::LoamSoil) temp += optimal;
if (type == Tile::PeatSoil) temp += poorly;
if (type == Tile::SandySoil) temp += great;
if (type == Tile::ClaySoil) temp += poorly;
if (type == Tile::SiltySoil) temp += good;
if (type == Tile::RockySoil) temp += rarely;
if (type == Tile::AridSoil) temp += rarely;
if (type == Tile::Oxisol) temp += poorly;
if (type == Tile::Gleysol) temp += rarely;
rangePenalty(temperature, 69, 81, temp);
rangePenalty(humidity, 55, 78, temp);
if (temp > threshold) {
             threshold = temp;
             int ran = rint(0,2);
             if (ran == 0) plant = Plant::Tomato;
             if (ran == 1) plant = Plant::Cucumber;
             if (ran == 2) plant = Plant::Pepper;
       }
}

// // Seed and Pod Vegetables
// if (type == Tile::Podzol) temp += good;
// if (type == Tile::LoamSoil) temp += optimal;
// if (type == Tile::PeatSoil) temp += poorly;
// if (type == Tile::SandySoil) temp += great;
// if (type == Tile::ClaySoil) temp += poorly;
// if (type == Tile::SiltySoil) temp += good;
// if (type == Tile::RockySoil) temp += rarely;
// if (type == Tile::AridSoil) temp += rarely;
// if (type == Tile::Oxisol) temp += poorly;
// if (type == Tile::Gleysol) temp += rarely;
// rangePenalty(temperature, 56, 70, temp);
// rangePenalty(humidity, 55, 78, temp);
// if (temp > threshold) {
//              threshold = temp;
//              int ran = rint(0,2);
//              if (ran == 0) plant = Plant::Peas;
//              if (ran == 1) plant = Plant::Beans;
//        }

// HERBS
if (rand() / (float) RAND_MAX < herbChance) {
// Sun-Loving Herbs
if (type == Tile::Podzol) temp += poorly;
if (type == Tile::LoamSoil) temp += optimal;
if (type == Tile::PeatSoil) temp += poorly;
if (type == Tile::SandySoil) temp += great;
if (type == Tile::ClaySoil) temp += poorly;
if (type == Tile::SiltySoil) temp += good;
if (type == Tile::RockySoil) temp += rarely;
if (type == Tile::AridSoil) temp += rarely;
if (type == Tile::Oxisol) temp += poorly;
rangePenalty(temperature, 70, 90, temp);
rangePenalty(humidity, 40, 60, temp);
if (temp > threshold) {
             threshold = temp;
             int ran = rint(0,2);
             if (ran == 0) plant = Plant::Woad;
             if (ran == 1) plant = Plant::Indigo;
             if (ran == 2) plant = Plant::Poppy;
       }
// Shade-Loving Herbs
if (type == Tile::Podzol) temp += good;
if (type == Tile::LoamSoil) temp += optimal;
if (type == Tile::PeatSoil) temp += great;
if (type == Tile::SandySoil) temp += poorly;
if (type == Tile::ClaySoil) temp += good;
if (type == Tile::SiltySoil) temp += good;
if (type == Tile::RockySoil) temp += rarely;
if (type == Tile::AridSoil) temp += rarely;
if (type == Tile::Oxisol) temp += poorly;
rangePenalty(temperature, 50, 70, temp);
rangePenalty(humidity, 60, 80, temp);
if (temp > threshold) {
             threshold = temp;
             int ran = rint(0,1);
             if (ran == 0) plant = Plant::Hemp;
             if (ran == 1) plant = Plant::Ginseng;
       }
// Drought-Tolerant Herbs (Low Water Requirements)
if (type == Tile::Podzol) temp += poorly;
if (type == Tile::LoamSoil) temp += optimal;
if (type == Tile::PeatSoil) temp += poorly;
if (type == Tile::SandySoil) temp += great;
if (type == Tile::ClaySoil) temp += poorly;
if (type == Tile::SiltySoil) temp += good;
if (type == Tile::RockySoil) temp += rarely;
if (type == Tile::AridSoil) temp += great;
if (type == Tile::Oxisol) temp += poorly;
rangePenalty(temperature, 70, 100, temp);
rangePenalty(humidity, 20, 40, temp);
if (temp > threshold) {
             threshold = temp;
             int ran = rint(0,2);
             if (ran == 0) plant = Plant::Lavendar;
             if (ran == 1) plant = Plant::Sage;
             if (ran == 2) plant = Plant::Madder;
       }
// Moisture-Loving Herbs
if (type == Tile::Podzol) temp += great;
if (type == Tile::LoamSoil) temp += optimal;
if (type == Tile::PeatSoil) temp += great;
if (type == Tile::SandySoil) temp += poorly;
if (type == Tile::ClaySoil) temp += good;
if (type == Tile::SiltySoil) temp += great;
if (type == Tile::RockySoil) temp += rarely;
if (type == Tile::AridSoil) temp += poorly;
if (type == Tile::Oxisol) temp += poorly;
rangePenalty(temperature, 60, 80, temp);
rangePenalty(humidity, 60, 80, temp);
if (temp > threshold) {
             threshold = temp;
             plant = Plant::Mint;
       }
// Cold-Hardy Herbs (Cold-Tolerant)
if (type == Tile::Podzol) temp += great;
if (type == Tile::LoamSoil) temp += optimal;
if (type == Tile::PeatSoil) temp += good;
if (type == Tile::SandySoil) temp += poorly;
if (type == Tile::ClaySoil) temp += good;
if (type == Tile::SiltySoil) temp += good;
if (type == Tile::RockySoil) temp += rarely;
if (type == Tile::AridSoil) temp += rarely;
if (type == Tile::Oxisol) temp += poorly;
rangePenalty(temperature, 40, 60, temp);
rangePenalty(humidity, 40, 60, temp);
if (temp > threshold) {
             threshold = temp;
             plant = Plant::Thyme;
       }
}
//TEXTILE
if (rand() / (float) RAND_MAX < textileChance) {
    temp = 0;
if (type == Tile::Podzol) temp += poorly;
if (type == Tile::LoamSoil) temp += optimal;
if (type == Tile::PeatSoil) temp += poorly;
if (type == Tile::SandySoil) temp += great;
if (type == Tile::ClaySoil) temp += poorly;
if (type == Tile::SiltySoil) temp += good;
if (type == Tile::RockySoil) temp += rarely;
if (type == Tile::AridSoil) temp += rarely;
if (type == Tile::Oxisol) temp += poorly;
rangePenalty(temperature, 60, 79, temp);
rangePenalty(humidity, 55, 78, temp);
if (temp > threshold) {
             threshold = temp;
             int ran = rint(0,2);
             if (ran == 0) plant = Plant::Cotton;
             if (ran == 1) plant = Plant::Hemp;
             if (ran == 2) plant = Plant::Flax;
       }
}
if (rand() / (float) RAND_MAX < fernChance) {
    temp = 0;
// Ferns
if (biome == 4) temp += 0.3;
if (biome == 5) temp += 0.2;
if (biome == 6) temp += 0.2;
if (biome == 7) temp += 0.3;
if (biome == 8) temp += 0.2;
if (type == Tile::Podzol) temp += great;
if (type == Tile::LoamSoil) temp += optimal;
if (type == Tile::PeatSoil) temp += optimal;
if (type == Tile::SandySoil) temp += poorly;
if (type == Tile::ClaySoil) temp += rarely;
if (type == Tile::SiltySoil) temp += great;
if (type == Tile::RockySoil) temp += rarely;
if (type == Tile::AridSoil) temp = 0;
if (type == Tile::Oxisol) temp += poorly;
if (type == Tile::Gleysol) temp += great;
rangePenalty(temperature,50,77,temp);
         rangePenalty(humidity,75,115,temp);
if (temp > threshold) {
             threshold = temp;
             plant = Plant::Fern;
         }
}
if (rand() / (float) RAND_MAX < reedChance) {
    temp = 0;
//Reeds
if (biome == 4) temp += 0.15;
if (adjCheck(tileIndex, tileType, (int)tile.first, (int)tile.second, Tile::ShallowWater, 1)) temp += 0.45;
if (type == Tile::Podzol)        temp += good;
if (type == Tile::LoamSoil)      temp += great;
if (type == Tile::PeatSoil)      temp += optimal;
if (type == Tile::SandySoil)     temp += poorly;
if (type == Tile::ClaySoil)      temp += good;
if (type == Tile::SiltySoil)     temp += great;
if (type == Tile::RockySoil)     temp += poorly;
if (type == Tile::AridSoil)      temp = 0;
if (type == Tile::Oxisol)        temp += poorly;
if (type == Tile::Gleysol)       temp += optimal;
rangePenalty(temperature,50,86,temp);
         rangePenalty(humidity,75,120,temp);
if (temp > threshold) {
             threshold = temp;
             plant = Plant::Reed;
        }
}
} // end of plants, checking random value against plant coverage
// GRASSES
if (rand() / (float) RAND_MAX < grassCoverage) {
    temp = 0;
    threshold = 0;
// Prairie Grasses
temp += 0.2;
temp -= (0.05 * adjCheckListCount(tileIndex, tilePlant, (int)tile.first, (int)tile.second, trees, 3));
if (biome == 2) temp += 0.45;
if (biome == 4) temp += 0.05;
if (type == Tile::Podzol) temp += good;
if (type == Tile::LoamSoil) temp += optimal;
if (type == Tile::PeatSoil) temp += rarely;
if (type == Tile::SandySoil) temp += great;
if (type == Tile::ClaySoil) temp += poorly;
if (type == Tile::SiltySoil) temp += optimal;
if (type == Tile::RockySoil) temp += rarely;
if (type == Tile::AridSoil) temp += good;
if (type == Tile::Oxisol) temp += poorly;
if (type == Tile::Gleysol) temp += poorly;
 rangePenalty(temperature,41,86,temp);
 rangePenalty(humidity,30,80,temp);
if (temp > threshold) {
             threshold = temp;
             grass = Grass::Grass;
         }
// Savannah Grasses
    temp = 0;
temp += 0.2;
temp -= (0.05 * adjCheckListCount(tileIndex, tilePlant, (int)tile.first, (int)tile.second, trees, 3));
if (biome == 3) temp += 0.5;
if (type == Tile::Podzol) temp += poorly;
if (type == Tile::LoamSoil) temp += great;
if (type == Tile::PeatSoil) temp += rarely;
if (type == Tile::SandySoil) temp += optimal;
if (type == Tile::ClaySoil) temp += good;
if (type == Tile::SiltySoil) temp += great;
if (type == Tile::RockySoil) temp += rarely;
if (type == Tile::AridSoil) temp += good;
if (type == Tile::Oxisol) temp += good;
if (type == Tile::Gleysol) temp += poorly;
rangePenalty(temperature,64,95,temp);
rangePenalty(humidity,20,60,temp);

if (temp > threshold) {
             threshold = temp;
             grass = Grass::SavannahGrass;
         }
}
tileGrass[i] = grass;
tileObject[i] = plant;
//TESTING
Tile tt = tileType[i];
Plant pt = tilePlant[i];
Grass gt = tileGrass[i];
cout << "coords: " << (int)tile.first << "," << (int)tile.second <<  " biome: " << biome << " tile: " << static_cast<int>(tt) << " plant: " << static_cast<int>(pt) << " grass: " << static_cast<int>(gt) << ";";
}
}

// APPLY ANIMAL SPAWNS
void spawnAnimals() {
     for (int i = 0; i < (int)tileIndex.size(); i++) {
         std::pair<int,int> tile = tileCoords[i];
         float threshold = 0.0; // amount animal must pass to be spawned
         float temp = 0.0;

         float dominant = 0.003;
         float abundant = 0.0015;
         float common = 0.0008;
         float semicommon = 0.0004;
         float uncommon = 0.0002;
         float rare = 0.00008;
         float veryrare = 0.00003;
         float endangered = 0.00001;
         float never = 0.0;

         Tile type = tileType[i];

          uint32_t cell = tileCellIndex[i];
         std::pair<int,int> cellCoord = mapsLink[cell];
         int biome = biomeMap[cellCoord.first][cellCoord.second];
         int temperature = temperatureMap[cellCoord.first][cellCoord.second];
         int humidity = humidityMap[cellCoord.first][cellCoord.second];

         float currentChance = 0.0;
         float pigChance = 0.0;
         float cowChance = 0.0;
         float chickenChance = 0.0;
         float duckChance = 0.0;
         float sheepChance = 0.0;
         float goatChance = 0.0;
         float horseChance = 0.0;
         float oxChance = 0.0;
         float donkeyChance = 0.0;
         float camelChance = 0.0;
         float waterBuffaloChance = 0.0;
         float rabbitChance = 0.0;
         float antelopeChance = 0.0;
         float deerChance = 0.0;
         float mooseChance = 0.0;
         float capybaraChance = 0.0;
         float turtleChance = 0.0;
         float elephantChance = 0.0;
         float bisonChance = 0.0;
         float wolfChance = 0.0;
         float bearChance = 0.0;
         float caribouChance = 0.0;

         // Hot Desert
if (biome == 1) {
    pigChance = rare;
    camelChance = dominant;
    waterBuffaloChance = uncommon;
    rabbitChance = common;
    antelopeChance = abundant;
    wolfChance = semicommon;
    bearChance = veryrare;
    caribouChance = never;
}

// Plain/Grassland
if (biome == 2) {
    pigChance = common;
    cowChance = abundant;
    sheepChance = abundant;
    goatChance = semicommon;
    horseChance = dominant;
    oxChance = semicommon;
    donkeyChance = uncommon;
    rabbitChance = abundant;
    antelopeChance = abundant;
    bisonChance = dominant;
    wolfChance = semicommon;
    bearChance = rare;
    caribouChance = never;
}

// Savannah
if (biome == 3) {
    pigChance = rare;
    cowChance = common;
    sheepChance = uncommon;
    goatChance = semicommon;
    camelChance = rare;
    waterBuffaloChance = uncommon;
    rabbitChance = common;
    antelopeChance = abundant;
    elephantChance = dominant;
    bisonChance = rare;
    wolfChance = semicommon;
    bearChance = rare;
    caribouChance = never;
}

// Wetlands
if (biome == 4) {
    pigChance = common;
    cowChance = uncommon;
    sheepChance = rare;
    goatChance = rare;
    camelChance = rare;
    waterBuffaloChance = dominant;
    rabbitChance = semicommon;
    antelopeChance = abundant;
    elephantChance = semicommon;
    bisonChance = rare;
    wolfChance = uncommon;
    bearChance = semicommon;
    caribouChance = never;
}

// Temperate Forest
if (biome == 5) {
    pigChance = semicommon;
    cowChance = common;
    sheepChance = uncommon;
    goatChance = semicommon;
    horseChance = rare;
    oxChance = uncommon;
    donkeyChance = rare;
    rabbitChance = abundant;
    antelopeChance = rare;
    deerChance = dominant;
    mooseChance = abundant;
    wolfChance = semicommon;
    bearChance = dominant;
    caribouChance = never;
}

// Boreal Forest
if (biome == 6) {
    pigChance = rare;
    cowChance = rare;
    sheepChance = rare;
    goatChance = rare;
    horseChance = rare;
    oxChance = rare;
    donkeyChance = rare;
    rabbitChance = semicommon;
    antelopeChance = never;
    deerChance = abundant;
    mooseChance = dominant;
    bisonChance = rare;
    wolfChance = semicommon;
    bearChance = abundant;
    caribouChance = dominant;
}

// Rainforest/Jungle
if (biome == 7) {
    pigChance = rare;
    cowChance = veryrare;
    horseChance = rare;
    oxChance = veryrare;
    donkeyChance = rare;
    rabbitChance = rare;
    antelopeChance = rare;
    elephantChance = abundant;
    wolfChance = rare;
    bearChance = rare;
    caribouChance = never;
}

// Rocky/Badlands
if (biome == 8) {
    sheepChance = semicommon;
    goatChance = dominant;
    horseChance = rare;
    oxChance = veryrare;
    donkeyChance = rare;
    rabbitChance = uncommon;
    antelopeChance = uncommon;
    bisonChance = veryrare;
    wolfChance = uncommon;
    bearChance = veryrare;
    caribouChance = never;
}

// Tundra
if (biome == 9) {
    pigChance = never;
    cowChance = never;
    sheepChance = rare;
    goatChance = uncommon;
    horseChance = never;
    oxChance = rare;
    donkeyChance = never;
    rabbitChance = semicommon;
    antelopeChance = never;
    elephantChance = never;
    bisonChance = never;
    wolfChance = abundant;
    bearChance = rare;
    caribouChance = dominant;
}

// Cold Desert
if (biome == 10) {
    pigChance = rare;
    cowChance = rare;
    sheepChance = uncommon;
    goatChance = semicommon;
    horseChance = rare;
    oxChance = rare;
    donkeyChance = rare;
    rabbitChance = common;
    antelopeChance = rare;
    elephantChance = veryrare;
    bisonChance = never;
    wolfChance = uncommon;
    bearChance = rare;
    caribouChance = never;
}
float random = rand() / (float) RAND_MAX;
if (random < currentChance + pigChance) {
    animals.push_back(Animal::Pig);
    animalCoords.push_back(tile);
}
else if (random < (currentChance += pigChance) + cowChance) {
    animals.push_back(Animal::Cow);
}
else if (random < (currentChance += cowChance) + chickenChance) {
    animals.push_back(Animal::Chicken);
}
else if (random < (currentChance += chickenChance) + duckChance) {
    animals.push_back(Animal::Duck);
}
else if (random < (currentChance += duckChance) + sheepChance) {
    animals.push_back(Animal::Sheep);
}
else if (random < (currentChance += sheepChance) + goatChance) {
    animals.push_back(Animal::Goat);
}
else if (random < (currentChance += goatChance) + horseChance) {
    animals.push_back(Animal::Horse);
}
else if (random < (currentChance += horseChance) + oxChance) {
    animals.push_back(Animal::Ox);
}
else if (random < (currentChance += oxChance) + donkeyChance) {
    animals.push_back(Animal::Donkey);
}
else if (random < (currentChance += donkeyChance) + camelChance) {
    animals.push_back(Animal::Camel);
}
else if (random < (currentChance += camelChance) + waterBuffaloChance) {
    animals.push_back(Animal::WaterBuffalo);
}
else if (random < (currentChance += waterBuffaloChance) + rabbitChance) {
    animals.push_back(Animal::Rabbit);
}
else if (random < (currentChance += rabbitChance) + antelopeChance) {
    animals.push_back(Animal::Antelope);
}
else if (random < (currentChance += antelopeChance) + deerChance) {
    animals.push_back(Animal::Deer);
}
else if (random < (currentChance += deerChance) + mooseChance) {
    animals.push_back(Animal::Moose);
}
else if (random < (currentChance += mooseChance) + capybaraChance) {
    animals.push_back(Animal::Capybara);
}
else if (random < (currentChance += capybaraChance) + turtleChance) {
    animals.push_back(Animal::Turtle);
}
else if (random < (currentChance += turtleChance) + elephantChance) {
    animals.push_back(Animal::Elephant);
}
else if (random < (currentChance += elephantChance) + bisonChance) {
    animals.push_back(Animal::Bison);
}
else if (random < (currentChance += bisonChance) + wolfChance) {
    animals.push_back(Animal::Wolf);
}
else if (random < (currentChance += wolfChance) + bearChance) {
    animals.push_back(Animal::Bear);
}
else if (random < (currentChance += bearChance) + caribouChance) {
    animals.push_back(Animal::Caribou);
}

     }
}

    template<typename T>
        void printMap(vector<vector<T>>& map) {
        for (int x = 0; x < WIDTH; ++x) {
            for (int y = 0; y < HEIGHT; ++y) {
                cout << map[x][y] << " ";
            }
            cout << endl;
        }
    }

    void cleanupUnusedDS() {
        //globalVec.clear();         // Remove all elements
        //globalVec.shrink_to_fit(); // Force memory deallocation (not guaranteed)
    }

    int main() {
        FastNoiseLite noiseLayer;
        noiseLayer.SetSeed(1434933);
        noiseLayer.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
        noiseLayer.SetFrequency(0.05f);
        noiseLayer.SetFractalType(FastNoiseLite::FractalType_FBm);
        noiseLayer.SetFractalLacunarity(1.8f); //chaos
        noiseLayer.SetFractalOctaves(7); //more detail, extremes appear in cells

        generateAltitudeMap(noiseLayer);
        generateOceanMap();
        cleanAltitudeMap();
        generateLandsMap();
        generateWaterMap();
        generateWBDistances();
        generateTemperatureMap();
        generateHumidityMap();
        generateBiomes();
        getRiversFromGroundwater();
        // cout << "Ocean" << endl;
        //printMap(oceanMap);
        cout << "Lands" << endl;
        printMap(landsMap);
        cout << "Altitude" << endl;
        printMap(altitudeMap);
        cout << "Water Bodies" << endl;
        printMap(waterMap);
        cout << "Temperature" << endl;
        printMap(temperatureMap);
        cout << "Humidity" << endl;
        printMap(humidityMap);
        cout << "Biomes" << endl;
        printMap(biomeMap);
        generateTiles();
        spawnPlants();
        cout << "PLANTS SPAWNED" << endl;
        spawnAnimals();
        cout << "TILE AMOUNT:" << tileIndex.size() << endl;
        int cell = tileCellIndex[5];
         cout << " Cell: " << cell;
        return 0;
    }
