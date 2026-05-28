#ifndef ROLES_H_
#define ROLES_H_
#include "enum.hpp"
#include <core/data.hpp>
#include <cstdint>
#include <limits>
#include <vector>
#include <variant>
#include <world/item/enum.hpp>
#include <core/tables.hpp>

constexpr uint16_t MAX_ROLES_PER_TASK = 6;

struct RoleData
{
	uint8_t cost;
	Time age;
	std::vector<std::vector<Role>> validPrerequisiteRole;
	std::vector<std::vector<Role>> requisitesOf;
	std::vector<std::pair<Role, uint8_t>> reductions;
	std::vector<int> apprenticeTime;
};

RoleData roleDatas[static_cast<int>(Role::MAX)];

//TODO: make both of these lookup tables more efficient, (make them ragged tables)
struct ToolArray
{
	ToolOrStation tool[9];
};

ToolArray actionToTools[static_cast<uint16_t>(Action::ACTION_MAX)];

//negatives are unnecessary.
inline constexpr RaggedLookupTable<Action, std::pair<std::variant<Station, Item>, int8_t>, ACTION_TOOLS_AMOUNT> actionToTools = [] {
	RaggedLookupTable<Action, std::pair<Item, int8_t>, ACTION_TOOLS_AMOUNT, std::numeric_limits<uint8_t>::max()> lt{};
	using enum Action;
	lt.set(Action::Pott, {1, 1, 0, -1, -2}, {Buildable::Oven, Buildable::Furnace, Buildable::PottersWheel, Item::Scraper, Item::Stylus});
	lt.set(Action::Smelt, {0, 1}, {Buildable::Furnace, Item::Crucible});
	lt.set(Action::Smith, {0, 1, 2}, {Buildable::Anvil, Item::Hammer, Item::Chisel});
	lt.set(Action::Perform, {-1, -1, -1, -1}, {Item::Lyre, Item::Drum, Item::Lur, Item::PanFlute});
	lt.set(Action::Operate, {0, 1}, {Item::Scalpel, Item::Needle});
	lt.set(Action::Build, {-1, -1}, {Item::Hammer, Item::Mallet});
	lt.set(Action::Woodwork, {-1, 1, 2, 3, 4, 5});
	lt.set(Action::Stonework, {0, 1, 2, 3, 4, 5});
	lt.set(Action::GlassMake, {0, 1, 2}, {Item::Bellows, Buildable::RollingMachine, Buildable::Furnace});
	lt.set(Action::Glasswork, {0, 1, (Action::Glasswork, {0, 1, 2})); //TODO
	lt.set(Action::Burn, {0, 1, 2}, {Item::Candle, Item::Flint, Item::Torch});
	lt.set(Action::WoodCarve, {0, 1, 2, 0}, {Item::Chisel, Item::Adze, Item::Knife, Item::Mallet});
	lt.set(Action::Weave, {0, 1}, {Item::HandheldLoom, Buildable::Loom});
	lt.set(Action::Cook, {0, 1, 2}, {Item::Pot, Buildable::Oven, Buildable::Tabletop});
	lt.set(Action::Harvest, {-1, -1}, {Item::Sickle, Item::Scythe});
	lt.set(Action::Milk, {0, 0, 0}, {Item::Bucket, Item::Pot, Item::Jar});
	lt.set(Action::Trade, {-1, -1, -1}, {Item::Bucket, Item::Basket, Item::Jar});
	lt.set(Action::Mix, {0, 0, 1, 1, 1}, {Item::Staff, Item::Stick, Item::Bucket, Item::ClayPot, Item::Pot});
	lt.set(Action::Churn, {0, 0, 1, 1, 1}, {Item::Staff, Item::Stick, Item::Bucket, Item::ClayPot, Item::Pot});
	lt.set(Action::Boil, {0, 0, 1, 1}, {Buildable::PitFire, Buildable::Oven, Item::Bucket, Item::Pot});
	lt.set(Action::Spin, {0, 0, -1}, {Item::Spindle, Item::Distaff, Buildable::Spinner});
	lt.set(Action::LeatherCraft, {0, 1, 2}, {Item::Knife, Item::Awl, Item::Needle});
	lt.set(Action::CanoeCarve, {0, 0, 1}, {Item::Saw, Item::Axe, Item::Adze});
	lt.set(
	    Action::BoatCraft,
	    {0, (Action::BoatCraft, {0, 1})); //TODO
        lt.set(Action::Engineer, {-1,0}, {Item::Mallet, Item::MeasuringTools}));
	lt.set(Action::MudbrickSculpt, {1, -2}, {Item::Trowel, Item::BrickMould});
	lt.set(Action::BrickSculpt, {1, -2}, {Item::Trowel, Item::BrickMould});
	lt.set(Action::Mash, {1, 1}, {Item::Pestle, Buildable::Mill});
	lt.set(Action::StoneCarve, {0, 1, 2}, {Item::Chisel, Item::Mallet, Item::Scraper});
	lt.set(Action::Mint, {0, 1, 2, 3},
	       {Item::PatternedDie, Item::PatternedDie, Item::Mallet, Buildable::Furnace});
	lt.set(Action::Sculpt, {0, 1, -1}, {Item::Scraper, Item::Stylus, Item::MeasuringItems});
	lt.set(Action::LowPott, {0, -1, -2}), {Buildable::PitFire, Item::Scraper, Item::Stylus};
	lt.set(Action::Hunt, {Item::PrimitiveSpear, Item::Spear, Item::Pike, Item::Greatsword,
			      Item::Halberd, Buildable::Animal}); // TODO: station
	lt.set(Action::Mine, {Item::Pickaxe});
	lt.set(Action::Cut, {Item::Knife, Item::Machete, Item::Sword});
	lt.set(Action::Chop, {Item::Axe, Item::Greataxe, Buildable::Tree}); // TODO: station
	lt.set(Action::FineChop, {Item::Knife, Item::Cleaver, Item::Machete});
	lt.set(Action::Dig, {Item::Shovel, Item::Trowel, Item::DiggingStick});
	lt.set(Action::Light, {Item::Torch, Item::Candle, Item::Flint});
	lt.set(Action::Butcher,
	       {Item::Cleaver, Item::Knife, Item::Machete, Buildable::Corpse}); // TODO: station
	lt.set(Action::Paint, {Item::Brush});
	lt.set(Action::Chisel, {Item::Chisel});
	lt.set(Action::Write, {Item::Pen});
	lt.set(Action::Mould, {Item::Mould});
	lt.set(Action::Glasswork, {Item::Blowpipe, Item::Graver, Buildable::Forge});
	lt.set(Action::Saw, {Item::Saw});
	lt.set(Action::Engrave, {Item::Graver});
	lt.set(Action::Fire, {Buildable::Furnace, Buildable::Oven, Buildable::Kiln, Buildable::Forge});
	lt.set(Action::Press, {Buildable::Press});
	lt.set(Action::Carve, {Item::Knife});
	lt.set(Action::Bless, {Item::Incense});
	lt.set(Action::Explore, {Item::Compass, Item::Binocular});
	lt.set(Action::Plow, {Item::Ard, Item::HeavyPlow});
	lt.set(Action::Weed, {Item::Trowel});
	lt.set(Action::Shear, {Item::Machete, Item::Shears});
	lt.set(Action::Mill, {Item::Pestle, Buildable::Mill});
	lt.set(Action::Fish, {Item::FishingRod, Item::Net});
	lt.set(Action::Herd, {Item::Whip, Item::Staff});
	lt.set(Action::Haul, {Item::Basket, Item::Bucket, Buildable::Cart, Buildable::Wagon});
	lt.set(Action::Bake, {Buildable::Oven, Item::Pot, Item::Plate});
	lt.set(Action::Treat, {Item::Pot, Item::Bucket});
	lt.set(Action::Tan, {Item::Bucket});
	lt.set(Action::Cast, {Item::Mould, Buildable::SculptMould});
	lt.set(Action::Whittle, {Item::Knife});
	lt.set(Action::Knapp, {Item::Hammerstone, Item::Chisel});
	lt.set(Action::Grind, {Item::Pestle});
	lt.set(Action::Preserve, {Buildable::Keg, Buildable::MashTun, Item::Pot});
	lt.set(Action::Dip, {Item::MeltingPot});
	lt.set(Action::CandleMould, {Item::CandleMould});
	lt.set(Action::Lay, {Item::Spindle, Buildable::Spinner});
	lt.set(Action::WoodCraft, {Item::Hammer, Item::Mallet});
	lt.set(Action::WheelCraft, {Item::Adze, Item::Hammer, Item::Chisel});
	lt.set(Action::BoatCraft, {Item::Mallet, Item::MeasuringItems});
	lt.set(Action::SiegeCraft, {Item::Mallet, Item::Hammerstone, Item::MeasuringItems});
	lt.set(Action::Engineer, {Item::Mallet, Item::MeasuringItems});
	lt.set(Action::Wait, {Item::Bucket, Item::Pot, Item::Jar});
	lt.set(Action::Measure, {Item::MeasuringItems, Item::Scale});
	lt.set(Action::Crush, {Item::Hammer, Item::Hammerstone});
	lt.set(Action::BowCraft, {Item::Knife, Item::Adze, Item::Awl, Item::Drill});
	lt.set(Action::Brew, {Buildable::Cask});
	lt.set(Action::OilMake, {Buildable::Press});
	lt.set(Action::SculptMould, {Buildable::ClaySculpture});
	lt.set(Action::Sew, {Item::Needle});
	lt.set(Action::Tan, {Item::Bucket, Item::Pot});
	lt.set(Action::CandleCast, {Item::CandleMould});
	return lt;
	    }();

	    inline constexpr RaggedLookupTable<Action, Role, ACTION_ROLE_AMOUNT, Action::MAX>
		actionToRoles =
		    []
	    {
		    using enum Action;

		    RaggedLookupTable<Action, Role, ACTION_ROLE_AMOUNT, Action::MAX> lt{};
		    
		    lt.set(Action::Melee, {Role::MeleeSoldier, Role::SpearHunter});
		    lt.set(Action::Mine, {Role::StoneMiner, Role::CopperMiner, Role::IronMiner,
					  Role::GoldMiner, Role::SilverMiner, Role::SaltMiner});
			   lt.set(Action::Cut, {Role::Apothecary, Role::Planter});
			   lt.set(Action::Chop, {Role::Woodcutter});
			   lt.set(Action::FineChop, {Role::Cook, Role::Chef, Role::Apothecary});
			   lt.set(Action::Dig, {Role::Planter, Role::Structures});
			   lt.set(Action::Light, {Role::NONE});
			   lt.set(Action::Butcher, {Role::Butcher});
			   lt.set(Action::Paint, {Role::Painter});
			   lt.set(Action::Sculpt, {Role::Sculptor, Role::ClayWorker, Role::Potter});
			   lt.set(Action::Chisel, {Role::Stoneworker});
			   lt.set(Action::Write,
				  {Role::BooksAcademicAny, Role::BooksAcademicHistory,
				   Role::BooksAcademicPhilosophy, Role::BooksAcademicMathematics,
				   Role::BooksAcademicNatural, Role::Transcriber,
				   Role::AdvisorKnowledge, Role::AdvisorOrderAdministrative});
			   lt.set(Action::LowPott, {Role::ClayWorker});
			   lt.set(Action::Pott, {Role::Potter});
			   lt.set(Action::Pott, {Role::Potter});
			   lt.set(Action::Smelt, {Role::CopperSmelter, Role::BronzeSmelter, Role::IronSmelter, Role::SteelSmelter, Role::SilverSmelter, Role::GoldSmelter});
			   lt.set(Action::Smith, {Role::Coppersmith, Role::Bronzesmith, Role::Ironsmith,
				   Role::Steelsmith, Role::Silversmith, Role::Goldsmith});
			   lt.set(Action::Perform, {Role::Performer});
			   // TODO: alternate shitty operation tools
			   lt.set(Action::Operate, {Role::Surgeon});
			   lt.set(Action::Administer, {Role::Surgeon, Role::Herbalist, Role::Apothecary});
			   lt.set(Action::Build = {Role::ShelterBuilder, Role::Builder});
			   lt.set(Action::Mould = {Role::Chandler, Role::Potter});
                            lt.set(Action::Woodwork, {Role::Woodworker});
			    lt.set(Action::Stonework, {Role::Stoneworker});
	lt.set(Action::GlassMake, {Role::GlassMaker});
	lt.set(Action::Glasswork, {Role::Glassworker});
	lt.set(Action::Glasswork, {Role::Glassworker});
	lt.set(Action::Saw, {Role::Woodworker, Role::Woodcutter});
	lt.set(Action::Engrave, {Role::Engraver, Role::GemCarver, Role::WoodCarver});
	lt.set(Action::Burn, {Role::Firekeeper});
	// NOTE: figure out who can do fire
	lt.set(Action::Fire, {Role::CharcoalMaker, Role::Potter});
	lt.set(Action::Press, {Role::Planter});
	lt.set(Action::Carve, {Role::Carver});
	lt.set(Action::WoodCarve, {Role::WoodCarver});
	lt.set(Action::Weave, {Role::Weaver});
	lt.set(Action::BasketWeave, {Role::BasketWeaver});
	lt.set(Action::Bless, {Role::Priest});
	lt.set(Action::Cook, {Role::Cook});
	lt.set(Action::Craft, {Role::Crafter});
	lt.set(Action::Explore, {Role::Explorer});
	lt.set(Action::Negotiate, {Role::Negotiater});
	lt.set(Action::Plow, {Role::Plower});
	lt.set(Action::Plant, {Role::Planter});
	lt.set(Action::Weed, {Role::Planter});
	lt.set(Action::Harvest, {Role::Planter});
	lt.set(Action::Milk, {Role::Herder, Role::Shepherd});
	lt.set(Action::Shear, {Role::Herder, Role::Shepherd});
	lt.set(Action::Mill, {Role::GrainGrinder, Role::Miller});
	lt.set(Action::Fish, {Role::Fisherman});
	lt.set(Action::Herd, {Role::Herder, Role::Shepherd});
	lt.set(Action::Trade, {Role::Trader});
	lt.set(Action::Haul, {Role::Hauler});
	lt.set(Action::Bake, {Role::Baker});
	lt.set(Action::Treat, {Role::Dyer, Role::PaperMaker});
	lt.set(Action::Cur, {Role::Butcher, Role::Tanner});
	lt.set(Action::Tan, {Role::Tanner});
	lt.set(Action::Cast, {Role::Founder, Role::Silversmith, Role::Goldsmith});
	lt.set(Action::Mix, {Role::Mixer});
	lt.set(Action::Boil, {Role::Cook, Role::Firekeeper});
	lt.set(Action::Whittle, {Role::Woodworker, Role::Carver});
	lt.set(Action::Knapp, {Role::Knapper, Role::StoneWorker});
	lt.set(Action::Spin, {Role::Spinner});
	lt.set(Action::Grind, {Role::Apothecary});
	lt.set(Action::Preserve, {Role::Preserver});
	// NOTE: maybe change awl to optional
	lt.set(Action::LeatherCraft, {Role::Leathercrafter, Role::Cuirassier});
	lt.set(Action::Dip, {Role::Chandler});
	lt.set(Action::CandleMould, {Role::Chandler});
	lt.set(Action::Lay, {Role::Ropemaker});
	lt.set(Action::WoodCraft, {Role::Woodworker});
	lt.set(Action::WheelCraft, {Role::Wheelwright});
	lt.set(Action::CanoeCarve, {Role::CanoeCarver});
	lt.set(Action::BoatCraft, {Role::BoatBuilder, Role::Shipwright});
	lt.set(Action::SiegeCraft, {Role::SiegeEngineer});
	lt.set(Action::Engineer, {Role::Engineer});
	// NOTE: maybe change awl to optional
	lt.set(Action::BowCraft, {Role::Bowyer});
	lt.set(Action::MudbrickSculpt, {Role::MudbrickMaker});
	lt.set(Action::BrickSculpt, {Role::BrickMaker});
	lt.set(Action::Mash, {Role::Brewer});
	// TODO: make sure this works
	lt.set(Action::Brew, {Role::Brewer});
	lt.set(Action::OilMake, {Role::OilMaker});
	// to do roles
	lt.set(Action::SculptMould, {Role::Sculptor});
	lt.set(Action::Sew, {Role::Tailor});
	lt.set(Action::Cur, {Role::Butcher, Role::Tanner});
	lt.set(Action::CandleCast, {Role::Chandler});
	lt.set(Action::Mint, {Role::Minter});

	// NON PRODUCT/RESOURCE
	lt.set(Action::Tame, {Role::HorseBreeder, Role::Shepherd, Role::Herder});
	lt.set(Action::Command, {Role::MilLeader, Role::Monarch, Role::Landowner});
		    return lt;
	    }	    
#endif // ROLES_H_
