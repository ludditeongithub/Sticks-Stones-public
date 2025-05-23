#ifndef EVENT_H_
#define EVENT_H_
#include "basic.hpp"
#include "categories.hpp"
#include "unit.cpp"
#include "animal.cpp"

enum class EventType {
    PawnMoveTile,
	AnimalMoveTile,
	TaskComplete,
	ProductComplete,
	SleepComplete,
	CheckIfAdjacentPawns,
	CheckIfAdjacentAnimals,
	CheckIfAdjacentPawnToAnimal,
	CheckIfAdjacentAnimalToPawn,
	PreyFeed,
	HerbivoreFeed,
	PredatorFeed,
	EatGrass,
	FutureSeedDropping,
	FutureSeedDroppingFruit,
	PlantGermination, //plant,
	PlantDeath,
	AnimalBreeding,
	Conception,
	NotFertilized,
	TreeDeath,
	AnimalDeath,
	UnitDeath,
	AnimalBirth,
	Hatch,
	Birth,
};

enum class DelayedEvent {
    Breeding,
	Hunting,
}

struct Event {
	uint64_t time;
	EventType eventType;
	int typeIndex; //index which converts to the enum class that is the main entity in the event in question
	int entitiesIndex; //index of the vector that stores the entities of the type in question
	int secondaryIndex; //if there is a secondary entity this converts to its enum class
};

std::vector<Event> upcomingEvents;

void addEvent(uint64_t time, EventType type, int typeIndex, int entitiesIndex) {
	upcomingEvents.push_back({time, type, typeIndex, entitiesIndex});
}

void addEvent(uint64_t time, EventType type, int typeIndex, int entitiesIndex, int secondaryIndex) {
	upcomingEvents.push_back({time, type, typeIndex, entitiesIndex, secondaryIndex});
}

void meetEventInterpreter(int event, int finderIndex, int targetIndex, bool finderAnimal, bool targetAnimal) {
	MeetEvent me = static_cast<MeetEvent>(event);
	switch (me) {
		case MeetEvent::Breeding:
			//TODO: breeding animation, pregnancy chance based on age instead of guranteed
			pregnancy(targetIndex);
		case MeetEvent::Hunting:
	}
}

//TODO: if things begin to lag, optimize this to O log n or O1 using jump table
void eventInterpreter(Event event) {
	switch(event.eventType) {
		case EventType::AnimalMoveTile:
			animalCoords[event.typeIndex] =	tileIndices[event.entitiesIndex];
			break;
		case EventType::PawnMoveTile:
			currentCoords[event.typeIndex] = tileIndices[event.entitiesIndex];
			break;
		case EventType::ProductComplete:
			Item product = static_cast<Item>(event.typeIndex);
			if (eventTypeIndex < static_cast<int>(Item::VARIANTSMAX)) {
		inventories[event.entitiesIndex].variantItems.push_back(product);
		inventories[event.entitiesIndex].variantItemTypes.push_back(event.secondaryIndex);
		occupied[pawn] = false;
			} else inventories[event.entitiesIndex].items.push_back(product);
	//TODO: add case for tools
			break;
	case EventType::AnimalBreeding:
		//TODO: maybe change this to type index
		breed(event.entitiesIndex);
		break;
	break;
	case EventType::AnimalBirth:
		animalBirth(event.entitiesIndex);
		break;
	case EventType::PreyFeed:
		preyFeed(event.entitiesIndex);
		break;
	case EventType::PredatorFeed:
		predatorFeed(event.entitiesIndex);
		break;
	case EventType::Birth:
		birth(event.entitiesIndex);
		break;
	case EventType::PlantDeath:
		cropDeath(event.entitiesIndex);
		break;
	case EventType::TreeDeath:
		treeDeath(event.entitiesIndex);
		break;
		//TODO: before this, check to see that the parameters are right
	case EventType::CheckIfAdjacentAnimals
		if (adjCheckEntity(event.entitiesIndex, event.secondaryIndex, true, true)) {
			meetEventInterpreter(event.typeIndex);
		} else meet(event.entitiesIndex, event.secondaryIndex, true, true, static_cast<DelayedEvent>(event.typeIndex));
		break;
	case EventType::CheckIfAdjacentAnimalToPawn:
		if (adjCheckEntity(event.entitiesIndex, event.secondaryIndex, true, false)) {
			meetEventInterpreter(event.typeIndex);
		} else meet(event.entitiesIndex, event.secondaryIndex, true, false, static_cast<DelayedEvent>(event.typeIndex));
		break;
	case EventType::CheckIfAdjacentPawnToAnimal:
		if (adjCheckEntity(event.entitiesIndex, event.secondaryIndex, false, true)) {
			meetEventInterpreter(event.typeIndex);
		} else meet(event.entitiesIndex, event.secondaryIndex, false, true, static_cast<DelayedEvent>(event.typeIndex));
		break;
	case EventType::CheckIfAdjacentPawns:
		if (adjCheckEntity(event.entitiesIndex, event.secondaryIndex, false, false)) {
			meetEventInterpreter(event.typeIndex);
		} else meet(event.entitiesIndex, event.secondaryIndex, false, false, static_cast<DelayedEvent>(event.typeIndex));
		break;
	case EventType::NotFertilized:
		setUnfertilized(event.entitiesIndex);
		break;
	case EventType::Lay:
		layEgg(static_cast<Animal>(event.typeIndex), event.entitiesIndex);
		break;
	case EventType::Hatch:
		hatchEgg(static_cast<Animal>(event.typeIndex), event.entitiesIndex);
	case EventType::Breed:
		breed(static_cast<Animal>(event.typeIndex),	event.entitiesIndex);
		break;
	case EventType::AnimalBirth:
		animalBirth(static_cast<Animal>(event.typeIndex),event.entitiesIndex);
		break;
	case EventType::EatGrass:
		animalConsume(event.typeIndex, event.entitiesIndex); //animal index, grass tile index
		break;
	case EventType::EatPlant:
		eatPlant(event.typeIndex, event.entitiesIndex);  //animal index, plant tile index
		break;
}

//main game loop for events
void click() {

}

#endif // EVENT_H_
