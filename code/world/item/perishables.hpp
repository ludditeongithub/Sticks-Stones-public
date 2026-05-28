#ifndef PERISHABLES_HPP
#define PERISHABLES_HPP
#include "enum.hpp"
#include <core/data.hpp>
#include <core/tables.hpp>

constexpr float FROZEN_TIME_MULT = 0.005;
constexpr float FRIDGE_TIME_MULT = 0.08;
constexpr float STANDARD_TIME_MULT = 1.00;
constexpr float HOT_TIME_MULT = 1.85;

inline constexpr LookupTable<Item, Temp> frozenTemps = []
{
	LookupTable<Item, Temp> lt{};
	using enum Item;

	return lt;
}();

inline constexpr LookupTable<Item, Temp> fridgeTemps = []
{
	LookupTable<Item, Temp> lt{};
	using enum Item;

	return lt;
}();

inline constexpr LookupTable<Item, Temp> standardTemps = []
{
	LookupTable<Item, Temp> lt{};
	using enum Item;

	return lt;
}();

#endif
