#include "core/data.hpp"
#include "database.hpp"
#include "render/sprite.hpp"
#include "render/sprite_sheet_settings.hpp"
#include "schedule/event.hpp"
#include "world/animal/enum.hpp"
#include "world/animal/tables.hpp"

void AnimalDatabase::birth_animal(Animal animal, size_t motherIndex)
{
	// TODO: perhaps include age lowering fertility later
	Coord origin = coords[motherIndex];	
	int length = animalSpriteInfos[animal].CHILD_SIDE_LENGTH;
	// TODO: make non-index versions of all pathfinding algos
	Coord bottom_left_corner = tiles.getNearestEmptyTileBlock(origin, length);
	spawn(animal, true, bottomLeftCorner);
	// after birth, add event for next breeding in the future
	// TODO: consider sleeping
	if (ages[motherIndex] < animal::senescenceAges[animal] - animal::breedingIntervals[animal])
	g_Events->addEvent(animal::breedingIntervals[animal], EventType::FindMate,
	static_cast<size_t>(animals[motherIndex]), motherIndex);
}


inline bool AnimalDatabase::get_conception_roll(Animal animal, size_t femaleIndex, size_t maleIndex)
{		
		const Time male_age = ages[maleIndex];
		const Time female_age = ages[femaleIndex];
		if (femaleAge < animal::fertilityAges[animal] || maleAge < animal::fertilityAges[animal])
			{
					// TODO: error handling
					return 0.0;
			}
		if (femaleAge < animal::senescenceAges[animal] || maleAge < animal::senescenceAges[animal])
			{
					// TODO: error handling
					return 0.0;
			}
		return (random_chance->next() < animal::baseFertilityChances[animal]);
}


void AnimalDatabase::breed(Animal animal, size_t femaleIndex, size_t maleIndex)
{
		if (animals[maleIndex] != animals[femaleIndex])
		{
		// TODO: error handling
		}
		if (getConceptionRoll(femaleIndex, maleIndex)) {
				// MTODO: change state to pregnant
				if (animal::isEggLayer[animal]) {
						// MTODO: fish differently
				fertilizationHandler.push_back(femaleIndex);                  
				} else g_Events->addEvent(animal::pregnancyLengths[animal], EventType::AnimalBirth, static_cast<size_t>(animal), femaleIndex);
		}
}

void AnimalDatabase::set_track_mate_path(Animal animal, size_t index)
{
		bool found = false;
		int nearest = 0;
		Coord origin = coords[index];
		EntitySearchData esd = search.getNearest(animal, origin);
		if (ages[esd.index] > animal::fertilityAges[animal])
				found = true;
		while (!found)
				{
						nearest++;
						search.getNthNearest(nearest, animal, origin);
				}
		targetTypes[index] = TargetType::Animal;
		targets[index] = esd.index;
		actions[index] = Action::Breed;
		animalStatuses[index].set<ActionStatus>(ActionStatus::NewPath);
}

// TODO: protective mothers
void AnimalDatabase::lay_egg(Animal animal, Coord coord, bool fertilized)
{
	
	Item item;
	switch (animal)
	{
	case Animal::Duck:
		item = Item::DuckEgg;
		break;
	case Animal::Chicken:
		item = Item::ChickenEgg;
		break;
	case Animal::Turtle:
		item = Item::TurtleEgg;
			break;
	default:
			// TODO: error, invalid animal
			break;
	}
	items.attemptSpawn(item, true, coord);	
	if (fertilized) g_Events->addEvent(animal::hatchTimes[animal], EventType::Hatch, static_cast<size_t>(animal), static_cast<size_t>(fertilized));
}


void AnimalDatabase::make_corpse(const size_t index)
{
	const Coord coord = coords[index];
	const Animal animal = animals[index];
	const Time age = ages[index];
	size_t length;
	if (age < animal::fertilityAges[animal]) {
	   length = animalSpriteInfos[animal].CHILD_FRONT_LENGTH;
	} else length = animalSpriteInfos[animal].FRONT_LENGTH;
	Coord left_corner = tiles.getNearestEmptyTileBlock(coord, length);
	variantItems.attemptSpawn(Item::Corpse, false, coord, static_cast<Variant>(animal));
}

void AnimalDatabase::kill_animal(const size_t index)
{
	if (remove(index)) makeCorpse(index);
	else
	  {
	  // TODO: error            
	  }
}


