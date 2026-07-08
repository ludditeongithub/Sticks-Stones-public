#pragma once
#include "database.hpp"

void AnimalDatabase::handleEvent(Event &event)
{
		const EventType type = event.eventType;
		switch (type)
				{
		// TODO: certain events will be delayed if something else is happening (being attacked), others not
		case EventType::FindMate:				
       			trackMate(event.databaseIndex);
       			break;
		case EventType::AnimalBirth:
       			birthAnimal(static_cast<Animal>(event.typeIndex), event.databaseIndex);
				break;
		case EventType::AnimalBreeding:
       			breed(static_cast<Animal>(event.typeIndex), event.databaseIndex, event.secondaryIndex);
       			break;
		default:
				
		}

}
