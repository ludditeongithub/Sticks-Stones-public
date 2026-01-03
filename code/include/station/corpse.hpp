
#ifndef CORPSE_H_
#define CORPSE_H_

#include "basic.hpp"
#include "categories.hpp"

std::stack<uint16_t> nextCorpseIndex;
vector<Station> corpses;
vector<uint8_t> stagesLeft;
vector<uint16_t> timeTillRot;

Station animalToCorpse[static_cast<int>(Animal::MAX)];
uint8_t corpseStages[static_cast<int>(Animal::MAX)];
int corpseRottingTime = 12400;

void initializeAnimalData() {
animalToCorpse[static_cast<int>(Animal::Pig)] =
corpseStages[static_cast<int>(Animal::Pig)] =
animalToCorpse[static_cast<int>(Animal::Cow)] =
corpseStages[static_cast<int>(Animal::Cow)] =
animalToCorpse[static_cast<int>(Animal::Chicken)] =
corpseStages[static_cast<int>(Animal::Chicken)] =
animalToCorpse[static_cast<int>(Animal::Duck)] =
corpseStages[static_cast<int>(Animal::Duck)] =
animalToCorpse[static_cast<int>(Animal::Sheep)] =
corpseStages[static_cast<int>(Animal::Sheep)] =
animalToCorpse[static_cast<int>(Animal::Goat)] =
corpseStages[static_cast<int>(Animal::Goat)] =
animalToCorpse[static_cast<int>(Animal::Horse)] =
corpseStages[static_cast<int>(Animal::Horse)] =
animalToCorpse[static_cast<int>(Animal::Ox)] =
corpseStages[static_cast<int>(Animal::Ox)] =
animalToCorpse[static_cast<int>(Animal::Donkey)] =
corpseStages[static_cast<int>(Animal::Donkey)] =
animalToCorpse[static_cast<int>(Animal::Camel)] =
corpseStages[static_cast<int>(Animal::Camel)] =
animalToCorpse[static_cast<int>(Animal::WaterBuffalo)] =
corpseStages[static_cast<int>(Animal::WaterBuffalo)] =
animalToCorpse[static_cast<int>(Animal::Rabbit)] =
corpseStages[static_cast<int>(Animal::Rabbit)] =
animalToCorpse[static_cast<int>(Animal::Antelope)] =
corpseStages[static_cast<int>(Animal::Antelope)] =
animalToCorpse[static_cast<int>(Animal::Deer)] =
corpseStages[static_cast<int>(Animal::Deer)] =
animalToCorpse[static_cast<int>(Animal::Moose)] =
corpseStages[static_cast<int>(Animal::Moose)] =
animalToCorpse[static_cast<int>(Animal::Capybara)] =
corpseStages[static_cast<int>(Animal::Capybara)] =
animalToCorpse[static_cast<int>(Animal::Turtle)] =
corpseStages[static_cast<int>(Animal::Turtle)] =
animalToCorpse[static_cast<int>(Animal::Elephant)] =
corpseStages[static_cast<int>(Animal::Elephant)] =
animalToCorpse[static_cast<int>(Animal::Bison)] =
corpseStages[static_cast<int>(Animal::Bison)] =
animalToCorpse[static_cast<int>(Animal::Wolf)] =
corpseStages[static_cast<int>(Animal::Wolf)] =
animalToCorpse[static_cast<int>(Animal::Bear)] =
corpseStages[static_cast<int>(Animal::Bear)] =
animalToCorpse[static_cast<int>(Animal::Caribou)] =
corpseStages[static_cast<int>(Animal::Caribou)] =
animalToCorpse[static_cast<int>(Animal::Fish)] =
corpseStages[static_cast<int>(Animal::Fish)] =
}


void addCorpse(Animal animal) {
    if (nextCorpseIndex.size() != 0) {
        uint16_t index = nextCorpseIndex.top();
        nextCorpseIndex.pop();
        corpses[index] = animalToCorpse[static_cast<int>(animal)];
        stagesLeft[index] =
    } else {
        corpses.push_back(animalToCorpse[static_cast<int>(animal)]);
        stagesLeft.push_back(corpseStages[static_cast<int>(animal)]);
        timeTillRot.push_back(corpseRottingTime);
    }

}

#endif // CORPSE_H_
