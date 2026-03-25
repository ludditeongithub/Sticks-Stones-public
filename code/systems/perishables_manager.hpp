#ifndef PERISHABLES_MANAGER_HPP
#define PERISHABLES_MANAGER_HPP

#include <core/containers.hpp>
#include <core/data.hpp>
#include <core/tables.hpp>
#include <world/item/enum.hpp>

constexpr float FROZEN_TIME_MULT = 0.005;
constexpr float FRIDGE_TIME_MULT = 0.08;
constexpr float STANDARD_TIME_MULT = 1.00;
constexpr float HOT_TIME_MULT = 1.85;

inline constexpr LookupTable<Item, Time> perishableDestructionTimes = []
{
	LookupTable<Item, Time> lt{};
	using enum Item;

	return lt;
}();

void processPerishableRots(Array<Item> &perishables, Array<Time> &livingTimes, Time timePassed);

inline bool checkRotten(Item perishable, Time livingTime);

inline Time getPerishableTime(Item item, Time timePassed, Temp temperature);

#endif
