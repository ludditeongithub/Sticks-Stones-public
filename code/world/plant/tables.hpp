#pragma once
#include "enum.hpp"
#include <array>
#include <core/containers.hpp>
#include <core/data.hpp>
#include <core/tables.hpp>
#include <world/world.hpp>

using enum Plant;
using PlantTable = LookupTable<PlantCategory, float>;

constexpr float UNOPTIMAL_TEMP_MULT = 0.65;
constexpr float LOW_WATER_MULT = 0.55;

inline constexpr LookupTable<PlantCategory, float> hotDesertPlantChances = []
{
	LookupTable<PlantCategory, float> lt{};
	using enum PlantCategory;
	lt[Tree] = 0.04; // acacia
	lt[Citrus] = 0.0;
	lt[Stone] = 0.0;
	lt[Pome] = 0.0;
	lt[Olive] = 0.06;
	lt[Moss] = 0.0;
	lt[Fern] = 0.0;
	lt[Bush] = 0.45;
	lt[Succulent] = 0.7;
	lt[BerryShrub] = 0.0;
	lt[Leafy] = 0.00;
	lt[Root] = 0.0;
	lt[Tuber] = 0.0;
	lt[Bulb] = 0.06;
	lt[Grain] = 0.0;
	lt[Grapevine] = 0.0;
	lt[Herb] = 0.075;
	lt[Textile] = 0.02;
	return lt;
}();

constexpr const PlantTable &hotDesertPlantTable() { return hotDesertPlantChances; }

inline constexpr LookupTable<PlantCategory, float> grasslandPlantChances = []
{
	LookupTable<PlantCategory, float> lt{};
	using enum PlantCategory;
	lt[Tree] = 0.2;
	lt[Citrus] = 0.0;
	lt[Stone] = 0.0;
	lt[Pome] = 0.0;
	lt[Olive] = 0.0;
	lt[Moss] = 0.2;
	lt[Fern] = 0.2;
	lt[Bush] = 0.3;
	lt[Succulent] = 0.06;
	lt[BerryShrub] = 0.2;
	lt[Leafy] = 0.2;
	lt[Root] = 0.1;
	lt[Reed] = 0.0;
	lt[Tuber] = 0.04;
	lt[Bulb] = 0.06;
	lt[Grain] = 0.35;
	lt[Grapevine] = 0.0;
	lt[Herb] = 0.25;
	lt[Textile] = 0.06;
	return lt;
}();

constexpr const PlantTable &grasslandPlantTable() { return grasslandPlantChances; }

inline constexpr LookupTable<PlantCategory, float> savannahPlantChances = []
{
	LookupTable<PlantCategory, float> lt{};
	using enum PlantCategory;
	lt[Tree] = 0.80;
	lt[Citrus] = 0.08;
	lt[Stone] = 0.08;
	lt[Pome] = 0.0;
	lt[Olive] = 0.08;
	lt[Moss] = 0.04;
	lt[Fern] = 0.08;
	lt[Bush] = 0.6;
	lt[Succulent] = 0.16;
	lt[BerryShrub] = 0.12;
	lt[Leafy] = 0.08;
	lt[Root] = 0.1;
	lt[Tuber] = 0.08;
	lt[Bulb] = 0.12;
	lt[Grain] = 0.2;
	lt[Grapevine] = 0.0;
	lt[Herb] = 0.2;
	lt[Textile] = 0.04;
	return lt;
}();

constexpr const PlantTable &savannahPlantTable() { return savannahPlantChances; }

inline constexpr LookupTable<PlantCategory, float> wetlandPlantChances = []
{
	LookupTable<PlantCategory, float> lt{};
	using enum PlantCategory;
	lt[Tree] = 0.3;
	lt[Citrus] = 0.0;
	lt[Stone] = 0.0;
	lt[Pome] = 0.0;
	lt[Olive] = 0.0;
	lt[Moss] = 0.15;
	lt[Fern] = 0.3;
	lt[Bush] = 0.3;
	lt[Reed] = 0.4;
	lt[Succulent] = 0.06;
	lt[BerryShrub] = 0.09;
	lt[Leafy] = 0.0; // increase when adding duckweed and lt] water plants
	lt[Root] = 0.0;	 // increase when adding wetland root plants
	lt[Tuber] = 0.0; // increase when adding water tubers
	lt[Bulb] = 0.0;
	lt[Grain] = 0.3;
	lt[Grapevine] = 0.0;
	lt[Herb] = 0.3;
	lt[Textile] = 0.02;
	return lt;
}();

constexpr const PlantTable &wetlandPlantTable() { return wetlandPlantChances; }

inline constexpr LookupTable<PlantCategory, float> temperatePlantChances = []
{
	LookupTable<PlantCategory, float> lt{};
	using enum PlantCategory;
	lt[Tree] = 0.92;
	lt[Citrus] = 0.02;
	lt[Stone] = 0.02;
	lt[Pome] = 0.0;
	lt[Olive] = 0.0;
	lt[Moss] = 0.25;
	lt[Fern] = 0.35;
	lt[Bush] = 0.2;
	lt[Reed] = 0.05;
	lt[Succulent] = 0.04;
	lt[BerryShrub] = 0.1;
	lt[Leafy] = 0.1;
	lt[Root] = 0.1;
	lt[Tuber] = 0.08;
	lt[Bulb] = 0.07;
	lt[Grain] = 0.1;
	lt[Grapevine] = 0.04;
	lt[Herb] = 0.18;
	lt[Textile] = 0.02;
	return lt;
}();

constexpr const PlantTable &temperatePlantTable() { return temperatePlantChances; }

inline constexpr LookupTable<PlantCategory, float> borealPlantChances = []
{
	LookupTable<PlantCategory, float> lt{};
	using enum PlantCategory;
	lt[Tree] = 0.85;
	lt[Citrus] = 0.0;
	lt[Stone] = 0.0;
	lt[Pome] = 0.0;
	lt[Olive] = 0.0;
	lt[Moss] = 0.2;
	lt[Fern] = 0.14;
	lt[Bush] = 0.2;
	lt[Succulent] = 0.02;
	lt[BerryShrub] = 0.2;
	lt[Leafy] = 0.08;
	lt[Root] = 0.08;
	lt[Tuber] = 0.02;
	lt[Bulb] = 0.04;
	lt[Grain] = 0.06;
	lt[Grapevine] = 0.0;
	lt[Herb] = 0.08;
	lt[Textile] = 0.02;
	return lt;
}();

constexpr const PlantTable &borealPlantTable() { return borealPlantChances; }

inline constexpr LookupTable<PlantCategory, float> junglePlantChances = []
{
	LookupTable<PlantCategory, float> lt{};
	using enum PlantCategory;
	lt[Tree] = 0.85;
	lt[Citrus] = 0.02;
	lt[Stone] = 0.02;
	lt[Pome] = 0.0;
	lt[Olive] = 0.0;
	lt[Moss] = 0.2;
	lt[Fern] = 0.3;
	lt[Bush] = 0.2;
	lt[Reed] = 0.02;
	lt[Succulent] = 0.0;
	lt[BerryShrub] = 0.2;
	lt[Leafy] = 0.05; // add more later
	lt[Root] = 0.06;
	lt[Tuber] = 0.05;
	lt[Bulb] = 0.04;
	lt[Grain] = 0.07;
	lt[Grapevine] = 0.04;
	lt[Herb] = 0.18;
	lt[Textile] = 0.02;
	return lt;
}();

constexpr const PlantTable &junglePlantTable() { return junglePlantChances; }

inline constexpr LookupTable<PlantCategory, float> rockyPlantChances = []
{
	LookupTable<PlantCategory, float> lt{};
	using enum PlantCategory;
	lt[Tree] = 0.114108f;
	lt[Moss] = 0.342324f;
	lt[Fern] = 0.114108f;
	lt[Succulent] = 0.186722f;
	lt[BerryShrub] = 0.082988f;
	lt[Leafy] = 0.020747f;
	lt[Root] = 0.031121f;
	lt[Tuber] = 0.020747f;
	lt[Herb] = 0.082988f;
	lt[Textile] = 0.004149f;
	return lt;
}();

constexpr const PlantTable &rockyPlantTable() { return rockyPlantChances; }

inline constexpr LookupTable<PlantCategory, float> tundraPlantChances = []
{
	LookupTable<PlantCategory, float> lt{};
	using enum PlantCategory;
	lt[Tree] = 0.0;
	lt[Citrus] = 0.0;
	lt[Stone] = 0.0;
	lt[Pome] = 0.0;
	lt[Olive] = 0.0;
	lt[Moss] = 0.6;
	lt[Fern] = 0.06;
	lt[Bush] = 0.4;
	lt[Succulent] = 0.07;
	lt[BerryShrub] = 0.0;
	lt[Leafy] = 0.2;
	lt[Root] = 0.2;
	lt[Tuber] = 0.0;
	lt[Bulb] = 0.0;
	lt[Grain] = 0.0;
	lt[Grapevine] = 0.0;
	lt[Herb] = 0.02;
	lt[Textile] = 0.0;
	return lt;
}();

constexpr const PlantTable &tundraPlantTable() { return tundraPlantChances; }

inline constexpr LookupTable<PlantCategory, float> coldDesertPlantChances = []
{
	LookupTable<PlantCategory, float> lt{};
	using enum PlantCategory;
	mossChance = 0.2;
	fernChance = 0.05;
	bushChance = 0.3;
	succulentChance = 0.2;
	berryShrubChance = 0.05;
	leafyChance = 0.15;
	rootChance = 0.15;
	tuberChance = 0.05;
	bulbChance = 0.05;
	grainChance = 0.0;
	grapevineChance = 0.0;
	herbChance = 0.02;
	textileChance = 0.03;
	return lt;
}();

constexpr const PlantTable &coldDesertPlantTable() { return coldDesertPlantChances; }

const PlantTable &getPlantChanceTable(Biome biome)
{
	switch (biome)
	{
	case Biome::HotDesert:
		return hotDesertPlantTable();
	case Biome::Grassland:
		return grasslandPlantTable();
	case Biome::Savanna:
		return savannahPlantTable();
	case Biome::Wetland:
		return wetlandPlantTable();
	case Biome::Temperate:
		return temperatePlantTable();
	case Biome::Boreal:
		return borealPlantTable();
	case Biome::Jungle:
		return junglePlantTable();
	case Biome::Rocky:
		return rockyPlantTable();
	case Biome::Tundra:
		return tundraPlantTable();
	case Biome::ColdDesert:
		return coldDesertPlantTable();
	}
}

inline constexpr LookupTable<Biome, float> plantCoverages = []
{
	LookupTable<Biome, float> lt{};
	using enum Biome;
	HotDesert = 0.08;
	Grasslands = 0.2;
	Savannah = 0.25;
	Wetlands = 0.43;
	Temperate = 0.89;
	Boreal = 0.79;
	Jungle = 0.98;
	Rocky = 0.17;
	Tundra = 0.15;
	ColdDesert = 0.08;
	return lt;
}();

inline constexpr LookupTable<Biome, float> grassCoverages = []
{
	LookupTable<Biome, float> lt{};
	using enum Biome;
	HotDesert = 0.03;
	Grasslands = 0.97;
	Savannah = 0.75;
	Wetlands = 0.35;
	Temperate = 0.08;
	Boreal = 0.05;
	Jungle = 0.04;
	Rocky = 0.1;
	Tundra = 0.075;
	ColdDesert = 0.04;
	return lt;
}();

// TODO: manage sunlight and sun values
// TODO: change these all to uint16_ts
inline constexpr LookupTable<Plant, float> waterDeathMin = []
{
	LookupTable<Plant, float> arr{};
	arr[Wheat] = 8.0;
	arr[Oat] = 8.0;
	arr[Corn] = 12.0;
	arr[Tomato] = 8.0;
	arr[Rice] = 8.0;
	arr[Onion] = 6.0;
	arr[Cabbage] = 6.0;
	arr[Pepper] = 8.0;
	arr[Potato] = 9.0;
	arr[Carrot] = 8.0;
	arr[Poppy] = 8.0;
	arr[Senna] = 8.5;
	arr[Cotton] = 15.5;
	arr[Papyrus] = 16.5;
	arr[Flax] = 8.0;
	arr[Hemp] = 9.5;
	arr[Lettuce] = 6.5;
	return arr;
}();

inline constexpr LookupTable<Plant, float> waterDeath = []
{
	LookupTable<Plant, float> arr{};
	arr[Wheat] = HOUR_LENGTH * 70;
	arr[Oat] = HOUR_LENGTH * 42;
	arr[Corn] = HOUR_LENGTH * 36;
	arr[Tomato] = HOUR_LENGTH * 20;
	arr[Rice] = HOUR_LENGTH * 20;
	arr[Onion] = HOUR_LENGTH * 36;
	arr[Cabbage] = HOUR_LENGTH * 36;
	arr[Pepper] = HOUR_LENGTH * 20;
	arr[Potato] = HOUR_LENGTH * 28;
	arr[Carrot] = HOUR_LENGTH * 30;
	arr[Poppy] = HOUR_LENGTH * 29;
	arr[Senna] = HOUR_LENGTH * 68;
	arr[Cotton] = HOUR_LENGTH * 104;
	arr[Papyrus] = HOUR_LENGTH * 1;
	arr[Flax] = HOUR_LENGTH * 30;
	arr[Hemp] = HOUR_LENGTH * 52;
	arr[Lettuce] = HOUR_LENGTH * 20;
	return arr;
}();

//  inline constexpr LookupTable<Plant, float> waterDeathMax = [] {
//  LookupTable<Plant, float> arr{};
//  arr[Oat] = 250.0;
//  arr[Wheat] =  250.0;
//  arr[Corn] = 250.0;
//  arr[Tomato] = 180.0;
//  arr[Onion] = 200.0;
//  arr[Rice] = 200.0;
//  arr[Cabbage] = 200.0;
//  arr[Pepper] = 220.0;
//  arr[Potato] = 220.0;
//  arr[Carrot] = 180.0;
//  arr[Poppy] = 200.0;
//  arr[Senna] = 220.0;
//  arr[Cotton] = 250.0;
//  arr[Papyrus] = 260.0;
//  arr[Flax] = 220.0;
//  arr[Hemp] = 250.0;
//  arr[Lettuce] = 150.0;
//  return arr;
// }();

inline constexpr LookupTable<Plant, float> waterRequired = []
{
	LookupTable<Plant, float> arr{};
	arr[Wheat] = 750.0 / DAY_LENGTH;
	arr[Oat] = 650.0 / DAY_LENGTH;
	arr[Corn] = 1250.0 / DAY_LENGTH;
	arr[Tomato] = 750.0 / DAY_LENGTH;
	arr[Rice] = 1750.0 / DAY_LENGTH;
	arr[Onion] = 450.0 / DAY_LENGTH;
	arr[Cabbage] = 600.0 / DAY_LENGTH;
	arr[Pepper] = 450.0 / DAY_LENGTH;
	arr[Potato] = 750.0 / DAY_LENGTH;
	arr[Carrot] = 600.0 / DAY_LENGTH;
	arr[Poppy] = 450.0 / DAY_LENGTH;
	arr[Senna] = 300.0 / DAY_LENGTH;
	arr[Cotton] = 800.0 / DAY_LENGTH;
	arr[Papyrus] = 1500.0 / DAY_LENGTH;
	arr[Flax] = 600.0 / DAY_LENGTH;
	arr[Hemp] = 750.0 / DAY_LENGTH;
	arr[Lettuce] = 400.0 / DAY_LENGTH;
	return arr;
}();

inline constexpr LookupTable<Plant, float> tempDeathMin = []
{
	LookupTable<Plant, float> arr{};
	arr[Wheat] = -10.0;
	arr[Oat] = -8.0;
	arr[Corn] = 0.0;
	arr[Tomato] = 0.0;
	arr[Rice] = 6.0;
	arr[Onion] = -5.0;
	arr[Cabbage] = -5.0;
	arr[Pepper] = 5.0;
	arr[Potato] = -2.0;
	arr[Carrot] = -6.0;
	arr[Poppy] = -5.0;
	arr[Senna] = 0.0;
	arr[Cotton] = 0.0;
	arr[Papyrus] = 0.0;
	arr[Flax] = -5.0;
	arr[Hemp] = -5.0;
	arr[Lettuce] = 0.0;
	return arr;
}();

// TODO : change these to int16_ts?
inline constexpr LookupTable<Plant, float> tempDeathMax = []
{
	LookupTable<Plant, float> arr{};
	arr[Wheat] = 42.0;
	arr[Oat] = 42.0;
	arr[Corn] = 45.0;
	arr[Rice] = 45.0;
	arr[Tomato] = 40.0;
	arr[Onion] = 40.0;
	arr[Cabbage] = 40.0;
	arr[Pepper] = 40.0;
	arr[Potato] = 40.0;
	arr[Carrot] = 40.0;
	arr[Poppy] = 40.0;
	arr[Senna] = 45.0;
	arr[Cotton] = 45.0;
	arr[Papyrus] = 45.0;
	arr[Flax] = 40.0;
	arr[Hemp] = 40.0;
	arr[Lettuce] = 32.0;
	return arr;
}();

inline constexpr LookupTable<Plant, float> tempOptimalMin = []
{
	LookupTable<Plant, float> arr{};
	arr[Oat] = 14.0;
	arr[Wheat] = 14.0;
	arr[Corn] = 16.0;
	arr[Tomato] = 18.0;
	arr[Onion] = 12.0;
	arr[Rice] = 20.0;
	arr[Cabbage] = 15.0;
	arr[Pepper] = 18.0;
	arr[Potato] = 13.0;
	arr[Carrot] = 12.0;
	arr[Poppy] = 10.0;
	arr[Senna] = 15.0;
	arr[Cotton] = 18.0;
	arr[Papyrus] = 15.0;
	arr[Flax] = 10.0;
	arr[Hemp] = 15.0;
	arr[Lettuce] = 16.0;
	return arr;
}();

inline constexpr LookupTable<Plant, float> tempOptimalMax = []
{
	LookupTable<Plant, float> arr{};
	arr[Oat] = 21.0;
	arr[Wheat] = 21.0;
	arr[Corn] = 28.0;
	arr[Rice] = 35.0;
	arr[Tomato] = 30.0;
	arr[Onion] = 25.0;
	arr[Cabbage] = 28.0;
	arr[Pepper] = 28.0;
	arr[Potato] = 27.0;
	arr[Carrot] = 25.0;
	arr[Poppy] = 25.0;
	arr[Senna] = 35.0;
	arr[Cotton] = 32.0;
	arr[Papyrus] = 32.0;
	arr[Flax] = 22.0;
	arr[Hemp] = 30.0;
	arr[Lettuce] = 21.0;
	return arr;
}();

inline constexpr LookupTable<Plant, float> tempGrowthMin = []
{
	LookupTable<Plant, float> arr{};
	arr[Oat] = 4.0;
	arr[Wheat] = 4.0;
	arr[Corn] = 10.0;
	arr[Tomato] = 10.0;
	arr[Rice] = 15.0;
	arr[Onion] = 5.0;
	arr[Cabbage] = 5.0;
	arr[Pepper] = 10.0;
	arr[Potato] = 6.0;
	arr[Carrot] = 5.0;
	arr[Poppy] = 5.0;
	arr[Senna] = 5.0;
	arr[Cotton] = 10.0;
	arr[Papyrus] = 20.0;
	arr[Flax] = 4.0;
	arr[Hemp] = 10.0;
	arr[Lettuce] = 7.0;
	return arr;
}();

inline constexpr LookupTable<Plant, float> tempGrowthMax = []
{
	LookupTable<Plant, float> arr{};
	arr[Oat] = 38.0;
	arr[Wheat] = 38.0;
	arr[Corn] = 40.0;
	arr[Tomato] = 35.0;
	arr[Onion] = 30.0;
	arr[Rice] = 40.0;
	arr[Cabbage] = 40.0;
	arr[Pepper] = 35.0;
	arr[Potato] = 32.0;
	arr[Carrot] = 30.0;
	arr[Poppy] = 30.0;
	arr[Senna] = 30.0;
	arr[Cotton] = 35.0;
	arr[Papyrus] = 35.0;
	arr[Flax] = 35.0;
	arr[Hemp] = 35.0;
	arr[Lettuce] = 24.0;
	return arr;
}();

inline constexpr LookupTable<Plant, Time> fullyGrownAmt = []
{
	LookupTable<Plant, Time> arr{};
	arr[Corn] = 34125.0;
	arr[Rice] = 29250.0;
	arr[Wheat] = 29250.0;
	arr[Tomato] = 25312.5;
	arr[Onion] = 27787.5;
	arr[Cabbage] = 33750.0;
	arr[Pepper] = 28125.0;
	arr[Potato] = 24318.0;
	arr[Carrot] = 25312.5;
	arr[Poppy] = 25312.5;
	arr[Senna] = 29250.0;
	arr[Cotton] = 42187.0;
	arr[Papyrus] = 42187.0;
	arr[Flax] = 33750.0;
	arr[Hemp] = 36562.5;
	arr[Lettuce] = 25312.5;
	return arr;
}();

inline constexpr LookupTable<Plant, int> harvestAmt = []
{
	LookupTable<Plant, int> arr{};
	arr[Wheat] = 30;
	arr[Oat] = 30;
	arr[Corn] = 30;
	arr[Rice] = 30;
	arr[Tomato] = 30;
	arr[Onion] = 30;
	arr[Potato] = 30;
	arr[Cabbage] = 30;
	arr[Pepper] = 30;
	arr[Carrot] = 30;
	arr[Poppy] = 30;
	arr[Senna] = 30;
	arr[Cotton] = 30;
	arr[Papyrus] = 30;
	arr[Flax] = 30;
	arr[Hemp] = 30;
	arr[Lettuce] = 30;
	return arr;
}();

inline constexpr LookupTable<Plant, bool> requiresScythe = []
{
	LookupTable<Plant, bool> arr{};
	arr[Wheat] = true;
	arr[Oat] = true;
	arr[Corn] = true;
	arr[Rice] = true;
	arr[Tomato] = false;
	arr[Onion] = false;
	arr[Potato] = false;
	arr[Cabbage] = true;
	arr[Pepper] = true;
	arr[Carrot] = true;
	arr[Poppy] = true;
	arr[Senna] = true;
	arr[Cotton] = true;
	arr[Papyrus] = true;
	arr[Flax] = true;
	arr[Hemp] = true;
	arr[Lettuce] = false;
	return arr;
}();

// TODO
inline constexpr LookupTable<Plant, float> perfectSunlight = []
{
	LookupTable<Plant, float> lt{};
	using enum Plant;
	lt[Wheat] = true;
	lt[Oat] = true;
	lt[Corn] = true;
	lt[Rice] = true;
	lt[Tomato] = false;
	lt[Onion] = false;
	lt[Potato] = false;
	lt[Cabbage] = true;
	lt[Pepper] = true;
	lt[Carrot] = true;
	lt[Poppy] = true;
	lt[Senna] = true;
	lt[Cotton] = true;
	lt[Papyrus] = true;
	lt[Flax] = true;
	lt[Hemp] = true;
	lt[Lettuce] = false;
	return lt;
}();
