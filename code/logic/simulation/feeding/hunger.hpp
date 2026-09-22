#pragma once
#include <core/containers.hpp>
#include <cstdint>
#include <data/types/animal.hpp>
#include <data/types/item.hpp>
#include <data/types/plant.hpp>
#include <data/types/tile.hpp>

void process_eating_animals(Array<Animal> &animals, Array<Hunger> &hungers, Array<Time> &timers,
			  Array<Coord> &coords, Array<uint16_t> &targets,
			  Array<TargetType> &target_types,
			  // plant info
			  Array<Plant> &plants, Array<Health> &plant_healths,
			  Array<Coord> &plant_coords,
			  // item info
			  Array<Item> &items,
			  // corpse info
			  Array<Animal> &corpses, Array<Coord> &corpse_coords,
			  Array<Time> &corpse_times, Array<Hunger> &corpse_hungers,
			  // tile info
			  Array<TileData> &tiles);

inline Time eating_timer(Hunger eating_amount, Animal eater);

void set_initial_feeding_time(int animal_index);

inline bool attempt_eat(Array<Animal> &animals, Array<Hunger> &hungers, Array<Coord> &animal_coords,
		       Array<Time> &timers, uint16_t animal_index);

inline bool eat_perishable(Array<Animal> &animals, Array<Hunger> &hungers,
			  Array<Coord> &animal_coords, Array<Time> &timers, uint16_t animal_index,
			  Array<Item> &perishables, Array<Hunger> &perishable_hungers,
			  Array<Time> &perishable_times, Array<Coord> &perishable_coords,
			  uint16_t perishable_index);

inline bool eat_plant(Array<Animal> &animals, Array<Hunger> &hungers, Array<Time> &timers,
		     Array<Coord> &animal_coords, uint16_t animal_index, Array<Plant> &plants,
		     Array<Health> &plant_healths, Array<Coord> &plant_coords, uint16_t plant_index);

inline bool eat_grass(Array<Animal> &animals, Array<Hunger> &hungers, Array<Time> &timers,
		     uint16_t animal_index, Array<TileData> &tiles);
int calculate_time_till_feed(int hunger_amount, Animal animal);
void prepare_feed(int animal_index);
void update(entt::registry &reg);
