#pragma once
#include "enum.hpp"
#include <array>
#include <core/containers.hpp>

#include <core/tables.hpp>
#include <data/run/world.hpp>

using enum Plant;
using PlantTable = LookupTable<PlantCategory, float>;

constexpr float UNOPTIMAL_TEMP_MULT = 0.65;
constexpr float LOW_WATER_MULT = 0.55;

// TODO: manage sunlight and sun values
// TODO: change these all to uint16_ts
inline constexpr LookupTable<Plant, float> WATER_DEATH_MIN = []
{
	LookupTable<Plant, float> arr{};
	arr[Fern] = 10.0;
	arr[Moss] = 14.0;
	arr[Reed] = 16.0;
	arr[Wheat] = 8.0;
	arr[Oat] = 8.0;
	arr[Rice] = 14.0;
	arr[Bush] = 7.5;
	arr[Papyrus] = 16.5;
	arr[PioneerTree] = 7.0;
	arr[DeciduousTree] = 8.0;
	arr[EvergreenTree] = 6.5;
	arr[TropicalTree] = 12.5;
	arr[Cactus] = 2.0;
	arr[Grapevine] = 6.5;
	arr[Lettuce] = 6.5;
	arr[Kale] = 6.0;
	arr[Corn] = 12.0;
	arr[Carrot] = 8.0;
	arr[Beets] = 7.5;
	arr[Potato] = 9.0;
	arr[Onion] = 6.0;
	arr[Garlic] = 5.5;
	arr[Cabbage] = 6.0;
	arr[Broccoli] = 6.5;
	arr[Tomato] = 8.0;
	arr[Cucumber] = 9.0;
	arr[Pepper] = 8.0;
	arr[BlackPepper] = 11.0;
	arr[Cotton] = 15.5;
	arr[Hemp] = 9.5;
	arr[Flax] = 8.0;
	arr[Woad] = 7.0;
	arr[Madder] = 7.5;
	arr[Indigo] = 10.0;
	arr[Lavender] = 4.5;
	arr[Mint] = 10.5;
	arr[Thyme] = 4.0;
	arr[Sage] = 4.5;
	arr[Ginseng] = 9.5;
	arr[Rhubarb] = 8.5;
	arr[Poppy] = 8.0;
	arr[Cocoa] = 13.0;
	arr[Senna] = 8.5;
	arr[Saffron] = 3.5;
	arr[AloeVera] = 3.0;
	arr[Orange] = 12.0;
	arr[Apple] = 8.0;
	arr[Lemon] = 12.0;
	arr[Pear] = 8.0;
	arr[Peach] = 9.0;
	arr[Cherry] = 8.5;
	arr[Apricot] = 8.5;
	arr[Plum] = 8.5;
	arr[Lime] = 12.5;
	arr[Blueberry] = 11.0;
	arr[Strawberry] = 9.0;
	arr[Grape] = 6.5;
	arr[Olive] = 5.0;

	return arr;
}();

inline constexpr LookupTable<Plant, float> WATER_DEATH = []
{
	LookupTable<Plant, float> arr{};

	arr[NONE] = 0.0;
	arr[Fern] = HOUR_LENGTH * 18;
	arr[Moss] = HOUR_LENGTH * 12;
	arr[Reed] = HOUR_LENGTH * 4;
	arr[Wheat] = HOUR_LENGTH * 70;
	arr[Oat] = HOUR_LENGTH * 42;
	arr[Rice] = HOUR_LENGTH * 20;
	arr[Bush] = HOUR_LENGTH * 60;
	arr[Papyrus] = HOUR_LENGTH * 1;
	arr[PioneerTree] = HOUR_LENGTH * 120;
	arr[DeciduousTree] = HOUR_LENGTH * 140;
	arr[EvergreenTree] = HOUR_LENGTH * 160;
	arr[TropicalTree] = HOUR_LENGTH * 80;
	arr[Cactus] = HOUR_LENGTH * 400;
	arr[Grapevine] = HOUR_LENGTH * 90;
	arr[Lettuce] = HOUR_LENGTH * 20;
	arr[Kale] = HOUR_LENGTH * 28;
	arr[Corn] = HOUR_LENGTH * 36;
	arr[Carrot] = HOUR_LENGTH * 30;
	arr[Beets] = HOUR_LENGTH * 32;
	arr[Potato] = HOUR_LENGTH * 28;
	arr[Onion] = HOUR_LENGTH * 36;
	arr[Garlic] = HOUR_LENGTH * 42;
	arr[Cabbage] = HOUR_LENGTH * 36;
	arr[Broccoli] = HOUR_LENGTH * 30;
	arr[Tomato] = HOUR_LENGTH * 20;
	arr[Cucumber] = HOUR_LENGTH * 22;
	arr[Pepper] = HOUR_LENGTH * 20;
	arr[BlackPepper] = HOUR_LENGTH * 26;
	arr[Cotton] = HOUR_LENGTH * 104;
	arr[Hemp] = HOUR_LENGTH * 52;
	arr[Flax] = HOUR_LENGTH * 30;
	arr[Woad] = HOUR_LENGTH * 48;
	arr[Madder] = HOUR_LENGTH * 55;
	arr[Indigo] = HOUR_LENGTH * 40;
	arr[Lavender] = HOUR_LENGTH * 120;
	arr[Mint] = HOUR_LENGTH * 24;
	arr[Thyme] = HOUR_LENGTH * 140;
	arr[Sage] = HOUR_LENGTH * 120;
	arr[Ginseng] = HOUR_LENGTH * 60;
	arr[Rhubarb] = HOUR_LENGTH * 50;
	arr[Poppy] = HOUR_LENGTH * 29;
	arr[Cocoa] = HOUR_LENGTH * 30;
	arr[Senna] = HOUR_LENGTH * 68;
	arr[Saffron] = HOUR_LENGTH * 180;
	arr[AloeVera] = HOUR_LENGTH * 220;
	arr[Orange] = HOUR_LENGTH * 80;
	arr[Apple] = HOUR_LENGTH * 120;
	arr[Lemon] = HOUR_LENGTH * 75;
	arr[Pear] = HOUR_LENGTH * 120;
	arr[Peach] = HOUR_LENGTH * 100;
	arr[Cherry] = HOUR_LENGTH * 110;
	arr[Apricot] = HOUR_LENGTH * 100;
	arr[Plum] = HOUR_LENGTH * 110;
	arr[Lime] = HOUR_LENGTH * 70;
	arr[Blueberry] = HOUR_LENGTH * 40;
	arr[Strawberry] = HOUR_LENGTH * 24;
	arr[Grape] = HOUR_LENGTH * 90;
	arr[Olive] = HOUR_LENGTH * 200;

	return arr;
}();

inline constexpr LookupTable<Plant, float> WATER_REQUIRED = []
{
	LookupTable<Plant, float> arr{};

	arr[NONE] = 0.0;
	arr[Fern] = 900.0 / DAY_LENGTH;
	arr[Moss] = 1200.0 / DAY_LENGTH;
	arr[Reed] = 1400.0 / DAY_LENGTH;
	arr[Wheat] = 750.0 / DAY_LENGTH;
	arr[Oat] = 650.0 / DAY_LENGTH;
	arr[Rice] = 1750.0 / DAY_LENGTH;
	arr[Bush] = 700.0 / DAY_LENGTH;
	arr[Papyrus] = 1500.0 / DAY_LENGTH;
	arr[PioneerTree] = 800.0 / DAY_LENGTH;
	arr[DeciduousTree] = 900.0 / DAY_LENGTH;
	arr[EvergreenTree] = 700.0 / DAY_LENGTH;
	arr[TropicalTree] = 1300.0 / DAY_LENGTH;
	arr[Cactus] = 100.0 / DAY_LENGTH;
	arr[Grapevine] = 700.0 / DAY_LENGTH;
	arr[Lettuce] = 400.0 / DAY_LENGTH;
	arr[Kale] = 500.0 / DAY_LENGTH;
	arr[Corn] = 1250.0 / DAY_LENGTH;
	arr[Carrot] = 600.0 / DAY_LENGTH;
	arr[Beets] = 650.0 / DAY_LENGTH;
	arr[Potato] = 750.0 / DAY_LENGTH;
	arr[Onion] = 450.0 / DAY_LENGTH;
	arr[Garlic] = 400.0 / DAY_LENGTH;
	arr[Cabbage] = 600.0 / DAY_LENGTH;
	arr[Broccoli] = 700.0 / DAY_LENGTH;
	arr[Tomato] = 750.0 / DAY_LENGTH;
	arr[Cucumber] = 800.0 / DAY_LENGTH;
	arr[Pepper] = 450.0 / DAY_LENGTH;
	arr[BlackPepper] = 900.0 / DAY_LENGTH;
	arr[Cotton] = 800.0 / DAY_LENGTH;
	arr[Hemp] = 750.0 / DAY_LENGTH;
	arr[Flax] = 600.0 / DAY_LENGTH;
	arr[Woad] = 600.0 / DAY_LENGTH;
	arr[Madder] = 650.0 / DAY_LENGTH;
	arr[Indigo] = 900.0 / DAY_LENGTH;
	arr[Lavender] = 300.0 / DAY_LENGTH;
	arr[Mint] = 800.0 / DAY_LENGTH;
	arr[Thyme] = 250.0 / DAY_LENGTH;
	arr[Sage] = 300.0 / DAY_LENGTH;
	arr[Ginseng] = 850.0 / DAY_LENGTH;
	arr[Rhubarb] = 750.0 / DAY_LENGTH;
	arr[Poppy] = 450.0 / DAY_LENGTH;
	arr[Cocoa] = 1400.0 / DAY_LENGTH;
	arr[Senna] = 300.0 / DAY_LENGTH;
	arr[Saffron] = 200.0 / DAY_LENGTH;
	arr[AloeVera] = 150.0 / DAY_LENGTH;
	arr[Orange] = 1200.0 / DAY_LENGTH;
	arr[Apple] = 900.0 / DAY_LENGTH;
	arr[Lemon] = 1200.0 / DAY_LENGTH;
	arr[Pear] = 900.0 / DAY_LENGTH;
	arr[Peach] = 950.0 / DAY_LENGTH;
	arr[Cherry] = 900.0 / DAY_LENGTH;
	arr[Apricot] = 900.0 / DAY_LENGTH;
	arr[Plum] = 900.0 / DAY_LENGTH;
	arr[Lime] = 1250.0 / DAY_LENGTH;
	arr[Blueberry] = 800.0 / DAY_LENGTH;
	arr[Strawberry] = 600.0 / DAY_LENGTH;
	arr[Grapevine] = 700.0 / DAY_LENGTH;
	arr[Olive] = 400.0 / DAY_LENGTH;

	return arr;
}();

inline constexpr LookupTable<Plant, float> TEMP_DEATH_MIN = []
{
	LookupTable<Plant, float> arr{};

	arr[NONE] = 0.0;
	arr[Fern] = -5.0;
	arr[Moss] = -10.0;
	arr[Reed] = -2.0;
	arr[Wheat] = -10.0;
	arr[Oat] = -8.0;
	arr[Rice] = 6.0;
	arr[Bush] = -8.0;
	arr[Papyrus] = 0.0;
	arr[PioneerTree] = -15.0;
	arr[DeciduousTree] = -25.0;
	arr[EvergreenTree] = -30.0;
	arr[TropicalTree] = 5.0;
	arr[Cactus] = 0.0;
	arr[Grapevine] = -12.0;
	arr[Lettuce] = 0.0;
	arr[Kale] = -10.0;
	arr[Corn] = 0.0;
	arr[Carrot] = -6.0;
	arr[Beets] = -5.0;
	arr[Potato] = -2.0;
	arr[Onion] = -5.0;
	arr[Garlic] = -10.0;
	arr[Cabbage] = -5.0;
	arr[Broccoli] = -3.0;
	arr[Tomato] = 0.0;
	arr[Cucumber] = 5.0;
	arr[Pepper] = 5.0;
	arr[BlackPepper] = 10.0;
	arr[Cotton] = 0.0;
	arr[Hemp] = -5.0;
	arr[Flax] = -5.0;
	arr[Woad] = -5.0;
	arr[Madder] = -5.0;
	arr[Indigo] = 5.0;
	arr[Lavender] = -5.0;
	arr[Mint] = -5.0;
	arr[Thyme] = -10.0;
	arr[Sage] = -8.0;
	arr[Ginseng] = -10.0;
	arr[Rhubarb] = -10.0;
	arr[Poppy] = -5.0;
	arr[Cocoa] = 10.0;
	arr[Senna] = 0.0;
	arr[Saffron] = -10.0;
	arr[AloeVera] = 0.0;
	arr[Orange] = -2.0;
	arr[Apple] = -25.0;
	arr[Lemon] = -2.0;
	arr[Pear] = -25.0;
	arr[Peach] = -20.0;
	arr[Cherry] = -25.0;
	arr[Apricot] = -20.0;
	arr[Plum] = -20.0;
	arr[Lime] = 0.0;
	arr[Blueberry] = -15.0;
	arr[Strawberry] = -10.0;
	arr[Grape] = -15.0;
	arr[Olive] = -10.0;

	return arr;
}();

// TODO : change these to int16_ts?
inline constexpr LookupTable<Plant, float> TEMP_DEATH_MAX = []
{
	LookupTable<Plant, float> arr{};

	arr[NONE] = 0.0;
	arr[Fern] = 35.0;
	arr[Moss] = 30.0;
	arr[Reed] = 42.0;
	arr[Wheat] = 42.0;
	arr[Oat] = 42.0;
	arr[Rice] = 45.0;
	arr[Bush] = 42.0;
	arr[Papyrus] = 45.0;
	arr[PioneerTree] = 45.0;
	arr[DeciduousTree] = 45.0;
	arr[EvergreenTree] = 42.0;
	arr[TropicalTree] = 48.0;
	arr[Cactus] = 55.0;
	arr[Grapevine] = 42.0;
	arr[Lettuce] = 32.0;
	arr[Kale] = 35.0;
	arr[Corn] = 45.0;
	arr[Carrot] = 40.0;
	arr[Beets] = 40.0;
	arr[Potato] = 40.0;
	arr[Onion] = 40.0;
	arr[Garlic] = 40.0;
	arr[Cabbage] = 40.0;
	arr[Broccoli] = 38.0;
	arr[Tomato] = 40.0;
	arr[Cucumber] = 42.0;
	arr[Pepper] = 40.0;
	arr[BlackPepper] = 42.0;
	arr[Cotton] = 45.0;
	arr[Hemp] = 40.0;
	arr[Flax] = 40.0;
	arr[Woad] = 40.0;
	arr[Madder] = 42.0;
	arr[Indigo] = 45.0;
	arr[Lavender] = 42.0;
	arr[Mint] = 35.0;
	arr[Thyme] = 45.0;
	arr[Sage] = 42.0;
	arr[Ginseng] = 35.0;
	arr[Rhubarb] = 35.0;
	arr[Poppy] = 40.0;
	arr[Cocoa] = 45.0;
	arr[Senna] = 45.0;
	arr[Saffron] = 42.0;
	arr[AloeVera] = 50.0;
	arr[Orange] = 45.0;
	arr[Apple] = 42.0;
	arr[Lemon] = 45.0;
	arr[Pear] = 42.0;
	arr[Peach] = 42.0;
	arr[Cherry] = 42.0;
	arr[Apricot] = 42.0;
	arr[Plum] = 42.0;
	arr[Lime] = 45.0;
	arr[Blueberry] = 35.0;
	arr[Strawberry] = 35.0;
	arr[Grape] = 42.0;
	arr[Olive] = 45.0;

	return arr;
}();

inline constexpr LookupTable<Plant, float> TEMP_OPTIMAL_MIN = []
{
	LookupTable<Plant, float> arr{};

	arr[NONE] = 0.0;
	arr[Fern] = 12.0;
	arr[Moss] = 8.0;
	arr[Reed] = 16.0;
	arr[Wheat] = 14.0;
	arr[Oat] = 14.0;
	arr[Rice] = 20.0;
	arr[Bush] = 14.0;
	arr[Papyrus] = 15.0;
	arr[PioneerTree] = 12.0;
	arr[DeciduousTree] = 12.0;
	arr[EvergreenTree] = 10.0;
	arr[TropicalTree] = 22.0;
	arr[Cactus] = 25.0;
	arr[Grapevine] = 14.0;
	arr[Lettuce] = 16.0;
	arr[Kale] = 10.0;
	arr[Corn] = 16.0;
	arr[Carrot] = 12.0;
	arr[Beets] = 12.0;
	arr[Potato] = 13.0;
	arr[Onion] = 12.0;
	arr[Garlic] = 10.0;
	arr[Cabbage] = 15.0;
	arr[Broccoli] = 14.0;
	arr[Tomato] = 18.0;
	arr[Cucumber] = 18.0;
	arr[Pepper] = 18.0;
	arr[BlackPepper] = 22.0;
	arr[Cotton] = 18.0;
	arr[Hemp] = 15.0;
	arr[Flax] = 10.0;
	arr[Woad] = 12.0;
	arr[Madder] = 14.0;
	arr[Indigo] = 20.0;
	arr[Lavender] = 16.0;
	arr[Mint] = 14.0;
	arr[Thyme] = 16.0;
	arr[Sage] = 16.0;
	arr[Ginseng] = 12.0;
	arr[Rhubarb] = 12.0;
	arr[Poppy] = 10.0;
	arr[Cocoa] = 22.0;
	arr[Senna] = 15.0;
	arr[Saffron] = 12.0;
	arr[AloeVera] = 20.0;
	arr[Orange] = 20.0;
	arr[Apple] = 12.0;
	arr[Lemon] = 20.0;
	arr[Pear] = 12.0;
	arr[Peach] = 14.0;
	arr[Cherry] = 12.0;
	arr[Apricot] = 14.0;
	arr[Plum] = 14.0;
	arr[Lime] = 22.0;
	arr[Blueberry] = 14.0;
	arr[Strawberry] = 14.0;
	arr[Grape] = 14.0;
	arr[Olive] = 18.0;

	return arr;
}();

inline constexpr LookupTable<Plant, float> TEMP_OPTIMAL_MAX = []
{
	LookupTable<Plant, float> arr{};

	arr[NONE] = 0.0;
	arr[Fern] = 22.0;
	arr[Moss] = 18.0;
	arr[Reed] = 30.0;
	arr[Wheat] = 21.0;
	arr[Oat] = 21.0;
	arr[Rice] = 35.0;
	arr[Bush] = 24.0;
	arr[Papyrus] = 32.0;
	arr[PioneerTree] = 26.0;
	arr[DeciduousTree] = 25.0;
	arr[EvergreenTree] = 22.0;
	arr[TropicalTree] = 32.0;
	arr[Cactus] = 40.0;
	arr[Grapevine] = 26.0;
	arr[Lettuce] = 21.0;
	arr[Kale] = 20.0;
	arr[Corn] = 28.0;
	arr[Carrot] = 25.0;
	arr[Beets] = 25.0;
	arr[Potato] = 27.0;
	arr[Onion] = 25.0;
	arr[Garlic] = 24.0;
	arr[Cabbage] = 28.0;
	arr[Broccoli] = 26.0;
	arr[Tomato] = 30.0;
	arr[Cucumber] = 30.0;
	arr[Pepper] = 28.0;
	arr[BlackPepper] = 32.0;
	arr[Cotton] = 32.0;
	arr[Hemp] = 30.0;
	arr[Flax] = 22.0;
	arr[Woad] = 24.0;
	arr[Madder] = 26.0;
	arr[Indigo] = 32.0;
	arr[Lavender] = 28.0;
	arr[Mint] = 24.0;
	arr[Thyme] = 30.0;
	arr[Sage] = 28.0;
	arr[Ginseng] = 22.0;
	arr[Rhubarb] = 24.0;
	arr[Poppy] = 25.0;
	arr[Cocoa] = 32.0;
	arr[Senna] = 35.0;
	arr[Saffron] = 28.0;
	arr[AloeVera] = 35.0;
	arr[Orange] = 30.0;
	arr[Apple] = 25.0;
	arr[Lemon] = 30.0;
	arr[Pear] = 25.0;
	arr[Peach] = 28.0;
	arr[Cherry] = 25.0;
	arr[Apricot] = 28.0;
	arr[Plum] = 28.0;
	arr[Lime] = 32.0;
	arr[Blueberry] = 24.0;
	arr[Strawberry] = 24.0;
	arr[Grape] = 26.0;
	arr[Olive] = 32.0;

	return arr;
}();

inline constexpr LookupTable<Plant, float> TEMP_GROWTH_MIN = []
{
	LookupTable<Plant, float> arr{};

	arr[NONE] = 0.0;
	arr[Fern] = 5.0;
	arr[Moss] = 0.0;
	arr[Reed] = 10.0;
	arr[Wheat] = 4.0;
	arr[Oat] = 4.0;
	arr[Rice] = 15.0;
	arr[Bush] = 6.0;
	arr[Papyrus] = 20.0;
	arr[PioneerTree] = 5.0;
	arr[DeciduousTree] = 5.0;
	arr[EvergreenTree] = 0.0;
	arr[TropicalTree] = 18.0;
	arr[Cactus] = 20.0;
	arr[Grapevine] = 8.0;
	arr[Lettuce] = 7.0;
	arr[Kale] = 5.0;
	arr[Corn] = 10.0;
	arr[Carrot] = 5.0;
	arr[Beets] = 5.0;
	arr[Potato] = 6.0;
	arr[Onion] = 5.0;
	arr[Garlic] = 4.0;
	arr[Cabbage] = 5.0;
	arr[Broccoli] = 5.0;
	arr[Tomato] = 10.0;
	arr[Cucumber] = 12.0;
	arr[Pepper] = 10.0;
	arr[BlackPepper] = 15.0;
	arr[Cotton] = 10.0;
	arr[Hemp] = 10.0;
	arr[Flax] = 4.0;
	arr[Woad] = 6.0;
	arr[Madder] = 6.0;
	arr[Indigo] = 15.0;
	arr[Lavender] = 6.0;
	arr[Mint] = 5.0;
	arr[Thyme] = 5.0;
	arr[Sage] = 5.0;
	arr[Ginseng] = 6.0;
	arr[Rhubarb] = 6.0;
	arr[Poppy] = 5.0;
	arr[Cocoa] = 18.0;
	arr[Senna] = 5.0;
	arr[Saffron] = 6.0;
	arr[AloeVera] = 18.0;
	arr[Orange] = 15.0;
	arr[Apple] = 5.0;
	arr[Lemon] = 15.0;
	arr[Pear] = 5.0;
	arr[Peach] = 8.0;
	arr[Cherry] = 5.0;
	arr[Apricot] = 8.0;
	arr[Plum] = 8.0;
	arr[Lime] = 18.0;
	arr[Blueberry] = 8.0;
	arr[Strawberry] = 8.0;
	arr[Grape] = 8.0;
	arr[Olive] = 10.0;

	return arr;
}();

inline constexpr LookupTable<Plant, float> TEMP_GROWTH_MAX = []
{
	LookupTable<Plant, float> arr{};

	arr[NONE] = 0.0;
	arr[Fern] = 28.0;
	arr[Moss] = 22.0;
	arr[Reed] = 38.0;
	arr[Wheat] = 38.0;
	arr[Oat] = 38.0;
	arr[Rice] = 40.0;
	arr[Bush] = 35.0;
	arr[Papyrus] = 35.0;
	arr[PioneerTree] = 40.0;
	arr[DeciduousTree] = 40.0;
	arr[EvergreenTree] = 38.0;
	arr[TropicalTree] = 45.0;
	arr[Cactus] = 55.0;
	arr[Grapevine] = 35.0;
	arr[Lettuce] = 24.0;
	arr[Kale] = 28.0;
	arr[Corn] = 40.0;
	arr[Carrot] = 30.0;
	arr[Beets] = 30.0;
	arr[Potato] = 32.0;
	arr[Onion] = 30.0;
	arr[Garlic] = 28.0;
	arr[Cabbage] = 40.0;
	arr[Broccoli] = 35.0;
	arr[Tomato] = 35.0;
	arr[Cucumber] = 38.0;
	arr[Pepper] = 35.0;
	arr[BlackPepper] = 40.0;
	arr[Cotton] = 35.0;
	arr[Hemp] = 35.0;
	arr[Flax] = 35.0;
	arr[Woad] = 35.0;
	arr[Madder] = 38.0;
	arr[Indigo] = 40.0;
	arr[Lavender] = 35.0;
	arr[Mint] = 28.0;
	arr[Thyme] = 38.0;
	arr[Sage] = 35.0;
	arr[Ginseng] = 28.0;
	arr[Rhubarb] = 30.0;
	arr[Poppy] = 30.0;
	arr[Cocoa] = 45.0;
	arr[Senna] = 40.0;
	arr[Saffron] = 35.0;
	arr[AloeVera] = 50.0;
	arr[Orange] = 40.0;
	arr[Apple] = 40.0;
	arr[Lemon] = 40.0;
	arr[Pear] = 40.0;
	arr[Peach] = 38.0;
	arr[Cherry] = 40.0;
	arr[Apricot] = 38.0;
	arr[Plum] = 38.0;
	arr[Lime] = 45.0;
	arr[Blueberry] = 28.0;
	arr[Strawberry] = 28.0;
	arr[Grape] = 35.0;
	arr[Olive] = 42.0;

	return arr;
}();


inline constexpr LookupTable<Plant, int> HARVEST_AMT = []
{
	LookupTable<Plant, int> arr{};

	arr[NONE] = 0;

	arr[Fern] = 1;
	arr[Moss] = 1;

	arr[Reed] = 4;
	arr[Papyrus] = 6;

	arr[Wheat] = 28;
	arr[Oat] = 26;
	arr[Rice] = 24;
	arr[Corn] = 2;

	arr[Bush] = 8;

	arr[PioneerTree] = 20;
	arr[DeciduousTree] = 25;
	arr[EvergreenTree] = 18;
	arr[TropicalTree] = 22;

	arr[Cactus] = 6;

	arr[Grapevine] = 20;

	arr[Lettuce] = 2;
	arr[Kale] = 2;
	arr[Cabbage] = 1;
	arr[Broccoli] = 1;

	arr[Carrot] = 1;
	arr[Beets] = 1;

	arr[Potato] = 1;

	arr[Onion] = 1;
	arr[Garlic] = 1;

	arr[Tomato] = 12;
	arr[Cucumber] = 10;
	arr[Pepper] = 8;
	arr[BlackPepper] = 200;

	arr[Cotton] = 4;
	arr[Hemp] = 6;
	arr[Flax] = 8;

	arr[Woad] = 10;
	arr[Madder] = 10;
	arr[Indigo] = 10;

	arr[Lavender] = 20;
	arr[Mint] = 30;
	arr[Thyme] = 25;
	arr[Sage] = 22;

	arr[Ginseng] = 1;
	arr[Rhubarb] = 3;

	arr[Poppy] = 150;

	arr[Cocoa] = 50;
	arr[Senna] = 20;
	arr[Saffron] = 1;
	arr[AloeVera] = 15;

	arr[Orange] = 80;
	arr[Apple] = 120;
	arr[Lemon] = 70;
	arr[Pear] = 110;
	arr[Peach] = 90;
	arr[Cherry] = 100;
	arr[Apricot] = 85;
	arr[Plum] = 95;
	arr[Lime] = 75;

	arr[Blueberry] = 60;
	arr[Strawberry] = 30;
	arr[Grape] = 40;

	arr[Olive] = 60;

	return arr;
}();

inline constexpr LookupTable<Plant, bool> PERFECT_SUNLIGHT = []
{
	LookupTable<Plant, bool> lt{};

	lt[NONE] = false;

	lt[Fern] = true;
	lt[Moss] = false;

	lt[Reed] = true;
	lt[Papyrus] = true;

	lt[Wheat] = true;
	lt[Oat] = true;
	lt[Rice] = true;
	lt[Corn] = true;

	lt[Bush] = true;

	lt[PioneerTree] = true;
	lt[DeciduousTree] = true;
	lt[EvergreenTree] = true;
	lt[TropicalTree] = true;

	lt[Cactus] = true;

	lt[Grapevine] = true;

	lt[Lettuce] = true;
	lt[Kale] = true;
	lt[Cabbage] = true;
	lt[Broccoli] = true;

	lt[Carrot] = true;
	lt[Beets] = true;
	lt[Potato] = true;

	lt[Onion] = true;
	lt[Garlic] = true;

	lt[Tomato] = true;
	lt[Cucumber] = true;
	lt[Pepper] = true;
	lt[BlackPepper] = true;

	lt[Cotton] = true;
	lt[Hemp] = true;
	lt[Flax] = true;

	lt[Woad] = true;
	lt[Madder] = true;
	lt[Indigo] = true;

	lt[Lavender] = true;
	lt[Mint] = true;
	lt[Thyme] = true;
	lt[Sage] = true;

	lt[Ginseng] = true;
	lt[Rhubarb] = true;

	lt[Poppy] = true;
	lt[Cocoa] = true;
	lt[Senna] = true;
	lt[Saffron] = true;
	lt[AloeVera] = true;

	lt[Orange] = true;
	lt[Apple] = true;
	lt[Lemon] = true;
	lt[Pear] = true;
	lt[Peach] = true;
	lt[Cherry] = true;
	lt[Apricot] = true;
	lt[Plum] = true;
	lt[Lime] = true;

	lt[Blueberry] = true;
	lt[Strawberry] = true;
	lt[Grape] = true;

	lt[Olive] = true;

	return lt;
}();

inline constexpr LookupTable<Plant, bool> REQUIRES_SCYTHE = []
{
	LookupTable<Plant, bool> arr{};

	arr[NONE] = false;

	arr[Fern] = false;
	arr[Moss] = false;

	arr[Reed] = true;
	arr[Papyrus] = true;

	arr[Wheat] = true;
	arr[Oat] = true;
	arr[Rice] = true;
	arr[Corn] = true;

	arr[Bush] = false;

	arr[PioneerTree] = false;
	arr[DeciduousTree] = false;
	arr[EvergreenTree] = false;
	arr[TropicalTree] = false;

	arr[Cactus] = false;

	arr[Grapevine] = true;

	arr[Lettuce] = false;
	arr[Kale] = false;
	arr[Cabbage] = true;
	arr[Broccoli] = true;

	arr[Carrot] = false;
	arr[Beets] = false;
	arr[Potato] = false;

	arr[Onion] = false;
	arr[Garlic] = false;

	arr[Tomato] = false;
	arr[Cucumber] = false;
	arr[Pepper] = true;
	arr[BlackPepper] = true;

	arr[Cotton] = true;
	arr[Hemp] = true;
	arr[Flax] = true;

	arr[Woad] = true;
	arr[Madder] = true;
	arr[Indigo] = true;

	arr[Lavender] = true;
	arr[Mint] = false;
	arr[Thyme] = false;
	arr[Sage] = false;

	arr[Ginseng] = false;
	arr[Rhubarb] = false;

	arr[Poppy] = true;
	arr[Cocoa] = true;
	arr[Senna] = true;
	arr[Saffron] = true;
	arr[AloeVera] = false;

	arr[Orange] = false;
	arr[Apple] = false;
	arr[Lemon] = false;
	arr[Pear] = false;
	arr[Peach] = false;
	arr[Cherry] = false;
	arr[Apricot] = false;
	arr[Plum] = false;
	arr[Lime] = false;

	arr[Blueberry] = false;
	arr[Strawberry] = false;
	arr[Grape] = true;

	arr[Olive] = false;

	return arr;
}();

inline constexpr LookupTable<Plant, Time> GERMINATION_PERIOD = []
{
	LookupTable<Plant, Time> lt{};
	using enum Plant;

	lt[NONE] = 0;

	lt[Fern] = 0.02 * YEAR_LENGTH;
	lt[Moss] = 0.01 * YEAR_LENGTH;

	lt[Reed] = 0.02 * YEAR_LENGTH;
	lt[Papyrus] = 0.03 * YEAR_LENGTH;

	lt[Wheat] = 0.03 * YEAR_LENGTH;
	lt[Oat] = 0.03 * YEAR_LENGTH;
	lt[Rice] = 0.03 * YEAR_LENGTH;
	lt[Corn] = 0.04 * YEAR_LENGTH;

	lt[Bush] = 0.04 * YEAR_LENGTH;

	lt[PioneerTree] = 0.08 * YEAR_LENGTH;
	lt[DeciduousTree] = 0.10 * YEAR_LENGTH;
	lt[EvergreenTree] = 0.12 * YEAR_LENGTH;
	lt[TropicalTree] = 0.10 * YEAR_LENGTH;

	lt[Cactus] = 0.05 * YEAR_LENGTH;

	lt[Grapevine] = 0.04 * YEAR_LENGTH;

	lt[Lettuce] = 0.02 * YEAR_LENGTH;
	lt[Kale] = 0.03 * YEAR_LENGTH;
	lt[Cabbage] = 0.03 * YEAR_LENGTH;
	lt[Broccoli] = 0.03 * YEAR_LENGTH;

	lt[Carrot] = 0.03 * YEAR_LENGTH;
	lt[Beets] = 0.03 * YEAR_LENGTH;

	lt[Potato] = 0.05 * YEAR_LENGTH;

	lt[Onion] = 0.04 * YEAR_LENGTH;
	lt[Garlic] = 0.05 * YEAR_LENGTH;

	lt[Tomato] = 0.02 * YEAR_LENGTH;
	lt[Cucumber] = 0.03 * YEAR_LENGTH;
	lt[Pepper] = 0.03 * YEAR_LENGTH;
	lt[BlackPepper] = 0.06 * YEAR_LENGTH;

	lt[Cotton] = 0.05 * YEAR_LENGTH;
	lt[Hemp] = 0.04 * YEAR_LENGTH;
	lt[Flax] = 0.03 * YEAR_LENGTH;

	lt[Woad] = 0.03 * YEAR_LENGTH;
	lt[Madder] = 0.04 * YEAR_LENGTH;
	lt[Indigo] = 0.05 * YEAR_LENGTH;

	lt[Lavender] = 0.02 * YEAR_LENGTH;
	lt[Mint] = 0.02 * YEAR_LENGTH;
	lt[Thyme] = 0.02 * YEAR_LENGTH;
	lt[Sage] = 0.03 * YEAR_LENGTH;

	lt[Ginseng] = 0.06 * YEAR_LENGTH;
	lt[Rhubarb] = 0.04 * YEAR_LENGTH;

	lt[Poppy] = 0.02 * YEAR_LENGTH;
	lt[Cocoa] = 0.08 * YEAR_LENGTH;
	lt[Senna] = 0.05 * YEAR_LENGTH;
	lt[Saffron] = 0.06 * YEAR_LENGTH;
	lt[AloeVera] = 0.04 * YEAR_LENGTH;

	lt[Orange] = 0.08 * YEAR_LENGTH;
	lt[Apple] = 0.10 * YEAR_LENGTH;
	lt[Lemon] = 0.08 * YEAR_LENGTH;
	lt[Pear] = 0.10 * YEAR_LENGTH;
	lt[Peach] = 0.08 * YEAR_LENGTH;
	lt[Cherry] = 0.08 * YEAR_LENGTH;
	lt[Apricot] = 0.08 * YEAR_LENGTH;
	lt[Plum] = 0.08 * YEAR_LENGTH;
	lt[Lime] = 0.08 * YEAR_LENGTH;

	lt[Blueberry] = 0.04 * YEAR_LENGTH;
	lt[Strawberry] = 0.02 * YEAR_LENGTH;
	lt[Grape] = 0.04 * YEAR_LENGTH;

	lt[Olive] = 0.10 * YEAR_LENGTH;

	return lt;
}();


inline constexpr LookupTable<Plant, Time> MAX_AGES = []
{
	LookupTable<Plant, Time> lt{};
	using enum Plant;

	lt[NONE] = 0;

	lt[Fern] = 10 * YEAR_LENGTH;
	lt[Moss] = 5 * YEAR_LENGTH;

	lt[Reed] = 3 * YEAR_LENGTH;
	lt[Papyrus] = 4 * YEAR_LENGTH;

	lt[Wheat] = 1 * YEAR_LENGTH;
	lt[Oat] = 1 * YEAR_LENGTH;
	lt[Rice] = 1 * YEAR_LENGTH;
	lt[Corn] = 1 * YEAR_LENGTH;

	lt[Bush] = 8 * YEAR_LENGTH;

	lt[PioneerTree] = 60 * YEAR_LENGTH;
	lt[DeciduousTree] = 120 * YEAR_LENGTH;
	lt[EvergreenTree] = 200 * YEAR_LENGTH;
	lt[TropicalTree] = 80 * YEAR_LENGTH;

	lt[Cactus] = 100 * YEAR_LENGTH;

	lt[Grapevine] = 40 * YEAR_LENGTH;

	lt[Lettuce] = 1 * YEAR_LENGTH;
	lt[Kale] = 2 * YEAR_LENGTH;
	lt[Cabbage] = 1 * YEAR_LENGTH;
	lt[Broccoli] = 1 * YEAR_LENGTH;

	lt[Carrot] = 1 * YEAR_LENGTH;
	lt[Beets] = 1 * YEAR_LENGTH;

	lt[Potato] = 1 * YEAR_LENGTH;

	lt[Onion] = 1 * YEAR_LENGTH;
	lt[Garlic] = 2 * YEAR_LENGTH;

	lt[Tomato] = 1 * YEAR_LENGTH;
	lt[Cucumber] = 1 * YEAR_LENGTH;
	lt[Pepper] = 2 * YEAR_LENGTH;
	lt[BlackPepper] = 15 * YEAR_LENGTH;

	lt[Cotton] = 3 * YEAR_LENGTH;
	lt[Hemp] = 5 * YEAR_LENGTH;
	lt[Flax] = 2 * YEAR_LENGTH;

	lt[Woad] = 2 * YEAR_LENGTH;
	lt[Madder] = 3 * YEAR_LENGTH;
	lt[Indigo] = 4 * YEAR_LENGTH;

	lt[Lavender] = 6 * YEAR_LENGTH;
	lt[Mint] = 3 * YEAR_LENGTH;
	lt[Thyme] = 8 * YEAR_LENGTH;
	lt[Sage] = 10 * YEAR_LENGTH;

	lt[Ginseng] = 20 * YEAR_LENGTH;
	lt[Rhubarb] = 8 * YEAR_LENGTH;

	lt[Poppy] = 1 * YEAR_LENGTH;
	lt[Cocoa] = 30 * YEAR_LENGTH;
	lt[Senna] = 4 * YEAR_LENGTH;
	lt[Saffron] = 3 * YEAR_LENGTH;
	lt[AloeVera] = 15 * YEAR_LENGTH;

	lt[Orange] = 50 * YEAR_LENGTH;
	lt[Apple] = 80 * YEAR_LENGTH;
	lt[Lemon] = 60 * YEAR_LENGTH;
	lt[Pear] = 80 * YEAR_LENGTH;
	lt[Peach] = 40 * YEAR_LENGTH;
	lt[Cherry] = 60 * YEAR_LENGTH;
	lt[Apricot] = 40 * YEAR_LENGTH;
	lt[Plum] = 50 * YEAR_LENGTH;
	lt[Lime] = 60 * YEAR_LENGTH;

	lt[Blueberry] = 20 * YEAR_LENGTH;
	lt[Strawberry] = 5 * YEAR_LENGTH;
	lt[Grape] = 40 * YEAR_LENGTH;

	lt[Olive] = 100 * YEAR_LENGTH;

	return lt;
}();

inline constexpr LookupTable<Plant, float> FULL_MATURITY_AGES = []
{
	LookupTable<Plant, float> lt{};
	using enum Plant;

	lt[Bush] = 0.35f;

	lt[PioneerTree] = 0.5f;
	lt[DeciduousTree] = 0.45f;
	lt[EvergreenTree] = 0.5f;
	lt[TropicalTree] = 0.45f;

	lt[Cactus] = 0.35f;

	lt[Grapevine] = 0.4f;

	lt[Lavender] = 0.3f;
	lt[Mint] = 0.25f;
	lt[Thyme] = 0.3f;
	lt[Sage] = 0.35f;

	lt[Ginseng] = 0.6f;
	lt[Rhubarb] = 0.4f;

	lt[Cocoa] = 0.6f;
	lt[AloeVera] = 0.5f;

	lt[Orange] = 0.5f;
	lt[Apple] = 0.45f;
	lt[Lemon] = 0.5f;
	lt[Pear] = 0.45f;
	lt[Peach] = 0.4f;
	lt[Cherry] = 0.45f;
	lt[Apricot] = 0.4f;
	lt[Plum] = 0.45f;
	lt[Lime] = 0.5f;

	lt[Blueberry] = 0.3f;
	lt[Strawberry] = 0.25f;
	lt[Grape] = 0.35f;

	lt[Olive] = 0.6f;

	return lt;
}();



inline constexpr BitsetTable<Plant> IS_REGROWTH = []
{
	BitsetTable<Plant> t{};

	t.set(Plant::Bush);

	t.set(Plant::PioneerTree);
	t.set(Plant::DeciduousTree);
	t.set(Plant::EvergreenTree);
	t.set(Plant::TropicalTree);

	t.set(Plant::Cactus);

	t.set(Plant::Grapevine);

	t.set(Plant::Lavender);
	t.set(Plant::Mint);
	t.set(Plant::Thyme);
	t.set(Plant::Sage);

	t.set(Plant::Ginseng);
	t.set(Plant::Rhubarb);

	t.set(Plant::Cocoa);
	t.set(Plant::AloeVera);

	t.set(Plant::Orange);
	t.set(Plant::Apple);
	t.set(Plant::Lemon);
	t.set(Plant::Pear);
	t.set(Plant::Peach);
	t.set(Plant::Cherry);
	t.set(Plant::Apricot);
	t.set(Plant::Plum);
	t.set(Plant::Lime);

	t.set(Plant::Blueberry);
	t.set(Plant::Strawberry);
	t.set(Plant::Grape);

	t.set(Plant::Olive);

	return t;
}();

//relative to max_age
inline constexpr LookupTable<Plant, float> REGROWTH_START_AGE = []
{
	LookupTable<Plant, float> lt{};
	using enum Plant;

	lt[NONE] = 0.0f;

	lt[Fern] = 0.0f;
	lt[Moss] = 0.0f;

	lt[Reed] = 0.15f;
	lt[Papyrus] = 0.15f;

	lt[Bush] = 0.25f;

	lt[PioneerTree] = 0.25f;
	lt[DeciduousTree] = 0.2f;
	lt[EvergreenTree] = 0.25f;
	lt[TropicalTree] = 0.2f;

	lt[Cactus] = 0.25f;

	lt[Grapevine] = 0.2f;

	lt[Lavender] = 0.2f;
	lt[Mint] = 0.15f;
	lt[Thyme] = 0.2f;
	lt[Sage] = 0.25f;

	lt[Ginseng] = 0.6f;
	lt[Rhubarb] = 0.3f;

	lt[Cocoa] = 0.35f;
	lt[AloeVera] = 0.3f;

	lt[Orange] = 0.2f;
	lt[Apple] = 0.15f;
	lt[Lemon] = 0.2f;
	lt[Pear] = 0.15f;
	lt[Peach] = 0.15f;
	lt[Cherry] = 0.2f;
	lt[Apricot] = 0.15f;
	lt[Plum] = 0.2f;
	lt[Lime] = 0.2f;

	lt[Blueberry] = 0.2f;
	lt[Strawberry] = 0.1f;
	lt[Grape] = 0.2f;

	lt[Olive] = 0.25f;

	return lt;
}();

inline constexpr LookupTable<Plant, Time> REGROWTH_MAX = []
{
	LookupTable<Plant, Time> lt{};
	using enum Plant;

	// Wild / generic
	lt[Bush] = 0.18f * YEAR_LENGTH;

	// Trees
	lt[PioneerTree]   = 0.85f * YEAR_LENGTH;
	lt[DeciduousTree] = 0.95f * YEAR_LENGTH;
	lt[EvergreenTree] = 1.2f  * YEAR_LENGTH;
	lt[TropicalTree]  = 0.65f * YEAR_LENGTH;

	// Arid
	lt[Cactus] = 1.3f * YEAR_LENGTH;

	// Vines
	lt[Grapevine] = 0.9f * YEAR_LENGTH;

	// Herbs
	lt[Lavender] = 0.2f * YEAR_LENGTH; 
	lt[Mint]     = 0.15f * YEAR_LENGTH; 
	lt[Thyme]    = 0.22f * YEAR_LENGTH;
	lt[Sage]     = 0.22f * YEAR_LENGTH;

	// Perennials
	lt[Ginseng] = 0.9f  * YEAR_LENGTH; // gameplay-friendly vs real multi-year root harvest
	lt[Rhubarb] = 0.2f  * YEAR_LENGTH;

	// Tropical crops
	lt[Cocoa]    = 0.45f * YEAR_LENGTH;
	lt[AloeVera] = 0.4f  * YEAR_LENGTH;

	// Fruit trees 
	lt[Orange]  = 0.6f  * YEAR_LENGTH;
	lt[Apple]   = 0.55f * YEAR_LENGTH;
	lt[Lemon]   = 0.45f * YEAR_LENGTH;
	lt[Pear]    = 0.65f * YEAR_LENGTH;
	lt[Peach]   = 0.6f  * YEAR_LENGTH;
	lt[Cherry]  = 0.7f  * YEAR_LENGTH;
	lt[Apricot] = 0.64f * YEAR_LENGTH;
	lt[Plum]    = 0.66f * YEAR_LENGTH;
	lt[Lime]    = 0.55f * YEAR_LENGTH;

	// Berries 
	lt[Blueberry]  = 0.42f * YEAR_LENGTH;
	lt[Strawberry] = 0.12f * YEAR_LENGTH;
	lt[Grape]      = 0.8f  * YEAR_LENGTH;

	// Slow 
	lt[Olive] = 1.1f * YEAR_LENGTH;

	return lt;
}();

float fruits_fall_chance_per_tick = 0.058;

inline constexpr LookupTable<Plant, bool> FRUITS_FALL = []
{
	LookupTable<Plant, bool> lt{};
	using enum Plant;

	lt[Orange] = true;
	lt[Apple] = true;
	lt[Lemon] = true;
	lt[Pear] = true;
	lt[Peach] = true;
	lt[Cherry] = true;
	lt[Apricot] = true;
	lt[Plum] = true;
	lt[Lime] = true;

	return lt;
}();


inline constexpr BitsetTable<Plant> PLANT_PRODUCES = []
	{
		BitsetTable<Plant> t{};
		using enum Plant;
	t.set(Wheat);
	t.set(Oat);
	t.set(Rice);
	t.set(Papyrus);
	t.set(Cactus);
	t.set(Grapevine);
	t.set(Lettuce);
	t.set(Kale);
	t.set(Corn);
	t.set(Carrot);
	t.set(Beets);
	t.set(Potato);
	t.set(Onion);
	t.set(Garlic);
	t.set(Cabbage);
	t.set(Broccoli);
	t.set(Tomato);
	t.set(Cucumber);
	t.set(Pepper);
	t.set(BlackPepper);
	t.set(Cotton);
	t.set(Hemp);
	t.set(Flax);
	t.set(Woad);
	t.set(Madder);
	t.set(Indigo);
	t.set(Lavender);
	t.set(Mint);
	t.set(Thyme);
	t.set(Sage);
	t.set(Ginseng);
	t.set(Rhubarb);
	t.set(Cocoa);
	t.set(Senna);
	t.set(Saffron);
	t.set(AloeVera);
	t.set(Orange);
	t.set(Apple);
	t.set(Lemon);
	t.set(Pear);
	t.set(Peach);
	t.set(Cherry);
	t.set(Apricot);
	t.set(Plum);
	t.set(Lime);
	t.set(Blueberry);
	t.set(Strawberry);
	t.set(Olive);
		return t;
	}();

inline constexpr LookupTable<Plant, int> PRODUCE_MAX_YIELD = []
{
	LookupTable<Plant, int> lt{};
	using enum Plant;


	lt[Cactus] = 30;

	lt[Grapevine] = 150;

	lt[Lavender] = 40;
	lt[Mint] = 35;
	lt[Thyme] = 45;
	lt[Sage] = 50;

	lt[Ginseng] = 10;
	lt[Rhubarb] = 25;

	lt[Cocoa] = 120;
	lt[AloeVera] = 60;

	lt[Orange] = 250;
	lt[Apple] = 300;
	lt[Lemon] = 220;
	lt[Pear] = 280;
	lt[Peach] = 200;
	lt[Cherry] = 320;
	lt[Apricot] = 210;
	lt[Plum] = 260;
	lt[Lime] = 200;

	lt[Blueberry] = 80;
	lt[Strawberry] = 120;
	lt[Grape] = 180;

	lt[Olive] = 240;

	return lt;
}();

inline constexpr LookupTable<Plant, int> MAX_PRODUCE = []
{
	LookupTable<Plant, int> lt{};
	using enum Plant;


	lt[Cactus] = 30;

	lt[Grapevine] = 150;

	lt[Lavender] = 40;
	lt[Mint] = 35;
	lt[Thyme] = 45;
	lt[Sage] = 50;

	lt[Ginseng] = 10;
	lt[Rhubarb] = 25;

	lt[Cocoa] = 120;
	lt[AloeVera] = 60;

	lt[Orange] = 250;
	lt[Apple] = 300;
	lt[Lemon] = 220;
	lt[Pear] = 280;
	lt[Peach] = 200;
	lt[Cherry] = 320;
	lt[Apricot] = 210;
	lt[Plum] = 260;
	lt[Lime] = 200;

	lt[Blueberry] = 80;
	lt[Strawberry] = 120;
	lt[Grape] = 180;

	lt[Olive] = 240;

	return lt;
}();

inline uint16_t get_produce_current_target(Plant plant, const Time current_regrowth, const Time current_age)
{
	Time fma = FULL_MATURITY_AGES[plant] * MAX_AGES[plant];
	float maturity = std::min(current_age, fma)  / fma;
	float produce_portion = std::min(current_regrowth, REGROWTH_MAX[plant]) / REGROWTH_MAX[plant];
	return MAX_PRODUCE[plant] * maturity * produce_portion;	
}
	
