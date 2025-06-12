#include "objectInteractions.h"
//PICK UPS
void

//FOR equipping necessary tools
void takeTool(int pawnIndex, std::pair<int,int> coord) {
    if (isTool(tileObject[tileIndices[coord]])) {
        Tool tool = tileObject[tileIndices[coord]];
        tools[pawnIndex].push_back(tool);
        tileObject[tileIndices[coord]] = Item::NONE;
        deleteObject(tool, coord.first, coord.second);
    }
}

void harvestPlant(int pawnIndex, std::pair<int,int> coord) {
    int tileIndex = tileIndices[coord];
    if (std::get_if<Plant>(&tileObject[tileIndex])) {
        Plant plant = tileObject[tileIndex];
        Item item = plantToItem[static_cast<int>(plant)];
        if (viableHarvest(plantIndicesFromTileIndices[tileIndex]) && checkActionRequisites(resources[static_cast<int>(item)], pawnIndex)) {
            addEvent(resources[static_cast<int>(item)].time, EventType::HarvestComplete, tileIndex, resources[static_cast<int>(item)].amounts);
        } else findNecessaryTools(getActionRole(pawnIndex), pawnIndex);
    }
}

//TODO: decide how to check whether if there are items of the same type in there, and combine instead of push back
void finishHarvestPlant(int pawnIndex, int tileIndex) {
    //NOTE: static cast here
    fullAddItem(pawnIndex, static_cast<Item>(tileObject[tileIndex]), resources[static_cast<int>(tileObject[tileIndex])].amounts);
    tileObject[tileIndex] = Plant::NONE;
    movingStatus[pawnIndex] = MovingStatus::Decide;
}

void collectFruit(int pawnIndex, std::pair<int,int> coord) {
    if (std::get_if<FruitObject>(&tileObject[tileIndices[coord]])) {
        Fruit fruit = tileObject[tileIndices[coord]].fruit;
        Item item = fruitToItem[static_cast<int>(fruit)];
        addEvent(resources[static_cast<int>(item)].time, EventType::FruitCollect, tileIndex, tileObject[tileIndices[coord]].amounts);
    }
}

void finishCollectFruit(int pawnIndex, int tileIndex, uint8_t amount) {
    fullAddItem(pawnIndex, static_cast<Item>(tileObject[tileIndex]), amount);
    tileObject[tileIndex] = Plant::NONE;
    movingStatus[pawnIndex] = MovingStatus::Decide;
}

void chopTree(int pawnIndex) {

}

//EATING

void eatCorpse(int animalIndex) {

}

void finishEatCorpse() {

}

void eatPlant(int animalIndex, int plantIndex) {
    Plant& plant = plants[plantIndex];
    animalHunger[animalIndex] -= plantHunger[plant];
    animalMovingStatus[animalIndex] = MovingStatus::Idle;
    //TODO
    addEvent(plantEatTime[plant], EventType::EatPlant, animalIndex, plantIndex);
}

void finishEatPlant() {

}

//ATTACKING

// true if killed, false if not. sets attacker's dest to corpse's index if true.
bool attack(int attackerIndex, int targetIndex, bool hunterAnimal, bool targetAnimal) {
    if (hunterAnimal) {
        animalHealth[targetIndex] -= getDamage[animals[attackerIndex]].damage;
    } else {
        if (targetAnimal) {
            animalHealth[targetIndex] -= getDamage[damage[attackerIndex]].damage;
            if (animalHealth[targetIndex] <= 0) {
                int corpseIndex = animalDeath(targetIndex);
                currentDest[attackerIndex] = corpseIndex;
                return true;
            }
            else return false;
        } else {
            health[targetIndex] -= getDamage[damage[attackerIndex]].damage;
        }
    }
}
