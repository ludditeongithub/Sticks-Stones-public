#include "animal.hpp"

//build nearest search tree
	SeedCloud animalCloud;
        using my_kd_tree_t = nanoflann::KDTreeSingleIndexAdaptor<
	nanoflann::L2_Simple_Adaptor<float, SeedCloud>,
            SeedCloud, /* Our dataset */
            2 /* 2D space */
            >;
void sortAnimals() {
	nearestAnimal.clear();
	for (int i = 0; i < animalCoords.size(); i++) {
		nearestAnimal.push_back(animalCoords[i]);
	}
	animalCloud.seeds = nearestAnimal;
}

  my_kd_tree_t animalTree(2 /*dim*/, animalCloud, {10} /* max leaf size */);

int getFruitHunger(Fruit fruit) {
	switch (fruit) {
		case Fruit::Apple:
			return 360;
		case Fruit::Orange:
			return 340;
		case Fruit::Pear:
			return 320;
		case Fruit::Peach:
			return 300;
		case Fruit::Plum:
			return 180;
		case Fruit::Apricot:
			return 160;
		case Fruit::Cherry:
			return 100;
		case Fruit::Blueberry:
			return 200;
		case Fruit::Strawberry:
			return 120;
		case Fruit::Grape:
			return 240;
		case Fruit::Lemon:
			return 20;
		case Fruit::Lime:
			return 20;
	}
}

//TODO: large corpses can be only partially eaten, and remain with the hunger points not consumed until they rot
int getCorpseHunger(Station corpse) {
	switch (corpse) {
		case Station::PigCorpse:
			return 19500;
		case Station::CowCorpse:
			return 40500;
		case Station::ChickenCorpse:
			return 800;
		case Station::DuckCorpse:
			return 1000;
		case Station::SheepCorpse:
			return 10000;
		case Station::GoatCorpse:
			return 8500;
		case Station::OxCorpse:
			return 700000;
		case Station::HorseCorpse:
			return 32500;
		case Station::DonkeyCorpse:
			return 9500;
		case Station::CamelCorpse:
			return 26500;
		case Station::WaterBuffaloCorpse:
			return 38000;
		case Station::RabbitCorpse:
			return 500;
		case Station::AntelopeCorpse:
			return 15000;
		case Station::DeerCorpse:
			return 16000;
		case Station::MooseCorpse:
			return 49000;
		case Station::CapybaraCorpse:
			return 6400;
		case Station::ElephantCorpse:
			return 650000;
		case Station::BisonCorpse:
			return 85000;
		case Station::WolfCorpse:
			return 5500;
		case Station::BearCorpse:
			return 65000;
		case Station::CaribouCorpse:
			return 22500;
	default:
			return 0;
	}
}

int getMeatAmount(Corpse corpse) {
	switch (corpse) {
		case Station::PigCorpse:
			return 98;
		case Station::CowCorpse:
			return 260;
		case Station::ChickenCorpse:
			return 7;
		case Station::DuckCorpse:
			return 5;
		case Station::SheepCorpse:
			return 36;
		case Station::GoatCorpse:
			return 32;
		case Station::OxCorpse:
			return 312;
		case Station::HorseCorpse:
			return 242;
		case Station::DonkeyCorpse:
			return 162;
		case Station::CamelCorpse:
			return 308;
		case Station::WaterBuffaloCorpse:
			return 320;
		case Station::RabbitCorpse:
			return 3;
		case Station::AntelopeCorpse:
			return 43;
		case Station::DeerCorpse:
			return 39;
		case Station::MooseCorpse:
			return 412;
		case Station::CapybaraCorpse:
			return 28;
		case Station::ElephantCorpse:
			return 1280;
		case Station::BisonCorpse:
			return 350;
		case Station::WolfCorpse:
			return 12;
		case Station::BearCorpse:
			return 580;
		case Station::CaribouCorpse:
			return 65;
	default:
			return 0;
}

int getPlantHunger(Plant plant) {
	case Plant::Fern: return 1;
case Plant::Moss: return 0;
case Plant::Reed: return 4;
case Plant::Wheat: return 4;
case Plant::Oat: return 5;
case Plant::Rice: return 4;
case Plant::Bush: return 3;
case Plant::Papyrus: return 4;
case Plant::PioneerTree: return 4;
case Plant::DeciduousTree: return 7;
case Plant::EvergreenTree: return 5;
case Plant::TropicalTree: return 8;
case Plant::OrangeTree: return 6;
case Plant::LemonTree: return 6;
case Plant::LimeTree: return 6;
case Plant::PeachTree: return 6;
case Plant::PlumTree: return 6;
case Plant::CherryTree: return 6;
case Plant::ApricotTree: return 6;
case Plant::Cactus: return 6;
case Plant::AppleTree: return 7;
case Plant::PearTree: return 6;
case Plant::OliveTree: return 5;
case Plant::BlueberryShrub: return 4;
case Plant::StrawberryShrub: return 4;
case Plant::Grapevine: return 6;
case Plant::Lettuce: return 3;
case Plant::Kale: return 3;
case Plant::Corn: return 6;
case Plant::Carrot: return 4;
case Plant::Beets: return 4;
case Plant::Potato: return 5;
case Plant::Onion: return 3;
case Plant::Garlic: return 3;
case Plant::Cabbage: return 4;
case Plant::Broccoli: return 4;
case Plant::Tomato: return 3;
case Plant::Cucumber: return 3;
case Plant::Pepper: return 3;
case Plant::Peas: return 4;
case Plant::Beans: return 4;
case Plant::Cotton: return 2;
case Plant::Hemp: return 2;
case Plant::Flax: return 2;
case Plant::Woad: return 1;
case Plant::Madder: return 1;
case Plant::Indigo: return 1;
case Plant::Lavendar: return 1;
case Plant::Mint: return 4;
case Plant::Thyme: return 3;
case Plant::Sage: return 3;
case Plant::Ginseng: return 1;
case Plant::Poppy: return 2;
case Plant::Cocoa: return 4;
case Plant::Senna: return 1;
case Plant::Saffron: return 0;
return 0;
}

void eatGrass(int entityIndex, int tileIndex {
	//entityIndex can be enum class conversion to item, or tile index
	animalHunger[entityIndex] += grassHunger;
	//TODO: cut grass between long and short
	tileGrass[tileIndex] = Grass::NONE;
}

void eatFruit(int entityIndex, int fruitTypeIndex, int tileIndex) {
	//entityIndex can be enum class conversion to item, or tile index
	animalHunger[entityIndex] += getFruitHunger(static_cast<Fruit>(fruitTypeIndex));
	tileObjectAmt[tileIndex] -= 1;
	if (tileObjectAmt[tileIndex] == 0) = Fruit::NONE;
}

void eatPlant(int entityIndex, int plantIndex, int tileIndex) {
	//entityIndex can be enum class conversion to item, or tile index
	animalHunger[entityIndex] += getPlantHunger(static_cast<Plant>(plants[plantIndex]));
	plants[plantIndex] = NONE;
}



// in ticks
int calculateTimeTillFeed(int hungerAmount, Animal animal) {
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
	rbool() ? animalSex.push_back(true) : animalSex.push_back(false);
	animalCoords.push_back(tileCoords[coordIndex]);
	animalHealth.push_back(getFullAnimalHealth(animal));
	animalHunger.push_back(getFullAnimalHunger(animal));
	//spawn new graphic here
}


void layEgg(Animal animal, int animalIndex) {
	std::pair<int, int> animalCoord = animalCoords[animalIndex];
	int index = tileIndices(animalCoords);
	bool fertilized;
	//TODO: make variable hatching times for each egg
	animalMatingStatus[animalIndex] == MatingStatus::Pregnant ?	addEvent(12400, EventType::Hatch, static_cast<int>(animal), animalIndex);
	switch (animal) {
		case Animal::Chicken:
			tileObject[index] =	Scavengeable::ChickenEgg;
			break;
		case Animal::Duck:
			tileObject[index] =	Scavengeable::DuckEgg;
			break;
		case Animal::Turtle:
			tileObject[index] =	Scavengeable::TurtleEgg;
			break;
	}
}

void hatchEgg(Animal animal, int coordIndex) {
	spawnAnimal(animal, coordIndex);
	tileObject[index] = Scavengeable::NONE;
}

int findBreedingPartnerIndex(int animalIndex, Animal animal) {
	std::vector<float> queryPoint = { (float) animalCoords[animalIndex].first, (float) animalCoords[animalIndex].second};
		bool found = false;
		size_t numResults = 5;
		lastSearch = 0;
	while (!found) {
     uint32_t retIndex[numResults]; // nearest neighbor index
     float outDistSqr[numResults]; //distance between nn and current
	animalTree.knnSearch(&queryPoint[0], numResults, &retIndex[0], &outDistSqr[0]);
	for (int i = lastSearch; i < numResults; i++) {
		//if animal is male, same species, and not searching for mate already
		if (animals[retIndex[i]] == animal && animalSex[retIndex[i]] && !(animalMatingStatus[retIndex[i]] == MatingStatus::Searching)) return i;
	}
	if (numResults < 20) {
		lastSearch = numResults;
		numResults *= 2;
	}
	}
	return -1; //not found
}

// doubles as carrying fertile egg for egg layers
void pregnancy(int animalIndex) {
	animalMatingStatus[animalIndex] = MatingStatus::Pregnant;
	//event which adds timer when hen becomes unfertilized and needs to mate again
	if (eggLayer(animals[animalIndex])) {
		//TODO: change values based on animal
		addEvent(40300, EventType::NotFertilized, 0, animalIndex);
		return;
	}
	//TODO: finish pregnancy timings for all animals
	switch(animals[animalIndex]) {
		default:
			pregnantAnimalTimer.push_back(160000);
	}
}

void setUnfertilized(int animalIndex) {
	animalMatingStatus[animalIndex] = MatingStatus::Idle;
}

bool eggLayer(Animal animal) {
	switch (animal) {
		case Animal::Duck:
		case Animal::Chicken:
		case Animal::Turtle:
			return true;
	}
	return false;
}

//animalIndex is female, but the male partner is who goes on path to find female
void breed(Animal animal, int animalIndex) {
		int partnerIndex = findBreedingPartnerIndex(animalIndex, animal);
		if (partnerIndex == -1) return;
		if (eggLayer(animalIndex)) {
			//egg lays on a schedule regardless, this randomizes interest of male
			meet(partnerIndex, animalIndex, true, true, MeetEvent::EggBreeding);
		}
		else meet(partnerIndex, animalIndex, true, true, MeetEvent::Breeding);
}

// for every animal, trigger breeding if female, interpret and some chance is met, not currently processing offspring
void setInitialBreedEvent(int i) {
	if (animalSex[i]) continue;
	if (isPregant[i]) continue;
		//TODO: get times for how often breeding triggers.
		switch (animals[i]) {
			default:
				addEvent(30000, EventType::AnimalBreeding, static_cast<int>(animals[i]), i);
		}
}

void animalBirth(Animal animal, int animalIndex) {
// TODO: perhaps include age lowering fertility later
std::pair<int,int> dest = animalCoords(animalIndex);
int animalSize = getAnimalSize(animal);
//TODO: make non-index versions of all pathfinding algos
TileBlock tb = getNearestAdjacentTileBlock(tileIndices[dest], animalSize * 2 - 1);
dest = tb.startTile;
moveAnimal(animalIndex, tileIndices[dest]);
// after birth, add event for next breeding in the future
addEvent(getBreedingTime(animal), EventType::AnimalBreeding, static_cast<int>(animals[animalIndex]), animalIndex);
}

void preyFeed(int animalIndex) {
	Animal feeder = animals(animalIndex);
	 bool grassEater = false;
	 for (int i = 0; i < grassEaters.size(); i++) {
		 if (feeder == grassEaters[i]) {
			 grassEater = true;
		 }
	 }
	 if (grassEater) {
		 moveAnimal(animalIndex, getNearestAdjacentEmptyTileIndex(tileIndices[animalCoords[animalIndex]]), DelayedEvent::EatGrass);
	 } else {
		 size_t numResults = 8;
		 	while (animalHunger[animalIndex] < hungerThreshold) {
				bool found = false;
		 int start = 0;
		 while (!found) {
			 uint32_t retIndex[numResults]; // nearest neighbor index
		 float outDistSqr[numResults]; //distance between nn and current
		 std::vector<float> coords = {(float)animalCoords[animalIndex].first, (float)animalCoords[animalIndex].second}
		 plants.knnSearch(coords, numResults, &retIndex[0], &outDistSqr[0]);
		 std::pair<int,int> dest;
		 for (int i = start; i < numResults; i++) {
			 for (int j = 0; j < diet.size(); j++) {
				 if (plants[retIndex[i]] == diet[j]) {
					 found = true;
					 dest = plantCoords[retIndex];
				 }
			 }
		 }
		 if (!found) {
			 start = numResults;
			 numResults *= 2;
		 }
	 }
		 //TODO: consume plant
		 moveAnimal(animalIndex, tileIndices[dest], DelayedEvent::EatPlant);
		}
	}
	 //calculate next feeding time and send as future event
	 	addEvent(calculateTimeTillFeed(animalHunger[animalIndex], feeder), EventType::PreyFeed, static_cast<int>(feeder), animalIndex);
}

//TODO: if outDistSqr not required, do not do it
void predatorFeed(int animalIndex) {
	 Animal predator = animals(animalIndex);
	 size_t numResults = 8;
	 int preyIndex;

	while (animalHunger[animalIndex] < hungerThreshold) {
		uint32_t retIndex[numResults]; // nearest neighbor index
     float outDistSqr[numResults]; //distance between nn and current
		std::vector<float> coords = {(float)animalCoords[animalIndex].first, (float)animalCoords[animalIndex].second};
		animalTree.knnSearch(coords, numResults, &retIndex[0], &outDistSqr[0]);
		bool found = false;
		int start = 0;
		while (!found) {
			for (int i = start; i < numResults; i++) {
			switch (predator) {
				case Animal::Wolf:
					for (int j = 0; j < wolfDiet.size(); j++) {
						if (animals(retIndex[i]) == wolfDiet[j]) {
							preyIndex = retIndex[i];
							found = true;
						}
					}
					break;
				case Animal::Bear:
					for (int j = 0; j < bearDiet.size(); j++) {
						if (animals(retIndex[i]) == bearDiet[j]) {
							preyIndex = retIndex[i];
							found = true;
						}
					}
					break;
			}
		}
			if (!found) {
				start = numResults;
				numResults *= 2;
				}
		}
		meet(animalIndex, true, preyIndex, true);
		//TODO: hunting
	}
	addEvent(feedingTime, EventType::PredatorFeed, animalType, animalIndex);
}

void setInitialFeedingTime(int animalIndex) {
	Animal animal = animals(animalIndex);
	//calculate feeding time
	bool predator;
	for (int i = 0; i < predators.size(); i++) {
		if (animal == predator[i]) predator = true;
	}
	if (!predator)addEvent(feedingTime, EventType::PreyFeed, animalType, animalIndex);
	else addEvent(feedingTime, EventType::PredatorFeed, animalType, animalIndex);
}


// for every predator, hunt prey if hunger is below certain value


// for every herbavore, search for plants if hunger is below certain value
