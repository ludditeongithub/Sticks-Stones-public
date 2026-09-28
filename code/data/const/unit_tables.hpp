#pragma once
#include <data/types/unit.hpp>
#include <data/const/unit_data.hpp>
#include <data/types/stats.hpp>

namespace unit {
inline constexpr LookupTable<Unit, Health> MAX_HEALTHS = []
{
	LookupTable<Unit, Health> lt{};
	using enum Unit;
	for (size_t i = 0; i < static_cast<size_t>(Unit::MAX); i++)
	{
		lt[static_cast<Unit>(i)] = MAX_HEALTH;
	}
	return lt;
}();

inline constexpr LookupTable<Unit, Hunger> MAX_HUNGERS = []
{
	LookupTable<Unit, Hunger> lt{};
	using enum Unit;
	for (size_t i = 0; i < static_cast<size_t>(Unit::MAX); i++) {
			lt[static_cast<Unit>(i)] = MAX_HUNGER;
	}
	return lt;
}();
}
