#include "world/tile/data.hpp"

inline Tile getTileType(int biome, float chance)
{
	switch (biome)
	{
	case 1: // desert
		if (chance < 0.70)
		{
			return Tile::Sand;
		}
		else if (chance < 0.75)
		{
			return Tile::SandySoil;
		}
		else if (chance < 0.83)
		{
			return Tile::AridSoil;
		}
		else if (chance < 0.90)
		{
			return Tile::Hardpan;
		}
		else
			return Tile::Gravel;
		break;
	case 2: // Grasslands
		if (chance < 0.80)
		{
			return Tile::LoamSoil;
		}
		else if (chance < 0.90)
		{
		}
		else
			return Tile::Gravel;
		break;
	case 3: // Savanna
		if (chance < 0.10)
			return Tile::AridSoil;
		if (chance < 0.55)
			return Tile::SandySoil;
		if (chance < 0.85)
		{
			return Tile::LoamSoil;
		}
		else
		{
			return Tile::ClaySoil;
		}
		break;
	case 4: // Wetlands
		if (chance < 0.50)
		{
			return Tile::PeatSoil;
		}
		if (chance < 0.70)
		{
			return Tile::Gleysol;
		}
		if (chance < 0.85)
		{
			return Tile::SiltySoil;
		}
		else
			return Tile::ClaySoil;
		break;
	case 5: // Forest
		if (chance < 0.05)
			return Tile::Podzol;
		if (chance < 0.75)
		{
			return Tile::LoamSoil;
		}
		if (chance < 0.90)
		{
			return Tile::ClaySoil;
		}
		else
			return Tile::SiltySoil;
		break;
	case 6: // Taiga
		if (chance < 0.60)
			return Tile::Podzol;
		if (chance < 0.65)
		{
			return Tile::LoamSoil;
		}
		if (chance < 0.75)
		{
			return Tile::Gleysol;
		}
		else
		{
			return Tile::PeatSoil;
		}
		break;
	case 7: // Jungle
		if (chance < 0.70)
		{
			return Tile::Oxisol;
		}
		if (chance < 0.85)
		{
			return Tile::LoamSoil;
		}
		else
			return Tile::Gleysol;
		break;
	case 8: // Rocky
		if (chance < 0.80)
		{
			return Tile::Stone;
		}
		else if (chance < 0.85)
		{
			return Tile::RockySoil;
		}
		else
			return Tile::Gravel;
		break;
	case 9: // tundra
		if (chance < 0.85)
		{
			return Tile::FrozenSoil;
		}
		else if (chance < 0.96)
		{
			return Tile::Ice;
		}
		else
			return Tile::PeatSoil;
		break;
	case 10: // cold desert
		if (chance < 0.75)
		{
			return Tile::Sand;
		}
		else if (chance < 0.80)
		{
			return Tile::AridSoil;
		}
		else if (chance < 0.95)
		{
			return Tile::FrozenSoil;
		}
		else
			return Tile::Gravel;
		break;
	default:
		return Tile::DeepWater;
	}
	return Tile::DeepWater;
}

std::vector<float> WorldSpawner::generateTileChances()
{
	std::vector<float> chances = std::vector<float>(TILE_AMOUNT);
	// generate Voronoi Noise
	FastNoiseLite noise;
	noise.SetNoiseType(FastNoiseLite::NoiseType_Cellular);
	noise.SetFrequency(0.02f);     // Adjust scale
	noise.SetCellularJitter(1.0f); // Controls cell shape variation
	noise.SetCellularDistanceFunction(FastNoiseLite::CellularDistanceFunction_Euclidean);
	noise.SetCellularReturnType(FastNoiseLite::CellularReturnType_CellValue);
	// secondary Noise for tile generation
	FastNoiseLite pnoise;
	pnoise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
	pnoise.SetFrequency(0.02f);

	int index = 0;

	for (int i = 0; i < TILE_AMOUNT; i++)
	{
		float chance = (pnoise.GetNoise(static_cast<float>(i / TILE_WIDTH),
						static_cast<float>(i % TILE_WIDTH)) +
				1.0) *
			       0.5;
		chances[i] = chance;
	}
	return chances;
}
