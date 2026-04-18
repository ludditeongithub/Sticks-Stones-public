#pragma once
#include "core/tables.hpp"
#include "world/tile/enum.hpp"
#include "world/unit/enum.hpp"
#include <world/buildable/enum.hpp>
#include <variant>
#include <vector>
#include <world/item/enum.hpp>
#include <world/progression/enum.hpp>
#include <core/combo_enum.hpp>

using Commodity = ConcatEnum<Item, Buildable, Knowledge, Order, Ritual>;

constexpr uint16_t ROLE_COMMODITY_JOB_AMOUNT = 4000;

template<typename... Cs>
constexpr auto mkv_commodity(Cs... cs) -> std::array<Commodity::underlying, sizeof...(Cs)> {
    return { Commodity::cast(cs)... };
}

//consider putting Material into commodity, which will determine possible material variants for all items if applicable. alternatively, pairs which include item and variant int8_t cast from material
// important: must be initialized in enum order!
inline constexpr RaggedLookupTable<Role, Commodity::underlying, ROLE_COMMODITY_JOB_AMOUNT,
				   Commodity::MAX>
    rolesToCommodities = []
{
	using u = Commodity::underlying;
	using enum Role;

	RaggedLookupTable<Role, u, ROLE_COMMODITY_JOB_AMOUNT, Commodity::MAX> lt{};

	lt.set(Performer, mkv_commodity(Ritual::Song));
	lt.set(Bard, mkv_commodity(Ritual::Song, Ritual::InstrumentalSong));
	lt.set(Sculptor,
	       mkv_commodity(Item::SmallSculpture, Buildable::MediumSculpture, Buildable::LargeSculpture));
	lt.set(Goldsmith, mkv_commodity(Item::Ring, Item::Earring, Item::Necklace, Item::Bracelet));
	lt.set(Poet, mkv_commodity(Ritual::Poem));
	lt.set(StoneCarver, mkv_commodity(Item::SmallCarving, Buildable::LargeCarving));
	lt.set(Actor, mkv_commodity(Ritual::Play));
	lt.set(Playwright, mkv_commodity(Item::PlayScript));
	lt.set(Musician, mkv_commodity(Ritual::InstrumentalSong));
	lt.set(Decorator, mkv_commodity(Item::SmallPaintedCarving, Item::SmallPaintedSculpture,
			      Buildable::MediumPaintedSculpture, Buildable::LargePaintedCarving));
	lt.set(Painter, mkv_commodity(Item::PaperPainting, Item::CanvasPainting));
	lt.set(WoodCarver, mkv_commodity(Item::SmallCarving, Buildable::LargeCarving, Buildable::WallCarving));
	lt.set(Storyteller, mkv_commodity(Ritual::Story));
	lt.set(GemCarver, mkv_commodity(Item::CutGem, Item::CutGreaterGem, Item::GemSeal));
	lt.set(Potter, mkv_commodity(Item::Pot));
	lt.set(GlassArtist, mkv_commodity(Item::PaintedGlass));
	lt.set(Writer, mkv_commodity(Item::Novel, Item::ShortStory, Item::Pamphlet));
	lt.set(Ornamenter, mkv_commodity(Item::Earring, Item::Ring, Item::Necklace, Item::Bracelet));
	lt.set(ClayWorker,
	       mkv_commodity(Item::Pot, Item::Jar, Item::BrickMould, Item::PikeHeadMould, Item::PikeHead, Item::HalberdHeadMould, Item::HalberdHead,
		   Item::GreataxeHeadMould, Item::GreataxeHead, Item::GreatswordHeadMould,
		   Item::SpearHeadMould, Item::PickaxeHeadMould, Item::AxeHeadMould,
		   Item::ShovelHeadMould, Item::SawHeadMould, Item::ArdHeadMould,
		   Item::ScytheHeadMould, Item::HandaxeHeadMould, Item::SwordHeadMould,
		   Item::MacheteHeadMould, Item::CleaverHeadMould, Item::TrowelHeadMould,
		   Item::ChiselHeadMould, Item::HammerHeadMould, Item::ScalpelHeadMould,
		   Item::MalletHeadMould, Item::AdzeHeadMould, Item::AwlHeadMould,
		   Item::SickleHeadMould, Item::KnifeHeadMould));
	lt.set(Prince, mkv_commodity(Ritual::LeaderSpeech));
	lt.set(Philosopher, mkv_commodity(Ritual::PublicTeaching, Ritual::Debate, Knowledge::Academic));
	lt.set(AdvisorKnowledge, mkv_commodity(Ritual::PublicTeaching, Ritual::Debate, Ritual::KnowledgeBoost, Item::Book, Knowledge::Academic, Knowledge::Technology));
	lt.set(Emperor, mkv_commodity(Ritual::LeaderSpeech, Ritual::Decree));
	lt.set(Moneyer, mkv_commodity(Item::Coins, Ritual::MinterBoost));
	lt.set(AdvisorStructures, mkv_commodity(Ritual::BlueprintOrder, Ritual::MonumentBlueprintOrder));
	lt.set(Architect, mkv_commodity(Ritual::BlueprintOrder, Ritual::BuilderBoost));
	lt.set(King, mkv_commodity(Ritual::Decree, Ritual::LeaderSpeech, Order::Cultural, Order::Legal, Order::Administrative));
	lt.set(AdvisorFarming, mkv_commodity(Ritual::AgricultureDecree, Order::Administrative));
	// TODO: continue from spreadsheet
	lt.set(AdvisorTrade, mkv_commodity(Ritual::TradeDecree, Order::Administrative));
	Bureaucrat, Order::Legal, Order::Administrative,
	    Knowledge::Units;
	// TODO: advisor medical
	AdvisorForeign, Knowledge::Foreign, Ritual::PeaceTreaty, Ritual::RequestAid,
	    Ritual::TradeOffer, Ritual::WarDeclaration, Ritual::FriendlyLetter;
	MiningEngineer, Buildable::Pulley, Buildable::BucketPump, Buildable::HydraulicPump,
	    Buildable::Siphon, Buildable::Waterwheel, Ritual::MinerBoost;
	WagonMaster, Ritual::TeamsterBoost;
	AdvisorOrderCulturalPerformer, Order::Cultural, Ritual::Song, Ritual::InstrumentalSong, Ritual::Poem;
	AdvisorOrderCulturalArtifact, Order::Cultural, Item::CanvasPainting, Buildable::LargeSculpture, Buildable::MediumSculpture, Item::SmallSculpture;
	Chieftan, Order::Cultural, Order::Administrative, Order::Legal, Ritual::Decree, Ritual::LeaderSpeech;
	Engineer, Buildable::CityGate, Buildable::StoneRoad, Buildable::ConcreteRoad, Buildable::BrickRoad, Buildable::Canal, Buildable::TallWall, Buildable::LargeDoor, Buildable::MiniGate, Buildable::Waterwheel, Buildable::Well, Buildable::Watchtower;
	CivilEngineer, Buildable::StoneRoad, Buildable::ConcreteRoad, Buildable::BrickRoad,
	    Buildable::Canal, Buildable::TallWall, Buildable::Waterwheel, Buildable::Well,
	    Buildable::Watchtower, Buildable::Aqueduct, Buildable::Bridge, Buildable::CityGate,
	    Buildable::CityWall;
// check if primitive rope, primitive sting should be paleo, TODO: more tools
	Crafter, Item::PrimitiveRope, Item::PrimitiveString, Item::HandDrill, Item::PrimitiveArrow, Buildable::TentSticks;
//TODO: cooking
	Firekeeper, Item::Soot, Buildable::PitFire, Item::Bone, Item::Sinew, Item::AnimalHair, Item::AnimalFat, Item::AnimalHides, Item::RawMeat;;
	Carver, Item::StickSpear, Item::HandDrill, Item::SmallHandle, Item::LargeHandle, Buildable::TentSticks;
	Knapper, Item::HandKnife, Item::HandChisel, Item::HandAxe, Item::Arrowhead, Item::SharpStone, Item::Hammerstone, Item::StickSpear, PrimitiveNeedle;
	HideCrafter, Item::Tribalwear, Buildable::TentCover, Item::PrimitiveSack, Item::Arrowhead;
	Butcher, Item::Bone, Item::Sinew, Item::AnimalHair, Item::AnimalFat, Item::AnimalHides, Item::RawMeat;
	Preserver, Item::Salt, Item::Vinegar, Item::PickledFruit, Item::PickledVegetable,
	    Item::SaltedCookedMeat, Item::SaltedRawMeat, Item::SaltedVegetable;
	StoneWorker, Item::Stone, Item::CrushedStone, Item::StoneTablet, Item::ToolHeadPlaceholder, Item::SolidWheel;
	Weaver, Item::Cloth, Item::DyedCloth, Item::DecorativeCloth;
	Woodworker, Item::Wood, Item::Plank, Item::LogBeam, Item::Beam;
	Spinner, Item::Thread, Item::Yarn, Item::String;
	BasketWeaver, Item::Basket, Item::LargeBasket;
	CanoeCarver, Buildable::Canoe;
	ShelterBuilder, Buildable::TentSticks, Buildable::WattleWall, Buildable::WattleRoof, Buildable::CobWall, Buildable::CobRoof;
	Tanner, Item::CuredHide, Item::TannedHide;
	Armorer, Item::Chainmail, Item::Breastplate, Item::Helmet, Item::Boots, Item::Bracers,
	    Item::Guards, Item::Gloves;
	Blacksmith, Item::Helmet, Item::Breastplate, Item::Boots, Item::Bracers, Item::Bracelet,
	    Item::Guards, Item::Gloves, Item::ToolHeadPlaceholder, Item::WeaponHeadPlaceholder, Item::Nail, Item::NailHeader,
	    Item::Peg, Item::Horseshoes, Item::Ring, Item::Rivet, Item::Axle, Item::LargeAxle,
	    Item::Jar, Item::Arrowhead;
	ParchmentMaker, Item::Parchment;
	SteelSmelter, Item::Ingot;
	Toolsmith, Item::ToolHeadPlaceholder, Item::ToolPlaceholder;
	Weaponsmith, Item::WeaponHeadPlaceholder, Item::WeaponPlaceholder;
	CandleMaker, Item::Wick, Item::Candle;
	Chandler, Item::Wick, Item::Candle;
	Glassblower, Item::Glass;
	IronSmelter, Item::Ingot;
	LoomWeaver, Item::Cloth, Item::DyedCloth, Item::DecorativeCloth;
	OilMaker, Item::CookingOil, Item::CornOil, Item::TruffleOil, Item::OliveOil;
	PaperMaker, Item::Paper;
	Shipwright, Buildable::Canoe, Buildable::Sailboat, Buildable::LargeSailboat, Buildable::Longboat, Buildable::LightWarship, Buildable::Cog;
	Vinter, Item::Wine, Item::FruitWine;
	BoatBuilder, Buildable::Canoe, Buildable::Sailboat, Buildable::LargeSailboat;
	Bowyer, Item::Bow, Item::Crossbow, Item::Longbow;
	Brewer, Item::Beer, Item::Vinegar, Item::Mead, Item::SugarJuice, Item::Cider;
	Coppersmith, Item::Helmet, Item::Breastplate, Item::Boots, Item::Bracers, Item::Bracelet,
	    Item::Guards,  Item::ToolHeadPlaceholder, Item::WeaponHeadPlaceholder, Item::Nail, Item::NailHeader,
	    Item::Peg, Item::Horseshoes, Item::Ring, Item::Rivet, Item::Axle, Item::LargeAxle,
	    Item::Jar, Item::Arrowhead;
	Fletcher, Item::Arrow, Item::ArrowShaft, Item::Arrowhead; //TODO: only bone variants for arrowhead
	Leathercrafter, Item::Satchel, Item::LargeSatchel, Item::Gambeson, Item::Coat, Item::Gloves, Item::Boots, Item::Bracers;
	MudbrickMaker, Item::Cob;
 	GrainGrinder, Item::Flour, Item::MilledRice;
	Miller, Item::MilledRice, Item::Flour;
	Cartwright, Buildable::WheeledCart, Buildable::WheeledWagon, Buildable::WheeledChariot;
	Cheesemaker, Item::Cheese, Item::BlueCheese, Item::GoatCheese;
	Engraver, Item::Die, Item::EngravedRing, Item::EngravedBracelet;
	Glassblower, Item::Bottle, Item::Jar, Item::Earring, Item::Ring, Item::Bracelet, Item::Tube, Item::Pane, Item::Vase;
	Minter, Item::Coins;
	Baker, Item::Bread, Item::Pastry, Item::Pie;
	BrickMaker, Item::Bricks;
	BronzeSmelter, Item::Ingot;
	Builder, Buildable::BrickRoad, Buildable::TentSticks, Buildable::WattleWall,
	    Buildable::CobRoof, Buildable::CobWall, Buildable::Wall, Buildable::TallWall,
	    Buildable::CityWall, Buildable::WallPanel, Buildable::Fence, Buildable::Gate,
	    Buildable::CityGate, Buildable::Arch, Buildable::Aqueduct, Buildable::WoodBridge,
	    Buildable::BrickBridge, Buildable::StoneBridge, Buildable::Dam, Buildable::LargeCanal,
	    Buildable::MiniGate, Buildable::LargeDoor, Buildable::Pillar, Buildable::Watchtower,
	    Buildable::PitFire, Buildable::TentCover, Buildable::WattleRoof, Buildable::RoofBeams,
	    Buildable::Roof, Buildable::Window, Buildable::PaintedWindow, Buildable::Foundation,
	    Buildable::Floor, Buildable::Carpet, Buildable::PlowedDirt, Buildable::Path,
	    Buildable::StoneRoad, Buildable::BrickRoad, Buildable::ConcreteRoad,
	    Buildable::DugCanal, Buildable::Canal, Buildable::Well;
	Carpenter, Item::Wood, Item::Plank, Item::JoinedPlank, Item::Peg, Item::LogBeam, Item::Beam,
	    Item::Timber;
	CharcoalMaker, Item::Charcoal, Item::Ash;
	Cook, Item::DrinkingWater; // TODO: consumables
	Cuirassier, Item::Satchel, Item::LargeSatchel, Item::Gambeson, Item::Coat, Item::Gloves, Item::Boots, Item::HorseSaddle, Item::OxSaddle, Item::Bracers; // TODO: more leather items, differentiate with leather crafter
	Provisioner, Item::Salt, Item::Vinegar, Item::PickledFruit, Item::PickledVegetable,
	    Item::SaltedCookedMeat, Item::SaltedRawMeat, Item::SaltedVegetable;
	Stonemason, Item::CurvedStone, Item::ToolHeadPlaceholder, Item::Stone, Item::CrushedStone,
	    Item::CurvedStone, Item::CutStone, Item::CutStoneSheet, Item::StoneTablet,
	    Item::ToolHeadPlaceholder, Item::SolidWheel;
	Wickerworker, Item::Basket, Item::LargeBasket;
	Bronzesmith, Item::Helmet, Item::Breastplate, Item::Boots, Item::Bracers, Item::Bracelet,
	    Item::Guards, Item::Gloves, Item::ToolHeadPlaceholder, Item::WeaponHeadPlaceholder,
	    Item::Nail, Item::NailHeader, Item::Peg, Item::Horseshoes, Item::Ring, Item::Rivet,
	    Item::Axle, Item::LargeAxle, Item::Jar, Item::Arrowhead;
	Chronicler, Item::Scroll, Item::Book, Order::Cultural, Knowledge::Academic;
	Scholar, Item::Scroll, Item::Book;
	Apothecary, Item::MedicinalSoap, Item::BlueDye, Item::RedDye, Item::YellowDye, Item::Poison,
	    Item::Cyanide, Item::Arsenic, Item::Hemlock, Item::Bandage, Item::Laxative,
	    Item::MedicinalSoap, Item::GileadBalm, Item::Theriac;
	Historian, Item::Scroll, Item::Book, Order::Cultural, Knowledge::Academic;
	Mathematician, Item::Scroll, Item::Book,
	    Knowledge::Academic; // TODO: perhaps divide up academics
	SiegeEngineer, Buildable::BatteringLog, Buildable::BatteringRam, Buildable::Trebuchet, Buildable::Ballista, Buildable::Catapult, Buildable::SiegeLadder, Buildable::SiegeTower;
	NavalEngineer, Buildable::Canoe, Buildable::Sailboat, Buildable::LargeSailboat,
	    Buildable::Longboat, Buildable::LightWarship, Buildable::Cog, Buildable::HeavyWarship,
	    Buildable::Freighter;
	Priest, Item::Incense, Order::Cultural;
	Librarian, Item::Book, Item::Scroll, Knowledge::Academic, Knowledge::Exploration, Knowledge::Foreign, Knowledge::Units, Knowledge::Technology;
	Scribe, Item::Scroll, Item::Book, Order::Legal, Knowledge::Academic;
	MasterWeaver, 
	return lt;
}();

inline constexpr RaggedLookupTable<Role, Material, total-element-size, max-enum-size>
roleToVariants = []
	{
		using enum Role;

		RaggedLookupTable<Role, Material, total-element-size, max-enum-size> lt{};

		return lt;
	}
