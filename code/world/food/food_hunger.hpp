#ifndef FOODHUNGER_HPP
#define FOODHUNGER_HPP

#include <array>
#include <core/data.hpp>
#include <core/tables.hpp>
#include <cstdint>
#include <cstdlib>
#include <world/plant/enum.hpp>

inline constexpr LookupTable<Plant, Hunger> fruitHunger = []
{
	LookupTable<Plant, Hunger> arr{};
	using enum Plant;
	arr[Apple] = 95;
	arr[Orange] = 62;
	arr[Pear] = 100;
	arr[Peach] = 65;
	arr[Plum] = 58;
	arr[Apricot] = 75;
	arr[Cherry] = 14;
	arr[Blueberry] = 4;
	arr[Strawberry] = 15;
	arr[Grape] = 6;
	arr[Lemon] = 20;
	arr[Lime] = 20;
	return arr;
}();

inline constexpr LookupTable<Plant, Hunger> plantHunger = []
{
	LookupTable<Plant, Hunger> arr{};
	using enum Plant;
	arr[Fern] = 20;
	arr[Reed] = 40;
	arr[Oat] = 45;
	arr[Bush] = 30;
	arr[PioneerTree] = 20;
	arr[EvergreenTree] = 25;
	arr[OrangeTree] = 60;
	arr[LimeTree] = 20;
	arr[PlumTree] = 40;
	arr[ApricotTree] = 45;
	arr[AppleTree] = 95;
	arr[OliveTree] = 25;
	arr[StrawberryShrub] = 10;
	arr[Lettuce] = 15;
	arr[Corn] = 80;
	arr[Beets] = 40;
	arr[Onion] = 20;
	arr[Cabbage] = 25;
	arr[Tomato] = 20;
	arr[Pepper] = 15;
	arr[Beans] = 40;
	arr[Hemp] = 20;
	arr[Woad] = 5;
	arr[Indigo] = 5;
	arr[Mint] = 20;
	arr[Sage] = 15;
	arr[Poppy] = 10;
	arr[Senna] = 10;
	arr[Saffron] = 5;
	return arr;
}();

/*
// -------------------- NOTES --------------------

// 1. Plant resilience
// Consider adding a "resilience class" for each plant:
// - Resilient: can regrow leaves, minimal permanent loss
// - Moderate: partial loss reduces health; repeated grazing can kill
// - Fragile: significant leaf removal can kill immediately
//
// 2. Hunger scaling
// The hunger values above are for fully edible portions.
// For plants, you could scale hunger by the "health" or "regrowth factor" of the plant.
// Example:
//    actualHunger = plantHunger * (currentHealth / maxHealth)
// This allows animals to eat partially regrown leaves realistically.
//
// 3. Meat and corpse chunks
// The `meatAmount` array defines how many "game pieces" the corpse can be divided into.
// Each piece satisfies a fraction of the total `corpseHunger`.
*/

#endif
