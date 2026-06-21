#pragma once
#include <cstdint>
// enum class Type {
// NONE, EDIBLE, WOOD, Fern, Moss, Reed, Wheat, Oat, Rice, Bush, Papyrus,
// PioneerTree, DeciduousTree, EvergreenTree, TropicalTree, OrangeTree,
// LemonTree, LimeTree, PeachTree, PlumTree, CherryTree, ApricotTree, MangoTree,
// Cactus, AppleTree, PearTree, OliveTree, BlueberryShrub, StrawberryShrub,
// Grapevine, Lettuce, Kale, Corn, Carrot, Beets, Potato, Onion, Garlic,
// Cabbage, Broccoli, Tomato, Cucumber, Pepper, BlackPepper, Cotton, Hemp, Flax,
// Woad, Madder, Indigo, Lavender, Mint, Thyme, Sage, Ginseng, Rhubarb, Poppy,
// Cocoa, Senna, Saffron, AloeVera, MAX,
// };

enum class Plant : uint16_t {
	NONE,
	Fern,
	Moss,
	Reed,
	Wheat,
	Oat,
	Rice,
	Bush,
	Papyrus,
	PioneerTree,
	DeciduousTree,
	EvergreenTree,
	TropicalTree,
	Cactus,
	Grapevine,
	Lettuce,
	Kale,
	Corn,
	Carrot,
	Beets,
	Potato,
	Onion,
	Garlic,
	Cabbage,
	Broccoli,
	Tomato,
	Cucumber,
	Pepper,
	BlackPepper,
	Cotton,
	Hemp,
	Flax,
	Woad,
	Madder,
	Indigo,
	Lavender,
	Mint,
	Thyme,
	Sage,
	Ginseng,
	Rhubarb,
	Poppy,
	Cocoa,
	Senna,
	Saffron,
	AloeVera,

	Orange,
	Apple,
	Lemon,
	Pear,
	Peach,
	Cherry,
	Apricot,
	Plum,
	Lime,
	// Non-fall fruits
	Blueberry,
	Strawberry,	

	// TODO: add data for olive!
	Olive,
	MAX
};
// TODO: let leaf types have heights-- tall animals, animals that climb can eat trees
enum class PlantCategory
{
	NONE,
	Tree,
	Citrus,
	Stone,
	Pome,
	Olive,
	Succulent,
	BerryShrub,
	Flowering,
	FruitVeggie,
	Leafy,
	Root,
	Reed,
	Bulb,
	Grain,
	Grapevine,
	Herb,
	Textile,
	Moss,
	Fern,
	Bush,
	MAX
};



enum class Fruit
{
	NONE,
	// also doubles for juice
	Orange,
	Apple,
	Lemon,
	Pear,
	Peach,
	Cherry,
	Apricot,
	Plum,
	Lime,
	// Non-fall fruits
	Blueberry,
	Strawberry,
	Grape,
	// FRUIT VEGGIES
	Cucumber,
	Pepper,
	Tomato,
	MAX

};
