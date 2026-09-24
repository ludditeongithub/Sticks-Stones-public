#ifndef PERISHABLES_MANAGER_HPP
#define PERISHABLES_MANAGER_HPP

#include <core/containers.hpp>

#include <core/tables.hpp>
#include <data/types/item.hpp>

constexpr float FROZEN_TIME_MULT = 0.005;
constexpr float FRIDGE_TIME_MULT = 0.08;
constexpr float STANDARD_TIME_MULT = 1.00;
constexpr float HOT_TIME_MULT = 1.85;

inline constexpr LookupTable<Item, Time> PERISHABLE_DESTRUCTION_TIMES = []
{
	LookupTable<Item, Time> lt{};
	using enum Item;

	return lt;
}();

void process_perishable_rots(Array<Item> &perishables, Array<Time> &living_times, Time time_passed);

inline bool check_rotten(Item perishable, Time living_time);

inline Time get_perishable_time(Item item, Time time_passed, Temp temperature);

#endif
