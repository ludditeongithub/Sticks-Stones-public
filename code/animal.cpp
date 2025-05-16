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


void buildAnimalTree() {
	animalTree.buildIndex();
}


void layEgg(Animal animal) {

}

int findBreedingPartner(std::vector<float> queryPoint) {
	 const size_t numResults = 10;
     uint32_t retIndex[numResults]; // nearest neighbor index
     float outDistSqr[numResults]; //distance between nn and current
	animalTree.knnSearch(&queryPoint[0], numResults, &retIndex[0], &outDistSqr[0]);
	bool found = false;
	for (int i = 0; i < numResults; i++) {
		//if animal is male
		if (animalSex[retIndex[0]]) {
			return i;
		}
	}
	return -1; //not found
}

void pregnancy(int animalIndex) {	pregnantAnimalIndex.push_back(animalIndex);
	//TODO: finish pregnancy timings for all animals
	switch(animals[animalIndex]) {
		case Animal::Cow:
			pregnantAnimalTimer.push_back()
	}
}

void breed(int animalIndex) {
	vector<float> coords = { (float) animalCoords[animalIndex].first, (float) animalCoords[animalIndex].second};
	int partnerIndex = findBreedingPartner(coords);
	meet(animalCoords[animalIndex],animalCoords[partnerIndex]);
	//TODO: trigger breeding animation
	pregnancy(animalIndex);
}

// for every animal, trigger breeding if female, interpret and some chance is met, not currently processing offspring
void setInitialBreedEvent(int i) {
		if (animalSex[i]) continue;
		if (isPregant[i]) continue;
		//TODO: get times for how often breeding triggers.
		switch (animals[i]) {
			// EGG LAYERS

			 addEvent();

			// NON-EGG LAYERS

		}
}

void animalBirth(int animalIndex) {
// TODO: perhaps include age lowering fertility later
std::pair<int,int> dest = animalCoords(animalIndex);
findNearestAdjacentEmptyTile(dest);
// after birth, add event for next breeding in the future
addEvent();
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
		 //just wander until on grass tile
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
		 moveTo(true, dest);
		 //TODO: consume plant
			}
	}
	 	addEvent(feedingTime, EventType::PreyFeed, animalType, animalIndex);
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
	int feedingTime;
	bool predator;
	for (int i = 0; i < predators.size(); i++) {
		if (animal == predator[i]) predator = true;
	}
	if (!predator)addEvent(feedingTime, EventType::PreyFeed, animalType, animalIndex);
	else addEvent(feedingTime, EventType::PredatorFeed, animalType, animalIndex);
}


// for every predator, hunt prey if hunger is below certain value


// for every herbavore, search for plants if hunger is below certain value
