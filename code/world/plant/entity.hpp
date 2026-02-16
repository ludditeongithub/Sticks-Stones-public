#pragma once

#include "enum.hpp"
#include "world/plant/tables.hpp"
#include <stdint.h>
#include <cstddef>
#include <systems/worldUpdates.hpp>

struct PlantDatabase {
Array<Plant> plantList;
Array<float> nextGrowth;
Array<Coord> coords;
Array<float> tileWater;
Array<float> lastFullyWatered;

void destroyPlant(size__t i) {
  plantList.remove(i);
  nextGrowth.remove(i);
  coords.remove(i);
  tileWater.remove(i);
  lastFullyWatered.remove(i);
}

  void bitePlant(size_t i, Animal animal) {
    animalBiteDamages[animal];
}

  
};
