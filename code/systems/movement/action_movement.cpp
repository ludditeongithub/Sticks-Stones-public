#include "movement.hpp"
template<typename DB>
void handle_prowlers(DB& database, std::vector<EntityID>& prowler_indices)
{
				switch (diets[animals[i]])
				{
				case Diet::Herbivore:
				case Diet::Omnivore:
					edible_plant_check(i, directions[i], ran);
					fruit_check(i, directions[i], ran);
				case Diet::Herbivore:
					break;
				case Diet::Scavenger:
					corpse_check(i, directions[i], ran);
				case Diet::Carnivore:
					hunt_check(i, directions[i], ran);
				}
				inertias[i] = calc_speed(mid_speed[animals[i]], coords[i]);
}

void handle_approachers();

void handle_movers();
