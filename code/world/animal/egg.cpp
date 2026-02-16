#include "core/data.hpp"

void layEgg(Coord coords, int index, Animal animal, bool fertilized) {
	switch (animal) {
		case Animal::Duck:
			Object object = Scavengeable::DuckEgg;
			break;
		case Animal::Chicken:
			Object object = Scavengeable::ChickenEgg;
			break;
		case Animal::Turtle:
                        Object object = Scavengeable::TurtleEgg;
		  break;
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
