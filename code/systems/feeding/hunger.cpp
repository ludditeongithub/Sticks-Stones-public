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
			  Array<TargetType> &targetTypes,
			  // plant info
			  Array<Plant> &plants, Array<Health> &plantHealths,
			  Array<Coord> &plantCoords,
			  // item info
			  Array<Item> &items,
			  // corpse info
			  Array<Coord> &perishableCoords, Array<Time> &perishableTimes,
			  Array<Hunger> &perishableHungers,
			  // tile info
			  Array<TileData> &tiles)
{
	for (uint16_t i = 0; i < hungers.capacity; i++)
	{
		bool ate = false;
		switch (targetTypes[i])
		{
		case TargetType::Plant:
			ate = eatPlant(animals, hungers, timers, coords, i, plants, plantHealths,
				       plantCoords, targets[i]);
			break;
		case TargetType::Item: // fruit, eggs, human meals, corpse
			ate = eatPerishable(animals, hungers, coords, timers, i, perishableHungers,
					    perishableTimes, perishableCoords, targets[i]);
			break;
			// case TargetType::Item:
			//   ate = eatCorpse(animals, hungers,
			//                   coords, timers,
			//                   i, corpseHungers,
			//                   corpseTimes, corpseCoords,
			// 			 targets[i]);
			//  break;
		default: // grass
			ate = eatGrass(animals, hungers, timers, i, tiles);
		}
		if (ate)
		{
		}
	}
}

inline Time eating_timer(Hunger eatingAmount, Animal eater)
{
	return eatingAmount / (eatingSpeeds[eater] / HOUR_LENGTH);
}

inline bool eat_perishable(Array<Animal> &animals, Array<Hunger> &hungers,
			  Array<Coord> &animalCoords, Array<Time> &timers, uint16_t animalIndex,
			  Array<Item> &perishables, Array<Hunger> &perishableHungers,
			  Array<Time> &perishableTimes, Array<Coord> &perishableCoords,
			  uint16_t perishableIndex)
{
	Animal a = animals[animalIndex];
	if (checkRotten(perishables[perishableIndex], perishableTimes[perishableIndex]) ||
	    !adjacentCoords(perishableCoords[perishableIndex], animalCoords[animalIndex]))
	{
		return false;
	}
	else
	{
		Hunger &ch = perishableHungers[perishableIndex];
		Hunger &h = hungers[animalIndex];
		if (maxHungers[animals[animalIndex]] > ch + h)
		{
			timers[animalIndex] = eatingTimer(ch, a);
			h += ch;
			ch = 0;
		}
		else
		{
			Hunger hd = maxHungers[a] - h;
			ch -= hd;
			h += hd;
			timers[animalIndex] = eatingTimer(hd, a);
		}
	}
	return true;
}

// lacks verification if animal can eat current plant
inline bool eat_plant(Array<Animal> &animals, Array<Hunger> &hungers, Array<Time> &timers, Array<Coord> &animalCoords, uint16_t animalIndex, Array<Health> &plantHealths, Array<Coord> &plantCoords, uint16_t plantIndex)
{
	if (adjacentCoords(plantCoords[plantIndex], animalCoords[animalIndex])) return false;
	Animal a = animals[animalIndex];
	Health &h = plantHealths[plantIndex];
	Hunger mh = maxHungers[a];
	Hunger &hv = hungers[animalIndex];
	if (mh < hv + static_cast<Hunger>(h))
	{
		Hunger rh = mh - hv;
		h -= static_cast<Health>(rh);
		hv = mh;
		timers[animalIndex] = eatingTimer(rh, a);
	}
	else
	{
		Hunger ah = h;
		h = 0;
		hv += ah;
		timers[animalIndex] = eatingTimer(ah, a);
	}
	return true;
}

// TODO: events like these, what happesn to the grass tile is
inline bool eat_grass(Array<Animal> &animals, Array<Hunger> &hungers, Array<Coord> &coords,
		     Array<Time> &timers, uint16_t animalIndex, Array<TileData> &tiles)
{
	uint16_t ti = coordToIndex(coords[animalIndex], TILE_AMOUNT);
	TileData &tile = tiles[ti];
	if (tileGrass(tile))
	{
		Animal a = animals[animalIndex];
		Hunger mh = maxHungers[a];
		Hunger &hv = hungers[animalIndex];
		hv = fmin(mh, hv + GRASS_HUNGER_VALUE);
		degrassTile(tile);
		timers[animalIndex] = eatingTimer(GRASS_HUNGER_VALUE, a);
		return true;
	}
	return false;
}

// for both Hunters and Herbivores
// TODO: perhaps have two levels of scanFood, one for within sight, first
// triggered, one for a search, like this
void scan_food(entt::registry &reg, entt::entity &e)
{
	const Type t = reg.get<Type>(e);
	auto index = entt::to_entity(e);
	uint16_t lowest = 0;
	// TODO
	auto rt = roamThreshold[t];
	if (carnivores[t])
	{
		uint32_t prey_index;
		BitsetTable bt = food::carnivoreDiets[t];
		for (Type prey : bt)
		{
			// TODO
			tpi = getNearest(e, prey);
			// possible improvement/alternate method: do not search for plants and
			// animals in non-native biomes!
			auto d = getDistance(index, tpi);
			if (d < roamThreshold)
			{
				setHuntTarget(reg, e, tpi);
				return;
			}
			if (d < lowest)
			{
				lowest = d;
				preyIndex = tpi;
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
		BitsetTable bt = food::getHerbivoreDiet(t);
		for (Type fd : bt)
		{
			// TODO
			tpi = getNearest(e, fd);
			auto d = getDistance(index, forageIndex);
			if (d < roamThreshold)
			{
				setForageTarget(reg, e, tfi);

				return;
			}
			if (d < lowest)
			{
				lowest = d;
				forageIndex = tfi;
			}
			// END TODO
		}
		if (carnivores[t])
		{
			setHuntTarget(reg, e, preyIndex);
			return;
		}
		setForageTarget(reg, e, forageIndex);
	}
}

// in ticks
int calculate_time_till_feed(int hungerAmount, Animal animal)
{
	float max_hunger;
	float tick_burn_rate;
	int time_till_feed;

	int eating_threshold = max_hunger / 2;
	if (hungerAmount < eating_threshold)
		return 0;
	else
		return static_cast<int>((hungerAmount - EatingThreshold) / burnRate);
}

// void preparePreyFeed(int animalIndex) {
// 	addEvent(calculateTimeTillFeed(hunger[animalIndex] + futureConsumption,
// feeder), EventType::PreyFeed, static_cast<int>(feeder), animalIndex);
// }

// //TODO: if outDistSqr not required, do not do it
// void preparePredatorFeed(int animalIndex) {

// 	addEvent(calculateTimeTillFeed(hunger[animalIndex] + futureConsumption,
// feeder), EventType::PredatorFeed, animalType, animalIndex);
// }
