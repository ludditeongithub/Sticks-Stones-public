#include "movement.hpp"
template<typename DB>
void handle_prowlers(DB& database, std::vector<EntityID>& prowler_indices)
{
				switch (diets[animals[i]])
				{
				case Diet::Herbivore:
				case Diet::Omnivore:
					scan_edible_plant(i, directions[i], ran);
					scan_fruit(i, directions[i], ran);
				case Diet::Herbivore:
					break;
				case Diet::Scavenger:
					scan_corpse(i, directions[i], ran);
				case Diet::Carnivore:
					scan_hunt(i, directions[i], ran);
				}
				inertias[i] = calc_speed(mid_speed[animals[i]], coords[i]);
}

void handle_approachers();

void handle_movers();
