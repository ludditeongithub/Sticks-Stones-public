#pragma once
#include "database.hpp"

void AnimalDatabase::handle_event(Event &event)
{
		const EventType type = event.event_type;
		switch (type)
				{
		// TODO: certain events will be delayed if something else is happening (being attacked), others not
		case EventType::FindMate:				
       			track_mate(event.database_index);
       			break;
		case EventType::AnimalBirth:
       			birth_animal(static_cast<Animal>(event.type_index), event.database_index);
				break;
		case EventType::AnimalBreeding:
       			breed(static_cast<Animal>(event.type_index), event.database_index, event.secondary_index);
       			break;
		default:
				
		}

}
