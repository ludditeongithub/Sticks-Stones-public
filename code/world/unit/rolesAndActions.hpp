#ifndef ROLES_H_
#define ROLES_H_
#include "enum.hpp"
#include <core/data.hpp>
#include <cstdint>
#include <vector>

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

struct ToolArray
{
	ToolOrStation tool[9];
};

ToolArray actionToTools[static_cast<uint16_t>(Action::ACTION_MAX)];
struct ToolsReplaceablesArray
{
	int replaceables[8];
};
ToolsReplaceablesArray actionToToolsReplaceables[static_cast<uint16_t>(Action::ACTION_MAX)];

struct RoleArray
{
	Role role[8];
};

RoleArray actionToRoles[static_cast<uint16_t>(Action::ACTION_MAX)];

void initializeActionToTools()
{
	actionToTools[(uint16_t)Action::Hunt] = {Tool::PrimitiveSpear, Tool::Spear,
						 Tool::Pike,	       Tool::Greatsword,
						 Tool::Halberd,	       Station::Animal};
	actionToRoles[(uint16_t)Action::Melee] = {Role::MeleeSoldier, Role::SpearHunter};
	actionToTools[(uint16_t)Action::Mine] = {Tool::Pickaxe};
	actionToRoles[(uint16_t)Action::Mine] = {Role::StoneMiner,  Role::CopperMiner,
						 Role::IronMiner,   Role::GoldMiner,
						 Role::SilverMiner, Role::SaltMiner};
	actionToTools[(uint16_t)Action::Cut] = {Tool::Knife, Tool::Machete, Tool::Sword};
	actionToRoles[(uint16_t)Action::Cut] = {Role::Apothecary, Role::Planter};
	actionToTools[(uint16_t)Action::Chop] = {Tool::Axe, Tool::Greataxe, Station::Tree};
	actionToRoles[(uint16_t)Action::Chop] = {Role::Woodcutter};
	actionToTools[(uint16_t)Action::FineChop] =
	    {Tool::Knife, Tool::Cleaver,
	     Tool::Machete} actionToRoles[(uint16_t)Action::FineChop] = {Role::Cook, Role::Chef,
									 Role::Apothecary};
	actionToTools[(uint16_t)Action::Dig] = {Tool::Shovel, Tool::Trowel, Tool::DiggingStick};
	actionToRoles[(uint16_t)Action::Dig] = {Role::Planter, Role::Structures};
	actionToTools[(uint16_t)Action::Light] = {Tool::Torch, Tool::Candle, Tool::Flint};
	actionToRoles[(uint16_t)Action::Light] = {Role::NONE};
	actionToTools[(uint16_t)Action::Butcher] = {Tool::Cleaver, Tool::Knife, Tool::Machete,
						    Station::Corpse};
	actionToRoles[(uint16_t)Action::Butcher] = {Role::Butcher};
	actionToTools[(uint16_t)Action::Paint] = {Tool::Brush};
	actionToRoles[(uint16_t)Action::Paint] = {Role::Painter};
	actionToTools[(uint16_t)Action::Sculpt] = {Tool::Scraper, Tool::Stylus,
						   Tool::MeasuringTools};
	actionToRoles[(uint16_t)Action::Sculpt] = {Role::Sculptor, Role::ClayWorker, Role::Potter};
	actionToToolsReplaceables[(uint16_t)Action::Sculpt] = {0, 1, -1};
	actionToTools[(uint16_t)Action::Chisel] = {Tool::Chisel};
	actionToRoles[(uint16_t)Action::Chisel] = {Role::Stoneworker};
	actionToTools[(uint16_t)Action::Write] = {Tool::Pen};
	actionToRoles[(uint16_t)Action::Write] = {
	    Role::BooksAcademicAny,	   Role::BooksAcademicHistory,
	    Role::BooksAcademicPhilosophy, Role::BooksAcademicMathematics,
	    Role::BooksAcademicNatural,	   Role::Transcriber,
	    Role::AdvisorKnowledge,	   Role::AdvisorOrderAdministrative};
	actionToTools[(uint16_t)Action::LowPott] = {Station::PitFire, Tool::Scraper, Tool::Stylus};
	actionToToolsReplaceables[(uint16_t)Action::LowPott] = {0, -1, -2};
	actionToRoles[(uint16_t)Action::LowPott] = {Role::ClayWorker};
	actionToRoles[(uint16_t)Action::Pott] = {Role::Potter};
	actionToTools[(uint16_t)Action::Pott] = {
	    Station::Oven, Station::Furnace, Station::PottersWheel, Tool::Scraper, Tool::Stylus};
	actionToToolsReplaceables[(uint16_t)Action::Pott] = {1, 1, 0, -1, -2};
	actionToRoles[(uint16_t)Action::Pott] = {Role::Potter};
	actionToTools[(uint16_t)Action::Smelt] = {Station::Furnace, Tool::Crucible};
	actionToToolsReplaceables[(uint16_t)Action::Smelt] = {0, 1};
	actionToRoles[(uint16_t)Action::Smelt] = {Role::CopperSmelter, Role::BronzeSmelter,
						  Role::IronSmelter,   Role::SteelSmelter,
						  Role::SilverSmelter, Role::GoldSmelter};
	actionToTools[(uint16_t)Action::Smith] = {Station::Anvil, Tool::Hammer, Tool::Chisel};
	actionToToolsReplaceables[(uint16_t)Action::Smith] = {0, 1, 2};
	actionToRoles[(uint16_t)Action::Smith] = {Role::Coppersmith, Role::Bronzesmith,
						  Role::Ironsmith,   Role::Steelsmith,
						  Role::Silversmith, Role::Goldsmith};
	actionToTools[(uint16_t)Action::Perform] = {Tool::Lyre, Tool::Drum, Tool::Lur,
						    Tool::PanFlute};
	actionToToolsReplaceables[(uint16_t)Action::Perform] = {-1, -1, -1, -1};
	actionToRoles[(uint16_t)Action::Perform] = {Role::Performer};
	// TODO: alternate shitty operation tools
	actionToTools[(uint16_t)Action::Operate] = {Tool::Scalpel, Tool::Needle};
	actionToToolsReplaceables[(uint16_t)Action::Operate] = {0, 1};
	actionToRoles[(uint16_t)Action::Operate] = {Role::Surgeon};
	actionToRoles[(uint16_t)Action::Administer] = {Role::Surgeon, Role::Herbalist,
						       Role::Apothecary};
	actionToTools[(uint16_t)Action::Build] = {Tool::Hammer, Tool::Mallet};
	actionToToolsReplaceables[(uint16_t)Action::Build] = {-1, -1};
	actionToRoles[(uint16_t)Action::Build] = {Role::ShelterBuilder, Role::Builder};
	actionToTools[(uint16_t)Action::Mould] = {Tool::Mould};
	actionToRoles[(uint16_t)Action::Mould] = {Role::Chandler, Role::Potter};
	actionToTools[(uint16_t)Action::Woodwork] = {Tool::Adze, Tool::MeasuringTools, Tool::Chisel,
						     Tool::Scraper, Station::Tabletop};
	actionToToolsReplaceables[(uint16_t)Action::Woodwork] = {-1, 1, 2, 3, 4, 5};
	actionToRoles[(uint16_t)Action::Woodwork] = {Role::Woodworker};
	actionToTools[(uint16_t)Action::Stonework] = {
	    Tool::Chisel, Tool::Mallet, Tool::MeasuringTools, Tool::Scraper, Station::Tabletop};
	actionToToolsReplaceables[(uint16_t)Action::Stonework] = {0, 1, 2, 3, 4, 5};
	actionToRoles[(uint16_t)Action::Stonework] = {Role::Stoneworker};
	actionToTools[(uint16_t)Action::GlassMake] = {Tool::Bellows, Station::RollingMachine,
						      Station::Furnace};
	actionToToolsReplaceables[(uint16_t)Action::GlassMake] = {0, 1, 2};
	actionToRoles[(uint16_t)Action::GlassMake] = {Role::GlassMaker};
	actionToToolsReplaceables[(uint16_t)Action::Glasswork] = {0, 1, 2};
	actionToRoles[(uint16_t)Action::Glasswork] = {Role::Glassworker};
	actionToTools[(uint16_t)Action::Glasswork] = {Tool::Blowpipe, Tool::Graver, Station::Forge};
	actionToToolsReplaceables[(uint16_t)Action::Glasswork] = {0, 1, 2};
	actionToRoles[(uint16_t)Action::Glasswork] = {Role::Glassworker};
	actionToTools[(uint16_t)Action::Saw] = {Tool::Saw};
	actionToRoles[(uint16_t)Action::Saw] = {Role::Woodworker, Role::Woodcutter};
	actionToTools[(uint16_t)Action::Engrave] = {Tool::Graver};
	actionToRoles[(uint16_t)Action::Engrave] = {Role::Engraver, Role::GemCarver,
						    Role::WoodCarver};
	actionToTools[(uint16_t)Action::Burn] = {Tool::Candle, Tool::Flint, Tool::Torch};
	actionToToolsReplaceables[(uint16_t)Action::Burn] = {0, 1, 2};
	actionToRoles[(uint16_t)Action::Burn] = {Role::Firekeeper};
	actionToTools[(uint16_t)Action::Fire] = {Station::Furnace, Station::Oven, Station::Kiln,
						 Station::Forge};
	// NOTE: figure out who can do fire
	actionToRoles[(uint16_t)Action::Fire] = {Role::CharcoalMaker, Role::Potter};
	actionToTools[(uint16_t)Action::Press] = {Station::Press};
	actionToRoles[(uint16_t)Action::Press] = {Role::Planter};
	actionToTools[(uint16_t)Action::Carve] = {Tool::Knife};
	actionToRoles[(uint16_t)Action::Carve] = {Role::Carver};
	actionToTools[(uint16_t)Action::WoodCarve] = {Tool::Chisel, Tool::Adze, Tool::Knife,
						      Tool::Mallet};
	actionToToolsReplaceables[(uint16_t)Action::WoodCarve] = {0, 1, 2, 0};
	actionToRoles[(uint16_t)Action::WoodCarve] = {Role::WoodCarver};
	actionToTools[(uint16_t)Action::Weave] = {Tool::HandheldLoom, Station::Loom};
	actionToToolsReplaceables[(uint16_t)Action::Weave] = {0, 1};
	actionToRoles[(uint16_t)Action::Weave] = {Role::Weaver};
	actionToRoles[(uint16_t)Action::BasketWeave] = {Role::BasketWeaver};
	actionToTools[(uint16_t)Action::Bless] = {Tool::Incense};
	actionToRoles[(uint16_t)Action::Bless] = {Role::Priest};
	actionToTools[(uint16_t)Action::Cook] = {Tool::Pot, Station::Oven, Station::Tabletop};
	actionToToolsReplaceables[(uint16_t)Action::Cook] = {0, 1, 2};
	actionToRoles[(uint16_t)Action::Cook] = {Role::Cook};
	actionToRoles[(uint16_t)Action::Craft] = {Role::Crafter};
	actionToTools[(uint16_t)Action::Explore] = {Tool::Compass, Tool::Binocular};
	actionToRoles[(uint16_t)Action::Explore] = {Role::Explorer};
	actionToRoles[(uint16_t)Action::Negotiate] = {Role::Negotiater};
	actionToTools[(uint16_t)Action::Plow] = {Tool::Ard, Tool::HeavyPlow};
	actionToRoles[(uint16_t)Action::Plow] = {Role::Plower};
	actionToRoles[(uint16_t)Action::Plant] = {Role::Planter};
	actionToTools[(uint16_t)Action::Weed] = {Tool::Trowel};
	actionToRoles[(uint16_t)Action::Weed] = {Role::Planter};
	actionToTools[(uint16_t)Action::Harvest] = {Tool::Sickle, Tool::Scythe};
	actionToToolsReplaceables[(uint16_t)Action::Harvest] = {-1, -1};
	actionToRoles[(uint16_t)Action::Harvest] = {Role::Planter};
	actionToTools[(uint16_t)Action::Milk] = {Tool::Bucket, Tool::Pot, Tool::Jar};
	actionToToolsReplaceables[(uint16_t)Action::Milk] = {0, 0, 0};
	actionToRoles[(uint16_t)Action::Milk] = {Role::Herder, Role::Shepherd};
	actionToTools[(uint16_t)Action::Shear] = {Tool::Machete, Tool::Shears};
	actionToRoles[(uint16_t)Action::Shear] = {Role::Herder, Role::Shepherd};
	actionToTools[(uint16_t)Action::Mill] = {Tool::Pestle, Station::Mill};
	actionToRoles[(uint16_t)Action::Mill] = {Role::GrainGrinder, Role::Miller};
	actionToTools[(uint16_t)Action::Fish] = {Tool::FishingRod, Tool::Net};
	actionToRoles[(uint16_t)Action::Fish] = {Role::Fisherman};
	actionToTools[(uint16_t)Action::Herd] = {Tool::Whip, Tool::Staff};
	actionToRoles[(uint16_t)Action::Herd] = {Role::Herder, Role::Shepherd};
	actionToTools[(uint16_t)Action::Trade] = {Tool::Bucket, Tool::Basket, Tool::Jar};
	actionToToolsReplaceables[(uint16_t)Action::Trade] = {-1, -1};
	actionToRoles[(uint16_t)Action::Trade] = {Role::Trader};
	actionToTools[(uint16_t)Action::Haul] = {Tool::Basket, Tool::Bucket, Station::Cart,
						 Station::Wagon};
	actionToRoles[(uint16_t)Action::Haul] = {Role::Hauler};
	actionToTools[(uint16_t)Action::Bake] = {Station::Oven, Tool::Pot, Tool::Plate};
	actionToRoles[(uint16_t)Action::Bake] = {Role::Baker};
	actionToTools[(uint16_t)Action::Treat] = {Tool::Pot, Tool::Bucket};
	actionToRoles[(uint16_t)Action::Treat] = {Role::Dyer, Role::PaperMaker};
	actionToRoles[(uint16_t)Action::Cur] = {Role::Butcher, Role::Tanner};
	actionToTools[(uint16_t)Action::Tan] = {Tool::Bucket};
	actionToRoles[(uint16_t)Action::Tan] = {Role::Tanner};
	actionToTools[(uint16_t)Action::Cast] = {Tool::Mould, Station::SculptMould};
	actionToRoles[(uint16_t)Action::Cast] = {Role::Founder, Role::Silversmith, Role::Goldsmith};
	actionToTools[(uint16_t)Action::Mix] = {Tool::Staff, Tool::Stick, Tool::Bucket,
						Tool::ClayPot, Tool::Pot};
	actionToToolsReplaceables[(uint16_t)Action::Mix] = {0, 0, 1, 1, 1};
	actionToRoles[(uint16_t)Action::Mix] = {Role::Mixer};
	actionToTools[(uint16_t)Action::Churn] = {Tool::Staff, Tool::Stick, Tool::Bucket,
						  Tool::ClayPot, Tool::Pot};
	actionToToolsReplaceables[(uint16_t)Action::Churn] = {0, 0, 1, 1, 1};
	actionToTools[(uint16_t)Action::Boil] = {Station::PitFire, Station::Oven, Tool::Bucket,
						 Tool::Pot};
	actionToToolsReplaceables[(uint16_t)Action::Boil] = {0, 0, 1, 1};
	actionToRoles[(uint16_t)Action::Boil] = {Role::Cook, Role::Firekeeper};
	actionToTools[(uint16_t)Action::Whittle] = {Tool::Knife};
	actionToRoles[(uint16_t)Action::Whittle] = {Role::Woodworker, Role::Carver};
	actionToTools[(uint16_t)Action::Knapp] = {Tool::Hammerstone, Tool::Chisel};
	actionToRoles[(uint16_t)Action::Knapp] = {Role::Knapper, Role::StoneWorker};
	actionToTools[(uint16_t)Action::Spin] = {Tool::Spindle, Tool::Distaff, Station::Spinner};
	actionToToolsReplaceables[(uint16_t)Action::Spin] = {0, 0, -1};
	actionToRoles[(uint16_t)Action::Spin] = {Role::Spinner};
	actionToTools[(uint16_t)Action::Grind] = {Tool::Pestle};
	actionToRoles[(uint16_t)Action::Grind] = {Role::Apothecary};
	actionToTools[(uint16_t)Action::Preserve] = {Station::Keg, Station::MashTun, Tool::Pot};
	actionToRoles[(uint16_t)Action::Preserve] = {Role::Preserver};
	// NOTE: maybe change awl to optional
	actionToTools[(uint16_t)Action::LeatherCraft] = {Tool::Knife, Tool::Awl, Tool::Needle};
	actionToToolsReplaceables[(uint16_t)Action::LeatherCraft] = {0, 1, 2};
	actionToRoles[(uint16_t)Action::LeatherCraft] = {Role::Leathercrafter, Role::Cuirassier};
	actionToTools[(uint16_t)Action::Dip] = {Tool::MeltingPot};
	actionToRoles[(uint16_t)Action::Dip] = {Role::Chandler};
	actionToTools[(uint16_t)Action::CandleMould] = {Tool::CandleMould};
	actionToRoles[(uint16_t)Action::CandleMould] = {Role::Chandler};
	actionToTools[(uint16_t)Action::Lay] = {Tool::Spindle, Station::Spinner};
	actionToRoles[(uint16_t)Action::Lay] = {Role::Ropemaker};
	actionToTools[(uint16_t)Action::WoodCraft] = {Tool::Hammer, Tool::Mallet};
	actionToRoles[(uint16_t)Action::WoodCraft] = {Role::Woodworker};
	actionToTools[(uint16_t)Action::WheelCraft] = {Tool::Adze, Tool::Hammer, Tool::Chisel};
	actionToRoles[(uint16_t)Action::WheelCraft] = {Role::Wheelwright};
	actionToTools[(uint16_t)Action::CanoeCarve] = {Tool::Saw, Tool::Axe, Tool::Adze};
	actionToToolsReplaceables[(uint16_t)Action::CanoeCarve] = {0, 0, 1};
	actionToRoles[(uint16_t)Action::CanoeCarve] = {Role::CanoeCarver};
	actionToTools[(uint16_t)Action::BoatCraft] = {Tool::Mallet, Tool::MeasuringTools};
	actionToToolsReplaceables[(uint16_t)Action::BoatCraft] = {0, 1};
	actionToRoles[(uint16_t)Action::BoatCraft] = {Role::BoatBuilder, Role::Shipwright};
	actionToTools[(uint16_t)Action::SiegeCraft] = {Tool::Mallet, Tool::Hammerstone,
						       Tool::MeasuringTools};
	actionToToolsReplaceables[(uint16_t)Action::BoatCraft] = {0, 1};
	actionToRoles[(uint16_t)Action::SiegeCraft] = {Role::SiegeEngineer};
	actionToTools[(uint16_t)Action::Engineer] = {Tool::Mallet, Tool::MeasuringTools};
	actionToToolsReplaceables[(uint16_t)Action::Engineer] = {-1, 1};
	actionToRoles[(uint16_t)Action::Engineer] = {Role::Engineer};
	actionToTools[(uint16_t)Action::Wait] = {Tool::Bucket, Tool::Pot, Tool::Jar};
	actionToTools[(uint16_t)Action::Measure] = {Tool::MeasuringTools, Tool::Scale};
	actionToTools[(uint16_t)Action::Crush] = {Tool::Hammer, Tool::Hammerstone};
	// NOTE: maybe change awl to optional
	actionToTools[(uint16_t)Action::BowCraft] = {Tool::Knife, Tool::Adze, Tool::Awl,
						     Tool::Drill};
	actionToToolsReplaceables[(uint16_t)Action::Engineer] = {0, 1, 2, 3};
	actionToRoles[(uint16_t)Action::BowCraft] = {Role::Bowyer};
	actionToTools[(uint16_t)Action::MudbrickSculpt] = {Tool::Trowel, Tool::BrickMould};
	actionToToolsReplaceables[(uint16_t)Action::MudbrickSculpt] = {1, -2};
	actionToRoles[(uint16_t)Action::MudbrickSculpt] = {Role::MudbrickMaker};
	actionToTools[(uint16_t)Action::BrickSculpt] = {Tool::Trowel, Tool::BrickMould};
	actionToToolsReplaceables[(uint16_t)Action::BrickSculpt] = {1, -2};
	actionToRoles[(uint16_t)Action::BrickSculpt] = {Role::BrickMaker};
	actionToTools[(uint16_t)Action::Mash] = {Tool::Pestle, Station::Mill};
	actionToToolsReplaceables[(uint16_t)Action::Mash] = {1, 1};
	actionToRoles[(uint16_t)Action::Mash] = {Role::Brewer};
	// TODO: make sure this works
	actionToTools[(uint16_t)Action::Brew] = {Station::Cask};
	actionToRoles[(uint16_t)Action::Brew] = {Role::Brewer};
	actionToTools[(uint16_t)Action::OilMake] = {Station::Press};
	actionToRoles[(uint16_t)Action::OilMake] = {Role::OilMaker};
	// to do roles
	actionToTools[(uint16_t)Action::SculptMould] = {Station::ClaySculpture};
	actionToRoles[(uint16_t)Action::SculptMould] = {Role::Sculptor};
	actionToTools[(uint16_t)Action::Sew] = {Tool::Needle};
	actionToRoles[(uint16_t)Action::Sew] = {Role::Tailor};
	actionToRoles[(uint16_t)Action::Cur] = {Role::Butcher, Role::Tanner};
	actionToTools[(uint16_t)Action::Tan] = {Tool::Bucket, Tool::Pot};
	actionToTools[(uint16_t)Action::CandleCast] = {Tool::CandleMould};
	actionToRoles[(uint16_t)Action::CandleCast] = {Role::Chandler};
	actionToTools[(uint16_t)Action::StoneCarve] = {Tool::Chisel, Tool::Mallet, Tool::Scraper};
	actionToToolsReplaceables[(uint16_t)Action::StoneCarve] = {0, 1, 2};
	actionToTools[(uint16_t)Action::Mint] = {Tool::PatternedDie, Tool::PatternedDie,
						 Tool::Mallet, Station::Furnace};
	actionToToolsReplaceables[(uint16_t)Action::Mint] = {0, 1, 2, 3};
	actionToRoles[(uint16_t)Action::Mint] = {Role::Minter};

	// NON PRODUCT/RESOURCE
	actionToRoles[(uint16_t)Action::Tame] = {Role::HorseBreeder, Role::Shepherd, Role::Herder};
	actionToRoles[(uint16_t)Action::Command] = {Role::MilLeader, Role::Monarch,
						    Role::Landowner};

#endif // ROLES_H_
