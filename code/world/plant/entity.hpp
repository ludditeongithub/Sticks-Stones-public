#pragma once

#include "enum.hpp"
#include "world/plant/tables.hpp"
#include <stdint.h>
#include <stack>
#include <cstddef>
#include <systems/worldUpdates.hpp>

struct PlantDatabase {
  std::stack<uint16_t> nextPlantIndex;
  int size = 0;
Array<Plant> plantList;
Array<float> nextGrowth;
Array<Coord> coords;
Array<float> tileWater;
Array<float> lastFullyWatered;

	void destroyPlant(uint16_t i);
uint32_t getPlantIndex();
void releasePlantSource(std::vector<Object>& rTileObject, std::vector<std::pair<int, int>>& rTileCoords, int tileIndex);
bool viableHarvest(int plantIndex);
void setGerminationTime(int seedIndex);
void germinate(int seedIndex, bool randomGrowth, ObjectDatabase& od);
void prepareSeedDropping(int animalIndex, int plantIndex, bool regrowth);
void attemptPlantGrowth(int plant, int time, int biomeIndex);
void excreteSeed(int animalIndex, Plant plant);
void plant(int unitIndex, Plant plant);
void killTree(int plantIndex);
void killPlant(int plantIndex);
void releasePlantSource(std::vector<Object>& rTileObject, std::vector<std::pair<int, int>>& rTileCoords, int tileIndex);	
};

struct RegrowthPlantDatabase : PlantDatabase {
  void destroyPlant(uint16_t i) {
	  
	  PlantDatabase::destroyPlant(i);
  }
};
