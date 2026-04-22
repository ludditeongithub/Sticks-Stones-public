#ifndef LIFESTATS_HPP
#define LIFESTATS_HPP

#include "enum.hpp"
#include <core/data.hpp>
#include <core/tables.hpp>
#include <core/time.hpp>

constexpr float dominant = 0.003;
constexpr float abundant = 0.0015;
constexpr float common = 0.0008;
constexpr float semicommon = 0.0004;
constexpr float uncommon = 0.0002;
constexpr float rare = 0.00008;
constexpr float veryrare = 0.00003;
constexpr float endangered = 0.00001;
constexpr float never = 0.0;

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
	return lt;
}();

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

inline constexpr LookupTable<Animal, float> rockySpawnChances = []
{
	LookupTable<Animal, float> lt{};
	using enum Animal;
	lt[Goat] = common;
	lt[Wolf] = rare;
	lt[Sheep] = rare;
	return lt;
}();

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
	return lt;
}();

// in terms of hunger consumed per hour
inline constexpr LookupTable<Animal, Hunger> eatingSpeeds = []
{
	LookupTable<Animal, Hunger> lt{};
	lt[Animal::Pig] = 2950;
	lt[Animal::Cow] = 1200;
	lt[Animal::Chicken] = 280;
	lt[Animal::Duck] = 280;
	lt[Animal::Sheep] = 1080;
	lt[Animal::Goat] = 1400;
	lt[Animal::Horse] = 1900;
	lt[Animal::Ox] = 1600;
	lt[Animal::Donkey] = 1550;
	lt[Animal::Camel] = 1450;
	lt[Animal::WaterBuffalo] = 1600;
	lt[Animal::Rabbit] = 450;
	lt[Animal::Antelope] = 890;
	lt[Animal::Deer] = 890;
	lt[Animal::Moose] = 3580;
	lt[Animal::Capybara] = 640;
	lt[Animal::Turtle] = 85;
	lt[Animal::Elephant] = 10800;
	lt[Animal::Bison] = 4300;
	lt[Animal::Wolf] = 6800;
	lt[Animal::Bear] = 13400;
	lt[Animal::Caribou] = 2130;
	lt[Animal::Fish] = 120;
	return lt;
}();

inline constexpr LookupTable<Animal, Time> fertilityAge = []
{
	LookupTable<Animal, Time> arr;
	arr[Animal::Pig] = static_cast<int>(0.5 * YEAR_LENGTH);
	arr[Animal::Cow] = static_cast<int>(1.5 * YEAR_LENGTH);
	arr[Animal::Chicken] = static_cast<int>(0.3 * YEAR_LENGTH);
	arr[Animal::Duck] = static_cast<int>(0.4 * YEAR_LENGTH);
	arr[Animal::Sheep] = static_cast<int>(1.0 * YEAR_LENGTH);
	arr[Animal::Goat] = static_cast<int>(1.0 * YEAR_LENGTH);
	arr[Animal::Horse] = static_cast<int>(3.0 * YEAR_LENGTH);
	arr[Animal::Ox] = static_cast<int>(2.0 * YEAR_LENGTH);
	arr[Animal::Donkey] = static_cast<int>(2.0 * YEAR_LENGTH);
	arr[Animal::Camel] = static_cast<int>(4.0 * YEAR_LENGTH);
	arr[Animal::WaterBuffalo] = static_cast<int>(3.0 * YEAR_LENGTH);
	arr[Animal::Rabbit] = static_cast<int>(0.3 * YEAR_LENGTH);
	arr[Animal::Antelope] = static_cast<int>(1.5 * YEAR_LENGTH);
	arr[Animal::Deer] = static_cast<int>(1.5 * YEAR_LENGTH);
	arr[Animal::Moose] = static_cast<int>(2.0 * YEAR_LENGTH);
	arr[Animal::Capybara] = static_cast<int>(1.0 * YEAR_LENGTH);
	arr[Animal::Turtle] = static_cast<int>(10.0 * YEAR_LENGTH);
	arr[Animal::Elephant] = static_cast<int>(10.0 * YEAR_LENGTH);
	arr[Animal::Bison] = static_cast<int>(2.5 * YEAR_LENGTH);
	arr[Animal::Wolf] = static_cast<int>(2.0 * YEAR_LENGTH);
	arr[Animal::Bear] = static_cast<int>(3.0 * YEAR_LENGTH);
	arr[Animal::Caribou] = static_cast<int>(2.0 * YEAR_LENGTH);
	arr[Animal::Fish] = static_cast<int>(1.0 * YEAR_LENGTH);

	return arr;
}();

inline constexpr LookupTable<Animal, Time> estimatedLifespan = []
{
	LookupTable<Animal, Time> arr;

	arr[Animal::Pig] = static_cast<int>(15.0 * YEAR_LENGTH);
	arr[Animal::Cow] = static_cast<int>(20.0 * YEAR_LENGTH);
	arr[Animal::Chicken] = static_cast<int>(8.0 * YEAR_LENGTH);
	arr[Animal::Duck] = static_cast<int>(10.0 * YEAR_LENGTH);
	arr[Animal::Sheep] = static_cast<int>(12.0 * YEAR_LENGTH);
	arr[Animal::Goat] = static_cast<int>(15.0 * YEAR_LENGTH);
	arr[Animal::Horse] = static_cast<int>(30.0 * YEAR_LENGTH);
	arr[Animal::Ox] = static_cast<int>(20.0 * YEAR_LENGTH);
	arr[Animal::Donkey] = static_cast<int>(30.0 * YEAR_LENGTH);
	arr[Animal::Camel] = static_cast<int>(40.0 * YEAR_LENGTH);
	arr[Animal::WaterBuffalo] = static_cast<int>(25.0 * YEAR_LENGTH);
	arr[Animal::Rabbit] = static_cast<int>(9.0 * YEAR_LENGTH);
	arr[Animal::Antelope] = static_cast<int>(12.0 * YEAR_LENGTH);
	arr[Animal::Deer] = static_cast<int>(15.0 * YEAR_LENGTH);
	arr[Animal::Moose] = static_cast<int>(20.0 * YEAR_LENGTH);
	arr[Animal::Capybara] = static_cast<int>(10.0 * YEAR_LENGTH);
	arr[Animal::Turtle] = static_cast<int>(80.0 * YEAR_LENGTH);
	arr[Animal::Elephant] = static_cast<int>(70.0 * YEAR_LENGTH);
	arr[Animal::Bison] = static_cast<int>(20.0 * YEAR_LENGTH);
	arr[Animal::Wolf] = static_cast<int>(13.0 * YEAR_LENGTH);
	arr[Animal::Bear] = static_cast<int>(25.0 * YEAR_LENGTH);
	arr[Animal::Caribou] = static_cast<int>(15.0 * YEAR_LENGTH);
	arr[Animal::Fish] = static_cast<int>(5.0 * YEAR_LENGTH);

	return arr;
}();

inline LookupTable<Animal, uint16_t> hungerSearchThreshold = []
{
	LookupTable<Animal, uint16_t> arr;
	using enum Animal;

	return arr;
}();

inline constexpr LookupTable<Animal, uint16_t> sightRanges = []
{
	LookupTable<Animal, uint16_t> arr;

	arr[Animal::Pig] = 50;
	arr[Animal::Cow] = 150;
	arr[Animal::Chicken] = 30;
	arr[Animal::Duck] = 80;
	arr[Animal::Sheep] = 200;
	arr[Animal::Goat] = 250;
	arr[Animal::Horse] = 300;
	arr[Animal::Ox] = 150;
	arr[Animal::Donkey] = 200;
	arr[Animal::Camel] = 500;
	arr[Animal::WaterBuffalo] = 100;
	arr[Animal::Rabbit] = 100;
	arr[Animal::Antelope] = 600;
	arr[Animal::Deer] = 500;
	arr[Animal::Moose] = 300;
	arr[Animal::Capybara] = 80;
	arr[Animal::Turtle] = 30;
	arr[Animal::Elephant] = 200;
	arr[Animal::Bison] = 300;
	arr[Animal::Wolf] = 1000;
	arr[Animal::Bear] = 400;
	arr[Animal::Caribou] = 600;
	arr[Animal::Fish] = 20;

	return arr;
}();

inline constexpr LookupTable<Animal, Speed> minSpeed = []
{
	LookupTable<Animal, Speed> arr;

	arr[Animal::Pig] = 1.5f;
	arr[Animal::Cow] = 1.0f;
	arr[Animal::Chicken] = 0.8f;
	arr[Animal::Duck] = 0.8f;
	arr[Animal::Sheep] = 1.0f;
	arr[Animal::Goat] = 1.0f;
	arr[Animal::Horse] = 1.6f;
	arr[Animal::Ox] = 1.0f;
	arr[Animal::Donkey] = 1.2f;
	arr[Animal::Camel] = 1.3f;
	arr[Animal::WaterBuffalo] = 0.9f;
	arr[Animal::Rabbit] = 1.0f;
	arr[Animal::Antelope] = 2.0f;
	arr[Animal::Deer] = 1.8f;
	arr[Animal::Moose] = 1.2f;
	arr[Animal::Capybara] = 0.8f;
	arr[Animal::Turtle] = 0.05f;
	arr[Animal::Elephant] = 1.5f;
	arr[Animal::Bison] = 1.5f;
	arr[Animal::Wolf] = 1.8f;
	arr[Animal::Bear] = 1.3f;
	arr[Animal::Caribou] = 1.8f;
	arr[Animal::Fish] = 0.5f;

	return arr;
}();

inline constexpr LookupTable<Animal, Speed> maxSpeed = []
{
	LookupTable<Animal, Speed> arr;

	arr[Animal::Pig] = 6.0f;
	arr[Animal::Cow] = 7.5f;
	arr[Animal::Chicken] = 4.0f;
	arr[Animal::Duck] = 10.0f;
	arr[Animal::Sheep] = 14.0f;
	arr[Animal::Goat] = 12.0f;
	arr[Animal::Horse] = 22.0f;
	arr[Animal::Ox] = 5.5f;
	arr[Animal::Donkey] = 8.3f;
	arr[Animal::Camel] = 14.0f;
	arr[Animal::WaterBuffalo] = 5.0f;
	arr[Animal::Rabbit] = 17.0f;
	arr[Animal::Antelope] = 27.0f;
	arr[Animal::Deer] = 22.0f;
	arr[Animal::Moose] = 15.0f;
	arr[Animal::Capybara] = 8.3f;
	arr[Animal::Turtle] = 0.3f;
	arr[Animal::Elephant] = 6.8f;
	arr[Animal::Bison] = 18.0f;
	arr[Animal::Wolf] = 17.0f;
	arr[Animal::Bear] = 13.4f;
	arr[Animal::Caribou] = 20.0f;
	arr[Animal::Fish] = 8.0f;

	return arr;
}();

inline constexpr LookupTable<Animal, Health> maxHealths = []
{
	LookupTable<Animal, Health> lt{};
	using enum Animal;

	return lt;
}();

inline constexpr LookupTable<Animal, Hunger> maxHungers = []
{
	LookupTable<Animal, Hunger> lt{};
	using enum Animal;

	return lt;
}();

inline constexpr LookupTable<Animal, Time> maxAges = []
{
	LookupTable<Animal, Time> lt{};
	using enum Animal;

	return lt;
}();

inline constexpr const BitsetTable<Animal> isEggLayer = []
{
	BitsetTable<Animal> t;
	auto add = [&](Animal a) { t.bitset.set(static_cast<uint16_t>(a)); };
	
	add(Animal::Chicken);
	add(Animal::Duck);
	add(Animal::Turtle);
	add(Animal::Fish);
	return t;
}();

#endif
