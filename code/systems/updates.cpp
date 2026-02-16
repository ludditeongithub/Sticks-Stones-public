#include "updates.hpp"
#include "pathfinding.hpp"
#include "world/animal/enum.hpp"
#include "world/world.hpp"

//TODO: have plant temp values be precalcuated so chunk temps is accessed faster
void updatePlants(Arena<float>& nextGrowth, Array<Plant> &plantList, Array<Coord> &coords,
                  Array<float> &chunkTemps, Array<float>& tileWater,
                  Array<float>& lastFullyWatered,
                  Arena2D<float> &dailyInsolations, Arena<float> &cloudCovers,
                  Arena<bool>& dead) {
  
  //temp
  for (uint32_t i = 0; i < plantList.size(); i++) {
        Plant p = plantList[i];

	if (plantList[i] == Plant::NONE) continue;
	nextGrowth[i] = 1.0;
	
        float dmin = tempDeathMin[p];
        float dmax = tempDeathMax[p];
	float ngmin = tempGrowthMin[p];
        float ngmax = tempGrowthMax[p];
        float omin = tempOptimalMin[p];
        float omax = tempOptimalMax[p];

	// Temperature
	Coord pos = coords[i];
        uint16_t chunk = getChunkIndexFromTile(pos);
	float temp = chunkTemps[chunk];        
	if (temp < omax && temp > omin) {
	  
	} else if (temp > ngmin && temp < ngmax) {
	  nextGrowth[i] = 0.0;
	} else if (temp < dmin || temp > dmax) {
	  dead[i] = true;
	  continue;
	} else {
	  nextGrowth[i] *= UNOPTIMAL_TEMP_MULT;
        }

	// Water
	// float wr = waterRequired[p];
        // uint16_t wd = waterDeath[p];        
	// if (tileWater[i] > wr) {
	//   lastFullyWatered[i] = time;	  
	// } else if (time - lastFullyWatered[i] > wd) {
	//   dead[i] = true;
	//   continue;
	// } else nextGrowth[i] *= LOW_WATER_MULT;		

	// Sunlight
        uint16_t latitude = getChunkLatitude(chunk);
	uint16_t timeZone = getChunkTimeZone(chunk);
        float is = dailyInsolations[latitude][timeZone];
        float psun = perfectSunlight[p];        
	//sunlight (from 0.0 to 1.0)
	if (is <= 0.0) {
            nextGrowth[i] = 0.0;
        } else {
          // factor cloud cover
          float ccf = cloudCovers[chunk] * MAX_CLOUD_FACTOR;
          float sunlight = is / (1 + ccf);
	  float sf = 1.0;
	  if (sunlight < psun) sf = normalize(sunlight, 0, psun);
          nextGrowth[i] *= sf;
        }	
   }
}

// wander becomes idle at end
// also automatically sets   
void updateAnimalPositions(PathfindingManager::PathsBuffer &rpd, Array<Coord> positions,
                     Array<float> timers, Array<ActionDecisionStatus> actions) {
  int j = 0;
  for (int i = 0; i < rpd.size; i++) {
    if (timers[i] <= 0 && actions[i] != ActionDecisionStatus::Idle) {
      // this could be pre-stored in a contiguous array
      Coord c = rpd.pop(i);      
         if (manhattanDist(c, positions[i]) > 1)
           throw std::invalid_argument("Tile movement must be between tiles 1 distance away from each other.");
	 Coord& p = positions[i];
         p = c;
	 // get new path if there are x or less tiles to go and destination farther than x tiles
         if (rpd.current[i] >= rpd.end[i] - NEW_PATH_DIST) {
           if (manhattanDist(rpd.destination[i], p) >= NEW_PATH_DIST) {
  	      actions[i] = ActionDecisionStatus::NewPath;
           } else switch (actions[i]) {
	   case ActionDecisionStatus::AnimalFoodSearch:
           case ActionDecisionStatus::AnimalDrinkSearch:
           case ActionDecisionStatus::AnimalBreedSearch:	     
	     break;
	   default:
	      actions[i] = ActionDecisionStatus::Assign;
	   }

             
	 }
      } 
   }
}

