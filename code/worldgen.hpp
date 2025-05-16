#ifndef WORLDGEN_H_
#define WORLDGEN_H_
#include "FastNoiseLite.h"
#include "nanoflann.hpp"
#include "basic.hpp"
#include "mapdimensions.hpp"
#include "tile.hpp"
#include "pathfinding.cpp"
#include "spawn.cpp"

void markCoasts();
void classifyLands(FastNoiseLite noiseLayer1);
// MAPS
vector<vector<int>> oceanMap(WIDTH_WITH_BORDER, vector<int>(HEIGHT_WITH_BORDER, 0));
vector<vector<int>> landsMap(WIDTH_WITH_BORDER, vector<int>(HEIGHT_WITH_BORDER, 0));
vector<vector<int>> altitudeMap(WIDTH_WITH_BORDER, vector<int>(HEIGHT_WITH_BORDER, 0));
vector<vector<int>> temperatureMap(WIDTH_WITH_BORDER, vector<int>(HEIGHT_WITH_BORDER, 0));
vector<vector<int>> waterMap(WIDTH_WITH_BORDER, vector<int>(HEIGHT_WITH_BORDER, 0));
vector<vector<int>> potentialHumidityMap(WIDTH_WITH_BORDER, vector<int>(HEIGHT_WITH_BORDER, 0));
vector<vector<int>> createdHumidityMap(WIDTH_WITH_BORDER, vector<int>(HEIGHT_WITH_BORDER, 0));
vector<vector<int>> humidityMap(WIDTH_WITH_BORDER, vector<int>(HEIGHT_WITH_BORDER, 0));
vector<vector<int>> biomeMap(WIDTH_WITH_BORDER, vector<int>(HEIGHT_WITH_BORDER, 0));
vector<vector<bool>> instantiatedWaterMap(WIDTH_WITH_BORDER, vector<bool>(HEIGHT_WITH_BORDER, 0));

//utility
vector<std::pair<float,float>> mapsLink(WIDTH*HEIGHT);
std::vector<std::vector<bool>> visited(WIDTH_WITH_BORDER, vector<bool>(HEIGHT_WITH_BORDER, 0));

//SPECIAL TILES for generation
vector<std::pair<float,float>> voronoiSites; // center point of biomes/cells
vector<std::pair<float,float>> riverSources;
vector<std::pair<float,float>> riverEnds;
std::unordered_map<std::pair<int, int>, bool, hashPair> lakeOrEnd (STARTING_MAP_WIDTH * STARTING_MAP_HEIGHT);

// current mins and maxes of map
int currentXMin = 0;
int currentXMax = 0;
int currentYMin = 0;
int currentYMax = 0;

const float coastThreshold = -0.2f;
const float landThreshold = -25.0f;
const float lowlandsThreshold = 9.0f;
const float midlandsThreshold = 14.0f;

int depressionThreshold = 15;
float lowlandsToHighlandsChance = 0.01f; // chance of lowlands becoming highlands
float lowlandsToLakeChance = 0.04f; //additional threshold to become lake
float highlandsChance = 0.20f;
float coastalRangeChance = 0.005f;
float riverFromMountainChance = 0.5f;
float riverFromHighlandChance = 0.2f;
float riverFromGroundwaterChance = 0.3f;
float riverEndChance = 0.50f;
float lakeFromRiverChance = 0.60f;
float lakeFromLowlandsChance = 0.05f;
float lakeFromMidlandsChance = 0.01f;
float lakeExpansionChance = 0.60f;
float riverFromLakeChance = 0.40f;
float groundWaterThreshold = 80.0f; // how high humidity needs to be for a chance of substantial groundwater to form
float humidityMult = 2.2f;
float lakeTileChance = 0.07f; //chance that lake tile does NOT happen (smaller sizes mean larger lakes)

/*
 * NOTES:
 * Need to ensure that if a block of tile generates, that some of those tiles aren't actually river tiles,  but haven't been generated as such because neighboring ungenerated tiles which should have river sources on them have not been generated. Thus, need to check if generated cells are river ends of any sort, or lakes, and then for each of those recursively check if there are river continues, following up the chain, until I find the original river sources/lakes, and then recursively generate rivers all the way down, even if those tiles haven't been generated.
 *
 */

#endif // WORLDGEN_H_
