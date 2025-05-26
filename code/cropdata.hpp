#ifndef CROPDATA_H_
#define CROPDATA_H_
#include "basic.hpp"
#include "tile.hpp"

Plant crops[] = {
Plant::Wheat, Plant::Oat, Plant::Corn, Plant::Rice, Plant::Tomato, Plant::Onion, Plant::Potato, Plant::Cabbage, Plant::Pepper, Plant::Carrot, Plant::Poppy, Plant::Senna, Plant::Cotton, Plant::Papyrus, Plant::Flax, Plant::Hemp, Plant::Lettuce,
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

void plantTable() {

}



Plant regrowthCrops[] = {
 Plant::OliveTree, Plant::Grapevine, Plant::AppleTree, Plant::PearTree, Plant::PeachTree, Plant::MangoTree, Plant::BlueberryShrub, Plant::StrawberryShrub, Plant::Lavendar, Plant::Saffron, Plant::AloeVera, Plant::Mint, Plant::Thyme, Plant::Sage, Plant::Rhubarb,
};

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
static constexpr size_t cropArrSize = (size_t) Crops::CROPS_MAX;

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

static constexpr size_t rCropArrSize = (size_t) RegrowthCrops::REGROWTH_CROPS_MAX;

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
    fullyGrownAmt[Wheat] = 29250.0;
    noGrowthMin[Wheat] = 4.0;
    noGrowthMax[Wheat] = 38.0;
    optimalMin[Wheat] = 14.0;
    optimalMax[Wheat] = 21.0;
    deathMin[Wheat] = 0.0;
    deathMax[Wheat] = 42.0;
    waterRequired[Wheat] = 25.0;
    waterDeath[Wheat] = 250.0;
    harvestAmt[Wheat] = 30;
    requiresScythe[Wheat] = true;

    fullyGrownAmt[Oat] = 27787.5;
    noGrowthMin[Oat] = 4.0;
    noGrowthMax[Oat] = 38.0;
    optimalMin[Oat] = 14.0;
    optimalMax[Oat] = 21.0;
    deathMin[Oat] = 0.0;
    deathMax[Oat] = 42.0;
    waterRequired[Oat] = 25.0;
    waterDeath[Oat] = 250.0;
    harvestAmt[Oat] = 30;
    requiresScythe[Oat] = true;

    fullyGrownAmt[Corn] = 34125.0;
    noGrowthMin[Corn] = 10.0;
    noGrowthMax[Corn] = 40.0;
    optimalMin[Corn] = 16.0;
    optimalMax[Corn] = 28.0;
    deathMin[Corn] = 0.0;
    deathMax[Corn] = 45.0;
    waterRequired[Corn] = 30.0;
    waterDeath[Corn] = 250.0;
    harvestAmt[Corn] = 30;
    requiresScythe[Corn] = true;

    fullyGrownAmt[Rice] = 29250.0;
    noGrowthMin[Rice] = 15.0;
    noGrowthMax[Rice] = 40.0;
    optimalMin[Rice] = 20.0;
    optimalMax[Rice] = 35.0;
    deathMin[Rice] = 0.0;
    deathMax[Rice] = 45.0;
    waterRequired[Rice] = 25.0;
    waterDeath[Rice] = 200.0;
    harvestAmt[Rice] = 30;
    requiresScythe[Rice] = true;

    fullyGrownAmt[Tomato] = 25312.5;
    noGrowthMin[Tomato] = 10.0;
    noGrowthMax[Tomato] = 35.0;
    optimalMin[Tomato] = 18.0;
    optimalMax[Tomato] = 30.0;
    deathMin[Tomato] = 0.0;
    deathMax[Tomato] = 40.0;
    waterRequired[Tomato] = 25.0;
    waterDeath[Tomato] = 180.0;
    harvestAmt[Tomato] = 30;
    requiresScythe[Tomato] = false;

    fullyGrownAmt[Onion] = 27787.5;
    noGrowthMin[Onion] = 5.0;
    noGrowthMax[Onion] = 30.0;
    optimalMin[Onion] = 12.0;
    optimalMax[Onion] = 25.0;
    deathMin[Onion] = 0.0;
    deathMax[Onion] = 40.0;
    waterRequired[Onion] = 20.0;
    waterDeath[Onion] = 200.0;
    harvestAmt[Onion] = 30;
    requiresScythe[Onion] = false;

    fullyGrownAmt[Potato] = 27787.5;
    noGrowthMin[Potato] = 5.0;
    noGrowthMax[Potato] = 30.0;
    optimalMin[Potato] = 12.0;
    optimalMax[Potato] = 22.0;
    deathMin[Potato] = 0.0;
    deathMax[Potato] = 40.0;
    waterRequired[Potato] = 25.0;
    waterDeath[Potato] = 200.0;
    harvestAmt[Potato] = 30;
    requiresScythe[Potato] = false;

fullyGrownAmt[Cabbage] = 33750.0;
noGrowthMin[Cabbage] = 5.0;
noGrowthMax[Cabbage] = 30.0;
optimalMin[Cabbage] = 14.0;
optimalMax[Cabbage] = 28.0;
deathMin[Cabbage] = 0.0;
deathMax[Cabbage] = 40.0;
waterRequired[Cabbage] = 20.0;
waterDeath[Cabbage] = 200.0;
harvestAmt[Cabbage] = 30;
requiresScythe[Cabbage] = true;

fullyGrownAmt[Pumpkin] = 36562.5;
noGrowthMin[Pumpkin] = 10.0;
noGrowthMax[Pumpkin] = 30.0;
optimalMin[Pumpkin] = 16.0;
optimalMax[Pumpkin] = 28.0;
deathMin[Pumpkin] = 0.0;
deathMax[Pumpkin] = 40.0;
waterRequired[Pumpkin] = 30.0;
waterDeath[Pumpkin] = 250.0;
harvestAmt[Pumpkin] = 30;
requiresScythe[Pumpkin] = true;

fullyGrownAmt[Pepper] = 28125.0;
noGrowthMin[Pepper] = 10.0;
noGrowthMax[Pepper] = 35.0;
optimalMin[Pepper] = 18.0;
optimalMax[Pepper] = 28.0;
deathMin[Pepper] = 0.0;
deathMax[Pepper] = 40.0;
waterRequired[Pepper] = 25.0;
waterDeath[Pepper] = 220.0;
harvestAmt[Pepper] = 30;
requiresScythe[Pepper] = true;

fullyGrownAmt[Carrot] = 25312.5;
noGrowthMin[Carrot] = 5.0;
noGrowthMax[Carrot] = 30.0;
optimalMin[Carrot] = 12.0;
optimalMax[Carrot] = 25.0;
deathMin[Carrot] = 0.0;
deathMax[Carrot] = 40.0;
waterRequired[Carrot] = 20.0;
waterDeath[Carrot] = 180.0;
harvestAmt[Carrot] = 30;
requiresScythe[Carrot] = true;

fullyGrownAmt[Poppy] = 25312.5;
noGrowthMin[Poppy] = 5.0;
noGrowthMax[Poppy] = 30.0;
optimalMin[Poppy] = 10.0;
optimalMax[Poppy] = 25.0;
deathMin[Poppy] = 0.0;
deathMax[Poppy] = 40.0;
waterRequired[Poppy] = 20.0;
waterDeath[Poppy] = 200.0;
harvestAmt[Poppy] = 30;
requiresScythe[Poppy] = true;

fullyGrownAmt[Cannabis] = 36562.5;
noGrowthMin[Cannabis] = 15.0;
noGrowthMax[Cannabis] = 30.0;
optimalMin[Cannabis] = 18.0;
optimalMax[Cannabis] = 32.0;
deathMin[Cannabis] = 0.0;
deathMax[Cannabis] = 45.0;
waterRequired[Cannabis] = 30.0;
waterDeath[Cannabis] = 250.0;
harvestAmt[Cannabis] = 30;
requiresScythe[Cannabis] = true;

fullyGrownAmt[Senna] = 29250.0;
noGrowthMin[Senna] = 5.0;
noGrowthMax[Senna] = 30.0;
optimalMin[Senna] = 15.0;
optimalMax[Senna] = 35.0;
deathMin[Senna] = 0.0;
deathMax[Senna] = 45.0;
waterRequired[Senna] = 28.0;
waterDeath[Senna] = 220.0;
harvestAmt[Senna] = 30;
requiresScythe[Senna] = true;

fullyGrownAmt[Cotton] = 42187.5;
noGrowthMin[Cotton] = 10.0;
noGrowthMax[Cotton] = 35.0;
optimalMin[Cotton] = 18.0;
optimalMax[Cotton] = 32.0;
deathMin[Cotton] = 0.0;
deathMax[Cotton] = 45.0;
waterRequired[Cotton] = 35.0;
waterDeath[Cotton] = 250.0;
harvestAmt[Cotton] = 30;
requiresScythe[Cotton] = true;

fullyGrownAmt[Papyrus] = 42187.5;
noGrowthMin[Papyrus] = 20.0;
noGrowthMax[Papyrus] = 35.0;
optimalMin[Papyrus] = 15.0;
optimalMax[Papyrus] = 32.0;
deathMin[Papyrus] = 0.0;
deathMax[Papyrus] = 45.0;
waterRequired[Papyrus] = 35.0;
waterDeath[Papyrus] = 260.0;
harvestAmt[Papyrus] = 30;
requiresScythe[Papyrus] = true;

fullyGrownAmt[Flax] = 33750.0;
noGrowthMin[Flax] = 4.0;
noGrowthMax[Flax] = 35.0;
optimalMin[Flax] = 10.0;
optimalMax[Flax] = 22.0;
deathMin[Flax] = 0.0;
deathMax[Flax] = 40.0;
waterRequired[Flax] = 24.0;
waterDeath[Flax] = 220.0;
harvestAmt[Flax] = 30;
requiresScythe[Flax] = true;

fullyGrownAmt[Hemp] = 36562.5;
noGrowthMin[Hemp] = 10.0;
noGrowthMax[Hemp] = 35.0;
optimalMin[Hemp] = 15.0;
optimalMax[Hemp] = 30.0;
deathMin[Hemp] = 0.0;
deathMax[Hemp] = 40.0;
waterRequired[Hemp] = 28.0;
waterDeath[Hemp] = 250.0;
harvestAmt[Hemp] = 30;
requiresScythe[Hemp] = true;

fullyGrownAmt[Lettuce] = 25312.5;
noGrowthMin[Lettuce] = 7.0;
noGrowthMax[Lettuce] = 24.0;
optimalMin[Lettuce] = 16.0;
optimalMax[Lettuce] = 21.0;
deathMin[Lettuce] = 0.0;
deathMax[Lettuce] = 32.0;
waterRequired[Lettuce] = 20.0;
waterDeath[Lettuce] = 150.0;
harvestAmt[Lettuce] = 30;

lifespanAmt[Olive] = 57600000.0;
rnoGrowthMin[Olive] = 5.0;
rnoGrowthMax[Olive] = 38.0;
roptimalMin[Olive] = 15.0;
roptimalMax[Olive] = 28.0;
rdeathMin[Olive] = -7.0;
rdeathMax[Olive] = 45.0;
rwaterRequired[Olive] = 20.0;
rwaterDeath[Olive] = 800.0;
rstartingHarvestAmt[Olive] = 50;
rendingHarvestAmt[Olive] = 1000;
regrowthStart[Olive] = 1152000.0;
regrowth[Olive] = 31000.0;

lifespanAmt[Grape] = 400000.0;
rnoGrowthMin[Grape] = 6.0;
rnoGrowthMax[Grape] = 35.0;
roptimalMin[Grape] = 16.0;
roptimalMax[Grape] = 26.0;
rdeathMin[Grape] = -5.0;
rdeathMax[Grape] = 40.0;
rwaterRequired[Grape] = 22.0;
rwaterDeath[Grape] = 850.0;
rstartingHarvestAmt[Grape] = 80;
rendingHarvestAmt[Grape] = 1200;
regrowthStart[Grape] = 0.25 * 4560000.0;
regrowth[Grape] = 30000.0;

lifespanAmt[Apple] = 4000000.0;
rnoGrowthMin[Apple] = 4.0;
rnoGrowthMax[Apple] = 38.0;
roptimalMin[Apple] = 15.0;
roptimalMax[Apple] = 25.0;
rdeathMin[Apple] = -20.0;
rdeathMax[Apple] = 40.0;
rwaterRequired[Apple] = 25.0;
rwaterDeath[Apple] = 940.0;
rstartingHarvestAmt[Apple] = 35;
rendingHarvestAmt[Apple] = 1500;
regrowthStart[Apple] = 4560000.0/6.0;
regrowth[Apple] = 34000.0;

lifespanAmt[Fig] = 450000.0;
rnoGrowthMin[Fig] = 10.0;
rnoGrowthMax[Fig] = 35.0;
roptimalMin[Fig] = 18.0;
roptimalMax[Fig] = 27.0;
rdeathMin[Fig] = -10.0;
rdeathMax[Fig] = 38.0;
rwaterRequired[Fig] = 30.0;
rwaterDeath[Fig] = 920.0;
rstartingHarvestAmt[Fig] = 35;
rendingHarvestAmt[Fig] = 1400;
regrowthStart[Fig] = 70000;
regrowth[Fig] = 42000.0;

lifespanAmt[Pear] = 4560000.0;
rnoGrowthMin[Pear] = 3.0;
rnoGrowthMax[Pear] = 36.0;
roptimalMin[Pear] = 14.0;
roptimalMax[Pear] = 24.0;
rdeathMin[Pear] = -15.0;
rdeathMax[Pear] = 39.0;
rwaterRequired[Pear] = 27.0;
rwaterDeath[Pear] = 930.0;
rstartingHarvestAmt[Pear] = 38;
rendingHarvestAmt[Pear] = 1450;
regrowthStart[Pear] = 0.29 * 4560000.0;
regrowth[Pear] = 40000.0;

lifespanAmt[Peach] = 4200000.0;
rnoGrowthMin[Peach] = 6.0;
rnoGrowthMax[Peach] = 36.0;
roptimalMin[Peach] = 18.0;
roptimalMax[Peach] = 28.0;
rdeathMin[Peach] = -15.0;
rdeathMax[Peach] = 38.0;
rwaterRequired[Peach] = 40.0;
rwaterDeath[Peach] = 900.0;
rstartingHarvestAmt[Peach] = 25;
rendingHarvestAmt[Peach] = 1500;
regrowthStart[Peach] = 684000.0;
regrowth[Peach] = 42000.0;

lifespanAmt[Mango] = 4800000.0;
rnoGrowthMin[Mango] = 10.0;
rnoGrowthMax[Mango] = 40.0;
roptimalMin[Mango] = 20.0;
roptimalMax[Mango] = 30.0;
rdeathMin[Mango] = -5.0;
rdeathMax[Mango] = 42.0;
rwaterRequired[Mango] = 50.0;
rwaterDeath[Mango] = 950.0;
rstartingHarvestAmt[Mango] = 30;
rendingHarvestAmt[Mango] = 1600;
regrowthStart[Mango] = 720000.0;
regrowth[Mango] = 45000.0;

lifespanAmt[Blueberry] = 4200000.0;
rnoGrowthMin[Blueberry] = 3.0;
rnoGrowthMax[Blueberry] = 32.0;
roptimalMin[Blueberry] = 16.0;
roptimalMax[Blueberry] = 24.0;
rdeathMin[Blueberry] = -25.0;
rdeathMax[Blueberry] = 35.0;
rwaterRequired[Blueberry] = 30.0;
rwaterDeath[Blueberry] = 700.0;
rstartingHarvestAmt[Blueberry] = 20;
rendingHarvestAmt[Blueberry] = 1000;
regrowthStart[Blueberry] = 600000.0;
regrowth[Blueberry] = 38000.0;

lifespanAmt[Strawberry] = 360000.0;
rnoGrowthMin[Strawberry] = 2.0;
rnoGrowthMax[Strawberry] = 30.0;
roptimalMin[Strawberry] = 15.0;
roptimalMax[Strawberry] = 23.0;
rdeathMin[Strawberry] = -10.0;
rdeathMax[Strawberry] = 33.0;
rwaterRequired[Strawberry] = 35.0;
rwaterDeath[Strawberry] = 650.0;
rstartingHarvestAmt[Strawberry] = 40;
rendingHarvestAmt[Strawberry] = 120;
regrowthStart[Strawberry] = 32000.0;
regrowth[Strawberry] = 35000.0;

lifespanAmt[Lavender] = 15000.0;
rnoGrowthMin[Lavender] = 5.0;
rnoGrowthMax[Lavender] = 35.0;
roptimalMin[Lavender] = 17.0;
roptimalMax[Lavender] = 26.0;
rdeathMin[Lavender] = -10.0;
rdeathMax[Lavender] = 38.0;
rwaterRequired[Lavender] = 20.0;
rwaterDeath[Lavender] = 500.0;
rstartingHarvestAmt[Lavender] = 15;
rendingHarvestAmt[Lavender] = 800;
regrowthStart[Lavender] = 620000.0;
regrowth[Lavender] = 40000.0;

// Saffron
lifespanAmt[Saffron] = 100000.0;
rnoGrowthMin[Saffron] = 5.0;
rnoGrowthMax[Saffron] = 30.0;
roptimalMin[Saffron] = 10.0;
roptimalMax[Saffron] = 20.0;
rdeathMin[Saffron] = -10.0;
rdeathMax[Saffron] = 35.0;
rwaterRequired[Saffron] = 10.0;
rwaterDeath[Saffron] = 300.0;
rstartingHarvestAmt[Saffron] = 1;
rendingHarvestAmt[Saffron] = 1;
regrowthStart[Saffron] = 100000.0 / 4.0;
regrowth[Saffron] = 5000.0;

// Aloe Vera
lifespanAmt[AloeVera] = 600000.0;
rnoGrowthMin[AloeVera] = 5.0;
rnoGrowthMax[AloeVera] = 35.0;
roptimalMin[AloeVera] = 15.0;
roptimalMax[AloeVera] = 30.0;
rdeathMin[AloeVera] = -5.0;
rdeathMax[AloeVera] = 40.0;
rwaterRequired[AloeVera] = 5.0;
rwaterDeath[AloeVera] = 600.0;
rstartingHarvestAmt[AloeVera] = 1;
rendingHarvestAmt[AloeVera] = 15;
regrowthStart[AloeVera] = 600000.0 / 6.0;
regrowth[AloeVera] = 25000.0;

// Mint
lifespanAmt[Mint] = 300000.0;
rnoGrowthMin[Mint] = 5.0;
rnoGrowthMax[Mint] = 30.0;
roptimalMin[Mint] = 13.0;
roptimalMax[Mint] = 25.0;
rdeathMin[Mint] = -10.0;
rdeathMax[Mint] = 35.0;
rwaterRequired[Mint] = 20.0;
rwaterDeath[Mint] = 480.0;
rstartingHarvestAmt[Mint] = 2;
rendingHarvestAmt[Mint] = 50;
regrowthStart[Mint] = 300000.0 / 6.0;
regrowth[Mint] = 15000.0;

// Thyme
lifespanAmt[Thyme] = 250000.0;
rnoGrowthMin[Thyme] = 5.0;
rnoGrowthMax[Thyme] = 28.0;
roptimalMin[Thyme] = 11.0;
roptimalMax[Thyme] = 22.0;
rdeathMin[Thyme] = -15.0;
rdeathMax[Thyme] = 38.0;
rwaterRequired[Thyme] = 8.0;
rwaterDeath[Thyme] = 500.0;
rstartingHarvestAmt[Thyme] = 1;
rendingHarvestAmt[Thyme] = 40;
regrowthStart[Thyme] = 250000.0 / 6.0;
regrowth[Thyme] = 12000.0;

// Sage
lifespanAmt[Sage] = 400000.0;
rnoGrowthMin[Sage] = 5.0;
rnoGrowthMax[Sage] = 32.0;
roptimalMin[Sage] = 8.0;
roptimalMax[Sage] = 22.0;
rdeathMin[Sage] = -15.0;
rdeathMax[Sage] = 38.0;
rwaterRequired[Sage] = 15.0;
rwaterDeath[Sage] = 500.0;
rstartingHarvestAmt[Sage] = 1;
rendingHarvestAmt[Sage] = 30;
regrowthStart[Sage] = 400000.0 / 6.0;
regrowth[Sage] = 18000.0;

// Rhubarb
lifespanAmt[Rhubarb] = 500000.0;
rnoGrowthMin[Rhubarb] = 5.0;
rnoGrowthMax[Rhubarb] = 30.0;
roptimalMin[Rhubarb] = 12.0;
roptimalMax[Rhubarb] = 22.0;
rdeathMin[Rhubarb] = -20.0;
rdeathMax[Rhubarb] = 35.0;
rwaterRequired[Rhubarb] = 20.0;
rwaterDeath[Rhubarb] = 400.0;
rstartingHarvestAmt[Rhubarb] = 3;
rendingHarvestAmt[Rhubarb] = 100;
regrowthStart[Rhubarb] = 500000.0 / 5.0;
regrowth[Rhubarb] = 20000.0;

// Hay
lifespanAmt[Hay] = 350000.0;
rnoGrowthMin[Hay] = 4.0;
rnoGrowthMax[Hay] = 35.0;
roptimalMin[Hay] = 15.0;
roptimalMax[Hay] = 30.0;
rdeathMin[Hay] = -15.0;
rdeathMax[Hay] = 40.0;
rwaterRequired[Hay] = 30.0;
rwaterDeath[Hay] = 300.0;
rstartingHarvestAmt[Hay] = 10;
rendingHarvestAmt[Hay] = 500;
regrowthStart[Hay] = 350000.0 / 4.0;
regrowth[Hay] = 25000.0;
}



#endif // CROPDATA_H_
