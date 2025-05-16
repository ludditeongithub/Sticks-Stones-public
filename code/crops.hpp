#ifndef CROPS_H_
#define CROPS_H_
#include "basic.hpp"
#include "cropdata.hpp"

/* RUNTIME CROP DATA MANAGEMENT */

//get current global temp and sunlight
    float temp;
float sunlight;
float date;

std::vector<Plant> cropList;
std::vector<float> growthAmt;
std::vector<int> yieldMisses;
    std::vector<float> collectedWater;
    std::vector<float> lastFullyWatered;
    std::vector<bool> fullyGrown;
    std::vector<std::pair<int,int>> plantCoords;
// add new crop to actively tracked crops
void addCrop(Crops crop, coord co) {
    //threading sensitive:
    cropList.push_back(crop);
    //size_t i = cropList.size() - 1;
    yieldMisses.push_back(0);
    collectedWater.push_back(0.0);
    lastFullyWatered.push_back(0.0);
    fullyGrown.push_back(false);
    growthAmt.push_back(0.0);
    coords.push_back(co);
}

// crops update loop
void updateCrops() {
    for (int i = 0; i < cropList.size(); i++) {
        //get data for croptype
        Crops c = cropList[i];
        float fga = fullyGrownAmt[c];
        float ngmin = noGrowthMin[c];
        float ngmax = noGrowthMax[c];
        float omin = optimalMin[c];
        float omax = optimalMax[c];
        float dmin = deathMin[c];
        float dmax = deathMax[c];
        float wr = waterRequired[c];
        float wd = waterDeath[c];
        float ha = harvestAmt[c];
        float rs = requiresScythe[c];
        /* determine water status:
         * all 3 states determined by one waterRequired variable. Plant can collect x2 of waterRequired. If <, yieldMissed, too dry. If x4, waterlogged, yieldMissed. */
        float wcomp = 1.0;
        //1. collect water from ground
        //check for waterlog
        //3.
        if (collectedWater[i] < wr) {
            yieldMisses[i]++;
            wcomp = collectedWater[i] / wr;
        } else {
            lastFullyWatered[i] = date;
        }
        //check if plant death
        if (temp < dmin || temp > dmax || date - lastFullyWatered[i] > wd) {
                cropList[i] = EMPTY;
                continue;
        }
        //if fully grown, skip
            if (fullyGrown[i]) continue;
        //growthrate = sunlight * watercomponent *  soilquality * temperature
        if (sunlight == 0.0) {
            growthAmt[i] = 0.0;
        } else {
            //get temp component
        float tcomp;
        if (temp > omin && temp < omax) {
            tcomp = 1.0;
        } else if (temp < omin) {
          if (temp < ngmin) {
                tcomp = 0.0;
            } else {
                tcomp = (20.0 - (cmath::abs(temp - omin))) * 0.05;
            }
        } else {
            if (temp > ngmax){
                tcomp = 0.0;
            } else {
                 tcomp = (20.0 - (cmath::abs(temp - omax))) * 0.05;
            }
        }
        //add growthrate
        growthAmt[i] += sunlight * tcomp * wcomp;
        if (growthAmt[i] >= fga)  fullyGrown[i] = true;
        } //if sunlight == 0
    }
}

    std::vector<Plant> rCropList;
    std::vector<float> rGrowthAmt;
    std::vector<int> rYieldMisses;
    std::vector<float> rCollectedWater;
    std::vector<float> rLastFullyWatered;
    std::vector<coord> rCoords;
    std::vector<bool> harvestable;
// add new regrowth crops to actively tracked regrowth crops
void addRegrowthCrop(RegrowthCrops crop, coord co) {
    //threading sensitive:
    rCropList.push_back(crop);
    //size_t i = cropList.size() - 1;
    rCollectedWater.push_back(0.0);
    rLastFullyWatered.push_back(0.0);
    rGrowthAmt.push_back(0.0);
    rYieldMisses.push_back(0);
    rCoords.push_back(co);
}

// crops update loop
void updateRegrowthCrops() {
    for (int i = 0; i < rCropList.size(); i++) {
        //get data for croptype
        RegrowthCrops c = rCropList[i];
        float la = lifespanAmt[c];
        float ngmin = rnoGrowthMin[c];
        float ngmax = rnoGrowthMax[c];
        float omin = roptimalMin[c];
        float omax = roptimalMax[c];
        float dmin = rdeathMin[c];
        float dmax = rdeathMax[c];
        float wr = rwaterRequired[c];
        float wd = rwaterDeath[c];
        float sha = rstartingHarvestAmt[c];
        float eha = rendingHarvestAmt[c];
        float rs = regrowthStart[c];
        float r = regrowth[c];
        /* determine water status:
         * all 3 states determined by one waterRequired variable. Plant can collect x2 of waterRequired. If <, yieldMissed, too dry. If x4, waterlogged, yieldMissed. */
        float wcomp = 1.0;
        //1. collect water from ground
        //check for waterlog
        //3.
        if (rCollectedWater[i] < wr) {
            rYieldMisses[i]++;
            wcomp = rCollectedWater[i] / wr;
        } else {
            rLastFullyWatered[i] = date;
        }
        //check if plant death
        if (temp < dmin || temp > dmax || date - rLastFullyWatered[i] > wd) {
                cropList[i] = EMPTY;
                continue;
        }
        //growthrate = sunlight * watercomponent *  soilquality * temperature
        if (sunlight == 0.0) {
            rGrowthAmt[i] = 0.0;
        } else {
            //get temp component
        float tcomp;
        if (temp > omin && temp < omax) {
            tcomp = 1.0;
        } else if (temp < omin) {
          if (temp < ngmin) {
                tcomp = 0.0;
            } else {
                tcomp = (20.0 - (cmath::abs(temp - omin))) * 0.05;
            }
        } else {
            if (temp > ngmax){
                tcomp = 0.0;
            } else {
                 tcomp = (20.0 - (cmath::abs(temp - omax))) * 0.05;
            }
        }
        //add growthrate
        rGrowthAmt[i] += sunlight * tcomp * wcomp;
        if (rGrowthAmt[i] >= la) {
            cropList[i] = EMPTY;
            continue;
        }
        //add regrowth
        if (rGrowthAmt[i] < rs && !harvestable[i]) {
            regrowth[i] += sunlight * tcomp * wcomp;
        }
        if (rGrowthAmt[i] > rs) {
            harvestable[i] = true;
        }
        } //if sunlight == 0
    }
}


#endif // CROPS_H_
