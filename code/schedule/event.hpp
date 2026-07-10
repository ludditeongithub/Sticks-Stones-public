#ifndef EVENT_H_
#define EVENT_H_
#include <vector>
#include <core/data.hpp>
#include <simulation/game.hpp>

enum class EventType
{
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
	FindMate,
	AnimalBreeding,
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
	EventType event_type;
	size_t type_index; // index which converts to the enum class that is the main object in the
		       // event in question
	size_t database_index;  // index of the vector that stores the entities of the type in question
	size_t secondary_index; // if there is a secondary object this converts to its enum class
};


struct EventManager {
		std::vector<Event> upcoming_events;
		Game& game;

void add_event(Time time, EventType type, size_t type_index, size_t database_index)
{
	upcomingEvents.push_back({game.absoluteTime + time, type, typeIndex, databaseIndex});
}

void add_event(Time time, EventType type, size_t type_index, size_t database_index, size_t secondary_index)
{
	upcomingEvents.push_back({game.absoluteTime + time, type, typeIndex, databaseIndex, secondaryIndex});
}

// OPTI: if things begin to lag, optimize this to O log n or O1 using jump table
void interpret_event(Event event)
{
	switch (event.eventType)
	{	
	case EventType::ProductComplete:
		Item product = static_cast<Item>(event.typeIndex);
		if (eventTypeIndex < static_cast<int>(Item::VARIANTSMAX))
		{
			inventories[event.databaseIndex].variantItems.push_back(product);
			inventories[event.databaseIndex].variantItemTypes.push_back(
			    event.secondaryIndex);
			occupied[pawn] = false;
		}
		else
			inventories[event.databaseIndex].items.push_back(product);
		// TODO: add case for tools
		break;
	case EventType::Birth:
		birth(event.databaseIndex);
		break;
	case EventType::PlantDeath:
		cropDeath(event.databaseIndex);
		break;
	case EventType::TreeDeath:
		treeDeath(event.databaseIndex);
		break;
		// TODO: before this, check to see that the parameters are right
	case EventType::ProductComplete:
		productFinish(event.typeIndex, event.databaseIndex, event.secondaryIndex);
		decidePawnTask(event.databaseIndex);
		break;
	case EventType::WakeUp:
		setMovingStatus(event.databaseIndex);
		break;
	case EventType::NotFertilized:
		setUnfertilized(event.databaseIndex);
		break;
	case EventType::Lay:
		layEgg(static_cast<Animal>(event.typeIndex), event.databaseIndex);
		break;
	case EventType::Hatch:
		hatchEgg(static_cast<Animal>(event.typeIndex), event.databaseIndex);
	case EventType::Breed:
		breed(static_cast<Animal>(event.typeIndex), event.databaseIndex);
		break;
	case EventType::AnimalBirth:
		animalBirth(static_cast<Animal>(event.typeIndex), event.databaseIndex);
		break;
	case EventType::EatGrass:
		animalConsume(event.typeIndex,
			      event.databaseIndex); // animal index, grass tile index
		break;
	case EventType::EatPlant:
		eatPlant(event.typeIndex, event.databaseIndex); // animal index, plant tile index
		break;
	}
}
};

EventManager* g_events;

#endif // EVENT_H_
