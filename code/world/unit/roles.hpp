#ifndef ROLES_H_
#define ROLES_H_

enum class Role {NONE,
    //MELEE
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


// actions require a certain job and also a certain tool. For example, "Butcher" requires a knife and also the Butcher job, while "Cut" only requires a knife. Burn needs fire, but not oven, while fire needs a kiln like structure
// TODO: use "FineChop" action in appropriate places, make "actions" for combat units, really weapons
enum class Actions { NONE, Collect, Hunt, Mine, Cut, Chop, Dig, Light, Butcher, Paint, Sculpt, Chisel, Write, Pott, Smelt, Smith, Perform, Operate, Administer, Build, Command, Mould, Woodwork, Stonework, Glasswork, Saw, Engrave, Burn,Fire,Press,Carve,WoodCarve,StoneCarve,Weave,Bless,PrimitiveCook,Cook,Craft,Explore,Negotiate,Plow,Plant,Weed,Harvest,Milk,Shear,Mill,Fish,Herd,Trade,Haul, Bake, Treat, Cast, Mix, Boil, Whittle, Knapp, Spin, Grind, Preserve, LeatherCraft, Dip, Lay, WoodCraft, WheelCraft, CanoeCarve, BoatCraft, SiegeCraft, Engineer, Lift, Wait, Measure, SculptMould, Sew, Cur, Tan, CandleCast, Ponder, Tabulate, CandleMould,  Mint, Bind, WireDraw, MudbrickSculpt, BrickSculpt, LowFire, Brew, OilMake, Mash, FineChop,
//TODO: MAY NOT BE IN ACTIONS TO TOOL OR ROLES YET
	Tame, Scrape, Churn, Crush, Leatherwork, Fletch, Compound, Saponify, BowCraft, MAX
};


struct RoleData {
uint8_t cost;
Age age;
vector<vector<Role>> validPrerequisiteRole;
vector<vector<Role>> requisitesOf;
vector<std::pair<Role, uint8_t>> reductions;
  vector<int> apprenticeTime;
}

RoleData roleDatas[static_cast<int>(Roles::MAX)];

struct ToolArray { ToolOrStation tool[9]; };
ToolArray actionToTools[static_cast<size_t>(Actions::MAX)];
struct ToolsReplaceablesArray { int replaceables[8]; };
ToolsReplaceablesArray actionToToolsReplaceables[static_cast<size_t>(Actions::MAX)];
struct RoleArray { Role role[8]; };
RoleArray actionToRoles[static_cast<size_t>(Actions::MAX)];

void initializeActionToTools() {
  actionToTools[(size_t)Actions::Hunt] = {Tool::PrimitiveSpear, Tool::Spear, Tool::Pike, Tool::Greatsword, Tool::Halberd, Station::Animal};
  actionToRoles[(size_t)Actions::Melee] = {Role::MeleeSoldier, Role::SpearHunter};
  actionToTools[(size_t)Actions::Mine] = {Tool::Pickaxe};
  actionToRoles[(size_t)Actions::Mine] = {Role::StoneMiner, Role::CopperMiner, Role::IronMiner, Role::GoldMiner, Role::SilverMiner, Role::SaltMiner};
  actionToTools[(size_t)Actions::Cut] = {Tool::Knife, Tool::Machete, Tool::Sword};
  actionToRoles[(size_t)Actions::Cut] = {Role::Apothecary, Role::Planter};
  actionToTools[(size_t)Actions::Chop] = {Tool::Axe, Tool::Greataxe, Station::Tree};
  actionToRoles[(size_t)Actions::Chop] = {Role::Woodcutter};
  actionToTools[(size_t)Actions::FineChop] = {Tool::Knife, Tool::Cleaver, Tool::Machete}
actionToRoles[(size_t)Actions::FineChop] = {Role::Cook, Role::Chef, Role::Apothecary};
  actionToTools[(size_t)Actions::Dig] = {Tool::Shovel, Tool::Trowel, Tool::DiggingStick};
    actionToRoles[(size_t)Actions::Dig] = {Role::Planter, Role::Structures};
  actionToTools[(size_t)Actions::Light] = {Tool::Torch, Tool::Candle, Tool::Flint};
    actionToRoles[(size_t)Actions::Light] = {Role::NONE};
  actionToTools[(size_t)Actions::Butcher] = {Tool::Cleaver, Tool::Knife, Tool::Machete, Station::Corpse};
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
    //TODO: alternate shitty operation tools
    actionToTools[(size_t)Actions::Operate] = {Tool::Scalpel,  Tool::Needle};
    actionToToolsReplaceables[(size_t)Actions::Operate] = {0,1};
    actionToRoles[(size_t)Actions::Operate] = {Role::Surgeon};
    actionToRoles[(size_t)Actions::Administer] = {Role::Surgeon, Role::Herbalist, Role::Apothecary};
    actionToTools[(size_t)Actions::Build] = {Tool::Hammer, Tool::Mallet};
        actionToToolsReplaceables[(size_t)Actions::Build] = {-1,-1};
    actionToRoles[(size_t)Actions::Build] = {Role::ShelterBuilder, Role::Builder};
    actionToTools[(size_t)Actions::Mould] = {Tool::Mould};
    actionToRoles[(size_t)Actions::Mould] = {Role::Chandler, Role::Potter};
    actionToTools[(size_t)Actions::Woodwork] = { Tool::Adze, Tool::MeasuringTools, Tool::Chisel, Tool::Scraper, Station::Tabletop};
    actionToToolsReplaceables[(size_t)Actions::Woodwork] = {-1,1,2,3,4,5};
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
        actionToToolsReplaceables[(size_t)Actions::WoodCarve] = {0,1,2,0};
    actionToRoles[(size_t)Actions::WoodCarve] = {Role::WoodCarver};
    actionToTools[(size_t)Actions::Weave] = {Tool::HandheldLoom, Station::Loom};
    actionToToolsReplaceables[(size_t)Actions::Weave] = {0,1};
    actionToRoles[(size_t)Actions::Weave] = {Role::Weaver};
    actionToRoles[(size_t)Actions::BasketWeave] = {Role::BasketWeaver};
    actionToTools[(size_t)Actions::Bless] = {Tool::Incense};
    actionToRoles[(size_t)Actions::Bless] = {Role::Priest};
    actionToTools[(size_t)Actions::Cook] = {Tool::Pot, Station::Oven, Station::Tabletop};
    actionToToolsReplaceables[(size_t)Actions::Cook] = {0,1,2};
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
    actionToTools[(size_t)Actions::Harvest] = {Tool::Sickle, Tool::Scythe};
     actionToToolsReplaceables[(size_t)Actions::Harvest] = {-1, -1};
    actionToRoles[(size_t)Actions::Harvest] = {Role::Planter};
    actionToTools[(size_t)Actions::Milk] = {Tool::Bucket, Tool::Pot, Tool::Jar};
    actionToToolsReplaceables[(size_t)Actions::Milk] = {0,0,0};
    actionToRoles[(size_t)Actions::Milk] = {Role::Herder, Role::Shepherd};
    actionToTools[(size_t)Actions::Shear] = {Tool::Machete, Tool::Shears};
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
    //NOTE: maybe change awl to optional
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
    actionToTools[(size_t)Actions::CanoeCarve] = {Tool::Saw, Tool::Axe, Tool::Adze};
        actionToToolsReplaceables[(size_t)Actions::CanoeCarve] = {0,0,1};
    actionToRoles[(size_t)Actions::CanoeCarve] = {Role::CanoeCarver};
    actionToTools[(size_t)Actions::BoatCraft] = {Tool::Mallet, Tool::MeasuringTools};
        actionToToolsReplaceables[(size_t)Actions::BoatCraft] = {0,1};
    actionToRoles[(size_t)Actions::BoatCraft] = {Role::BoatBuilder, Role::Shipwright};
    actionToTools[(size_t)Actions::SiegeCraft] = {Tool::Mallet, Tool::Hammerstone, Tool::MeasuringTools};
        actionToToolsReplaceables[(size_t)Actions::BoatCraft] = {0,1};
    actionToRoles[(size_t)Actions::SiegeCraft] = {Role::SiegeEngineer};
    actionToTools[(size_t)Actions::Engineer] = {Tool::Mallet, Tool::MeasuringTools};
    actionToToolsReplaceables[(size_t)Actions::Engineer] = {-1,1};
    actionToRoles[(size_t)Actions::Engineer] = {Role::Engineer};
    actionToTools[(size_t)Actions::Wait] = {Tool::Bucket, Tool::Pot, Tool::Jar};
    actionToTools[(size_t)Actions::Measure] = {Tool::MeasuringTools, Tool::Scale};
    actionToTools[(size_t)Actions::Crush] = {Tool::Hammer, Tool::Hammerstone};
    //NOTE: maybe change awl to optional
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

    

enum class Role {NONE,
    //MELEE
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

 

#endif // ROLES_H_
