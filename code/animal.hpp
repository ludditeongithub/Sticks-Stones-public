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

enum class MatingStatus {
Idle,
Searching,
Pregnant, // equivalent of fertilized for egg layers
Infertile
}

vector<MatingStatus> animalMatingStatus;

vector<pair<float,float>> nearestAnimal;

//TODO: specify herbivore diets and	nutrition values
Plant diet[] = {Plant::Fern, Plant::Moss, Plant::Reed, Plant::Wheat, Plant::Oat, Plant::Rice, Plant::BlueberryShrub, Plant::StrawberryShrub, Plant::Grapvine, Plant::Lettuce, Plant::Kale, Plant::Corn, Plant::Carrot, Plant::Beets, Plant::Potato, Plant::Onion, Plant::Garlic, Plant::Cabbage, Plant::Broccoli, Plant::Tomato, Plant::Cucumber, Plant::Pepper, Plant::Peas, Plant::Beans, Plant::Cotton, Plant::Hemp, Plant::Flax, Plant::Woad, Plant::Madder, Plant::Indigo, Plant::Lavendar, Plant::Mint, Plant::Thyme, Plant::Sage, Plant::Ginseng, Plant::Poppy, Plant::Cocoa, Plant::Senna, Plant::Saffron};

#endif // ANIMAL_H_
