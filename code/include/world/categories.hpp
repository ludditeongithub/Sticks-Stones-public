#ifndef CATEGORIES_H_
#define CATEGORIES_H_
#include "basic.hpp"

enum class SoftMaterial {
Leather, Linen, Cloth, Silk
};

enum class HardMaterial {
Wood, Stone, Bone, Copper, Bronze, Iron, Steel, Gold, Leather, Silver
};

using Material = std::variant<SoftMaterial, HardMaterial>;

enum class Quality {
Terrible, Poor, Average, Good, Great, Stellar, Legendary
};

enum class BodyArea {
Head, Face, Neck, Chest, LeftShoulder, RightShoulder, LeftArm, RightArm, LeftLeg, RightLeg, LeftHand, RightHand, LeftFoot, RightFoot,
};


enum class Tile {
EMPTY, DeepWater,ShallowSaltWater,RiverSource,FlowingWater,ShallowWater,Gravel, FrozenSoil, Snow, Ice, Stone, Ore, GemOre, RockSalt, Sand, Podzol, PlowedPodzol, LoamSoil, PlowedLoamSoil, PeatSoil, PlowedPeatSoil, SandySoil, PlowedSandySoil, ClaySoil, PlowedClaySoil, SiltySoil, PlowedSiltySoil, RockySoil, PlowedRockySoil, AridSoil, Oxisol, PlowedOxisol, Gleysol, Hardpan, Path, DirtRoad, StoneRoad, BrickRoad, PavedRoad, ConcreteRoad, WoodFloor, Carpet, StoneFloor, BrickFloor,  MAX,
};

std::vector<Tile> plowableDirts = { Tile::Podzol, Tile::LoamSoil, Tile::ClaySoil, Tile::SandySoil, Tile::SiltySoil, Tile::Oxisol, Tile::RockySoil };

std::vector<Tile> plowedDirts = { Tile::PlowedPodzol, Tile::PlowedLoamSoil, Tile::PlowedSandySoil, Tile::PlowedClaySoil, Tile::PlowedSiltySoil, Tile::PlowedRockySoil, Tile::PlowedOxisol  };



enum class Grass {
NONE, EDIBLE, Grass, SavannahGrass,
};


enum class Wall {
NONE, TentSticks, Wattle, Cob, Wood, Stone, Brick, Log, Fence, Gate, Bronze, Iron, Steel, Pillar, Door, CityGate, MAX
};

enum class Roof {
TentCover, Wattle, Cob, Wood, Beams, StoneSlab, ClayTiled, MAX
};

// TODO: move all tool head to variant items, then also figure out how ore and metal work
enum class Item {
NONE,
//VARIANT ITEMS
Log,
Fruit,
Seed,
Juice,
AlcoholicDrink,
AgedAlcoholicDrink,
Metal,
Corpse,
Gem,
GreaterGem,
Ore,
CuredHide,
TannedHide,
RawMeat,
CookedMeat,
CandiedFruit,
Gambeson,
Breastplate,
Helmet,
Bracers,
Guards,
Gloves,
VARIANTSMAX,
//RESOURCES
Saltwater,
Rock,
Pebble,
LargeRock,
Boulder,
Stick,
LargeStick,
LoamSoil,
SiltySoil,
SandySoil,
ClaySoil,
Podzol,
PeatSoil,
RockySoil,
Oxisol,
Stone,
Flint,
Gravel,
FruitPit,
ArsenicOre,
Milk,
GoatMilk,
CamelMilk,
ChickenEgg,
DuckEgg,
TurtleEgg,
Fish,
Shellfish,
Honey,
RawWax,
Wax,
Resin,
Wool,
RawSalt,
Olive,
Sugarcane,
Coconut,
Truffle,
Wheat, Oat, Corn, Rice, Tomato, Onion, Potato, Cabbage, Pumpkin, Pepper, Carrot, Poppy, Cannabis, Senna, Cotton, Papyrus, Flax, Hemp, Lettuce, Cocoa, Cucumber, Kale, Beets, Madder, Indigo, Saffron, Ginseng, Garlic, Sage,
//TODO: add to resources
Mint,	Thyme, Syrup, Lavender, TreeResin, Rhubarb,
RESOURCESMAX,
//RESOURCES/PRODUCTS BEGIN HERE
SaltWater,
Water,
Sand,
Clay,
BOTHMAX,
//PRODUCTS BEGIN HERE
//paleo:
PitFire,
Tribalwear,
Torch,
HandAxe,
StickSpear,
Hammerstone,
HandKnife,
HandDrill,
HandChisel,
Ash,
Straw,
Hay,
Soot,
Fiber,
AnimalHides,
Feather,
AnimalHair,
Bone,
Sinew,
Peat,
Salt,
DrinkingWater,
AnimalFat,
//meso:
PrimitiveChair,
PrimitiveStool,
LargeSatchel,
Satchel,
Javelin,
SmoothedPebbles,
Earring,
Ring,
Necklace,
WoodCrown,
Sling,
PrimitiveRope,
PrimitiveString,
LargeHandle,
SmallHandle,
BoneArtifact,
PrimitiveAxe,
PrimitiveAxeHead,
PrimitiveSpear,
PrimitiveSpearHead,
DiggingStick,
Thread,
Arrowhead,
SolidWheel,
Strap,
PackedEarth,
PrimitiveArrow,
PrimitiveBow,
Basket,
Waterskin,

//neo:
String,
BackstrapLoom,
ClayJar,
ClayPot,
ClayBowl,
Whip,
Fertilizer,
FishMeal,
BoneMeal,
Daub,
WheatGrain,
Cloth,
Silk,
Linen,
Charcoal,
Cob,
Wood,
LogBeam,
Beam,
Timber,
Plank,
Cheese,
GoatCheese,
Butter,
Flour,
Sugar,
Grist,
MilledRice,
WoodArtifact,
//copper:
Arrow,
Shortbow,
ArrowShaft,
AxeHead,
ShovelHead,
SawHead,
ArdHead,
ScytheHead,
HandaxeHead,
SwordHead,
MacheteHead,
CleaverHead,
TrowelHead,
ChiselHead,
HammerHead,
ScalpelHead,
MalletHead,
AdzeHead,
AwlHead,
SickleHead,
KnifeHead,
StoneTablet,
FiredClay,
Pot,
Kettle,
Jar,
Bowl,
OilLamp,
Incense,
BrickMold,
Rivet,
Socket,
Wedge,
Peg,
Nail,
LargeAxle,
Axle,
Glue,
TanningAgent,
HeavyTannedHides,
Mortar,
Plaster,
SugarJuice,
Mead,
FruitWine,
Wine,
Beer,
TemporaryTablet,
Carpet,
Rug, //TODO: item specifications
JoinedPlank,
CurvedStone,
CutStoneSheet,
CutStone,
CrushedStone,
JoinedBeam,
LongStave,
Stave,
Bread,
CornOil,
CookingOil,
OliveOil,
BlueCheese,
Porridge,
//bronze:
Blowpipe,
StoneArtifact,
Bleach,
YellowDye,
BlueDye,
RedDye,
HandheldBellows,
Chair,
Stool,
ArtificialBeehive,
Keg,
Bottle,
Scroll,
Horseshoes,
OxSaddle,
HorseSaddle,
GoldCrown,
FancyClothes,
FormalClothes,
Sword,
PermanentSpearHeadMould,
SpearHeadMould,
PermanentPickaxeHeadMould,
PickaxeHeadMould,
PermanentAxeHeadMould,
AxeHeadMould,
PermanentShovelHeadMould,
ShovelHeadMould,
PermanentSawHeadMould,
SawHeadMould,
PermanentArdHeadMould,
ArdHeadMould,
PermanentScytheHeadMould,
ScytheHeadMould,
PermanentHandaxeHeadMould,
HandaxeHeadMould,
PermanentSwordHeadMould,
SwordHeadMould,
PermanentMacheteHeadMould,
MacheteHeadMould,
PermanentCleaverHeadMould,
CleaverHeadMould,
PermanentTrowelHeadMould,
TrowelHeadMould,
PermanentChiselHeadMould,
ChiselHeadMould,
PermanentHammerHeadMould,
HammerHeadMould,
ScalpelHeadMould,
PermanentScalpelHeadMould,
MalletHeadMould,
PermanentMalletHeadMould,
AdzeHeadMould,
PermanentAdzeHeadMould,
AwlHeadMould,
PermanentAwlHeadMould,
SickleHeadMould,
PermanentSickleHeadMould,
PermanentKnifeHeadMould,
KnifeHeadMould,
Poison,
Cyanide,
Arsenic,
Hemlock,
Bandage,
Laxative,
MedicinalSoap,
GileadBalm,
Theriac,
MetalArrowhead,
Tube,
Sail,
Wheel,
Needles,
Clips,
Paper,
Ink,
DyedCloth,
Rope,
RopemakingFrame,
Bricks,
Lime,
GroundBlackPepper,
ChiliPowder,
TruffleOil,
Vinegar,
Pastry,
//iron:
Airbag,
FloorLoom,
Loom,
Tabletop,
Bucket,
Crucible,
MashTun,   //size
Book,
BasicClothes,
Axe,
Spear,
Bow,
SpearHead,
PickaxeHead,
Die,
Tonic,
Elactuarium,
Trigger,
Gear,
Wick,
NailHeader,
Glass,
Soap,
ColoredPane,
Pane,
Concrete,
Pie,
//classical
GreatswordHead,
Coins,
CoinBlank,
Lens,
CoinMould,
Wire,
//mediev
Pulley,
Waterwheel,
Candle,
Chainmail,
EmperorsStaff,
RoyalCrown,
Pike,
Halberd,
Greataxe,
Longbow,
Crossbow,
PermanentPikeHeadMould,
PikeHeadMould,
PikeHead,
PermanentHalberdHeadMould,
HalberdHeadMould,
HalberdHead,
PermanentGreataxeHeadMould,
GreataxeHeadMould,
GreataxeHead,
PermanentGreatswordHeadMould,
GreatswordHeadMould,
MAX
};

enum class Buildable {
NONE,
TentSticks,
WattleWall,
Wall, // variants
WallPanel,
Fence,
Gate,
Pillar,
CityGate,

TentCover,
WattleRoof,
RoofBeams,
Roof,

Foundation,
Floor,
Carpet,
PlowedDirt,
Path,
StoneRoad,
BrickRoad,
ConcreteRoad,

DugCanal,
Canal,
Well,
Siphon,
BucketPump,
SuctionPump,
HydraulicPump,
Aqueduct,

VerticalLoom,
FloorLoom,
PottersWheel,
Anvil,
PitKiln,
EarthMoundKiln, //small, medium, large variants
PitFurnace,
AdvancedPitFurnace,
BloomeryFurnace,
Forge,
Bellows,
DoubleBellows,
WaterPoweredBellows,
MAX
};

enum class Vehicle {
NONE,
WheeledCart,
WheeledWagon,
WheeledChariot,
Canoe,
Sailboat,
LargeSailboat,
Longboat,
LightWarship,
HeavyWarship,
Cog,
Freighter,

BatteringLog,
BatteringRam,
Trebuchet,
Ballista,
Catapult,
SiegeLadder,
SiegeTower,
MAX
};

enum class Container {
NONE,
Bucket,
Pot,
LargePot,
Kettle,
Jar,
Keg,
Basket,
MashTun,
Crucible,
//ITEMS TO ADD
Chest,
Satchel,
Waterskin,
MAX
};

enum class ResourceType {
NONE, Plant, Fruit, Wood,
};

enum class Meat {
Pork, Beef, Chicken, Duck, Sheep, Goat, Ox, Horse, Donkey, Camel, WaterBuffalo, Rabbit, Antelope, Deer, Moose, Capybara, Elephant, Bison, Wolf, Bear, Caribou,
};

enum class Hide {
NONE, PigSkin, CowHide, OxHide, SheepHide, GoatHide, HorseSkin, DonkeySkin, WaterBuffaloHide, RabbitHide, AntelopeHide, DeerHide, MooseHide, CapybaraHide, ElephantHide, BisonHide, WolfPelt,
};

struct ItemObject {
Item item;
uint8_t amount;
};

enum class AlcoholicDrink {
    Brandy, Wine, Beer, Cider, Mead,
};

enum class ToolheadMould {
    Handaxe, Sword, Pike, Machete, Pickaxe, Axe, Shovel, Trowel, Knife, Cleaver, Chisel, Scraper, Hammer, Mallet,
};

enum class MeleeWeapon {
    Rock, PrimitiveSpear, PrimitiveAxe, Javelin, HandAxe, Knife, Machete, Hammer, Spear, Sword, Axe, Halberd, Pike, Greatsword, Greataxe,
};

enum class RangedWeapon {
    Slingstone, Rock, Sling, Javelin, Bow, Crossbow, Longbow,
};

enum class SmallHandle {
    Knife, Trowel, Handaxe, Machete, Cleaver, Chisel, Mallet, Scraper, Sword, Greatsword,
};

enum class LargeHandle {
    Axe, Shovel, Spear, Pike, Machete, Pickaxe, Hammer, Halberd, Greataxe,
};

enum class Clothing {
  PartTribalwear, Tribalwear, Robe, Tunic, Pants, Dress, Sandles, Boots, Scarf, Headwrap, Mitts, Shoes, Gloves, Apron, Helmet, Bracers, Guards, Cape, HeavyShirt, HeavyPants, Gambeson, Chainmail, Breastplate, HalfPlate, Plate, WoodCrown, GoldCrown, RoyalCrown,
};

enum class Jewelry {
  Ring, Necklace, Earring,
};


//if weapon is both weapon and tool, tool takes priority over weapon (cast doubled values from tool)
enum class Weapon {
NONE, CARRYING,
//SHORT HANDLE WEAPONS
Handaxe, Sword, Machete, Knife, Cleaver, Chisel, Hammer, PrimitiveSpear, Spear,
//LONG HANDLE
	Pike, Halberd, Greataxe, Greatsword, Axe, Whip,
};

enum class Tool {
	NONE, CARRYING,
	//SHORT HANDLE TOOLS
Handaxe, Machete, Knife, Cleaver, Trowel, Chisel, Hammer, Scalpel,  Mallet,  Sickle, Adze, Awl,  Graver,
	//LONG HANDLE
 Pickaxe, Axe, Shovel, Saw,  Ard, HeavyPlow, Whip, FishingRod, Staff, DiggingStick, Scythe,
//NO HANDLE
Blowpipe, Shears, HandheldBellows,  Pestle, Needle, Drum, Torch, Bucket, Basket, Jar, Pot, Plate, Candle, Flint, Brush, Pen, Stylus, Scraper, Crucible, Lyre, Lur, PanFlute, Scroll, Book, PermanentMould, MeasuringTools, Lens, Scale, HandheldLoom, Shuttle, Cheesecloth, Compass, Binocular, SurveyingTools, Net, Stamp, Cart, Wagon, Ladle, Rock, Spindle, Distaff, DryingRack, Abacus, Die, Mould, Incense, Stick, Tame, Mint, CandleMould, MeltingPot, Hammerstone, PatternedDie, Log, Shield, HeavyShield, Corpse
};

Tool oneHandedTools[] = {Tool::Basket, Tool::Jar, Tool::Pot, Tool::Plate,Tool:: Handaxe,  Tool::Machete, Tool::Trowel, Tool::Torch, Tool::Candle, Tool::Flint, Tool::Knife, Tool::Cleaver, Tool::Brush, Tool::Pen, Tool::Stylus, Tool::Scraper, Tool::Hammer, Tool::Scalpel,  Tool::Sickle,  Tool::Needle, Tool::Mallet, Tool::Scroll, Tool::Book, Tool::HandheldBellows, Tool::Blowpipe, Tool::PermanentMould,  Tool::MeasuringTools, Tool::Graver, Tool::Lens, Tool::Scale, Tool::Shuttle, Tool::Cheesecloth, Tool::Compass, Tool::Binocular, Tool::SurveyingTools, Tool::Chisel, Tool::Whip, Tool::Shears, Tool::Pestle, Tool::FishingRod, Tool::Net, Tool::Staff, Tool::Stamp, Tool::Ladle, Tool::Rock, Tool::Spindle, Tool::Distaff, Tool::DryingRack, Tool::Awl, Tool::Abacus, Tool::Die, Tool::Mould, Tool::Incense, Tool::Stick,  Tool::CandleMould, Tool::MeltingPot, Tool::Hammerstone, Tool::PatternedDie, Tool::Shield};
// can be used with lower efficiency with one hand
Tool optionalTwoHandedTools[] = { Tool::Basket, Tool::DiggingStick, Tool::Bucket, Tool::Pickaxe, Tool::Axe,  Tool::Saw, Tool::Crucible, Tool::HeavyShield };
// can be lifted with one hand, but must be used with two
Tool TwoHandedTools[] = { Tool::Adze, Tool::Shovel, Tool::Scythe,  Tool::Drum, Tool::Lyre, Tool::PanFlute, Tool::HandheldLoom, };
//must be both used and lifted with two hands, cannot enter any other inventory slot
Tool mandatoryTwoHandedTools[] = { Tool::Lur,  Tool::Ard,  Tool::Log, Tool::Corpse, Tool::Cart };
Tool unHandleableTools[] = { Tool::HeavyPlow,  Tool::Wagon,};


// Collect requires no items or roles. harvesting is collect but with scythe.

//Consumes items:: operate, administer, write, bless, plan

// if a task has to be peformed on a specific object, or at a specific tile
enum class Station {
	PottersWheel, Animal, ClaySculpture, Plant, Tree, Pawn, Wall, Furnace, Bellows, TemporaryMould, Press, Mill, Loom, Oven, Tabletop, PitFire, SpinningWheel, Smokehouse, Kiln, WaterWheel, Hive, Forge, Cart, Wagon, MashTun, Keg, Anvil, SculptMould, FirePit, Spinner,

	//Corpses
	PigCorpse, CowCorpse, ChickenCorpse, DuckCorpse, SheepCorpse, GoatCorpse, OxCorpse, HorseCorpse, DonkeyCorpse, CamelCorpse, WaterBuffaloCorpse, RabbitCorpse, AntelopeCorpse, DeerCorpse, MooseCorpse, CapybaraCorpse, ElephantCorpse, BisonCorpse, WolfCorpse, BearCorpse, CaribouCorpse,
};


enum class ItemType {
Item, Vehicle, Buildable, Tool, Container
};

//ARRAY CATEGORIES / SUB - CATEGORIES
using Object = std::variant<Plant, Container, Item, Scavengeable, Buildable, Fruit, Tool>;

enum class ObjectType {
NONE, Plant, Container, Item, Scavengeable, Buildable, Fruit, Tool
};

bool isPlant(Object obj) {
    return std::holds_alternative<Plant>(obj);
}

bool isItem(Object obj) {
    return std::holds_alternative<Item>(obj);
}

bool isScavengeable(Object obj) {
    return std::holds_alternative<Scavengeable>(obj);
}

bool isFruit(Object obj) {
    return std::holds_alternative<Fruit>(obj);
}

bool isTool(Object obj) {
    return std::holds_alternative<Tool>(obj);
}

using ScavengeableVariant = std::variant<Scavengeable, Plant, Fruit>;

enum class FoodSource {
Grass, Fruit, Plant, Corpse, Meal
};

std::vector<Plant> woodTrees = {Plant::PioneerTree, Plant::DeciduousTree, Plant::EvergreenTree, Plant::TropicalTree};

std::vector<ScavengeableVariant> nonScavengeables = {Plant::Fern, Plant::Moss, Plant::Reed, Plant::Cactus, Scavengeable::Log, Scavengeable::Boulder, Scavengeable::LargeRock, Scavengeable::Corpse};

std::vector<ScavengeableVariant> digScavengeables =
	{ Plant::Potato, Plant::Carrot, Plant::Beets, Plant::Onion, Plant::Garlic };

std::vector<Plant> grains = {
	Plant::Rice, Plant::Wheat, Plant::Oat,
};

std::vector<Plant> herbs = {
	Plant::Flax, Plant::Poppy, Plant::Senna
};

std::vector<Plant> vegetables = {
	Plant::Tomato, Plant::Pepper, Plant::Kale, Plant::Lettuce, Plant::Corn, Plant::Carrot, Plant::Beets, Plant::Onion, Plant::Garlic, Plant::Cabbage, Plant::Broccoli, Plant::Cucumber,
};

std::vector<Plant> fruits = {
	Plant::OrangeTree, Plant::LemonTree, Plant::LimeTree, Plant::PeachTree, Plant::PlumTree, Plant::CherryTree, Plant::ApricotTree, Plant::AppleTree, Plant::PearTree, Plant:: BlueberryShrub, Plant::StrawberryShrub,
};

std::vector<Plant> textiles = { Plant::Cotton, Plant::Hemp, Plant::Flax };

vector<Plant> plantRoleMap(Role role) {
	switch (role) {
		case Role::CerealFarmer:
			return grains;
		case Role::TextileFarmer:
			return textiles;
		case Role::HerbFarmer:
			return herbs;
		case Role::Horticulturalist:
			return vegetables;
		case Role::OrchardFarmer:
			return fruits;
		case Role::VineyardWorker:
		    return {Plant::Grapevine};
		case Role::OliveGrower:
			return {Plant::OliveTree};
		case Role::WoodFarmer:
			return woodTrees;
		default:
			return {};
		}
	return {};
}

std::vector<Animal> shepherdables = {Animal::Sheep, Animal::Goat, Animal::Caribou,};
std::vector<Animal> herdables = {Animal::Cow, Animal::Pig, Animal::Camel, Animal::WaterBuffalo};
std::vector<Animal> draft = {Animal::Donkey, Animal::Ox, Animal::WaterBuffalo};
std::vector<Animal> poultry = {Animal::Duck, Animal::Chicken};

int objectToInt(Object object) {
    return std::visit([](auto&& arg) -> int {
        using T = std::decay_t<decltype(arg)>;
        return static_cast<std::underlying_type_t<T>>(arg);
    }, object);
}

enum class MovingStatus {
Idle,
Wander,
Prowl, // looking for targets, but don't know where
Flee,
//PursuitX means sprinting to visible target
Pursuit,
AnimalPursuit,
// ApproachX means walking to known/visible target
ApproachPlant,
ApproachGrass,
ReturnHome,
};

enum class MatingStatus {
  Idle,
  Searching,
  Pregnant, // equivalent of fertilized for egg layers
  Infertile
};

enum class Diet {
Herbivore, Omnivore, Carnivore, Scavenger
};


//TODO: animal diet categories



#endif // CATEGORIES_H_

