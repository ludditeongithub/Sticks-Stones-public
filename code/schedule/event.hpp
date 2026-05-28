#ifndef EVENT_H_
#define EVENT_H_
#include <vector>

#include <core/data.hpp>
#include <systems/work_operations.hpp>

enum class EventType
{
	PawnMoveTile,
	AnimalMoveTile,
	ProductComplete,
	ResourceComplete,
	WakeUp,
	PreyFeed,
	HerbivoreFeed,
	PredatorFeed,
	EatGrass,
	FutureSeedDropping,
	FutureSeedDroppingFruit,
	PlantGermination, // plant,
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

enum class DelayedEvent
{
	Breeding,
	Hunting,
	Combat,
};

enum class ProwlAction
{
	Hunt,
	Breed,
};

struct Event
{
	Time time;
	EventType eventType;
	int typeIndex; // index which converts to the enum class that is the main object in the
		       // event in question
	int entitiesIndex;  // index of the vector that stores the entities of the type in question
	int secondaryIndex; // if there is a secondary object this converts to its enum class
};

std::vector<Event> upcomingEvents;

void addEvent(Time time, EventType type, int typeIndex, int entitiesIndex)
{
	upcomingEvents.push_back({time, type, typeIndex, entitiesIndex});
}

void addEvent(Time time, EventType type, int typeIndex, int entitiesIndex, int secondaryIndex)
{
	upcomingEvents.push_back({time, type, typeIndex, entitiesIndex, secondaryIndex});
}

// TODO: if things begin to lag, optimize this to O log n or O1 using jump table
void eventInterpreter(Event event)
{
	switch (event.eventType)
	{
	case EventType::AnimalMoveTile:
		animalCoords[event.typeIndex] = tileIndices[event.entitiesIndex];
		break;
	case EventType::PawnMoveTile:
		currentCoords[event.typeIndex] = tileIndices[event.entitiesIndex];
		break;
	case EventType::ProductComplete:
		Item product = static_cast<Item>(event.typeIndex);
		if (eventTypeIndex < static_cast<int>(Item::VARIANTSMAX))
		{
			inventories[event.entitiesIndex].variantItems.push_back(product);
			inventories[event.entitiesIndex].variantItemTypes.push_back(
			    event.secondaryIndex);
			occupied[pawn] = false;
		}
		else
			inventories[event.entitiesIndex].items.push_back(product);
		// TODO: add case for tools
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
		// TODO: before this, check to see that the parameters are right
	case EventType::ProductComplete:
		productFinish(event.typeIndex, event.entitiesIndex, event.secondaryIndex);
		decidePawnTask(event.entitiesIndex);
		break;
	case EventType::WakeUp:
		setMovingStatus(event.entitiesIndex);
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
		breed(static_cast<Animal>(event.typeIndex), event.entitiesIndex);
		break;
	case EventType::AnimalBirth:
		animalBirth(static_cast<Animal>(event.typeIndex), event.entitiesIndex);
		break;
	case EventType::EatGrass:
		animalConsume(event.typeIndex,
			      event.entitiesIndex); // animal index, grass tile index
		break;
	case EventType::EatPlant:
		eatPlant(event.typeIndex, event.entitiesIndex); // animal index, plant tile index
		break;
	}

	// main game loop for events
	void click() {}

#endif // EVENT_H_
