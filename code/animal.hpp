#ifndef ANIMAL_H_
#define ANIMAL_H_

#include "basic.hpp"
#include "categories.hpp"

std::stack<uint16_t> nextAnimalIndex;

using  animalIndices = std::unordered_map<std::pair<uint16_t, uint16_t>, int>; //TODO: update animalIndices on movement
vector<Animal> animals;
vector<std::pair<uint16_t, uint16_t>> animalCoords;
vector<Direction> animalDirection;
vector<bool> animalSex; //m = true, f = false
vector<uint16_t> animalHealth;
vector<uint16_t> animalHunger;

enum class MovingStatus {
Idle,
Wander,
Prowl, // looking for targets, but don't know where
Flee,
//PursuitX means sprinting to visible target
Pursuit,
AnimalPursuit,
// ApproachX means walking to known/visible target
ApproachPlant,
ApproachGrass,
ReturnHome,
};

enum class MatingStatus {
Idle,
Searching,
Pregnant, // equivalent of fertilized for egg layers
Infertile
};

vector<MovingStatus> animalMovingStatus;
vector<MatingStatus> animalMatingStatus;

//TODO: specify herbivore diets and	nutrition values
Plant diet[] = {Plant::Fern, Plant::Moss, Plant::Reed, Plant::Wheat, Plant::Oat, Plant::Rice, Plant::BlueberryShrub, Plant::StrawberryShrub, Plant::Grapvine, Plant::Lettuce, Plant::Kale, Plant::Corn, Plant::Carrot, Plant::Beets, Plant::Potato, Plant::Onion, Plant::Garlic, Plant::Cabbage, Plant::Broccoli, Plant::Tomato, Plant::Cucumber, Plant::Pepper, Plant::Peas, Plant::Beans, Plant::Cotton, Plant::Hemp, Plant::Flax, Plant::Woad, Plant::Madder, Plant::Indigo, Plant::Lavendar, Plant::Mint, Plant::Thyme, Plant::Sage, Plant::Ginseng, Plant::Poppy, Plant::Cocoa, Plant::Senna, Plant::Saffron};

Animal predatorDiet[2];

void initializeDiets() {
predatorDiet[Animal::Wolf] = {Animal::Rabbit, Animal::Sheep, Animal::Pig, Animal::Goat, Animal::Chicken, Animal::Duck, Animal::Antelope, Animal::Deer, Animal::Caribou, Animal::Capybara};
predatorDiet[Animal::Bear] = {Animal::Rabbit, Animal::Sheep, Animal::Pig, Animal::Goat, Animal::Chicken, Animal::Duck, Animal::Antelope, Animal::Deer, Animal::Caribou, Animal::Capybara, Animal::Fish, Animal::Donkey};
}

enum class Diet {
Herbivore, Omnivore, Carnivore, Scavenger
};



int sightRanges[static_cast<int>(Animal::MAX)];
int minSpeeds[static_cast<int>(Animal::MAX)];
int midSpeeds[static_cast<int>(Animal::MAX)];
int maxSpeeds[static_cast<int>(Animal::MAX)];

void initializeAnimalData() {
    sightRanges[static_cast<int>(Animal::Pig)];
    minSpeeds[static_cast<int>(Animal::Pig)];
    midSpeeds[static_cast<int>(Animal::Pig)];
    maxSpeeds[static_cast<int>(Animal::Pig)];
    sightRanges[static_cast<int>(Animal::Cow)];
    minSpeeds[static_cast<int>(Animal::Cow)];
    midSpeeds[static_cast<int>(Animal::Cow)];
    maxSpeeds[static_cast<int>(Animal::Cow)];
    sightRanges[static_cast<int>(Animal::Chicken)];
    minSpeeds[static_cast<int>(Animal::Chicken)];
    midSpeeds[static_cast<int>(Animal::Chicken)];
    maxSpeeds[static_cast<int>(Animal::Chicken)];
    sightRanges[static_cast<int>(Animal::Duck)];
    minSpeeds[static_cast<int>(Animal::Duck)];
    midSpeeds[static_cast<int>(Animal::Duck)];
    maxSpeeds[static_cast<int>(Animal::Duck)];
    sightRanges[static_cast<int>(Animal::Sheep)];
    minSpeeds[static_cast<int>(Animal::Sheep)];
    midSpeeds[static_cast<int>(Animal::Sheep)];
    maxSpeeds[static_cast<int>(Animal::Sheep)];
    sightRanges[static_cast<int>(Animal::Goat)];
    minSpeeds[static_cast<int>(Animal::Goat)];
    midSpeeds[static_cast<int>(Animal::Goat)];
    maxSpeeds[static_cast<int>(Animal::Goat)];
    sightRanges[static_cast<int>(Animal::Horse)];
    minSpeeds[static_cast<int>(Animal::Horse)];
    midSpeeds[static_cast<int>(Animal::Horse)];
    maxSpeeds[static_cast<int>(Animal::Horse)];
    sightRanges[static_cast<int>(Animal::Ox)];
    minSpeeds[static_cast<int>(Animal::Ox)];
    midSpeeds[static_cast<int>(Animal::Ox)];
    maxSpeeds[static_cast<int>(Animal::Ox)];
    sightRanges[static_cast<int>(Animal::Donkey)];
    minSpeeds[static_cast<int>(Animal::Donkey)];
    midSpeeds[static_cast<int>(Animal::Donkey)];
    maxSpeeds[static_cast<int>(Animal::Donkey)];
    sightRanges[static_cast<int>(Animal::Camel)];
    minSpeeds[static_cast<int>(Animal::Camel)];
    midSpeeds[static_cast<int>(Animal::Camel)];
    maxSpeeds[static_cast<int>(Animal::Camel)];
    sightRanges[static_cast<int>(Animal::WaterBuffalo)];
    minSpeeds[static_cast<int>(Animal::WaterBuffalo)];
    midSpeeds[static_cast<int>(Animal::WaterBuffalo)];
    maxSpeeds[static_cast<int>(Animal::WaterBuffalo)];
    sightRanges[static_cast<int>(Animal::Rabbit)];
    minSpeeds[static_cast<int>(Animal::Rabbit)];
    midSpeeds[static_cast<int>(Animal::Rabbit)];
    maxSpeeds[static_cast<int>(Animal::Rabbit)];
    sightRanges[static_cast<int>(Animal::Antelope)];
    minSpeeds[static_cast<int>(Animal::Antelope)];
    midSpeeds[static_cast<int>(Animal::Antelope)];
    maxSpeeds[static_cast<int>(Animal::Antelope)];
    sightRanges[static_cast<int>(Animal::Deer)];
    minSpeeds[static_cast<int>(Animal::Deer)];
    midSpeeds[static_cast<int>(Animal::Deer)];
    maxSpeeds[static_cast<int>(Animal::Deer)];
    sightRanges[static_cast<int>(Animal::Moose)];
    minSpeeds[static_cast<int>(Animal::Moose)];
    midSpeeds[static_cast<int>(Animal::Moose)];
    maxSpeeds[static_cast<int>(Animal::Moose)];
    sightRanges[static_cast<int>(Animal::Capybara)];
    minSpeeds[static_cast<int>(Animal::Capybara)];
    midSpeeds[static_cast<int>(Animal::Capybara)];
    maxSpeeds[static_cast<int>(Animal::Capybara)];
    sightRanges[static_cast<int>(Animal::Turtle)];
    minSpeeds[static_cast<int>(Animal::Turtle)];
    midSpeeds[static_cast<int>(Animal::Turtle)];
    maxSpeeds[static_cast<int>(Animal::Turtle)];
    sightRanges[static_cast<int>(Animal::Elephant)];
    minSpeeds[static_cast<int>(Animal::Elephant)];
    midSpeeds[static_cast<int>(Animal::Elephant)];
    maxSpeeds[static_cast<int>(Animal::Elephant)];
    sightRanges[static_cast<int>(Animal::Bison)];
    minSpeeds[static_cast<int>(Animal::Bison)];
    midSpeeds[static_cast<int>(Animal::Bison)];
    maxSpeeds[static_cast<int>(Animal::Bison)];
    sightRanges[static_cast<int>(Animal::Wolf)];
    minSpeeds[static_cast<int>(Animal::Wolf)];
    midSpeeds[static_cast<int>(Animal::Wolf)];
    maxSpeeds[static_cast<int>(Animal::Wolf)];
    sightRanges[static_cast<int>(Animal::Bear)];
    minSpeeds[static_cast<int>(Animal::Bear)];
    midSpeeds[static_cast<int>(Animal::Bear)];
    maxSpeeds[static_cast<int>(Animal::Bear)];
    sightRanges[static_cast<int>(Animal::Caribou)];
    minSpeeds[static_cast<int>(Animal::Caribou)];
    midSpeeds[static_cast<int>(Animal::Caribou)];
    maxSpeeds[static_cast<int>(Animal::Caribou)];
    sightRanges[static_cast<int>(Animal::Fish)];
    minSpeeds[static_cast<int>(Animal::Fish)];
    midSpeeds[static_cast<int>(Animal::Fish)];
    maxSpeeds[static_cast<int>(Animal::Fish)];

}



#endif // ANIMAL_H_
