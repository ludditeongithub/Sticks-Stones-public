#pragma once
#include <cstdint>
#include <vector>
#include <core/tables.hpp>
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
enum class PlantCategory : size_t
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

namespace plant
{
inline constexpr LookupTable<PlantCategory, float> test = []
{
	LookupTable<PlantCategory, float> lt{};
	using enum PlantCategory;
	lt[PlantCategory::NONE] = 0.4;
	return lt;
}();
  
  inline const RaggedLookupTable<PlantCategory, Plant> 56>
  categories = []
  {
    using enum Plant;

    RaggedLookupTable<PlantCategory, Plant, 56> lt{};
  lt.set(PlantCategory::Tree,
       {PioneerTree,
        DeciduousTree,
        EvergreenTree,
        TropicalTree,
        Cocoa});

lt.set(PlantCategory::Citrus,
       {Orange,
        Lemon,
        Lime});

lt.set(PlantCategory::Stone,
       {Peach,
        Cherry,
        Apricot,
        Plum});

lt.set(PlantCategory::Pome,
       {Apple,
        Pear});

lt.set(PlantCategory::Olive,
       {Olive});

lt.set(PlantCategory::Succulent,
       {Cactus,
        AloeVera});

lt.set(PlantCategory::BerryShrub,
       {Blueberry,
        Strawberry});

lt.set(PlantCategory::Flowering,
       {Broccoli,
        Poppy,
        Saffron});

lt.set(PlantCategory::FruitVeggie,
       {Tomato,
        Cucumber,
        Pepper});

lt.set(PlantCategory::Leafy,
       {Lettuce,
        Kale,
        Cabbage});

lt.set(PlantCategory::Root,
       {Carrot,
        Beets,
        Potato,
        Ginseng,
        Rhubarb});

lt.set(PlantCategory::Bulb,
       {Onion,
        Garlic});

lt.set(PlantCategory::Reed,
       {Reed,
        Papyrus});

lt.set(PlantCategory::Grain,
       {Wheat,
        Oat,
        Rice,
        Corn});

lt.set(PlantCategory::Grapevine,
       {Grapevine});

lt.set(PlantCategory::Herb,
       {BlackPepper,
        Woad,
        Madder,
        Indigo,
        Lavender,
        Mint,
        Thyme,
        Sage,
        Senna});

lt.set(PlantCategory::Textile,
       {Cotton,
        Hemp,
        Flax});

lt.set(PlantCategory::Moss,
       {Moss});

lt.set(PlantCategory::Fern,
       {Fern});

lt.set(PlantCategory::Bush,
       {Bush});
    return lt;
  };
}
