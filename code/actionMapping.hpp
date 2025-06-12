#ifndef ACTIONS_H_
#define ACTIONS_H_
#include "basic.hpp"
#include "categories.hpp"

template <typename T>
struct FixedList {
    std::array<T, 8> list;
    uint8_t size = 0;

    void add(T t) {
        if (size < 8) list[size++] = t;
    }

    T operator[](int i) const { return list[i]; }

    auto begin() const { return list.begin(); }
    auto end() const { return list.begin() + size; }
};

using ToolOrStation = std::variant<Tool, Station>;

//which tools can be used to perform which actions
struct ToolArray { ToolOrStation tool[9]; };
ToolArray actionToTools[static_cast<size_t>(Actions::MAX)];
struct ToolsReplaceablesArray { int replaceables[8]; };
ToolsReplaceablesArray actionToToolsReplaceables[static_cast<size_t>(Actions::MAX)];
struct RoleArray { Role role[8]; };
RoleArray actionToRoles[static_cast<size_t>(Actions::MAX)];

void initializeActionToTools() {
  actionToTools[(size_t)Actions::Hunt] = {Tool::PrimitiveSpear, Tool::Spear, Tool::Pike, Tool::Greatsword, Tool::Halberd, Station::Animal};
  actionToTools[(size_t)Actions::Melee] = {Tool::PrimitiveSpear, Tool::Spear, Tool::Handaxe, Tool::Sword, Tool::Pike, Tool::Halberd, Tool::Greataxe, Tool::Greatsword, Station::Pawn};
  actionToRoles[(size_t)Actions::Melee] = {Role::MeleeSoldier, Role::SpearHunter};
  actionToTools[(size_t)Actions::Mine] = {Tool::Pickaxe};
  actionToRoles[(size_t)Actions::Mine] = {Role::StoneMiner, Role::CopperMiner, Role::IronMiner, Role::GoldMiner, Role::SilverMiner, Role::SaltMiner};
  actionToTools[(size_t)Actions::Cut] = {Tool::Knife, Tool::Machete, Tool::Sword};
  actionToRoles[(size_t)Actions::Cut] = {Role::Apothecary, Role::Planter};
  actionToTools[(size_t)Actions::Chop] = {Tool::Axe, Tool::Greataxe, Station::Tree};
  actionToRoles[(size_t)Actions::Chop] = {Role::Woodcutter};
  actionToTools[(size_t)Actions::Dig] = {Tool::Shovel, Tool::Trowel};
    actionToRoles[(size_t)Actions::Dig] = {Role::Planter, Role::Structures};
  actionToTools[(size_t)Actions::Light] = {Tool::Torch, Tool::Candle, Tool::Flint};
    actionToRoles[(size_t)Actions::Light] = {Role::NONE};
  actionToTools[(size_t)Actions::Butcher] = {Tool::Cleaver, Tool::Knife, Station::Corpse};
    actionToRoles[(size_t)Actions::Butcher] = {Role::Butcher};
  actionToTools[(size_t)Actions::Paint] = {Tool::Brush};
    actionToRoles[(size_t)Actions::Paint] = {Role::Painter};
  actionToTools[(size_t)Actions::Sculpt] = {Tool::Scraper, Tool::Stylus, Tool::MeasuringTools};
    actionToRoles[(size_t)Actions::Sculpt] = {Role::Sculptor, Role::ClayWorker, Role::Potter};
  actionToToolsReplaceables[(size_t)Actions::Sculpt] = {0,1,-1};
 actionToTools[(size_t)Actions::Chisel] = {Tool::Chisel};
   actionToRoles[(size_t)Actions::Chisel] = {Role::Stoneworker};
actionToTools[(size_t)Actions::Write] = {Tool::Pen};
actionToRoles[(size_t)Actions::Write] = {Role::BooksAcademicAny, Role::BooksAcademicHistory, Role::BooksAcademicPhilosophy, Role::BooksAcademicMathematics, Role::BooksAcademicNatural, Role::Transcriber, Role::AdvisorKnowledge, Role::AdvisorOrderAdministrative};
actionToTools[(size_t)Actions::LowPott] = {Station::PitFire, Tool::Scraper, Tool::Stylus};
  actionToToolsReplaceables[(size_t)Actions::LowPott] = {0,-1,-2};
  actionToRoles[(size_t)Actions::LowPott] = {Role::ClayWorker};
  actionToRoles[(size_t)Actions::Pott] = {Role::Potter};
actionToTools[(size_t)Actions::Pott] = {Station::Oven, Station::Furnace, Station::PottersWheel,Tool::Scraper, Tool::Stylus};
  actionToToolsReplaceables[(size_t)Actions::Pott] = {1,1,0,-1,-2};
  actionToRoles[(size_t)Actions::Pott] = {Role::Potter};
  actionToTools[(size_t)Actions::Smelt] = {Station::Furnace, Tool::Crucible};
  actionToToolsReplaceables[(size_t)Actions::Smelt] = {0,1};
  actionToRoles[(size_t)Actions::Smelt] = {Role::CopperSmelter,Role::BronzeSmelter,Role::IronSmelter,Role::SteelSmelter,Role::SilverSmelter,Role::GoldSmelter};
  actionToTools[(size_t)Actions::Smith] = {Station::Anvil, Tool::Hammer, Tool::Chisel};
    actionToToolsReplaceables[(size_t)Actions::Smith] = {0,1,2};
    actionToRoles[(size_t)Actions::Smith] = {Role::Coppersmith, Role::Bronzesmith,Role::Ironsmith,Role::Steelsmith,Role::Silversmith,Role::Goldsmith};
    actionToTools[(size_t)Actions::Perform] = {Tool::Lyre, Tool::Drum, Tool::Lur, Tool::PanFlute};
    actionToToolsReplaceables[(size_t)Actions::Perform] = {-1,-1,-1,-1};
    actionToRoles[(size_t)Actions::Perform] = {Role::Performer};
    actionToTools[(size_t)Actions::Operate] = {Tool::Scalpel,  Tool::Needle};
    actionToToolsReplaceables[(size_t)Actions::Operate] = {0,1};
    actionToRoles[(size_t)Actions::Operate] = {Role::Surgeon};
    actionToRoles[(size_t)Actions::Administer] = {Role::Surgeon, Role::Herbalist, Role::Apothecary};
    actionToTools[(size_t)Actions::Build] = {Tool::Hammer, Tool::Mallet};
        actionToToolsReplaceables[(size_t)Actions::Build] = {-1,-1};
    actionToRoles[(size_t)Actions::Build] = {Role::ShelterBuilder, Role::Builder};
    actionToTools[(size_t)Actions::Mould] = {Tool::Mould};
    actionToRoles[(size_t)Actions::Mould] = {Role::Chandler, Role::Potter};
    actionToTools[(size_t)Actions::Woodwork] = {Tool::HandDrill, Tool::Adze, Tool::MeasuringTools, Tool::Chisel, Tool::Scraper, Station::Tabletop};
    actionToToolsReplaceables[(size_t)Actions::Woodwork] = {0,1,2,3,4,5};
    actionToRoles[(size_t)Actions::Woodwork] = {Role::Woodworker};
    actionToTools[(size_t)Actions::Stonework] = {Tool::Chisel, Tool::Mallet, Tool::MeasuringTools, Tool::Scraper, Station::Tabletop};
    actionToToolsReplaceables[(size_t)Actions::Stonework] = {0,1,2,3,4,5};
    actionToRoles[(size_t)Actions::Stonework] = {Role::Stoneworker};
    actionToTools[(size_t)Actions::GlassMake] = {Tool::Bellows, Station::RollingMachine, Station::Furnace};
    actionToToolsReplaceables[(size_t)Actions::GlassMake] = {0,1,2};
    actionToRoles[(size_t)Actions::GlassMake] = {Role::GlassMaker};
    actionToToolsReplaceables[(size_t)Actions::Glasswork] = {0,1,2};
    actionToRoles[(size_t)Actions::Glasswork] = {Role::Glassworker};
    actionToTools[(size_t)Actions::Glasswork] = {Tool::Blowpipe, Tool::Graver, Station::Forge};
    actionToToolsReplaceables[(size_t)Actions::Glasswork] = {0,1,2};
    actionToRoles[(size_t)Actions::Glasswork] = {Role::Glassworker};
    actionToTools[(size_t)Actions::Saw] = {Tool::Saw};
    actionToRoles[(size_t)Actions::Saw] = {Role::Woodworker, Role::Woodcutter};
    actionToTools[(size_t)Actions::Engrave] = {Tool::Graver};
    actionToRoles[(size_t)Actions::Engrave] = {Role::Engraver, Role::GemCarver, Role::WoodCarver};
    actionToTools[(size_t)Actions::Burn] = {Tool::Candle, Tool::Flint, Tool::Torch};
    actionToToolsReplaceables[(size_t)Actions::Burn] = {0,1,2};
    actionToRoles[(size_t)Actions::Burn] = {Role::Firekeeper};
    actionToTools[(size_t)Actions::Fire] = {Station::Furnace, Station::Oven, Station::Kiln, Station::Forge};
    //NOTE: figure out who can do fire
    actionToRoles[(size_t)Actions::Fire] = {Role::CharcoalMaker, Role::Potter};
    actionToTools[(size_t)Actions::Press] = {Station::Press};
    actionToRoles[(size_t)Actions::Press] = {Role::Planter};
    actionToTools[(size_t)Actions::Carve] = {Tool::Knife};
    actionToRoles[(size_t)Actions::Carve] = {Role::Carver};
    actionToTools[(size_t)Actions::WoodCarve] = {Tool::Chisel, Tool::Adze, Tool::Knife, Tool::Mallet};
        actionToToolsReplaceables[(size_t)Actions::WoodCarve] = {0,1,2};
    actionToRoles[(size_t)Actions::WoodCarve] = {Role::WoodCarver};
    actionToTools[(size_t)Actions::Weave] = {Tool::HandheldLoom, Station::Loom};
    actionToToolsReplaceables[(size_t)Actions::Weave] = {0,1};
    actionToRoles[(size_t)Actions::Weave] = {Role::Weaver};
    actionToRoles[(size_t)Actions::BasketWeave] = {Role::BasketWeaver};
    actionToTools[(size_t)Actions::Bless] = {Tool::Incense};
    actionToRoles[(size_t)Actions::Bless] = {Role::Priest};
    actionToTools[(size_t)Actions::Cook] = {Tool::Pot, Tool::Knife, Station::Oven, Station::Tabletop};
    actionToToolsReplaceables[(size_t)Actions::Cook] = {0,1,2,3};
    actionToRoles[(size_t)Actions::Cook] = {Role::Cook};
    actionToRoles[(size_t)Actions::Craft] = {Role::Crafter};
    actionToTools[(size_t)Actions::Explore] = {Tool::Compass, Tool::Binocular};
    actionToRoles[(size_t)Actions::Explore] = {Role::Explorer};
    actionToRoles[(size_t)Actions::Negotiate] = {Role::Negotiater};
    actionToTools[(size_t)Actions::Plow] = {Tool::Ard, Tool::HeavyPlow };
    actionToRoles[(size_t)Actions::Plow] = {Role::Plower};
    actionToRoles[(size_t)Actions::Plant] = {Role::Planter};
    actionToTools[(size_t)Actions::Weed] = {Tool::Trowel};
    actionToRoles[(size_t)Actions::Weed] = {Role::Planter};
    actionToTools[(size_t)Actions::Harvest] = {Tool::Sickle};
    actionToRoles[(size_t)Actions::Harvest] = {Role::Planter};
    actionToTools[(size_t)Actions::Milk] = {Tool::Bucket, Tool::Pot, Tool::Jar};
    actionToToolsReplaceables[(size_t)Actions::Milk] = {0,0,0};
    actionToRoles[(size_t)Actions::Milk] = {Role::Herder, Role::Shepherd};
    actionToTools[(size_t)Actions::Shear] = {Tool::Shears};
    actionToRoles[(size_t)Actions::Shear] = {Role::Herder, Role::Shepherd};
    actionToTools[(size_t)Actions::Mill] = {Tool::Pestle, Station::Mill};
    actionToRoles[(size_t)Actions::Mill] = {Role::GrainGrinder, Role::Miller};
    actionToTools[(size_t)Actions::Fish] = {Tool::FishingRod, Tool::Net};
    actionToRoles[(size_t)Actions::Fish] = {Role::Fisherman};
    actionToTools[(size_t)Actions::Herd] = {Tool::Whip, Tool::Staff};
    actionToRoles[(size_t)Actions::Herd] = {Role::Herder, Role::Shepherd};
    actionToTools[(size_t)Actions::Trade] = {Tool::Bucket, Tool::Basket, Tool::Jar};
    actionToToolsReplaceables[(size_t)Actions::Trade] = {-1,-1};
    actionToRoles[(size_t)Actions::Trade] = {Role::Trader};
    actionToTools[(size_t)Actions::Haul] = {Tool::Basket, Tool::Bucket, Station::Cart, Station::Wagon};
    actionToRoles[(size_t)Actions::Haul] = {Role::Hauler};
    actionToTools[(size_t)Actions::Bake] = {Station::Oven, Tool::Pot, Tool::Plate};
    actionToRoles[(size_t)Actions::Bake] = {Role::Baker};
    actionToTools[(size_t)Actions::Treat] = {Tool::Pot, Tool::Bucket};
    actionToRoles[(size_t)Actions::Treat] = {Role::Dyer, Role::PaperMaker};
    actionToRoles[(size_t)Actions::Cur] = {Role::Butcher, Role::Tanner};
    actionToTools[(size_t)Actions::Tan] = {Tool::Bucket};
    actionToRoles[(size_t)Actions::Tan] = {Role::Tanner};
    actionToTools[(size_t)Actions::Cast] = {Tool::Mould, Station::SculptMould};
    actionToRoles[(size_t)Actions::Cast] = {Role::Founder, Role::Silversmith, Role::Goldsmith};
    actionToTools[(size_t)Actions::Mix] = {Tool::Staff, Tool::Stick, Tool::Bucket, Tool::ClayPot, Tool::Pot};
    actionToToolsReplaceables[(size_t)Actions::Mix] = {0,0,1,1,1};
    actionToRoles[(size_t)Actions::Mix] = {Role::Mixer};
    actionToTools[(size_t)Actions::Churn] = {Tool::Staff, Tool::Stick, Tool::Bucket, Tool::ClayPot, Tool::Pot};
    actionToToolsReplaceables[(size_t)Actions::Churn] = {0,0,1,1,1};
    actionToTools[(size_t)Actions::Boil] = {Station::PitFire, Station::Oven, Tool::Bucket, Tool::Pot};
    actionToToolsReplaceables[(size_t)Actions::Boil] = {0,0,1,1};
    actionToRoles[(size_t)Actions::Boil] = {Role::Cook, Role::Firekeeper};
    actionToTools[(size_t)Actions::Whittle] = {Tool::Knife};
    actionToRoles[(size_t)Actions::Whittle] = {Role::Woodworker, Role::Carver};
    actionToTools[(size_t)Actions::Knapp] = {Tool::Hammerstone, Tool::Chisel};
    actionToRoles[(size_t)Actions::Knapp] = {Role::Knapper, Role::StoneWorker};
    actionToTools[(size_t)Actions::Spin] = {Tool::Spindle, Tool::Distaff, Station::Spinner};
    actionToToolsReplaceables[(size_t)Actions::Spin] = {0,0,-1};
    actionToRoles[(size_t)Actions::Spin] = {Role::Spinner};
    actionToTools[(size_t)Actions::Grind] = {Tool::Pestle};
    actionToRoles[(size_t)Actions::Grind] = {Role::Apothecary};
    actionToTools[(size_t)Actions::Preserve] = {Station::Keg, Station::MashTun, Tool::Pot};
    actionToRoles[(size_t)Actions::Preserve] = {Role::Preserver};
    actionToTools[(size_t)Actions::LeatherCraft] = {Tool::Knife, Tool::Awl, Tool::Needle};
    actionToToolsReplaceables[(size_t)Actions::LeatherCraft] = {0,1,2};
    actionToRoles[(size_t)Actions::LeatherCraft] = {Role::Leathercrafter, Role::Cuirassier};
    actionToTools[(size_t)Actions::Dip] = {Tool::MeltingPot};
    actionToRoles[(size_t)Actions::Dip] = {Role::Chandler};
    actionToTools[(size_t)Actions::CandleMould] = {Tool::CandleMould};
    actionToRoles[(size_t)Actions::CandleMould] = {Role::Chandler};
    actionToTools[(size_t)Actions::Lay] = {Tool::Spindle, Station::Spinner};
    actionToRoles[(size_t)Actions::Lay] = {Role::Ropemaker};
    actionToTools[(size_t)Actions::WoodCraft] = {Tool::Hammer, Tool::Mallet};
    actionToRoles[(size_t)Actions::WoodCraft] = {Role::Woodworker};
    actionToTools[(size_t)Actions::WheelCraft] = {Tool::Adze, Tool::Hammer, Tool::Chisel};
    actionToRoles[(size_t)Actions::WheelCraft] = {Role::Wheelwright};
    actionToTools[(size_t)Actions::CanoeCarve] = {Tool::Saw, Tool::Adze};
        actionToToolsReplaceables[(size_t)Actions::CanoeCarve] = {0,1};
    actionToRoles[(size_t)Actions::CanoeCarve] = {Role::CanoeCarver};
    actionToTools[(size_t)Actions::BoatCraft] = {Tool::Mallet, Tool::MeasuringTools};
        actionToToolsReplaceables[(size_t)Actions::BoatCraft] = {0,1};
    actionToRoles[(size_t)Actions::BoatCraft] = {Role::BoatBuilder, Role::Shipwright};
    actionToTools[(size_t)Actions::SiegeCraft] = {Tool::Mallet, Tool::MeasuringTools};
        actionToToolsReplaceables[(size_t)Actions::BoatCraft] = {-1,1};
    actionToRoles[(size_t)Actions::SiegeCraft] = {Role::SiegeEngineer};
    actionToTools[(size_t)Actions::Engineer] = {Tool::Mallet, Tool::MeasuringTools};
    actionToToolsReplaceables[(size_t)Actions::Engineer] = {-1,1};
    actionToRoles[(size_t)Actions::Engineer] = {Role::Engineer};
    actionToTools[(size_t)Actions::Wait] = {Tool::Bucket, Tool::Pot, Tool::Jar};
    actionToTools[(size_t)Actions::Measure] = {Tool::MeasuringTools, Tool::Scale};
    actionToTools[(size_t)Actions::Crush] = {Tool::Hammer};
    actionToTools[(size_t)Actions::BowCraft] = {Tool::Knife, Tool::Adze, Tool::Awl, Tool::Drill};
    actionToToolsReplaceables[(size_t)Actions::Engineer] = {0,1,2,3};
    actionToRoles[(size_t)Actions::BowCraft] = {Role::Bowyer};
    actionToTools[(size_t)Actions::MudbrickSculpt] = {Tool::Trowel, Tool::BrickMould};
    actionToToolsReplaceables[(size_t)Actions::MudbrickSculpt] = {1, -2};
    actionToRoles[(size_t)Actions::MudbrickSculpt] = {Role::MudbrickMaker};
    actionToTools[(size_t)Actions::BrickSculpt] = {Tool::Trowel, Tool::BrickMould};
    actionToToolsReplaceables[(size_t)Actions::BrickSculpt] = {1, -2};
    actionToRoles[(size_t)Actions::BrickSculpt] = {Role::BrickMaker};
    actionToTools[(size_t)Actions::Mash] = {Tool::Pestle, Station::Mill};
    actionToToolsReplaceables[(size_t)Actions::Mash] = {1, 1};
    actionToRoles[(size_t)Actions::Mash] = {Role::Brewer};
    //TODO: make sure this works
    actionToTools[(size_t)Actions::Brew] = {Station::Cask};
    actionToRoles[(size_t)Actions::Brew] = {Role::Brewer};
    actionToTools[(size_t)Actions::OilMake] = {Station::Press};
    actionToRoles[(size_t)Actions::OilMake] = {Role::OilMaker};
    //to do roles
    actionToTools[(size_t)Actions::SculptMould] = {Station::ClaySculpture};
    actionToRoles[(size_t)Actions::SculptMould] = {Role::Sculptor};
    actionToTools[(size_t)Actions::Sew] = {Tool::Needle};
    actionToRoles[(size_t)Actions::Sew] = {Role::Tailor};
    actionToRoles[(size_t)Actions::Cur] = {Role::Butcher, Role::Tanner};
    actionToTools[(size_t)Actions::Tan] = {Tool::Bucket, Tool::Pot};
    actionToTools[(size_t)Actions::CandleCast] = {Tool::CandleMould};
    actionToRoles[(size_t)Actions::CandleCast] = {Role::Chandler};
    actionToTools[(size_t)Actions::StoneCarve] = {Tool::Chisel, Tool::Mallet, Tool::Scraper};
    actionToToolsReplaceables[(size_t)Actions::StoneCarve] = {0,1,2};
    actionToTools[(size_t)Actions::Mint] = {Tool::PatternedDie, Tool::PatternedDie, Tool::Mallet, Station::Furnace};
    actionToToolsReplaceables[(size_t)Actions::Mint] = {0,1,2,3};
    actionToRoles[(size_t)Actions::Mint] = {Role::Minter};

        //NON PRODUCT/RESOURCE
   actionToRoles[(size_t)Actions::Tame] = {Role::HorseBreeder, Role::Shepherd, Role::Herder};
    actionToRoles[(size_t)Actions::Command] = {Role::MilLeader, Role::Monarch, Role::Landowner};

}

bool queuedActionInterpreter(Actions actionToQueue) {

}



#endif // ACTIONS_H_
