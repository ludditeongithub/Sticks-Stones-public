#include <world/item/enum.hpp>
#include <core/data.hpp>

inline bool check_rotten(Item perishable, Time living_time);

inline Time get_perishable_time(Item item, Time time_passed, Temp temperature)
{
	// TODO: error checking if (!is_perishable(item)) {
	//   }
	if (temperature < frozen_temps[item])
	{
		return time_passed * FROZEN_TIME_MULT;
	}
	else if (temperature < fridge_temps[item])
	{
		return time_passed * FRIDGE_TIME_MULT;
	}
	else if (temperature < standard_temps[item])
	{
		return time_passed * STANDARD_TIME_MULT;
	}
	else
	{
		return time_passed * HOT_TIME_MULT;
	}
}
