#ifndef ANIMAL_H_
#define ANIMAL_H_

#include "basic.hpp"
#include "categories.hpp"
#include "unit.hpp"

std::stack<uint16_t> nextAnimalIndex;

unordered_map<std::pair<uint16_t, uint16_t>, int> animalIndices;
vector<Animal> animals;
vector<std::pair<uint16_t, uint16_t>> animalCoords;
vector<bool> animalSex; //m = true, f = false
vector<uint16_t> animalHealth;
vector<uint16_t> animalHunger;
vector<MovingStatus> animalMovingStatus;

struct AnimalData {
    Animal type;
    uint16_t health;
    uint16_t hunger;
    uint16_t damage;
};

enum class MovingStatus {
Sleeping,
Idle,
Wander,
ProwlUp,
ProwlDown,
ProwlLeft,
ProwlRight,
Flee,
Pursuit
};

enum class MatingStatus {
Idle,
Searching,
Pregnant, // equivalent of fertilized for egg layers
Infertile
};


//TODO: specify herbivore diets and	nutrition values
Plant diet[] = {Plant::Fern, Plant::Moss, Plant::Reed, Plant::Wheat, Plant::Oat, Plant::Rice, Plant::BlueberryShrub, Plant::StrawberryShrub, Plant::Grapvine, Plant::Lettuce, Plant::Kale, Plant::Corn, Plant::Carrot, Plant::Beets, Plant::Potato, Plant::Onion, Plant::Garlic, Plant::Cabbage, Plant::Broccoli, Plant::Tomato, Plant::Cucumber, Plant::Pepper, Plant::Peas, Plant::Beans, Plant::Cotton, Plant::Hemp, Plant::Flax, Plant::Woad, Plant::Madder, Plant::Indigo, Plant::Lavendar, Plant::Mint, Plant::Thyme, Plant::Sage, Plant::Ginseng, Plant::Poppy, Plant::Cocoa, Plant::Senna, Plant::Saffron};

predatorDiet[Animal::Wolf] = {Animal::Rabbit, Animal::Sheep, Animal::Pig, Animal::Goat, Animal::Chicken, Animal::Duck, Animal::Antelope, Animal::Deer, Animal::Caribou, Animal::Capybara};
predatorDiet[Animal::Bear] = {Animal::Rabbit, Animal::Sheep, Animal::Pig, Animal::Goat, Animal::Chicken, Animal::Duck, Animal::Antelope, Animal::Deer, Animal::Caribou, Animal::Capybara, Animal::Fish, Animal::Donkey};

#endif // ANIMAL_H_
