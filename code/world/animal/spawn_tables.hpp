#include "enum.hpp"
#include <core/tables.hpp>

using SpawnTable = LookupTable<Animal, float>;

inline constexpr LookupTable<Animal, float> hotDesertSpawnChances = []
{
	LookupTable<Animal, float> lt{};
	using enum Animal;
	lt[Pig] = rare;
	lt[Camel] = dominant;
	lt[WaterBuffalo] = uncommon;
	lt[Rabbit] = common;
	lt[Antelope] = abundant;
	lt[Wolf] = semicommon;
	lt[Bear] = veryrare;
	return lt;
}();

constexpr const SpawnTable &hotDesertSpawnTable() { return hotDesertSpawnChances; }

inline constexpr LookupTable<Animal, float> grasslandSpawnChances = []
{
	LookupTable<Animal, float> lt{};
	using enum Animal;
	lt[Pig] = common;
	lt[Cow] = abundant;
	lt[Sheep] = abundant;
	lt[Goat] = semicommon;
	lt[Horse] = dominant;
	lt[Ox] = semicommon;
	lt[Donkey] = uncommon;
	lt[Rabbit] = abundant;
	lt[Antelope] = abundant;
	lt[Bison] = dominant;
	lt[Wolf] = semicommon;
	lt[Bear] = rare;
	lt[Caribou] = never;
	return lt;
}();

constexpr const SpawnTable &grasslandSpawnTable() { return grasslandSpawnChances; }

inline constexpr LookupTable<Animal, float> savannahSpawnChances = []
{
	LookupTable<Animal, float> lt{};
	using enum Animal;
	lt[Pig] = rare;
	lt[Cow] = common;
	lt[Sheep] = uncommon;
	lt[Goat] = semicommon;
	lt[Camel] = rare;
	lt[WaterBuffalo] = uncommon;
	lt[Rabbit] = common;
	lt[Antelope] = abundant;
	lt[Elephant] = dominant;
	lt[Bison] = rare;
	lt[Wolf] = semicommon;
	lt[Bear] = rare;
	lt[Caribou] = never;
	Return lt;
}();

constexpr const SpawnTable &savannahSpawnTable() { return savannahSpawnChances; }

inline constexpr LookupTable<Animal, float> wetlandSpawnChances = []
{
	LookupTable<Animal, float> lt{};
	using enum Animal;
	lt[Pig] = common;
	lt[Cow] = uncommon;
	lt[Sheep] = rare;
	lt[Goat] = rare;
	lt[Camel] = rare;
	lt[WaterBuffalo] = dominant;
	lt[Rabbit] = semicommon;
	lt[Antelope] = abundant;
	lt[Elephant] = semicommon;
	lt[Bison] = rare;
	lt[Wolf] = uncommon;
	lt[Bear] = semicommon;
	lt[Caribou] = never;
	return lt;
}();

constexpr const SpawnTable &wetlandSpawnTable() { return wetlandSpawnChances; }

inline constexpr LookupTable<Animal, float> temperateSpawnChances = []
{
	LookupTable<Animal, float> lt{};
	using enum Animal;
	lt[Pig] = semicommon;
	lt[Cow] = common;
	lt[Sheep] = uncommon;
	lt[Goat] = semicommon;
	lt[Horse] = rare;
	lt[Ox] = uncommon;
	lt[Donkey] = rare;
	lt[Rabbit] = abundant;
	lt[Antelope] = rare;
	lt[Deer] = dominant;
	lt[Moose] = abundant;
	lt[Wolf] = semicommon;
	lt[Bear] = dominant;
	lt[Caribou] = never;
	return lt;
}();

constexpr const SpawnTable &temperateSpawnTable() { return temperateSpawnChances; }

inline constexpr LookupTable<Animal, float> borealSpawnChances = []
{
	LookupTable<Animal, float> lt{};
	using enum Animal;
	lt[Pig] = rare;
	lt[Cow] = rare;
	lt[Sheep] = rare;
	lt[Goat] = rare;
	lt[Horse] = rare;
	lt[Ox] = rare;
	lt[Donkey] = rare;
	lt[Rabbit] = semicommon;
	lt[Antelope] = never;
	lt[Deer] = abundant;
	lt[Moose] = dominant;
	lt[Bison] = rare;
	lt[Wolf] = semicommon;
	lt[Bear] = abundant;
	lt[Caribou] = dominant;
	return lt;
}();

constexpr const SpawnTable &borealSpawnTable() { return borealSpawnChances; }

inline constexpr LookupTable<Animal, float> jungleSpawnChances = []
{
	LookupTable<Animal, float> lt{};
	using enum Animal;
	lt[Pig] = rare;
	lt[Cow] = veryrare;
	lt[Horse] = rare;
	lt[Ox] = veryrare;
	lt[Donkey] = rare;
	lt[Rabbit] = rare;
	lt[Antelope] = rare;
	lt[Elephant] = abundant;
	lt[Wolf] = rare;
	lt[Bear] = rare;
	lt[Caribou] = never;
	return lt;
}();

constexpr const SpawnTable &jungleSpawnTable() { return jungleSpawnChances; }

inline constexpr LookupTable<Animal, float> rockySpawnChances = []
{
	LookupTable<Animal, float> lt{};
	using enum Animal;
	lt[Goat] = common;
	lt[Wolf] = rare;
	lt[Sheep] = rare;
	return lt;
}();

constexpr const SpawnTable &rockySpawnTable() { return rockySpawnChances; }

inline constexpr LookupTable<Animal, float> tundraSpawnChances = []
{
	LookupTable<Animal, float> lt{};
	using enum Animal;
	lt[Pig] = never;
	lt[Cow] = never;
	lt[Sheep] = rare;
	lt[Goat] = uncommon;
	lt[Horse] = never;
	lt[Ox] = rare;
	lt[Donkey] = never;
	lt[Rabbit] = semicommon;
	lt[Antelope] = never;
	lt[Elephant] = never;
	lt[Bison] = never;
	lt[Wolf] = abundant;
	lt[Bear] = rare;
	lt[Caribou] = dominant;
	return lt;
}();

constexpr const SpawnTable &tundraSpawnTable() { return tundraSpawnChances; }

inline constexpr LookupTable<Animal, float> coldDesertSpawnChances = []
{
	LookupTable<Animal, float> lt{};
	using enum Animal;
	lt[Pig] = rare;
	lt[Cow] = rare;
	lt[Sheep] = uncommon;
	lt[Goat] = semicommon;
	lt[Horse] = rare;
	lt[Ox] = rare;
	lt[Donkey] = rare;
	lt[Rabbit] = common;
	lt[Antelope] = rare;
	lt[Elephant] = veryrare;
	lt[Bison] = never;
	lt[Wolf] = uncommon;
	lt[Bear] = rare;
	lt[Caribou] = never;
	Return lt;
}();

constexpr const SpawnTable &coldDesertSpawnTable() { return coldDesertSpawnChances; }

const AnimalTable &getAnimalChanceTable(Biome biome)
{
	switch (biome)
	{
	case Biome::HotDesert:
		return hotDesertSpawnTable();
	case Biome::Grassland:
		return grasslandSpawnTable();
	case Biome::Savanna:
		return savannahSpawnTable();
	case Biome::Wetlands:
		return wetlandsSpawnTable();
	case Biome::Temperate:
		return temperateSpawnTable();
	case Biome::Boreal:
		return borealSpawnTable();
	case Biome::Jungle:
		return jungleSpawnTable();
	case Biome::Rocky:
		return rockySpawnTable();
	case Biome::Tundra:
		return tundraSpawnTable();
	case Biome::ColdDesert:
		return coldDesertSpawnTable();
	}
}
