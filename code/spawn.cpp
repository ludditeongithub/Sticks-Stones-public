#include "spawn.hpp"

/*  GUIDELINES FOR SPAWNING
 *   all natural entities must roughly spawn as often as they die in nature to ensure that they are not eliminated or grow too much as the game progresses.
 *
 *   ergo, the formula for annual plant spawning is to just have them spawn with the same formula they used before, since all of the annuals will die in the winter, so an equal chance amount of annuals should spawn next spring, as seeds.
 *
 *   perrenials or multi-year plants should spawn at a randomized growth amount. the formula for their respawns should be their total growth amount (period from ), divided by the respawn period,
 *   */
void releasePlantSource(int plantIndex) {
Plant plant = std::get_if<Plant>(&tileObject[tileIndex]);
//TODO: place seed in adjacent tile nearby, instead of on the same tile
seedCoords.push_back(tileCoords[plantIndex]);
seeds.push_back(plant);
//TODO: show on ground if it is tuber, bulb, cone, or other visible seed, and eventually bury over time (other seeds can be searched for, but are invisible in grass)
}

// an event is sent to the event manager which triggers the mass spawn of all that type of plant, by this function, which sends events distributed over a set amount of time to germinate all seeds of that plant
void startPlantGrowth(Plant plant) {
for (int i = 0; i < seeds.size(); i++) {
    if (seeds[i] == plant) {
        //randomize time based on duration of germination period
        int time = (int) (plant.germinationPeriod * rfloat(0.01,1.0));
        addEvent(time, EventType::SeedGermination, (int)plant, i);
    }
}
}

// Germination is activated randomly as events that start triggering en-masse automatically at the time of the year the plant type in question starts germinating
void germinate(int seedIndex) {
std::pair<int,int> coord = seedCoords[seedIndex];
int plantIndex = tileIndex[coord];
tileObject[plantIndex] = seeds[seedIndex];
PlantType plantType = plants[seeds[seedIndex]].plantType;
if (plantType != PlantType::Root | plantType != PlantType::Tuber | plantType != PlantType::Bulb) seeds[seedIndex] = Plant::NONE;
}
//TODO: have seed in seeds vector become none upon pick up or consuming animals or pawns

//used for moss, foliage, etc
void spawnPlant(Plant plant) {

}

void spawnInitialPlants() {
	for (int i = 0; i < (int)tileIndex.size(); i++) {
        //TODO: separate mechanism for plants that stay in the same place and those who do not
		// mechanism to only work on some tiles for subsequent spawns.
		if (tileChance != 0.0) {
			if (rfloat(0.0,1.0) > tileChance) continue;
		}

         std::pair<int,int> tile = tileCoords[i];
		 float temp = 0.0;
		 float threshold = 0.0;
         float optimal = 0.55;
         float great = 0.4;
         float good = 0.25;
         float poorly = 0.05;
         float rarely = 0.01;

         Tile type = tileType[i];
         Plant plant = Plant::NONE;
         Grass grass = Grass::NONE;
         // invalid tiles
         if (type == Tile::Ice) continue;
         if (type == Tile::FrozenSoil) continue;
         if (type == Tile::Gravel) continue;
         if (type == Tile::Stone) continue;
         if (type == Tile::ShallowWater) continue;
         if (type == Tile::FlowingWater) continue;
         if (type == Tile::DeepWater) continue;
         if (type == Tile::Sand) continue;
         if (type == Tile::Snow) continue;
         uint32_t cell = tileCellIndex[i];
         cout << " Cell: " << cell;
         std::pair<float,float> cellCoord = mapsLink[cell];
         cout << " Cell Coords: " << cellCoord.first << "," << cellCoord.second << endl;
         int biome = biomeMap[(int)cellCoord.first][(int)cellCoord.second];
         int temperature = temperatureMap[(int)cellCoord.first][(int)cellCoord.second];
         int humidity = humidityMap[(int)cellCoord.first][(int)cellCoord.second];

// PLANT CATEGORY RARITIES - chance of each plant type spawning in each biome, on a tile, not adjusted for other checks (trees have higher raw spawn rate due to not being able to spawn next to other trees)
// the threshold that the random generated number needs to pass to ensure that the plant species even has a chance of competing.

    //% of much non-grass plants appear on tiles and grass plants respectively
    float treesChance = 0.0;
    float citrusChance = 0.0;
    float stoneChance = 0.0;
    float pomeChance = 0.0;
    float oliveChance = 0.0;
    float mossChance = 0.0;
        float fernChance = 0.0;
        float bushChance = 0.0;
        float succulentChance = 0.0;
        float berryShrubChance = 0.0;
        float floweringChance = 0.0;
        float fruitVeggieChance = 0.0;
        float leafyChance = 0.0;
        float rootChance = 0.0;
        float reedChance = 0.0;
        float tuberChance = 0.0;
        float bulbChance = 0.0;
        float grainChance = 0.0;
        float grapevineChance = 0.0;
        float herbChance = 0.0;
        float textileChance = 0.0;
    float plantCoverage = 0.0;
    float grassCoverage = 0.0;

    if (biome == 1) {
        treesChance = 0.04; // acacia
        citrusChance = 0.0;
        stoneChance = 0.0;
        pomeChance = 0.0;
        oliveChance = 0.06;
        mossChance = 0.0;
        fernChance = 0.0;
        bushChance = 0.45;
        succulentChance = 0.7;
        berryShrubChance = 0.0;
        leafyChance = 0.00;
        rootChance = 0.0;
        tuberChance = 0.0;
        bulbChance = 0.06;
        grainChance = 0.0;
        grapevineChance = 0.0;
        herbChance = 0.075;
        textileChance = 0.02;

        plantCoverage = 0.15;
        grassCoverage = 0.03;
    }
    if (biome == 2) {
        treesChance = 0.2;
        citrusChance = 0.0;
        stoneChance = 0.0;
     pomeChance = 0.0;
     oliveChance = 0.0;
     mossChance = 0.2;
     fernChance = 0.2;
     bushChance = 0.3;
     succulentChance = 0.06;
     berryShrubChance = 0.2;
     leafyChance = 0.2;
     rootChance = 0.1;
     reedChance = 0.0;
     tuberChance = 0.04;
     bulbChance = 0.06;
     grainChance = 0.35;
     grapevineChance = 0.0;
     herbChance = 0.25;
     textileChance = 0.06;

     plantCoverage = 0.2;
     grassCoverage = 0.97;
    }
    if (biome == 3) {
    treesChance = 0.80;
    citrusChance = 0.08;
    stoneChance = 0.08;
    pomeChance = 0.0;
    oliveChance = 0.08;
    mossChance = 0.04;
    fernChance = 0.08;
    bushChance = 0.6;
    succulentChance = 0.16;
    berryShrubChance = 0.12;
    leafyChance = 0.08;
    rootChance = 0.1;
    tuberChance = 0.08;
    bulbChance = 0.12;
    grainChance = 0.2;
    grapevineChance = 0.0;
    herbChance = 0.2;
    textileChance = 0.04;

    plantCoverage = 0.25;
    grassCoverage = 0.75;
}
if (biome == 4) {
    treesChance = 0.3;
    citrusChance = 0.0;
    stoneChance = 0.0;
    pomeChance = 0.0;
    oliveChance = 0.0;
    mossChance = 0.15;
    fernChance = 0.3;
    bushChance = 0.3;
    reedChance = 0.4;
    succulentChance = 0.06;
    berryShrubChance = 0.09;
    leafyChance = 0.0; // increase when adding duckweed and other water plants
    rootChance = 0.0; // increase when adding wetland root plants
    tuberChance = 0.0; // increase when adding water tubers
    bulbChance = 0.0;
    grainChance = 0.3;
    grapevineChance = 0.0;
     herbChance = 0.3;
    textileChance = 0.02;

    plantCoverage = 0.55;
    grassCoverage = 0.35;
}
if (biome == 5) {
    treesChance = 0.92;
    citrusChance = 0.02;
    stoneChance = 0.02;
    pomeChance = 0.0;
    oliveChance = 0.0;
    mossChance = 0.25;
    fernChance = 0.35;
    bushChance = 0.2;
    reedChance = 0.05;
    succulentChance = 0.04;
    berryShrubChance = 0.1;
    leafyChance = 0.1;
    rootChance = 0.1;
    tuberChance = 0.08;
    bulbChance = 0.07;
    grainChance = 0.1;
    grapevineChance = 0.04;
    herbChance = 0.18;
    textileChance = 0.02;

    plantCoverage = 0.93;
    grassCoverage = 0.08;
}
if (biome == 6) {
    treesChance = 0.85;
    citrusChance = 0.0;
    stoneChance = 0.0;
    pomeChance = 0.0;
    oliveChance = 0.0;
    mossChance = 0.2;
    fernChance = 0.14;
    bushChance = 0.2;
    succulentChance = 0.02;
    berryShrubChance = 0.2;
    leafyChance = 0.08;
    rootChance = 0.08;
    tuberChance = 0.02;
    bulbChance = 0.04;
    grainChance = 0.06;
    grapevineChance = 0.0;
     herbChance = 0.08;
    textileChance = 0.02;

    plantCoverage = 0.94;
    grassCoverage = 0.05;
}
if (biome == 7) {
    treesChance = 0.85;
    citrusChance = 0.02;
    stoneChance = 0.02;
    pomeChance = 0.0;
    oliveChance = 0.0;
    mossChance = 0.2;
    fernChance = 0.3;
    bushChance = 0.2;
    reedChance = 0.02;
    succulentChance = 0.0;
    berryShrubChance = 0.2;
    leafyChance = 0.05; //add more later
    rootChance = 0.06;
    tuberChance = 0.05;
    bulbChance = 0.04;
    grainChance = 0.07;
    grapevineChance = 0.04;
     herbChance = 0.18;
    textileChance = 0.02;

    plantCoverage = 0.96;
    grassCoverage = 0.04;
}
if (biome == 8) {
    treesChance = 0.25;
    citrusChance = 0.0;
    stoneChance = 0.0;
    pomeChance = 0.0;
    oliveChance = 0.0;
    mossChance = 0.5;
    fernChance = 0.4;
    bushChance = 0.5;
    succulentChance = 0.3;
    berryShrubChance = 0.1;
    leafyChance = 0.3;
    rootChance = 0.2;
    tuberChance = 0.2;
    bulbChance = 0.15;
    grainChance = 0.04;
    herbChance = 0.05;
    grapevineChance = 0.05;
    textileChance = 0.01;

    plantCoverage = 0.2;
    grassCoverage = 0.1;
}
if (biome == 9) {
    treesChance = 0.0;
    citrusChance = 0.0;
    stoneChance = 0.0;
    pomeChance = 0.0;
    oliveChance = 0.0;
    mossChance = 0.6;
    fernChance = 0.06;
    bushChance = 0.4;
    succulentChance = 0.07;
    berryShrubChance = 0.0;
    leafyChance = 0.2;
    rootChance = 0.2;
    tuberChance = 0.0;
    bulbChance = 0.0;
    grainChance = 0.0;
    grapevineChance = 0.0;
    herbChance = 0.02;
    textileChance = 0.0;

    plantCoverage = 0.15;
    grassCoverage = 0.075;
}
if (biome == 10) {
    treesChance = 0.0; // make trees later
    citrusChance = 0.0;
    stoneChance = 0.0;
    pomeChance = 0.0;
    oliveChance = 0.0;
    mossChance = 0.2;
    fernChance = 0.05;
    bushChance = 0.3;
    succulentChance = 0.2;
    berryShrubChance = 0.05;
    leafyChance = 0.15;
    rootChance = 0.15;
    tuberChance = 0.05;
    bulbChance = 0.05;
    grainChance = 0.0;
    grapevineChance = 0.0;
    herbChance = 0.02;
    textileChance = 0.03;

    plantCoverage = 0.1;
    grassCoverage = 0.04;
}


constexpr std::array<Plant, 4> trees = {
    Plant::DeciduousTree,
    Plant::EvergreenTree,
    Plant::PioneerTree,
    Plant::TropicalTree
};

// SPAWN ALL PLANTS
if (rand() / (float) RAND_MAX < plantCoverage) {
	tileEmpty[tileIndex] = false;
if (rand() / (float) RAND_MAX < treesChance) {
if (adjCheckList(tileIndex, tilePlant, (int)tile.first, (int)tile.second, trees, 1))  {
     // TREES
         //if tree is adjacent, skip trees
         // Deciduous
temp = 0;
    if (type == Tile::Podzol) temp += poorly;
         if (type == Tile::LoamSoil) temp += optimal;
         if (type == Tile::PeatSoil) temp += poorly;
         if (type == Tile::SandySoil) temp += poorly;
         if (type == Tile::ClaySoil) temp += poorly;
         if (type == Tile::SiltySoil) temp += optimal;
         if (type == Tile::RockySoil) temp = 0;
         if (type == Tile::AridSoil) temp += poorly;
         if (type == Tile::Oxisol) temp += poorly;
         if (type == Tile::Gleysol) temp += rarely;
         rangePenalty(temperature,64,77,temp);
         rangePenalty(humidity,52,78,temp);
         if (temp > threshold) {
             threshold = temp;
             plant = Plant::DeciduousTree;
         }

         // Evergreen
temp = 0;
         if (type == Tile::Podzol) temp += good;
if (type == Tile::LoamSoil) temp += good;
if (type == Tile::PeatSoil) temp += poorly;
if (type == Tile::SandySoil) temp += good;
if (type == Tile::ClaySoil) temp += poorly;
if (type == Tile::SiltySoil) temp += good;
if (type == Tile::RockySoil) temp += poorly;
if (type == Tile::AridSoil) temp += rarely;
if (type == Tile::Oxisol) temp += poorly;
if (type == Tile::Gleysol) temp += poorly;
 rangePenalty(temperature,46,68,temp);
  rangePenalty(humidity,60,87,temp);
if (temp > threshold) {
             threshold = temp;
             plant = Plant::EvergreenTree;
         }

         // Pioneer
temp = 0;
if (type == Tile::Podzol) temp += rarely;
if (type == Tile::LoamSoil) temp += optimal;
if (type == Tile::PeatSoil) temp += great;
if (type == Tile::SandySoil) temp += good;
if (type == Tile::ClaySoil) temp += poorly;
if (type == Tile::SiltySoil) temp += optimal;
if (type == Tile::RockySoil) temp += rarely;
if (type == Tile::AridSoil) temp += poorly;
if (type == Tile::Oxisol) temp += poorly;
if (type == Tile::Gleysol) temp += great;
 rangePenalty(temperature,55,86,temp);
 rangePenalty(humidity,50,80,temp);
 if (temp > threshold && plant != Plant::EvergreenTree && plant != Plant::DeciduousTree) {
             threshold = temp;
             plant = Plant::PioneerTree;
         }
         // Tropical
temp = 0;
if (type == Tile::Podzol) temp += poorly;
if (type == Tile::LoamSoil) temp += optimal;
if (type == Tile::PeatSoil) temp += optimal;
if (type == Tile::SandySoil) temp += good;
if (type == Tile::ClaySoil) temp += poorly;
if (type == Tile::SiltySoil) temp += good;
if (type == Tile::RockySoil) temp = 0;
if (type == Tile::AridSoil) temp += poorly;
if (type == Tile::Oxisol) temp += optimal;
if (type == Tile::Gleysol) temp += optimal;
 rangePenalty(temperature,73,87,temp);
 rangePenalty(humidity,80,120,temp);
 if (temp > threshold) {
             threshold = temp;
             plant = Plant::TropicalTree;
         }
}
}

if (rand() / (float) RAND_MAX < mossChance) {
    // Moss
temp = 0;
    if (type == Tile::Podzol) temp += great;
if (type == Tile::LoamSoil) temp += great;
if (type == Tile::PeatSoil) temp += optimal;
if (type == Tile::SandySoil) temp += good;
if (type == Tile::ClaySoil) temp += good;
if (type == Tile::SiltySoil) temp += great;
if (type == Tile::RockySoil) temp += great;
if (type == Tile::AridSoil) temp = 0;
if (type == Tile::Oxisol) temp += poorly;
if (type == Tile::Gleysol) temp += optimal;
rangePenalty(temperature,40,75,temp);
         rangePenalty(humidity,85,120,temp);
if (temp > threshold) {
        threshold = temp;
        plant = Plant::Moss;
}
}
if (rand() / (float) RAND_MAX < bushChance) {
         // BUSHES
if (type == Tile::Podzol) temp += optimal;
if (type == Tile::LoamSoil) temp += optimal;
if (type == Tile::PeatSoil) temp += great;
if (type == Tile::SandySoil) temp += good;
if (type == Tile::ClaySoil) temp += good;
if (type == Tile::SiltySoil) temp += great;
if (type == Tile::RockySoil) temp += poorly;
if (type == Tile::AridSoil) temp += rarely;
if (type == Tile::Oxisol) temp += great;
if (type == Tile::Gleysol) temp += great;
 rangePenalty(temperature,45,86,temp);
 rangePenalty(humidity,60,87,temp);
 if (temp > threshold) {
             threshold = temp;
             plant = Plant::Bush;
         }
}
if (rand() / (float) RAND_MAX < succulentChance) {
//Cacti
temp = 0;
    if (type == Tile::Podzol) temp += rarely;
if (type == Tile::LoamSoil) temp += great;
if (type == Tile::PeatSoil) temp += poorly;
if (type == Tile::SandySoil) temp += optimal;
if (type == Tile::ClaySoil) temp += good;
if (type == Tile::SiltySoil) temp += great;
if (type == Tile::RockySoil) temp += good;
if (type == Tile::AridSoil) temp += optimal;
if (type == Tile::Oxisol) temp += great;
if (type == Tile::Gleysol) temp += rarely;
rangePenalty(temperature, 45, 86, temp);
rangePenalty(humidity, 1, 30, temp);
if (temp > threshold) {
             threshold = temp;
             plant = Plant::Cactus;
         }
}

// FRUIT TREES
if (rand() / (float) RAND_MAX < citrusChance) {
// Citrus
temp = 0;
    if (type == Tile::Podzol) temp += poorly;
if (type == Tile::LoamSoil) temp += optimal;
if (type == Tile::PeatSoil) temp += good;
if (type == Tile::SandySoil) temp += great;
if (type == Tile::ClaySoil) temp += poorly;
if (type == Tile::SiltySoil) temp += great;
if (type == Tile::RockySoil) temp += rarely;
if (type == Tile::AridSoil) temp += rarely;
if (type == Tile::Oxisol) temp += poorly;
if (type == Tile::Gleysol) temp += poorly;
rangePenalty(temperature, 70, 80, temp);
rangePenalty(humidity, 60, 75, temp);
if (temp > threshold) {
             threshold = temp;
             int ran = rint(0,2);
             if (ran == 0) plant = Plant::OrangeTree;
             if (ran == 1) plant = Plant::LemonTree;
             if (ran == 2) plant = Plant::LimeTree;
         }
}
if (rand() / (float) RAND_MAX < stoneChance) {
// Stone/Drupe
temp = 0;
    if (type == Tile::Podzol) temp += poorly;
if (type == Tile::LoamSoil) temp += optimal;
if (type == Tile::PeatSoil) temp += good;
if (type == Tile::SandySoil) temp += great;
if (type == Tile::ClaySoil) temp += poorly;
if (type == Tile::SiltySoil) temp += great;
if (type == Tile::RockySoil) temp += rarely;
if (type == Tile::AridSoil) temp += rarely;
if (type == Tile::Oxisol) temp += poorly;
if (type == Tile::Gleysol) temp += poorly;
rangePenalty(temperature, 60, 75, temp);
rangePenalty(humidity, 45, 68, temp);
if (temp > threshold) {
             threshold = temp;
             int ran = rint(0,3);
             if (ran == 0) plant = Plant::PeachTree;
             if (ran == 1) plant = Plant::PlumTree;
             if (ran == 2) plant = Plant::CherryTree;
             if (ran == 3) plant = Plant::ApricotTree;
         }
}
if (rand() / (float) RAND_MAX < pomeChance) {
// Pome
temp = 0;
    if (type == Tile::Podzol) temp += poorly;
if (type == Tile::LoamSoil) temp += optimal;
if (type == Tile::PeatSoil) temp += good;
if (type == Tile::SandySoil) temp += great;
if (type == Tile::ClaySoil) temp += poorly;
if (type == Tile::SiltySoil) temp += great;
if (type == Tile::RockySoil)temp += rarely;
if (type == Tile::AridSoil)temp += rarely;
if (type == Tile::Oxisol)temp += poorly;
if (type == Tile::Gleysol)temp += poorly;
rangePenalty(temperature, 55, 72, temp);
rangePenalty(humidity, 55, 75, temp);
if (temp > threshold) {
             threshold = temp;
             int ran = rint(0,1);
             if (ran == 0) plant = Plant::AppleTree;
             if (ran == 1) plant = Plant::PearTree;
     }
}
if (rand() / (float) RAND_MAX < oliveChance) {
// Olive Trees
temp = 0;
    if (type == Tile::Podzol) temp += rarely;
if (type == Tile::LoamSoil) temp += great;
if (type == Tile::PeatSoil) temp += rarely;
if (type == Tile::SandySoil) temp += optimal;
if (type == Tile::ClaySoil) temp += rarely;
if (type == Tile::SiltySoil) temp += great;
if (type == Tile::RockySoil) temp += good;
if (type == Tile::AridSoil) temp += optimal;
if (type == Tile::Oxisol) temp += poorly;
if (type == Tile::Gleysol) temp += rarely;
rangePenalty(temperature, 61, 80, temp);
rangePenalty(humidity, 33, 58, temp);
if (temp > threshold) {
             threshold = temp;
             plant = Plant::OliveTree;
     }
}

if (rand() / (float) RAND_MAX < berryShrubChance) {
// Berry Shrubs
temp = 0;
if (type == Tile::Podzol) temp += good;
if (type == Tile::LoamSoil) temp += optimal;
if (type == Tile::PeatSoil) temp += great;
if (type == Tile::SandySoil) temp += good;
if (type == Tile::ClaySoil) temp += poorly;
if (type == Tile::SiltySoil) temp += great;
if (type == Tile::RockySoil) temp += rarely;
if (type == Tile::AridSoil) temp += rarely;
if (type == Tile::Oxisol) temp += poorly;
if (type == Tile::Gleysol) temp += good;
rangePenalty(temperature, 61, 75, temp);
rangePenalty(humidity, 65, 90, temp);
if (temp > threshold) {
             threshold = temp;
             int ran = rint(0,3);
             if (ran == 0) plant = Plant::BlueberryShrub;
             if (ran == 1) plant = Plant::StrawberryShrub;
         }
}
if (rand() / (float) RAND_MAX < grapevineChance) {
// Grapevines
temp = 0;
if (type == Tile::Podzol) temp += rarely;
if (type == Tile::LoamSoil) temp += optimal;
if (type == Tile::PeatSoil) temp += good;
if (type == Tile::SandySoil) temp += great;
if (type == Tile::ClaySoil) temp += poorly;
if (type == Tile::SiltySoil) temp += great;
if (type == Tile::RockySoil) temp += good;
if (type == Tile::AridSoil) temp += good;
if (type == Tile::Oxisol) temp += poorly;
if (type == Tile::Gleysol) temp += rarely;
rangePenalty(temperature, 61, 80, temp);
rangePenalty(humidity, 45, 68, temp);
if (temp > threshold) {
             threshold = temp;
             plant = Plant::Grapevine;
       }
}
if (rand() / (float) RAND_MAX < grainChance) {
//GRAINS
// Wheat
temp = 0;
if (type == Tile::Podzol) temp += poorly;
if (type == Tile::LoamSoil) temp += optimal;
if (type == Tile::PeatSoil) temp += good;
if (type == Tile::SandySoil) temp += good;
if (type == Tile::ClaySoil) temp += good;
if (type == Tile::SiltySoil) temp += good;
if (type == Tile::RockySoil) temp += poorly;
if (type == Tile::AridSoil) temp += poorly;
if (type == Tile::Oxisol) temp += poorly;
if (type == Tile::Gleysol) temp += rarely;

rangePenalty(temperature, 58, 75, temp);
rangePenalty(humidity, 45, 70, temp);

if (temp > threshold) {
    threshold = temp;
    plant = Plant::Wheat;
}

// Rice
temp = 0;
if (type == Tile::Podzol) temp += poorly;
if (type == Tile::LoamSoil) temp += good;
if (type == Tile::PeatSoil) temp += great;
if (type == Tile::SandySoil) temp += poorly;
if (type == Tile::ClaySoil) temp += optimal;
if (type == Tile::SiltySoil) temp += optimal;
if (type == Tile::RockySoil) temp += poorly;
if (type == Tile::AridSoil) temp += poorly;
if (type == Tile::Oxisol) temp += poorly;
if (type == Tile::Gleysol) temp += great;

rangePenalty(temperature, 75, 92, temp);
rangePenalty(humidity, 75, 100, temp);
if (temp > threshold) {
    threshold = temp;
    plant = Plant::Rice;
}
// Oat
temp = 0;
if (type == Tile::Podzol) temp += rarely;
if (type == Tile::LoamSoil) temp += optimal;
if (type == Tile::PeatSoil) temp += good;
if (type == Tile::SandySoil) temp += great;
if (type == Tile::ClaySoil) temp += poorly;
if (type == Tile::SiltySoil) temp += good;
if (type == Tile::RockySoil) temp += good;
if (type == Tile::AridSoil) temp += good;
if (type == Tile::Oxisol) temp += poorly;
if (type == Tile::Gleysol) temp += rarely;

rangePenalty(temperature, 61, 80, temp);
rangePenalty(humidity, 45, 68, temp);

if (temp > threshold) {
    threshold = temp;
    plant = Plant::Oat;
}
}

// VEGETABLES
if (rand() / (float) RAND_MAX < leafyChance) {
temp = 0;
// Leafy Vegetables
if (type == Tile::Podzol) temp += good;
if (type == Tile::LoamSoil) temp += optimal;
if (type == Tile::PeatSoil) temp += great;
if (type == Tile::SandySoil) temp += poorly;
if (type == Tile::ClaySoil) temp += good;
if (type == Tile::SiltySoil) temp += optimal;
if (type == Tile::RockySoil) temp += rarely;
if (type == Tile::AridSoil) temp += rarely;
if (type == Tile::Oxisol) temp += poorly;
if (type == Tile::Gleysol) temp += great;
rangePenalty(temperature, 50, 72, temp);
rangePenalty(humidity, 65, 88, temp);
if (temp > threshold) {
             threshold = temp;
             int ran = rint(0,1);
             if (ran == 0) plant = Plant::Lettuce;
             if (ran == 1) plant = Plant::Kale;
       }
}
if (rand() / (float) RAND_MAX < rootChance) {
    temp = 0;
    // Root Vegetables
if (type == Tile::Podzol) temp += good;
if (type == Tile::LoamSoil) temp += optimal;
if (type == Tile::PeatSoil) temp += poorly;
if (type == Tile::SandySoil) temp += great;
if (type == Tile::ClaySoil) temp += poorly;
if (type == Tile::SiltySoil) temp += good;
if (type == Tile::RockySoil) temp += rarely;
if (type == Tile::AridSoil) temp += rarely;
if (type == Tile::Oxisol) temp += poorly;
if (type == Tile::Gleysol) temp += rarely;
rangePenalty(temperature, 56, 69, temp);
rangePenalty(humidity, 55, 78, temp);
if (temp > threshold) {
             threshold = temp;
             int ran = rint(0,1);
             if (ran == 0) plant = Plant::Carrot;
             if (ran == 1) plant = Plant::Beets;
       }
}
if (rand() / (float) RAND_MAX < tuberChance) {
    temp = 0;
// Tubers
if (type == Tile::Podzol) temp += good;
if (type == Tile::LoamSoil) temp += great;
if (type == Tile::PeatSoil) temp += poorly;
if (type == Tile::SandySoil) temp += optimal;
if (type == Tile::ClaySoil) temp += poorly;
if (type == Tile::SiltySoil) temp += good;
if (type == Tile::RockySoil) temp += rarely;
if (type == Tile::AridSoil) temp += rarely;
if (type == Tile::Oxisol) temp += poorly;
if (type == Tile::Gleysol) temp += rarely;
rangePenalty(temperature, 60, 67, temp);
rangePenalty(humidity, 65, 88, temp);
if (temp > threshold) {
             threshold = temp;
             plant = Plant::Potatoes;
       }
}
if (rand() / (float) RAND_MAX < bulbChance) {
    // Bulbs
if (type == Tile::Podzol) temp += good;
if (type == Tile::LoamSoil) temp += optimal;
if (type == Tile::PeatSoil) temp += poorly;
if (type == Tile::SandySoil) temp += great;
if (type == Tile::ClaySoil) temp += poorly;
if (type == Tile::SiltySoil) temp += good;
if (type == Tile::RockySoil) temp += rarely;
if (type == Tile::AridSoil) temp += rarely;
if (type == Tile::Oxisol) temp += poorly;
if (type == Tile::Gleysol) temp += rarely;
rangePenalty(temperature, 60, 70, temp);
rangePenalty(humidity, 55, 77, temp);
if (temp > threshold) {
             threshold = temp;
             int ran = rint(0,1);
             if (ran == 0) plant = Plant::Onion;
             if (ran == 1) plant = Plant::Garlic;
       }
}
if (rand() / (float) RAND_MAX < floweringChance) {
    // Flowering Vegetables
if (type == Tile::Podzol) temp += good;
if (type == Tile::LoamSoil) temp += optimal;
if (type == Tile::PeatSoil) temp += poorly;
if (type == Tile::SandySoil) temp += good;
if (type == Tile::ClaySoil) temp += poorly;
if (type == Tile::SiltySoil) temp += great;
if (type == Tile::RockySoil) temp += rarely;
if (type == Tile::AridSoil) temp += rarely;
if (type == Tile::Oxisol) temp += poorly;
if (type == Tile::Gleysol) temp += rarely;
rangePenalty(temperature, 56, 67, temp);
rangePenalty(humidity, 65, 88, temp);
if (temp > threshold) {
             threshold = temp;
             int ran = rint(0,1);
             if (ran == 0) plant = Plant::Cabbage;
             if (ran == 1) plant = Plant::Broccoli;
       }
}
if (rand() / (float) RAND_MAX < fruitVeggieChance) {
   // Fruit Vegetables
if (type == Tile::Podzol) temp += good;
if (type == Tile::LoamSoil) temp += optimal;
if (type == Tile::PeatSoil) temp += poorly;
if (type == Tile::SandySoil) temp += great;
if (type == Tile::ClaySoil) temp += poorly;
if (type == Tile::SiltySoil) temp += good;
if (type == Tile::RockySoil) temp += rarely;
if (type == Tile::AridSoil) temp += rarely;
if (type == Tile::Oxisol) temp += poorly;
if (type == Tile::Gleysol) temp += rarely;
rangePenalty(temperature, 69, 81, temp);
rangePenalty(humidity, 55, 78, temp);
if (temp > threshold) {
             threshold = temp;
             int ran = rint(0,2);
             if (ran == 0) plant = Plant::Tomato;
             if (ran == 1) plant = Plant::Cucumber;
             if (ran == 2) plant = Plant::Pepper;
       }
}

// // Seed and Pod Vegetables
// if (type == Tile::Podzol) temp += good;
// if (type == Tile::LoamSoil) temp += optimal;
// if (type == Tile::PeatSoil) temp += poorly;
// if (type == Tile::SandySoil) temp += great;
// if (type == Tile::ClaySoil) temp += poorly;
// if (type == Tile::SiltySoil) temp += good;
// if (type == Tile::RockySoil) temp += rarely;
// if (type == Tile::AridSoil) temp += rarely;
// if (type == Tile::Oxisol) temp += poorly;
// if (type == Tile::Gleysol) temp += rarely;
// rangePenalty(temperature, 56, 70, temp);
// rangePenalty(humidity, 55, 78, temp);
// if (temp > threshold) {
//              threshold = temp;
//              int ran = rint(0,2);
//              if (ran == 0) plant = Plant::Peas;
//              if (ran == 1) plant = Plant::Beans;
//        }

// HERBS
if (rand() / (float) RAND_MAX < herbChance) {
// Sun-Loving Herbs
if (type == Tile::Podzol) temp += poorly;
if (type == Tile::LoamSoil) temp += optimal;
if (type == Tile::PeatSoil) temp += poorly;
if (type == Tile::SandySoil) temp += great;
if (type == Tile::ClaySoil) temp += poorly;
if (type == Tile::SiltySoil) temp += good;
if (type == Tile::RockySoil) temp += rarely;
if (type == Tile::AridSoil) temp += rarely;
if (type == Tile::Oxisol) temp += poorly;
rangePenalty(temperature, 70, 90, temp);
rangePenalty(humidity, 40, 60, temp);
if (temp > threshold) {
             threshold = temp;
             int ran = rint(0,2);
             if (ran == 0) plant = Plant::Woad;
             if (ran == 1) plant = Plant::Indigo;
             if (ran == 2) plant = Plant::Poppy;
       }
// Shade-Loving Herbs
if (type == Tile::Podzol) temp += good;
if (type == Tile::LoamSoil) temp += optimal;
if (type == Tile::PeatSoil) temp += great;
if (type == Tile::SandySoil) temp += poorly;
if (type == Tile::ClaySoil) temp += good;
if (type == Tile::SiltySoil) temp += good;
if (type == Tile::RockySoil) temp += rarely;
if (type == Tile::AridSoil) temp += rarely;
if (type == Tile::Oxisol) temp += poorly;
rangePenalty(temperature, 50, 70, temp);
rangePenalty(humidity, 60, 80, temp);
if (temp > threshold) {
             threshold = temp;
             int ran = rint(0,1);
             if (ran == 0) plant = Plant::Hemp;
             if (ran == 1) plant = Plant::Ginseng;
       }
// Drought-Tolerant Herbs (Low Water Requirements)
if (type == Tile::Podzol) temp += poorly;
if (type == Tile::LoamSoil) temp += optimal;
if (type == Tile::PeatSoil) temp += poorly;
if (type == Tile::SandySoil) temp += great;
if (type == Tile::ClaySoil) temp += poorly;
if (type == Tile::SiltySoil) temp += good;
if (type == Tile::RockySoil) temp += rarely;
if (type == Tile::AridSoil) temp += great;
if (type == Tile::Oxisol) temp += poorly;
rangePenalty(temperature, 70, 100, temp);
rangePenalty(humidity, 20, 40, temp);
if (temp > threshold) {
             threshold = temp;
             int ran = rint(0,2);
             if (ran == 0) plant = Plant::Lavendar;
             if (ran == 1) plant = Plant::Sage;
             if (ran == 2) plant = Plant::Madder;
       }
// Moisture-Loving Herbs
if (type == Tile::Podzol) temp += great;
if (type == Tile::LoamSoil) temp += optimal;
if (type == Tile::PeatSoil) temp += great;
if (type == Tile::SandySoil) temp += poorly;
if (type == Tile::ClaySoil) temp += good;
if (type == Tile::SiltySoil) temp += great;
if (type == Tile::RockySoil) temp += rarely;
if (type == Tile::AridSoil) temp += poorly;
if (type == Tile::Oxisol) temp += poorly;
rangePenalty(temperature, 60, 80, temp);
rangePenalty(humidity, 60, 80, temp);
if (temp > threshold) {
             threshold = temp;
             plant = Plant::Mint;
       }
// Cold-Hardy Herbs (Cold-Tolerant)
if (type == Tile::Podzol) temp += great;
if (type == Tile::LoamSoil) temp += optimal;
if (type == Tile::PeatSoil) temp += good;
if (type == Tile::SandySoil) temp += poorly;
if (type == Tile::ClaySoil) temp += good;
if (type == Tile::SiltySoil) temp += good;
if (type == Tile::RockySoil) temp += rarely;
if (type == Tile::AridSoil) temp += rarely;
if (type == Tile::Oxisol) temp += poorly;
rangePenalty(temperature, 40, 60, temp);
rangePenalty(humidity, 40, 60, temp);
if (temp > threshold) {
             threshold = temp;
             plant = Plant::Thyme;
       }
}
//TEXTILE
if (rand() / (float) RAND_MAX < textileChance) {
    temp = 0;
if (type == Tile::Podzol) temp += poorly;
if (type == Tile::LoamSoil) temp += optimal;
if (type == Tile::PeatSoil) temp += poorly;
if (type == Tile::SandySoil) temp += great;
if (type == Tile::ClaySoil) temp += poorly;
if (type == Tile::SiltySoil) temp += good;
if (type == Tile::RockySoil) temp += rarely;
if (type == Tile::AridSoil) temp += rarely;
if (type == Tile::Oxisol) temp += poorly;
rangePenalty(temperature, 60, 79, temp);
rangePenalty(humidity, 55, 78, temp);
if (temp > threshold) {
             threshold = temp;
             int ran = rint(0,2);
             if (ran == 0) plant = Plant::Cotton;
             if (ran == 1) plant = Plant::Hemp;
             if (ran == 2) plant = Plant::Flax;
       }
}
if (rand() / (float) RAND_MAX < fernChance) {
    temp = 0;
// Ferns
if (biome == 4) temp += 0.3;
if (biome == 5) temp += 0.2;
if (biome == 6) temp += 0.2;
if (biome == 7) temp += 0.3;
if (biome == 8) temp += 0.2;
if (type == Tile::Podzol) temp += great;
if (type == Tile::LoamSoil) temp += optimal;
if (type == Tile::PeatSoil) temp += optimal;
if (type == Tile::SandySoil) temp += poorly;
if (type == Tile::ClaySoil) temp += rarely;
if (type == Tile::SiltySoil) temp += great;
if (type == Tile::RockySoil) temp += rarely;
if (type == Tile::AridSoil) temp = 0;
if (type == Tile::Oxisol) temp += poorly;
if (type == Tile::Gleysol) temp += great;
rangePenalty(temperature,50,77,temp);
         rangePenalty(humidity,75,115,temp);
if (temp > threshold) {
             threshold = temp;
             plant = Plant::Fern;
         }
}
if (rand() / (float) RAND_MAX < reedChance) {
    temp = 0;
//Reeds
if (biome == 4) temp += 0.15;
if (adjCheck(tileIndex, tileType, (int)tile.first, (int)tile.second, Tile::ShallowWater, 1)) temp += 0.45;
if (type == Tile::Podzol)        temp += good;
if (type == Tile::LoamSoil)      temp += great;
if (type == Tile::PeatSoil)      temp += optimal;
if (type == Tile::SandySoil)     temp += poorly;
if (type == Tile::ClaySoil)      temp += good;
if (type == Tile::SiltySoil)     temp += great;
if (type == Tile::RockySoil)     temp += poorly;
if (type == Tile::AridSoil)      temp = 0;
if (type == Tile::Oxisol)        temp += poorly;
if (type == Tile::Gleysol)       temp += optimal;
rangePenalty(temperature,50,86,temp);
         rangePenalty(humidity,75,120,temp);
if (temp > threshold) {
             threshold = temp;
             plant = Plant::Reed;
        }
}
} // end of plants, checking random value against plant coverage
// GRASSES
if (rand() / (float) RAND_MAX < grassCoverage) {
    temp = 0;
    threshold = 0;
// Prairie Grasses
temp += 0.2;
temp -= (0.05 * adjCheckListCount(tileIndex, tilePlant, (int)tile.first, (int)tile.second, trees, 3));
if (biome == 2) temp += 0.45;
if (biome == 4) temp += 0.05;
if (type == Tile::Podzol) temp += good;
if (type == Tile::LoamSoil) temp += optimal;
if (type == Tile::PeatSoil) temp += rarely;
if (type == Tile::SandySoil) temp += great;
if (type == Tile::ClaySoil) temp += poorly;
if (type == Tile::SiltySoil) temp += optimal;
if (type == Tile::RockySoil) temp += rarely;
if (type == Tile::AridSoil) temp += good;
if (type == Tile::Oxisol) temp += poorly;
if (type == Tile::Gleysol) temp += poorly;
 rangePenalty(temperature,41,86,temp);
 rangePenalty(humidity,30,80,temp);
if (temp > threshold) {
             threshold = temp;
             grass = Grass::Grass;
         }
// Savannah Grasses
    temp = 0;
temp += 0.2;
temp -= (0.05 * adjCheckListCount(tileIndex, tilePlant, (int)tile.first, (int)tile.second, trees, 3));
if (biome == 3) temp += 0.5;
if (type == Tile::Podzol) temp += poorly;
if (type == Tile::LoamSoil) temp += great;
if (type == Tile::PeatSoil) temp += rarely;
if (type == Tile::SandySoil) temp += optimal;
if (type == Tile::ClaySoil) temp += good;
if (type == Tile::SiltySoil) temp += great;
if (type == Tile::RockySoil) temp += rarely;
if (type == Tile::AridSoil) temp += good;
if (type == Tile::Oxisol) temp += good;
if (type == Tile::Gleysol) temp += poorly;
rangePenalty(temperature,64,95,temp);
rangePenalty(humidity,20,60,temp);

if (temp > threshold) {
             threshold = temp;
             grass = Grass::SavannahGrass;
         }
}
tileGrass[i] = grass;
tileObject[i] = plant;
PlantType type = plants[(int)plant].plantType;
//plant permanent
switch(type) {
    case PlantType::Root:
    case PlantType::Tuber:
    case PlantType::Bulb:
       seeds.push_back(plant);
       seedCoords.push_back(tile);
}
//TODO: randomly generate growth stage of plant
float multiplier = rfloat(0.001,0.998);
plantCoords.push_back(tile);
growthAmt.push_back(multiplier * plants[(int)plant].fullyGrownAmt);

//TESTING
// Tile tt = tileType[i];
// Plant pt = tilePlant[i];
// Grass gt = tileGrass[i];
// cout << "coords: " << (int)tile.first << "," << (int)tile.second <<  " biome: " << biome << " tile: " << static_cast<int>(tt) << " plant: " << static_cast<int>(pt) << " grass: " << static_cast<int>(gt) << ";";
 }
}



void spawnEnemies() {

}

void spawnDisasters() {

}
