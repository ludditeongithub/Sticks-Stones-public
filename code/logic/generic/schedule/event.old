#ifndef EVENT_H_
#define EVENT_H_
#include <vector>

#include <logic/simulation/game.hpp>

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
	upcoming_events.push_back({game.absolute_time + time, type, type_index, database_index});
}

void add_event(Time time, EventType type, size_t type_index, size_t database_index, size_t secondary_index)
{
	upcoming_events.push_back({game.absolute_time + time, type, type_index, database_index, secondary_index});
}

// OPTI: if things begin to lag, optimize this to O log n or O1 using jump table
void interpret_event(Event event)
{
	switch (event.event_type)
	{	
	case EventType::ProductComplete:
		Item product = static_cast<Item>(event.type_index);
		if (event_type_index < static_cast<int>(Item::VARIANTSMAX))
		{
			inventories[event.database_index].variant_items.push_back(product);
			inventories[event.database_index].variant_item_types.push_back(
			    event.secondary_index);
			occupied[pawn] = false;
		}
		else
			inventories[event.database_index].items.push_back(product);
		// TODO: add case for tools
		break;
	case EventType::Birth:
		birth(event.database_index);
		break;
	case EventType::PlantDeath:
		crop_death(event.database_index);
		break;
	case EventType::TreeDeath:
		tree_death(event.database_index);
		break;
		// TODO: before this, check to see that the parameters are right
	case EventType::ProductComplete:
		product_finish(event.type_index, event.database_index, event.secondary_index);
		decide_pawn_task(event.database_index);
		break;
	case EventType::WakeUp:
		set_moving_status(event.database_index);
		break;
	case EventType::NotFertilized:
		set_unfertilized(event.database_index);
		break;
	case EventType::Lay:
		lay_egg(static_cast<Animal>(event.type_index), event.database_index);
		break;
	case EventType::Hatch:
		hatch_egg(static_cast<Animal>(event.type_index), event.database_index);
	case EventType::Breed:
		breed(static_cast<Animal>(event.type_index), event.database_index);
		break;
	case EventType::AnimalBirth:
		animal_birth(static_cast<Animal>(event.type_index), event.database_index);
		break;
	case EventType::EatGrass:
		animal_consume(event.type_index,
			      event.database_index); // animal index, grass tile index
		break;
	case EventType::EatPlant:
		eat_plant(event.type_index, event.database_index); // animal index, plant tile index
		break;
	}
}
};

EventManager* g_events;

#endif // EVENT_H_
