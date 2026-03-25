#include "enum.hpp"
#include <core/tables.hpp>
using PlantTable = LookupTable<Plant, float>;

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

inline constexpr LookupTable<PlantCategory, float> grasslandPlantChances = []
{
	LookupTable<PlantCategory, float> lt{};
	using enum PlantCategory;
	lt[Trees] = 0.2;
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

inline constexpr LookupTable<PlantCategory, float> savannahPlantChances = []
{
	LookupTable<PlantCategory, float> lt{};
	using enum PlantCategory;
	lt[Trees] = 0.80;
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

inline constexpr LookupTable<PlantCategory, float> wetlandPlantChances = []
{
	LookupTable<PlantCategory, float> lt{};
	using enum PlantCategory;
	lt[Trees] = 0.3;
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
	lt[Trees] = 0.92;
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
	lt[Trees] = 0.85;
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
	lt[Trees] = 0.85;
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
	lt[Trees] = 0.114108f;
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
	lt[Trees] = 0.0;
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
	case Biome::Grasslands:
		return grasslandsPlantTable();
	case Biome::Savannah:
		return savannahPlantTable();
	case Biome::Wetlands:
		return wetlandsPlantTable();
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
