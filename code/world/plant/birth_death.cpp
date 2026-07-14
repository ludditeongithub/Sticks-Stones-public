#include <core/random.hpp>
#include "core/database.hpp"
#include "database.hpp"
#include "tables.hpp"

inline void PlantDatabase::set_germination_time(int seedIndex)
{
	Plant plant = seeds[seedIndex];
	// randomize time based on duration of germination period
	int time = (int)(germinationPeriod[static_cast<int>(plant)] * random_chance->next());
	addEvent(time, EventType::PlantGermination, (int)plant, seedIndex);
}

// Germination is activated randomly as events that start triggering en-masse
// automatically at the time of the year the plant type in question starts
// germinating. Also activates upon world spawn with a randomGrowth to generate
// plants.
inline void PlantDatabase::germinate(int seedIndex, bool randomGrowth, SearchGrid& searchGrid)
{
	Plant plant = seeds[seedIndex];
	Coord coord = seedCoords[seedIndex];
	uint16_t index = nextPlantIndex.top();
	nextPlantIndex.pop();
	plantList[index] = plant;
			growthAmt[index] = 0;
		coords[index] = coord;
		tileWater[index] = 0;
		lastFullyWatered[index] = ;
		
		
		if (randomGrowth)
		{
			growthAmt[index] = random_chance->next() * fullyGrownAmt[plant];
		}
		else growthAmt[index] = 0;
	searchGrid.insertEntity(plant, {index, coord});	
}

inline void RegrowthPlantDatabase::germinate(int seedIndex, bool randomGrowth, SearchGrid& searchGrid)
{
	plantDatabase.germinate(seedIndex, randomGrowth, searchGrid);	
}		

// TODO: consider making this array, so that animals can eat and poop many
// seeds, consider making this in animal database
//  only performs the seed function, and removing the plant object, does not
//  affect the animal
void PlantDatabase::prepare_seed_dropping(int animalIndex, int plantIndex, bool regrowth)
{
	if (tileIndexToPlantIndex.contains(foodTileIndex))
	{
		int index = tileIndexToPlantIndex[foodTileIndex];
		bool regrowth = false;
	}
	else if (regrowthTileIndexToPlantIndex.contains(foodTileIndex))
	{
		int index = tileIndexToRegrowthPlantIndex[foodTileIndex];
		bool regrowth = true;
	}
	else
	{
		sendError("Animal tried to eat plant at tile " + toString(foodTileIndex) +
			  " but no plant was found.");
		return;
	}
	if (regrowth)
	{
		Plant &plant_type = regrowthPlants[index];
	}
	else
		Plant &plant_type = plants[index];
	addEvent(digestionTime, EventType::FutureSeedDropping, (int)plantType, animalIndex);
}

// TODO: complete and render
void PlantDatabase::kill_tree(int plantIndex)
{
	switch (tilePlant[plantIndex])
	{
	case Plant::PioneerTree:
		blockSize = 1;
		break;
	case Plant::DeciduousTree:
		blockSize = 2;
		break;
	case Plant::EvergreenTree:
		blockSize = 3;
		break;
	case Plant::RainforestTree:
		blockSize = 4;
		break;
	default:
		return;
	}
	TileBlock tb = findNearestAdjacentEmptyTileBlock(plantIndex, blockSize);
	std::tuple<int, int, int, int> adjacent_tiles = adjacentTilesIndices[plantIndex];
	tilePlant[plantIndex] = Plant::Stump;
	int new_tile_index;
	for (int i = 1; i < blockSize; i++)
	{
		if (tb.direction == Direction::North)
		{
			new_tile_index = std::get<0>(adjacentTiles);
			adjacentTiles = adjacentTilesIndices;
		}
		if (tb.direction == Direction::South)
		{
			return std::get<2>(adjacentTiles);
		}
		if (tb.direction == Direction::West)
		{
			return std::get<4>(adjacentTiles);
		}
		if (tb.direction == Direction::East)
		{
			return std::get<1>(adjacentTiles);
		}
	}
}

void PlantDatabase::kill_plant(int plantIndex)
{
	Plant plant = tilePlant[tileIndex];
	PlantType type = plants[(int)plant].plantType;

	tileObject[tileObjectIndex] = Plant::None;
	switch (plantType)
	{
	case Tree:
	case FruitTree:
		treeDeath(plantIndex);
	}
}
