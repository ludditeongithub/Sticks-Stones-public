#include "updates.hpp"
#include "core/containers.hpp"
#include "data/types/aliases.hpp"
#include "core/random.hpp"
#include "pathfinding.hpp"
#include "data/types/animal.hpp"
#include "data/const/chunk_data.hpp"
#include "world/plant/tables.hpp"
#include <cstddef>
#include <data/run/plant_database.hpp>
#include "data/run/world.hpp"
#include <data/run/item_database.hpp>
#include <optional>

// TODO: eval water
	// Water
		// float wr = water_required[p];
		// uint16_t wd = water_death[p];
		// if (tile_water[i] > wr) {
		//   last_fully_watered[i] = time;
		// } else if (time - last_fully_watered[i] > wd) {
		//   alive[i] = true;
		//   continue;
		// } else next_growth *= LOW_WATER_MULT;
		

inline void eval_temperature(World& world, int chunk_index, Plant p, float& next_growth, auto&& alive, bool regrowth = false)
{
	float dmin = temp_death_min[p];
		Temp dmax = temp_death_max[p];
		Temp ngmin = temp_growth_min[p];
		Temp ngmax = temp_growth_max[p];
		Temp omin = temp_optimal_min[p];
		Temp omax = temp_optimal_max[p];

		Temp temp = world.temperatures[chunk_index];		
		
		if (temp < omax && temp > omin)
		{
		}
		else if (temp > ngmin && temp < ngmax)
		{
			next_growth = 0.0;
			if (regrowth) next_growth = -1.0;
		}
		else if (temp < dmin || temp > dmax)
		{
			alive = false;			
		}
		else
		{
			next_growth *= UNOPTIMAL_TEMP_MULT;
		}
}

inline void eval_sunlight(World& world, int chunk_index, float& next_growth, Array2D<float>& daily_insolations, Array<float>& cloud_covers, Plant p, bool regrowth = false)
{
		uint16_t latitude = world.get_chunk_latitude(chunk_index);
		uint16_t time_zone = world.get_chunk_time_zone(chunk_index);
		float is = daily_insolations[latitude][time_zone];
		float psun = perfect_sunlight[p];
		// sunlight (from 0.0 to 1.0)
		if (is <= 0.0)
		{
			next_growth = 0.0; 
		}
		else
		{
			// factor cloud cover
			float ccf = cloud_covers[chunk_index] * MAX_CLOUD_FACTOR;
			float sunlight = is / (1 + ccf);
			float sf = 1.0;
			if (sunlight < psun)
				sf = normalize(sunlight, 0, psun);
			next_growth *= sf;
		}
}

// OPTI: have plant temp values be precalcuated so chunk temps is accessed
// faster
void plant::Database::update_plants(World& world, Array2D<float> &daily_insolations, Array<float> &cloud_covers, Time time_passed)
{
	for (uint32_t i = 0; i < plant_list.size(); i++)
	{
		Plant p = plant_list[i];		
		
		if (plant_list[i] == Plant::NONE)
			continue;
		float next_growth = 1.0;
		const Coord pos = coords[i];
		uint32_t chunk_index = get_chunk_index_from_tile(pos);
		eval_sunlight(world, chunk_index, next_growth, world.daily_insolations, world.cloud_covers, p);
		eval_temperature(world, chunk_index, p, next_growth, alive[i]);
		if (!alive[i]) continue;		

		growths[i] += next_growth * time_passed;
	}
}

void Regrowthplant::Database::update_regrowth_plants(item::Database& item_database, World& world, Array<float> &tile_water, Time time_passed)
{
	Array<Plant> &plant_list = plant_database.plant_list;
	
		for (uint32_t i = 0; i < plant_list.size(); i++)
	{
		Plant p = plant_list[i];		
		
		if (plant_list[i] == Plant::NONE) continue;
		float next_growth = 1.0;
		const Coord pos = plant_database.coords[i];
		uint32_t chunk_index = get_chunk_index_from_tile(pos);

		eval_sunlight(world, chunk_index, next_growth, world.daily_insolations, world.cloud_covers, p);
		// sunlight must come before temp, because temp sets next_growth to negative
		// sometimes for regrowth
		eval_temperature(world, chunk_index, p, next_growth, plant_database.alive[i], true);
		if (!plant_database.alive[i]) continue;

		Time& growth = plant_database.growths[i];
		growth += std::fmin(next_growth * time_passed, 0);
		if (growth > max_age[p]) plant_database.alive[i] = false;
		else if (growth > regrowth_start_age[p]) {
			Time &regrowth = regrowths[i];
		if (regrowth <= regrowth_max[p])
			regrowth += next_growth * time_passed;
		uint16_t produce_target = get_produce_current_target(p, regrowths[i], ages[i]);
		uint16_t current_produce = produces[i];
		if (produce_target < current_produce)
		{
			if (fruits_fall[p])
				item_database.drop_fruit(p, pos, current_produce - produce_target);
			regrowths[i] -= regrowths[i] *  static_cast<float>(static_cast<int>(produces[i] - produce_target) / produce_target);
		}		
		produces[i] = produce_target;
		}
	}						
}

void update_alive_plants(plant::Database& database)
{
	for (size_t i = 0; i < database.alive.size(); i++) {
		
	}
}	
