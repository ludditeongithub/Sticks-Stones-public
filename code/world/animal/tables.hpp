#ifndef LIFESTATS_HPP
#define LIFESTATS_HPP

#include "enum.hpp"
#include <core/data.hpp>
#include <core/tables.hpp>
#include <core/time.hpp>
#include <world/tile/enum.hpp>

namespace animal
{
inline constexpr LookupTable<Animal, Frame> walking_frame_per_tiles = [] 
{
	LookupTable<Animal, Frame> lt{};
	using enum Animal;

	return lt;
}();

inline constexpr LookupTable<Animal, Frame> running_frame_per_tiles = []
{
	LookupTable<Animal, Frame> lt{};
	using enum Animal;

	return lt;
}();

LookupTable<Animal, Frame> get_frame_per_tiles_table(bool running)
{
	if (running)
			return runningFramePerTiles;
	else return walkingFramePerTiles;
}

inline constexpr LookupTable<Animal, Time> breeding_intervals = []
{
	LookupTable<Animal, Time> lt{};
	using enum Animal;
	lt[Animal::Pig] = year_length * 2.4;
	lt[Animal::Cow] = year_length * 3.0;
	lt[Animal::Chicken] = year_length * 0.7;
	lt[Animal::Duck] = year_length * 0.8;
	lt[Animal::Sheep] = year_length * 2.4;
	lt[Animal::Goat] = year_length * 2.4;
	lt[Animal::Horse] = year_length * 4.0;
	lt[Animal::Ox] = year_length * 3.2;
	lt[Animal::Donkey] = year_length * 4.0;
	lt[Animal::Camel] = year_length * 5.0;
	lt[Animal::WaterBuffalo] = year_length * 4.0;
	lt[Animal::Rabbit] = year_length * 0.6;
	lt[Animal::Antelope] = year_length * 3.0;
	lt[Animal::Deer] = year_length * 3.0;
	lt[Animal::Moose] = year_length * 5.0;
	lt[Animal::Capybara] = year_length * 2.0;
	lt[Animal::Turtle] = year_length * 7.0;
	lt[Animal::Elephant] = year_length * 12.0;
	lt[Animal::Bison] = year_length * 4.0;
	lt[Animal::Wolf] = year_length * 4.0;
	lt[Animal::Bear] = year_length * 7.0;
	lt[Animal::Caribou] = year_length * 3.0;
	lt[Animal::Fish] = YEAR_LENGTH * 0.5;
	return lt;
}();

inline constexpr LookupTable<Animal,Time> pregnancy_lengths = [] {
  LookupTable<Animal,Time> lt{};
  using enum Animal;
  lt[Animal::Pig] = 114 * day_length;
lt[Animal::Cow] = 283 * day_length;
lt[Animal::Chicken] = 21 * day_length;
lt[Animal::Duck] = 28 * day_length;
lt[Animal::Sheep] = 151 * day_length;
lt[Animal::Goat] = 150 * day_length;
lt[Animal::Horse] = 335 * day_length;
lt[Animal::Ox] = 283 * day_length;
lt[Animal::Donkey] = 365 * day_length;
lt[Animal::Camel] = 395 * day_length;
lt[Animal::WaterBuffalo] = 325 * day_length;
lt[Animal::Rabbit] = 31 * day_length;
lt[Animal::Antelope] = 200 * day_length;
lt[Animal::Deer] = 205 * day_length;
lt[Animal::Moose] = 235 * day_length;
lt[Animal::Capybara] = 150 * day_length;
lt[Animal::Turtle] = 60 * day_length;
lt[Animal::Elephant] = 660 * day_length;
lt[Animal::Bison] = 285 * day_length;
lt[Animal::Wolf] = 63 * day_length;
lt[Animal::Bear] = 220 * day_length;
lt[Animal::Caribou] = 230 * day_length;
lt[Animal::Fish] = 4 * DAY_LENGTH;
  return lt;
 }();  

inline constexpr LookupTable<Animal,float> base_fertility_chances = [] {
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
inline constexpr LookupTable<Animal, Hunger> eating_speeds = []
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

inline constexpr LookupTable<Animal, Time> max_ages = []
{
	LookupTable<Animal, Time> lt{};
	using enum Animal;
	lt[Animal::Pig] = static_cast<int>(15.0 * year_length);
	lt[Animal::Cow] = static_cast<int>(20.0 * year_length);
	lt[Animal::Chicken] = static_cast<int>(8.0 * year_length);
	lt[Animal::Duck] = static_cast<int>(10.0 * year_length);
	lt[Animal::Sheep] = static_cast<int>(12.0 * year_length);
	lt[Animal::Goat] = static_cast<int>(15.0 * year_length);
	lt[Animal::Horse] = static_cast<int>(30.0 * year_length);
	lt[Animal::Ox] = static_cast<int>(20.0 * year_length);
	lt[Animal::Donkey] = static_cast<int>(30.0 * year_length);
	lt[Animal::Camel] = static_cast<int>(40.0 * year_length);
	lt[Animal::WaterBuffalo] = static_cast<int>(25.0 * year_length);
	lt[Animal::Rabbit] = static_cast<int>(9.0 * year_length);
	lt[Animal::Antelope] = static_cast<int>(12.0 * year_length);
	lt[Animal::Deer] = static_cast<int>(15.0 * year_length);
	lt[Animal::Moose] = static_cast<int>(20.0 * year_length);
	lt[Animal::Capybara] = static_cast<int>(10.0 * year_length);
	lt[Animal::Turtle] = static_cast<int>(80.0 * year_length);
	lt[Animal::Elephant] = static_cast<int>(70.0 * year_length);
	lt[Animal::Bison] = static_cast<int>(20.0 * year_length);
	lt[Animal::Wolf] = static_cast<int>(13.0 * year_length);
	lt[Animal::Bear] = static_cast<int>(25.0 * year_length);
	lt[Animal::Caribou] = static_cast<int>(15.0 * year_length);
	lt[Animal::Fish] = static_cast<int>(5.0 * YEAR_LENGTH);
	return lt;
}();

inline constexpr LookupTable<Animal, Time> fertility_ages = []
{
	LookupTable<Animal, Time> lt;
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
		lt[static_cast<Animal>(i)] *= maxAges[static_cast<Animal>(i)];
        }
	return lt;
}();

  
inline constexpr LookupTable<Animal, Time> senescence_ages = [] {
	LookupTable<Animal, Time> lt{};
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
          lt[static_cast<Animal>(i)] *= maxAges[static_cast<Animal>(i)];
        }
	return lt;
}();

inline LookupTable<Animal, uint16_t> hunger_search_threshold = []
{
	LookupTable<Animal, uint16_t> lt;
	using enum Animal;

	return lt;
}();

inline constexpr LookupTable<Animal, uint16_t> sight_ranges = []
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

inline constexpr LookupTable<Animal, Speed> min_speed = []
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

inline constexpr LookupTable<Animal, Speed> max_speed = []
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

inline constexpr LookupTable<Animal, Health> max_healths = []
{
	LookupTable<Animal, Health> lt{};
	using enum Animal;

	return lt;
}();

inline constexpr LookupTable<Animal, Hunger> max_hungers = []
{
	LookupTable<Animal, Hunger> lt{};
	using enum Animal;

	return lt;
}();
	
inline constexpr const BitsetTable<Animal> is_egg_layer = []
{
	BitsetTable<Animal> t;
	auto add = [&](Animal a) { t.bitset.set(static_cast<uint16_t>(a)); };
	
	add(Animal::Chicken);
	add(Animal::Duck);
	add(Animal::Turtle);
	add(Animal::Fish);
	return t;
}();

inline constexpr LookupTable<Animal,Time> hatch_times = [] {
		LookupTable<Animal,Time> lt{};
		using enum Animal;
		lt[Chicken] = day_length * 23;
		lt[Duck] = day_length * 29;
		lt[Turtle] = day_length * 99;
		// TODO: fish
		return lt;
}();

}//namespace animal

#endif
