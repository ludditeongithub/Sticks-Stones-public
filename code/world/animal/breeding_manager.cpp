#include "breeding_manager.hpp"

void AnimalDatabase::birthAnimal(Animal animal, int animalIndex) {
// TODO: perhaps include age lowering fertility later
std::pair<int,int> dest = coords(animalIndex);
int animalSize = getAnimalSize(animal);
//TODO: make non-index versions of all pathfinding algos
TileBlock tb = getNearestAdjacentTileBlock(tileIndices[dest], animalSize * 2 - 1);
dest = tb.startTile;
moveAnimal(animalIndex, tileIndices[dest]);
// after birth, add event for next breeding in the future
//TODO: consider sleeping
addAnimal(animal, dest.first, dest.second);
addEvent(getBreedingTime(animal), EventType::AnimalBreeding, static_cast<int>(animals[animalIndex]), animalIndex);
 }
