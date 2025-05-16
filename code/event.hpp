#ifndef EVENT_H_
#define EVENT_H_
#include "basic.hpp"
#include "categories.hpp"
#include "unit.cpp"
#include "animal.cpp"

enum class EventType {
	TaskComplete,
	ProductComplete,
	SleepComplete,
	PreyFeed,
	HerbivoreFeed,
	PredatorFeed,
	PlantDeath,
	AnimalBreeding,
	Conception,
	AnimalDeath,
	UnitDeath,
	AnimalBirth,
	Birth,
};

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

void eventInterpreter(Event event) {
	switch(event.eventType) {
		case::EventType::ProductComplete:
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
}

//main game loop for events
void click() {

}

#endif // EVENT_H_
