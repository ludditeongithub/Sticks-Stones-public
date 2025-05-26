#ifndef PLANT_H_
#define PLANT_H_

#include "basic.hpp"
#include "mapdimensions.hpp"
#include "categories.hpp"
#include "cropdata.hpp"

/* RUNTIME CROP DATA MANAGEMENT */
//get current global temp and sunlight
std::stack<uint16_t> nextPlantIndex;
float temp;
float sunlight;
float date;

std::vector<Plant> cropList;

std::vector<Plant> plants;
std::vector<uint16_t> growthAmt;
std::vector<uint8_t> yieldMisses;
std::vector<uint16_t> collectedWater;
std::vector<uint16_t> lastFullyWatered;
std::vector<bool> fullyGrown;


enum class PlantType {
    Tree, FruitTree, Foliage, Succulent, Shrub, Flowering, FruitVeggie, Leafy, Root, Reed, Tuber, Grain, Bulb, Grapevine, Herb, Textile
}

#endif // PLANT_H_
