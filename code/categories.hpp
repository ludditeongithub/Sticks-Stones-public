#ifndef CATEGORIES_H_
#define CATEGORIES_H_
#include "basic.hpp"

enum class Tile {
EMPTY, DeepWater,ShallowSaltWater,RiverSource,FlowingWater,ShallowWater,Gravel, FrozenSoil, Snow, Ice, Stone, Ore, GemOre, RockSalt, Sand, Podzol, PlowedPodzol, LoamSoil, PlowedLoamSoil, PeatSoil, PlowedPeatSoil, SandySoil, PlowedSandySoil, ClaySoil, PlowedClaySoil, SiltySoil, PlowedSiltySoil, RockySoil, PlowedRockySoil, AridSoil, Oxisol, PlowedOxisol, Gleysol, Hardpan, Path, DirtRoad, StoneRoad, BrickRoad, PavedRoad, ConcreteRoad, WoodFloor, Carpet, StoneFloor, BrickFloor,  MAX,
};

std::vector<Tile> plowableDirts = { Tile::Podzol, Tile::LoamSoil, Tile::ClaySoil, Tile::SandySoil, Tile::SiltySoil, Tile::Oxisol, Tile::RockySoil };

std::vector<Tile> plowedDirts = { Tile::PlowedPodzol, Tile::PlowedLoamSoil, Tile::PlowedSandySoil, Tile::PlowedClaySoil, Tile::PlowedSiltySoil, Tile::PlowedRockySoil, Tile::PlowedOxisol  };

enum class Animal {
NONE, Pig, Cow, Chicken, Duck, Sheep, Goat, Horse, Ox, Donkey, Camel, WaterBuffalo, Rabbit, Antelope, Deer, Moose, Capybara, Turtle, Elephant, Bison, Wolf, Bear, Caribou, Fish, MAX,
};

Animal grassEaters[] = {Animal::Cow, Animal::Sheep, Animal::Goat, Animal::Rabbit, Animal::Antelope, Animal::Deer, Animal::Caribou};

Animal wolfDiet[] = {Animal::Pig, Animal::Chicken, Animal::Duck, Animal::Sheep, Animal::Goat, Animal::Rabbit, Animal::Antelope, Animal::Deer, Animal::Capybara, Animal::Caribou};
Animal bearDiet[] = {Animal::Pig, Animal::Chicken, Animal::Cow, Animal::Duck, Animal::Sheep, Animal::Goat, Animal::Ox, Animal::WaterBuffalo, Animal::Rabbit, Animal::Antelope, Animal::Deer, Animal::Capybara, Animal::Caribou, Animal::Fish};


enum class Grass {
NONE, EDIBLE, Grass, SavannahGrass,
};

enum class Plant {
NONE, EDIBLE, WOOD, Fern, Moss, Reed, Wheat, Oat, Rice, Bush, Papyrus, PioneerTree, DeciduousTree, EvergreenTree, TropicalTree, OrangeTree, LemonTree, LimeTree, PeachTree, PlumTree, CherryTree, ApricotTree, Cactus, AppleTree, PearTree, OliveTree, BlueberryShrub, StrawberryShrub, Grapevine, Lettuce, Kale, Corn, Carrot, Beets, Potato, Onion, Garlic, Cabbage, Broccoli, Tomato, Cucumber, Pepper, BlackPepper, Cotton, Hemp, Flax, Woad, Madder, Indigo, Lavender, Mint, Thyme, Sage, Ginseng, Rhubarb, Poppy, Cocoa, Senna, Saffron, MAX,
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
HeavySawHead,
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
PermanentHeavySawHeadMould,
HeavySawHeadMould,
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

enum class Fruit {
	NONE,
    //also doubles for juice
    Orange, Apple, Lemon, Pear, Peach, Cherry, Apricot, Plum, Lime,
    //Non-fall fruits
    Blueberry, Strawberry, Grape,
    //FRUIT VEGGIES
    Cucumber, Pepper, Tomato
};

struct FruitObject {
Fruit fruit;
uint8_t amount;
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
  Tribalwear, BasicClothing, FormalClothing, AdvancedClothing, Sandles, Boots, Gloves, Apron, Helmet, Bracers, Guards, Cape, Gambeson, Chainmail, Breastplate, WoodCrown, GoldCrown, RoyalCrown,
};

enum class Jewelry {
  Ring, Necklace, Earring,
};

// actions require a certain job and also a certain tool. For example, "Butcher" requires a knife and also the Butcher job, while "Cut" only requires a knife. Burn needs fire, but not oven, while fire needs a kiln like structure
enum class Actions { NONE, Collect, Hunt, Melee, Ranged, Mine, Cut, Chop, Dig, Light, Butcher, Paint, Sculpt, Chisel, Write, Pott, Smelt, Smith, Perform, Operate, Administer, Build, Command, Mould, Woodwork, Stonework, Glasswork, Saw, Engrave, Burn,Fire,Press,Carve,WoodCarve,StoneCarve,Weave,Bless,PrimitiveCook,Cook,Craft,Explore,Negotiate,Plow,Plant,Weed,Harvest,Milk,Shear,Mill,Fish,Herd,Trade,Haul, Bake, Treat, Cast, Mix, Boil, Whittle, Knapp, Spin, Grind, Preserve, LeatherCraft, Dip, Lay, WoodCraft, WheelCraft, CanoeCarve, BoatCraft, SiegeCraft, Engineer, Lift, Wait, Measure, SculptMould, Sew, Cur, Tan, CandleCast, Ponder, Tabulate, CandleMould,  Mint, Bind, WireDraw, MudbrickSculpt, BrickSculpt, LowFire, Brew, OilMake, Mash,
//TODO: MAY NOT BE IN ACTIONS TO TOOL OR ROLES YET
	Tame, Scrape, Churn, Crush, Leatherwork, Fletch, Compound, Saponify, BowCraft, MAX
};

enum class Tool {
	NONE, CARRYING,
	//SHORT HANDLE TOOLS
Handaxe, Sword, Machete, Knife, Cleaver, Trowel, Chisel, Hammer, Scalpel,  Mallet,  Sickle, Adze, Awl, HandDrill, Graver
	//LONG HANDLE
	,PrimitiveSpear, Spear, Pike, Halberd, Greataxe, Greatsword, Pickaxe, Axe, Shovel, Saw, HeavySaw, Ard, HeavyPlow, Whip, FishingRod, Staff, DiggingStick, Scythe,
//NO HANDLE
Blowpipe, Shears, HandheldBellows,  Pestle, Tongs, Needle, Drum, Torch, Bucket, Basket, Jar, Pot, Plate, Candle, Flint, Brush, Pen, Stylus, Scraper, Crucible, Lyre, Lur, PanFlute, Scroll, Book, PermanentMould, MeasuringTools, Lens, Scale, HandheldLoom, Shuttle, Cheesecloth, Compass, Binocular, SurveyingTools, Net, Stamp, Cart, Wagon, Ladle, Rock, Spindle, Distaff, DryingRack, Abacus, Die, Mould, Incense, Stick, Tame, Mint, CandleMould, MeltingPot, Hammerstone, PatternedDie, Log, Shield, HeavyShield, Corpse
};

enum class Material {
Wood, Stone, Bone, Copper, Bronze, Iron, Steel, Gold, Leather, Silver
};

float weightMultiplier[static_cast<int>(Material::Silver)];

void initializeWeightMultipliers() {
    weightMultiplier[static_cast<int>(Material::Wood)] = 0.7;
    weightMultiplier[static_cast<int>(Material::Bone)] = 0.8;
    weightMultiplier[static_cast<int>(Material::Leather)] = 0.6;
    weightMultiplier[static_cast<int>(Material::Stone)] = 1.4;
    weightMultiplier[static_cast<int>(Material::Copper)] = 3.8;
    weightMultiplier[static_cast<int>(Material::Bronze)] = 3.9;
    weightMultiplier[static_cast<int>(Material::Iron)] = 4.4;
    weightMultiplier[static_cast<int>(Material::Steel)] = 4.45;
    weightMultiplier[static_cast<int>(Material::Silver)] = 5.2;
    weightMultiplier[static_cast<int>(Material::Gold)] = 5.7;
};


Tool oneHandedTools[] = {Tool::Basket, Tool::Jar, Tool::Pot, Tool::Plate,Tool:: Handaxe, Tool::Sword, Tool::Machete, Tool::Trowel, Tool::Torch, Tool::Candle, Tool::Flint, Tool::Knife, Tool::Cleaver, Tool::Brush, Tool::Pen, Tool::Stylus, Tool::Scraper, Tool::Hammer, Tool::Scalpel,  Tool::Sickle,  Tool::Needle, Tool::Mallet, Tool::Scroll, Tool::Book, Tool::Tongs, Tool::HandheldBellows, Tool::Blowpipe, Tool::PermanentMould,  Tool::MeasuringTools, Tool::Graver, Tool::Lens, Tool::Scale, Tool::Shuttle, Tool::Cheesecloth, Tool::Compass, Tool::Binocular, Tool::SurveyingTools, Tool::Chisel, Tool::Whip, Tool::Shears, Tool::Pestle, Tool::FishingRod, Tool::Net, Tool::Staff, Tool::Stamp, Tool::Ladle, Tool::Rock, Tool::Spindle, Tool::Distaff, Tool::DryingRack, Tool::Awl, Tool::Abacus,Tool::HandDrill, Tool::Die, Tool::Mould, Tool::Incense, Tool::Stick,  Tool::CandleMould, Tool::MeltingPot, Tool::Hammerstone, Tool::PatternedDie, Tool::Shield};
// can be used with lower efficiency with one hand
Tool optionalTwoHandedTools[] = { Tool::Basket, Tool::DiggingStick, Tool::Bucket, Tool::PrimitiveSpear, Tool::Spear, Tool::Pickaxe, Tool::Axe,  Tool::Saw, Tool::HeavySaw, Tool::Crucible, Tool::HeavyShield };
// can be lifted with one hand, but must be used with two
Tool TwoHandedTools[] = { Tool::Adze, Tool::Halberd, Tool::Shovel, Tool::Scythe,  Tool::Drum, Tool::Lyre, Tool::PanFlute, Tool::HandheldLoom, };
//must be both used and lifted with two hands, cannot enter any other inventory slot
Tool mandatoryTwoHandedTools[] = { Tool::Greataxe, Tool::Greatsword, Tool::Lur,  Tool::Ard,  Tool::Log, Tool::Corpse, Tool::Cart, Tool::Pike };
Tool unHandleableTools[] = { Tool::HeavyPlow,  Tool::Wagon,};
// Collect requires no items or roles. harvesting is collect but with scythe.
enum class Role {NONE,
;    //MELEE
    //RANGED
    //ARTIST
    Performer, Sculptor, WoodCarver, Musician, Bard, Poet, StoneCarver, Decorator, GlassArtist, Actor, Playwright, Painter, Writer,
    //SUPPORT
    //paleo
    //meso
    //neo
    Plower,
    //copper
    Prostitute, Porter, CombatHealer, Landowner, Trader, ShipCaptain, Sailor,
    //bronze
    Carter, ChariotDriver,
    //iron
    Bureaucrat, ChariotRacer, MoneyLender, Merchant, Gladiator,
    //classical
    Factor, FieldSurgeon, Judge, Lawyer, Teamster, TradeBaron, Veterinarian, Governor, Senator, Mariner, Curer,
    SUPPORTMAX,
    //RESOURCE
    //paleo
    Scavenger,
    //meso
    FishHunter, Woodcutter, Gatherer,
    //neo
    Herder, Shepherd, StoneMiner, Herbalist, Planter,   //farmer is combination of planter and plower
    //copper negotiator put here instead of neo
    CopperMiner, Fisherman, Beekeeper, CerealFarmer, HerbFarmer, Horticulturalist, TextileFarmer, Negotiater,
    //iron, no fishmonger, no rancher, no vineyard worker,
    PapyrusHarvester, IronMiner, OliveGrower, VineyardWorker,
    //classical
    GoldMiner, SaltMiner, SilverMiner, LivestockFarmer, DairyFarmer,
    //medieval
    CottonFarmer, GemstoneMiner,
    OrchardFarmer, HorseBreeder, WoodFarmer,  RESOURCEMAX,
   //PRODUCER
   //paleo: make hidecrafter roles
   Knapper, Carver, Firekeeper, HideCrafter,
   //meso: tanner = hidetanner
   CanoeCarver, BasketWeaver, Crafter,  ShelterBuilder, Tanner, Ornamenter, Mixer,
   //neo
   ClayWorker, Butcher, Preserver, Weaver, Woodworker, Spinner, MudbrickMaker, StoneWorker,
   //copper
   CopperSmelter, Coppersmith, GrainGrinder, BoatBuilder, Bowyer, Fletcher, Leathercrafter, Priest, Brewer,
   //bronze note: no carpnter, no provisioner, no stonemason, no tanner,  wagon maker = wheelwright, no wickerworker, wise man = philosopher
   SilverSmelter, GoldSmelter, Silversmith, Goldsmith, GemCarver,
   Potter, Engineer, Baker, BrickMaker, BronzeSmelter, Bronzesmith, Builder, CharcoalMaker,
 Cook, Cuirassier, Wheelwright, Scribe, Philosopher,
  //iron: no loom weaver,
    IronSmelter, Ironsmith, OilMaker, PaperMaker, Apothecary, Glassworker,
   //classical, no cartwright, no cheesmaker, shipwright = naval engineer, no chef, no philosopher
    Glassblower, Engraver, Minter, Shipwright, SiegeEngineer,
    SteelSmelter,  Steelsmith,  Founder, Surgeon,  Monarch, MilLeader, Miller,  Caretaker, Hauler,  Dyer,  Chandler, Ropemaker, Tailor,  Armorer, PRODUCTSMAX,
   //SUPPORTPRODUCER
   //RESEARCHER
   Envoy, Explorer, Navigator, Spy, Historian, Mathematician, Cartographer, Diplomat,
   //LEADER
   AdvisorFarming, AdvisorForeign, AdvisorNatural, AdvisorKnowledge, AdvisorOrderAdministrative, AdvisorOrderCulturalArtifact, AdvisorOrderCulturalPerformer, AdvisorOrderLegal, AdvisorStructures, AdvisorTrade,
   Chieftan, Prince, Architect, King, Emperor, Moneyer, CivilEngineer, Aristocrat, MiningEngineer, WagonMaster, Baron,
   MAX};

//Consumes items:: operate, administer, write, bless, plan

// if a task has to be peformed on a specific object, or at a specific tile
enum class Station {
	PottersWheel, Animal, ClaySculpture, Plant, Tree, Pawn, Wall, Furnace, Bellows, TemporaryMould, Press, Mill, Loom, Oven, Tabletop, PitFire, SpinningWheel, Smokehouse, Kiln, WaterWheel, Hive, Forge, Cart, Wagon, MashTun, Keg, Anvil, SculptMould, FirePit, Spinner,

	//Corpses
	PigCorpse, CowCorpse, ChickenCorpse, DuckCorpse, SheepCorpse, GoatCorpse, OxCorpse, HorseCorpse, DonkeyCorpse, CamelCorpse, WaterBuffaloCorpse, RabbitCorpse, AntelopeCorpse, DeerCorpse, MooseCorpse, CapybaraCorpse, ElephantCorpse, BisonCorpse, WolfCorpse, BearCorpse, CaribouCorpse,
};

enum class Scavengeable {
NONE, Log, Pebble, LargeStick, Stick, Rock, LargeRock, Boulder, Flint, Ore, Corpse, Beehive, ArtificialBeehive, Stump, ChickenEgg, DuckEgg, TurtleEgg, Truffle
};

enum class ItemType {
Item, Vehicle, Buildable, Tool, Container
};

//ARRAY CATEGORIES / SUB - CATEGORIES
using Object = std::variant<Plant, Container, Item, Scavengeable, Buildable, Fruit, Tool>;

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

//TODO: animal diet categories

#endif // CATEGORIES_H_
