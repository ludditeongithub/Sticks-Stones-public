#include "animal.hpp"


void AnimalDatabase::eatGrass(int index, int tileIndex, TileDatabase &tdb) {
	//objectIndex can be enum class conversion to item, or tile index
    uint16_t maxGrassFill = calcGrassHungerFill(grassLength[tileIndex]);
    uint16_t maxHunger = calcMaxHunger(index);
    uint16_t hungerTillMax = maxHunger - hunger[index];
    uint16_t grassDemanded = calcGrassLengthForHungerFill(hungerTillMax);
    hunger[index] = min(maxHunger, hunger[index] + maxGrassFill);
    tdb.cutGrass(tileIndex, );
	//TODO: cut grass between long and short
	renderTile(tileIndex);
}

void AnimalDatabase::eatFruit(int index, int fruitTypeIndex, int tileIndex) {
	//objectIndex can be enum class conversion to item, or tile index
  hunger[index] = min(hunger[index] + fruitHungerFill[static_cast<Fruit>(fruitTypeIndex)], maxHunger[animal]);
	tileObjectAmt[tileIndex] -= 1;
	if (tileObjectAmt[tileIndex] == 0) tileObject[tileIndex] = Fruit::NONE;
}

void AnimalDatabase::eatPlant(int index, int tileIndex) {
	//objectIndex can be enum class conversion to item, or tile index
        Plant& plant = tileIndexToPlantIndex[tileIndex];
	
	hunger[objectIndex] = min(hunger[index] + plantHungerFill[static_cast<Fruit>(fruitTypeIndex)], maxHunger[animal]);
	//TODO: make it affect the object database	
}

// in ticks
int AnimalDatabase::calculateTimeTillFeed(int hungerAmount, Animal animal) {
	float maxHunger;
	float tickBurnRate;
	int timeTillFeed;
	switch (animal) {
		case Animal::Pig:
			maxHunger = 9000;
			burnRate = 1.3;
		case Animal::Cow:
			maxHunger = 20000;
			burnRate = 1.6;
		case Animal::Chicken:
			maxHunger = 400;
			burnRate = 0.08;
		case Animal::Duck:
			maxHunger = 500;
			burnRate = 0.09;
		case Animal::Sheep:
			maxHunger = 5000;
			burnRate = 0.7;
		case Animal::Goat:
			maxHunger = 4500;
			burnRate = 0.6;
		case Animal::Horse:
			maxHunger = 16000;
			burnRate = 1.8;
		case Animal::Ox:
			maxHunger = 25000;
			burnRate = 2.2;
		case Animal::Donkey:
			maxHunger = 10000;
			burnRate = 1.3;
		case Animal::Camel:
			maxHunger = 18000;
			burnRate = 1.6;
		case Animal::WaterBuffalo:
			maxHunger = 22000;
			burnRate = 2.0;
		case Animal::Rabbit:
			maxHunger = 300;
			burnRate = 0.09;
		case Animal::Antelope:
			maxHunger = 4500;
			burnRate = 0.7;
		case Animal::Deer:
			maxHunger = 6600;
			burnRate = 0.9;
		case Animal::Moose:
			maxHunger = 18000;
			burnRate = 1.6;
		case Animal::Capybara:
			maxHunger = 3500;
			burnRate = 0.4;
		case Animal::Turtle:
			maxHunger = 250;
			burnRate = 0.02;
		case Animal::Elephant:
			maxHunger = 120000;
			burnRate = 5.0;
		case Animal::Bison:
			maxHunger = 22000;
			burnRate = 2.0;
		case Animal::Wolf:
			maxHunger = 3000;
			burnRate = 0.4;
		case Animal::Bear:
			maxHunger = 12000;
			burnRate = 1.3;
		case Animal::Caribou:
			maxHunger = 8500;
			burnRate = 1.3;
		case Animal::Fish:
			maxHunger = 600;
			burnRate = 0.05;
}
	int feedingThreshold = maxHunger / 2;
	if (hungerAmount < feedingThreshold) return 0;
	else return static_cast<int>((hungerAmount - feedingThreshold) / burnRate);
}

void buildAnimalTree() {
	animalTree.buildIndex();
}

void spawnAnimal(Animal animal, int coordIndex) {
	animals.push_back(animal);
	rbool() ? sex.push_back(true) : sex.push_back(false);
	coords.push_back(tileCoords[coordIndex]);
	health.push_back(getFullAnimalHealth(animal));
	hunger.push_back(getFullAnimalHunger(animal));
	//spawn new graphic here
}

void addEgg(std::pair<int,int> coords, int index, Animal animal, bool fertilized) {
	switch (animal) {
		case Animal::Duck:
			Object object = Scavengeable::DuckEgg;
			break;
		case Animal::Chicken:
			Object object = Scavengeable::ChickenEgg;
			break;
		case Animal::Turtle:
			Object object = Scavengeable::TurtleEgg;
	}
	insertObject(object, coords.first, coords.second, index);
	if (fertilized) {
		if (nextEggIndex.size() != 0) {
		int eggIndex = nextEggIndex.pop();
		eggCoords[eggIndex] = getNearestEmptyTile(index);
		} else {
			eggCoords.push_back(getNearestEmptyTile(index));
			int eggIndex = eggCoords.size();
		}
		addEvent(hatchTime[static_cast<int>(object)], EventType::Hatch, eggIndex);
	}
}

void AnimalDatabase::animalHunt(Direction direction, Animal animal, int animalIndex) {
		//NOTE: random here, maybe simplify
	if (rint(0, 10)	< 9) {

		 //TODO: if time == night and has Tool torch, currentSight = x
		 std::pair<int,int>	gt = getMoveTimeAndTileIndex(direction);
		addEvent(gt.second, EventType::AnimalMoveTile, animalIndex, gt.first);
		huntCheck(predatorDiet[animal], animalIndex, currentSight, direction, true);
	}
}

void AnimalDatabase::animalHunt(Direction direction, Animal animal, int animalIndex) {
	while (bool found = false) {
		Direction goDirection = direction;
		//NOTE: random here, maybe simplify
	if (rint(0, 20)	< 19) goDirection = getRandomAdjDirection(direction);
		 //TODO: if time == night and has Tool torch, currentSight = x
		 std::pair<int,int>	gt = getMoveTimeAndTileIndex(goDirection);
		addEvent(gt.second, EventType::AnimalMoveTile, animalIndex, gt.first);
		huntCheck(predatorDiet[animal], animalIndex, currentSight, goDirection, true);
		if (movingStatus[pawnIndex] == MovingStatus::Pursuit) return;
		if (movingStatus[pawnIndex] == MovingStatus::Idle) return;
	}
}


//animalIndex is female, but the male partner is who goes on path to find female
/void AnimalDatabase::breed(int maleIndex, int femaleIndex) {
// 		if (eggLayer(animals[femaleIndex])) {
// 			//egg lays on a schedule regardless, this randomizes interest of male
// 			meet(maleIndex, femaleIndex, true, true, MeetEvent::EggBreeding);
// 		}
// 		else meet(maleIndex, femaleIndex, true, true, MeetEvent::Breeding);
// }

// for every animal, trigger breeding if female, interpret and some chance is met, not currently processing offspring
void AnimalDatabase::setInitialBreedEvent(int i) {
	if (sex[i]) continue;
	if (isPregant[i]) continue;
		//TODO: get times for how often breeding triggers.
		switch (animals[i]) {
			default:
				addEvent(30000, EventType::AnimalBreeding, static_cast<int>(animals[i]), i);
		}
}
 
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

void AnimalDatabase::preparePreyFeed(int animalIndex) {
	addEvent(calculateTimeTillFeed(hunger[animalIndex] + futureConsumption, feeder), EventType::PreyFeed, static_cast<int>(feeder), animalIndex);
}

//TODO: if outDistSqr not required, do not do it
void AnimalDatabase::preparePredatorFeed(int animalIndex) {

	addEvent(calculateTimeTillFeed(hunger[animalIndex] + futureConsumption, feeder), EventType::PredatorFeed, animalType, animalIndex);
}
 
void AnimalDatabase::setInitialFeedingTime(int animalIndex) {
	Animal animal = animals(animalIndex);
	//calculate feeding time
	bool predator;
	for (int i = 0; i < predators.size(); i++) {
		if (animal == predator[i]) predator = true;
	}
	if (!predator)addEvent(feedingTime, EventType::PreyFeed, animalType, animalIndex);
	else addEvent(feedingTime, EventType::PredatorFeed, animalType, animalIndex);
}

//TODO: migratin
void suitableEnvironmentCheck() {

}


// for every predator, hunt prey if hunger is below certain value


// for every herbavore, search for plants if hunger is below certain value
