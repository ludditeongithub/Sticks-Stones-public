#ifndef ROLES_H_
#define ROLES_H_
#include "enum.hpp"
#include <core/data.hpp>
#include <cstdint>
#include <limits>
#include <vector>
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
inline constexpr RaggedLookupTable<Action, std::pair<Item, int8_t>, ACTION_TOOLS_AMOUNT> actionToTools = [] {
	RaggedLookupTable<Action, std::pair<Item, int8_t>, ACTION_TOOLS_AMOUNT, std::numeric_limits<uint8_t>::max()> lt{};
	using enum Action;
	lt.set(Action::Pott, {1, 1, 0, -1, -2}, {Station::Oven, Station::Furnace, Station::PottersWheel, Item::Scraper, Item::Stylus});
	lt.set(Action::Smelt, {0, 1}, {Station::Furnace, Item::Crucible});
	lt.set(Action::Smith, {0, 1, 2}, {Station::Anvil, Item::Hammer, Item::Chisel});
	lt.set(Action::Perform, {-1, -1, -1, -1}, {Item::Lyre, Item::Drum, Item::Lur, Item::PanFlute});
	lt.set(Action::Operate, {0, 1}, {Item::Scalpel, Item::Needle});
	lt.set(Action::Build, {-1, -1}, {Item::Hammer, Item::Mallet});
	lt.set(Action::Woodwork, {-1, 1, 2, 3, 4, 5});
	lt.set(Action::Stonework, {0, 1, 2, 3, 4, 5});
	lt.set(Action::GlassMake, {0, 1, 2}, {Item::Bellows, Station::RollingMachine, Station::Furnace});
	lt.set(Action::Glasswork, {0, 1, (Action::Glasswork, {0, 1, 2})); //TODO
	lt.set(Action::Burn, {0, 1, 2}, {Item::Candle, Item::Flint, Item::Torch});
	lt.set(Action::WoodCarve, {0, 1, 2, 0}, {Item::Chisel, Item::Adze, Item::Knife, Item::Mallet});
	lt.set(Action::Weave, {0, 1}, {Item::HandheldLoom, Station::Loom});
	lt.set(Action::Cook, {0, 1, 2}, {Item::Pot, Station::Oven, Station::Tabletop});
	lt.set(Action::Harvest, {-1, -1}, {Item::Sickle, Item::Scythe});
	lt.set(Action::Milk, {0, 0, 0}, {Item::Bucket, Item::Pot, Item::Jar});
	lt.set(Action::Trade, {-1, -1, -1}, {Item::Bucket, Item::Basket, Item::Jar});
	lt.set(Action::Mix, {0, 0, 1, 1, 1}, {Item::Staff, Item::Stick, Item::Bucket, Item::ClayPot, Item::Pot});
	lt.set(Action::Churn, {0, 0, 1, 1, 1}, {Item::Staff, Item::Stick, Item::Bucket, Item::ClayPot, Item::Pot});
	lt.set(Action::Boil, {0, 0, 1, 1}, {Station::PitFire, Station::Oven, Item::Bucket, Item::Pot});
	lt.set(Action::Spin, {0, 0, -1}, {Item::Spindle, Item::Distaff, Station::Spinner});
	lt.set(Action::LeatherCraft, {0, 1, 2}, {Item::Knife, Item::Awl, Item::Needle});
	lt.set(Action::CanoeCarve, {0, 0, 1}, {Item::Saw, Item::Axe, Item::Adze});
	lt.set(
	    Action::BoatCraft,
	    {0, (Action::BoatCraft, {0, 1})); //TODO
        lt.set(Action::Engineer, {-1,0}, {Tool::Mallet, Tool::MeasuringTools}));
	lt.set(Action::MudbrickSculpt, {1, -2}, {Item::Trowel, Item::BrickMould});
	lt.set(Action::BrickSculpt, {1, -2}, {Item::Trowel, Item::BrickMould});
	lt.set(Action::Mash, {1, 1}, {Item::Pestle, Station::Mill});
	lt.set(Action::StoneCarve, {0, 1, 2}, {Item::Chisel, Item::Mallet, Item::Scraper});
	lt.set(Action::Mint, {0, 1, 2, 3},
	       {Item::PatternedDie, Item::PatternedDie, Item::Mallet, Station::Furnace});
	lt.set(Action::Sculpt, {0, 1, -1}, {Item::Scraper, Item::Stylus, Item::MeasuringItems});
	lt.set(Action::LowPott, {0, -1, -2}), {Station::PitFire, Item::Scraper, Item::Stylus};
	lt.set(Action::Hunt, {Item::PrimitiveSpear, Item::Spear, Item::Pike, Item::Greatsword,
			      Item::Halberd, Station::Animal}); // TODO: station
	lt.set(Action::Mine, {Item::Pickaxe});
	lt.set(Action::Cut, {Item::Knife, Item::Machete, Item::Sword});
	lt.set(Action::Chop, {Item::Axe, Item::Greataxe, Station::Tree}); // TODO: station
	lt.set(Action::FineChop, {Item::Knife, Item::Cleaver, Item::Machete});
	lt.set(Action::Dig, {Item::Shovel, Item::Trowel, Item::DiggingStick});
	lt.set(Action::Light, {Item::Torch, Item::Candle, Item::Flint});
	lt.set(Action::Butcher,
	       {Item::Cleaver, Item::Knife, Item::Machete, Station::Corpse}); // TODO: station
	lt.set(Action::Paint, {Item::Brush});
	lt.set(Action::Chisel, {Item::Chisel});
	lt.set(Action::Write, {Item::Pen});
	lt.set(Action::Mould, {Item::Mould});
	lt.set(Action::Glasswork, {Item::Blowpipe, Item::Graver, Station::Forge});
	lt.set(Action::Saw, {Item::Saw});
	lt.set(Action::Engrave, {Item::Graver});
	lt.set(Action::Fire, {Station::Furnace, Station::Oven, Station::Kiln, Station::Forge});
	lt.set(Action::Press, {Station::Press});
	lt.set(Action::Carve, {Item::Knife});
	lt.set(Action::Bless, {Item::Incense});
	lt.set(Action::Explore, {Item::Compass, Item::Binocular});
	lt.set(Action::Plow, {Item::Ard, Item::HeavyPlow});
	lt.set(Action::Weed, {Item::Trowel});
	lt.set(Action::Shear, {Item::Machete, Item::Shears});
	lt.set(Action::Mill, {Item::Pestle, Station::Mill});
	lt.set(Action::Fish, {Item::FishingRod, Item::Net});
	lt.set(Action::Herd, {Item::Whip, Item::Staff});
	lt.set(Action::Haul, {Item::Basket, Item::Bucket, Station::Cart, Station::Wagon});
	lt.set(Action::Bake, {Station::Oven, Item::Pot, Item::Plate});
	lt.set(Action::Treat, {Item::Pot, Item::Bucket});
	lt.set(Action::Tan, {Item::Bucket});
	lt.set(Action::Cast, {Item::Mould, Station::SculptMould});
	lt.set(Action::Whittle, {Item::Knife});
	lt.set(Action::Knapp, {Item::Hammerstone, Item::Chisel});
	lt.set(Action::Grind, {Item::Pestle});
	lt.set(Action::Preserve, {Station::Keg, Station::MashTun, Item::Pot});
	lt.set(Action::Dip, {Item::MeltingPot});
	lt.set(Action::CandleMould, {Item::CandleMould});
	lt.set(Action::Lay, {Item::Spindle, Station::Spinner});
	lt.set(Action::WoodCraft, {Item::Hammer, Item::Mallet});
	lt.set(Action::WheelCraft, {Item::Adze, Item::Hammer, Item::Chisel});
	lt.set(Action::BoatCraft, {Item::Mallet, Item::MeasuringItems});
	lt.set(Action::SiegeCraft, {Item::Mallet, Item::Hammerstone, Item::MeasuringItems});
	lt.set(Action::Engineer, {Item::Mallet, Item::MeasuringItems});
	lt.set(Action::Wait, {Item::Bucket, Item::Pot, Item::Jar});
	lt.set(Action::Measure, {Item::MeasuringItems, Item::Scale});
	lt.set(Action::Crush, {Item::Hammer, Item::Hammerstone});
	lt.set(Action::BowCraft, {Item::Knife, Item::Adze, Item::Awl, Item::Drill});
	lt.set(Action::Brew, {Station::Cask});
	lt.set(Action::OilMake, {Station::Press});
	lt.set(Action::SculptMould, {Station::ClaySculpture});
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
		    
		    return lt;
	    }	    

	       
	actionToRoles[(uint16_t)Action::Melee] = {Role::MeleeSoldier, Role::SpearHunter};
	actionToRoles[(uint16_t)Action::Mine] = {Role::StoneMiner,  Role::CopperMiner,
						 Role::IronMiner,   Role::GoldMiner,
						 Role::SilverMiner, Role::SaltMiner};
	actionToRoles[(uint16_t)Action::Cut] = {Role::Apothecary, Role::Planter};
	actionToRoles[(uint16_t)Action::Chop] = {Role::Woodcutter};
	actionToRoles[(uint16_t)Action::FineChop] = {Role::Cook, Role::Chef,
									 Role::Apothecary};
	actionToRoles[(uint16_t)Action::Dig] = {Role::Planter, Role::Structures};
	actionToRoles[(uint16_t)Action::Light] = {Role::NONE};
	actionToRoles[(uint16_t)Action::Butcher] = {Role::Butcher};
	actionToRoles[(uint16_t)Action::Paint] = {Role::Painter};
	actionToRoles[(uint16_t)Action::Sculpt] = {Role::Sculptor, Role::ClayWorker, Role::Potter};
	actionToRoles[(uint16_t)Action::Chisel] = {Role::Stoneworker};
	actionToRoles[(uint16_t)Action::Write] = {Role::BooksAcademicAny, Role::BooksAcademicHistory, Role::BooksAcademicPhilosophy, Role::BooksAcademicMathematics,
	    Role::BooksAcademicNatural,	   Role::Transcriber,
	    Role::AdvisorKnowledge,	   Role::AdvisorOrderAdministrative};
	actionToRoles[(uint16_t)Action::LowPott] = {Role::ClayWorker};
	actionToRoles[(uint16_t)Action::Pott] = {Role::Potter};
	actionToRoles[(uint16_t)Action::Pott] = {Role::Potter};
	actionToRoles[(uint16_t)Action::Smelt] = {Role::CopperSmelter, Role::BronzeSmelter, Role::IronSmelter,   Role::SteelSmelter, Role::SilverSmelter, Role::GoldSmelter};
	actionToRoles[(uint16_t)Action::Smith] = {Role::Coppersmith, Role::Bronzesmith,
						  Role::Ironsmith,   Role::Steelsmith,
						  Role::Silversmith, Role::Goldsmith};
	actionToRoles[(uint16_t)Action::Perform] = {Role::Performer};
	// TODO: alternate shitty operation tools
	actionToRoles[(uint16_t)Action::Operate] = {Role::Surgeon};
	actionToRoles[(uint16_t)Action::Administer] = {Role::Surgeon, Role::Herbalist,
						       Role::Apothecary};
	actionToRoles[(uint16_t)Action::Build] = {Role::ShelterBuilder, Role::Builder};
	actionToRoles[(uint16_t)Action::Mould] = {Role::Chandler, Role::Potter, actionToRoles[(uint16_{Role::Woodworker}, actionToRoles[(uint16_{Role::Stoneworker}};
	actionToRoles[(uint16_t)Action::GlassMake] = {Role::GlassMaker};
	actionToRoles[(uint16_t)Action::Glasswork] = {Role::Glassworker};
	actionToRoles[(uint16_t)Action::Glasswork] = {Role::Glassworker};
	actionToRoles[(uint16_t)Action::Saw] = {Role::Woodworker, Role::Woodcutter};
	actionToRoles[(uint16_t)Action::Engrave] = {Role::Engraver, Role::GemCarver, Role::WoodCarver};
	actionToRoles[(uint16_t)Action::Burn] = {Role::Firekeeper};
	// NOTE: figure out who can do fire
	actionToRoles[(uint16_t)Action::Fire] = {Role::CharcoalMaker, Role::Potter};
	actionToRoles[(uint16_t)Action::Press] = {Role::Planter};
	actionToRoles[(uint16_t)Action::Carve] = {Role::Carver};
	actionToRoles[(uint16_t)Action::WoodCarve] = {Role::WoodCarver};
	actionToRoles[(uint16_t)Action::Weave] = {Role::Weaver};
	actionToRoles[(uint16_t)Action::BasketWeave] = {Role::BasketWeaver};
	actionToRoles[(uint16_t)Action::Bless] = {Role::Priest};
	actionToRoles[(uint16_t)Action::Cook] = {Role::Cook};
	actionToRoles[(uint16_t)Action::Craft] = {Role::Crafter};
	actionToRoles[(uint16_t)Action::Explore] = {Role::Explorer};
	actionToRoles[(uint16_t)Action::Negotiate] = {Role::Negotiater};
	actionToRoles[(uint16_t)Action::Plow] = {Role::Plower};
	actionToRoles[(uint16_t)Action::Plant] = {Role::Planter};
	actionToRoles[(uint16_t)Action::Weed] = {Role::Planter};
	actionToRoles[(uint16_t)Action::Harvest] = {Role::Planter};
	actionToRoles[(uint16_t)Action::Milk] = {Role::Herder, Role::Shepherd};
	actionToRoles[(uint16_t)Action::Shear] = {Role::Herder, Role::Shepherd};
	actionToRoles[(uint16_t)Action::Mill] = {Role::GrainGrinder, Role::Miller};
	actionToRoles[(uint16_t)Action::Fish] = {Role::Fisherman};
	actionToRoles[(uint16_t)Action::Herd] = {Role::Herder, Role::Shepherd};
	actionToRoles[(uint16_t)Action::Trade] = {Role::Trader};
	actionToRoles[(uint16_t)Action::Haul] = {Role::Hauler};
	actionToRoles[(uint16_t)Action::Bake] = {Role::Baker};
	actionToRoles[(uint16_t)Action::Treat] = {Role::Dyer, Role::PaperMaker};
	actionToRoles[(uint16_t)Action::Cur] = {Role::Butcher, Role::Tanner};
	actionToRoles[(uint16_t)Action::Tan] = {Role::Tanner};
	actionToRoles[(uint16_t)Action::Cast] = {Role::Founder, Role::Silversmith, Role::Goldsmith};
	actionToRoles[(uint16_t)Action::Mix] = {Role::Mixer};
	actionToRoles[(uint16_t)Action::Boil] = {Role::Cook, Role::Firekeeper};
	actionToRoles[(uint16_t)Action::Whittle] = {Role::Woodworker, Role::Carver};
	actionToRoles[(uint16_t)Action::Knapp] = {Role::Knapper, Role::StoneWorker};
	actionToRoles[(uint16_t)Action::Spin] = {Role::Spinner};
	actionToRoles[(uint16_t)Action::Grind] = {Role::Apothecary};
	actionToRoles[(uint16_t)Action::Preserve] = {Role::Preserver};
	// NOTE: maybe change awl to optional
	actionToRoles[(uint16_t)Action::LeatherCraft] = {Role::Leathercrafter, Role::Cuirassier};
	actionToRoles[(uint16_t)Action::Dip] = {Role::Chandler};
	actionToRoles[(uint16_t)Action::CandleMould] = {Role::Chandler};
	actionToRoles[(uint16_t)Action::Lay] = {Role::Ropemaker};
	actionToRoles[(uint16_t)Action::WoodCraft] = {Role::Woodworker};
	actionToRoles[(uint16_t)Action::WheelCraft] = {Role::Wheelwright};
	actionToRoles[(uint16_t)Action::CanoeCarve] = {Role::CanoeCarver};
	actionToRoles[(uint16_t)Action::BoatCraft] = {Role::BoatBuilder, Role::Shipwright};
	actionToRoles[(uint16_t)Action::SiegeCraft] = {Role::SiegeEngineer};
	actionToRoles[(uint16_t)Action::Engineer] = {Role::Engineer};
	// NOTE: maybe change awl to optional
	actionToRoles[(uint16_t)Action::BowCraft] = {Role::Bowyer};
	actionToRoles[(uint16_t)Action::MudbrickSculpt] = {Role::MudbrickMaker};
	actionToRoles[(uint16_t)Action::BrickSculpt] = {Role::BrickMaker};
	actionToRoles[(uint16_t)Action::Mash] = {Role::Brewer};
	// TODO: make sure this works
	actionToRoles[(uint16_t)Action::Brew] = {Role::Brewer};
	actionToRoles[(uint16_t)Action::OilMake] = {Role::OilMaker};
	// to do roles
	actionToRoles[(uint16_t)Action::SculptMould] = {Role::Sculptor};
	actionToRoles[(uint16_t)Action::Sew] = {Role::Tailor};
	actionToRoles[(uint16_t)Action::Cur] = {Role::Butcher, Role::Tanner};
	actionToRoles[(uint16_t)Action::CandleCast] = {Role::Chandler};
	actionToRoles[(uint16_t)Action::Mint] = {Role::Minter};

	// NON PRODUCT/RESOURCE
	actionToRoles[(uint16_t)Action::Tame] = {Role::HorseBreeder, Role::Shepherd, Role::Herder};
	actionToRoles[(uint16_t)Action::Command] = {Role::MilLeader, Role::Monarch, Role::Landowner};
#endif // ROLES_H_
