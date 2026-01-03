#include "basic.hpp"

class RegionDatabase
{
private:
  // each of these values are generated from worldSpawn.cpp, and then afterwards
  // can be assigned to a region. 
  //TODO find out if its bettter to do these as 2d or 1d with consts.
  struct Region {
    Biome biome;
    uint8_t humidity;
    temp temperature;
    alt altitude;
  };

  std::vector<std::vector<Region>> regions;
  std::vector<std::vector<coord>> voronoiSites;
  
  // a region is created whenever a player explores a neighboring region. Databases which contain objects that do not move are only managed whenever the player enters the region (a tile within the region becomes visible). Databases which contian objects that move by themselves (and thus move per cycle) are managed separately, as are inventories.
public:
  RegionDatabase() {
    
    
  };

    /* first, world spawns regions, with deterministic (from voronoi generation:
  1. temperature, humidity, biome value
  2. status of whether water bodies are present

  then,

  */
  void createRegions(uint32_t regions);
  void setVoronoiSites();
  void setTemperatureMap();
  void setHumidityMap();
  alt getRegionAltitude();
  coord getRegionFromTile(coord tileCoord);
  coord getNthNearestRegionFromRegion(coord regionCoord, uint16_t n);
  std::pair<float, float> getDistanceWeightFromNearestTwoRegions(coord tileCoord);
};


