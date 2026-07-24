#include <core/random.hpp>
#include "core/database.hpp"
#include "database.hpp"
#include "tables.hpp"

inline void PlantDatabase::set_germination_time(int seed_index)
{
	Plant plant = seeds[seed_index];
	// randomize time based on duration of germination period
	int time = (int)(germination_period[static_cast<int>(plant)] * random_chance->next());
	add_event(time, EventType::PlantGermination, (int)plant, seed_index);
}

// Germination is activated randomly as events that start triggering en-masse
// automatically at the time of the year the plant type in question starts
// germinating. Also activates upon world spawn with a random_growth to generate
// plants.
inline void PlantDatabase::germinate(int seed_index, bool random_growth, SearchGrid& search_grid)
{
	Plant plant = seeds[seed_index];
	Coord coord = seed_coords[seed_index];
	uint16_t index = next_plant_index.top();
	next_plant_index.pop();
	plant_list[index] = plant;
			growth_amt[index] = 0;
		coords[index] = coord;
		tile_water[index] = 0;
		last_fully_watered[index] = ;
		
		
		if (random_growth)
		{
			growth_amt[index] = random_chance->next() * fully_grown_amt[plant];
		}
		else growth_amt[index] = 0;
	search_grid.insert_entity(plant, {index, coord});	
}

inline void RegrowthPlantDatabase::germinate(int seed_index, bool random_growth, SearchGrid& search_grid)
{
	plant_database.germinate(seed_index, random_growth, search_grid);	
}		

// TODO: consider making this array, so that animals can eat and poop many
// seeds, consider making this in animal database
//  only performs the seed function, and removing the plant object, does not
//  affect the animal
void PlantDatabase::prepare_seed_dropping(int animal_index, int plant_index, bool regrowth)
{
	if (tile_index_to_plant_index.contains(food_tile_index))
	{
		int index = tile_index_to_plant_index[food_tile_index];
		bool regrowth = false;
	}
	else if (regrowth_tile_index_to_plant_index.contains(food_tile_index))
	{
		int index = tile_index_to_regrowth_plant_index[food_tile_index];
		bool regrowth = true;
	}
	else
	{
		send_error("Animal tried to eat plant at tile " + to_string(food_tile_index) +
			  " but no plant was found.");
		return;
	}
	if (regrowth)
	{
		Plant &plant_type = regrowth_plants[index];
	}
	else
		Plant &plant_type = plants[index];
	add_event(digestion_time, EventType::FutureSeedDropping, (int)plant_type, animal_index);
}

// TODO: complete and render
void PlantDatabase::kill_tree(int plant_index)
{
	switch (tile_plant[plant_index])
	{
	case Plant::PioneerTree:
		block_size = 1;
		break;
	case Plant::DeciduousTree:
		block_size = 2;
		break;
	case Plant::EvergreenTree:
		block_size = 3;
		break;
	case Plant::RainforestTree:
		block_size = 4;
		break;
	default:
		return;
	}
	TileBlock tb = find_nearest_adjacent_empty_tile_block(plant_index, block_size);
	std::tuple<int, int, int, int> adjacent_tiles = adjacent_tiles_indices[plant_index];
	tile_plant[plant_index] = Plant::Stump;
	int new_tile_index;
	for (int i = 1; i < block_size; i++)
	{
		if (tb.direction == Direction::North)
		{
			new_tile_index = std::get<0>(adjacent_tiles);
			adjacent_tiles = adjacent_tiles_indices;
		}
		if (tb.direction == Direction::South)
		{
			return std::get<2>(adjacent_tiles);
		}
		if (tb.direction == Direction::West)
		{
			return std::get<4>(adjacent_tiles);
		}
		if (tb.direction == Direction::East)
		{
			return std::get<1>(adjacent_tiles);
		}
	}
}

void PlantDatabase::kill_plant(int plant_index)
{
	Plant plant = tile_plant[tile_index];
	PlantType type = plants[(int)plant].plant_type;

	tile_object[tile_object_index] = Plant::None;
	switch (plant_type)
	{
	case Tree:
	case FruitTree:
		tree_death(plant_index);
	}
}
