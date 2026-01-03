#include <plant/tables.hpp>
#include <plant/growth_manager.hpp>
#include <region/entity.hpp>
#include <plant/registry.hpp>
#include "basic.hpp"


namespace plant {

bool GrowthManager::viableHarvest(entt::entity& crop) {
  if (crop.view<Growth> < fullyGrownAmt[static_cast<int>(crop.view<Type>)] return true;
}

  // performs growth over interval
  void GrowthManager::attemptPlantGrowth(PlantRegistry& pr, entt::entity& region) {    
    entt::entity &tile = getTile();
    int i = static_cast<int>(crop.get<Type>);
    auto &t{region.get<Temperature>};
    auto &g{crop.get<Growth>};
    auto &w{tile.get<WaterStored>};
    // these 3 multipliers factor to apply the interval of time which has passed since the last growth check.
    float tcomp = 1.0;
    float wcomp = 1.0;
    float scomp = 1.0;
    // check if dead   
    if (t < tempDeathMin[i] || t > tempDeathMax[i] || w < waterDeathMin[i] || w > waterDeathMax[i]) {
      pr.destroyCrop(e);
      return;
    }
    // 1.  //temperature
    if (t < tempOptimalMax[i] && t > tempOptimalMin[i]) {
      tcomp *= 1.1;
    } else if (t < tempGrowthMax[i]) {
      tcomp = std::lerp(diffMult(t, tempOptimalMax[i], tempGrowthMax[i]), 1.0, 0.4);
    } else if (t > tempGrowthMin[i]) {
      tcomp = std::lerp(diffMult(t, tempOptimalMin[i], tempGrowthMin[i]), 1.0, 0.4);
    } 
    //2. collect water from ground
    if (waterGrowthMin[i] <= w) w -= waterGrowthMin[i];
    else {
      wcomp = std::lerp(diffMult(w, waterGrowthMin[i], 0), 1.0, 0.4); 
      w = 0;
    }
    // 3. sunlight
    
    // 5. apply yield miss if applicable (TODO: trigger offshoot algo for regrowth)
    if ((currentTime - interval < lastCheckTime) && yield == false) yieldMisses++;
      
}

  // plants update loop
void PlantDatabase::updatePlants() {
    for (int i = 0; i < plantList.size(); i++) {
        //get data for planttype
        Plants c = plantList[i];
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


// plants update loop
void PlantDatabase::updateRegrowthPlants() {
  view.each(auto e, Type t) {

  }
    for (int i = 0; i < regrowthPlantList.size(); i++) {
        //get data for planttype
        RegrowthPlants c = rPlantList[i];
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
        float r = regrowthPeriod[c];
        /* determine water status:
         * all 3 states determined by one waterRequired variable. Plant can collect x2 of waterRequired. If <, yieldMissed, too dry. If x4, waterlogged, yieldMissed. */
        float wcomp = 1.0;
        //1. collect water from ground
        //check for waterlog
        if (rCollectedWater[i] < wr) {
            rYieldMisses[i]++;
            wcomp = rCollectedWater[i] / wr;
        } else {
            regrowthLastFullyWatered[i] = date;
        }
        //check if plant death
        if (temp < dmin || temp > dmax || date - rLastFullyWatered[i] > wd) {
                regrowthPlantList[i] = EMPTY;
                continue;
        }
        //growthrate = sunlight * watercomponent *  soilquality * temperature
        if (sunlight == 0.0) {
            regrowthGrowthAmt[i] = 0.0;
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
        regrowthGrowthAmt[i] += sunlight * tcomp * wcomp;
        if (regrowthGrowthAmt[i] >= la) {
            regrowthPlantList[i] = EMPTY;
            continue;
        }
        //add regrowth
        if (regrowthGrowthAmt[i] < rs && !regrowthHarvestable[i]) {
            regrowthAmt[i] += sunlight * tcomp * wcomp;
        }
        if (regrowthAmt[i] > rs) {
            regrowthHarvestable[i] = true;
        }
        } //if sunlight == 0
    }
}


};
