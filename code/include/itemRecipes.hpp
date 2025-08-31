#ifndef ITEMRECIPES_H_
#define ITEMRECIPES_H_
#include "basic.hpp"
#include "categories.hpp"

std::stack<uint16_t> nextItemIndex;

using SourceVariant = std::variant<Tile, Plant, Animal, Scavengeable>;

//TODO:: sieve, which can separte sand and clay in, liquids and soil, etc
enum class itemTags {
    NONE = 0,
    Alternate = 1 << 1,
    Liquid = 1 << 2,
    VariableAmountProduced = 1 << 3,
    VariableAmountsRequired = 1 << 4,
    FromCorpse = 1 << 5,
    RequiresUniqueVariant = 1 << 6,
    OptionalIngredient = 1 << 7,
    Mould = 1 << 8,
    Container = 1 << 9,
    //TODO: add flammable tags
    Flammable = 1 << 10,
};

// how resource is gotten
struct Resource {
  Actions actions[12];
  uint16_t time;
  SourceVariant sources[12];
  uint16_t amounts[12]; //maximum amountcollected from the source - 0 means infinite
};

Resource resources[static_cast<int>(Item::BOTHMAX)];

inline itemTags operator|(itemTags a, itemTags b) {
    return static_cast<itemTags>(
        static_cast<std::underlying_type_t<itemTags>>(a) |
        static_cast<std::underlying_type_t<itemTags>>(b)
    );
}

inline itemTags& operator|=(itemTags& a, itemTags b) {
    a = a | b;
    return a;
}

inline itemTags operator&(itemTags a, itemTags b) {
    return static_cast<itemTags>(
        static_cast<std::underlying_type_t<itemTags>>(a) &
        static_cast<std::underlying_type_t<itemTags>>(b)
    );
}

inline bool hasTag(itemTags value, itemTags tag) {
    return static_cast<std::underlying_type_t<itemTags>>(value & tag) != 0;
}

// RESOURCE GUIDELINES
// 1L = 100 units of water/sand/dirt/clay
// 30L - max capacity of tile
// Water - unlimited
// Sand - unlimitled
// ClaySoil -
// Dirt Tile -
// 1 Rock Salt averages 100 units of salt
//
// TODO: minimize the fruit one
void intializeResources() {
    resources[static_cast<int>(Item::SaltWater)] = {{Actions::Collect, Actions::Collect}, 10, {Tile::ShallowSaltWater, Tile::DeepWater}, {0, 0}};
    resources[static_cast<int>(Item::Water)] = {{Actions::Collect, Actions::Collect, Actions::Collect}, 10, {Tile::FlowingWater, Tile::ShallowWater, Tile::RiverSource}, {0, 0, 0}};
    resources[static_cast<int>(Item::Log)] = {{Actions::Lift, Actions::Chop, Actions::Chop, Actions::Chop, Actions::Chop}, 720,  {Scavengeable::Log, Plant::PioneerTree, Plant::DeciduousTree, Plant::EvergreenTree, Plant::TropicalTree}, {1,1,2,2,3}};
    //TODO: fix how lift and chop should take different times
    resources[static_cast<int>(Item::Pebble)] = {{Actions::Collect}, 10, {Scavengeable::Pebble}, {1}};
    resources[static_cast<int>(Item::Rock)] = {{Actions::Collect}, 10, {Scavengeable::Rock}, {1}};
    resources[static_cast<int>(Item::LargeRock)] = {{Actions::Lift}, 20, {Scavengeable::LargeRock}, {1}};
    resources[static_cast<int>(Item::Boulder)] = {{Actions::Lift}, 50, {Scavengeable::Boulder}, {1}};
    resources[static_cast<int>(Item::Sand)] = {{Actions::Collect}, 20, {Tile::Sand}, {300}};
    resources[static_cast<int>(Item::Stick)] = {{Actions::Collect}, 10, {Scavengeable::Stick}, {4}};
    resources[static_cast<int>(Item::LargeStick)] = {{Actions::Collect}, 10, {Scavengeable::LargeStick}, {1}};
    resources[static_cast<int>(Item::Oxisol)] = {{Actions::Collect}, 50, {Tile::Oxisol}, {300}};
    resources[static_cast<int>(Item::RockySoil)] = {{Actions::Collect}, 50, {Tile::RockySoil}, {300}};
    resources[static_cast<int>(Item::SiltySoil)] = {{Actions::Collect}, 50, {Tile::SiltySoil}, {300}};
    resources[static_cast<int>(Item::SandySoil)] = {{Actions::Collect}, 50, {Tile::SandySoil}, {300}};
    resources[static_cast<int>(Item::PeatSoil)] = {{Actions::Collect}, 50, {Tile::PeatSoil}, {300}};
    resources[static_cast<int>(Item::LoamSoil)] = {{Actions::Collect}, 50, {Tile::LoamSoil}, {300}};
    resources[static_cast<int>(Item::Podzol)] = {{Actions::Collect}, 50, {Tile::Podzol}, {300}};
    resources[static_cast<int>(Item::ClaySoil)] = {{Actions::Collect}, 50, {Tile::ClaySoil}, {300}};
    resources[static_cast<int>(Item::Stone)] = {{Actions::Mine, Actions::Mine, Actions::Mine}, 980, {Tile::Stone, Scavengeable::LargeRock, Scavengeable::Boulder}, {20,8,140}};
    resources[static_cast<int>(Item::Flint)] = {{Actions::Collect},10, {Scavengeable::Flint}, {1}};
    resources[static_cast<int>(Item::RawSalt)] = {{Actions::Mine}, 1080, {Tile::RockSalt}, {10}};
    resources[static_cast<int>(Item::Gem)] = {{Actions::Mine}, 1200, {Tile::GemOre}, {2}}; //random
//    resources[static_cast<int>(Item::Corpse)] = {{Actions::Lift}, {Scavengeable::Corpse}, {1}};
    resources[static_cast<int>(Item::Milk)] = {{Actions::Milk}, 300, {Animal::Cow}, {125}}; //twice a day
    resources[static_cast<int>(Item::GoatMilk)] = {{Actions::Milk}, 180, {Animal::Goat}, {25}}; //twice a day
    resources[static_cast<int>(Item::Fish)] = {{Actions::Fish, Actions::Fish, Actions::Fish}, 300, {Tile::ShallowWater, Tile::ShallowSaltWater, Tile::DeepWater}, {1,1,1}}; //NOTE: should be randomized
    resources[static_cast<int>(Item::Honey)] = {{Actions::Scrape, Actions::Scrape}, 480, {Scavengeable::Beehive, Scavengeable::ArtificialBeehive}, {250}}; //one action only, only 1-2 times a year
    resources[static_cast<int>(Item::RawWax)] = {{Actions::Scrape, Actions::Scrape, Actions::Cut, Actions::Cut}, 520, {Scavengeable::Beehive, Scavengeable::ArtificialBeehive, Scavengeable::Beehive, Scavengeable::ArtificialBeehive}, {15,15,15,15}}; //NOTE: destructive, only 1-2 times a year
    resources[static_cast<int>(Item::Wool)] = {{Actions::Shear}, 730, {Animal::Sheep}, {15}}; //depends on sheep growth
    resources[static_cast<int>(Item::Fruit)] = {{Actions::Collect, Actions::Collect, Actions::Collect, Actions::Collect, Actions::Collect, Actions::Collect, Actions::Collect, Actions::Collect, Actions::Collect, Actions::Collect, Actions::Collect}, 5, {Plant::OrangeTree, Plant::LemonTree, Plant::LimeTree, Plant::PeachTree, Plant::PlumTree, Plant::CherryTree, Plant::ApricotTree, Plant::AppleTree, Plant::PearTree, Plant::BlueberryShrub, Plant::StrawberryShrub, Plant::Grapevine}};
    //TODO: make much longer time for collecting
    resources[static_cast<int>(Item::Wheat)] = {{Actions::Harvest}, 8, {Plant::Wheat}, {10}};
    resources[static_cast<int>(Item::Oat)] = {{Actions::Harvest}, 8, {Plant::Oat}, {10}};
    resources[static_cast<int>(Item::Corn)] = {{Actions::Collect}, 20, {Plant::Corn}, {3}};
    resources[static_cast<int>(Item::Rice)] = {{Actions::Collect}, 80, {Plant::Rice}, {30}};
    resources[static_cast<int>(Item::Tomato)] = {{Actions::Collect}, 10, {Plant::Tomato}, {12}};
    resources[static_cast<int>(Item::Onion)] = {{Actions::Collect}, 40, {Plant::Onion}, {4}};
    resources[static_cast<int>(Item::Garlic)] = {{Actions::Dig}, 60, {Plant::Garlic}, {4}};
    resources[static_cast<int>(Item::Ginseng)] = {{Actions::Dig}, 60, {Plant::Ginseng}, {4}};
    resources[static_cast<int>(Item::Potato)] = {{Actions::Dig}, 80, {Plant::Potato}, {4}};
    resources[static_cast<int>(Item::Cabbage)] = {{Actions::Collect}, 8, {Plant::Cabbage}, {4}};
    resources[static_cast<int>(Item::Pepper)] = {{Actions::Collect}, 20, {Plant::Pepper}, {8}};
    resources[static_cast<int>(Item::Carrot)] = {{ Actions::Dig}, 60, {Plant::Carrot}, {3}};
    resources[static_cast<int>(Item::Beets)] = {{Actions::Dig}, 60, {Plant::Beets}, {4}};
    resources[static_cast<int>(Item::Kale)] = {{Actions::Collect}, 8, {Plant::Kale}, {8}};
    resources[static_cast<int>(Item::Cucumber)] = {{Actions::Collect}, 8, {Plant::Cucumber}, {3}};
    resources[static_cast<int>(Item::Poppy)] = {{Actions::Collect}, 20, {Plant::Poppy}, {7}};
    resources[static_cast<int>(Item::Hemp)] = {{Actions::Collect, Actions::Cut}, 20, {Plant::Hemp, Plant::Hemp}, {16}};
    resources[static_cast<int>(Item::Senna)] = {{Actions::Collect}, 20, {Plant::Senna}, {7}};
    resources[static_cast<int>(Item::Cotton)] = {{Actions::Collect}, 80, {Plant::Cotton}, {30}};
    resources[static_cast<int>(Item::Papyrus)] = {{Actions::Cut, Actions::Harvest}, 50, {Plant::Papyrus, Plant::Papyrus}, {8}};
    resources[static_cast<int>(Item::Flax)] = {{Actions::Cut, Actions::Harvest}, 30, {Plant::Flax, Plant::Flax}, {12}};
    resources[static_cast<int>(Item::Lettuce)] = {{Actions::Cut, Actions::Collect}, 8, {Plant::Lettuce, Plant::Lettuce}, {4}};
    resources[static_cast<int>(Item::Cocoa)] = {{Actions::Cut}, 60, {Plant::Cocoa},  {8}};
    resources[static_cast<int>(Item::Madder)] = {{Actions::Dig}, 60, {Plant::Madder}, {8}};
    resources[static_cast<int>(Item::Indigo)] = {{Actions::Collect}, 20, {Plant::Indigo}, {8}};
    resources[static_cast<int>(Item::Saffron)] = {{Actions::Collect}, 20, {Plant::Saffron}, {8}};
    resources[static_cast<int>(Item::Truffle)] = {{Actions::Dig}, 50, {Scavengeable::Truffle}, {1}};
    resources[static_cast<int>(Item::Mint)] = {{Actions::Cut}, 8, {Plant::Mint}, {8}};
    resources[static_cast<int>(Item::Thyme)] = {{Actions::Cut}, 8, {Plant::Thyme}, {8}};
    resources[static_cast<int>(Item::Lavender)] = {{Actions::Cut}, 8, {Plant::Lavender}, {8}};
    resources[static_cast<int>(Item::Rhubarb)] = {{Actions::Cut}, 8, {Plant::Rhubarb}, {4}};
    resources[static_cast<int>(Item::BlackPepper)] = {{Actions::Cut}, 8, {Plant::BlackPepper}, {4}};
    //TODO: syrup and tree resin
    //steps to create an item
}
struct Recipe {
   Actions action;
   uint32_t time;
   Item ingredients[5];
   uint8_t amounts[5]; //amounts of items
   uint8_t replaceable[5]; // 0 means totally optional, and then The value means which place it can fill. so if '1' that means any other replaceable indices (which correspond to ingredients indices) also having '1' are swappable with that ingredient.
   itemTags tags; //how much of the item is produced.
};

Recipe products[static_cast<int>(Item::MAX) - (static_cast<int>(Item::RESOURCESMAX) - static_cast<int>(Item::VARIANTSMAX))];

void initializeProducts() {
products[static_cast<int>(Item::Salt)] = {Actions::Wait, 21000,  {Item::Saltwater}, {20}, {1}, itemTags::Liquid};
products[static_cast<int>(Item::Grist)] = {Actions::Mill, 1,  {Item::Wheat, Item::Oat, Item::Corn}, {8, 4, 1}, {1,1,1}};
products[static_cast<int>(Item::Flour)] = {Actions::Mill, 1,  {Item::Grist},{1}, {1}};
products[static_cast<int>(Item::MilledRice)] = {Actions::Mill, 1,  {Item::Rice},{1}, {1}};
products[static_cast<int>(Item::Bread)] = {Actions::Bake, 320, {Item::Flour}, {20}};
products[static_cast<int>(Item::Pastry)] = {Actions::Bake, 360,  {Item::Flour, Item::Sugar, Item::Fruit, Item::Cocoa},{2, 1, 1, 1}, {1,0,2,2}, itemTags::OptionalIngredient};
products[static_cast<int>(Item::Pie)] = {Actions::Bake, 520,  {Item::Flour, Item::Sugar, Item::Fruit, Item::Milk, Item::DrinkingWater},{5, 2, 3, 2, 2}, {1,0,2,3,3}, itemTags::OptionalIngredient};
products[static_cast<int>(Item::Porridge)] = {Actions::Cook, 120,  {Item::Grist, Item::DrinkingWater, Item::Milk, Item::Fruit, Item::Honey},{2, 2, 2, 1, 1}, {1,2,2,0,0}, itemTags::OptionalIngredient};
products[static_cast<int>(Item::RawMeat)] = {Actions::Butcher,  0, {Item::Corpse}};
products[static_cast<int>(Item::CookedMeat)] = {Actions::Cook, 90,  {Item::RawMeat},{1}, {1}};
products[static_cast<int>(Item::AnimalFat)] = {Actions::Butcher, 0, {Item::Corpse}};
products[static_cast<int>(Item::Cheese)] = {Actions::Preserve, 2200,   {Item::Milk},{5}, {1}};
products[static_cast<int>(Item::GoatCheese)] = {Actions::Preserve, 2200,   {Item::Milk},{5}, {1}};
products[static_cast<int>(Item::BlueCheese)] = {Actions::Preserve, 56000,  {Item::Cheese, Item::GoatCheese},{1}, {1, 1}};
products[static_cast<int>(Item::Beer)] = {Actions::Preserve, 16000,  {Item::Wheat, Item::DrinkingWater},{30, 200}, {1,1}, itemTags::Liquid};
products[static_cast<int>(Item::Wine)] = {Actions::Preserve, 32000,  {Item::Fruit, Item::DrinkingWater},{30, 200}, {1,1}, itemTags::Liquid | itemTags::RequiresUniqueVariant};
products[static_cast<int>(Item::FruitWine)] = {Actions::Preserve, 22000,  {Item::Fruit, Item::DrinkingWater},{30, 200}, {1,1}, itemTags::Liquid};
products[static_cast<int>(Item::Mead)] = {Actions::Preserve, 54000,  {Item::Honey, Item::DrinkingWater},{20, 200}, {1, 1}, itemTags::Liquid};
products[static_cast<int>(Item::Vinegar)] = {Actions::Preserve, 70000,  {Item::Beer, Item::Wine, Item::FruitWine},{1, 1, 1}, {1,1,1}, itemTags::Liquid};
products[static_cast<int>(Item::Butter)] = {Actions::Churn, 300,  {Item::Milk},{5}, {1}, itemTags::Liquid};
products[static_cast<int>(Item::OliveOil)] = {Actions::Press, 100,  {Item::Olive},{1}, {1}, itemTags::Liquid};
products[static_cast<int>(Item::CookingOil)] = {Actions::Press, 100,  {Item::Corn, Item::Truffle, Item::Coconut, Item::DrinkingWater},{1, 2, 1, 10}, {1,1,1,2}, itemTags::Liquid | itemTags::VariableAmountProduced};
products[static_cast<int>(Item::DrinkingWater)] = {Actions::Boil, 100,  {Item::Water},{1},{1}, itemTags::Liquid};
products[static_cast<int>(Item::Juice)] = {Actions::Press, 120,  {Item::Fruit},{1},{1}, itemTags::Liquid};
products[static_cast<int>(Item::CandiedFruit)] = {Actions::Preserve, 20000,  {Item::Fruit, Item::SugarJuice},{1,15}, {1,2}};
products[static_cast<int>(Item::AgedAlcoholicDrink)] = {Actions::Preserve, 140000,   {Item::AlcoholicDrink},{1}, {1}};
products[static_cast<int>(Item::SugarJuice)] = {Actions::Mill, 100,  {Item::Sugarcane}, {1}, {1}, itemTags::Liquid};
products[static_cast<int>(Item::Sugar)] = {Actions::Boil, 400,  {Item::SugarJuice, Item::Lime}, {20, 1}, {1,2}};
products[static_cast<int>(Item::GroundBlackPepper)] = {Actions::Mill, 100,  {Item::BlackPepper},{1}, {1}};
products[static_cast<int>(Item::ChiliPowder)] = {Actions::Mill, 100,  {Item::Pepper},{1}, {1}};

// BASE MATERIALS
products[static_cast<int>(Item::Metal)] = {Actions::Smelt, 0,  {Item::Ore},{5}, .tags=itemTags::VariableAmountsRequired | itemTags::VariableAmountProduced};
products[static_cast<int>(Item::Wood)] = {Actions::Saw, 400, {Item::Log}, {18}};
products[static_cast<int>(Item::Timber)] = {Actions::Saw, 400, {Item::Log}, .tags=itemTags::VariableAmountProduced};
products[static_cast<int>(Item::Plank)] = {Actions::Saw, 200, {Item::Wood}, {1}};
products[static_cast<int>(Item::Stave)] = {Actions::Woodwork, 280,  {Item::Wood},{1}, {1}};
products[static_cast<int>(Item::LongStave)] = {Actions::Woodwork, 660,  {Item::Log, Item::Timber},{4}, {1,2}};
products[static_cast<int>(Item::Beam)] = {Actions::Woodwork, 280,  {Item::Wood, Item::LargeStick},{2,1}, {1,1}};
products[static_cast<int>(Item::LogBeam)] = {Actions::Saw, 570,  {Item::Log},{1}, {1}};
products[static_cast<int>(Item::JoinedPlank)] = {Actions::Woodwork, 100,  {Item::Plank},{1}, {1}};
products[static_cast<int>(Item::JoinedBeam)] = {Actions::Woodwork, 100,  {Item::Beam},{1}, {1}};
//products[static_cast<int>(Item::SpringPole)] = {Actions::Woodwork, {1}, {Item::LogBeam}};
products[static_cast<int>(Item::CutStone)] = {Actions::Stonework, 800,  {Item::Stone},{8}, {1}};
//products[static_cast<int>(Item::CutStoneSheet)] = {Actions::Stonework, 640,  {Item::CutStone},{1}, {1}, 8};

products[static_cast<int>(Item::Daub)] = {Actions::Mix, 180, {Item::ClaySoil, Item::Hay, Item::Sand, Item::Water},{15,3,15,20} , {1,2,3,4}, itemTags::VariableAmountProduced};
products[static_cast<int>(Item::Cob)] = {Actions::Mix, 180, {Item::ClaySoil, Item::Sand, Item::Straw, Item::Water, Item::Gravel}, {10,30,2,20,8}, {1,2,3,4,0}, itemTags::VariableAmountProduced};
products[static_cast<int>(Item::PackedEarth)] = {Actions::Mix , 40,  {Item::LoamSoil, Item::SiltySoil, Item::ClaySoil, Item::Podzol}, {15,20,12,15}, {1,1,1,1}, itemTags::Alternate};
products[static_cast<int>(Item::Lime)] = {Actions::Fire, 10800,  {Item::Stone},{1}, {1}, .tags=itemTags::RequiresUniqueVariant};
products[static_cast<int>(Item::Plaster)] = {Actions::Mix, 380, {Item::Lime,Item::Water, Item::Sand}, {1,15,10}, .tags=itemTags::Liquid};
products[static_cast<int>(Item::CrushedStone)] = {Actions::Crush, 80,  {Item::Stone, Item::Rock, Item::LargeRock},{1,1,1}, {1,2,3}, itemTags::VariableAmountsRequired | itemTags::VariableAmountProduced};
products[static_cast<int>(Item::Concrete)] = {Actions::Mix, 120,  {Item::Ash, Item::Lime, Item::Water, Item::CrushedStone, Item::Sand},{1,1,5,20,10}, {1,2,3,4,5}, itemTags::VariableAmountProduced|itemTags::Liquid};
products[static_cast<int>(Item::Mortar)] = {Actions::Mix, 140,  {Item::Clay, Item::Lime, Item::Water, Item::Sand},{1,1,1,1}, {1,1,2,3}, itemTags::Liquid};
products[static_cast<int>(Item::Glass)] = {Actions::Smelt, 400, {Item::Sand}, {20}, .tags=itemTags::VariableAmountProduced | itemTags::VariableAmountsRequired};
products[static_cast<int>(Item::Pane)] = {Actions::Glasswork, 180, {Item::Glass}, .tags=itemTags::VariableAmountProduced | itemTags::VariableAmountsRequired};
products[static_cast<int>(Item::ColoredPane)] = {Actions::Treat, 9000, {Item::Pane, Item::RedDye, Item::BlueDye, Item::YellowDye}, {1,20}, {1,2, 2,2}};
products[static_cast<int>(Item::FiredClay)] = {Actions::Fire, 150, {Item::Clay}, .tags=itemTags::Liquid | itemTags::VariableAmountProduced};
products[static_cast<int>(Item::Bricks)] = {Actions::Fire, 150, {Item::Clay, Item::BrickMold}};
products[static_cast<int>(Item::Charcoal)] = {Actions::Fire, 80, {Item::Wood}, .tags=itemTags::VariableAmountProduced | itemTags::VariableAmountsRequired};
products[static_cast<int>(Item::Bone)] = {Actions::Butcher, 0, {Item::Corpse}, .tags=itemTags::FromCorpse};
products[static_cast<int>(Item::AnimalHair)] = {Actions::Butcher, 0, {Item::Corpse}, .tags=itemTags::FromCorpse | itemTags::VariableAmountProduced};
products[static_cast<int>(Item::AnimalHides)] = {Actions::Butcher, 0, {Item::Corpse}, .tags=itemTags::FromCorpse | itemTags::VariableAmountProduced};
products[static_cast<int>(Item::Linen)] = {Actions::Treat, 950, {Item::Flax, Item::Water}, {1,10}, {1,2}, itemTags::Liquid};
products[static_cast<int>(Item::Rope)] = {Actions::Lay, 800, {Item::AnimalHair, Item::Fiber}, {30,10}, {1,1}};
products[static_cast<int>(Item::Fiber)] = {Actions::Cut, 20, {Item::Flax, Item::Hemp, Item::Papyrus}, {1,1,1}, {1,1,1}};
//TODO: do soot and ash  many items must be viable
//products[static_cast<int>(Item::Soot)] = {Actions::Burn, 50,  {Item::Wood, Item::Fruit,  Item::Plank}, {1,1,1,1}, {1,1,1,1}, itemTags::VariableAmountsRequired | itemTags::VariableAmountProduced};

products[static_cast<int>(Item::CuredHide)] = {Actions::Cur, 18000, {Item::Salt, Item::Lime, Item::AnimalHides}, {5, 2, 1}, {1,1}};
products[static_cast<int>(Item::TanningAgent)] = {Actions::Mix, 28000,{Item::Wood, Item::Water}, {1,20}, {1,2}, itemTags::VariableAmountProduced};
products[static_cast<int>(Item::TannedHide)] = {Actions::Tan, 30000, {Item::CuredHide, Item::TanningAgent}, {1,10}, {1,2}};
products[static_cast<int>(Item::HeavyTannedHide)] = {Actions::Tan, 75000, {Item::CuredHide, Item::TanningAgent}, {1,15}, {1,2}};
//ASSEMBLY
products[static_cast<int>(Item::Needles)] = {Actions::Smith, 780, {Item::Metal}, {1}};
products[static_cast<int>(Item::Strap)] = {Actions::Leatherwork, 200, {Item::CuredHide}, {1}};
products[static_cast<int>(Item::Nail)] = {Actions::Smith, 90, {Item::Metal, Item::NailHeader}, {1,0}, .tags=itemTags::OptionalIngredient | itemTags::VariableAmountProduced};
products[static_cast<int>(Item::NailHeader)] = {Actions::Smith, 1200, {Item::Metal}, {2}, {1}, .tags=itemTags::Mould};
products[static_cast<int>(Item::Lens)] = {Actions::Sculpt, 10000, {Item::Pane}};
products[static_cast<int>(Item::Wick)] = {Actions::Weave, 800, {Item::Cotton, Item::Fiber}};
products[static_cast<int>(Item::Glue)] = {Actions::Boil, 900, {Item::AnimalHides, Item::Bone, Item::Flour, Item::Resin, Item::Water}, {1,1,1,1,2}};
products[static_cast<int>(Item::String)] = {Actions::Spin, 1000, {Item::Fiber, Item::AnimalHair, Item::Sinew}, {5,20,2}, {1,1,1}, itemTags::VariableAmountProduced | itemTags::VariableAmountsRequired};
products[static_cast<int>(Item::Axle)] = {Actions::Whittle, 400, {Item::Wood}, .tags=itemTags::Alternate};
products[static_cast<int>(Item::LargeAxle)] = {Actions::Whittle, 1000, {Item::Log}};
products[static_cast<int>(Item::Gear)] = {Actions::Whittle, 2800, {Item::Wood}, .tags=itemTags::Alternate};
products[static_cast<int>(Item::SolidWheel)] = {Actions::Chisel, 48000, {Item::Stone}, .tags=itemTags::Alternate};
products[static_cast<int>(Item::Wheel)] = {Actions::WheelCraft, 4800, {Item::Stave, Item::Peg, Item::Nail, Item::Beam}, {1,2,2}};
products[static_cast<int>(Item::Sail)] = {Actions::Sew, 3300, {Item::Cloth, Item::String}};
products[static_cast<int>(Item::Tube)] = {Actions::Pott, 7400, {Item::Clay}, .tags=itemTags::Alternate};


        // CONTINUED ITEMS
products[static_cast<int>(Item::Peg)] = {Actions::Whittle, 200, {Item::Wood}, .tags=itemTags::Alternate};
products[static_cast<int>(Item::Wedge)] = {Actions::Whittle, 250, {Item::Wood}, .tags=itemTags::VariableAmountProduced};
products[static_cast<int>(Item::Rivet)] = {Actions::Smith, 300, {Item::Metal}};
products[static_cast<int>(Item::SmallHandle)] = {Actions::Whittle, 200, {Item::Beam}, .tags=itemTags::VariableAmountProduced | itemTags::Alternate};
products[static_cast<int>(Item::LargeHandle)] = {Actions::Whittle, 200, {Item::Beam}, .tags=itemTags::Alternate};
//products[static_cast<int>(Item::SocketedLargeHandle)] = {Actions::Whittle, 200, {Item::Beam}};
products[static_cast<int>(Item::BrickMold)] = {Actions::Woodwork, 750, {Item::Wood}, .tags=itemTags::Mould};
products[static_cast<int>(Item::Arrowhead)] = {Actions::Knapp, 80, {Item::Rock, Item::Bone}};
products[static_cast<int>(Item::MetalArrowhead)] = {Actions::Smith, 80, {Item::Metal}, .tags=itemTags::Alternate};

products[static_cast<int>(Item::ArrowShaft)] = {Actions::Fletch, 150, {Item::Beam}, .tags=itemTags::Alternate};

products[static_cast<int>(Item::Arrow)] = {Actions::Fletch, 60, {Item::Arrowhead, Item::MetalArrowhead, Item::ArrowShaft, Item::Feather}, {1,1,2,0}};
products[static_cast<int>(Item::Trigger)] = {Actions::Smith, 770, {Item::Metal}, .tags=itemTags::VariableAmountsRequired};
products[static_cast<int>(Item::Yarn)] = {Actions::Spin, 120, {Item::Flax, Item::Wool, Item::Cotton}};
products[static_cast<int>(Item::Thread)] = {Actions::Spin, 40, {Item::Yarn}};
products[static_cast<int>(Item::PrimitiveString)] = {Actions::Craft, 220, {Item::Fiber, Item::Sinew}, {2,1}, {1,2}};
products[static_cast<int>(Item::PrimitiveRope)] = {Actions::Craft,  1200, {Item::Fiber, Item::AnimalHair}, {2,1}};
products[static_cast<int>(Item::RopemakingFrame)] = {Actions::Woodwork, 750, {Item::Wood}};
products[static_cast<int>(Item::BackstrapLoom)] = {Actions::Craft, 890, {Item::Axle, Item::Stick, Item::PrimitiveString, Item::String, Item::TannedHide}, {1,1,2,2,3}};
products[static_cast<int>(Item::Loom)] = {Actions::Craft, 1000, {Item::Beam, Item::String}};
products[static_cast<int>(Item::FloorLoom)] = {Actions::Craft, 1280, {Item::Beam, Item::String}};
products[static_cast<int>(Item::RedDye)] = {Actions::Treat, 1780, {Item::Madder, Item::Water}, {1,2}, .tags=itemTags::Alternate | itemTags::Liquid};
products[static_cast<int>(Item::YellowDye)] = {Actions::Treat, 1780, {Item::Saffron, Item::Water}, {1,2}, .tags=itemTags::Alternate | itemTags::Liquid};
products[static_cast<int>(Item::BlueDye)] = {Actions::Treat, 1780, {Item::Indigo, Item::Water}, {1,2}, .tags=itemTags::Alternate | itemTags::Liquid};
products[static_cast<int>(Item::Bleach)] = {Actions::Treat, 1780, {Item::Lime, Item::Water}, {1,20}, {1,2}, .tags=itemTags::Liquid};
products[static_cast<int>(Item::Ink)] = {Actions::Treat, 1780, {Item::Soot, Item::Water}, .tags=itemTags::Liquid};
products[static_cast<int>(Item::Incense)] = {Actions::Burn, 1580, {Item::Resin, Item::Lavender, Item::Honey}, {3,3,4}, {1,1,2}};
products[static_cast<int>(Item::StoneTablet)] = {Actions::Chisel, 390, {Item::CutStone}};
products[static_cast<int>(Item::Paper)] = {Actions::Treat, 13000, {Item::Papyrus, Item::CuredHide, Item::Bleach}, {1,1,4}, {1,1,2}};
products[static_cast<int>(Item::TemporaryTablet)] = {Actions::Sculpt, 170, {Item::Wax, Item::Clay}, {5,5}};
products[static_cast<int>(Item::Theriac)] = {Actions::Compound, 350, {Item::Wine, Item::Poppy, Item::Saffron, Item::Mint, Item::Honey}, {1,3,3,3,8}, {1,2,3,4,5}};
products[static_cast<int>(Item::GileadBalm)] = {Actions::Compound,350, {Item::OliveOil, Item::Wax, Item::Incense},{3,3,1},{1,2,3}};
products[static_cast<int>(Item::Elactuarium)] = {Actions::Compound, 350, {Item::Honey, Item::Thyme, Item::Syrup}, {6,3,3}, {1,2,3}};
products[static_cast<int>(Item::Soap)] = {Actions::Saponify, 480, {Item::Soot, Item::AnimalFat, Item::Lavender, Item::TreeResin, Item::Incense}, {3,3,4,4,2},{1,2,0,0,0}};
products[static_cast<int>(Item::MedicinalSoap)] = {Actions::Saponify, 750, {Item::Soot, Item::AnimalFat, Item::Lavender, Item::TreeResin, Item::Incense},{3,4,4,3,2},{1,2,3,4,4}};
products[static_cast<int>(Item::Laxative)] = {Actions::Compound, 350, {Item::Water, Item::Rhubarb, Item::Senna},{4,2,2},{1,2,3}, .tags=itemTags::Alternate};

products[static_cast<int>(Item::Tonic)] = {Actions::Compound, 350, {Item::DrinkingWater, Item::Honey, Item::Ginseng}, {3,3,2}, {1,2,3}, itemTags::Alternate | itemTags::Liquid};
products[static_cast<int>(Item::Bandage)] = {Actions::Cut, 60, {Item::Cloth}};
products[static_cast<int>(Item::Poison)] = {Actions::Compound, 75, {Item::Hemlock, Item::Arsenic, Item::Cyanide, Item::Water}, {1,1,1,1}, {1,1,1,2}};
products[static_cast<int>(Item::Arsenic)] = {Actions::Smelt, 320, {Item::ArsenicOre}};
products[static_cast<int>(Item::Cyanide)] = {Actions::Grind, 200, {Item::FruitPit}, {10}};
products[static_cast<int>(Item::BoneMeal)] = {Actions::Grind, 100, {Item::Bone}};
products[static_cast<int>(Item::FishMeal)] = {Actions::Grind, 100, {Item::Fish}};
//TODO: fix fertilizer, allow any of these products to be combined together into fertilizer
products[static_cast<int>(Item::Fertilizer)] = {Actions::Mix, 130, {Item::BoneMeal, Item::FishMeal, Item::Peat, Item::Ash, Item::Lime}, {1,1,4,3,2}, {1,1,1,1,1}};
products[static_cast<int>(Item::Die)] = {Actions::Woodwork, 630, {Item::Wood}};
products[static_cast<int>(Item::CoinMould)] = {Actions::Smith, 730, {Item::Metal}, {1}, {1}, .tags=itemTags::Alternate};
products[static_cast<int>(Item::CoinBlank)] = {Actions::Cast, 190, {Item::Metal, Item::CoinMould}, {1,1}, {1,2}};
products[static_cast<int>(Item::Coins)] = {Actions::Mint, 20, {Item::CoinBlank}};
products[static_cast<int>(Item::Sling)] = {Actions::Craft, 1240, {Item::CuredHide, Item::String, Item::Rope}, {1,2,3}};
products[static_cast<int>(Item::PrimitiveBow)] = {Actions::Craft, 5800, {Item::LargeStick, Item::PrimitiveString}, {1,1}, {1,2}};
products[static_cast<int>(Item::Shortbow)] = {Actions::BowCraft, 10800, {Item::Stave, Item::String}, {1,1}, {1,2}};
products[static_cast<int>(Item::Bow)] = {Actions::BowCraft, 19000, {Item::Stave, Item::String}, {1,2}, {1,2}};
products[static_cast<int>(Item::Crossbow)] = {Actions::BowCraft, 50500, {Item::Stave, Item::Wood, Item::Trigger, Item::String}, {1,1,1,4}, {1,2,3,4}};
products[static_cast<int>(Item::Longbow)] = {Actions::BowCraft, 23800, {Item::LongStave, Item::String}, {1,4}, {1,2,3}};

//Carved Tools and Art
products[static_cast<int>(Item::PrimitiveSpearHead)] = {Actions::Knapp, 2000, {Item::Rock, Item::Bone}, .tags=itemTags::Alternate};
products[static_cast<int>(Item::PrimitiveAxeHead)] = {Actions::Knapp, 2000, {Item::Rock}};
products[static_cast<int>(Item::BoneArtifact)] = {Actions::Carve, 4800, {Item::Bone}};
products[static_cast<int>(Item::WoodArtifact)] = {Actions::WoodCarve, 4800, {Item::Wood}};
products[static_cast<int>(Item::StoneArtifact)] = {Actions::StoneCarve, 13800, {Item::Stone}};

//Tool Parts
//TODO: alternate tool head making
//short handle
products[static_cast<int>(Item::KnifeHead)] = {Actions::Smith, 2900, {Item::Metal}, {2}, .tags=itemTags::Alternate};
products[static_cast<int>(Item::SickleHead)] = {Actions::Smith, 2900, {Item::Metal}, {4}, .tags=itemTags::Alternate};
products[static_cast<int>(Item::AwlHead)] = {Actions::Smith, 4800, {Item::Metal}, {6}, .tags=itemTags::Alternate};
products[static_cast<int>(Item::AdzeHead)] = {Actions::Smith, 3200, {Item::Metal}, {5}, .tags=itemTags::Alternate};
products[static_cast<int>(Item::MalletHead)] = {Actions::Smith, 3200, {Item::Metal}, {6}, .tags=itemTags::Alternate};
products[static_cast<int>(Item::ScalpelHead)] = {Actions::Smith, 3200, {Item::Metal}, {2}, .tags=itemTags::Alternate};
products[static_cast<int>(Item::HammerHead)] = {Actions::Smith, 3200, {Item::Metal}, {11}, .tags=itemTags::Alternate};
products[static_cast<int>(Item::ChiselHead)] = {Actions::Smith, 3200, {Item::Metal}, {3}, .tags=itemTags::Alternate};
products[static_cast<int>(Item::TrowelHead)] = {Actions::Smith, 3200, {Item::Metal}, {3}, .tags=itemTags::Alternate};
products[static_cast<int>(Item::CleaverHead)] = {Actions::Smith, 3200, {Item::Metal}, {4}, .tags=itemTags::Alternate};
products[static_cast<int>(Item::MacheteHead)] = {Actions::Smith, 3200, {Item::Metal}, {5}, .tags=itemTags::Alternate};
products[static_cast<int>(Item::SwordHead)] = {Actions::Smith, 3200, {Item::Metal}, {7}, .tags=itemTags::Alternate};
products[static_cast<int>(Item::HandaxeHead)] = {Actions::Smith, 3200, {Item::Metal}, {4}, .tags=itemTags::Alternate};


products[static_cast<int>(Item::KnifeHeadMould)] = {Actions::Sculpt, 520, {Item::Clay, Item::Sand}, {1,1}};
products[static_cast<int>(Item::PermanentKnifeHeadMould)] = {Actions::Smith, 560, {Item::Metal}, .tags=itemTags::Alternate | itemTags::Mould};
products[static_cast<int>(Item::PermanentSickleHeadMould)] = {Actions::Smith, 6200, {Item::Metal}, .tags=itemTags::Alternate | itemTags::Mould};
products[static_cast<int>(Item::SickleHeadMould)] = {Actions::Sculpt, 520, {Item::Clay, Item::Sand}, {1,1}};
products[static_cast<int>(Item::PermanentAwlHeadMould)] = {Actions::Smith, 6200, {Item::Metal}, .tags=itemTags::Alternate | itemTags::Mould};
products[static_cast<int>(Item::AwlHeadMould)] = {Actions::Sculpt, 520, {Item::Clay, Item::Sand}, {1,1}};
products[static_cast<int>(Item::PermanentAdzeHeadMould)] = {Actions::Smith, 6200, {Item::Metal}, .tags=itemTags::Alternate | itemTags::Mould};
products[static_cast<int>(Item::AdzeHeadMould)] = {Actions::Sculpt, 520, {Item::Clay, Item::Sand}, {1,1}};
products[static_cast<int>(Item::PermanentMalletHeadMould)] = {Actions::Smith, 6200, {Item::Metal}, .tags=itemTags::Alternate | itemTags::Mould};
products[static_cast<int>(Item::MalletHeadMould)] = {Actions::Sculpt, 520, {Item::Clay, Item::Sand}, {1,1}};
products[static_cast<int>(Item::PermanentScalpelHeadMould)] = {Actions::Smith, 6200, {Item::Metal}, .tags=itemTags::Alternate | itemTags::Mould};
products[static_cast<int>(Item::ScalpelHeadMould)] = {Actions::Sculpt, 520, {Item::Clay, Item::Sand}, {1,1}};
products[static_cast<int>(Item::HammerHeadMould)] = {Actions::Sculpt, 520, {Item::Clay, Item::Sand}, {1,1}};
products[static_cast<int>(Item::PermanentHammerHeadMould)] = {Actions::Smith, 6200, {Item::Metal}, .tags=itemTags::Alternate | itemTags::Mould};
products[static_cast<int>(Item::ChiselHeadMould)] = {Actions::Sculpt, 520, {Item::Clay, Item::Sand},  {1,1}};
products[static_cast<int>(Item::PermanentChiselHeadMould)] = {Actions::Smith,6200, {Item::Metal}, .tags=itemTags::Alternate | itemTags::Mould};
products[static_cast<int>(Item::TrowelHeadMould)] = {Actions::Sculpt, 520, {Item::Clay, Item::Sand}, {1,1}};
products[static_cast<int>(Item::PermanentTrowelHeadMould)] = {Actions::Smith,6200, {Item::Metal}, .tags=itemTags::Alternate | itemTags::Mould};
products[static_cast<int>(Item::CleaverHeadMould)] = {Actions::Sculpt, 520, {Item::Clay, Item::Sand}, {1,1}};
products[static_cast<int>(Item::PermanentCleaverHeadMould)] = {Actions::Smith,6200, {Item::Metal}, .tags=itemTags::Alternate | itemTags::Mould};
products[static_cast<int>(Item::MacheteHeadMould)] = {Actions::Sculpt, 520, {Item::Clay, Item::Sand}, {1,1}};
products[static_cast<int>(Item::PermanentMacheteHeadMould)] = {Actions::Smith,6200, {Item::Metal}, .tags=itemTags::Alternate | itemTags::Mould};
products[static_cast<int>(Item::SwordHeadMould)] = {Actions::Sculpt, 520, {Item::Clay, Item::Sand}, {1,1}};
products[static_cast<int>(Item::PermanentSwordHeadMould)] = {Actions::Smith,6200, {Item::Metal}, .tags=itemTags::Alternate | itemTags::Mould};
products[static_cast<int>(Item::HandaxeHeadMould)] = {Actions::Sculpt,  520, {Item::Clay, Item::Sand},{1,1}};
products[static_cast<int>(Item::PermanentHandaxeHeadMould)] = {Actions::Smith,6200, {Item::Metal}, .tags=itemTags::Alternate | itemTags::Mould};

//long handle
products[static_cast<int>(Item::PrimitiveSpearHead)] = {Actions::Knapp, 1800, {Item::Rock}, {1}, .tags=itemTags::Alternate};
products[static_cast<int>(Item::ScytheHead)] = {Actions::Smith, 3200, {Item::Metal}, {6}, .tags=itemTags::Alternate};
products[static_cast<int>(Item::ScytheHeadMould)] = {Actions::Sculpt, 520, {Item::Clay, Item::Sand}, {1,1}};
products[static_cast<int>(Item::PermanentScytheHeadMould)] = {Actions::Smith,6200, {Item::Metal}, .tags=itemTags::Alternate | itemTags::Mould};
products[static_cast<int>(Item::ArdHead)] = {Actions::Smith, 3200,{Item::Metal}, {7}, .tags=itemTags::Alternate};
products[static_cast<int>(Item::ArdHeadMould)] = {Actions::Sculpt, 520, {Item::Clay, Item::Sand}, {1,1}};
products[static_cast<int>(Item::PermanentArdHeadMould)] = {Actions::Smith,6200, {Item::Metal}, .tags=itemTags::Alternate | itemTags::Mould};
products[static_cast<int>(Item::HeavySawHead)] = {Actions::Smith, 3200, {Item::Metal}, {8}, .tags=itemTags::Alternate};
products[static_cast<int>(Item::HeavySawHeadMould)] = {Actions::Sculpt,520, {Item::Clay, Item::Sand}, {1,1}};
products[static_cast<int>(Item::PermanentHeavySawHeadMould)] = {Actions::Smith, 6200, {Item::Metal}, .tags=itemTags::Alternate | itemTags::Mould};
products[static_cast<int>(Item::SawHead)] = {Actions::Smith, 3200, {Item::Metal}, {6}, .tags=itemTags::Alternate};
products[static_cast<int>(Item::SawHeadMould)] = {Actions::Sculpt, 520, {Item::Clay, Item::Sand}, {1,1}};
products[static_cast<int>(Item::PermanentSawHeadMould)] = {Actions::Smith, 6200, {Item::Metal}, .tags=itemTags::Alternate | itemTags::Mould};
products[static_cast<int>(Item::ShovelHead)] = {Actions::Smith,3200, {Item::Metal}, {9}, .tags=itemTags::Alternate};
products[static_cast<int>(Item::ShovelHeadMould)] = {Actions::Sculpt, 520, {Item::Clay, Item::Sand}, {1,1}};
products[static_cast<int>(Item::PermanentShovelHeadMould)] = {Actions::Smith, 6200, {Item::Metal}, .tags=itemTags::Alternate | itemTags::Mould};
products[static_cast<int>(Item::AxeHead)] = {Actions::Smith,3200, {Item::Metal}, {5}, .tags=itemTags::Alternate};
products[static_cast<int>(Item::AxeHeadMould)] = {Actions::Sculpt,520, {Item::Clay, Item::Sand}, {1,1}};
products[static_cast<int>(Item::PermanentAxeHeadMould)] = {Actions::Smith, 6200, {Item::Metal}, .tags=itemTags::Alternate | itemTags::Mould};
products[static_cast<int>(Item::PickaxeHead)] = {Actions::Smith, 3200, {Item::Metal}, {5}, .tags=itemTags::Alternate};
products[static_cast<int>(Item::PickaxeHeadMould)] = {Actions::Sculpt,520, {Item::Clay, Item::Sand}, {1,1}};
products[static_cast<int>(Item::PermanentPickaxeHeadMould)] = {Actions::Smith,6200, {Item::Metal}, .tags=itemTags::Alternate | itemTags::Mould};
products[static_cast<int>(Item::GreatswordHead)] = {Actions::Smith, 3200, {Item::Metal}, {12}, .tags=itemTags::Alternate};
products[static_cast<int>(Item::GreatswordHeadMould)] = {Actions::Sculpt,520, {Item::Clay, Item::Sand}, {1,1}};
products[static_cast<int>(Item::PermanentGreatswordHeadMould)] = {Actions::Smith,6200, {Item::Metal}, .tags=itemTags::Alternate | itemTags::Mould};
products[static_cast<int>(Item::GreataxeHead)] = {Actions::Smith, 3200, {Item::Metal}, {10}, .tags=itemTags::Alternate};
products[static_cast<int>(Item::GreataxeHeadMould)] = {Actions::Sculpt,520, {Item::Clay, Item::Sand}, {1,1}};
products[static_cast<int>(Item::PermanentGreataxeHeadMould)] = {Actions::Smith, 6200, {Item::Metal}, .tags=itemTags::Alternate | itemTags::Mould};
products[static_cast<int>(Item::HalberdHead)] = {Actions::Smith, 3200, {Item::Metal}, {8}, .tags=itemTags::Alternate};
products[static_cast<int>(Item::HalberdHeadMould)] = {Actions::Sculpt,520, {Item::Clay, Item::Sand}, {1,1}};
products[static_cast<int>(Item::PermanentHalberdHeadMould)] = {Actions::Smith, 6200, {Item::Metal}, .tags=itemTags::Alternate | itemTags::Mould};
products[static_cast<int>(Item::PikeHead)] = {Actions::Smith, 3200, {Item::Metal}, {10}, .tags=itemTags::Alternate};
products[static_cast<int>(Item::PikeHeadMould)] = {Actions::Sculpt,520, {Item::Clay, Item::Sand}, {1,1}};
products[static_cast<int>(Item::PermanentPikeHeadMould)] = {Actions::Smith, 6200, {Item::Metal}, .tags=itemTags::Alternate | itemTags::Mould};
products[static_cast<int>(Item::SpearHead)] = {Actions::Smith, 3200, {Item::Metal}, {4}, .tags=itemTags::Alternate};
products[static_cast<int>(Item::SpearHeadMould)] = {Actions::Sculpt, 520, {Item::Clay, Item::Sand}, {1,1}};
products[static_cast<int>(Item::PermanentSpearHeadMould)] = {Actions::Smith, 6200, {Item::Metal}, .tags=itemTags::Alternate | itemTags::Mould};
//non-handle tool

//products[static_cast<int>(Item::Yarn)] = {Actions::Weave, 750, {Item::Flax, Item::Cotton, Item::Wool, Item::Silk}, {1,1,1,1}};
products[static_cast<int>(Item::Cloth)] = {Actions::Weave, 1450, {Item::Yarn}};
products[static_cast<int>(Item::DyedCloth)] = {Actions::Treat, 960, {Item::BlueDye, Item::RedDye, Item::YellowDye, Item::Cloth, Item::DyedCloth}, {1,1,1,1,1},  {1,1,1,2,2}};
products[static_cast<int>(Item::Carpet)] = {Actions::Weave, 2000, {Item::Yarn}, {40,60,120}, {1,1,1}};
products[static_cast<int>(Item::Tribalwear)] = {Actions::LeatherCraft, 6500, {Item::CuredHide, Item::PrimitiveString}, {1,5}, {1,2}};
products[static_cast<int>(Item::BasicClothes)] = {Actions::Sew,  9800, {Item::Cloth, Item::DyedCloth, Item::Thread}, {1,1,1}, {1,1,2}};
products[static_cast<int>(Item::FormalClothes)] = {Actions::Sew, 19400, {Item::Cloth, Item::DyedCloth, Item::DyedCloth, Item::Thread}, {10,10,10,20}, {1,1,2,3}, .tags=itemTags::VariableAmountRequired};
products[static_cast<int>(Item::FancyClothes)] = {Actions::Sew, 32000, {Item::DyedCloth, Item::DyedCloth, Item::DyedCloth, Item::Thread}, {10,10,10,20}, {1,2,3,4}, .tags=itemTags::VariableAmountRequired};
products[static_cast<int>(Item::WoodCrown)] = {Actions::Whittle, 10800, {Item::Wood}, {2}};
//TODO: have it so gold crown, emperor's staff, can only be made of gold
products[static_cast<int>(Item::GoldCrown)] = {Actions::Smith, 39000, {Item::Metal}, {4}};
products[static_cast<int>(Item::RoyalCrown)] = {Actions::Smith, 23000, {Item::GoldCrown, Item::GreaterGem}, {1,5}, {1,2}};
products[static_cast<int>(Item::EmperorsStaff)] = {Actions::Craft, 34000, {Item::Metal, Item::GreaterGem, Item::Beam},{3,3,1}, {1,2,3}};
products[static_cast<int>(Item::Necklace)] = {Actions::Craft, 3500, {Item::String, Item::Bone, Item::Gold, Item::Silver}, {1,4,2,2}, {1,2,2,2}};
products[static_cast<int>(Item::Ring)] = {Actions::Smith, 5200, {Item::Metal}, .tags=itemTags::Alternate};
products[static_cast<int>(Item::Earring)] = {Actions::Smith, 4800, {Item::Metal}, .tags=itemTags::Alternate};
products[static_cast<int>(Item::Gambeson)] = {Actions::LeatherCraft, 8800, {Item::Leather, Item::Thread}, {14, 20}, {1,2}};
products[static_cast<int>(Item::DrawPlate)] = {Actions::Smith, 5400, {Item::Metal}, {6}, .tags=itemTags::Mould};
products[static_cast<int>(Item::Wire)] = {Actions::WireDraw, 750, {Item::Metal, Item::DrawPlate}, {1,1},{1,2}};
products[static_cast<int>(Item::Chainmail)] = {Actions::Smith, 72000, {Item::Wire}, {45}};
products[static_cast<int>(Item::Helmet)] = {Actions::Smith, 10400, {Item::Metal}, {18}, .tags=itemTags::Alternate};
products[static_cast<int>(Item::Breastplate)] = {Actions::Smith, 44000, {Item::Metal}, {55}, .tags=itemTags::Alternate};
products[static_cast<int>(Item::Guards)] = {Actions::Smith, 12500, {Item::Metal}, {14}, .tags=itemTags::Alternate};
products[static_cast<int>(Item::Bracers)] = {Actions::Smith, 12500, {Item::Metal}, {14}, .tags=itemTags::Alternate};
products[static_cast<int>(Item::Gloves)] = {Actions::LeatherCraft, 5600, {Item::TannedHide, Item::Thread}, {1,3}, {1,2}};
products[static_cast<int>(Item::Apron)] = {Actions::LeatherCraft, 3000, {Item::TannedHide, Item::Thread}, {3,6}, {1,2}};
products[static_cast<int>(Item::Sandals)] = {Actions::LeatherCraft, 8500, {Item::TannedHide, Item::Thread}, {1,2}};
products[static_cast<int>(Item::Boots)] = {Actions::LeatherCraft, 12000, {Item::TannedHide, Item::Thread}, {1,2}};
products[static_cast<int>(Item::Cape)] = {Actions::LeatherCraft, 9300, {Item::TannedHide, Item::Thread}, {1,2}};
products[static_cast<int>(Item::Slingstone)] = {Actions::Knapp, 130, {Item::Pebble}};
products[static_cast<int>(Item::Javelin)] = {Actions::Craft, 480, {Item::PrimitiveSpearhead, Item::Handle, Item::PrimitiveString}, {1,1,2}, {1,2,3}, itemTags::Alternate};
products[static_cast<int>(Item::Saddle)] = {Actions::LeatherCraft, 20800, {Item::Leather, Item::Wood}, {4,2}, {1,2}};
products[static_cast<int>(Item::Whip)] = {Actions::LeatherCraft, 9800, {Item::Leather, Item::Wood}, {2,1}, {1,2}};
products[static_cast<int>(Item::Horseshoes)] = {Actions::Smith, 2100, {Item::Metal}};
products[static_cast<int>(Item::Scroll)] = {Actions::Bind, 100, {Item::Paper, Item::Beam}, {1,0}};
products[static_cast<int>(Item::Book)] = {Actions::Bind, 490, {Item::Leather, Item::Wood, Item::Paper}, {1,2,3}};
products[static_cast<int>(Item::PitFire)] = {Actions::Light, 40, {Item::Stick,Item::Beam,Item::Wood,Item::Plank}, {1,1,1,1}, .tags=itemTags::VariableAmountRequired};
products[static_cast<int>(Item::Torch)] = {Actions::Light, 40, {Item::Beam,Item::Stick}};
products[static_cast<int>(Item::CandleMould)] = {Actions::Smith , 2380, {Item::Metal}, {4}, .tags=itemTags::Alternate};
products[static_cast<int>(Item::Candle)] = {Actions::Dip, 1080, {Item::Wax, Item::AnimalFat Item::Wick}, {8,6,1}, {1,1,2}, .tags=itemTags::Alternate};
products[static_cast<int>(Item::OilLamp)] = {Actions::Pott, 680, {Item::Clay, Item::Wick}, {8,1}, {1,2}, .tags=itemTags::Alternate};


//CONTAINERS

//stone

//clay
//stone
products[static_cast<int>(Item::ArtificialBeehive)] = {Actions::Pott, 4760, {Item::Clay}, {40}};

 // Overriding replaceable to default '1'
    for (auto& r : products) {
        if (/* logic to detect uninitialized recipe */) continue;
        // Default to all ones if replaceable is still zero
        bool allZero = std::all_of(std::begin(r.replaceable), std::end(r.replaceable), [](uint8_t v){ return v == 0; });
        if (allZero) {
            r.replaceable[0] = 1;
        }
        bool amountsZero = std::all_of(std::begin(r.amounts), std::end(r.replaceable), [](uint8_t v){ return v == 0; });
    }
}

Recipe alternateInterpreter(Item product) {
    Recipe recipe = products[static_cast<int>(Item::product)];
    if (static_cast<int>(recipe.tags) & static_cast<int>(itemTags::Alternate)) {
        switch (product) {
            case Item::Axle:
                return {Actions::Cast, 150 {Item::Metal, Item::AxleMould}, {7,1}, {1,2}};
            case Item::LargeAxle:
                return {Actions::Cast, 190 {Item::Metal, Item::LargeAxleMould}, {20,1}, {1,2}};
            case Item::Gear:
                return {Actions::Smith, 90,  {Item::Metal, Item::GearMould}, {1,1}, {1,2}};
            case Item::Tube:
                return {Actions::WoodCarve, 480, {Item::Wood}, {4}};
            case Item::Peg:
                return {Actions::Smith, 120, {Item::Metal}};
            case Item::MetalArrowhead:
                return {Actions::Cast, 105 {Item::Metal}, {2}};
            case Item::ArrowShaft:
                return {Actions::Whittle, 70, {Item::Beam}};
            case Item::RedDye:
                return {Actions::Treat, 1480, {Item::RedOchre, Item::Water}, {1,10}, {1,2}, .tags=itemTags::Liquid};
            case Item::YellowDye:
                return {Actions::Treat, 1480, {Item::YellowOchre, Item::Water}, {1,10}, {1,2}, .tags=itemTags::Liquid};
            case Item::BlueDye:
                return {Actions::Treat, 1480, {Item::LapisLazuli, Item::Water}, {1,10}, {1,2}, .tags=itemTags::Liquid};
            case Item::Laxative:
                return {Actions::Grind, 150, {Item::AloeVera}, {3}};
            case Item::Tonic:
                return {Actions::Compound, 1280, {Item::DrinkingWater, Item::Salt, Item::Sugar, Item::Vinegar}, {3,2,2,1}, {1,2,3,4}, itemTags::Liquid};
            case Item::PrimitiveSpearhead:
                return {Actions::Carve, 300, {Item::Bone}};
            case Item::SickleHead:
                return {Actions::Cast, 300, {Item::Metal,  Item::SickleHeadMould, Item::PermanentSickleHeadMould}, {4,1,1}, {1,2,2}};
            case Item::AwlHead:
                return {Actions::Cast, 300, {Item::Metal,  Item::AwlHeadMould, Item::PermanentAwlHeadMould}, {6,1,1}, {1,2,2}};
        case Item::AdzeHead:
            return {Actions::Cast, 300, {Item::Metal,  Item::AdzeHeadMould, Item::PermanentAdzeHeadMould}, {5,1,1}, {1,2,2}};
        case Item::MalletHead:
            return {Actions::Cast, 300, {Item::Metal,  Item::MalletHeadMould, Item::PermanentMalletHeadMould}, {6,1,1}, {1,2,2}};
        case Item::ScalpelHead:
            return {Actions::Cast, 300, {Item::Metal, Item::ScalpelHeadMould, Item::PermanentScalpelHeadMould}, {2,1,1}, {1,2,2}};
        case Item::HammerHead:
            return {Actions::Cast, 300, {Item::Metal,  Item::HammerHeadMould, Item::PermanentHammerHeadMould}, {11,1,1}, {1,2,2}};
        case Item::ChiselHead:
            return {Actions::Cast,300, {Item::Metal,  Item::ChiselHeadMould, Item::PermanentChiselHeadMould}, {3,1,1}, {1,2,2}};
        case Item::TrowelHead:
            return {Actions::Cast,300, {Item::Metal,  Item::TrowelHeadMould, Item::PermanentTrowelHeadMould}, {3,1,1}, {1,2,2}};
        case Item::CleaverHead:
            return {Actions::Cast, 300, {Item::Metal,  Item::CleaverHeadMould, Item::PermanentCleaverHeadMould}, {4,1,1}, {1,2,2}};
        case Item::MacheteHead:
            return {Actions::Cast, 300, {Item::Metal,  Item::MacheteHeadMould, Item::PermanentMacheteHeadMould}, {5,1,1}, {1,2,2}};
        case Item::SwordHead:
            return {Actions::Cast, 300, {Item::Metal,  Item::SwordHeadMould, Item::PermanentSwordHeadMould}, {7,1,1}, {1,2,2}};
        case Item::HandaxeHead:
            return {Actions::Cast, 300, {Item::Metal,  Item::HandaxeHeadMould, Item::PermanentHandaxeHeadMould}, {4,1,1}, {1,2,2}};
        case Item::PrimitiveSpearHead:
            return {Actions::Cast, 300, {Item::Metal,  Item::PrimitiveSpearHeadMould, Item::PermanentPrimitiveSpearHeadMould}, {3,1,1}, {1,2,2}};
case Item::ScytheHead:
 return {Actions::Cast, 300, {Item::Metal,  Item::ScytheHeadMould, Item::PermanentScytheHeadMould}, {6,1,1}, {1,2,2}};
case Item::ArdHead:
 return {Actions::Cast,300,{Item::Metal,  Item::ArdHeadMould, Item::PermanentArdHeadMould}, {7,1,1}, {1,2,2}};
case Item::HeavySaw:
  return {Actions::Cast,300, {Item::Metal,  Item::HeavySawMould, Item::PermanentHeavySawMould}, {8,1,1}, {1,2,2}};
case Item::SawHead:
 return {Actions::Cast,300, {Item::Metal,  Item::SawHeadMould, Item::PermanentSawHeadMould}, {6,1,1}, {1,2,2}};
case Item::ShovelHead:
 return {Actions::Cast,300, {Item::Metal,  Item::ShovelHeadMould, Item::PermanentShovelHeadMould}, {9,1,1}, {1,2,2}};
case Item::AxeHead:
 return {Actions::Cast,300, {Item::Metal,  Item::AxeHeadMould, Item::PermanentAxeHeadMould}, {5,1,1}, {1,2,2}};
case Item::PickaxeHead:
 return {Actions::Cast,300, {Item::Metal,  Item::PickaxeHeadMould, Item::PermanentPickaxeHeadMould}, {5,1,1}, {1,2,2}};
case Item::GreatswordHead:
 return {Actions::Cast,300, {Item::Metal,  Item::GreatswordHeadMould, Item::PermanentGreatswordHeadMould}, {12,1,1}, {1,2,2}};
case Item::GreataxeHead:
return {Actions::Cast,300, {Item::Metal,  Item::GreataxeHeadMould, Item::PermanentGreataxeHeadMould}, {10,1,1}, {1,2,2}};
case Item::HalberdHead:
return {Actions::Cast,300, {Item::Metal,  Item::HalberdHeadMould, Item::PermanentHalberdHeadMould}, {8,1,1}, {1,2,2}};
case Item::PikeHead:
return {Actions::Cast,300, {Item::Metal,  Item::PikeHeadMould, Item::PermanentPikeHeadMould}, {10,1,1}, {1,2,2}};
case Item::SpearHead:
return {Actions::Cast,300, {Item::Metal,  Item::SpearHeadMould, Item::PermanentSpearHeadMould}, {4,1,1}, {1,2,2}};
case Item::SmallHandle:
    return {Actions::Whittle, 860, {Item::Stick}, {1}};
case Item::LargeHandle:
    return {Actions::Whittle, 1260, {Item::LargeStick}, {1}};
case Item::DyedCloth:
return {Actions::Treat, 980,{Item::Bleach, Item::Ink, Item::Cloth, Item::DyedCloth}, {1,1,2,2}}
case Item::Ring:
return {Actions::Carve, 490, {Item::Bone}};
case Item::Earring:
return {Actions::Carve, 410, {Item::Bone}};
case Item::Helmet:
    return {Actions::Leatherwork, 1080, {Item::TannedHide, Item::Thread}, {4,2},{1,2}};
case Item::Breastplate:
    return {Actions::Leatherwork, 2390, {Item::TannedHide, Item::Thread}, {10,4}, {1,2}};
case Item::Guards:
    return {Actions::Leatherwork, 880, {Item::TannedHide, Item::Thread}, {4,2}, {1,2}};
case Item::Bracers:
    return {Actions::Leatherwork, 790, {Item::TannedHide, Item::Thread}, {4,2}, {1,2}};
case Item::Javelin:
    return {Actions::Craft, 40, {Item::Weaponhead, Item::LargeHandle, Item::PrimitiveString, Item::String}, {1,1,1,1}, {1,2,3,3}};
case Item::CandleMould:
return {Actions::Pott , 230, {Item::Clay}};
case Item::Candle:
return {Actions::CandleMould, 990, {Item::Wax, Item::AnimalFat, Item::Wick,}, {8,6,1}, {1,1,2}};
case Item::OilLamp:
return {Actions::Smith, 990, {Item::Metal, Item::Wick}, {4,1} {1,2}};
case Item::Bowl:
return {Actions::Pott, 420, {Item::Clay}};
default:
    return {};
}
        return {};
}


struct CorpseData {
            Item products[];
            uint16_t amounts[];
            Hide hide;
            Meat meat;
            int time;
}

CorpseData corpseInterpreter(Station corpse) {
                switch (corpse) {
                case Station::PigCorpse:
                    return {{Item::RawMeat, Item::AnimalFat, Item::Bone, Item::AnimalHides}, {785, 22, 18, 30}, Meat::Pork, Hide::PigSkin, 950};
                case Station::CowCorpse:
                    return {{Item::RawMeat, Item::AnimalFat, Item::Bone, Item::AnimalHides, Item::AnimalHair}, {1890, 20, 35, 55, 6}, Meat::Beef, Hide::CowHide, 1670};
                case Station::ChickenCorpse:
                    return {{Item::RawMeat, Item::AnimalFat, Item::Bone, Item::Feather}, {95, 2, 7, 35}, Meat::Chicken, Hide::NONE, 270};
                case Station::DuckCorpse:
                    return {{Item::RawMeat, Item::AnimalFat, Item::Bone, Item::Feather}, {78, 4, 7, 24}, Meat::Duck, Hide::NONE, 270};
                case Station::SheepCorpse:
                    return {{Item::RawMeat, Item::AnimalFat, Item::Bone, Item::AnimalHides}, {410, 10, 14, 20}, Meat::Sheep, Hide::SheepHide, 840};
                case Station::GoatCorpse:
                    return {{Item::RawMeat, Item::AnimalFat, Item::Bone, Item::AnimalHides, Item::AnimalHair}, {360, 11, 12, 20, 3}, Meat::Goat, Hide::GoatHide, 810};
                case Station::OxCorpse:
                    return {{Item::RawMeat, Item::AnimalFat, Item::Bone, Item::AnimalHides, Item::AnimalHair}, {3200, 15, 55, 80, 10}, Meat::Ox, Hide::OxHide, 2250};
                case Station::HorseCorpse:
                    return {{Item::RawMeat, Item::AnimalFat, Item::Bone, Item::AnimalHides, Item::AnimalHair}, {40, 1, 40, 30, 6}, Meat::Horse, Hide::HorseSkin, 1340};
                case Station::DonkeyCorpse:
                    return {{Item::RawMeat, Item::AnimalFat, Item::Bone, Item::AnimalHides, Item::AnimalHair}, {30, 1, 30, 20, 3}, Meat::Donkey, Hide::DonkeySkin, 1100};
                case Station::CamelCorpse:
                    return {{Item::RawMeat, Item::AnimalFat, Item::Bone, Item::AnimalHides, Item::AnimalHair}, {520, 8, 20, 30, 12}, Meat::Camel, 1800};
                case Station::WaterBuffaloCorpse:
                    return {{Item::RawMeat, Item::AnimalFat, Item::Bone, Item::AnimalHides, Item::AnimalHair}, {2800, 15, 55, 75, 10}, Meat::WaterBuffalo, Hide::WaterBuffaloHide, 2100};
                case Station::RabbitCorpse:
                    return {{Item::RawMeat, Item::AnimalFat, Item::Bone, Item::AnimalHides, Item::AnimalHair}, {55, 3, 5, 3}, Meat::Rabbit, 240};
                case Station::AntelopeCorpse:
                    return {{Item::RawMeat, Item::AnimalFat, Item::Bone, Item::AnimalHides, Item::AnimalHair}, {540, 1, 20, 20, 12}, Meat::Antelope, Hide::AntelopeHide, 1280};
                case Station::DeerCorpse:
                    return {{Item::RawMeat, Item::AnimalFat, Item::Bone, Item::AnimalHides, Item::AnimalHair}, {480, 1, 18, 18, 10}, Meat::Deer, Hide::DeerHide, 1000};
                case Station::MooseCorpse:
                    return {{Item::RawMeat, Item::AnimalFat, Item::Bone, Item::AnimalHides, Item::AnimalHair}, {2480, 5, 55, 65, 20}, Meat::Moose, Hide::MooseHide, 2690};
                case Station::CapybaraCorpse:
                    return {{Item::RawMeat, Item::AnimalFat, Item::Bone, Item::AnimalHides, Item::AnimalHair}, {280, 2, 10, 12, 18}, Meat::Capybara, Hide::CapybaraHide, 560};
                case Station::ElephantCorpse:
                    return {{Item::RawMeat, Item::AnimalFat, Item::Bone, Item::AnimalHides}, {11800, 30, 120, 104}, Meat::Elephant, Hide::ElephantHide, 4060};
                case Station::BisonCorpse:
                    return {{Item::RawMeat, Item::AnimalFat, Item::Bone, Item::AnimalHides, Item::AnimalHair}, {3800, 25, 42, 55, 45}, Meat::Bison, Hide::BisonHide, 2600};
                case Station::WolfCorpse:
                    return {{Item::RawMeat, Item::AnimalFat, Item::Bone, Item::AnimalHides, Item::AnimalHair}, {180, 1, 22, 15, 25}, Meat::Wolf, Hide::WolfPelt, 1080};
                case Station::BearCorpse:
                    return {{Item::RawMeat, Item::AnimalFat, Item::Bone, Item::AnimalHides, Item::AnimalHair}, {2200, 3, 50, 40, 20}, Meat::Bear, Hide::Bear, 2350};
                case Station::CaribouCorpse:
                    return {{Item::RawMeat, Item::AnimalFat, Item::Bone, Item::AnimalHides, Item::AnimalHair}, {740, 1, 28, 24, 14}, Meat::Caribou, Hide::CaribouHide, 1280};
                default:
                    return {};
            }

void meals() {

}

struct ToolRecipe() {
    Actions action;
    uint16_t time;
    Item ingredients[7];
    uint8_tslots[7];
};

ToolRecipe tools[Tool::MAX];

void initializeTools() {
//SHORT HANDLE
tools[static_cast<int>(Tools::DiggingStick)] = {Actions::Carve, 1300, {Item::Stick, Item::LargeStick}};
tools[static_cast<int>(Tools::StickSpear)] = {Actions::Carve, 900, {Item::LargeStick}};
tools[static_cast<int>(Tools::PrimitiveSpear)] = {Actions::Craft, 500, {Item::Stick, Item::LargeHandle, Item::PrimitiveString, Item::PrimitiveSpearHead}};
tools[static_cast<int>(Tools::PrimitiveAxe)] = {Actions::Craft, 500, {Item::Stick, Item::LargeHandle, Item::PrimitiveString, Item::PrimitiveAxeHead}};
tools[static_cast<int>(Tools::Sickle)] = {{Actions::Craft}, 280, {Item::SickleHead, Item::SmallHandle, Item::Peg}, {1,1,1}, {1,2,3}};
tools[static_cast<int>(Tools::Awl)] = {{Actions::Craft}, 280, {Item::AwlHead, Item::SmallHandle, Item::Peg}, {1,1,1}, {1,2,3}};
tools[static_cast<int>(Tools::Adze)] = {{Act::Craft}, 280, {Item::SmallHandle, Item::SmallHandle, Item::Peg}  {1,1,1},, {1,2,3}};
tools[static_cast<int>(Tools::Mallet)] = {{Action::Craft},280, {Item::MalletHead, Item::SmallHandle, Item::Peg}, {1,1,1}, {1,2,3}};
tools[static_cast<int>(Tools::Hammer)] = {{Actions::Craft}, 280, {Item::HammerHead, Item::SmallHandle, Item::Peg}, {1,1,1}, {1,2,3}};
tools[static_cast<int>(Tools::Chisel)] = {{Actions::Craft}, 280, {Item::ChiselHead, Item::SmallHandle, Item::Peg}, {1,1,1}, {1,2,3}};
tools[static_cast<int>(Tools::Trowel)] = {{Actions::Craft}, 280, {Item::TrowelHead, Item::SmallHandle, Item::Peg}, {1,1,1}, {1,2,3}};
tools[static_cast<int>(Tools::Cleaver)] = {{Actions::Craft}, 280, {Item::CleaverHead, Item::SmallHandle, Item::Peg}, {1,1,1}, {1,2,3}};
tools[static_cast<int>(Tools::Machete)] = {{Actions::Craft}, 280, {Item::MacheteHead, Item::SmallHandle, Item::Peg}, {1,1,1}, {1,2,3}};
tools[static_cast<int>(Tools::Sword)] = {{Actions::Craft}, 280, {Item::SwordHead, Item::SmallHandle, Item::Peg}, {1,1,1}, {1,2,3}};
tools[static_cast<int>(Tools::Handaxe)] = {{Actions::Craft}, 280, {Item::HandaxeHead, Item::SmallHandle, Item::Peg}, {1,1,1}, {1,2,3}};
tools[static_cast<int>(Tools::HandDrill)] = {{Actions::Craft}, 280, {Item::Stick, Item::Beam, Item::SmallHandle, Item::Peg, Item::String}, {1,1,1}, {1,1,2,3,3}};
case Item::ArdHead:
 return {Actions::Smith, 3200,{Item::Metal}, {7}};tools[static_cast<int>(Tools::Graver)] = {{Actions::Craft}, 280, {Item::SmallHandle, Item::Peg, Item::GraverHead}, {1,1,1}, {1,2,3}};

//LONG HANDLE
tools[static_cast<int>(Tools::PrimitiveSpear)] = 280, {{Actions::Craft}, {Item::PrimitiveSpearHead, Item::LargeHandle, Item::PrimitiveString}} {1,1,1},;
tools[static_cast<int>(Tools::Scythe)] = {{Actions::Craft}, 280, {Item::ScytheHead, Item::LargeHandle, Item::Wedge, Item::Rivet}, {1,1,1}, {1,2,3,3}};
tools[static_cast<int>(Tools::Ard)] = {{Actions::Craft}, 280, {Item::ArdHead, Item::LargeHandle, Item::Wedge, Item::Rivet}, {1,1,1}, {1,2,3,3}};
tools[static_cast<int>(Tools::HeavySaw)] = {{Actions::Craft}, 280, {Item::HeavySawHead, Item::LargeHandle, Item::Wedge, Item::Rivet}, {1,1,1}, {1,2,3,3}};
tools[static_cast<int>(Tools::Saw)] = {{Actions::Craft}, 280, {Item::SawHead, Item::LargeHandle, Item::Wedge, Item::Rivet}, {1,1,1}, {1,2,3,3}};
tools[static_cast<int>(Tools::Shovel)] = {{Actions::Craft}, 280, {Item::ShovelHead, Item::LargeHandle, Item::Wedge, Item::Rivet}, {1,1,1}, {1,2,3,3}};
tools[static_cast<int>(Tools::Axe)] = {{Actions::Craft}, 280, {Item::AxeHead, Item::LargeHandle, Item::Wedge, Item::Rivet}, {1,1,1}, {1,2,3,3}};
tools[static_cast<int>(Tools::Pickaxe)] = {{Actions::Craft}, 280, {Item::PickaxeHead, Item::LargeHandle, Item::Wedge, Item::Rivet}, {1,1,1}, {1,2,3,3}};
tools[static_cast<int>(Tools::Greatsword)] = {{Actions::Craft}, 280, {Item::GreatswordHead, Item::LargeHandle, Item::Wedge, Item::Rivet}, {1,1,1}, {1,2,3,3}};
tools[static_cast<int>(Tools::Greataxe)] = {{Actions::Craft}, 280, {Item::GreataxeHead, Item::LargeHandle, Item::Wedge, Item::Rivet}, {1,1,1}, {1,2,3,3}};
tools[static_cast<int>(Tools::Halberd)] = {{Actions::Craft}, 280, {Item::HalberdHead, Item::LargeHandle, Item::Wedge, Item::Rivet}, {1,1,1}, {1,2,3,3}};
tools[static_cast<int>(Tools::Pike)] = {{Actions::Craft}, 280, {Item::PikeHead, Item::LargeHandle, Item::Wedge, Item::Rivet}, {1,1,1}, {1,2,3,3}};
tools[static_cast<int>(Tools::Spear)] = {{Actions::Craft}, 280, {Item::SpearHead, Item::LargeHandle, Item::Wedge, Item::Rivet}, {1,1,1}, {1,2,3,3}};


// NON-HANDLE
tools[static_cast<int>(Tools::Shear)] = {{Actions::Smith}, 670, {Item::Metal}, {4}};
tools[static_cast<int>(Tools::Tongs)] = {{Actions::Smith}, 1000, {Item::Metal}, {4}};
tools[static_cast<int>(Tools::Pestle)] = {{Actions::Knapp}, 1280, {Item::Stone, Item::Rock}, {1,1}};
tools[static_cast<int>(Item::PatternedDie)] = {Actions::Engrave, 1400, {Item::Die}};
tools[static_cast<int>(Item::BackstrapLoom)] = {Actions::Craft, 1380, {Item::Beam, Item::Stick, Item::Peg, Item::String, Item::Leather}, {1,1,2,4,2}, {1,1,0,3,4}};
tools[static_cast<int>(Item::Blowpipe)] = {Actions::Pott, 720, {Item::Clay, Item::Papyrus}, {7,2}, {1,1}};
tools[static_cast<int>(Item::HandheldBellows)] = {Actions::Craft, 1480, {Item::Airbag, Item::SmallHandle, Item::Strap}, {1,1,1}, {1,2,3}};
//possible edit
tools[static_cast<int>(Item::Satchel)] = {Actions::LeatherCraft, 1280, {Item::Leather, Item::PrimitiveString, Item::String}, {8,3,3}, {1,2,2}};
tools[static_cast<int>(Item::LargeSatchel)] = {Actions::LeatherCraft, 2180, {Item::Leather, Item::PrimitiveString, Item::String}, {16,6,6}, {1,2,2}};
}

uint32_t liquidCapacityInterpreter(Item container) {
switch (container) {
    case Item::Keg:
        return 8000;
    case Item::Jar:
        return 30;
    case Item::Kettle:
        return 200;
    case Item::Pot:
        return 500;
    case Item::LargePot:
        return 2000;
    case Item::Bucket:
        return 1200;
    default:
        return 0;
}
}

struct ContainerRecipe() {
    Actions action;
    uint16_t time;
    Item ingredients[7];
    uint8_t amounts[7];
    uint16_t liquidCapacity;
};

ContainerRecipe containers[Container::MAX];
ContainerRecipe containersAlternate[Container::MAX];

void initializeContainers() {
containers[static_cast<int>(Container::Pot)] =  {{Actions::Smith, {Item::Metal}};
containers[static_cast<int>(Container::Bucket)] = {Actions::Smith, 1900, {Item::Metal}, {25}, 1200};
containers[static_cast<int>(Container::Basket)] = {Actions::BasketWeave, 2650, {Item::Hemp, Item::Flax}, {20}, 0};
containers[static_cast<int>(Container::MashTun)] =  {Actions::Pott, {Item::Clay}};
containers[static_cast<int>(Container::Pot)] =  {Actions::Smith, {Item::Metal}};
containers[static_cast<int>(Container::MeltingPot)] =  {Actions::Smith, {Item::Metal}};
containers[static_cast<int>(Container::Kettle)] =  {Actions::Smith, {Item::Metal}};
containers[static_cast<int>(Container::Jar)] =  {Actions::Glasswork, {Item::Glass}};
containers[static_cast<int>(Container::Crucible)] =  {Actions::Smith, {Item::Metal}};
containers[static_cast<int>(Container::Bucket)] =  {Actions::Pott, 1400, {Item::Clay}, {25}};
containers[static_cast<int>(Container::Bowl)] = {Actions::Whittle, 650, {Item::Wood}};
containers[static_cast<int>(Container::Keg)] = {Actions::Craft, 880, {Item::Stave, Item::Nail}, {25,45}, {1,2}};
containers[static_cast<int>(Container::MashTun)] = {Actions::Craft, 1480, {Item::LongStave, Item::Nail}, {18,40}, {1,2}};
containers[static_cast<int>(Container::Pot)] = {Actions::Pott, 3270, {Item::Clay}, {30}};
containers[static_cast<int>(Container::LargePot)] = {Actions::Pott, 9400, {Item::Clay}, {108}};
containers[static_cast<int>(Container::MeltingPot)] = {Actions::Pott, 1850, {Item::Clay}, {13}};
containers[static_cast<int>(Container::Kettle)] = {Actions::Pott, 1700, {Item::Clay}, {10}};
containers[static_cast<int>(Container::Jar)] = {Actions::Pott, 850, {Item::Clay}, {4}};
containers[static_cast<int>(Container::Crucible)] = {Actions::Pott, 1700, {Item::Clay}, {20}};
}

struct BuildableRecipe() {
    Actions action;
    Item ingredients[8];
    uint8_t slots[8];
};

BuildableRecipe buidables[Buildable::MAX];

void intiailizeBuildables() {
// WALLS AND ROOFS
buildables[static_cast<int>(Buildable::TentSticks)] = {Actions::Build, 150,  {Item::Stick, Item::Beam, Item::PrimitiveString, Item::String}, {6,6,4,4}, {1,1,2,2}};
buildables[static_cast<int>(Buildable::WattleWall)] = {Actions::Build, 240, {Item::Stick, Item::Daub}, {6, 20}, {1,2}};
buildables[static_cast<int>(Buildable::WoodWall)] = {Actions::Build, 140, {Item::Timber, Item::Plank, Item::Nails}, {1,0,0}};
buildables[static_cast<int>(Buildable::Wall)] = {Actions::Build, 200, {Item::Brick, Item::Mudbrick, Item::Stone, Item::Cob}, {16,16, 16, 30}, {1,1,1,1}};
buildables[static_cast<int>(Buildable::WallPanel)] = {Actions::Build, 120 {Item::Plank, Item::MetalPlate, Item::Peg, Item::Nail}, , {1,1,4,4}, {1,1,2,2}};
buildables[static_cast<int>(Buildable::Pillar)] = {Actions::Stonework, 3000, {Item::Stone}};
buildables[static_cast<int>(Buildable::PlacedPillar)] = {Actions::Build, 150, {Item::Pillar}};
buildables[static_cast<int>(Buildable::TentCover)] = {Actions::Build, 60, {Item::CuredHide}};
buildables[static_cast<int>(Buildable::WattleRoof)] = {Actions::Build, 440, {Item::Stick, Item::Daub}, {6, 20}, {1,2}};
buildables[static_cast<int>(Buildable::RoofBeams)] = {Actions::Build, 380, {Item::LogBeam}};
buildables[static_cast<int>(Buildable::Roof)] = {Actions::Build, 320, {Item::CutStone, Item::Brick, Item::FiredClay, Item::Plank}, {1,2,3,4}};
buildables[static_cast<int>(Buildable::PottersWheel)] = {Actions::Craft, {Item::SolidWheel, Item::Wheel, Item::Beam, Item::Stick, Item::JoinedBeam}, {1,1,1,1,6}, {1,1,2,2,0}, .tags=itemTags::OptionalIngredient};
buildables[static_cast<int>(Buildable::Anvil)] = {Actions::Smith, 14700, {Item::Metal}, {90}, .tags=itemTags::OptionalIngredient};
buildables[static_cast<int>(Buildable::PitKiln)] = {Actions::Dig, 680}; // possible edit
buildables[static_cast<int>(Buildable::EarthMoundKiln)] = {Actions::Build, 1490, {Item::Timber, Item::Clay, Item::PackedEarth, Item::Rock}, {1,2,2,0}};
buildables[static_cast<int>(Buildable::PitFurnace)] = {Actions::Dig, 900}; // possible edit
buildables[static_cast<int>(Buildable::AdvancedPitFurnace)] = {Actions::Build, 2080, {Item::Clay}};
buildables[static_cast<int>(Item::Furnace)] = {Actions::Build, 5060, {Item::Clay, Item::Bricks, Item::Stone, Item::Tube}, {1,2,2,3}};
buildables[static_cast<int>(Buildable::BloomeryFurnace)] = {Actions::Build, 7800, {Item::Clay, Item::Bricks, Item::Stone, Item::Tube}, {1,2,2,3}};
buildables[static_cast<int>(Buildable::Forge)] = {Actions::Build, 3080, {Item::Clay, Item::Bricks, Item::Stone, Item::Tube}, {1,2,2,3}};
buildables[static_cast<int>(Buildable::Bellows)] = {Actions::Build, 2200, {Item::Airbag, Item::FootPedal, Item::Hinge, Item::Piston, Item::Tube}, {2,1,6,2,3}, {1,2,3,4,5}};
buildables[static_cast<int>(Buildable::DoubleBellows)] = {Actions::Build, 4000, {Item::Airbag, Item::FootPedal, Item::Hinge, Item::Piston, Item::Tube}, {4,2,12,4,6}, {1,2,3,4,5}, .tags=itemTags::Alternate};
buildables[static_cast<int>(Buildable::WaterPoweredBellows)] = {Actions::Build, 1400, {Item::WaterWheel, Item::Hinge, Item::Piston, Item::Axle, Item::LargeAxle, Item::Tube}, {1,8,3,1,1,4}, {1,2,3,4,4,5}};

buildables[static_cast<int>(Buildable::DugCanal)] = {Actions::Dig, 440};
buildables[static_cast<int>(Buildable::Canal)] = {Actions::DigBuild, 1300, {Item::Clay, Item::Brick}, {25,15}, {1,1}};
buildables[static_cast<int>(Buildable::Well)] = {Actions::Engineer, 50800, {Item::CutStone, Item::Brick, Item::Mortar, Item::Rope, Item::Bucket}, {30,150,300,8,1},{1,1,2,3,0}};
buildables[static_cast<int>(Buildable::Siphon)] = {Actions::Engineer, 1080, {Item::Tube, Item::Wax, Item::Clay, Item::Bucket, Item::Stone, Item::Brick, Item::Strap},{1,1,1,1,4,6,1}, {1,2,2,3,4,4,5}};
buildables[static_cast<int>(Buildable::Tube)] = {Actions::Build, 200, {Item::Tube, Item::Wax, Item::Clay}, {1,4,4}, {1,2,2}};
buildables[static_cast<int>(Buildable::BucketPump)] = {Actions::Build, 100, {Item::Bucket, Item::Pulley}, {1,1}, {1,2}};
buildables[static_cast<int>(Buildable::SuctionPump)] = {Actions::Engineer, 1600, {Item::Tube, Item::Strap, Item::Piston, Item::FootPedal}, {1,2,1,1}, {1,2,3,4}};
buildables[static_cast<int>(Buildable::HydraulicPump)] = {Actions::Engineer, 1300, {Item::WaterWheel, Item::Strap, Item::Bucket, Item::Gear, Item::Axle, Item::Stone, Item::Brick},{1,2,1,5,1,6,10}, {1,2,3,4,5,6,6}};
buildables[static_cast<int>(Buildable::Aqueduct)] = {Actions::Engineer, 500, {Item::CutStone, Item::Brick, Item::Mortar}, {1,1,2}, {8,20,10}};

buildables[static_cast<int>(Buildable::Foundation)] = {Actions::Build, 500, {Item::Stone, Item::Concrete, Item::Rock, Item::Brick, Item::PackedEarth}, {6,30,14,24,30}, {1,1,1,1,1}};
buildables[static_cast<int>(Buildable::Floor)] = {Actions::Build, 300, {Item::Plank, Item::Brick, Item::PackedEarth, Item::FiredClay}, {8,14,20,20}, {1,1,1,1}};
buildables[static_cast<int>(Buildable::Carpet)] = {Actions::Build, 10, {Item::Carpet}};
buildables[static_cast<int>(Buildable::PlowedDirt)] = {Actions::Plow, 180};

// WORKSTATIONS
buildables[static_cast<int>(Buildable::Tabletop)] = {Actions::WoodCraft, 2300, {Item::Plank, Item::CutStone, Item::Beam, Item::Peg, Item::Nail}, {8,3,4,8,8} {1,1,2,3,3}, .tags=itemTags::Alternate};
buildables[static_cast<int>(Buildable::Stool)] = {Actions::WoodCraft, 900, {Item::Plank, Item::Beam, Item::Peg, Item::Nail}, {8,4,4,4}, {1,2,3,3}, .tags=itemTags::Alternate};
buildables[static_cast<int>(Buildable::PrimitiveStool)] = {Actions::Chisel, 6200, {Item::LargeRock, Item::Boulder}, {2,1}, {1,1}, .tags=itemTags::Alternate};
buildables[static_cast<int>(Buildable::Chair)] = {Actions::Craft, 1300, {Item::Plank, Item::Beam, Item::Peg, Item::Nail}, {3,4,8,8},{1,2,3,3}, .tags=itemTags::Alternate};
buildables[static_cast<int>(Buildable::Waterwheel)] = {Actions::Engineer, 5400, {Item::Stave, Item::Nail, Item::Bolt, Item::Axle, Item::LargeAxle}, {12,40,4,1,1}, {1,2,3,4,4}};
buildables[static_cast<int>(Buildable::Pulley)] = {Actions::Engineer, 12800,{Item::Plank, Item::Wood, Item::Beam, Item::Rope, Item::Nail, Item::Bolt}, {8,10,10,4,20,4}, {1,2,3,4,5,6}};
buildables[static_cast<int>(Buildable::SimpleLoom)] = {Actions::Craft, 800, {Item::Beam, Item::Stick, Item::Peg, Item::String}, {4,4,4,30}, {1,1,0,3}};
buildables[static_cast<int>(Buildable::Vertical)] = {Actions::Craft, 1900, {Item::Beam, Item::Stick, Item::Peg, Item::Nail, Item::Cloth, Item::Papyrus, Item::String}, {7,7,12,12,4,4,70}, {1,1,2,2,3,3,4}};
buildables[static_cast<int>(Buildable::Floor)] = {Actions::Craft, 2200, {Item::Beam, Item::Stick, Item::Peg, Item::Nail, Item::Cloth, Item::Papyrus, Item::String}, {10,10,16,16,6,6,80} {1,1,2,2,3,3,4}};
// Art
buildables[static_cast<int>(Buildable::ClaySculpture)] = {Actions::Sculpt, 21600, {Item::Clay}, {250}, itemTags::VariableAmountRequired};
buildables[static_cast<int>(Buildable::SculptMould)] = {Actions::SculptMould, 820, {Item::Plaster}, {20}, itemTags::VariableAmountRequired};
buildables[static_cast<int>(Buildable::WoodSculpture)] = {Actions::WoodCarve, 56800, {Item::Log}, {1}, itemTags::VariableAmountRequired};
buildables[static_cast<int>(Buildable::StoneSculpture)] = {Actions::StoneCarve, 104890, {Item::Stone}, {70}, itemTags::VariableAmountRequired};
buildables[static_cast<int>(Buildable::MetalSculpture)] = {Actions::Cast, 4500, {Item::Metal, Item::SculptMould}, {250, 1}, {1,2}, itemTags::VariableAmountRequired};
}

BuildableRecipe buildableAlternateInterpreter(Buildable building) {
    BuildableRecipe recipe = buildables[static_cast<int>(Item::building)];
    if (static_cast<int>(recipe.tags) & static_cast<int>(itemTags::Alternate)) {
        switch (building) {
            case Buildable::Anvil:
                return {Actions::Chisel, 7900, {Item::Stone, Item::LargeRock}, {10,3}, {1,1}};
            case Buildable::DoubleBellows:
            return {Actions::Build, 2300, {Item::Bellows, Item::LargeAirbag, Item::Hinge, Item::Piston, Item::Tube}, {1,2,6,3,4} {1,2,3,4,5}};
            case Buildable::Tabletop:
                return {Actions::WoodCraft, 2000, {Item::JoinedPlank, Item::JoinedBeam}, {8,4}, {1,2}};
            case Buildable::Stool:
            return {Actions::WoodCraft, 800, {Item::JoinedPlank, Item::JoinedBeam}, {8,4}, {1,2}};
            case Buildable::PrimitiveStool:
            return {Actions::Saw, 2800, {Item::Log}, {1}, {1}};
        }
    }
    return {};
}

struct VehicleRecipe() {
    Item item;
    Actions action;
    Item ingredients[10];
    uint_8 slots[10];
    uint_8 maximumWorkers;
};

VehicleRecipe vehicles[1000];

void intializeVehicles() {
//VEHICLES
vehicles[static_cast<int>(Vehicle::WheeledCart)] = {Actions::CartCraft, 21500, {Item::Wheel, Item::Plank, Item::Peg, Item::Nail, Item::Axle},{4,30,60,60,4},{1,2,3,3,4}};
vehicles[static_cast<int>(Vehicle::WheeledWagon)] = {Actions::CartCraft, 50800, {Item::Wheel, Item::Plank, Item::Peg, Item::Nail, Item::LargeAxle, Item::Leather},{4,70,100,100,4},{1,2,3,3,4,5}};
vehicles[static_cast<int>(Vehicle::Canoe)] = {Actions::BoatCraft, 27500, {Item::Log, Item::Plank, Item::Peg, Item::Nail, Item::Axle, Item::Plank}, {1,10,20,20,1,2},{1,0,0,0,2,3}};
vehicles[static_cast<int>(Vehicle::Sailboat)] = {Actions::BoatCraft, 30800, {Item::Timber, Item::Wood, Item::LogBeam, Item::Plank, Item::Nail, Item::Rivet, Item::Sail, Item::Rope}, {8,9,1,18,30,16,3,4}, {1,2,3,4,5,6,7,8}};
vehicles[static_cast<int>(Vehicle::LargeSailboat)] = {Actions::BoatCraft, 58900, {Item::Timber, Item::Beam, Item::LogBeam, Item::Wood, Item::Plank, Item::Nail, Item::Rivet, Item::Sail, Item::Rope}, {20,4,1,40,30,70,30,9,12}, {1,2,3,4,5,6,7,8,9}};
vehicles[static_cast<int>(Vehicle::Longboat)] = {Actions::BoatCraft, 37300, {Item::Log, Item::Wood, Item::Plank, Item::Sail, Item::Rivet, Item::Nail, Item::Rope}, {8,10,8,4,20,10,5}, {1,2,3,4,5,6,7}};
vehicles[static_cast<int>(Vehicle::LightWarship)] = {Actions::BoatCraft, 38300, {Item::Timber, Item::Wood, Item::Beam, Item::LogBeam, Item::Plank, Item::Nail, Item::Rivet, Item::Sail, Item::Rope}, {14,20,4,1,30,50,25,5,8}, {1,2,3,4,5,6,7,8,9}};
vehicles[static_cast<int>(Vehicle::HeavyWarship)] = {Actions::BoatCraft, 78400, {Item::Timber, Item::LogBeam, Item::Beam, Item::Wood, Item::Plank, Item::Nail, Item::Rivet, Item::Sail, Item::Rope}, {40,2,16,30,50,100,50,14,25}, {1,2,3,4,5,6,7,8,9}};
vehicles[static_cast<int>(Vehicle::Cog)] = {Actions::BoatCraft, 36600, {Item::Timber, Item::Wood, Item::Plank, Item::Beam, Item::Nail, Item::Rivet, Item::Sail, Item::Rope, Item::LogBeam}, {10,14,26,4,40,20,5,8,1}, {1,2,3,4,5,6,7,8,9}};
vehicles[static_cast<int>(Vehicle::Freighter)] = {Actions::BoatCraft, 69600, {Item::Timber, Item::LogBeam, Item::Beam, Item::Wood, Item::Plank, Item::Nail, Item::Rivet, Item::Sail, Item::Rope}, {30,2,7,28,35,90,45,12,20},{1,2,3,4,5,6,7,8,9}};
//SIEGE MACHINES
vehicles[static_cast<int>(Tool::BatteringLog)] = {Actions::Saw, 500, {Item::Log}};
vehicles[static_cast<int>(Tool::BatteringRam)] = {Actions::SiegeCraft, 5300, {Item::BatteringLog, Item::Plank, Item::Beam, Item::Nail, Item::CuredHide, Item::Rope, Item::Wheel, Item::Axle}, {1,30,8,60,8,2,4,2}, {1,2,3,4,5,6,7,8}};
vehicles[static_cast<int>(Buildable::Trebuchet)] = {Actions::SiegeCraft, 46800, {Item::LogBeam, Item::Plank, Item::Beam, Item::Nail, Item::Bolt, Item::Gear, Item::CuredHide, Item::Rope, Item::Wheel, Item::LargeAxle}, {1,25,8,70,8,6,6,8,4,2}, {1,2,3,4,5,6,7,8,0,0}};
vehicles[static_cast<int>(Vehicle::Balllista)] = {Actions::SiegeCraft, 29400, {Item::Wood, Item::Beam, Item::Nail,  Item::Trigger, Item::CuredHide, Item::Wheel, Item::Axle}, {15,8,40,1,3,4,2}, {1,2,3,4,5,0,0}};
vehicles[static_cast<int>(Buildable::Catapult)] = {Actions::SiegeCraft, 38000, {Item::LogBeam, Item::Plank, Item::Beam, Item::Nail, Item::Gear, Item::CuredHide, Item::Rope, Item::Wheel, Item::LargeAxle}, {1,18,6,50,4,4,2,4,2}, {1,2,3,4,5,6,7,8,0,0}};
vehicles[static_cast<int>(Tool::SiegeLadder)] = {Actions::Craft, 580, {Item::LargeAxle, Item::Beam}, {2,14}, {1,2}};
vehicles[static_cast<int>(Vehicle::SiegeTower)] = {Actions::SiegeCraft, 12800, {Item::SiegeLadder, Item::Planks, Item::Nail, Item::LargeAxle, Item::Wheel}, {1, 40, 80, 2, 4}, {1,2,3,4,5}};
}
#endif // ITEMRECIPES_H_
