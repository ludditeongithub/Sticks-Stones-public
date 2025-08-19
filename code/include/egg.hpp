#ifndef EGG_H_
#define EGG_H_

#include "basic.hpp"
#include "categories.hpp"

std::stack<int> nextEggIndex;
vector<std::pair<int,int>> eggCoords;
uint16_t hatchTime[static_cast<int>(Scavengeable::EGGMAX)];

void initializeHatchTimes() {
    hatchTime[static_cast<int>(Scavengeable::DuckEgg)] = 43320;
    hatchTime[static_cast<int>(Scavengeable::ChickenEgg)] = 28830;
    hatchTime[static_cast<int>(Scavengeable::TurtleEgg)] = 65400;
}

#endif // EGG_H_
