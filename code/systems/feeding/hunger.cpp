#include "eating_manager.hpp"
#include "systems/perishables_manager.hpp"
#include <core/containers.hpp>
#include <core/data.hpp>
#include <world/animal/enum.hpp>
#include <world/animal/tables.hpp>
#include <world/item/enum.hpp>
#include <world/plant/enum.hpp>
#include <world/tile/data.hpp>
#include <world/tile/grass.hpp>

// all functions that consume are unsafe. safety controlled by main eating
// function
void process_eating_animals(Array<Animal> &animals, Array<Hunger> &hungers, Array<Time> &timers,
			  Array<Coord> &coords, Array<uint16_t> &targets,
			  Array<TargetType> &target_types,
			  // plant info
			  Array<Plant> &plants, Array<Health> &plant_healths,
			  Array<Coord> &plant_coords,
			  // item info
			  Array<Item> &items,
			  // corpse info
			  Array<Coord> &perishable_coords, Array<Time> &perishable_times,
			  Array<Hunger> &perishable_hungers,
			  // tile info
			  Array<TileData> &tiles)
{
	for (uint16_t i = 0; i < hungers.capacity; i++)
	{
		bool ate = false;
		switch (target_types[i])
		{
		case TargetType::Plant:
			ate = eat_plant(animals, hungers, timers, coords, i, plants, plant_healths,
				       plant_coords, targets[i]);
			break;
		case TargetType::Item: // fruit, eggs, human meals, corpse
			ate = eat_perishable(animals, hungers, coords, timers, i, perishable_hungers,
					    perishable_times, perishable_coords, targets[i]);
			break;
			// case TargetType::Item:
			//   ate = eat_corpse(animals, hungers,
			//                   coords, timers,
			//                   i, corpse_hungers,
			//                   corpse_times, corpse_coords,
			// 			 targets[i]);
			//  break;
		default: // grass
			ate = eat_grass(animals, hungers, timers, i, tiles);
		}
		if (ate)
		{
		}
	}
}

inline Time eating_timer(Hunger eating_amount, Animal eater)
{
	return eating_amount / (eating_speeds[eater] / HOUR_LENGTH);
}

inline bool eat_perishable(Array<Animal> &animals, Array<Hunger> &hungers,
			  Array<Coord> &animal_coords, Array<Time> &timers, uint16_t animal_index,
			  Array<Item> &perishables, Array<Hunger> &perishable_hungers,
			  Array<Time> &perishable_times, Array<Coord> &perishable_coords,
			  uint16_t perishable_index)
{
	Animal a = animals[animal_index];
	if (check_rotten(perishables[perishable_index], perishable_times[perishable_index]) ||
	    !adjacent_coords(perishable_coords[perishable_index], animal_coords[animal_index]))
	{
		return false;
	}
	else
	{
		Hunger &ch = perishable_hungers[perishable_index];
		Hunger &h = hungers[animal_index];
		if (max_hungers[animals[animal_index]] > ch + h)
		{
			timers[animal_index] = eating_timer(ch, a);
			h += ch;
			ch = 0;
		}
		else
		{
			Hunger hd = max_hungers[a] - h;
			ch -= hd;
			h += hd;
			timers[animal_index] = eating_timer(hd, a);
		}
	}
	return true;
}

// lacks verification if animal can eat current plant
inline bool eat_plant(Array<Animal> &animals, Array<Hunger> &hungers, Array<Time> &timers, Array<Coord> &animal_coords, uint16_t animal_index, Array<Health> &plant_healths, Array<Coord> &plant_coords, uint16_t plant_index)
{
	if (adjacent_coords(plant_coords[plant_index], animal_coords[animal_index])) return false;
	Animal a = animals[animal_index];
	Health &h = plant_healths[plant_index];
	Hunger mh = max_hungers[a];
	Hunger &hv = hungers[animal_index];
	if (mh < hv + static_cast<Hunger>(h))
	{
		Hunger rh = mh - hv;
		h -= static_cast<Health>(rh);
		hv = mh;
		timers[animal_index] = eating_timer(rh, a);
	}
	else
	{
		Hunger ah = h;
		h = 0;
		hv += ah;
		timers[animal_index] = eating_timer(ah, a);
	}
	return true;
}

// TODO: events like these, what happesn to the grass tile is
inline bool eat_grass(Array<Animal> &animals, Array<Hunger> &hungers, Array<Coord> &coords,
		     Array<Time> &timers, uint16_t animal_index, Array<TileData> &tiles)
{
	uint16_t ti = coord_to_index(coords[animal_index], TILE_AMOUNT);
	TileData &tile = tiles[ti];
	if (tile_grass(tile))
	{
		Animal a = animals[animal_index];
		Hunger mh = max_hungers[a];
		Hunger &hv = hungers[animal_index];
		hv = fmin(mh, hv + GRASS_HUNGER_VALUE);
		degrass_tile(tile);
		timers[animal_index] = eating_timer(GRASS_HUNGER_VALUE, a);
		return true;
	}
	return false;
}

// for both Hunters and Herbivores
// TODO: perhaps have two levels of scan_food, one for within sight, first
// triggered, one for a search, like this
void scan_food(entt::registry &reg, entt::entity &e)
{
	const Type t = reg.get<Type>(e);
	auto index = entt::to_entity(e);
	uint16_t lowest = 0;
	// TODO
	auto rt = roam_threshold[t];
	if (carnivores[t])
	{
		uint32_t prey_index;
		BitsetTable bt = food::carnivore_diets[t];
		for (Type prey : bt)
		{
			// TODO
			tpi = get_nearest(e, prey);
			// possible improvement/alternate method: do not search for plants and
			// animals in non-native biomes!
			auto d = get_distance(index, tpi);
			if (d < roam_threshold)
			{
				set_hunt_target(reg, e, tpi);
				return;
			}
			if (d < lowest)
			{
				lowest = d;
				prey_index = tpi;
			}
			// END TODO
		}
	}

	if (scavengers[i])
	{
	}

	if (herbivores[t])
	{
		uint32_t forage_index;
		BitsetTable bt = food::get_herbivore_diet(t);
		for (Type fd : bt)
		{
			// TODO
			tpi = get_nearest(e, fd);
			auto d = get_distance(index, forage_index);
			if (d < roam_threshold)
			{
				set_forage_target(reg, e, tfi);

				return;
			}
			if (d < lowest)
			{
				lowest = d;
				forage_index = tfi;
			}
			// END TODO
		}
		if (carnivores[t])
		{
			set_hunt_target(reg, e, prey_index);
			return;
		}
		set_forage_target(reg, e, forage_index);
	}
}

// in ticks
int calculate_time_till_feed(int hunger_amount, Animal animal)
{
	float max_hunger;
	float tick_burn_rate;
	int time_till_feed;

	int eating_threshold = max_hunger / 2;
	if (hunger_amount < eating_threshold)
		return 0;
	else
		return static_cast<int>((hunger_amount - EatingThreshold) / burn_rate);
}

// void prepare_prey_feed(int animal_index) {
// 	add_event(calculate_time_till_feed(hunger[animal_index] + future_consumption,
// feeder), EventType::PreyFeed, static_cast<int>(feeder), animal_index);
// }

// //TODO: if out_dist_sqr not required, do not do it
// void prepare_predator_feed(int animal_index) {

// 	add_event(calculate_time_till_feed(hunger[animal_index] + future_consumption,
// feeder), EventType::PredatorFeed, animal_type, animal_index);
// }
