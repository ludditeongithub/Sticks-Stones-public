#include "data/types/aliases.hpp"
#include <data/run/animal_database.hpp>
#error "DATABASE HEADER INCLUDED"
#include "display/render/sprite.hpp"
#include "display/render/sprite.hpp"
#include "logic/generic/schedule/event.hpp"
#include "data/types/animal.hpp"
#include "world/animal/tables.hpp"
#include <stdexcept>
#include <string>

namespace animal {

void Database::birth_animal(Animal animal, size_t mother_index)
{
        #if !SHIPPING_BUILD
	if (mother_index >= size)
		throw std::out_of_range("Mother index out of range when birthing.");
    if (animal == Animal::NONE || animal == Animal::MAX) throw std::invalid_argument("Attempted to birth animal as NONE or MAX.");
        #endif
        
	// TODO: perhaps include age lowering fertility later
	Coord origin = coords[mother_index];	
	int length = animal_sprite_infos[animal].CHILD_SIDE_LENGTH;
	// TODO: make non-index versions of all pathfinding algos
	Coord bottom_left_corner = tiles.get_nearest_empty_tile_block(origin, length);
	spawn(animal, true, bottom_left_corner);
	// after birth, add event for next breeding in the future
	// TODO: consider sleeping
	if (ages[mother_index] < senescence_ages[animal] - breeding_intervals[animal])
	g_Events->add_event(breeding_intervals[animal], EventType::FindMate,
	static_cast<size_t>(animals[mother_index]), mother_index);
}


inline bool Database::get_conception_roll(Animal animal, size_t female_index, size_t male_index)
{
        #if !SHIPPING_BUILD
	if (female_index >= size)
		throw std::out_of_range("female index out of range when birthing.");
        if (male_index >= size)
		throw std::out_of_range("male index out of range when birthing.");
        if (animal == Animal::NONE || animal == Animal::MAX) throw std::invalid_argument("Attempted to roll conception for animal as NONE or MAX.");
        #endif
  
		const Time male_age = ages[male_index];
		const Time female_age = ages[female_index];
		if (female_age < fertility_ages[animal] || male_age < fertility_ages[animal])
			{
					// TODO: error handling
					return 0.0;
			}
		if (female_age < senescence_ages[animal] || male_age < senescence_ages[animal])
			{
					// TODO: error handling
					return 0.0;
			}
		return (random_chance->next() < base_fertility_chances[animal]);
}


void Database::breed(Animal animal, size_t female_index, size_t male_index)
{
        #if !SHIPPING_BUILD
	if (female_index >= size)
		throw std::out_of_range("female index out of range when birthing.");
        if (male_index >= size)
		throw std::out_of_range("male index out of range when birthing.");
        if (animal == Animal::NONE || animal == Animal::MAX) throw std::invalid_argument("Attempted to roll conception for animal as NONE or MAX.");
        #endif
  
		if (animals[male_index] != animals[female_index])
		{
		// TODO: error handling
		}
		if (get_conception_roll(female_index, male_index)) {
				// MTODO: change state to pregnant
				if (IS_EGG_LAYER[animal]) {
						// MTODO: fish differently
				fertilization_handler.push_back(female_index);                  
				} else g_Events->add_event(PREGNANCY_LENGTHS[animal], EventType::AnimalBirth, static_cast<size_t>(animal), female_index);
		}
}

void Database::set_track_mate_path(Animal animal, size_t index)
{
  #if !SHIPPING_BUILD
  assert(index <= size, "Mate candidate index out of range.");
  if (animal == Animal::NONE || animal == Animal::MAX) throw std::invalid_argument("Attempted to track mate for animal as NONE or MAX.");
#endif
        
		bool found = false;
		int nearest = 0;
		Coord origin = coords[index];
		EntitySearchData esd = search.get_nearest(animal, origin);
		if (ages[esd.index] > FERTILITY_AGES[animal])
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
void Database::lay_egg(Animal animal, Coord coord, bool fertilized)
{
	#if !SHIPPING_BUILD
  assert(!IS_EGG_LAYER[animal], "Non egg-laying animal attempted to lay egg at " + std::to_string(coord.x) + "," + std::to_string(coord.y));
#endif
        
	Item item;
	switch (animal)
	{
	case Duck:
		item = Item::DuckEgg;
		break;
	case Chicken:
		item = Item::ChickenEgg;
		break;
	case Turtle:
		item = Item::TurtleEgg;
			break;
	default:
			// TODO: error, invalid animal
			break;
	}
	items.attempt_spawn(item, true, coord);	
	if (fertilized) g_Events->add_event(hatch_times[animal], EventType::Hatch, static_cast<size_t>(animal), static_cast<size_t>(fertilized));
}


void Database::make_corpse(const size_t index)
{
  #if !SHIPPING_BUILD
  assert(index <= size, "Attempted to make corpse out of range.");
#endif
  
	const Coord coord = coords[index];
	const Animal animal = animals[index];
	const Time age = ages[index];
	size_t length;
	if (age < fertility_ages[animal]) {
	   length = animal_sprite_infos[animal].CHILD_FRONT_LENGTH;
	} else length = animal_sprite_infos[animal].FRONT_LENGTH;
	Coord left_corner = tiles.get_nearest_empty_tile_block(coord, length);
	variant_items.attempt_spawn(Item::Corpse, false, coord, static_cast<Variant>(animal));
}

void Database::kill_animal(const size_t index)
{
	if (remove(index)) make_corpse(index);
	else
	  {
	  // TODO: error            
	  }
}


}
