#ifndef LIFESTATS_HPP
#define LIFESTATS_HPP

#include <data/types/animal.hpp>
#include <core/coord.hpp>
#include <core/tables.hpp>
#include <data/types/tile.hpp>
#include <data/types/stats.hpp>
#include <data/types/time.hpp>
#include <data/const/time_data.hpp>

namespace animal
{
inline constexpr LookupTable<Animal, SCoord> TEMPERATURE_PENALTY_RANGES = []
{
	LookupTable<Animal, SCoord> lt{};
	using enum Animal;

	lt[Pig]          = {23, 77};
	lt[Cow]          = {14, 77};
	lt[Chicken]      = {50, 86};
	lt[Duck]         = {32, 77};
	lt[Sheep]        = {14, 68};
	lt[Goat]         = {41, 86};
	lt[Horse]        = {14, 77};
	lt[Ox]           = {14, 77};
	lt[Donkey]       = {50, 95};
	lt[Camel]        = {59, 104};
	lt[WaterBuffalo] = {68, 95};
	lt[Rabbit]       = {41, 68};
	lt[Antelope]     = {50, 95};
	lt[Deer]         = {14, 68};
	lt[Moose]        = {-4, 59};
	lt[Capybara]     = {68, 95};
	lt[Turtle]       = {68, 95};
	lt[Elephant]     = {68, 95};
	lt[Bison]        = {-4, 68};
	lt[Wolf]         = {-4, 59};
	lt[Bear]         = {5, 68};
	lt[Caribou]      = {-13, 50};

	return lt;
}();

inline constexpr LookupTable<Animal,SCoord> HUMIDITY_PENALTY_RANGES = [] {
		LookupTable<Animal,SCoord> lt{};
		using enum Animal;
		
	lt[Pig]          = {50, 80};
	lt[Cow]          = {40, 80};
	lt[Chicken]      = {40, 70};
	lt[Duck]         = {60, 100};
	lt[Sheep]        = {30, 70};
	lt[Goat]         = {20, 60};
	lt[Horse]        = {30, 70};
	lt[Ox]           = {30, 70};
	lt[Donkey]       = {20, 50};
	lt[Camel]        = {10, 40};
	lt[WaterBuffalo] = {60, 100};
	lt[Rabbit]       = {40, 70};
	lt[Antelope]     = {20, 60};
	lt[Deer]         = {40, 80};
	lt[Moose]        = {50, 90};
	lt[Capybara]     = {70, 100};
	lt[Turtle]       = {60, 100};
	lt[Elephant]     = {40, 80};
	lt[Bison]        = {30, 70};
	lt[Wolf]         = {40, 80};
	lt[Bear]         = {40, 80};
	lt[Caribou]      = {40, 90};

		return lt;
}();
constexpr float dominant = 0.003;
constexpr float abundant = 0.0015;
constexpr float common = 0.0008;
constexpr float semicommon = 0.0004;
constexpr float uncommon = 0.0002;
constexpr float rare = 0.00008;
constexpr float veryrare = 0.00003;
constexpr float endangered = 0.00001;
constexpr float never = 0.0;

inline constexpr LookupTable2D<Biome, Animal, float> BIOME_SPAWN_CHANCES = []
{
	LookupTable2D<Biome, Animal, float> lt{};
	using enum Animal;

        lt[Biome::HotDesert][Pig]          = rare;
        lt[Biome::HotDesert][Camel]        = dominant;
        lt[Biome::HotDesert][WaterBuffalo] = uncommon;
        lt[Biome::HotDesert][Rabbit]       = common;
        lt[Biome::HotDesert][Antelope]     = abundant;
        lt[Biome::HotDesert][Wolf]         = semicommon;
        lt[Biome::HotDesert][Bear]         = veryrare;

        lt[Biome::Grassland][Pig]      = common;
        lt[Biome::Grassland][Cow]      = abundant;
        lt[Biome::Grassland][Sheep]    = abundant;
        lt[Biome::Grassland][Goat]     = semicommon;
        lt[Biome::Grassland][Horse]    = dominant;
        lt[Biome::Grassland][Ox]       = semicommon;
        lt[Biome::Grassland][Donkey]   = uncommon;
        lt[Biome::Grassland][Rabbit]   = abundant;
        lt[Biome::Grassland][Antelope] = abundant;
        lt[Biome::Grassland][Bison]    = dominant;
        lt[Biome::Grassland][Wolf]     = semicommon;
        lt[Biome::Grassland][Bear]     = rare;
        lt[Biome::Grassland][Caribou]  = never;

        lt[Biome::Savanna][Pig]          = rare;
        lt[Biome::Savanna][Cow]          = common;
        lt[Biome::Savanna][Sheep]        = uncommon;
        lt[Biome::Savanna][Goat]         = semicommon;
        lt[Biome::Savanna][Camel]        = rare;
        lt[Biome::Savanna][WaterBuffalo] = uncommon;
        lt[Biome::Savanna][Rabbit]       = common;
        lt[Biome::Savanna][Antelope]     = abundant;
        lt[Biome::Savanna][Elephant]     = dominant;
        lt[Biome::Savanna][Bison]        = rare;
        lt[Biome::Savanna][Wolf]         = semicommon;
        lt[Biome::Savanna][Bear]         = rare;
        lt[Biome::Savanna][Caribou]      = never;

        lt[Biome::Wetland][Pig]          = common;
        lt[Biome::Wetland][Cow]          = uncommon;
        lt[Biome::Wetland][Sheep]        = rare;
        lt[Biome::Wetland][Goat]         = rare;
        lt[Biome::Wetland][Camel]        = rare;
        lt[Biome::Wetland][WaterBuffalo] = dominant;
        lt[Biome::Wetland][Rabbit]       = semicommon;
        lt[Biome::Wetland][Antelope]     = abundant;
        lt[Biome::Wetland][Elephant]     = semicommon;
        lt[Biome::Wetland][Bison]        = rare;
        lt[Biome::Wetland][Wolf]         = uncommon;
        lt[Biome::Wetland][Bear]         = semicommon;
        lt[Biome::Wetland][Caribou]      = never;

        lt[Biome::Temperate][Pig]      = semicommon;
        lt[Biome::Temperate][Cow]      = common;
        lt[Biome::Temperate][Sheep]    = uncommon;
        lt[Biome::Temperate][Goat]     = semicommon;
        lt[Biome::Temperate][Horse]    = rare;
        lt[Biome::Temperate][Ox]       = uncommon;
        lt[Biome::Temperate][Donkey]   = rare;
        lt[Biome::Temperate][Rabbit]   = abundant;
        lt[Biome::Temperate][Antelope] = rare;
        lt[Biome::Temperate][Deer]     = dominant;
        lt[Biome::Temperate][Moose]    = abundant;
        lt[Biome::Temperate][Wolf]     = semicommon;
        lt[Biome::Temperate][Bear]     = dominant;
        lt[Biome::Temperate][Caribou]  = never;

        lt[Biome::Boreal][Pig]      = rare;
        lt[Biome::Boreal][Cow]      = rare;
        lt[Biome::Boreal][Sheep]    = rare;
        lt[Biome::Boreal][Goat]     = rare;
        lt[Biome::Boreal][Horse]    = rare;
        lt[Biome::Boreal][Ox]       = rare;
        lt[Biome::Boreal][Donkey]   = rare;
        lt[Biome::Boreal][Rabbit]   = semicommon;
        lt[Biome::Boreal][Antelope] = never;
        lt[Biome::Boreal][Deer]     = abundant;
        lt[Biome::Boreal][Moose]    = dominant;
        lt[Biome::Boreal][Bison]    = rare;
        lt[Biome::Boreal][Wolf]     = semicommon;
        lt[Biome::Boreal][Bear]     = abundant;
        lt[Biome::Boreal][Caribou]  = dominant;

        lt[Biome::Jungle][Pig]      = rare;
        lt[Biome::Jungle][Cow]      = veryrare;
        lt[Biome::Jungle][Horse]    = rare;
        lt[Biome::Jungle][Ox]       = veryrare;
        lt[Biome::Jungle][Donkey]   = rare;
        lt[Biome::Jungle][Rabbit]   = rare;
        lt[Biome::Jungle][Antelope] = rare;
        lt[Biome::Jungle][Elephant] = abundant;
        lt[Biome::Jungle][Wolf]     = rare;
        lt[Biome::Jungle][Bear]     = rare;
        lt[Biome::Jungle][Caribou]  = never;

        lt[Biome::Rocky][Goat]  = common;
        lt[Biome::Rocky][Wolf]  = rare;
        lt[Biome::Rocky][Sheep] = rare;

        lt[Biome::Tundra][Pig]      = never;
        lt[Biome::Tundra][Cow]      = never;
        lt[Biome::Tundra][Sheep]    = rare;
        lt[Biome::Tundra][Goat]     = uncommon;
        lt[Biome::Tundra][Horse]    = never;
        lt[Biome::Tundra][Ox]       = rare;
        lt[Biome::Tundra][Donkey]   = never;
        lt[Biome::Tundra][Rabbit]   = semicommon;
        lt[Biome::Tundra][Antelope] = never;
        lt[Biome::Tundra][Elephant] = never;
        lt[Biome::Tundra][Bison]    = never;
        lt[Biome::Tundra][Wolf]     = abundant;
        lt[Biome::Tundra][Bear]     = rare;
        lt[Biome::Tundra][Caribou] = dominant;
    return lt;
  }();
		
inline constexpr LookupTable<Animal, Frame> WALKING_FRAME_PER_TILES = [] 
{
	LookupTable<Animal, Frame> lt{};
	using enum Animal;

	return lt;
}();

inline constexpr LookupTable<Animal, Frame> RUNNING_FRAME_PER_TILES = []
{
	LookupTable<Animal, Frame> lt{};
	using enum Animal;

	return lt;
}();

LookupTable<Animal, Frame> get_frame_per_tiles_table(bool running)
{
	if (running)
			return RUNNING_FRAME_PER_TILES;
	else return WALKING_FRAME_PER_TILES;
}

inline constexpr LookupTable<Animal, Time> BREEDING_INTERVALS = []
{
	LookupTable<Animal, Time> lt{};
	using enum Animal;
	lt[Animal::Pig] = YEAR_LENGTH * 2.4;
	lt[Animal::Cow] = YEAR_LENGTH * 3.0;
	lt[Animal::Chicken] = YEAR_LENGTH * 0.7;
	lt[Animal::Duck] = YEAR_LENGTH * 0.8;
	lt[Animal::Sheep] = YEAR_LENGTH * 2.4;
	lt[Animal::Goat] = YEAR_LENGTH * 2.4;
	lt[Animal::Horse] = YEAR_LENGTH * 4.0;
	lt[Animal::Ox] = YEAR_LENGTH * 3.2;
	lt[Animal::Donkey] = YEAR_LENGTH * 4.0;
	lt[Animal::Camel] = YEAR_LENGTH * 5.0;
	lt[Animal::WaterBuffalo] = YEAR_LENGTH * 4.0;
	lt[Animal::Rabbit] = YEAR_LENGTH * 0.6;
	lt[Animal::Antelope] = YEAR_LENGTH * 3.0;
	lt[Animal::Deer] = YEAR_LENGTH * 3.0;
	lt[Animal::Moose] = YEAR_LENGTH * 5.0;
	lt[Animal::Capybara] = YEAR_LENGTH * 2.0;
	lt[Animal::Turtle] = YEAR_LENGTH * 7.0;
	lt[Animal::Elephant] = YEAR_LENGTH * 12.0;
	lt[Animal::Bison] = YEAR_LENGTH * 4.0;
	lt[Animal::Wolf] = YEAR_LENGTH * 4.0;
	lt[Animal::Bear] = YEAR_LENGTH * 7.0;
	lt[Animal::Caribou] = YEAR_LENGTH * 3.0;
	lt[Animal::Fish] = YEAR_LENGTH * 0.5;
	return lt;
}();

inline constexpr LookupTable<Animal,Time> PREGNANCY_LENGTHS = [] {
  LookupTable<Animal,Time> lt{};
  using enum Animal;
  lt[Animal::Pig] = 114 * DAY_LENGTH;
lt[Animal::Cow] = 283 * DAY_LENGTH;
lt[Animal::Chicken] = 21 * DAY_LENGTH;
lt[Animal::Duck] = 28 * DAY_LENGTH;
lt[Animal::Sheep] = 151 * DAY_LENGTH;
lt[Animal::Goat] = 150 * DAY_LENGTH;
lt[Animal::Horse] = 335 * DAY_LENGTH;
lt[Animal::Ox] = 283 * DAY_LENGTH;
lt[Animal::Donkey] = 365 * DAY_LENGTH;
lt[Animal::Camel] = 395 * DAY_LENGTH;
lt[Animal::WaterBuffalo] = 325 * DAY_LENGTH;
lt[Animal::Rabbit] = 31 * DAY_LENGTH;
lt[Animal::Antelope] = 200 * DAY_LENGTH;
lt[Animal::Deer] = 205 * DAY_LENGTH;
lt[Animal::Moose] = 235 * DAY_LENGTH;
lt[Animal::Capybara] = 150 * DAY_LENGTH;
lt[Animal::Turtle] = 60 * DAY_LENGTH;
lt[Animal::Elephant] = 660 * DAY_LENGTH;
lt[Animal::Bison] = 285 * DAY_LENGTH;
lt[Animal::Wolf] = 63 * DAY_LENGTH;
lt[Animal::Bear] = 220 * DAY_LENGTH;
lt[Animal::Caribou] = 230 * DAY_LENGTH;
lt[Animal::Fish] = 4 * DAY_LENGTH;
  return lt;
 }();  

inline constexpr LookupTable<Animal,float> BASE_FERTILITY_CHANCES = [] {
  LookupTable<Animal,float> lt{};
  using enum Animal;
  lt[Animal::Pig] = 0.90f;
lt[Animal::Cow] = 0.85f;
lt[Animal::Chicken] = 0.95f;
lt[Animal::Duck] = 0.90f;
lt[Animal::Sheep] = 0.90f;
lt[Animal::Goat] = 0.90f;
lt[Animal::Horse] = 0.80f;
lt[Animal::Ox] = 0.85f;
lt[Animal::Donkey] = 0.80f;
lt[Animal::Camel] = 0.75f;
lt[Animal::WaterBuffalo] = 0.80f;
lt[Animal::Rabbit] = 0.95f;
lt[Animal::Antelope] = 0.80f;
lt[Animal::Deer] = 0.85f;
lt[Animal::Moose] = 0.75f;
lt[Animal::Capybara] = 0.90f;
lt[Animal::Turtle] = 0.70f;
lt[Animal::Elephant] = 0.60f;
lt[Animal::Bison] = 0.80f;
lt[Animal::Wolf] = 0.80f;
lt[Animal::Bear] = 0.70f;
lt[Animal::Caribou] = 0.80f;
lt[Animal::Fish] = 0.98f;
  return lt;
 }();
  
// in terms of hunger consumed per hour
inline constexpr LookupTable<Animal, Hunger> EATING_SPEEDS = []
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

inline constexpr LookupTable<Animal, Time> MAX_AGES = []
{
	LookupTable<Animal, Time> lt{};
	using enum Animal;
	lt[Animal::Pig] = static_cast<int>(15.0 * YEAR_LENGTH);
	lt[Animal::Cow] = static_cast<int>(20.0 * YEAR_LENGTH);
	lt[Animal::Chicken] = static_cast<int>(8.0 * YEAR_LENGTH);
	lt[Animal::Duck] = static_cast<int>(10.0 * YEAR_LENGTH);
	lt[Animal::Sheep] = static_cast<int>(12.0 * YEAR_LENGTH);
	lt[Animal::Goat] = static_cast<int>(15.0 * YEAR_LENGTH);
	lt[Animal::Horse] = static_cast<int>(30.0 * YEAR_LENGTH);
	lt[Animal::Ox] = static_cast<int>(20.0 * YEAR_LENGTH);
	lt[Animal::Donkey] = static_cast<int>(30.0 * YEAR_LENGTH);
	lt[Animal::Camel] = static_cast<int>(40.0 * YEAR_LENGTH);
	lt[Animal::WaterBuffalo] = static_cast<int>(25.0 * YEAR_LENGTH);
	lt[Animal::Rabbit] = static_cast<int>(9.0 * YEAR_LENGTH);
	lt[Animal::Antelope] = static_cast<int>(12.0 * YEAR_LENGTH);
	lt[Animal::Deer] = static_cast<int>(15.0 * YEAR_LENGTH);
	lt[Animal::Moose] = static_cast<int>(20.0 * YEAR_LENGTH);
	lt[Animal::Capybara] = static_cast<int>(10.0 * YEAR_LENGTH);
	lt[Animal::Turtle] = static_cast<int>(80.0 * YEAR_LENGTH);
	lt[Animal::Elephant] = static_cast<int>(70.0 * YEAR_LENGTH);
	lt[Animal::Bison] = static_cast<int>(20.0 * YEAR_LENGTH);
	lt[Animal::Wolf] = static_cast<int>(13.0 * YEAR_LENGTH);
	lt[Animal::Bear] = static_cast<int>(25.0 * YEAR_LENGTH);
	lt[Animal::Caribou] = static_cast<int>(15.0 * YEAR_LENGTH);
	lt[Animal::Fish] = static_cast<int>(5.0 * YEAR_LENGTH);
	return lt;
}();

inline constexpr LookupTable<Animal, float> FERTILITY_AGES = []
{
	LookupTable<Animal, float> lt;
	lt[Animal::Pig] = 0.10f;
	lt[Animal::Cow] = 0.18f;
	lt[Animal::Chicken] = 0.22f;
	lt[Animal::Duck] = 0.22f;
	lt[Animal::Sheep] = 0.18f;
	lt[Animal::Goat] = 0.18f;
	lt[Animal::Horse] = 0.20f;
	lt[Animal::Ox] = 0.18f;
	lt[Animal::Donkey] = 0.20f;
	lt[Animal::Camel] = 0.25f;
	lt[Animal::WaterBuffalo] = 0.20f;
	lt[Animal::Rabbit] = 0.18f;
	lt[Animal::Antelope] = 0.20f;
	lt[Animal::Deer] = 0.20f;
	lt[Animal::Moose] = 0.22f;
	lt[Animal::Capybara] = 0.18f;
	lt[Animal::Turtle] = 0.10f;
	lt[Animal::Elephant] = 0.15f;
	lt[Animal::Bison] = 0.18f;
	lt[Animal::Wolf] = 0.25f;
	lt[Animal::Bear] = 0.22f;
	lt[Animal::Caribou] = 0.20f;
	lt[Animal::Fish] = 0.08f;
        for (size_t i = 0; i < static_cast<size_t>(Animal::MAX); i++)
	{
		lt[static_cast<Animal>(i)] *= MAX_AGES[static_cast<Animal>(i)];
        }
	return lt;
}();

  
inline constexpr LookupTable<Animal, float> SENESCENCE_AGES = [] {
	LookupTable<Animal, float> lt{};
	using enum Animal;

	lt[Pig]           = 0.80f;
	lt[Cow]           = 0.75f;
	lt[Chicken]       = 0.80f;
	lt[Duck]          = 0.80f;
	lt[Sheep]         = 0.75f;
	lt[Goat]          = 0.75f;
	lt[Horse]         = 0.75f;
	lt[Ox]            = 0.75f;
	lt[Donkey]        = 0.75f;
	lt[Camel]         = 0.75f;
	lt[WaterBuffalo]  = 0.75f;
	lt[Rabbit]        = 0.85f;
	lt[Antelope]      = 0.75f;
	lt[Deer]          = 0.75f;
	lt[Moose]         = 0.75f;
	lt[Capybara]      = 0.80f;
	lt[Turtle]        = 0.85f;
	lt[Elephant]      = 0.70f;
	lt[Bison]         = 0.75f;
	lt[Wolf]          = 0.75f;
	lt[Bear]          = 0.70f;
	lt[Caribou]       = 0.75f;
	lt[Fish]          = 0.85f;
        for (size_t i = 0; i < static_cast<size_t>(Animal::MAX); i++) {
          lt[static_cast<Animal>(i)] *= MAX_AGES[static_cast<Animal>(i)];
        }
	return lt;
}();

inline constexpr LookupTable<Animal, uint16_t> HUNGER_SEARCH_THRESHOLD = []
{
	LookupTable<Animal, uint16_t> lt;
	using enum Animal;

	return lt;
}();

inline constexpr LookupTable<Animal, uint16_t> SIGHT_RANGES = []
{
	LookupTable<Animal, uint16_t> lt;

	lt[Animal::Pig] = 50;
	lt[Animal::Cow] = 150;
	lt[Animal::Chicken] = 30;
	lt[Animal::Duck] = 80;
	lt[Animal::Sheep] = 200;
	lt[Animal::Goat] = 250;
	lt[Animal::Horse] = 300;
	lt[Animal::Ox] = 150;
	lt[Animal::Donkey] = 200;
	lt[Animal::Camel] = 500;
	lt[Animal::WaterBuffalo] = 100;
	lt[Animal::Rabbit] = 100;
	lt[Animal::Antelope] = 600;
	lt[Animal::Deer] = 500;
	lt[Animal::Moose] = 300;
	lt[Animal::Capybara] = 80;
	lt[Animal::Turtle] = 30;
	lt[Animal::Elephant] = 200;
	lt[Animal::Bison] = 300;
	lt[Animal::Wolf] = 1000;
	lt[Animal::Bear] = 400;
	lt[Animal::Caribou] = 600;
	lt[Animal::Fish] = 20;

	return lt;
}();

inline constexpr LookupTable<Animal, Speed> MIN_SPEED = []
{
	LookupTable<Animal, Speed> lt;

	lt[Animal::Pig] = 1.5f;
	lt[Animal::Cow] = 1.0f;
	lt[Animal::Chicken] = 0.8f;
	lt[Animal::Duck] = 0.8f;
	lt[Animal::Sheep] = 1.0f;
	lt[Animal::Goat] = 1.0f;
	lt[Animal::Horse] = 1.6f;
	lt[Animal::Ox] = 1.0f;
	lt[Animal::Donkey] = 1.2f;
	lt[Animal::Camel] = 1.3f;
	lt[Animal::WaterBuffalo] = 0.9f;
	lt[Animal::Rabbit] = 1.0f;
	lt[Animal::Antelope] = 2.0f;
	lt[Animal::Deer] = 1.8f;
	lt[Animal::Moose] = 1.2f;
	lt[Animal::Capybara] = 0.8f;
	lt[Animal::Turtle] = 0.05f;
	lt[Animal::Elephant] = 1.5f;
	lt[Animal::Bison] = 1.5f;
	lt[Animal::Wolf] = 1.8f;
	lt[Animal::Bear] = 1.3f;
	lt[Animal::Caribou] = 1.8f;
	lt[Animal::Fish] = 0.5f;

	return lt;
}();

inline constexpr LookupTable<Animal, Speed> MAX_SPEED = []
{
	LookupTable<Animal, Speed> lt;

	lt[Animal::Pig] = 6.0f;
	lt[Animal::Cow] = 7.5f;
	lt[Animal::Chicken] = 4.0f;
	lt[Animal::Duck] = 10.0f;
	lt[Animal::Sheep] = 14.0f;
	lt[Animal::Goat] = 12.0f;
	lt[Animal::Horse] = 22.0f;
	lt[Animal::Ox] = 5.5f;
	lt[Animal::Donkey] = 8.3f;
	lt[Animal::Camel] = 14.0f;
	lt[Animal::WaterBuffalo] = 5.0f;
	lt[Animal::Rabbit] = 17.0f;
	lt[Animal::Antelope] = 27.0f;
	lt[Animal::Deer] = 22.0f;
	lt[Animal::Moose] = 15.0f;
	lt[Animal::Capybara] = 8.3f;
	lt[Animal::Turtle] = 0.3f;
	lt[Animal::Elephant] = 6.8f;
	lt[Animal::Bison] = 18.0f;
	lt[Animal::Wolf] = 17.0f;
	lt[Animal::Bear] = 13.4f;
	lt[Animal::Caribou] = 20.0f;
	lt[Animal::Fish] = 8.0f;

	return lt;
}();

inline constexpr LookupTable<Animal, Health> MAX_HEALTHS = []
{
	LookupTable<Animal, Health> lt{};
	using enum Animal;

	return lt;
}();

inline constexpr LookupTable<Animal, Hunger> MAX_HUNGERS = []
{
	LookupTable<Animal, Hunger> lt{};
	using enum Animal;

	return lt;
}();
	
inline constexpr const BitsetTable<Animal> IS_EGG_LAYER = []
{
	BitsetTable<Animal> t;
	auto add = [&](Animal a) { t.bitset.set(static_cast<uint16_t>(a)); };
	
	add(Animal::Chicken);
	add(Animal::Duck);
	add(Animal::Turtle);
	add(Animal::Fish);
	return t;
}();

inline constexpr LookupTable<Animal, Time> HATCH_TIMES = []
{
	LookupTable<Animal, Time> lt{};
	using enum Animal;
	lt[Chicken] = DAY_LENGTH * 23;
	lt[Duck] = DAY_LENGTH * 29;
	lt[Turtle] = DAY_LENGTH * 99;
	// TODO: fish
	return lt;
}();

inline constexpr LookupTable<Animal, Time> BREEDING_SEASON_START = []
{
	LookupTable<Animal, Time> lt{};
	using enum Animal;

	return lt;
}();

inline constexpr LookupTable<Animal, Time> BREEDING_SEASON_END = []
{
	LookupTable<Animal, Time> lt{};
	using enum Animal;

	return lt;
}();

inline constexpr LookupTable<Animal, Time> MIGRATION_SEASON_START = []
{
	LookupTable<Animal, Time> lt{};
	using enum Animal;

	return lt;
}();

  inline constexpr LookupTable<Animal,Time> MIGRATION_SEASON_END = [] {
    LookupTable<Animal,Time> lt{};
    using enum Animal;
    
    return lt;
  }();

}//namespace animal

#endif
