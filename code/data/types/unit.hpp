#pragma once
#include "core/packed_enum.hpp"
#include <core/random.hpp>
#include <SDL2/SDL_pixels.h>
#include <cstdint>
#include <array>
#include <data/types/stats.hpp>
#include <data/types/container.hpp>
#include <data/const/unit_data.hpp>

enum class Unit : uint8_t
{
		NONE,
	// GreenEyesRedHair,
	// BlueEyesRedHair,
	// BrownEyesRedHair,
	// BlueEyesBlondeHair,
	// GreenEyesBlondeHair,
	// BrownEyesBlondeHair,
	// GreenEyesBrownHair,
	BlueEyesBrownHair,
	// BrownEyesBrownHair,
	// GreenEyesBlackHair,
	// BlueEyesBlackHair,
	// BrownEyesBlackHair,
	MAX
};

enum class UnitStage : uint8_t{
	NONE,
	Child,
	Adult,
	Elder,
	MAX
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

struct SkinData {
	float melanin;
	float skin_warmth;
	float environmental_tan_offset;
    float sunburn;
};

struct Inventory
{
	static constexpr uint16_t CONTAINER_UNDERFLOW_LIMIT = 3;
	// anything inside containers over the OVERFLOW is put into overflow vector and accessed through indirection. for memory optimization	
	// TODO
	//  std::variant<ItemSlot, VariantItemSlot, ToolSlot> left_hand;
	//  std::variant<ItemSlot, VariantItemSlot, ToolSlot> right_hand;
	std::array<Container, CONTAINER_UNDERFLOW_LIMIT> containers; // first container is HANDS
	BulkStatus bulk_status = BulkStatus::NONE;		     // for hands
	float weight;
	Inventory()
	{
		containers[0].type = ContainerType::Hands;
		weight = 0;
	}

	bool attempt_hold(Item item) {}
};

struct Skills
{
	Strength strength;
	Athleticism athleticism;
	Dexterity dexterity;
	Intellect intellect;
	Memory memory;
	Perception perception;
	Creativity creativity;
	Charisma charisma;
	Determination determination;

	uint8_t get_random_starting_skill()
	{
		return static_cast<uint8_t>(STARTING_SKILL_MAX * random_chance->next());
	}

	Skills()
	{
		strength = get_random_starting_skill();
		athleticism = get_random_starting_skill();
		dexterity = get_random_starting_skill();
		intellect = get_random_starting_skill();
		perception = get_random_starting_skill();
		creativity = get_random_starting_skill();
		charisma = get_random_starting_skill();
		determination = get_random_starting_skill();
	}
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

// places that units own or participate in.
struct Place
{
	Coord pos;
	PlaceType type;
};

using Roles = std::array<Role, MAX_ROLES>;
using RoleMana = uint8_t;
using Places = std::array<Place, 3>;
