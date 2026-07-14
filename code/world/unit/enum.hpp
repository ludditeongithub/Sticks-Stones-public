#pragma once
#include "core/packed_enum.hpp"
#include <SDL2/SDL_pixels.h>
#include <cstdint>
#include <core/data.hpp>

constexpr size_t MATURITY_AGE = 15;

enum class Unit : uint8_t
{
	Child,
	Adult,
	Elder,
	MAX
};

enum class PlaceType
{
	Home,
	Work,
	Property,
	Collection,
	Delivery,
	Unload,
	Tend
};

//TODO: calligrapher, calligraphy art
enum class Role : uint8_t
{
	NONE,
	Apprentice,
	Student,
	// MELEE
	SpearHunter,
	MeleeSoldier,
	// RANGED
	// ARTIST
	Performer,
	Sculptor,
	WoodCarver,
	Musician,
	Bard,
	Poet,
	StoneCarver,
	Decorator,
	GlassArtist,
	Actor,
	Playwright,
	Painter,
	Writer,
	Storyteller,
	// SUPPORT
	// paleo
	Shaman,
	// meso
	// neo
	Plower,
	// copper
	Prostitute,
	Porter,
	CombatHealer,
	Landowner,
	Trader,
	ShipCaptain,
	Sailor,
	Negotiator,
	// bronze
	Carter,
	ChariotDriver,
	// iron
	Bureaucrat,
	ChariotRacer,
	MoneyLender,
	Merchant,
	Gladiator,
	// classical
	Factor,
	Administrator,
	FieldSurgeon,
	Judge,
	Lawyer,
	Teamster,
	TradeBaron,
	Veterinarian,
	Governor,
	Senator,
	Mariner,
	Curer,
	Banker,
	// medieval
	HeavyPlower,
	Tutor,
	HighPriest,
	SUPPORTMAX,
	// RESOURCE
	// paleo
	Scavenger,
	// meso
	FishHunter,
	Woodcutter,
	Gatherer,
	// neo
	Farmer,
	Herder,
	Shepherd,
	StoneMiner,
	Herbalist,
	Planter, // farmer is combination of planter and plower
	Harvester,
	// copper 
	CopperMiner,
	Fisherman,
	Beekeeper,
	Stoneworker,
	CerealFarmer,
	FlaxFarmer,
	HerbFarmer,
	Horticulturalist,
	TextileFarmer,	
	HorseBreeder,
	// iron, no fishmonger, no rancher, no vineyard worker,
	PapyrusHarvester,
	Rancher,
	IronMiner,
	OliveGrower,
	VineyardWorker,
	Vinter,
	// classical
	GoldMiner,
	SaltMiner,
	SilverMiner,
	LivestockFarmer,
	DairyFarmer,
	MasterFisher,
	// medieval
	CottonFarmer,
	GemstoneMiner,
	OrchardFarmer,
	HorseMaster,
	WoodFarmer,
	RESOURCEMAX,
	// PRODUCER
	// paleo: make hidecrafter roles
	Knapper,
	Carver,
	Firekeeper,
	HideCrafter,
	// meso: tanner = hidetanner
	CanoeCarver,
	BasketWeaver,
	Crafter,
	ShelterBuilder,
	Tanner,
	Ornamenter,
	Mixer,
	// neo
	ClayWorker,
	Butcher,
	Preserver,
	Weaver,
	Woodworker,
	Spinner,
	MudbrickMaker,
	StoneWorker,
	// copper
	CopperSmelter,
	Coppersmith,
	GrainGrinder,
	BoatBuilder,
	Bowyer,
	Fletcher,
	Leathercrafter,
	Priest,
	Brewer,
	// bronze note:  no stonemason, no tanner, wagon
	// maker = wheelwright, no wickerworker, wise man = philosopher
	SilverSmelter,
	GoldSmelter,
	Silversmith,
	Goldsmith,
	ParchmentMaker,
	GemCarver,
	Potter,
	Engineer,
	Baker,
	BrickMaker,
	BronzeSmelter,
	Bronzesmith,
	Provisioner,
	Stonemason,
	Builder,
	CharcoalMaker,
	Carpenter,
	Cook,
	Cuirassier,
	Wheelwright,
	Wickerworker,
	Scribe,
	// iron: no loom weaver,
	Matron,
	CandleMaker,
	IronSmelter,
	Ironsmith,
	OilMaker,
	PaperMaker,
	Shipwright,
	Apothecary,
	Glassworker,
	GlassMaker,
	LoomWeaver,
	// classical,
	Cartwright,
	Cheesemaker,
	Teacher,
	// chef, no philosopher
	Glassblower,
	Engraver,
	Minter,
	SiegeEngineer,
	SteelSmelter,
	SteelSmith,
	Founder,
	Surgeon,
	BrewMaster,
	KilnMaster,
	MasterBaker,
	MasterBowyer,
	MasterBuilder,
	MasterButcher,
	MasterCarpenter,
	MasterCraftsman,
	MasterCuirassier,
	MasterFletcher,
	MasterMason,
	MasterSpinner,
	Chef,
	// Medieval Monarch,
	MilLeader,
	Miller,
	Caretaker,
	Hauler,
	Dyer,
	Blacksmith,
	NavalEngineer,
	Steelsmith,
	Toolsmith,
	Weaponsmith,
	Chandler,
	Ropemaker,
	Tailor,
	Armorer,
	MasterWeaver,
	PRODUCTSMAX,
	// SUPPORTPRODUCER
	// RESEARCHER
	Elder,
	Scout,
	Philosopher,
	Envoy,
	Explorer,
	Navigator,
	Scholar,
	Chronicler,
	Spy,
	Historian,
	Mathematician,
	Cartographer,
	Diplomat,

	Librarian,
	Surveyor,
	BooksAcademicAny,
	BooksAcademicHistory,
	BooksAcademicPhilosophy,
	BooksAcademicMathematics,
	BooksAcademicNatural,
	// LEADER
	AdvisorFarming,
	AdvisorForeign,
	AdvisorNatural,
	AdvisorKnowledge,
	AdvisorOrderAdministrative,
	AdvisorOrderCulturalArtifact,
	AdvisorOrderCulturalPerformer,
	AdvisorOrderLegal,
	AdvisorStructures,
	AdvisorTrade,
	Chieftan,
	Prince,
	Architect,
	King,
	Emperor,
	Moneyer,
	CivilEngineer,
	Aristocrat,
	MiningEngineer,
	WagonMaster,
	MAX
};

float sunburn_level1_threshold = 0.3;
float sunburn_level2_threshold = 0.75;

struct SkinData {
	float melanin;
	float skin_warmth;
	float environmental_tan_offset;
        float sunburn;
};
