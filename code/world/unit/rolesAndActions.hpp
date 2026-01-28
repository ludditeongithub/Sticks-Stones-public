#ifndef ROLES_H_
#define ROLES_H_
#include <cstdint>


enum class Role : uint8_t {NONE,
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
 Cook, Cuirassier, Wheelwright, Scribe,
  //iron: no loom weaver,
    IronSmelter, Ironsmith, OilMaker, PaperMaker, Apothecary, Glassworker,
   //classical, no cartwright, no cheesmaker, shipwright = naval engineer, no chef, no philosopher
    Glassblower, Engraver, Minter, Shipwright, SiegeEngineer,
    SteelSmelter,  Steelsmith,  Founder, Surgeon,  Monarch, MilLeader, Miller,  Caretaker, Hauler,  Dyer,  Chandler, Ropemaker, Tailor,  Armorer, PRODUCTSMAX,
   //SUPPORTPRODUCER
   //RESEARCHER
   Philosopher, Envoy, Explorer, Navigator, Spy, Historian, Mathematician, Cartographer, Diplomat,
   //LEADER
   AdvisorFarming, AdvisorForeign, AdvisorNatural, AdvisorKnowledge, AdvisorOrderAdministrative, AdvisorOrderCulturalArtifact, AdvisorOrderCulturalPerformer, AdvisorOrderLegal, AdvisorStructures, AdvisorTrade,
   Chieftan, Prince, Architect, King, Emperor, Moneyer, CivilEngineer, Aristocrat, MiningEngineer, WagonMaster, Baron,
   MAX};


// actions require a certain job and also a certain tool. For example, "Butcher" requires a knife and also the Butcher job, while "Cut" only requires a knife. Burn needs fire, but not oven, while fire needs a kiln like structure
// TODO: use "FineChop" action in appropriate places, make "actions" for combat units, really weapons
enum class Action : uint8_t {
  NONE,
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

  // TODO: this maybe should be a special MAX
  ACTION_MAX,
  // WALK_MIN,

  // WalkThenCollect,
  // WalkThenHunt,
  // WalkThenMine,
  // WalkThenCut,
  // WalkThenChop,
  // WalkThenDig,
  // WalkThenLight,
  // WalkThenButcher,
  // WalkThenPaint,
  // WalkThenSculpt,
  // WalkThenChisel,
  // WalkThenWrite,
  // WalkThenPott,
  // WalkThenSmelt,
  // WalkThenSmith,
  // WalkThenPerform,
  // WalkThenOperate,
  // WalkThenAdminister,
  // WalkThenBuild,
  // WalkThenCommand,
  // WalkThenMould,
  // WalkThenWoodwork,
  // WalkThenStonework,
  // WalkThenGlasswork,
  // WalkThenSaw,
  // WalkThenEngrave,
  // WalkThenBurn,
  // WalkThenFire,
  // WalkThenPress,
  // WalkThenCarve,
  // WalkThenWoodCarve,
  // WalkThenStoneCarve,
  // WalkThenWeave,
  // WalkThenBless,
  // WalkThenPrimitiveCook,
  // WalkThenCook,
  // WalkThenCraft,
  // WalkThenExplore,
  // WalkThenNegotiate,
  // WalkThenPlow,
  // WalkThenPlant,
  // WalkThenWeed,
  // WalkThenHarvest,
  // WalkThenMilk,
  // WalkThenShear,
  // WalkThenMill,
  // WalkThenFish,
  // WalkThenHerd,
  // WalkThenTrade,
  // WalkThenHaul,
  // WalkThenBake,
  // WalkThenTreat,
  // WalkThenCast,
  // WalkThenMix,
  // WalkThenBoil,
  // WalkThenWhittle,
  // WalkThenKnapp,
  // WalkThenSpin,
  // WalkThenGrind,
  // WalkThenPreserve,
  // WalkThenLeatherCraft,
  // WalkThenDip,
  // WalkThenLay,
  // WalkThenWoodCraft,
  // WalkThenWheelCraft,
  // WalkThenCanoeCarve,
  // WalkThenBoatCraft,
  // WalkThenSiegeCraft,
  // WalkThenEngineer,
  // WalkThenLift,
  // WalkThenWait,
  // WalkThenMeasure,
  // WalkThenSculptMould,
  // WalkThenSew,
  // WalkThenCur,
  // WalkThenTan,
  // WalkThenCandleCast,
  // WalkThenPonder,
  // WalkThenTabulate,
  // WalkThenCandleMould,
  // WalkThenMint,
  // WalkThenBind,
  // WalkThenWireDraw,
  // WalkThenMudbrickSculpt,
  // WalkThenBrickSculpt,
  // WalkThenLowFire,
  // WalkThenBrew,
  // WalkThenOilMake,
  // WalkThenMash,
  // WalkThenFineChop,
  // // TODO: MAY NOT BE IN ACTIONS TO TOOL OR ROLES YET
  // WalkThenTame,
  // WalkThenScrape,
  // WalkThenChurn,
  // WalkThenCrush,
  // WalkThenLeatherwork,
  // WalkThenFletch,
  // WalkThenCompound,
  // WalkThenSaponify,
  // WalkThenBowCraft,

  // WALK_MAX,
  MAIN_MIN,

  Dead,
  Idle,
  Assign,
  NewPath,
  Wander,
  AnimalFoodSearch,
  AnimalHunt,
  AnimalBreedSearch,

  MAIN_MAX,
  MAX
};

enum class MiniAction : uint8_t {
  Walk,
  Run,
  Pickup,
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
ToolArray actionToTools[static_cast<size_t>(Action::ACTION_MAX)];
struct ToolsReplaceablesArray { int replaceables[8]; };
ToolsReplaceablesArray actionToToolsReplaceables[static_cast<size_t>(Action::ACTION_MAX)];
struct RoleArray { Role role[8]; };
RoleArray actionToRoles[static_cast<size_t>(Action::ACTION_MAX)];

void initializeActionToTools() {
  actionToTools[(size_t)Action::Hunt] = {Tool::PrimitiveSpear, Tool::Spear, Tool::Pike, Tool::Greatsword, Tool::Halberd, Station::Animal};
  actionToRoles[(size_t)Action::Melee] = {Role::MeleeSoldier, Role::SpearHunter};
  actionToTools[(size_t)Action::Mine] = {Tool::Pickaxe};
  actionToRoles[(size_t)Action::Mine] = {Role::StoneMiner, Role::CopperMiner, Role::IronMiner, Role::GoldMiner, Role::SilverMiner, Role::SaltMiner};
  actionToTools[(size_t)Action::Cut] = {Tool::Knife, Tool::Machete, Tool::Sword};
  actionToRoles[(size_t)Action::Cut] = {Role::Apothecary, Role::Planter};
  actionToTools[(size_t)Action::Chop] = {Tool::Axe, Tool::Greataxe, Station::Tree};
  actionToRoles[(size_t)Action::Chop] = {Role::Woodcutter};
  actionToTools[(size_t)Action::FineChop] = {Tool::Knife, Tool::Cleaver, Tool::Machete}
actionToRoles[(size_t)Action::FineChop] = {Role::Cook, Role::Chef, Role::Apothecary};
  actionToTools[(size_t)Action::Dig] = {Tool::Shovel, Tool::Trowel, Tool::DiggingStick};
    actionToRoles[(size_t)Action::Dig] = {Role::Planter, Role::Structures};
  actionToTools[(size_t)Action::Light] = {Tool::Torch, Tool::Candle, Tool::Flint};
    actionToRoles[(size_t)Action::Light] = {Role::NONE};
  actionToTools[(size_t)Action::Butcher] = {Tool::Cleaver, Tool::Knife, Tool::Machete, Station::Corpse};
    actionToRoles[(size_t)Action::Butcher] = {Role::Butcher};
  actionToTools[(size_t)Action::Paint] = {Tool::Brush};
    actionToRoles[(size_t)Action::Paint] = {Role::Painter};
  actionToTools[(size_t)Action::Sculpt] = {Tool::Scraper, Tool::Stylus, Tool::MeasuringTools};
    actionToRoles[(size_t)Action::Sculpt] = {Role::Sculptor, Role::ClayWorker, Role::Potter};
  actionToToolsReplaceables[(size_t)Action::Sculpt] = {0,1,-1};
 actionToTools[(size_t)Action::Chisel] = {Tool::Chisel};
   actionToRoles[(size_t)Action::Chisel] = {Role::Stoneworker};
actionToTools[(size_t)Action::Write] = {Tool::Pen};
actionToRoles[(size_t)Action::Write] = {Role::BooksAcademicAny, Role::BooksAcademicHistory, Role::BooksAcademicPhilosophy, Role::BooksAcademicMathematics, Role::BooksAcademicNatural, Role::Transcriber, Role::AdvisorKnowledge, Role::AdvisorOrderAdministrative};
actionToTools[(size_t)Action::LowPott] = {Station::PitFire, Tool::Scraper, Tool::Stylus};
  actionToToolsReplaceables[(size_t)Action::LowPott] = {0,-1,-2};
  actionToRoles[(size_t)Action::LowPott] = {Role::ClayWorker};
  actionToRoles[(size_t)Action::Pott] = {Role::Potter};
actionToTools[(size_t)Action::Pott] = {Station::Oven, Station::Furnace, Station::PottersWheel,Tool::Scraper, Tool::Stylus};
  actionToToolsReplaceables[(size_t)Action::Pott] = {1,1,0,-1,-2};
  actionToRoles[(size_t)Action::Pott] = {Role::Potter};
  actionToTools[(size_t)Action::Smelt] = {Station::Furnace, Tool::Crucible};
  actionToToolsReplaceables[(size_t)Action::Smelt] = {0,1};
  actionToRoles[(size_t)Action::Smelt] = {Role::CopperSmelter,Role::BronzeSmelter,Role::IronSmelter,Role::SteelSmelter,Role::SilverSmelter,Role::GoldSmelter};
  actionToTools[(size_t)Action::Smith] = {Station::Anvil, Tool::Hammer, Tool::Chisel};
    actionToToolsReplaceables[(size_t)Action::Smith] = {0,1,2};
    actionToRoles[(size_t)Action::Smith] = {Role::Coppersmith, Role::Bronzesmith,Role::Ironsmith,Role::Steelsmith,Role::Silversmith,Role::Goldsmith};
    actionToTools[(size_t)Action::Perform] = {Tool::Lyre, Tool::Drum, Tool::Lur, Tool::PanFlute};
    actionToToolsReplaceables[(size_t)Action::Perform] = {-1,-1,-1,-1};
    actionToRoles[(size_t)Action::Perform] = {Role::Performer};
    //TODO: alternate shitty operation tools
    actionToTools[(size_t)Action::Operate] = {Tool::Scalpel,  Tool::Needle};
    actionToToolsReplaceables[(size_t)Action::Operate] = {0,1};
    actionToRoles[(size_t)Action::Operate] = {Role::Surgeon};
    actionToRoles[(size_t)Action::Administer] = {Role::Surgeon, Role::Herbalist, Role::Apothecary};
    actionToTools[(size_t)Action::Build] = {Tool::Hammer, Tool::Mallet};
        actionToToolsReplaceables[(size_t)Action::Build] = {-1,-1};
    actionToRoles[(size_t)Action::Build] = {Role::ShelterBuilder, Role::Builder};
    actionToTools[(size_t)Action::Mould] = {Tool::Mould};
    actionToRoles[(size_t)Action::Mould] = {Role::Chandler, Role::Potter};
    actionToTools[(size_t)Action::Woodwork] = { Tool::Adze, Tool::MeasuringTools, Tool::Chisel, Tool::Scraper, Station::Tabletop};
    actionToToolsReplaceables[(size_t)Action::Woodwork] = {-1,1,2,3,4,5};
    actionToRoles[(size_t)Action::Woodwork] = {Role::Woodworker};
    actionToTools[(size_t)Action::Stonework] = {Tool::Chisel, Tool::Mallet, Tool::MeasuringTools, Tool::Scraper, Station::Tabletop};
    actionToToolsReplaceables[(size_t)Action::Stonework] = {0,1,2,3,4,5};
    actionToRoles[(size_t)Action::Stonework] = {Role::Stoneworker};
    actionToTools[(size_t)Action::GlassMake] = {Tool::Bellows, Station::RollingMachine, Station::Furnace};
    actionToToolsReplaceables[(size_t)Action::GlassMake] = {0,1,2};
    actionToRoles[(size_t)Action::GlassMake] = {Role::GlassMaker};
    actionToToolsReplaceables[(size_t)Action::Glasswork] = {0,1,2};
    actionToRoles[(size_t)Action::Glasswork] = {Role::Glassworker};
    actionToTools[(size_t)Action::Glasswork] = {Tool::Blowpipe, Tool::Graver, Station::Forge};
    actionToToolsReplaceables[(size_t)Action::Glasswork] = {0,1,2};
    actionToRoles[(size_t)Action::Glasswork] = {Role::Glassworker};
    actionToTools[(size_t)Action::Saw] = {Tool::Saw};
    actionToRoles[(size_t)Action::Saw] = {Role::Woodworker, Role::Woodcutter};
    actionToTools[(size_t)Action::Engrave] = {Tool::Graver};
    actionToRoles[(size_t)Action::Engrave] = {Role::Engraver, Role::GemCarver, Role::WoodCarver};
    actionToTools[(size_t)Action::Burn] = {Tool::Candle, Tool::Flint, Tool::Torch};
    actionToToolsReplaceables[(size_t)Action::Burn] = {0,1,2};
    actionToRoles[(size_t)Action::Burn] = {Role::Firekeeper};
    actionToTools[(size_t)Action::Fire] = {Station::Furnace, Station::Oven, Station::Kiln, Station::Forge};
    //NOTE: figure out who can do fire
    actionToRoles[(size_t)Action::Fire] = {Role::CharcoalMaker, Role::Potter};
    actionToTools[(size_t)Action::Press] = {Station::Press};
    actionToRoles[(size_t)Action::Press] = {Role::Planter};
    actionToTools[(size_t)Action::Carve] = {Tool::Knife};
    actionToRoles[(size_t)Action::Carve] = {Role::Carver};
    actionToTools[(size_t)Action::WoodCarve] = {Tool::Chisel, Tool::Adze, Tool::Knife, Tool::Mallet};
        actionToToolsReplaceables[(size_t)Action::WoodCarve] = {0,1,2,0};
    actionToRoles[(size_t)Action::WoodCarve] = {Role::WoodCarver};
    actionToTools[(size_t)Action::Weave] = {Tool::HandheldLoom, Station::Loom};
    actionToToolsReplaceables[(size_t)Action::Weave] = {0,1};
    actionToRoles[(size_t)Action::Weave] = {Role::Weaver};
    actionToRoles[(size_t)Action::BasketWeave] = {Role::BasketWeaver};
    actionToTools[(size_t)Action::Bless] = {Tool::Incense};
    actionToRoles[(size_t)Action::Bless] = {Role::Priest};
    actionToTools[(size_t)Action::Cook] = {Tool::Pot, Station::Oven, Station::Tabletop};
    actionToToolsReplaceables[(size_t)Action::Cook] = {0,1,2};
    actionToRoles[(size_t)Action::Cook] = {Role::Cook};
    actionToRoles[(size_t)Action::Craft] = {Role::Crafter};
    actionToTools[(size_t)Action::Explore] = {Tool::Compass, Tool::Binocular};
    actionToRoles[(size_t)Action::Explore] = {Role::Explorer};
    actionToRoles[(size_t)Action::Negotiate] = {Role::Negotiater};
    actionToTools[(size_t)Action::Plow] = {Tool::Ard, Tool::HeavyPlow };
    actionToRoles[(size_t)Action::Plow] = {Role::Plower};
    actionToRoles[(size_t)Action::Plant] = {Role::Planter};
    actionToTools[(size_t)Action::Weed] = {Tool::Trowel};
    actionToRoles[(size_t)Action::Weed] = {Role::Planter};
    actionToTools[(size_t)Action::Harvest] = {Tool::Sickle, Tool::Scythe};
     actionToToolsReplaceables[(size_t)Action::Harvest] = {-1, -1};
    actionToRoles[(size_t)Action::Harvest] = {Role::Planter};
    actionToTools[(size_t)Action::Milk] = {Tool::Bucket, Tool::Pot, Tool::Jar};
    actionToToolsReplaceables[(size_t)Action::Milk] = {0,0,0};
    actionToRoles[(size_t)Action::Milk] = {Role::Herder, Role::Shepherd};
    actionToTools[(size_t)Action::Shear] = {Tool::Machete, Tool::Shears};
    actionToRoles[(size_t)Action::Shear] = {Role::Herder, Role::Shepherd};
    actionToTools[(size_t)Action::Mill] = {Tool::Pestle, Station::Mill};
    actionToRoles[(size_t)Action::Mill] = {Role::GrainGrinder, Role::Miller};
    actionToTools[(size_t)Action::Fish] = {Tool::FishingRod, Tool::Net};
    actionToRoles[(size_t)Action::Fish] = {Role::Fisherman};
    actionToTools[(size_t)Action::Herd] = {Tool::Whip, Tool::Staff};
    actionToRoles[(size_t)Action::Herd] = {Role::Herder, Role::Shepherd};
    actionToTools[(size_t)Action::Trade] = {Tool::Bucket, Tool::Basket, Tool::Jar};
    actionToToolsReplaceables[(size_t)Action::Trade] = {-1,-1};
    actionToRoles[(size_t)Action::Trade] = {Role::Trader};
    actionToTools[(size_t)Action::Haul] = {Tool::Basket, Tool::Bucket, Station::Cart, Station::Wagon};
    actionToRoles[(size_t)Action::Haul] = {Role::Hauler};
    actionToTools[(size_t)Action::Bake] = {Station::Oven, Tool::Pot, Tool::Plate};
    actionToRoles[(size_t)Action::Bake] = {Role::Baker};
    actionToTools[(size_t)Action::Treat] = {Tool::Pot, Tool::Bucket};
    actionToRoles[(size_t)Action::Treat] = {Role::Dyer, Role::PaperMaker};
    actionToRoles[(size_t)Action::Cur] = {Role::Butcher, Role::Tanner};
    actionToTools[(size_t)Action::Tan] = {Tool::Bucket};
    actionToRoles[(size_t)Action::Tan] = {Role::Tanner};
    actionToTools[(size_t)Action::Cast] = {Tool::Mould, Station::SculptMould};
    actionToRoles[(size_t)Action::Cast] = {Role::Founder, Role::Silversmith, Role::Goldsmith};
    actionToTools[(size_t)Action::Mix] = {Tool::Staff, Tool::Stick, Tool::Bucket, Tool::ClayPot, Tool::Pot};
    actionToToolsReplaceables[(size_t)Action::Mix] = {0,0,1,1,1};
    actionToRoles[(size_t)Action::Mix] = {Role::Mixer};
    actionToTools[(size_t)Action::Churn] = {Tool::Staff, Tool::Stick, Tool::Bucket, Tool::ClayPot, Tool::Pot};
    actionToToolsReplaceables[(size_t)Action::Churn] = {0,0,1,1,1};
    actionToTools[(size_t)Action::Boil] = {Station::PitFire, Station::Oven, Tool::Bucket, Tool::Pot};
    actionToToolsReplaceables[(size_t)Action::Boil] = {0,0,1,1};
    actionToRoles[(size_t)Action::Boil] = {Role::Cook, Role::Firekeeper};
    actionToTools[(size_t)Action::Whittle] = {Tool::Knife};
    actionToRoles[(size_t)Action::Whittle] = {Role::Woodworker, Role::Carver};
    actionToTools[(size_t)Action::Knapp] = {Tool::Hammerstone, Tool::Chisel};
    actionToRoles[(size_t)Action::Knapp] = {Role::Knapper, Role::StoneWorker};
    actionToTools[(size_t)Action::Spin] = {Tool::Spindle, Tool::Distaff, Station::Spinner};
    actionToToolsReplaceables[(size_t)Action::Spin] = {0,0,-1};
    actionToRoles[(size_t)Action::Spin] = {Role::Spinner};
    actionToTools[(size_t)Action::Grind] = {Tool::Pestle};
    actionToRoles[(size_t)Action::Grind] = {Role::Apothecary};
    actionToTools[(size_t)Action::Preserve] = {Station::Keg, Station::MashTun, Tool::Pot};
    actionToRoles[(size_t)Action::Preserve] = {Role::Preserver};
    //NOTE: maybe change awl to optional
    actionToTools[(size_t)Action::LeatherCraft] = {Tool::Knife, Tool::Awl, Tool::Needle};
    actionToToolsReplaceables[(size_t)Action::LeatherCraft] = {0,1,2};
    actionToRoles[(size_t)Action::LeatherCraft] = {Role::Leathercrafter, Role::Cuirassier};
    actionToTools[(size_t)Action::Dip] = {Tool::MeltingPot};
    actionToRoles[(size_t)Action::Dip] = {Role::Chandler};
    actionToTools[(size_t)Action::CandleMould] = {Tool::CandleMould};
    actionToRoles[(size_t)Action::CandleMould] = {Role::Chandler};
    actionToTools[(size_t)Action::Lay] = {Tool::Spindle, Station::Spinner};
    actionToRoles[(size_t)Action::Lay] = {Role::Ropemaker};
    actionToTools[(size_t)Action::WoodCraft] = {Tool::Hammer, Tool::Mallet};
    actionToRoles[(size_t)Action::WoodCraft] = {Role::Woodworker};
    actionToTools[(size_t)Action::WheelCraft] = {Tool::Adze, Tool::Hammer, Tool::Chisel};
    actionToRoles[(size_t)Action::WheelCraft] = {Role::Wheelwright};
    actionToTools[(size_t)Action::CanoeCarve] = {Tool::Saw, Tool::Axe, Tool::Adze};
        actionToToolsReplaceables[(size_t)Action::CanoeCarve] = {0,0,1};
    actionToRoles[(size_t)Action::CanoeCarve] = {Role::CanoeCarver};
    actionToTools[(size_t)Action::BoatCraft] = {Tool::Mallet, Tool::MeasuringTools};
        actionToToolsReplaceables[(size_t)Action::BoatCraft] = {0,1};
    actionToRoles[(size_t)Action::BoatCraft] = {Role::BoatBuilder, Role::Shipwright};
    actionToTools[(size_t)Action::SiegeCraft] = {Tool::Mallet, Tool::Hammerstone, Tool::MeasuringTools};
        actionToToolsReplaceables[(size_t)Action::BoatCraft] = {0,1};
    actionToRoles[(size_t)Action::SiegeCraft] = {Role::SiegeEngineer};
    actionToTools[(size_t)Action::Engineer] = {Tool::Mallet, Tool::MeasuringTools};
    actionToToolsReplaceables[(size_t)Action::Engineer] = {-1,1};
    actionToRoles[(size_t)Action::Engineer] = {Role::Engineer};
    actionToTools[(size_t)Action::Wait] = {Tool::Bucket, Tool::Pot, Tool::Jar};
    actionToTools[(size_t)Action::Measure] = {Tool::MeasuringTools, Tool::Scale};
    actionToTools[(size_t)Action::Crush] = {Tool::Hammer, Tool::Hammerstone};
    //NOTE: maybe change awl to optional
    actionToTools[(size_t)Action::BowCraft] = {Tool::Knife, Tool::Adze, Tool::Awl, Tool::Drill};
    actionToToolsReplaceables[(size_t)Action::Engineer] = {0,1,2,3};
    actionToRoles[(size_t)Action::BowCraft] = {Role::Bowyer};
    actionToTools[(size_t)Action::MudbrickSculpt] = {Tool::Trowel, Tool::BrickMould};
    actionToToolsReplaceables[(size_t)Action::MudbrickSculpt] = {1, -2};
    actionToRoles[(size_t)Action::MudbrickSculpt] = {Role::MudbrickMaker};
    actionToTools[(size_t)Action::BrickSculpt] = {Tool::Trowel, Tool::BrickMould};
    actionToToolsReplaceables[(size_t)Action::BrickSculpt] = {1, -2};
    actionToRoles[(size_t)Action::BrickSculpt] = {Role::BrickMaker};
    actionToTools[(size_t)Action::Mash] = {Tool::Pestle, Station::Mill};
    actionToToolsReplaceables[(size_t)Action::Mash] = {1, 1};
    actionToRoles[(size_t)Action::Mash] = {Role::Brewer};
    //TODO: make sure this works
    actionToTools[(size_t)Action::Brew] = {Station::Cask};
    actionToRoles[(size_t)Action::Brew] = {Role::Brewer};
    actionToTools[(size_t)Action::OilMake] = {Station::Press};
    actionToRoles[(size_t)Action::OilMake] = {Role::OilMaker};
    //to do roles
    actionToTools[(size_t)Action::SculptMould] = {Station::ClaySculpture};
    actionToRoles[(size_t)Action::SculptMould] = {Role::Sculptor};
    actionToTools[(size_t)Action::Sew] = {Tool::Needle};
    actionToRoles[(size_t)Action::Sew] = {Role::Tailor};
    actionToRoles[(size_t)Action::Cur] = {Role::Butcher, Role::Tanner};
    actionToTools[(size_t)Action::Tan] = {Tool::Bucket, Tool::Pot};
    actionToTools[(size_t)Action::CandleCast] = {Tool::CandleMould};
    actionToRoles[(size_t)Action::CandleCast] = {Role::Chandler};
    actionToTools[(size_t)Action::StoneCarve] = {Tool::Chisel, Tool::Mallet, Tool::Scraper};
    actionToToolsReplaceables[(size_t)Action::StoneCarve] = {0,1,2};
    actionToTools[(size_t)Action::Mint] = {Tool::PatternedDie, Tool::PatternedDie, Tool::Mallet, Station::Furnace};
    actionToToolsReplaceables[(size_t)Action::Mint] = {0,1,2,3};
    actionToRoles[(size_t)Action::Mint] = {Role::Minter};

        //NON PRODUCT/RESOURCE
   actionToRoles[(size_t)Action::Tame] = {Role::HorseBreeder, Role::Shepherd, Role::Herder};
    actionToRoles[(size_t)Action::Command] = {Role::MilLeader, Role::Monarch, Role::Landowner};



#endif // ROLES_H_
