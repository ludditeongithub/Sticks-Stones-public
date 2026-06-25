#pragma once
#include "enum.hpp"
#include "world/tile/grass.hpp"

enum class Scavengeable : uint16_t
{
	NONE,
	Log,
	Pebble,
	LargeStick,
	Stick,
	Rock,
	LargeRock,
	Boulder,
	Flint,
	Beehive,
	ArtificialBeehive,
	Stump,
	ChickenEgg,
	DuckEgg,
	TurtleEgg,
	Truffle,
	Leafy,
	// Variants
	// fruits
	// corpses
	PigCorpse,
	CowCorpse,
	ChickenCorpse,
	DuckCorpse,
	SheepCorpse,
	GoatCorpse,
	HorseCorpse,
	OxCorpse,
	DonkeyCorpse,
	CamelCorpse,
	WaterBuffaloCorpse,
	RabbitCorpse,
	AntelopeCorpse,
	DeerCorpse,
	MooseCorpse,
	CapybaraCorpse,
	TurtleCorpse,
	ElephantCorpse,
	BisonCorpse,
	WolfCorpse,
	BearCorpse,
	CaribouCorpse,
	// ores
	CopperOre,
	TinOre,
	IronOre,
	SilverOre,
	GoldOre,
        Coal,
        MAX
};

namespace scavengeable
{
        float extreme = 1.8;
        float dominant = 1.0;
	float abundant = 0.65;
	float common = 0.33;
	float semicommon = 0.1;
	float uncommon = 0.04;
	float rare = 0.0125;
	float veryrare = 0.0046;
	float legendary = 0.0015;
	float never = 0.0;
inline LookupTable2D<Biome, Scavengeable, float> biomeSpawnChances = []
{
	LookupTable2D<Biome, Scavengeable, float> lt{};
        using enum Scavengeable;


	lt[Biome::Grassland][Log] = common;
lt[Biome::Savanna][Log] = semicommon;
lt[Biome::Wetland][Log] = common;
lt[Biome::Temperate][Log] = dominant;
lt[Biome::Boreal][Log] = abundant;
lt[Biome::Jungle][Log] = extreme;

lt[Biome::Grassland][LargeStick] = semicommon;
lt[Biome::Savanna][LargeStick] = common;
lt[Biome::Wetland][LargeStick] = common;
lt[Biome::Temperate][LargeStick] = abundant;
lt[Biome::Boreal][LargeStick] = abundant;
lt[Biome::Jungle][LargeStick] = dominant;

lt[Biome::Grassland][Stick] = abundant;
lt[Biome::Savanna][Stick] = abundant;
lt[Biome::Wetland][Stick] = common;
lt[Biome::Temperate][Stick] = extreme;
lt[Biome::Boreal][Stick] = dominant;
lt[Biome::Jungle][Stick] = extreme;

    lt[Biome::HotDesert][Pebble] = semicommon;
	lt[Biome::Grassland][Pebble] = common;
	lt[Biome::Savanna][Pebble] = common;
	lt[Biome::Wetland][Pebble] = semicommon;
	lt[Biome::Temperate][Pebble] = common;
	lt[Biome::Boreal][Pebble] = abundant;
	lt[Biome::Jungle][Pebble] = uncommon;
	lt[Biome::Rocky][Pebble] = extreme;
        lt[Biome::ColdDesert][Pebble] = abundant;
 
lt[Biome::HotDesert][Rock] = semicommon;
lt[Biome::Grassland][Rock] = common;
lt[Biome::Savanna][Rock] = common;
lt[Biome::Wetland][Rock] = uncommon;
lt[Biome::Temperate][Rock] = common;
lt[Biome::Boreal][Rock] = abundant;
lt[Biome::Jungle][Rock] = uncommon;
lt[Biome::Rocky][Rock] = extreme;
lt[Biome::ColdDesert][Rock] = common;

lt[Biome::HotDesert][LargeRock] = uncommon;
lt[Biome::Grassland][LargeRock] = semicommon;
lt[Biome::Savanna][LargeRock] = semicommon;
lt[Biome::Temperate][LargeRock] = semicommon;
lt[Biome::Boreal][LargeRock] = common;
lt[Biome::Rocky][LargeRock] = dominant;
lt[Biome::ColdDesert][LargeRock] = common;

lt[Biome::Temperate][Boulder] = uncommon;
lt[Biome::Boreal][Boulder] = semicommon;
lt[Biome::Rocky][Boulder] = extreme;
lt[Biome::ColdDesert][Boulder] = semicommon;

lt[Biome::Grassland][Flint] = uncommon;
lt[Biome::Savanna][Flint] = uncommon;
lt[Biome::Temperate][Flint] = uncommon;
lt[Biome::Boreal][Flint] = rare;
lt[Biome::Rocky][Flint] = common;
lt[Biome::ColdDesert][Flint] = semicommon;

lt[Biome::Grassland][Beehive] = uncommon;
lt[Biome::Savanna][Beehive] = uncommon;
lt[Biome::Wetland][Beehive] = rare;
lt[Biome::Temperate][Beehive] = semicommon;
lt[Biome::Boreal][Beehive] = uncommon;
lt[Biome::Jungle][Beehive] = common;

lt[Biome::Grassland][Stump] = semicommon;
lt[Biome::Savanna][Stump] = semicommon;
lt[Biome::Wetland][Stump] = common;
lt[Biome::Temperate][Stump] = abundant;
lt[Biome::Boreal][Stump] = common;
lt[Biome::Jungle][Stump] = common;

lt[Biome::Grassland][ChickenEgg] = rare;
lt[Biome::Savanna][ChickenEgg] = rare;

lt[Biome::Wetland][DuckEgg] = rare;
lt[Biome::Temperate][DuckEgg] = veryrare;
lt[Biome::Boreal][DuckEgg] = veryrare;

lt[Biome::Wetland][TurtleEgg] = veryrare;
lt[Biome::Jungle][TurtleEgg] = rare;

lt[Biome::Temperate][Truffle] = veryrare;
lt[Biome::Boreal][Truffle] = legendary;
lt[Biome::Jungle][Truffle] = rare;

lt[Biome::Grassland][Leafy] = common;
lt[Biome::Savanna][Leafy] = semicommon;
lt[Biome::Wetland][Leafy] = abundant;
lt[Biome::Temperate][Leafy] = extreme;
lt[Biome::Boreal][Leafy] = common;
lt[Biome::Jungle][Leafy] = extreme;
// Variants
// fruits
// corpses
// ores
//TODO: ore spawning in rivers, caves, underground
	lt[Biome::Rocky][CopperOre] = uncommon;
lt[Biome::ColdDesert][CopperOre] = rare;
lt[Biome::Temperate][CopperOre] = veryrare;
lt[Biome::Boreal][CopperOre] = veryrare;

lt[Biome::Rocky][TinOre] = rare;
lt[Biome::ColdDesert][TinOre] = veryrare;
lt[Biome::Temperate][TinOre] = veryrare;

lt[Biome::Rocky][IronOre] = uncommon;
lt[Biome::ColdDesert][IronOre] = rare;
lt[Biome::Boreal][IronOre] = veryrare;
lt[Biome::Temperate][IronOre] = veryrare;

lt[Biome::Rocky][SilverOre] = veryrare;
lt[Biome::ColdDesert][SilverOre] = legendary;

lt[Biome::Rocky][GoldOre] = legendary;
lt[Biome::ColdDesert][GoldOre] = legendary;

lt[Biome::Rocky][Coal] = uncommon;
lt[Biome::Boreal][Coal] = rare;
lt[Biome::Temperate][Coal] = rare;
    return lt;
  }();
}
