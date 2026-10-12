
// TODO: factor in variable distances creating variable chance of hitting
#include "core/random.hpp"
#include "data/run/unit_database.hpp"
#include "data/types/target.hpp"
void update_attacks(unit::Database db)
{
	// precompute attack success and damages

	Arena<bool> attack_success; // ensure arena makes default value
	Arena<float> damages;
	for (int i = 0; i < db.targets.size; i++)
	  {	    	   
		if (db.inertia(i) <= 0 && db.action(i) == Action::Attack)
		{
		    auto ti = db.target(i);
		    Inventory& inventory = db.inventory(i);
 		    if (hit(random_chance->next(), get_weapon(i), stat(i), armor(ti), stat(ti)))
			{
			}
		}
	}
	int j = 0;
	for (int i = 0; i < ; i++)
	{
		if (timer(i) <= 0 && action(i) == Action::Attack)
		{
			auto ti = target(i);
			float &h = health(ti);
			if (attack_success[j++])
				h -= damage[j];
			if (h <= 0.0)
				action(i) = Action::Assign;
		}
	}
}
