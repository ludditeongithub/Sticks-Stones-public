/*  GUIDELINES FOR SPAWNING
 *   all natural entities must roughly spawn as often as they die in nature to
 * ensure that they are not eliminated or grow too much as the game progresses.
 *
 *   ergo, the formula for annual plant spawning is to just have them spawn with
 * the same formula they used before, since all of the annuals will die in the
 * winter, so an equal chance amount of annuals should spawn next spring, as
 * seeds.
 *
 *   perrenials or multi-year plants should spawn at a randomized growth amount.
 * the formula for their respawns should be their total growth amount (period
 * from ), divided by the respawn period, spread throughout every instance in
 * which plants are able to spawn.
 *
 *   A deterministic plant score is given for each cell, which represents how
 * well the plant grows in that area. This is so that it is generally always the
 * most competitive plants which grow in an area, so that natural-looking
 * clusters form.
 *   */

// TODO: have seed in seeds vector become none upon pick up or consuming animals
// or pawns

// TODO: take data from this method into lookup table. make sure it is
// array-based

// APPLY PLANT SPAWNS - get random value from noise generation
// based on factors:
// biome type
// soil type
// temperature
// humidity
// neighboring plants

#include "first_spawn.hpp"
#include "world/tile/data.hpp"
#include "world/world.hpp"
#include <core/random.hpp>
#include <world/animal/entity.hpp>
#include <world/animal/spawn_tables.hpp>
#include <world/plant/enum.hpp>
#include <world/plant/spawn_tables.hpp>
#include <world/tile/enum.hpp>

// puts into relevant buffer for each
void WorldSpawner::spawnEntities()
{
	// spawn grass and plants
	spawnGrassAndFirstPlants();
	// spawn scavengeables
	spawnScavengeables();
	// spawn animals

	// spawn tribes
}

// TODO: shrink by making lookuptables of spawn chances based on tiles
void WorldSpawner::spawnGrassAndFirstPlants()
{
	bool regrowthPlant = false;
	float chances = 0;
	float p = 0;
	for (int i = 0; i < tsb.tiles.size(); i++)
	{
		switch (tsb.tiles[i])
		{
		case Tile::Ice:
			continue;
			break;
		case Tile::FrozenSoil:
			continue;
			break;
		case Tile::Gravel:
			continue;
			break;
		case Tile::Stone:
			continue;
			break;
		case Tile::ShallowWater:
			continue;
			break;
		case Tile::FlowingWater:
			continue;
			break;
		case Tile::DeepWater:
			continue;
			break;
		case Tile::Sand:
			continue;
			break;
		case Tile::Snow:
			continue;
			break;
		default:
		}

		// TODO: separate mechanism for plants that stay in the same place and
		// those who do not
		//  mechanism to only work on some tsb.tiles for subsequent spawns.
		Coord tile = getTileCoordFromIndex(i);
		float temp = 0.0;
		float threshold = 0.0;
		float optimal = 0.55;
		float great = 0.4;
		float good = 0.25;
		float poorly = 0.05;
		float rarely = 0.01;

		Tile type = tsb.tiles[i];
		Plant plant = Plant::NONE;
		Grass grass = Grass::NONE;
		Biome biome = biomeMap[i / CHUNK_LENGTH][i % CHUNK_LENGTH];
		int temperature = temperatureMap[i / CHUNK_LENGTH][i % CHUNK_LENGTH];
		int humidity = humidityMap[i / CHUNK_LENGTH][i % CHUNK_LENGTH];

		// PLANT CATEGORY RARITIES - chance of each plant type spawning in each
		// biome, on a tile, not adjusted for other checks (trees have higher raw
		// spawn rate due to not being able to spawn next to other trees) the
		// threshold that the random generated number needs to pass to ensure that
		// the plant species even has a chance of competing.

		//% of much non-grass plants appear on tsb.tiles and grass plants
		// respectively

		float plantCoverage = plantCoverages[biome];
		float grassCoverage = grassCoverages[biome];

		const PlantTable &lt = getPlantChanceTable(biome);

		constexpr std::array<Plant, 4> trees = {Plant::DeciduousTree, Plant::EvergreenTree,
							Plant::PioneerTree, Plant::TropicalTree};

		// SPAWN ALL PLANTS
		if (rand() / (float)RAND_MAX < plantCoverage)
		{
			if (rand() / (float)RAND_MAX < lt[trees])
			{
				if (adjCheckList(tileIndex, tilePlant, (int)tile.first,
						 (int)tile.second, trees, 1))
				{
					// TREES
					// if tree is adjacent, skip trees
					// Deciduous
					temp = 0;
					if (type == Tile::Podzol)
						temp += poorly;
					if (type == Tile::LoamSoil)
						temp += optimal;
					if (type == Tile::PeatSoil)
						temp += poorly;
					if (type == Tile::SandySoil)
						temp += poorly;
					if (type == Tile::ClaySoil)
						temp += poorly;
					if (type == Tile::SiltySoil)
						temp += optimal;
					if (type == Tile::RockySoil)
						temp = 0;
					if (type == Tile::AridSoil)
						temp += poorly;
					if (type == Tile::Oxisol)
						temp += poorly;
					if (type == Tile::Gleysol)
						temp += rarely;
					temp = rangePenalty(temperature, 64, 77, temp);
					temp = rangePenalty(humidity, 52, 78, temp);
					if (temp > threshold)
					{
						threshold = temp;
						plant = Plant::DeciduousTree;
					}

					// Evergreen
					temp = 0;
					if (type == Tile::Podzol)
						temp += good;
					if (type == Tile::LoamSoil)
						temp += good;
					if (type == Tile::PeatSoil)
						temp += poorly;
					if (type == Tile::SandySoil)
						temp += good;
					if (type == Tile::ClaySoil)
						temp += poorly;
					if (type == Tile::SiltySoil)
						temp += good;
					if (type == Tile::RockySoil)
						temp += poorly;
					if (type == Tile::AridSoil)
						temp += rarely;
					if (type == Tile::Oxisol)
						temp += poorly;
					if (type == Tile::Gleysol)
						temp += poorly;
					temp = rangePenalty(temperature, 46, 68, temp);
					temp = rangePenalty(humidity, 60, 87, temp);
					if (temp > threshold)
					{
						threshold = temp;
						plant = Plant::EvergreenTree;
					}

					// Pioneer
					temp = 0;
					if (type == Tile::Podzol)
						temp += rarely;
					if (type == Tile::LoamSoil)
						temp += optimal;
					if (type == Tile::PeatSoil)
						temp += great;
					if (type == Tile::SandySoil)
						temp += good;
					if (type == Tile::ClaySoil)
						temp += poorly;
					if (type == Tile::SiltySoil)
						temp += optimal;
					if (type == Tile::RockySoil)
						temp += rarely;
					if (type == Tile::AridSoil)
						temp += poorly;
					if (type == Tile::Oxisol)
						temp += poorly;
					if (type == Tile::Gleysol)
						temp += great;
					temp = rangePenalty(temperature, 55, 86, temp);
					temp = rangePenalty(humidity, 50, 80, temp);
					if (temp > threshold && plant != Plant::EvergreenTree &&
					    plant != Plant::DeciduousTree)
					{
						threshold = temp;
						plant = Plant::PioneerTree;
					}
					// Tropical
					temp = 0;
					if (type == Tile::Podzol)
						temp += poorly;
					if (type == Tile::LoamSoil)
						temp += optimal;
					if (type == Tile::PeatSoil)
						temp += optimal;
					if (type == Tile::SandySoil)
						temp += good;
					if (type == Tile::ClaySoil)
						temp += poorly;
					if (type == Tile::SiltySoil)
						temp += good;
					if (type == Tile::RockySoil)
						temp = 0;
					if (type == Tile::AridSoil)
						temp += poorly;
					if (type == Tile::Oxisol)
						temp += optimal;
					if (type == Tile::Gleysol)
						temp += optimal;
					temp = rangePenalty(temperature, 73, 87, temp);
					temp = rangePenalty(humidity, 80, 120, temp);
					if (temp > threshold)
					{
						threshold = temp;
						plant = Plant::TropicalTree;
					}
				}
			}

			if (rand() / (float)RAND_MAX < lt[Moss])
			{
				// Moss
				temp = 0;
				if (type == Tile::Podzol)
					temp += great;
				if (type == Tile::LoamSoil)
					temp += great;
				if (type == Tile::PeatSoil)
					temp += optimal;
				if (type == Tile::SandySoil)
					temp += good;
				if (type == Tile::ClaySoil)
					temp += good;
				if (type == Tile::SiltySoil)
					temp += great;
				if (type == Tile::RockySoil)
					temp += great;
				if (type == Tile::AridSoil)
					temp = 0;
				if (type == Tile::Oxisol)
					temp += poorly;
				if (type == Tile::Gleysol)
					temp += optimal;
				temp = rangePenalty(temperature, 40, 75, temp);
				temp = rangePenalty(humidity, 85, 120, temp);
				if (temp > threshold)
				{
					threshold = temp;
					plant = Plant::Moss;
				}
			}
			if (rand() / (float)RAND_MAX < lt[Bush])
			{
				// BUSHES
				if (type == Tile::Podzol)
					temp += optimal;
				if (type == Tile::LoamSoil)
					temp += optimal;
				if (type == Tile::PeatSoil)
					temp += great;
				if (type == Tile::SandySoil)
					temp += good;
				if (type == Tile::ClaySoil)
					temp += good;
				if (type == Tile::SiltySoil)
					temp += great;
				if (type == Tile::RockySoil)
					temp += poorly;
				if (type == Tile::AridSoil)
					temp += rarely;
				if (type == Tile::Oxisol)
					temp += great;
				if (type == Tile::Gleysol)
					temp += great;
				temp = rangePenalty(temperature, 45, 86, temp);
				temp = rangePenalty(humidity, 60, 87, temp);
				if (temp > threshold)
				{
					threshold = temp;
					plant = Plant::Bush;
				}
			}
			if (rand() / (float)RAND_MAX < lt[Succulent])
			{
				// Cacti
				temp = 0;
				if (type == Tile::Podzol)
					temp += rarely;
				if (type == Tile::LoamSoil)
					temp += great;
				if (type == Tile::PeatSoil)
					temp += poorly;
				if (type == Tile::SandySoil)
					temp += optimal;
				if (type == Tile::ClaySoil)
					temp += good;
				if (type == Tile::SiltySoil)
					temp += great;
				if (type == Tile::RockySoil)
					temp += good;
				if (type == Tile::AridSoil)
					temp += optimal;
				if (type == Tile::Oxisol)
					temp += great;
				if (type == Tile::Gleysol)
					temp += rarely;
				temp = rangePenalty(temperature, 45, 86, temp);
				temp = rangePenalty(humidity, 1, 30, temp);
				if (temp > threshold)
				{
					threshold = temp;
					plant = Plant::Cactus;
				}
			}

			// FRUIT TREES
			if (rand() / (float)RAND_MAX < lt[Citrus])
			{
				// Citrus
				temp = 0;
				if (type == Tile::Podzol)
					temp += poorly;
				if (type == Tile::LoamSoil)
					temp += optimal;
				if (type == Tile::PeatSoil)
					temp += good;
				if (type == Tile::SandySoil)
					temp += great;
				if (type == Tile::ClaySoil)
					temp += poorly;
				if (type == Tile::SiltySoil)
					temp += great;
				if (type == Tile::RockySoil)
					temp += rarely;
				if (type == Tile::AridSoil)
					temp += rarely;
				if (type == Tile::Oxisol)
					temp += poorly;
				if (type == Tile::Gleysol)
					temp += poorly;
				temp = rangePenalty(temperature, 70, 80, temp);
				temp = rangePenalty(humidity, 60, 75, temp);
				if (temp > threshold)
				{
					threshold = temp;
					int ran = rint(0, 2);
					if (ran == 0)
						plant = Plant::OrangeTree;
					if (ran == 1)
						plant = Plant::LemonTree;
					if (ran == 2)
						plant = Plant::LimeTree;
				}
			}
			if (rand() / (float)RAND_MAX < lt[Stone])
			{
				// Stone/Drupe
				temp = 0;
				if (type == Tile::Podzol)
					temp += poorly;
				if (type == Tile::LoamSoil)
					temp += optimal;
				if (type == Tile::PeatSoil)
					temp += good;
				if (type == Tile::SandySoil)
					temp += great;
				if (type == Tile::ClaySoil)
					temp += poorly;
				if (type == Tile::SiltySoil)
					temp += great;
				if (type == Tile::RockySoil)
					temp += rarely;
				if (type == Tile::AridSoil)
					temp += rarely;
				if (type == Tile::Oxisol)
					temp += poorly;
				if (type == Tile::Gleysol)
					temp += poorly;
				temp = rangePenalty(temperature, 60, 75, temp);
				temp = rangePenalty(humidity, 45, 68, temp);
				if (temp > threshold)
				{
					threshold = temp;
					int ran = rint(0, 3);
					if (ran == 0)
						plant = Plant::PeachTree;
					if (ran == 1)
						plant = Plant::PlumTree;
					if (ran == 2)
						plant = Plant::CherryTree;
					if (ran == 3)
						plant = Plant::ApricotTree;
				}
			}
			if (rand() / (float)RAND_MAX < lt[Pome])
			{
				// Pome
				temp = 0;
				if (type == Tile::Podzol)
					temp += poorly;
				if (type == Tile::LoamSoil)
					temp += optimal;
				if (type == Tile::PeatSoil)
					temp += good;
				if (type == Tile::SandySoil)
					temp += great;
				if (type == Tile::ClaySoil)
					temp += poorly;
				if (type == Tile::SiltySoil)
					temp += great;
				if (type == Tile::RockySoil)
					temp += rarely;
				if (type == Tile::AridSoil)
					temp += rarely;
				if (type == Tile::Oxisol)
					temp += poorly;
				if (type == Tile::Gleysol)
					temp += poorly;
				temp = rangePenalty(temperature, 55, 72, temp);
				temp = rangePenalty(humidity, 55, 75, temp);
				if (temp > threshold)
				{
					threshold = temp;
					int ran = rint(0, 1);
					if (ran == 0)
						plant = Plant::AppleTree;
					if (ran == 1)
						plant = Plant::PearTree;
				}
			}
			if (rand() / (float)RAND_MAX < lt[Olive])
			{
				// Olive Trees
				temp = 0;
				if (type == Tile::Podzol)
					temp += rarely;
				if (type == Tile::LoamSoil)
					temp += great;
				if (type == Tile::PeatSoil)
					temp += rarely;
				if (type == Tile::SandySoil)
					temp += optimal;
				if (type == Tile::ClaySoil)
					temp += rarely;
				if (type == Tile::SiltySoil)
					temp += great;
				if (type == Tile::RockySoil)
					temp += good;
				if (type == Tile::AridSoil)
					temp += optimal;
				if (type == Tile::Oxisol)
					temp += poorly;
				if (type == Tile::Gleysol)
					temp += rarely;
				temp = rangePenalty(temperature, 61, 80, temp);
				temp = rangePenalty(humidity, 33, 58, temp);
				if (temp > threshold)
				{
					threshold = temp;
					plant = Plant::OliveTree;
				}
			}

			if (rand() / (float)RAND_MAX < lt[BerryShrub])
			{
				// Berry Shrubs
				temp = 0;
				if (type == Tile::Podzol)
					temp += good;
				if (type == Tile::LoamSoil)
					temp += optimal;
				if (type == Tile::PeatSoil)
					temp += great;
				if (type == Tile::SandySoil)
					temp += good;
				if (type == Tile::ClaySoil)
					temp += poorly;
				if (type == Tile::SiltySoil)
					temp += great;
				if (type == Tile::RockySoil)
					temp += rarely;
				if (type == Tile::AridSoil)
					temp += rarely;
				if (type == Tile::Oxisol)
					temp += poorly;
				if (type == Tile::Gleysol)
					temp += good;
				temp = rangePenalty(temperature, 61, 75, temp);
				temp = rangePenalty(humidity, 65, 90, temp);
				if (temp > threshold)
				{
					threshold = temp;
					int ran = rint(0, 3);
					if (ran == 0)
						plant = Plant::BlueberryShrub;
					if (ran == 1)
						plant = Plant::StrawberryShrub;
				}
			}
			if (rand() / (float)RAND_MAX < lt[Grapevine])
			{
				// Grapevines
				temp = 0;
				if (type == Tile::Podzol)
					temp += rarely;
				if (type == Tile::LoamSoil)
					temp += optimal;
				if (type == Tile::PeatSoil)
					temp += good;
				if (type == Tile::SandySoil)
					temp += great;
				if (type == Tile::ClaySoil)
					temp += poorly;
				if (type == Tile::SiltySoil)
					temp += great;
				if (type == Tile::RockySoil)
					temp += good;
				if (type == Tile::AridSoil)
					temp += good;
				if (type == Tile::Oxisol)
					temp += poorly;
				if (type == Tile::Gleysol)
					temp += rarely;
				temp = rangePenalty(temperature, 61, 80, temp);
				temp = rangePenalty(humidity, 45, 68, temp);
				if (temp > threshold)
				{
					threshold = temp;
					plant = Plant::Grapevine;
				}
			}
			if (rand() / (float)RAND_MAX < lt[Grain])
			{
				// GRAINS
				//  Wheat
				temp = 0;
				if (type == Tile::Podzol)
					temp += poorly;
				if (type == Tile::LoamSoil)
					temp += optimal;
				if (type == Tile::PeatSoil)
					temp += good;
				if (type == Tile::SandySoil)
					temp += good;
				if (type == Tile::ClaySoil)
					temp += good;
				if (type == Tile::SiltySoil)
					temp += good;
				if (type == Tile::RockySoil)
					temp += poorly;
				if (type == Tile::AridSoil)
					temp += poorly;
				if (type == Tile::Oxisol)
					temp += poorly;
				if (type == Tile::Gleysol)
					temp += rarely;

				temp = rangePenalty(temperature, 58, 75, temp);
				temp = rangePenalty(humidity, 45, 70, temp);

				if (temp > threshold)
				{
					threshold = temp;
					plant = Plant::Wheat;
				}

				// Rice
				temp = 0;
				if (type == Tile::Podzol)
					temp += poorly;
				if (type == Tile::LoamSoil)
					temp += good;
				if (type == Tile::PeatSoil)
					temp += great;
				if (type == Tile::SandySoil)
					temp += poorly;
				if (type == Tile::ClaySoil)
					temp += optimal;
				if (type == Tile::SiltySoil)
					temp += optimal;
				if (type == Tile::RockySoil)
					temp += poorly;
				if (type == Tile::AridSoil)
					temp += poorly;
				if (type == Tile::Oxisol)
					temp += poorly;
				if (type == Tile::Gleysol)
					temp += great;

				temp = rangePenalty(temperature, 75, 92, temp);
				temp = rangePenalty(humidity, 75, 100, temp);
				if (temp > threshold)
				{
					threshold = temp;
					plant = Plant::Rice;
				}
				// Oat
				temp = 0;
				if (type == Tile::Podzol)
					temp += rarely;
				if (type == Tile::LoamSoil)
					temp += optimal;
				if (type == Tile::PeatSoil)
					temp += good;
				if (type == Tile::SandySoil)
					temp += great;
				if (type == Tile::ClaySoil)
					temp += poorly;
				if (type == Tile::SiltySoil)
					temp += good;
				if (type == Tile::RockySoil)
					temp += good;
				if (type == Tile::AridSoil)
					temp += good;
				if (type == Tile::Oxisol)
					temp += poorly;
				if (type == Tile::Gleysol)
					temp += rarely;

				temp = rangePenalty(temperature, 61, 80, temp);
				temp = rangePenalty(humidity, 45, 68, temp);

				if (temp > threshold)
				{
					threshold = temp;
					plant = Plant::Oat;
				}
			}

			// VEGETABLES
			if (rand() / (float)RAND_MAX < lt[Leafy])
			{
				temp = 0;
				// Leafy Vegetables
				if (type == Tile::Podzol)
					temp += good;
				if (type == Tile::LoamSoil)
					temp += optimal;
				if (type == Tile::PeatSoil)
					temp += great;
				if (type == Tile::SandySoil)
					temp += poorly;
				if (type == Tile::ClaySoil)
					temp += good;
				if (type == Tile::SiltySoil)
					temp += optimal;
				if (type == Tile::RockySoil)
					temp += rarely;
				if (type == Tile::AridSoil)
					temp += rarely;
				if (type == Tile::Oxisol)
					temp += poorly;
				if (type == Tile::Gleysol)
					temp += great;
				temp = rangePenalty(temperature, 50, 72, temp);
				temp = rangePenalty(humidity, 65, 88, temp);
				if (temp > threshold)
				{
					threshold = temp;
					int ran = rint(0, 1);
					if (ran == 0)
						plant = Plant::Lettuce;
					if (ran == 1)
						plant = Plant::Kale;
				}
			}
			if (rand() / (float)RAND_MAX < lt[Root])
			{
				temp = 0;
				// Root Vegetables
				if (type == Tile::Podzol)
					temp += good;
				if (type == Tile::LoamSoil)
					temp += optimal;
				if (type == Tile::PeatSoil)
					temp += poorly;
				if (type == Tile::SandySoil)
					temp += great;
				if (type == Tile::ClaySoil)
					temp += poorly;
				if (type == Tile::SiltySoil)
					temp += good;
				if (type == Tile::RockySoil)
					temp += rarely;
				if (type == Tile::AridSoil)
					temp += rarely;
				if (type == Tile::Oxisol)
					temp += poorly;
				if (type == Tile::Gleysol)
					temp += rarely;
				temp = rangePenalty(temperature, 56, 69, temp);
				temp = rangePenalty(humidity, 55, 78, temp);
				if (temp > threshold)
				{
					threshold = temp;
					int ran = rint(0, 1);
					if (ran == 0)
						plant = Plant::Carrot;
					if (ran == 1)
						plant = Plant::Beets;
				}
			}
			if (rand() / (float)RAND_MAX < lt[Tuber])
			{
				temp = 0;
				// Tubers
				if (type == Tile::Podzol)
					temp += good;
				if (type == Tile::LoamSoil)
					temp += great;
				if (type == Tile::PeatSoil)
					temp += poorly;
				if (type == Tile::SandySoil)
					temp += optimal;
				if (type == Tile::ClaySoil)
					temp += poorly;
				if (type == Tile::SiltySoil)
					temp += good;
				if (type == Tile::RockySoil)
					temp += rarely;
				if (type == Tile::AridSoil)
					temp += rarely;
				if (type == Tile::Oxisol)
					temp += poorly;
				if (type == Tile::Gleysol)
					temp += rarely;
				temp = rangePenalty(temperature, 60, 67, temp);
				temp = rangePenalty(humidity, 65, 88, temp);
				if (temp > threshold)
				{
					threshold = temp;
					plant = Plant::Potatoes;
				}
			}
			if (rand() / (float)RAND_MAX < lt[Bulb])
			{
				// Bulbs
				if (type == Tile::Podzol)
					temp += good;
				if (type == Tile::LoamSoil)
					temp += optimal;
				if (type == Tile::PeatSoil)
					temp += poorly;
				if (type == Tile::SandySoil)
					temp += great;
				if (type == Tile::ClaySoil)
					temp += poorly;
				if (type == Tile::SiltySoil)
					temp += good;
				if (type == Tile::RockySoil)
					temp += rarely;
				if (type == Tile::AridSoil)
					temp += rarely;
				if (type == Tile::Oxisol)
					temp += poorly;
				if (type == Tile::Gleysol)
					temp += rarely;
				temp = rangePenalty(temperature, 60, 70, temp);
				temp = rangePenalty(humidity, 55, 77, temp);
				if (temp > threshold)
				{
					threshold = temp;
					int ran = rint(0, 1);
					if (ran == 0)
						plant = Plant::Onion;
					if (ran == 1)
						plant = Plant::Garlic;
				}
			}
			if (rand() / (float)RAND_MAX < lt[Flowering])
			{
				// Flowering Vegetables
				if (type == Tile::Podzol)
					temp += good;
				if (type == Tile::LoamSoil)
					temp += optimal;
				if (type == Tile::PeatSoil)
					temp += poorly;
				if (type == Tile::SandySoil)
					temp += good;
				if (type == Tile::ClaySoil)
					temp += poorly;
				if (type == Tile::SiltySoil)
					temp += great;
				if (type == Tile::RockySoil)
					temp += rarely;
				if (type == Tile::AridSoil)
					temp += rarely;
				if (type == Tile::Oxisol)
					temp += poorly;
				if (type == Tile::Gleysol)
					temp += rarely;
				temp = rangePenalty(temperature, 56, 67, temp);
				temp = rangePenalty(humidity, 65, 88, temp);
				if (temp > threshold)
				{
					threshold = temp;
					int ran = rint(0, 1);
					if (ran == 0)
						plant = Plant::Cabbage;
					if (ran == 1)
						plant = Plant::Broccoli;
				}
			}
			if (rand() / (float)RAND_MAX < lt[FruitVeggie])
			{
				// Fruit Vegetables
				if (type == Tile::Podzol)
					temp += good;
				if (type == Tile::LoamSoil)
					temp += optimal;
				if (type == Tile::PeatSoil)
					temp += poorly;
				if (type == Tile::SandySoil)
					temp += great;
				if (type == Tile::ClaySoil)
					temp += poorly;
				if (type == Tile::SiltySoil)
					temp += good;
				if (type == Tile::RockySoil)
					temp += rarely;
				if (type == Tile::AridSoil)
					temp += rarely;
				if (type == Tile::Oxisol)
					temp += poorly;
				if (type == Tile::Gleysol)
					temp += rarely;
				temp = rangePenalty(temperature, 69, 81, temp);
				temp = rangePenalty(humidity, 55, 78, temp);
				if (temp > threshold)
				{
					threshold = temp;
					int ran = rint(0, 2);
					if (ran == 0)
						plant = Plant::Tomato;
					if (ran == 1)
						plant = Plant::Cucumber;
					if (ran == 2)
						plant = Plant::Pepper;
				}
			}

			// // Seed and Pod Vegetables
			// if (type == Tile::Podzol) temp += good;
			// if (type == Tile::LoamSoil) temp += optimal;
			// if (type == Tile::PeatSoil) temp += poorly;
			// if (type == Tile::SandySoil) temp += great;
			// if (type == Tile::ClaySoil) temp += poorly;
			// if (type == Tile::SiltySoil) temp += good;
			// if (type == Tile::RockySoil) temp += rarely;
			// if (type == Tile::AridSoil) temp += rarely;
			// if (type == Tile::Oxisol) temp += poorly;
			// if (type == Tile::Gleysol) temp += rarely;
			// temp = rangePenalty(temperature, 56, 70, temp);
			// temp = rangePenalty(humidity, 55, 78, temp);
			// if (temp > threshold) {
			//              threshold = temp;
			//              int ran = rint(0,2);
			//              if (ran == 0) plant = Plant::Peas;
			//              if (ran == 1) plant = Plant::Beans;
			//        }

			// HERBS
			if (rand() / (float)RAND_MAX < lt[Herb])
			{
				// Sun-Loving Herbs
				if (type == Tile::Podzol)
					temp += poorly;
				if (type == Tile::LoamSoil)
					temp += optimal;
				if (type == Tile::PeatSoil)
					temp += poorly;
				if (type == Tile::SandySoil)
					temp += great;
				if (type == Tile::ClaySoil)
					temp += poorly;
				if (type == Tile::SiltySoil)
					temp += good;
				if (type == Tile::RockySoil)
					temp += rarely;
				if (type == Tile::AridSoil)
					temp += rarely;
				if (type == Tile::Oxisol)
					temp += poorly;
				temp = rangePenalty(temperature, 70, 90, temp);
				temp = rangePenalty(humidity, 40, 60, temp);
				if (temp > threshold)
				{
					threshold = temp;
					int ran = rint(0, 2);
					if (ran == 0)
						plant = Plant::Woad;
					if (ran == 1)
						plant = Plant::Indigo;
					if (ran == 2)
						plant = Plant::Poppy;
				}
				// Shade-Loving Herbs
				if (type == Tile::Podzol)
					temp += good;
				if (type == Tile::LoamSoil)
					temp += optimal;
				if (type == Tile::PeatSoil)
					temp += great;
				if (type == Tile::SandySoil)
					temp += poorly;
				if (type == Tile::ClaySoil)
					temp += good;
				if (type == Tile::SiltySoil)
					temp += good;
				if (type == Tile::RockySoil)
					temp += rarely;
				if (type == Tile::AridSoil)
					temp += rarely;
				if (type == Tile::Oxisol)
					temp += poorly;
				temp = rangePenalty(temperature, 50, 70, temp);
				temp = rangePenalty(humidity, 60, 80, temp);
				if (temp > threshold)
				{
					threshold = temp;
					int ran = rint(0, 1);
					if (ran == 0)
						plant = Plant::Hemp;
					if (ran == 1)
						plant = Plant::Ginseng;
				}
				// Drought-Tolerant Herbs (Low Water Requirements)
				if (type == Tile::Podzol)
					temp += poorly;
				if (type == Tile::LoamSoil)
					temp += optimal;
				if (type == Tile::PeatSoil)
					temp += poorly;
				if (type == Tile::SandySoil)
					temp += great;
				if (type == Tile::ClaySoil)
					temp += poorly;
				if (type == Tile::SiltySoil)
					temp += good;
				if (type == Tile::RockySoil)
					temp += rarely;
				if (type == Tile::AridSoil)
					temp += great;
				if (type == Tile::Oxisol)
					temp += poorly;
				temp = rangePenalty(temperature, 70, 100, temp);
				temp = rangePenalty(humidity, 20, 40, temp);
				if (temp > threshold)
				{
					threshold = temp;
					int ran = rint(0, 2);
					if (ran == 0)
						plant = Plant::Lavendar;
					if (ran == 1)
						plant = Plant::Sage;
					if (ran == 2)
						plant = Plant::Madder;
				}
				// Moisture-Loving Herbs
				if (type == Tile::Podzol)
					temp += great;
				if (type == Tile::LoamSoil)
					temp += optimal;
				if (type == Tile::PeatSoil)
					temp += great;
				if (type == Tile::SandySoil)
					temp += poorly;
				if (type == Tile::ClaySoil)
					temp += good;
				if (type == Tile::SiltySoil)
					temp += great;
				if (type == Tile::RockySoil)
					temp += rarely;
				if (type == Tile::AridSoil)
					temp += poorly;
				if (type == Tile::Oxisol)
					temp += poorly;
				temp = rangePenalty(temperature, 60, 80, temp);
				temp = rangePenalty(humidity, 60, 80, temp);
				if (temp > threshold)
				{
					threshold = temp;
					plant = Plant::Mint;
				}
				// Cold-Hardy Herbs (Cold-Tolerant)
				if (type == Tile::Podzol)
					temp += great;
				if (type == Tile::LoamSoil)
					temp += optimal;
				if (type == Tile::PeatSoil)
					temp += good;
				if (type == Tile::SandySoil)
					temp += poorly;
				if (type == Tile::ClaySoil)
					temp += good;
				if (type == Tile::SiltySoil)
					temp += good;
				if (type == Tile::RockySoil)
					temp += rarely;
				if (type == Tile::AridSoil)
					temp += rarely;
				if (type == Tile::Oxisol)
					temp += poorly;
				temp = rangePenalty(temperature, 40, 60, temp);
				temp = rangePenalty(humidity, 40, 60, temp);
				if (temp > threshold)
				{
					threshold = temp;
					plant = Plant::Thyme;
				}
			}
			// TEXTILE
			if (rand() / (float)RAND_MAX < lt[Textile])
			{
				temp = 0;
				if (type == Tile::Podzol)
					temp += poorly;
				if (type == Tile::LoamSoil)
					temp += optimal;
				if (type == Tile::PeatSoil)
					temp += poorly;
				if (type == Tile::SandySoil)
					temp += great;
				if (type == Tile::ClaySoil)
					temp += poorly;
				if (type == Tile::SiltySoil)
					temp += good;
				if (type == Tile::RockySoil)
					temp += rarely;
				if (type == Tile::AridSoil)
					temp += rarely;
				if (type == Tile::Oxisol)
					temp += poorly;
				temp = rangePenalty(temperature, 60, 79, temp);
				temp = rangePenalty(humidity, 55, 78, temp);
				if (temp > threshold)
				{
					threshold = temp;
					int ran = rint(0, 2);
					if (ran == 0)
						plant = Plant::Cotton;
					if (ran == 1)
						plant = Plant::Hemp;
					if (ran == 2)
						plant = Plant::Flax;
				}
			}
			if (rand() / (float)RAND_MAX < lt[Fern])
			{
				temp = 0;
				// Ferns
				if (biome == 4)
					temp += 0.3;
				if (biome == 5)
					temp += 0.2;
				if (biome == 6)
					temp += 0.2;
				if (biome == 7)
					temp += 0.3;
				if (biome == 8)
					temp += 0.2;
				if (type == Tile::Podzol)
					temp += great;
				if (type == Tile::LoamSoil)
					temp += optimal;
				if (type == Tile::PeatSoil)
					temp += optimal;
				if (type == Tile::SandySoil)
					temp += poorly;
				if (type == Tile::ClaySoil)
					temp += rarely;
				if (type == Tile::SiltySoil)
					temp += great;
				if (type == Tile::RockySoil)
					temp += rarely;
				if (type == Tile::AridSoil)
					temp = 0;
				if (type == Tile::Oxisol)
					temp += poorly;
				if (type == Tile::Gleysol)
					temp += great;
				temp = rangePenalty(temperature, 50, 77, temp);
				temp = rangePenalty(humidity, 75, 115, temp);
				if (temp > threshold)
				{
					threshold = temp;
					plant = Plant::Fern;
				}
			}
			if (rand() / (float)RAND_MAX < lt[Reed])
			{
				temp = 0;
				// Reeds
				if (biome == 4)
					temp += 0.15;
				if (adjCheck(tileIndex, tileType, (int)tile.first, (int)tile.second,
					     Tile::ShallowWater, 1))
					temp += 0.45;
				if (type == Tile::Podzol)
					temp += good;
				if (type == Tile::LoamSoil)
					temp += great;
				if (type == Tile::PeatSoil)
					temp += optimal;
				if (type == Tile::SandySoil)
					temp += poorly;
				if (type == Tile::ClaySoil)
					temp += good;
				if (type == Tile::SiltySoil)
					temp += great;
				if (type == Tile::RockySoil)
					temp += poorly;
				if (type == Tile::AridSoil)
					temp = 0;
				if (type == Tile::Oxisol)
					temp += poorly;
				if (type == Tile::Gleysol)
					temp += optimal;
				temp = rangePenalty(temperature, 50, 86, temp);
				temp = rangePenalty(humidity, 75, 120, temp);
				if (temp > threshold)
				{
					threshold = temp;
					plant = Plant::Reed;
				}
			}
		} // end of plants, checking random value against plant coverage
		// GRASSES
		if (rand() / (float)RAND_MAX < grassCoverage)
		{
			temp = 0;
			threshold = 0;
			// Prairie Grasses
			temp += 0.2;
			temp -= (0.05 * adjCheckListCount(tileIndex, tilePlant, (int)tile.first,
							  (int)tile.second, trees, 3));
			if (biome == 2)
				temp += 0.45;
			if (biome == 4)
				temp += 0.05;
			if (type == Tile::Podzol)
				temp += good;
			if (type == Tile::LoamSoil)
				temp += optimal;
			if (type == Tile::PeatSoil)
				temp += rarely;
			if (type == Tile::SandySoil)
				temp += great;
			if (type == Tile::ClaySoil)
				temp += poorly;
			if (type == Tile::SiltySoil)
				temp += optimal;
			if (type == Tile::RockySoil)
				temp += rarely;
			if (type == Tile::AridSoil)
				temp += good;
			if (type == Tile::Oxisol)
				temp += poorly;
			if (type == Tile::Gleysol)
				temp += poorly;
			temp = rangePenalty(temperature, 41, 86, temp);
			temp = rangePenalty(humidity, 30, 80, temp);
			if (temp > threshold)
			{
				threshold = temp;
				grass = Grass::Grass;
			}
			// Savannah Grasses
			temp = 0;
			temp += 0.2;
			temp -= (0.05 * adjCheckListCount(tileIndex, tilePlant, (int)tile.first,
							  (int)tile.second, trees, 3));
			if (biome == 3)
				temp += 0.5;
			if (type == Tile::Podzol)
				temp += poorly;
			if (type == Tile::LoamSoil)
				temp += great;
			if (type == Tile::PeatSoil)
				temp += rarely;
			if (type == Tile::SandySoil)
				temp += optimal;
			if (type == Tile::ClaySoil)
				temp += good;
			if (type == Tile::SiltySoil)
				temp += great;
			if (type == Tile::RockySoil)
				temp += rarely;
			if (type == Tile::AridSoil)
				temp += good;
			if (type == Tile::Oxisol)
				temp += good;
			if (type == Tile::Gleysol)
				temp += poorly;
			temp = rangePenalty(temperature, 64, 95, temp);
			temp = rangePenalty(humidity, 20, 60, temp);

			if (temp > threshold)
			{
				threshold = temp;
				grass = Grass::SavannahGrass;
			}
		}
		tileGrass[i] = grass;
		if (plants != Plant::NONE)
			psb.add(plant, coord);
	}
}

// TODO: move data into lookup table. possibly spawn animals per chunk instead
// of per tile!
//  APPLY ANIMAL SPAWNS
AnimalSpawnBuffer WorldSpawner::spawnAnimals(SearchGrid &sg)
{
	AnimalSpawnBuffer asb;
	asb.types.reserve(TILE_AMOUNT);
	asb.coords.reserve(TILE_AMOUNT);

	for (int i = 0; i < TILE_AMOUNT; i++)
	{
		// TODO: water animals
	 if (isWater(tsb.tiles[i]) continue;
         if (sg.isOccupied(i)) continue;
         Coord coord = getTileCoordFromIndex(i);
         Coord chunkCoord = getChunkFromTile(coord);
	 // skip if within player chunk bounds -- animals within player bounds managed separately         
	 if (chunkCoord.x >= playerChunkBorderWest && chunkCoord.x <= playerChunkBorderEast && chunkCoord.y >= playerChunkBorderNorth && chunkCoord.y <= playerChunkBorderSouth) continue;
         int biome = biomeChunk[chunkCoord.first][chunkCoord.second];

	 float currentChance = 0;
         float random = nextRandomPropFrac();

         asb.size++; // size is subtracted at the end if no animal added.
                  
	 //make more efficient by adding up total chance of all anial spawns, just skipping if less than that chance         
if (random < currentChance + pigChance) {
			asb.types.emplace_back(Animal::Pig);
			asb.coords.emplace_back(coord);
}
else if (random < (currentChance += pigChance) + cowChance) {
			asb.types.emplace_back(Animal::Cow);
			asb.coords.emplace_back(coord);
}
else if (random < (currentChance += cowChance) + chickenChance) {
			asb.types.emplace_back(Animal::Chicken);
			asb.coords.emplace_back(coord);
}
else if (random < (currentChance += chickenChance) + duckChance) {
			asb.types.emplace_back(Animal::Duck);
			asb.coords.emplace_back(coord);
}
else if (random < (currentChance += duckChance) + sheepChance) {
			asb.types.emplace_back(Animal::Sheep);
			asb.coords.emplace_back(coord);
}
else if (random < (currentChance += sheepChance) + goatChance) {
			asb.types.emplace_back(Animal::Goat);
			asb.coords.emplace_back(coord);
}
else if (random < (currentChance += goatChance) + horseChance) {
			asb.types.emplace_back(Animal::Horse);
			asb.coords.emplace_back(coord);
}
else if (random < (currentChance += horseChance) + oxChance) {
			asb.types.emplace_back(Animal::Ox);
			asb.coords.emplace_back(coord);
}
else if (random < (currentChance += oxChance) + donkeyChance) {
			asb.types.emplace_back(Animal::Donkey);
			asb.coords.emplace_back(coord);
}
else if (random < (currentChance += donkeyChance) + camelChance) {
			asb.types.emplace_back(Animal::Camel);
			asb.coords.emplace_back(coord);
}
else if (random < (currentChance += camelChance) + waterBuffaloChance) {
			asb.types.emplace_back(Animal::WaterBuffalo);
			asb.coords.emplace_back(coord);
}
else if (random < (currentChance += waterBuffaloChance) + rabbitChance) {
			asb.types.emplace_back(Animal::Rabbit);
			asb.coords.emplace_back(coord);
}
else if (random < (currentChance += rabbitChance) + antelopeChance) {
			asb.types.emplace_back(Animal::Antelope);
			asb.coords.emplace_back(coord);
}
else if (random < (currentChance += antelopeChance) + deerChance) {
			asb.types.emplace_back(Animal::Deer);
			asb.coords.emplace_back(coord);
}
else if (random < (currentChance += deerChance) + mooseChance) {
			asb.types.emplace_back(Animal::Moose);
			asb.coords.emplace_back(coord);
}
else if (random < (currentChance += mooseChance) + capybaraChance) {
			asb.types.emplace_back(Animal::Capybara);
			asb.coords.emplace_back(coord);
}
else if (random < (currentChance += capybaraChance) + turtleChance) {
			asb.types.emplace_back(Animal::Turtle);
			asb.coords.emplace_back(coord);
}
else if (random < (currentChance += turtleChance) + elephantChance) {
			asb.types.emplace_back(Animal::Elephant);
			asb.coords.emplace_back(coord);
}
else if (random < (currentChance += elephantChance) + bisonChance) {
			asb.types.emplace_back(Animal::Bison);
			asb.coords.emplace_back(coord);
}
else if (random < (currentChance += bisonChance) + wolfChance) {
			asb.types.emplace_back(Animal::Wolf);
			asb.coords.emplace_back(coord);
}
else if (random < (currentChance += wolfChance) + bearChance) {
			asb.types.emplace_back(Animal::Bear);
			asb.coords.emplace_back(coord);
}
else if (random < (currentChance += bearChance) + caribouChance) {
			asb.types.emplace_back(Animal::Caribou);
			asb.coords.emplace_back(coord);
} else asb.size--;
	}
	asb.types.shrink_to_fit(asb.size);
	asb.coords.shrink_to_fit(asb.size);
	return asb;
}

void WorldSpawner::spawnScavengeables(std::vector<bool> &tileWater, vector<bool> &tileOccupied,
				      ScavengeableDatabase &sd)
{
	float dominant = 0.009;
	float abundant = 0.003;
	float common = 0.001;
	float semicommon = 0.0005;
	float uncommon = 0.00025;
	float rare = 0.000125;
	float veryrare = 0.000066;
	float legendary = 0.000033;
	float never = 0.0;
	for (int i = 0; i < rAdIndex.size(); i++)
	{
		if (static_cast<int>(rAdObject[i]) != 0)
			continue;
		uint32_t chunk = rAdChunkIndex[i];
		std::pair<int, int> chunkCoord = rMapsLink[chunk];
		int biome = biomeMap[chunkCoord.first][chunkCoord.second];
		Scavengeable scavengeable;
		float logChance = 0.0;
		float pebbleChance = 0.0;
		float rockChance = 0.0;
		float largeRockChance = 0.0;
		float boulderChance = 0.0;
		float flintChance = 0.0;
		float oreChance = 0.0;
		float beehiveChance = 0.0;
		float stickChance = 0.0;

		// hot desert
		if (biome == 1)
			logChance = legendary;
		pebbleChance = abundant;
		rockChance = common;
		largeRockChance = semicommon;
		boulderChance = rare;
		flintChance = rare;
		oreChance = veryrare;
		beehiveChance = legendary;
		stickChance = uncommon;
	}
	// plains
	if (biome == 2)
	{
		logChance = rare;
		pebbleChance = common;
		rockChance = semicommon;
		largeRockChance = uncommon;
		boulderChance = rare;
		flintChance = veryrare;
		oreChance = veryrare;
		beehiveChance = uncommon;
		stickChance = common;
	}
	// savannah
	if (biome == 3)
	{
		logChanceChance = semicommon;
		pebbleChance = common;
		rockChance = common;
		largeRockChance = semicommon;
		boulderChance = uncommon;
		flintChance = rare;
		oreChance = veryrare;
		beehiveChance = semicommon;
		stickChance = abundant;
	}
	// wetlands
	if (biome == 4)
	{
		logChance = common;
		pebbleChance = uncommon;
		rockChance = rare;
		largeRockChance = veryrare;
		boulderChance = legendary;
		flintChance = veryrare;
		oreChance = veryrare;
		beehiveChance = uncommon;
		stickChance = abundant;
	}
	// forests
	if (biome == 5)
	{
		logChance = abundant;
		pebbleChance = common;
		rockChance = common;
		largeRockChance = semicommon;
		boulderChance = uncommon;
		flintChance = rare;
		oreChance = veryrare;
		beehiveChance = semicommon;
		stickChance = dominant;
	}
	// taiga
	if (biome == 6)
	{
		logChance = abundant;
		pebbleChance = common;
		rockChance = common;
		largeRockChance = semicommon;
		boulderChance = uncommon;
		flintChance = rare;
		oreChance = veryrare;
		beehiveChance = rare;
		stickChance = dominant;
	}
	// rainforest
	if (biome == 7)
	{
		logChance = abundant;
		pebbleChance = uncommon;
		rockChance = uncommon;
		largeRockChance = veryrare;
		boulderChance = veryrare;
		flintChance = veryrare;
		oreChance = legendary;
		beehiveChance = semicommon;
		stickChance = dominant;
	}
	// rocky
	if (biome == 8)
	{
		logChance = veryrare;
		pebbleChance = dominant;
		rockChance = abundant;
		largeRockChance = semicommon;
		boulderChance = uncommon;
		flintChance = uncommon;
		oreChance = rare;
		beehiveChance = veryrare;
		stickChance = rare;
	}
	// tundra
	if (biome == 9)
	{
		logChance = veryrare;
		pebbleChance = abundant;
		rockChance = common;
		largeRockChance = uncommon;
		boulderChance = veryrare;
		flintChance = rear;
		oreChance = legendary;
		beehiveChance = veryrare;
		stickChance = uncommon;
	}
	// cold desert
	if (biome == 10)
	{
		logChance = legendary;
		pebbleChance = dominant;
		rockChance = abundant;
		largeRockChance = common;
		boulderChance = semicommon;
		flintChance = rare;
		oreChance = veryrare;
		beehiveChance = legendary;
		stickChance = rare;
	}

	float random = rand() / (float)RAND_MAX;
	if (random < currentChance + logChance)
	{
		scavengeable = Scavengeable::Log;
	}
	else if (random < currentChance + pebbleChance)
	{
		scavengeable = Scavengeable::Pebble;
	}
	else if (random < currentChance + rockChance)
	{
		scavengeable = Scavengeable::Rock;
	}
	else if (random < currentChance + largeRockChance)
	{
		scavengeable = Scavengeable::LargeRock;
	}
	else if (random < currentChance + boulderChance)
	{
		scavengeable = Scavengeable::Boulder;
	}
	else if (random < currentChance + flintChance)
	{
		scavengeable = Scavengeable::Flint;
	}
	else if (random < currentChance + oreChance)
	{
		scavengeable = Scavengeable::Ore;
	}
	else if (random < currentChance + beehiveChance)
	{
		scavengeable = Scavengeable::Beehive;
	}
	else if (random < currentChance + stickChance)
	{
		scavengeable = Scavengeable::Stick;
	}
	// log must take up multiple ads, and depends on tree type, which is randomly
	// generated
	if (scavengeable == Scavengeable::Log)
	{
	}
}

Coord World::getRandomPlayerStart()
{
	return {random_chance.next() * CHUNK_LATITUDE_WIDTH,
		random_chance.next() * CHUNK_LATITUDE_HEIGHT};
};
