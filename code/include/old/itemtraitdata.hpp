#ifndef DATA_H_
#define DATA_H_

/* REMINDER
 * In product lists, leave 0 empty, to be able to reference nothing! */
/* DESCRIPTION
 *
 * Items are stored in separate enums and arrays based on their subtype (resources, products,
 * equippables, placeables), but these are often sorted into a multiplier hash function. +0:
 * Resources +1: Products +2: Equippables +3: Placeables lt = linked to i = int a = array f = float
 * b = bool
 * */
/* ITEM TRAITS */
enum ItemTraits
{
	// linked arays are small int arrays
	RequiresHarvest,     // if the item cannot just be picked up
	CanHarvest,	     // whether item itself can harvest others, lta blockType/resourceType
	CanProduce,	     // whether item itself produces others, lta productType
	Cookable,	     // lta cookQuality
	Edible,		     // lta mealQuality
	Equippable,	     // linked to array unitType
	EquippableByAnimals, // linked to array animalType
	Grows,		     // lti rate
	Heals,		     // lti amt
	Moves,		     // lti spd
	Placeable,	     // if the item is a structure
};

enum NumItemTraits
{
	AmtMadeOf, // creates array itemType
	Size,	   // ltf
	Weight,	   // ltf
	Beauty,	   // ltf
};

enum class PlaceableItemTraits
{
	SupportsRoof, // links to int, higher int means heavier roof, 0 for none
	Floor,
	Transport,
	Holds,		 // links to array itemType
	SecondDimension, // links to int which is its length
	Durability,	 // ltf
};
enum class EquippableItemTraits
{
	Armor,	  // Whether it's armor
	Ammo,	  // Whether it's ammo
	Tool,	  // Whether it's a tool
	Weapon,	  // Whether it's a weapon
	Strength, // ltf
};

/* ITEM TRAIT SETS */

// using BTraitSet = std::array<bool, NUM_BTRAITS>;
// using NTraitSet = std::array<uint8_t, NUM_NTRAITS>;

// Resources
//  const BTraitSet Crops =
//  {1,0,1,0,0,0,0,1,0,0,1};
//  const BTraitSet AnimalProducts =
//  {0,0,0,1,0,0,0,0,0,0,0};
//  const BTraitSet Animals =
//  {1,0,1,0,0,0,0,1,0,1,0};
//  const BTraitSet Surface =
//  {0,0,0,0,0,0,0,1,0,0,0};
//  const BTraitSet EarthMaterials =
//  {1,0,0,0,0,0,0,0,0,0,0};
//  // Products
//  const BTraitSet Ingredients =
//  {0,0,0,1,1,0,0,0,0,0,0};
//  const BTraitSet Consumables =
//  {0,0,0,0,1,1,0,0,1,0,0};

// for inventory management, units have array storing ints which map to the index of the enum
// classes, and then the same index of a second array is the index of the item within that enum
// class

enum class AnimalProducts
{
	Corpses,
	Milk,
	GoatMilk,
	Eggs,
	Fish,
	Honey,
	Wax,
	Wool,
};

enum class Animals
{
	Ox,
	Horse,
	Cow,
	Chicken,
	Pig,
	Sheep,
	Goat,
	Duck,
	Deer,
	Boar,
	Bear,
	Wolf,
	Dog,
	Cat,
};

enum class Surface
{
	Water,
	Tree,
	Log,
	Pebble,
	Rock,
	LargeRock,
	Boulder,
	Bitumen,
	Sand,
	Clay,
};

enum class EarthMaterials
{
	Dirt,
	Stone,
	Flint,
	Marble,
	Limestone,
	CopperOre,
	TinOre,
	IronOre,
	GoldOre,
	SilverOre,
	Salt,
	Ruby,
	Emerald,
	Diamond,
	Sapphire,
	Amethyst,
	Garnet,
	Topaz,
};

enum class Ingredients
{
	Flour,
	Grist,
	Oat,
	AnimalFat,
	Bread,
	Pastry,
	Pie,
	Porridge,
	MilledRice,
	Fish,
	RawBeef,
	RawChicken,
	RawPork,
	RawLamb,
	RawGoat,
	RawOx,
	RawDuck,
	RawVenison,
	Eggs,
	Milk,
	GoatMilk,
	Honey,
	GoatCheese,
	BlueCheese,
	Corn,
	Tomato,
	Onion,
	Potato,
	Cabbage,
	Olive,
	Pepper,
	Apple,
	Fig,
	Pear,
	Grape,
	Vinegar,
	Butter,
	OliveOil,
	VegetableOil,
	TruffleOil,
	Pea,
	Carrot,
	DrinkingWater,
	CornOil,
	Garlic,
	Beer,
	Cider,
	Juice,
	Cheese,
	Mead,
	Wine,
	Shellfish,
	CandiedFruit,
	AgedWine,
	Peacock,
	ChiliPowder,
	GroundBlackPepper,
	Sugar,
	Salt,
	Oils,
	Drinks,
};

enum class BaseMaterials
{
	Copper,
	Bronze,
	Iron,
	Gold,
	Silver,
	Steel,
	Wood,
	Planks,
	Beams,
	Log,
	LogBeam,
	CutStone,
	CutStoneSheet,
	CutMarble,
	Lime,
	PavingStone,
	Concrete,
	Pane,
	ColoredPane,
	Cob,
	FiredClay,
	Bricks,
	Charcoal,
	Sinew,
	Bone,
	AnimalHair,
	Feather,
	AnimalHides,
	Linen,
	Silk,
	Cloth,
	Wool,
	Rope,
	Fiber,
	Soot,
	Hay,
	WheatGrain,
	CuredHides,
};

enum class CraftingItems
{
	Clips,
	SpearHeadMold,
	AxeHeadMold,
	SmallBladeMold,
	LargeBladeMold,
	GreataxeHeadMold,
	HalberdHeadMold,
	PikeHeadMold,
	MalletHeadMold,
	ChiselHeadMold,
	GraverHeadMold,
	ArdHeadMold,
	ScytheHeadMold,
	HoeHeadMold,
	PickHeadMold,
	CutterHeadMold,
	SawHeadMold,
	CircularSawpieceMold,
	TriggerMold,
	GearMold,
	Needles,
	Lens,
	Wick,
	Glue,
	Resin,
	PrimitiveString,
	String,
	Axle,
	LargeAxle,
	Gear,
	Wheel,
	Nails,
	Peg,
	Wedge,
	Socket,
	Rivet,
	MalletHead,
	ChiselHead,
	GraverHead,
	ArdHead,
	ScytheHead,
	HoeHead,
	PickHead,
	CutterHead,
	SawHead,
	SpadeHead,
	ShovelHead,
	CircularSawpiece,
	BrickMold,
	Handle,
	Arrowhead,
	SpearHead,
	AxeHead,
	SmallBlade,
	LargeBlade,
	GreataxeHead,
	HalberdHead,
	PikeHead,
	Trigger,
	Notch,
	Thread,
	RedDye,
	BlueDye,
	YellowDye,
	Bleach,
	Ink,
	Incense,
	StoneTablet,
	Papyrus,
};

enum class Substances
{
	Bone,
	Wood,
	Stone,
	Leather,
	Cloth,
	Linen,
	Glass,
	Clay,
	Cob,
	Copper,
	Bronze,
	Iron,
	Steel,
	Silver,
	Gold,
	LesserGem,
	GreaterGem,
	Papyrus,
	Parchment,
};

enum class HealthItems
{
	WeakPainkiller,
	Painkiller,
	PrimitiveMedicine,
	Theriac,
	GileadBalm,
	Elactuarium,
	MedicinalSoap,
	Laxative,
	Tonic,
	Bandage,
	Hemlock,
	Arsenic,
	Cyanide,
};

enum class Weapons
{
	Sling,
	Shortbow,
	Bow,
	Crossbow,
	Longbow,
	Spear,
	Axe,
	Sword,
	Greataxe,
	Halberd,
	Pike,
};

enum class Tools
{
	Knife,
	Mallet,
	Chisel,
	Graver,
	Cutters,
	Pestle,
	Distaff,
	Saw,
	Shovel,
	Blowpipe,
	Tongs,
	Cheesecloth,
	Die,
	Stamp,
	OfficialStamp,
	Spindle,
	Dies,
	Basket,
	Ard,
	Scythe,
	Hoe,
	Pick,
	Spade,
	HeavyPlow,
	Shears,
	Stylus,
	ReedPen,
	QuillPen,
	Brush,
	Drum,
	Lur,
	Lyre,
	PanFlute,
	Compass,
	Binocular,
	Scale,
	Abacus,
	MeasuringTools,
	SurveyingTools,
	DiplomaticLetter,
};

enum class Clothes
{
	BasicClothes,
	FormalClothes,
	FancyClothes,
	WoodCrown,
	GoldCrown,
	RoyalCrown,
	EmperorsStaff,
	Necklace,
	Ring,
	Earring,
};

enum class Armor
{
	Gambeson,
	Chainmail,
	Helmet,
	Breastplate,
	Guards,
};

enum class Ammo
{
	SmoothedPebbles,
	Javelin,
	Arrow,
};

enum class OtherEquippables
{
	HorseSaddle,
	OxSaddle,
	Whip,
	Horseshoes,
	Books,
	OilLamp,
	Candle,
};

enum class Walls
{
	TentSticks,
	WattleWalls,
	CobWalls,
	WoodWall,
	StoneWall,
	BrickWall,
	LogWall,
	Fence,
	Gate,
	BronzeReinforcedWall,
	IronReinforcedWall,
	SteelReinforcedWall,
	Pillar,
	CityGate
};

enum class Roofs
{
	TentCover,
	WattleRoof,
	RoofBeams,
	CobRoof,
	WoodRoof,
	StoneSlabRoof,
	ClayTiledRoof,
};

enum class Floors
{
	Foundation,
	WoodFloor,
	Carpet,
	StoneFloor,
	BrickFloor,
	DirtFloor,
	PlowedDirt,
	Path,
	Road,
};

enum class Transport
{
	SaddledHorse,
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
};

enum class Containers
{
	MashTun,
	Pot,
	Kettle,
	Jar,
	Crucible,
	Bucket,
};

enum class Stations
{
	Tabletop,
	Stool,
	Chair,
	Waterwheel,
	Pulley,
	SpinningWheel,
	BackstrapLoom,
	SimpleLoom,
	VerticalLoom,
	CircularSaw,
	PottersWheel,
	Anvil,
	CharcoalKiln,
	Furnace,
	BloomeryFurnace,
	Forge,
	Bellows,
	DoubleBellows,
	WaterPoweredBellows,
	Siphon,
	Pump,
	Aqueduct,
};

enum class Siege
{
	BatteringLog,
	BatteringRam,
	Trebuchet,
	Ballista,
	Catapult,
	SiegeLadder,
	SiegeTower,
};

enum class AnimalProductTraits
{ // f
	Weight,
	Size,
	Edible
};

enum class AnimalTraits
{ // f
	GrowthRate,
	FullyGrown,
	Produces, // 0.0 if nothing
	Consumes,
	ConsumptionAmount,
	MoveSpeed,
	Mountable,
};

enum class SurfaceTraits
{ // f
	Weight,
	Size,
};

enum class EarthMaterialTraits
{
	StoneWaste
};

enum class IngredientTraits
{		 // i
	Quality, // cheap = 0, average = 1, expensive = 2, delicacy = 3
	Filling,
	Type,  // food = 0, drink = 1, oil = 2
	Taste, // savory = 0, sweet = 1, sour = 2, bitter = 3, spicy = 4
	Expiration,
};

enum class SubstanceTraits
{
	BeautyMultiplier,
	DurabilityMultiplier,
};

enum class BaseMaterialTraits
{ // i
	Durability,
	Substance,
};

enum class CraftingMaterialTraits
{
};

enum class HealthItemTraits
{		 // i
	Healing, // negative for poisons
	Curing,	 // diseases/symptoms it cures
	PainRelief,
	Humor, // 0 = Phlegm, 1 = Yellow Bile, 2 = BB, 3 = Blood
};

enum class WeaponTraits
{ // f
	Damage,
	SwingSpeed,
	Range,
	Pierce,
	AmmoRequired, // 0 if nothing
	ShieldBreaker,
};

enum class ToolTraits
{ // f
	// list of harvestable
	// list of producable
	// list of equipable by
	Durability,
};

enum class ArmorTraits
{
	Protection,
	Durability,
	Covers,
};

enum class ClothesTraits
{ // f
	Durability,
	Beauty,
};

enum class BuildingPieceTraits
{ // f
	Durability,
	Beauty,
	ModularValue,
	Type, // 0 if floor, 1 if wall, 2 if roof, changes modularvalue to movespeed,
	      // holdingstrength, weight respectively
};

enum class TransportTraits
{ // f
	Length,
	Width,
	MovementSpeed,
	Capacity,
	Water,
	WeightLimit,
};

enum class ContainerTraits
{ // i
	// list of objects it can hold
	Produces, // whether it produces an object, or just stores
	Capacity,
};

enum class StationTraits
{ // f
	Size,
	// list of activities that can be done here
};

enum class SiegeTraits
{ // i
	CrewAmount,
	Durability,
	Damage,
	Range,
};

/* UNIT TRAITS */
enum unitTraits
{
	// linked arrays are small int arrays
	IsAdult,
	CanCraft,	     // linked to array productType
	ProducesIntangibles, // linked to arrayIntangibleType
	CanGather,	     // linked to array blockType
	CanBuff,	     // linked to array unitType
	CanTrain,	     // linked to array unitType
	HasAbilities,	     // linked to array abilityType
	CanMount,	     // linked to array animalType
		  //  array equipmentType
};

/* ITEMS */

#endif // DATA_H_
