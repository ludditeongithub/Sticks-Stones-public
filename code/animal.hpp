#ifndef ANIMAL_H_
#define ANIMAL_H_

#include "basic.hpp"
#include "categories.hpp"
#include "unit.hpp"

vector<Animal> animals;
vector<bool> animalSex; //m = true, f = false
vector<pair<int,int>> animalCoords;
vector<int> animalHealth;
vector<int> animalHunger;
vector<int> pregnantAnimalIndex;
vector<pair<float,float>> nearestAnimal;

#endif // ANIMAL_H_
