#ifndef FEEDING_MANAGER_HPP
#define FEEDING_MANAGER_HPP
#include <core/containers.hpp>
#include <cstdint>
#include <world/animal/enum.hpp>
#include <world/item/enum.hpp>
#include <world/plant/enum.hpp>
#include <world/tile/enum.hpp>

void processEatingAnimals(Array<Animal> &animals, Array<Hunger> &hungers, Array<Time> &timers,
			  Array<Coord> &coords, Array<uint16_t> &targets,
			  Array<TargetType> &targetTypes,
			  // plant info
			  Array<Plant> &plants, Array<Health> &plantHealths,
			  Array<Coord> &plantCoords,
			  // item info
			  Array<Item> &items,
			  // corpse info
			  Array<Animal> &corpses, Array<Coord> &corpseCoords,
			  Array<Time> &corpseTimes, Array<Hunger> &corpseHungers,
			  // tile info
			  Array<TileData> &tiles);

inline Time eatingTimer(Hunger eatingAmount, Animal eater);

void setInitialFeedingTime(int animalIndex);

inline bool attemptEat(Array<Animal> &animals, Array<Hunger> &hungers, Array<Coord> &animalCoords,
		       Array<Time> &timers, uint16_t animalIndex);

inline bool eatPerishable(Array<Animal> &animals, Array<Hunger> &hungers,
			  Array<Coord> &animalCoords, Array<Time> &timers, uint16_t animalIndex,
			  Array<Item> &perishables, Array<Hunger> &perishableHungers,
			  Array<Time> &perishableTimes, Array<Coord> &perishableCoords,
			  uint16_t perishableIndex);

inline bool eatPlant(Array<Animal> &animals, Array<Hunger> &hungers, Array<Time> &timers,
		     Array<Coord> &animalCoords, uint16_t animalIndex, Array<Plant> &plants,
		     Array<Health> &plantHealths, Array<Coord> &plantCoords, uint16_t plantIndex);

inline bool eatGrass(Array<Animal> &animals, Array<Hunger> &hungers, Array<Time> &timers,
		     uint16_t animalIndex, Array<TileData> &tiles);
int calculateTimeTillFeed(int hungerAmount, Animal animal);
void prepareFeed(int animalIndex);
void update(entt::registry &reg);

#endif
