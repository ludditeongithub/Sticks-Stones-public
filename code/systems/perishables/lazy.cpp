#include <world/item/enum.hpp>
#include <core/data.hpp>

inline bool check_rotten(Item perishable, Time livingTime);

inline Time get_perishable_time(Item item, Time timePassed, Temp temperature)
{
	// TODO: error checking if (!isPerishable(item)) {
	//   }
	if (temperature < frozenTemps[item])
	{
		return timePassed * FROZEN_TIME_MULT;
	}
	else if (temperature < fridgeTemps[item])
	{
		return timePassed * FRIDGE_TIME_MULT;
	}
	else if (temperature < standardTemps[item])
	{
		return timePassed * STANDARD_TIME_MULT;
	}
	else
	{
		return timePassed * HOT_TIME_MULT;
	}
}
