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
		
	for (EntityID i = 0; i < animals.size; i++) determineFeedingTarget(animals[i], i, positions, destinations);
}


void determine_feeding_target(Animal a, EntityID i, Array<Coord>& positions, Array<Coord>& destinations)
{
        uint16_t lowest = 0;
		Coord nearest;
		auto rt = roamThreshold[a];
		auto pos = positions[i];
		Coord loc;
		bool found = false;
		GeneralFeedingCategory t = GeneralFeedingCategory::Herbivore;
		if (herbivores[a])
		{
			BitsetTable bt = herbivoreDiets[a];
			for (Food fd : bt)
			{
				loc = getNearestFood(fd);
				auto d = getDistance(pos, loc);
				if (d < rt)
				{
					setForageTarget(loc, destinations);
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
			BitsetTable bt = carnivoreDiets[a];
			for (Animal prey : bt)
			{
				loc = getNearestAnimal(prey);
				// possible improvement/alternate method: do not search for plants
				// and animals in non-native biomes!
				auto d = getDistance(pos, loc);
				auto rt = roamThreshold[a];
				if (d < rt)
				{
					setHuntTarget(loc, destinations);
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

		// TODO: SET action to SEARCH if not in roamThreshold
		switch (t)
		{
		case GeneralFeedingCategory::Herbivore:
			setForageTarget(i, loc, destinations);
			break;
		case GeneralFeedingCategory::Carnivore:
			setHuntTarget(i, loc, destinations);
			break;
		case GeneralFeedingCategory::Scavenger:
			setScavengeTarget(i, loc, destinations);
			break;
		}
}
