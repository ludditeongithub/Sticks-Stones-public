#include <core/containers.hpp>
#include <core/data.hpp>
#include <schedule/dispatch.hpp>
#include <world/animal/enum.hpp>
#include <world/animal/tables.hpp>
#include <world/food/categories.hpp>

enum class GeneralFeedingCategory
	{
		Herbivore,
		Carnivore,
		Scavenger
	};

// TODO: possible optimization: separate herbivores and carnivores into separate loops, to improve
// cache efficiency
void set_hungry_destinations(DispatchData<Animal> &dispatch)
{
	Array<Animal> &animals = dispatch.types;
	Array<Coord> &positions = dispatch.positions;
	Array<Coord> &destinations = dispatch.destinations;	
		
	for (EntityID i = 0; i < animals.size; i++) determine_feeding_target(animals[i], i, positions, destinations);
}


void determine_feeding_target(Animal a, EntityID i, Array<Coord>& positions, Array<Coord>& destinations)
{
        uint16_t lowest = 0;
		Coord nearest;
		auto rt = roam_threshold[a];
		auto pos = positions[i];
		Coord loc;
		bool found = false;
		GeneralFeedingCategory t = GeneralFeedingCategory::Herbivore;
		if (herbivores[a])
		{
			BitsetTable bt = herbivore_diets[a];
			for (Food fd : bt)
			{
				loc = get_nearest_food(fd);
				auto d = get_distance(pos, loc);
				if (d < rt)
				{
					set_forage_target(loc, destinations);
					continue;
				}
				if (d < lowest)
				{
					lowest = d;
					nearest = loc;
					t = GeneralFeedingCategory::Herbivore;
				}
			}
		}

		if (carnivores[a])
		{
			uint32_t prey_index;
			BitsetTable bt = carnivore_diets[a];
			for (Animal prey : bt)
			{
				loc = get_nearest_animal(prey);
				// possible improvement/alternate method: do not search for plants
				// and animals in non-native biomes!
				auto d = get_distance(pos, loc);
				auto rt = roam_threshold[a];
				if (d < rt)
				{
					set_hunt_target(loc, destinations);
					continue;
				}
				if (d < lowest)
				{
					lowest = d;
					nearest = loc;
					t = GeneralFeedingCategory::Carnivore;
				}
			}
		}

		if (scavengers[i])
		{
		}

		// TODO: SET action to SEARCH if not in roam_threshold
		switch (t)
		{
		case GeneralFeedingCategory::Herbivore:
			set_forage_target(i, loc, destinations);
			break;
		case GeneralFeedingCategory::Carnivore:
			set_hunt_target(i, loc, destinations);
			break;
		case GeneralFeedingCategory::Scavenger:
			set_scavenge_target(i, loc, destinations);
			break;
		}
}
