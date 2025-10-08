#ifndef PLANT_H_
#define PLANT_H_

#include "basic.hpp"
#include "categories.hpp"

/* RUNTIME CROP DATA MANAGEMENT */
//get current global temp and sunlight


struct soilTraits {
    float waterRetention;
};


Plant crops[] = {

};

enum class PlantType {
EMPTY, Tree, FruitTree, Foliage, Succulent, BerryShrub, Flowering, FruitVeggie, Leafy, Root, Reed, Tuber, Bulb, Grain, Grapevine, Herb, Textile
};


struct CropTraits {
    PlantType type = PlantType::Tree;
    //57000 fullyGrownAmt means one forty-day season to grow, at a 1.0 growth amount. Ths implies perfect growing conditions.
    float fullyGrownAmt = 78000.0;
    //temps in Celsius
    float noGrowthMin = 4.0;
    float noGrowthMax = 38.0;
    float optimalMin = 14.0;
    float optimalMax = 21.0;
    float deathMin = 0.0;
    float deathMax = 42.0;
    float waterRequired = 25.0; //in mm
    float waterDeath = 940.0;
    //static constexpr int Produces = 1;
    //static constexpr int ProducesIndex = BaseMaterials::WheatGrain;
    int harvestAmount = 30;
    bool requiresScythe = true;
};

bool regrowthPlants[<static_cast<int>(Plant::MAX)>];

void setRegrowthPlants() {
  regrowthPlants[static_cast<int>(Plant::Wheat)] = false;
  regrowthPlants[static_cast<int>(Plant::Oat)] = false;
  regrowthPlants[static_cast<int>(Plant::Corn)] = false;
  regrowthPlants[static_cast<int>(Plant::Rice)] = false;
  regrowthPlants[static_cast<int>(Plant::Tomato)] = false;
  regrowthPlants[static_cast<int>(Plant::Onion)] = false;
  regrowthPlants[static_cast<int>(Plant::Potato)] = false;
  regrowthPlants[static_cast<int>(Plant::Cabbage)] = false;
  regrowthPlants[static_cast<int>(Plant::Pepper)] = false;
  regrowthPlants[static_cast<int>(Plant::Carrot)] = false;
  regrowthPlants[static_cast<int>(Plant::Poppy)] = false;
  regrowthPlants[static_cast<int>(Plant::Senna)] = false;
  regrowthPlants[static_cast<int>(Plant::Cotton)] = false;
  regrowthPlants[static_cast<int>(Plant::Papyrus)] = false;
  regrowthPlants[static_cast<int>(Plant::Flax)] = false;
  regrowthPlants[static_cast<int>(Plant::Hemp)] = false;
  regrowthPlants[static_cast<int>(Plant::Lettuce)] = false;
}

struct RegrowthCropTraits {
    static constexpr float lifespanAmt = 4560000.0;
    //temps in Celsius
    static constexpr float noGrowthMin = 4.0;
    static constexpr float noGrowthMax = 38.0;
    static constexpr float optimalMin = 15.0;
    static constexpr float optimalMax = 25.0;
    static constexpr float deathMin = -20.0;
    static constexpr float deathMax = 40.0;
    static constexpr float waterRequired = 25.0; //in mm, multiplied by an amount related to age
    static constexpr int waterDeath = 940.0;
    //static constexpr int Produces = 1;
    //static constexpr int ProducesIndex = BaseMaterials::WheatGrain;
    static constexpr int startingHarvestAmt = 25;
    static constexpr int endingHarvestAmt = 1500;
    static constexpr float regrowthStart = 654000.0;
    static constexpr float regrowth = 38000.0;
    static constexpr int regrowthCycles = 20;
};

enum class activeCropTraits {
    ActiveGrowthRate,
    CollectedWater,
    LastFullyWatered,
    FullyGrown,
};

enum class activeRegrowthCropTraits {
    ActiveGrowthRate,
    CollectedWater,
    LastFullyWatered,
    FullyGrown,
    HarvestAmt,
};


// fill lookup table for CropTraits
static constexpr size_t cropArrSize = (size_t) Plant::MAX;

// Separate arrays for each field of CropTraits
std::array<float, cropArrSize> waterRequired;
std::array<float, cropArrSize> deathMin;
std::array<float, cropArrSize> deathMax;
std::array<float, cropArrSize> optimalMin;
std::array<float, cropArrSize> optimalMax;
std::array<float, cropArrSize> noGrowthMin;
std::array<float, cropArrSize> noGrowthMax;
std::array<float, cropArrSize> waterDeath;
std::array<float, cropArrSize> fullyGrownAmt;
std::array<float, cropArrSize> harvestAmt;
std::array<float, cropArrSize> requiresScythe;

static constexpr size_t rCropArrSize = (size_t) Plant::MAX;

std::array<float, rCropArrSize> lifespanAmt;
std::array<float, rCropArrSize> rnoGrowthMin;
std::array<float, rCropArrSize> rnoGrowthMax;
std::array<float, rCropArrSize> roptimalMin;
std::array<float, rCropArrSize> roptimalMax;
std::array<float, rCropArrSize> rdeathMin;
std::array<float, rCropArrSize> rdeathMax;
std::array<float, rCropArrSize> rwaterRequired;
std::array<float, rCropArrSize> rwaterDeath;
std::array<int, rCropArrSize> rstartingHarvestAmt;
std::array<int, rCropArrSize> rendingHarvestAmt;
std::array<float, rCropArrSize> regrowthStart;
std::array<float, rCropArrSize> regrowth;

void assignCropData() {
    fullyGrownAmt[static_cast<int>(Plant::Wheat)] = 29250.0;
    noGrowthMin[static_cast<int>(Plant::Wheat)] = 4.0;
    noGrowthMax[static_cast<int>(Plant::Wheat)] = 38.0;
    optimalMin[static_cast<int>(Plant::Wheat)] = 14.0;
    optimalMax[static_cast<int>(Plant::Wheat)] = 21.0;
    deathMin[static_cast<int>(Plant::Wheat)] = 0.0;
    deathMax[static_cast<int>(Plant::Wheat)] = 42.0;
    waterRequired[static_cast<int>(Plant::Wheat)] = 25.0;
    waterDeath[static_cast<int>(Plant::Wheat)] = 250.0;
    harvestAmt[static_cast<int>(Plant::Wheat)] = 30;
    requiresScythe[static_cast<int>(Plant::Wheat)] = true;

    fullyGrownAmt[static_cast<int>(Plant::Oat)] = 27787.5;
    noGrowthMin[static_cast<int>(Plant::Oat)] = 4.0;
    noGrowthMax[static_cast<int>(Plant::Oat)] = 38.0;
    optimalMin[static_cast<int>(Plant::Oat)] = 14.0;
    optimalMax[static_cast<int>(Plant::Oat)] = 21.0;
    deathMin[static_cast<int>(Plant::Oat)] = 0.0;
    deathMax[static_cast<int>(Plant::Oat)] = 42.0;
    waterRequired[static_cast<int>(Plant::Oat)] = 25.0;
    waterDeath[static_cast<int>(Plant::Oat)] = 250.0;
    harvestAmt[static_cast<int>(Plant::Oat)] = 30;
    requiresScythe[static_cast<int>(Plant::Oat)] = true;

    fullyGrownAmt[static_cast<int>(Plant::Corn)] = 34125.0;
    noGrowthMin[static_cast<int>(Plant::Corn)] = 10.0;
    noGrowthMax[static_cast<int>(Plant::Corn)] = 40.0;
    optimalMin[static_cast<int>(Plant::Corn)] = 16.0;
    optimalMax[static_cast<int>(Plant::Corn)] = 28.0;
    deathMin[static_cast<int>(Plant::Corn)] = 0.0;
    deathMax[static_cast<int>(Plant::Corn)] = 45.0;
    waterRequired[static_cast<int>(Plant::Corn)] = 30.0;
    waterDeath[static_cast<int>(Plant::Corn)] = 250.0;
    harvestAmt[static_cast<int>(Plant::Corn)] = 30;
    requiresScythe[static_cast<int>(Plant::Corn)] = true;

    fullyGrownAmt[static_cast<int>(Plant::Rice)] = 29250.0;
    noGrowthMin[static_cast<int>(Plant::Rice)] = 15.0;
    noGrowthMax[static_cast<int>(Plant::Rice)] = 40.0;
    optimalMin[static_cast<int>(Plant::Rice)] = 20.0;
    optimalMax[static_cast<int>(Plant::Rice)] = 35.0;
    deathMin[static_cast<int>(Plant::Rice)] = 0.0;
    deathMax[static_cast<int>(Plant::Rice)] = 45.0;
    waterRequired[static_cast<int>(Plant::Rice)] = 25.0;
    waterDeath[static_cast<int>(Plant::Rice)] = 200.0;
    harvestAmt[static_cast<int>(Plant::Rice)] = 30;
    requiresScythe[static_cast<int>(Plant::Rice)] = true;

    fullyGrownAmt[static_cast<int>(Plant::Tomato)] = 25312.5;
    noGrowthMin[static_cast<int>(Plant::Tomato)] = 10.0;
    noGrowthMax[static_cast<int>(Plant::Tomato)] = 35.0;
    optimalMin[static_cast<int>(Plant::Tomato)] = 18.0;
    optimalMax[static_cast<int>(Plant::Tomato)] = 30.0;
    deathMin[static_cast<int>(Plant::Tomato)] = 0.0;
    deathMax[static_cast<int>(Plant::Tomato)] = 40.0;
    waterRequired[static_cast<int>(Plant::Tomato)] = 25.0;
    waterDeath[static_cast<int>(Plant::Tomato)] = 180.0;
    harvestAmt[static_cast<int>(Plant::Tomato)] = 30;
    requiresScythe[static_cast<int>(Plant::Tomato)] = false;

    fullyGrownAmt[static_cast<int>(Plant::Onion)] = 27787.5;
    noGrowthMin[static_cast<int>(Plant::Onion)] = 5.0;
    noGrowthMax[static_cast<int>(Plant::Onion)] = 30.0;
    optimalMin[static_cast<int>(Plant::Onion)] = 12.0;
    optimalMax[static_cast<int>(Plant::Onion)] = 25.0;
    deathMin[static_cast<int>(Plant::Onion)] = 0.0;
    deathMax[static_cast<int>(Plant::Onion)] = 40.0;
    waterRequired[static_cast<int>(Plant::Onion)] = 20.0;
    waterDeath[static_cast<int>(Plant::Onion)] = 200.0;
    harvestAmt[static_cast<int>(Plant::Onion)] = 30;
    requiresScythe[static_cast<int>(Plant::Onion)] = false;

    fullyGrownAmt[static_cast<int>(Plant::Potato)] = 27787.5;
    noGrowthMin[static_cast<int>(Plant::Potato)] = 5.0;
    noGrowthMax[static_cast<int>(Plant::Potato)] = 30.0;
    optimalMin[static_cast<int>(Plant::Potato)] = 12.0;
    optimalMax[static_cast<int>(Plant::Potato)] = 22.0;
    deathMin[static_cast<int>(Plant::Potato)] = 0.0;
    deathMax[static_cast<int>(Plant::Potato)] = 40.0;
    waterRequired[static_cast<int>(Plant::Potato)] = 25.0;
    waterDeath[static_cast<int>(Plant::Potato)] = 200.0;
    harvestAmt[static_cast<int>(Plant::Potato)] = 30;
    requiresScythe[static_cast<int>(Plant::Potato)] = false;

fullyGrownAmt[static_cast<int>(Plant::Cabbage)] = 33750.0;
noGrowthMin[static_cast<int>(Plant::Cabbage)] = 5.0;
noGrowthMax[static_cast<int>(Plant::Cabbage)] = 30.0;
optimalMin[static_cast<int>(Plant::Cabbage)] = 14.0;
optimalMax[static_cast<int>(Plant::Cabbage)] = 28.0;
deathMin[static_cast<int>(Plant::Cabbage)] = 0.0;
deathMax[static_cast<int>(Plant::Cabbage)] = 40.0;
waterRequired[static_cast<int>(Plant::Cabbage)] = 20.0;
waterDeath[static_cast<int>(Plant::Cabbage)] = 200.0;
harvestAmt[static_cast<int>(Plant::Cabbage)] = 30;
requiresScythe[static_cast<int>(Plant::Cabbage)] = true;

// fullyGrownAmt[static_cast<int>(Plant::Pumpkin)] = 36562.5;
// noGrowthMin[static_cast<int>(Plant::Pumpkin)] = 10.0;
// noGrowthMax[static_cast<int>(Plant::Pumpkin)] = 30.0;
// optimalMin[static_cast<int>(Plant::Pumpkin)] = 16.0;
// optimalMax[static_cast<int>(Plant::Pumpkin)] = 28.0;
// deathMin[static_cast<int>(Plant::Pumpkin)] = 0.0;
// deathMax[static_cast<int>(Plant::Pumpkin)] = 40.0;
// waterRequired[static_cast<int>(Plant::Pumpkin)] = 30.0;
// waterDeath[static_cast<int>(Plant::Pumpkin)] = 250.0;
// harvestAmt[static_cast<int>(Plant::Pumpkin)] = 30;
// requiresScythe[static_cast<int>(Plant::Pumpkin)] = true;

fullyGrownAmt[static_cast<int>(Plant::Pepper)] = 28125.0;
noGrowthMin[static_cast<int>(Plant::Pepper)] = 10.0;
noGrowthMax[static_cast<int>(Plant::Pepper)] = 35.0;
optimalMin[static_cast<int>(Plant::Pepper)] = 18.0;
optimalMax[static_cast<int>(Plant::Pepper)] = 28.0;
deathMin[static_cast<int>(Plant::Pepper)] = 0.0;
deathMax[static_cast<int>(Plant::Pepper)] = 40.0;
waterRequired[static_cast<int>(Plant::Pepper)] = 25.0;
waterDeath[static_cast<int>(Plant::Pepper)] = 220.0;
harvestAmt[static_cast<int>(Plant::Pepper)] = 30;
requiresScythe[static_cast<int>(Plant::Pepper)] = true;

fullyGrownAmt[static_cast<int>(Plant::Carrot)] = 25312.5;
noGrowthMin[static_cast<int>(Plant::Carrot)] = 5.0;
noGrowthMax[static_cast<int>(Plant::Carrot)] = 30.0;
optimalMin[static_cast<int>(Plant::Carrot)] = 12.0;
optimalMax[static_cast<int>(Plant::Carrot)] = 25.0;
deathMin[static_cast<int>(Plant::Carrot)] = 0.0;
deathMax[static_cast<int>(Plant::Carrot)] = 40.0;
waterRequired[static_cast<int>(Plant::Carrot)] = 20.0;
waterDeath[static_cast<int>(Plant::Carrot)] = 180.0;
harvestAmt[static_cast<int>(Plant::Carrot)] = 30;
requiresScythe[static_cast<int>(Plant::Carrot)] = true;

fullyGrownAmt[static_cast<int>(Plant::Poppy)] = 25312.5;
noGrowthMin[static_cast<int>(Plant::Poppy)] = 5.0;
noGrowthMax[static_cast<int>(Plant::Poppy)] = 30.0;
optimalMin[static_cast<int>(Plant::Poppy)] = 10.0;
optimalMax[static_cast<int>(Plant::Poppy)] = 25.0;
deathMin[static_cast<int>(Plant::Poppy)] = 0.0;
deathMax[static_cast<int>(Plant::Poppy)] = 40.0;
waterRequired[static_cast<int>(Plant::Poppy)] = 20.0;
waterDeath[static_cast<int>(Plant::Poppy)] = 200.0;
harvestAmt[static_cast<int>(Plant::Poppy)] = 30;
requiresScythe[static_cast<int>(Plant::Poppy)] = true;

fullyGrownAmt[static_cast<int>(Plant::Senna)] = 29250.0;
noGrowthMin[static_cast<int>(Plant::Senna)] = 5.0;
noGrowthMax[static_cast<int>(Plant::Senna)] = 30.0;
optimalMin[static_cast<int>(Plant::Senna)] = 15.0;
optimalMax[static_cast<int>(Plant::Senna)] = 35.0;
deathMin[static_cast<int>(Plant::Senna)] = 0.0;
deathMax[static_cast<int>(Plant::Senna)] = 45.0;
waterRequired[static_cast<int>(Plant::Senna)] = 28.0;
waterDeath[static_cast<int>(Plant::Senna)] = 220.0;
harvestAmt[static_cast<int>(Plant::Senna)] = 30;
requiresScythe[static_cast<int>(Plant::Senna)] = true;

fullyGrownAmt[static_cast<int>(Plant::Cotton)] = 42187.5;
noGrowthMin[static_cast<int>(Plant::Cotton)] = 10.0;
noGrowthMax[static_cast<int>(Plant::Cotton)] = 35.0;
optimalMin[static_cast<int>(Plant::Cotton)] = 18.0;
optimalMax[static_cast<int>(Plant::Cotton)] = 32.0;
deathMin[static_cast<int>(Plant::Cotton)] = 0.0;
deathMax[static_cast<int>(Plant::Cotton)] = 45.0;
waterRequired[static_cast<int>(Plant::Cotton)] = 35.0;
waterDeath[static_cast<int>(Plant::Cotton)] = 250.0;
harvestAmt[static_cast<int>(Plant::Cotton)] = 30;
requiresScythe[static_cast<int>(Plant::Cotton)] = true;

fullyGrownAmt[static_cast<int>(Plant::Papyrus)] = 42187.5;
noGrowthMin[static_cast<int>(Plant::Papyrus)] = 20.0;
noGrowthMax[static_cast<int>(Plant::Papyrus)] = 35.0;
optimalMin[static_cast<int>(Plant::Papyrus)] = 15.0;
optimalMax[static_cast<int>(Plant::Papyrus)] = 32.0;
deathMin[static_cast<int>(Plant::Papyrus)] = 0.0;
deathMax[static_cast<int>(Plant::Papyrus)] = 45.0;
waterRequired[static_cast<int>(Plant::Papyrus)] = 35.0;
waterDeath[static_cast<int>(Plant::Papyrus)] = 260.0;
harvestAmt[static_cast<int>(Plant::Papyrus)] = 30;
requiresScythe[static_cast<int>(Plant::Papyrus)] = true;

fullyGrownAmt[static_cast<int>(Plant::Flax)] = 33750.0;
noGrowthMin[static_cast<int>(Plant::Flax)] = 4.0;
noGrowthMax[static_cast<int>(Plant::Flax)] = 35.0;
optimalMin[static_cast<int>(Plant::Flax)] = 10.0;
optimalMax[static_cast<int>(Plant::Flax)] = 22.0;
deathMin[static_cast<int>(Plant::Flax)] = 0.0;
deathMax[static_cast<int>(Plant::Flax)] = 40.0;
waterRequired[static_cast<int>(Plant::Flax)] = 24.0;
waterDeath[static_cast<int>(Plant::Flax)] = 220.0;
harvestAmt[static_cast<int>(Plant::Flax)] = 30;
requiresScythe[static_cast<int>(Plant::Flax)] = true;

fullyGrownAmt[static_cast<int>(Plant::Hemp)] = 36562.5;
noGrowthMin[static_cast<int>(Plant::Hemp)] = 10.0;
noGrowthMax[static_cast<int>(Plant::Hemp)] = 35.0;
optimalMin[static_cast<int>(Plant::Hemp)] = 15.0;
optimalMax[static_cast<int>(Plant::Hemp)] = 30.0;
deathMin[static_cast<int>(Plant::Hemp)] = 0.0;
deathMax[static_cast<int>(Plant::Hemp)] = 40.0;
waterRequired[static_cast<int>(Plant::Hemp)] = 28.0;
waterDeath[static_cast<int>(Plant::Hemp)] = 250.0;
harvestAmt[static_cast<int>(Plant::Hemp)] = 30;
requiresScythe[static_cast<int>(Plant::Hemp)] = true;

fullyGrownAmt[static_cast<int>(Plant::Lettuce)] = 25312.5;
noGrowthMin[static_cast<int>(Plant::Lettuce)] = 7.0;
noGrowthMax[static_cast<int>(Plant::Lettuce)] = 24.0;
optimalMin[static_cast<int>(Plant::Lettuce)] = 16.0;
optimalMax[static_cast<int>(Plant::Lettuce)] = 21.0;
deathMin[static_cast<int>(Plant::Lettuce)] = 0.0;
deathMax[static_cast<int>(Plant::Lettuce)] = 32.0;
waterRequired[static_cast<int>(Plant::Lettuce)] = 20.0;
waterDeath[static_cast<int>(Plant::Lettuce)] = 150.0;
harvestAmt[static_cast<int>(Plant::Lettuce)] = 30;

lifespanAmt[static_cast<int>(Plant::OliveTree)] = 57600000.0;
rnoGrowthMin[static_cast<int>(Plant::OliveTree)] = 5.0;
rnoGrowthMax[static_cast<int>(Plant::OliveTree)] = 38.0;
roptimalMin[static_cast<int>(Plant::OliveTree)] = 15.0;
roptimalMax[static_cast<int>(Plant::OliveTree)] = 28.0;
rdeathMin[static_cast<int>(Plant::OliveTree)] = -7.0;
rdeathMax[static_cast<int>(Plant::OliveTree)] = 45.0;
rwaterRequired[static_cast<int>(Plant::OliveTree)] = 20.0;
rwaterDeath[static_cast<int>(Plant::OliveTree)] = 800.0;
rstartingHarvestAmt[static_cast<int>(Plant::OliveTree)] = 50;
rendingHarvestAmt[static_cast<int>(Plant::OliveTree)] = 1000;
regrowthStart[static_cast<int>(Plant::OliveTree)] = 1152000.0;
regrowthPeriod[static_cast<int>(Plant::OliveTree)] = 31000.0;

lifespanAmt[static_cast<int>(Plant::Grapevine)] = 400000.0;
rnoGrowthMin[static_cast<int>(Plant::Grapevine)] = 6.0;
rnoGrowthMax[static_cast<int>(Plant::Grapevine)] = 35.0;
roptimalMin[static_cast<int>(Plant::Grapevine)] = 16.0;
roptimalMax[static_cast<int>(Plant::Grapevine)] = 26.0;
rdeathMin[static_cast<int>(Plant::Grapevine)] = -5.0;
rdeathMax[static_cast<int>(Plant::Grapevine)] = 40.0;
rwaterRequired[static_cast<int>(Plant::Grapevine)] = 22.0;
rwaterDeath[static_cast<int>(Plant::Grapevine)] = 850.0;
rstartingHarvestAmt[static_cast<int>(Plant::Grapevine)] = 80;
rendingHarvestAmt[static_cast<int>(Plant::Grapevine)] = 1200;
regrowthStart[static_cast<int>(Plant::Grapevine)] = 0.25 * 4560000.0;
regrowthPeriod[static_cast<int>(Plant::Grapevine)] = 30000.0;

lifespanAmt[static_cast<int>(Plant::AppleTree)] = 4000000.0;
rnoGrowthMin[static_cast<int>(Plant::AppleTree)] = 4.0;
rnoGrowthMax[static_cast<int>(Plant::AppleTree)] = 38.0;
roptimalMin[static_cast<int>(Plant::AppleTree)] = 15.0;
roptimalMax[static_cast<int>(Plant::AppleTree)] = 25.0;
rdeathMin[static_cast<int>(Plant::AppleTree)] = -20.0;
rdeathMax[static_cast<int>(Plant::AppleTree)] = 40.0;
rwaterRequired[static_cast<int>(Plant::AppleTree)] = 25.0;
rwaterDeath[static_cast<int>(Plant::AppleTree)] = 940.0;
rstartingHarvestAmt[static_cast<int>(Plant::AppleTree)] = 35;
rendingHarvestAmt[static_cast<int>(Plant::AppleTree)] = 1500;
regrowthStart[static_cast<int>(Plant::AppleTree)] = 4560000.0/6.0;


lifespanAmt[static_cast<int>(Plant::Fig)] = 450000.0;
rnoGrowthMin[static_cast<int>(Plant::Fig)] = 10.0;
rnoGrowthMax[static_cast<int>(Plant::Fig)] = 35.0;
roptimalMin[static_cast<int>(Plant::Fig)] = 18.0;
roptimalMax[static_cast<int>(Plant::Fig)] = 27.0;
rdeathMin[static_cast<int>(Plant::Fig)] = -10.0;
rdeathMax[static_cast<int>(Plant::Fig)] = 38.0;
rwaterRequired[static_cast<int>(Plant::Fig)] = 30.0;
rwaterDeath[static_cast<int>(Plant::Fig)] = 920.0;
rstartingHarvestAmt[static_cast<int>(Plant::Fig)] = 35;
rendingHarvestAmt[static_cast<int>(Plant::Fig)] = 1400;
regrowthStart[static_cast<int>(Plant::Fig)] = 70000;
regrowthPeriod[static_cast<int>(Plant::Fig)] = 42000.0;

lifespanAmt[static_cast<int>(Plant::Pear)] = 4560000.0;
rnoGrowthMin[static_cast<int>(Plant::Pear)] = 3.0;
rnoGrowthMax[static_cast<int>(Plant::Pear)] = 36.0;
roptimalMin[static_cast<int>(Plant::Pear)] = 14.0;
roptimalMax[static_cast<int>(Plant::Pear)] = 24.0;
rdeathMin[static_cast<int>(Plant::Pear)] = -15.0;
rdeathMax[static_cast<int>(Plant::Pear)] = 39.0;
rwaterRequired[static_cast<int>(Plant::Pear)] = 27.0;
rwaterDeath[static_cast<int>(Plant::Pear)] = 930.0;
rstartingHarvestAmt[static_cast<int>(Plant::Pear)] = 38;
rendingHarvestAmt[static_cast<int>(Plant::Pear)] = 1450;
regrowthStart[static_cast<int>(Plant::Pear)] = 0.29 * 4560000.0;
regrowthPeriod[static_cast<int>(Plant::Pear)] = 40000.0;

lifespanAmt[static_cast<int>(Plant::Peach)] = 4200000.0;
rnoGrowthMin[static_cast<int>(Plant::Peach)] = 6.0;
rnoGrowthMax[static_cast<int>(Plant::Peach)] = 36.0;
roptimalMin[static_cast<int>(Plant::Peach)] = 18.0;
roptimalMax[static_cast<int>(Plant::Peach)] = 28.0;
rdeathMin[static_cast<int>(Plant::Peach)] = -15.0;
rdeathMax[static_cast<int>(Plant::Peach)] = 38.0;
rwaterRequired[static_cast<int>(Plant::Peach)] = 40.0;
rwaterDeath[static_cast<int>(Plant::Peach)] = 900.0;
rstartingHarvestAmt[static_cast<int>(Plant::Peach)] = 25;
rendingHarvestAmt[static_cast<int>(Plant::Peach)] = 1500;
regrowthStart[static_cast<int>(Plant::Peach)] = 684000.0;
regrowthPeriod[static_cast<int>(Plant::Peach)] = 42000.0;

lifespanAmt[static_cast<int>(Plant::Mango)] = 4800000.0;
rnoGrowthMin[static_cast<int>(Plant::Mango)] = 10.0;
rnoGrowthMax[static_cast<int>(Plant::Mango)] = 40.0;
roptimalMin[static_cast<int>(Plant::Mango)] = 20.0;
roptimalMax[static_cast<int>(Plant::Mango)] = 30.0;
rdeathMin[static_cast<int>(Plant::Mango)] = -5.0;
rdeathMax[static_cast<int>(Plant::Mango)] = 42.0;
rwaterRequired[static_cast<int>(Plant::Mango)] = 50.0;
rwaterDeath[static_cast<int>(Plant::Mango)] = 950.0;
rstartingHarvestAmt[static_cast<int>(Plant::Mango)] = 30;
rendingHarvestAmt[static_cast<int>(Plant::Mango)] = 1600;
regrowthStart[static_cast<int>(Plant::Mango)] = 720000.0;
regrowthPeriod[static_cast<int>(Plant::Mango)] = 45000.0;

lifespanAmt[static_cast<int>(Plant::Blueberry)] = 4200000.0;
rnoGrowthMin[static_cast<int>(Plant::Blueberry)] = 3.0;
rnoGrowthMax[static_cast<int>(Plant::Blueberry)] = 32.0;
roptimalMin[static_cast<int>(Plant::Blueberry)] = 16.0;
roptimalMax[static_cast<int>(Plant::Blueberry)] = 24.0;
rdeathMin[static_cast<int>(Plant::Blueberry)] = -25.0;
rdeathMax[static_cast<int>(Plant::Blueberry)] = 35.0;
rwaterRequired[static_cast<int>(Plant::Blueberry)] = 30.0;
rwaterDeath[static_cast<int>(Plant::Blueberry)] = 700.0;
rstartingHarvestAmt[static_cast<int>(Plant::Blueberry)] = 20;
rendingHarvestAmt[static_cast<int>(Plant::Blueberry)] = 1000;
regrowthStart[static_cast<int>(Plant::Blueberry)] = 600000.0;
regrowthPeriod[static_cast<int>(Plant::Blueberry)] = 38000.0;

lifespanAmt[static_cast<int>(Plant::Strawberry)] = 360000.0;
rnoGrowthMin[static_cast<int>(Plant::Strawberry)] = 2.0;
rnoGrowthMax[static_cast<int>(Plant::Strawberry)] = 30.0;
roptimalMin[static_cast<int>(Plant::Strawberry)] = 15.0;
roptimalMax[static_cast<int>(Plant::Strawberry)] = 23.0;
rdeathMin[static_cast<int>(Plant::Strawberry)] = -10.0;
rdeathMax[static_cast<int>(Plant::Strawberry)] = 33.0;
rwaterRequired[static_cast<int>(Plant::Strawberry)] = 35.0;
rwaterDeath[static_cast<int>(Plant::Strawberry)] = 650.0;
rstartingHarvestAmt[static_cast<int>(Plant::Strawberry)] = 40;
rendingHarvestAmt[static_cast<int>(Plant::Strawberry)] = 120;
regrowthStart[static_cast<int>(Plant::Strawberry)] = 32000.0;
regrowthPeriod[static_cast<int>(Plant::Strawberry)] = 35000.0;

lifespanAmt[static_cast<int>(Plant::Lavender)] = 15000.0;
rnoGrowthMin[static_cast<int>(Plant::Lavender)] = 5.0;
rnoGrowthMax[static_cast<int>(Plant::Lavender)] = 35.0;
roptimalMin[static_cast<int>(Plant::Lavender)] = 17.0;
roptimalMax[static_cast<int>(Plant::Lavender)] = 26.0;
rdeathMin[static_cast<int>(Plant::Lavender)] = -10.0;
rdeathMax[static_cast<int>(Plant::Lavender)] = 38.0;
rwaterRequired[static_cast<int>(Plant::Lavender)] = 20.0;
rwaterDeath[static_cast<int>(Plant::Lavender)] = 500.0;
rstartingHarvestAmt[static_cast<int>(Plant::Lavender)] = 15;
rendingHarvestAmt[static_cast<int>(Plant::Lavender)] = 800;
regrowthStart[static_cast<int>(Plant::Lavender)] = 620000.0;
regrowthPeriod[static_cast<int>(Plant::Lavender)] = 40000.0;

// Saffron
lifespanAmt[static_cast<int>(Plant::Saffron)] = 100000.0;
rnoGrowthMin[static_cast<int>(Plant::Saffron)] = 5.0;
rnoGrowthMax[static_cast<int>(Plant::Saffron)] = 30.0;
roptimalMin[static_cast<int>(Plant::Saffron)] = 10.0;
roptimalMax[static_cast<int>(Plant::Saffron)] = 20.0;
rdeathMin[static_cast<int>(Plant::Saffron)] = -10.0;
rdeathMax[static_cast<int>(Plant::Saffron)] = 35.0;
rwaterRequired[static_cast<int>(Plant::Saffron)] = 10.0;
rwaterDeath[static_cast<int>(Plant::Saffron)] = 300.0;
rstartingHarvestAmt[static_cast<int>(Plant::Saffron)] = 1;
rendingHarvestAmt[static_cast<int>(Plant::Saffron)] = 1;
regrowthStart[static_cast<int>(Plant::Saffron)] = 100000.0 / 4.0;
regrowthPeriod[static_cast<int>(Plant::Saffron)] = 5000.0;

// Aloe static_cast<int>(Plant::Vera)
lifespanAmt[static_cast<int>(Plant::AloeVera)] = 600000.0;
rnoGrowthMin[static_cast<int>(Plant::AloeVera)] = 5.0;
rnoGrowthMax[static_cast<int>(Plant::AloeVera)] = 35.0;
roptimalMin[static_cast<int>(Plant::AloeVera)] = 15.0;
roptimalMax[static_cast<int>(Plant::AloeVera)] = 30.0;
rdeathMin[static_cast<int>(Plant::AloeVera)] = -5.0;
rdeathMax[static_cast<int>(Plant::AloeVera)] = 40.0;
rwaterRequired[static_cast<int>(Plant::AloeVera)] = 5.0;
rwaterDeath[static_cast<int>(Plant::AloeVera)] = 600.0;
rstartingHarvestAmt[static_cast<int>(Plant::AloeVera)] = 1;
rendingHarvestAmt[static_cast<int>(Plant::AloeVera)] = 15;
regrowthStart[static_cast<int>(Plant::AloeVera)] = 600000.0 / 6.0;
regrowthPeriod[static_cast<int>(Plant::AloeVera)] = 25000.0;

// Mint
lifespanAmt[static_cast<int>(Plant::Mint)] = 300000.0;
rnoGrowthMin[static_cast<int>(Plant::Mint)] = 5.0;
rnoGrowthMax[static_cast<int>(Plant::Mint)] = 30.0;
roptimalMin[static_cast<int>(Plant::Mint)] = 13.0;
roptimalMax[static_cast<int>(Plant::Mint)] = 25.0;
rdeathMin[static_cast<int>(Plant::Mint)] = -10.0;
rdeathMax[static_cast<int>(Plant::Mint)] = 35.0;
rwaterRequired[static_cast<int>(Plant::Mint)] = 20.0;
rwaterDeath[static_cast<int>(Plant::Mint)] = 480.0;
rstartingHarvestAmt[static_cast<int>(Plant::Mint)] = 2;
rendingHarvestAmt[static_cast<int>(Plant::Mint)] = 50;
regrowthStart[static_cast<int>(Plant::Mint)] = 300000.0 / 6.0;
regrowthPeriod[static_cast<int>(Plant::Mint)] = 15000.0;

// Thyme
lifespanAmt[static_>cast<int>(Plant::Thyme)] = 250000.0;
rnoGrowthMin[static_cast<int>(Plant::Thyme)] = 5.0;
rnoGrowthMax[static_cast<int>(Plant::Thyme)] = 28.0;
roptimalMin[static_cast<int>(Plant::Thyme)] = 11.0;
roptimalMax[static_cast<int>(Plant::Thyme)] = 22.0;
rdeathMin[static_cast<int>(Plant::Thyme)] = -15.0;
rdeathMax[static_cast<int>(Plant::Thyme)] = 38.0;
rwaterRequired[static_cast<int>(Plant::Thyme)] = 8.0;
rwaterDeath[static_cast<int>(Plant::Thyme)] = 500.0;
rstartingHarvestAmt[static_cast<int>(Plant::Thyme)] = 1;
rendingHarvestAmt[static_cast<int>(Plant::Thyme)] = 40;
regrowthStart[static_cast<int>(Plant::Thyme)] = 250000.0 / 6.0;
regrowthPeriod[static_cast<int>(Plant::Thyme)] = 12000.0;

// Sage
lifespanAmt[static_cast<>int>(Plant::Sage)] = 400000.0;
rnoGrowthMin[static_cast<int>(Plant::Sage)] = 5.0;
rnoGrowthMax[static_cast<int>(Plant::Sage)] = 32.0;
roptimalMin[static_cast<int>(Plant::Sage)] = 8.0;
roptimalMax[static_cast<int>(Plant::Sage)] = 22.0;
rdeathMin[static_cast<int>(Plant::Sage)] = -15.0;
rdeathMax[static_cast<int>(Plant::Sage)] = 38.0;
rwaterRequired[static_cast<int>(Plant::Sage)] = 15.0;
rwaterDeath[static_cast<int>(Plant::Sage)] = 500.0;
rstartingHarvestAmt[static_cast<int>(Plant::Sage)] = 1;
rendingHarvestAmt[static_cast<int>(Plant::Sage)] = 30;
regrowthStart[static_cast<int>(Plant::Sage)] = 400000.0 / 6.0;
regrowthPeriod[static_cast<int>(Plant::Sage)] = 18000.0;

// Rhubarb
lifespanAmt[static_cast<int>(Plant::Rhubarb)] = 500000.0;
rnoGrowthMin[static_cast<int>(Plant::Rhubarb)] = 5.0;
rnoGrowthMax[static_cast<int>(Plant::Rhubarb)] = 30.0;
roptimalMin[static_cast<int>(Plant::Rhubarb)] = 12.0;
roptimalMax[static_cast<int>(Plant::Rhubarb)] = 22.0;
rdeathMin[static_cast<int>(Plant::Rhubarb)] = -20.0;
rdeathMax[static_cast<int>(Plant::Rhubarb)] = 35.0;
rwaterRequired[static_cast<int>(Plant::Rhubarb)] = 20.0;
rwaterDeath[static_cast<int>(Plant::Rhubarb)] = 400.0;
rstartingHarvestAmt[static_cast<int>(Plant::Rhubarb)] = 3;
rendingHarvestAmt[static_cast<int>(Plant::Rhubarb)] = 100;
regrowthStart[static_cast<int>(Plant::Rhubarb)] = 500000.0 / 5.0;
regrowthPeriod[static_cast<int>(Plant::Rhubarb)] = 20000.0;

// Hay
lifespanAmt[static_cast<int>(Plant::Hay)] = 350000.0;
rnoGrowthMin[static_cast<int>(Plant::Hay)] = 4.0;
rnoGrowthMax[static_cast<int>(Plant::Hay)] = 35.0;
roptimalMin[static_cast<int>(Plant::Hay)] = 15.0;
roptimalMax[static_cast<int>(Plant::Hay)] = 30.0;
rdeathMin[static_cast<int>(Plant::Hay)] = -15.0;
rdeathMax[static_cast<int>(Plant::Hay)] = 40.0;
rwaterRequired[static_cast<int>(Plant::Hay)] = 30.0;
rwaterDeath[static_cast<int>(Plant::Hay)] = 300.0;
rstartingHarvestAmt[static_cast<int>(Plant::Hay)] = 10;
rendingHarvestAmt[static_cast<int>(Plant::Hay)] = 500;
regrowthStart[static_cast<int>(Plant::Hay)] = 350000.0 / 4.0;
regrowthPeriod[static_cast<int>(Plant::Hay)] = 25000.0;
}

class PlantDatabase {
  //TODO consider having plantdatabases for each region so that only necessary plant databases needs to be loaded in at a time.
    private:
    std::vector<Plant> seeds;
    std::vector<std::pair<int,int>> seedCoords;

    std::vector<Plant> 
    std::stack nextCropIndex;
    std::vector<Plant> cropList;
    std::vector<float> growthAmt;
    std::vector<int> yieldMisses;
    std::vector<float> collectedWater;
    std::vector<float> lastFullyWatered;
    std::vector<std::pair<int,int>> coords;
    std::vector<bool> harvestable;
  
    std::stack nextRegrowthCropIndgsex;
    std::vector<Plant> regrowthCropList;
    std::vector<float> regrowthGrowthAmt; //total amt for plant
    std::vector<float> regrowthAmt; //amount for regrowth
    std::vector<int> regrowthYieldMisses;
    std::vector<float> regrowthCollectedWater;
    std::vector<float> regrowthLastFullyWatered;
    std::vector<float> regrowthFullyGrownAmt;
    std::vector<std::pair<int,int>> regrowthCoords;
    std::vector<bool> regrowthHarvestable;
    public:
    PlantDatabase();
  
    //spawn.cpp
    void releasePlantSource(std::vector<Object>& rTileObject, std::vector<std::pair<int, int>>& rTileCoords, std::vector<Plant>& rSeeds, std::vector<std::pair<int,int>>& rSeedCoords, int tileIndex);
void setGerminationTime(std::vector<Plant>& rSeeds, Plant plant, int seedIndex);
void germinate(int seedIndex, bool regrowthPlant, bool randomGrowth);
void getCropIndex();
void addCrop(Plant plant, coord co);
void getRegrowthCropIndex();
void addRegrowthCrop(Plant plant, coord co);
bool viableHarvest(int plantIndex);
void eatSeeds(int animalIndex, int foodTileIndex, bool fruitTree);
void attemptPlantGrowth(int plant, int time, int biomeIndex);
void excreteSeed(int animalIndex, Plant plant);
void plant(int unitIndex, Plant plant);
void killTree(int plantIndex);
void killPlant(int plantIndex);
void updateCrops();
void updateRegrowthCrops();
};


#endif // PLANT_H_
