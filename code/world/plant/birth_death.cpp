#include "entity.hpp"
#include "tables.hpp"

void PlantDatabase::releasePlantSource(std::vector<Object>& rTileObject, std::vector<std::pair<int, int>>& rTileCoords, int tileIndex) {
    if (isPlant(rTileObject[tileIndex])) { 
        //TODO: place seed in adjacent tile nearby, instead of on the same tile
Plant plant = std::get<Plant>(rTileObject[tileIndex]);
std::pair<int,int> empty = getNearestEmptyTile(tileIndex);
seedCoords.push_back(empty);
seeds.push_back(plant);
setGerminationTime();
//TODO: show on ground if it is tuber, bulb, cone, or other visible seed, and eventually bury over time (other seeds can be searched for, but are invisible in grass)
    }
}

void PlantDatabase::destroyPlant(uint16_t i) {
  plantList.remove(i);
  nextGrowth.remove(i);
  coords.remove(i);
  tileWater.remove(i);
  lastFullyWatered.remove(i);
}

void PlantDatabase::setGerminationTime(int seedIndex) {
  Plant plant = seeds[seedIndex];
   //randomize time based on duration of germination period
   int time = (int) (germinationPeriod[static_cast<int>(plant)] * rfloat( 0.01,1.0));
   addEvent(time, EventType::PlantGermination, (int)plant, seedIndex);
}


// Germination is activated randomly as events that start triggering en-masse automatically at the time of the year the plant type in question starts germinating. Also activates upon world spawn with a randomGrowth to generate plants.
void PlantDatabase::germinate(int seedIndex, bool randomGrowth, ObjectDatabase& od) {
  Plant plant = seeds[seedIndex];
  std::pair<int,int> coord = seedCoords[seedIndex];
  bool regrowthPlant = regrowthPlants[static_cast<int>(plant)];
  if (regrowthPlant) {
    uint32_t index = getRegrowthPlantIndex();
  regrowthCoords[index] = coord;
  regrowthPlants[index] = plant;
  regrowthCollectedWater[index] = 0.0;
  regrowthLastFullyWatered[index] = 0.0;
  regrowthGrowthAmt[index] = 0.0;
  yieldMisses[index] = 0.0;
  if (randomGrowth) {
    float multiplier = rfloat(0.001,0.998);
    regrowthGrowthAmt[index] = multiplier * regrowthFullyGrownAmt[static_cast<int>(plant)];
} else regrowthGrowthAmt[index] = 0;
} else {
  uint32_t index = getPlantIndex();
  coords[index] = coord;
  plants[index] = plant;
  if (randomGrowth) {
    float multiplier = rfloat(0.001,0.998);
    growthAmt[index] = multiplier * fullyGrownAmt[static_cast<int>(plant)];
  } else
    growthAmt[index] = 0;
}
 od.addObject(plant, coord.first, coord.second);
}


//TODO: consider making this array, so that animals can eat and poop many seeds, consider making this in animal database
// only performs the seed function, and removing the plant object, does not affect the animal
void PlantDatabase::prepareSeedDropping(int animalIndex, int plantIndex, bool regrowth) {
      if (tileIndexToPlantIndex.contains(foodTileIndex)) {
	int index = tileIndexToPlantIndex[foodTileIndex];
	bool regrowth = false;
    } else if (regrowthTileIndexToPlantIndex.contains(foodTileIndex)) {
	int index = tileIndexToRegrowthPlantIndex[foodTileIndex];
	bool regrowth = true;
      } else {
	sendError("Animal tried to eat plant at tile " + toString(foodTileIndex) + " but no plant was found.");
	return;
       }
      if (regrowth) {
	Plant& plantType = regrowthPlants[index];
      }
      else Plant& plantType = plants[index]; 
      addEvent(digestionTime, EventType::FutureSeedDropping, (int) plantType, animalIndex);
}


//TODO: complete and render
void PlantDatabase::killTree(int plantIndex) {
    switch (tilePlant[plantIndex]) {
        case Plant::PioneerTree:
            blockSize = 1;
            break;
        case Plant::DeciduousTree:
            blockSize = 2;
            break;
        case Plant::EvergreenTree:
            blockSize = 3;
            break;
        case Plant::RainforestTree:
            blockSize = 4;
            break;
        default:
            return;
    }
    TileBlock tb = findNearestAdjacentEmptyTileBlock(plantIndex, blockSize);
    std::tuple<int,int,int,int> adjacentTiles = adjacentTilesIndices[plantIndex];
    tilePlant[plantIndex] = Plant::Stump;
    int newTileIndex;
    for (int i = 1; i < blockSize; i++) {
        if (tb.direction == Direction::North) {
            newTileIndex = std::get<0>(adjacentTiles);
            adjacentTiles = adjacentTilesIndices;
        }
        if (tb.direction == Direction::South) {
            return std::get<2>(adjacentTiles);
        }
        if (tb.direction == Direction::West) {
            return std::get<4>(adjacentTiles);
        }
        if (tb.direction == Direction::East) {
            return std::get<1>(adjacentTiles);
        }
    }
}

void PlantDatabase::killPlant(int plantIndex) {
        Plant plant = tilePlant[tileIndex];
        PlantType type = plants[(int)plant].plantType;

        tileObject[tileObjectIndex] = Plant::None;
        switch (plantType) {
            case Tree:
            case FruitTree:
                treeDeath(plantIndex);
        }
}
