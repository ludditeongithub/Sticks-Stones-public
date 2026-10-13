#pragma once
#include <cstdint>
#include <variant>
#include <core/coord.hpp>
#include <core/packed_enum.hpp>
#include <data/types/buildable.hpp>
#include <data/types/item.hpp>
#include <data/types/time.hpp>


// actions require a certain job and also a certain tool. For example, "Butcher" requires a knife
// and also the Butcher job, while "Cut" only requires a knife. Burn needs fire, but not oven, while
// fire needs a kiln like structure
// TODO: use "FineChop" action in appropriate places, make "actions" for combat units, really
// weapons
enum class Action : uint8_t
{
	NONE,
	UNIT_MIN,
	Collect,
	Hunt,
	Mine,
	Cut,
	Chop,
	Dig,
	Light,
	Butcher,
	Paint,
	Sculpt,
	Chisel,
	Write,
	Pott,
	Smelt,
	Smith,
	Perform,
	Operate,
	Administer,
	Build,
	Command,
	Mould,
	Woodwork,
	Stonework,
	Glasswork,
	Saw,
	Engrave,
	Burn,
	Fire,
	Press,
	Carve,
	WoodCarve,
	StoneCarve,
	Weave,
	Bless,
	PrimitiveCook,
	Cook,
	Craft,
	Explore,
	Negotiate,
	Plow,
	Plant,
	Weed,
	Harvest,
	Milk,
	Shear,
	Mill,
	Fish,
	Herd,
	Trade,
	Haul,
	Bake,
	Treat,
	Cast,
	Mix,
	Boil,
	Whittle,
	Knapp,
	Spin,
	Grind,
	Preserve,
	LeatherCraft,
	Dip,
	Lay,
	WoodCraft,
	WheelCraft,
	CanoeCarve,
	BoatCraft,
	SiegeCraft,
	Engineer,
	Lift,
	Wait,
	Measure,
	SculptMould,
	Sew,
	Cur,
	Tan,
	CandleCast,
	Ponder,
	Tabulate,
	CandleMould,
	Mint,
	Bind,
	WireDraw,
	MudbrickSculpt,
	BrickSculpt,
	LowFire,
	Brew,
	OilMake,
	Mash,
	FineChop,
	// TODO: MAY NOT BE IN ACTIONS TO TOOL OR ROLES YET
	Tame,
	Scrape,
	Churn,
	Crush,
	Leatherwork,
	Fletch,
	Compound,
	Saponify,
	BowCraft,
	GlassMake,
	Melee,
	LowPott,
	BasketWeave,
	// TODO: this maybe should be a special MAX
	UNIT_MAX,

	MAIN_MIN,
	// shared by animals
	Dead,
	Idle,
	Sleep,
	Prowl,
	CheckProwl,
	Assign,
	Wander,
	Flee,
	Pursuit,
	// end shared by animals
	PickupTool,
	MAIN_MAX,

	APPROACH_MIN,
	ApproachFruit,
	ApproachPlant,
	ApproachGrass,
	ApproachTile,
	APPROACH_MAX,

	ANIMAL_MIN,
	Breed,		   // TODO
	AnimalFoodSearch,  // TODO
	AnimalBreedSearch, // TODO
	AnimalDrinkSearch, // TODO
	AnimalFollowPack,	   // wanders if animal is not a pack animal, possibly change
			   // to wander
	AnimalMigration,	   // TODO
	ANIMAL_MAX,
	MAX
};

enum class ActionClass
{
	Resource,
	Production,
	Support,
	Research,
	Exploration,
	Combat,
	Hauling
};

enum class ActState : uint8_t
{
	Walk = 0,
	Run = 1,
	Act = 2,
        NewPath = 3
};

struct ActionRequirement
{
	std::variant<Buildable, Item> requirement;
	uint8_t index;
        uint8_t amount;
};
