#include "core/data.hpp"
#include "database.hpp"
#include "render/sprite.hpp"
#include "render/sprite_sheet_settings.hpp"
#include "schedule/event.hpp"
#include "world/animal/enum.hpp"
#include "world/animal/tables.hpp"

void AnimalDatabase::birth_animal(Animal animal, size_t mother_index)
{
	// TODO: perhaps include age lowering fertility later
	Coord origin = coords[mother_index];	
	int length = animal_sprite_infos[animal].CHILD_SIDE_LENGTH;
	// TODO: make non-index versions of all pathfinding algos
	Coord bottom_left_corner = tiles.get_nearest_empty_tile_block(origin, length);
	spawn(animal, true, bottom_left_corner);
	// after birth, add event for next breeding in the future
	// TODO: consider sleeping
	if (ages[mother_index] < animal::senescence_ages[animal] - animal::breeding_intervals[animal])
	g_Events->add_event(animal::breeding_intervals[animal], EventType::FindMate,
	static_cast<size_t>(animals[mother_index]), mother_index);
}


inline bool AnimalDatabase::get_conception_roll(Animal animal, size_t female_index, size_t male_index)
{		
		const Time male_age = ages[male_index];
		const Time female_age = ages[female_index];
		if (female_age < animal::fertility_ages[animal] || male_age < animal::fertility_ages[animal])
			{
					// TODO: error handling
					return 0.0;
			}
		if (female_age < animal::senescence_ages[animal] || male_age < animal::senescence_ages[animal])
			{
					// TODO: error handling
					return 0.0;
			}
		return (random_chance->next() < animal::base_fertility_chances[animal]);
}


void AnimalDatabase::breed(Animal animal, size_t female_index, size_t male_index)
{
		if (animals[male_index] != animals[female_index])
		{
		// TODO: error handling
		}
		if (get_conception_roll(female_index, male_index)) {
				// MTODO: change state to pregnant
				if (animal::is_egg_layer[animal]) {
						// MTODO: fish differently
				fertilization_handler.push_back(female_index);                  
				} else g_Events->add_event(animal::pregnancy_lengths[animal], EventType::AnimalBirth, static_cast<size_t>(animal), female_index);
		}
}

void AnimalDatabase::set_track_mate_path(Animal animal, size_t index)
{
		bool found = false;
		int nearest = 0;
		Coord origin = coords[index];
		EntitySearchData esd = search.get_nearest(animal, origin);
		if (ages[esd.index] > animal::fertility_ages[animal])
				found = true;
		while (!found)
				{
						nearest++;
						search.get_nth_nearest(nearest, animal, origin);
				}
		target_types[index] = TargetType::Animal;
		targets[index] = esd.index;
		actions[index] = Action::Breed;
		animal_statuses[index].set<ActionStatus>(ActionStatus::NewPath);
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
	items.attempt_spawn(item, true, coord);	
	if (fertilized) g_Events->add_event(animal::hatch_times[animal], EventType::Hatch, static_cast<size_t>(animal), static_cast<size_t>(fertilized));
}


void AnimalDatabase::make_corpse(const size_t index)
{
	const Coord coord = coords[index];
	const Animal animal = animals[index];
	const Time age = ages[index];
	size_t length;
	if (age < animal::fertility_ages[animal]) {
	   length = animal_sprite_infos[animal].CHILD_FRONT_LENGTH;
	} else length = animal_sprite_infos[animal].FRONT_LENGTH;
	Coord left_corner = tiles.get_nearest_empty_tile_block(coord, length);
	variant_items.attempt_spawn(Item::Corpse, false, coord, static_cast<Variant>(animal));
}

void AnimalDatabase::kill_animal(const size_t index)
{
	if (remove(index)) make_corpse(index);
	else
	  {
	  // TODO: error            
	  }
}


