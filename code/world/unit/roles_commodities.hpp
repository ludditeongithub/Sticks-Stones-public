#pragma once
#include "core/tables.hpp"
#include <world/plant/enum.hpp>
#include <world/animal/enum.hpp>
#include "world/unit/enum.hpp"
#include <world/buildable/enum.hpp>
#include <world/item/enum.hpp>
#include <world/progression/enum.hpp>
#include <core/combo_enum.hpp>

using Commodity = ConcatEnum<Item, Buildable, knowledge::Category, order::Category, Ritual, PlantCategory, Animal>;  

constexpr uint16_t ROLE_COMMODITY_JOB_AMOUNT = 4000;

//consider putting Material into commodity, which will determine possible material variants for all items if applicable. alternatively, pairs which include item and variant int8_t cast from material
// important: must be initialized in enum order!
inline const RaggedLookupTable<Role, Commodity::Variant> roles_to_commodities = []
{
	using enum Role;

	RaggedLookupTable<Role, Commodity::Variant> lt{};

	lt.set(Performer, {Ritual::Song});
	lt.set(Bard, {Ritual::Song, Ritual::InstrumentalSong});
	lt.set(Sculptor,
	       {Item::SmallSculpture, Buildable::MediumSculpture, Buildable::LargeSculpture});
	lt.set(Goldsmith, {Item::Ring, Item::Earring, Item::Necklace, Item::Bracelet});
	lt.set(Poet, {Ritual::Poem});
	lt.set(StoneCarver, {Item::SmallCarving, Buildable::LargeCarving});
	lt.set(Actor, {Ritual::Play});
	lt.set(Playwright, {Item::PlayScript});
	lt.set(Musician, {Ritual::InstrumentalSong});
	lt.set(Decorator, {Item::SmallPaintedCarving, Item::SmallPaintedSculpture,
					   Buildable::MediumPaintedSculpture, Buildable::LargePaintedCarving});
	lt.set(Painter, {Item::PaperPainting, Item::CanvasPainting});
	lt.set(WoodCarver, {Item::SmallCarving, Buildable::LargeCarving, Buildable::WallCarving});
	lt.set(Storyteller, {Ritual::Story});
	lt.set(GemCarver, {Item::CutGem, Item::CutGreaterGem, Item::GemSeal});
	lt.set(Potter, {Item::Pot});
	lt.set(GlassArtist, {Item::PaintedGlass});
	lt.set(Writer, {Item::Novel, Item::ShortStory, Item::Pamphlet});
	lt.set(Ornamenter, {Item::Earring, Item::Ring, Item::Necklace, Item::Bracelet});
	lt.set(ClayWorker,
	       {Item::Pot, Item::Jar, Item::BrickMould, Item::PikeHeadMould, Item::PikeHead, Item::HalberdHeadMould, Item::HalberdHead,
		   Item::GreataxeHeadMould, Item::GreataxeHead, Item::GreatswordHeadMould,
		   Item::SpearHeadMould, Item::PickaxeHeadMould, Item::AxeHeadMould,
		   Item::ShovelHeadMould, Item::SawHeadMould, Item::ArdHeadMould,
		   Item::ScytheHeadMould, Item::HandaxeHeadMould, Item::SwordHeadMould,
		   Item::MacheteHeadMould, Item::CleaverHeadMould, Item::TrowelHeadMould,
		   Item::ChiselHeadMould, Item::HammerHeadMould, Item::ScalpelHeadMould,
		   Item::MalletHeadMould, Item::AdzeHeadMould, Item::AwlHeadMould,
		   Item::SickleHeadMould, Item::KnifeHeadMould});
	lt.set(Prince, {Ritual::LeaderSpeech});
	lt.set(Philosopher, {Ritual::PublicTeaching, Ritual::Debate, knowledge::Category::Academic});
	lt.set(Advisorknowledge::Category, {Ritual::PublicTeaching, Ritual::Debate, Ritual::knowledge::CategoryBoost, Item::Book, knowledge::Category::Academic, knowledge::Category::Technology});
	lt.set(Emperor, {Ritual::LeaderSpeech, Ritual::Decree});
	lt.set(Moneyer, {Item::Coins, Ritual::MinterBoost});
	lt.set(AdvisorStructures, {Ritual::BlueprintOrder, Ritual::MonumentBlueprintOrder});
	lt.set(Architect, {Ritual::BlueprintOrder, Ritual::BuilderBoost});
	lt.set(King, {Ritual::Decree, Ritual::LeaderSpeech, order::Category::Cultural, order::Category::Legal, order::Category::Administrative});
	lt.set(AdvisorFarming, {Ritual::AgricultureDecree, order::Category::Administrative});
	lt.set(AdvisorTrade, {Ritual::SingleTradeContract, Ritual::RepeatTradeContract, Ritual::CreateTariff, order::Category::Administrative});
	lt.set(Bureaucrat, {order::Category::Legal, order::Category::Administrative, knowledge::Category::Units});
	// TODO: advisor medical
	lt.set(AdvisorForeign, {knowledge::Category::Foreign, Ritual::PeaceTreaty, Ritual::RequestAid, Ritual::TradeOffer, Ritual::WarDeclaration, Ritual::FriendlyLetter});
	lt.set(MiningEngineer, {Buildable::Pulley, Buildable::BucketPump, Buildable::HydraulicPump, Buildable::Siphon, Buildable::Waterwheel, Ritual::MinerBoost});
	lt.set(WagonMaster, {Ritual::TeamsterBoost});
	lt.set(AdvisorOrderCulturalPerformer, {order::Category::Cultural, Ritual::Song, Ritual::InstrumentalSong, Ritual::Poem});
	lt.set(AdvisorOrderCulturalArtifact, {order::Category::Cultural, Item::CanvasPainting, Buildable::LargeSculpture, Buildable::MediumSculpture, Item::SmallSculpture});
	lt.set(Chieftan, {order::Category::Cultural, order::Category::Administrative, order::Category::Legal, Ritual::Decree, Ritual::LeaderSpeech});
	lt.set(Engineer, {Buildable::CityGate, Buildable::StoneRoad, Buildable::ConcreteRoad, Buildable::BrickRoad, Buildable::Canal, Buildable::TallWall, Buildable::LargeDoor, Buildable::MiniGate, Buildable::Waterwheel, Buildable::Well, Buildable::Watchtower});
	lt.set(CivilEngineer, {Buildable::StoneRoad, Buildable::ConcreteRoad, Buildable::BrickRoad, Buildable::Canal, Buildable::TallWall, Buildable::Waterwheel, Buildable::Well, Buildable::Watchtower, Buildable::Aqueduct, Buildable::WoodBridge, Buildable::StoneBridge, Buildable::BrickBridge, Buildable::CityGate, Buildable::CityWall});
// check if primitive rope, primitive sting should be paleo, TODO: more tools
lt.set(Crafter, {Item::PrimitiveRope, Item::PrimitiveString, Item::HandDrill, Item::PrimitiveArrow, Buildable::TentSticks});
//TODO: cooking
lt.set(Firekeeper, {Item::Soot, Buildable::PitFire, Item::Bone, Item::Sinew, Item::AnimalHair, Item::AnimalFat, Item::AnimalHides, Item::RawMeat});
lt.set(Carver, {Item::StickSpear, Item::HandDrill, Item::SmallHandle, Item::LargeHandle, Buildable::TentSticks});
lt.set(Knapper, {Item::HandKnife, Item::HandChisel, Item::HandAxe, Item::Arrowhead, Item::SharpStone, Item::Hammerstone, Item::StickSpear, Item::PrimitiveNeedle});
lt.set(HideCrafter, {Item::Tribalwear, Buildable::TentCover, Item::PrimitiveSack, Item::Arrowhead});
lt.set(Butcher, {Item::Bone, Item::Sinew, Item::AnimalHair, Item::AnimalFat, Item::AnimalHides, Item::RawMeat});
lt.set(Preserver, {Item::Salt, Item::Vinegar, Item::PickledFruit, Item::PickledVegetable, Item::SaltedCookedMeat, Item::SaltedRawMeat, Item::SaltedVegetable});
lt.set(StoneWorker, {Item::Stone, Item::CrushedStone, Item::StoneTablet, Item::ToolHeadPlaceholder, Item::SolidWheel});
lt.set(Weaver, {Item::Cloth, Item::DyedCloth, Item::DecorativeCloth});
lt.set(Woodworker, {Item::Wood, Item::Plank, Item::LogBeam, Item::Beam});
lt.set(Spinner, {Item::Thread, Item::Yarn, Item::String});
lt.set(BasketWeaver, {Item::Basket, Item::LargeBasket});
lt.set(CanoeCarver, {Buildable::Canoe});
lt.set(ShelterBuilder, {Buildable::TentSticks, Buildable::WattleWall, Buildable::WattleRoof, Buildable::CobWall, Buildable::CobRoof});
lt.set(Tanner, {Item::CuredHide, Item::TannedHide});
lt.set(Armorer, {Item::Chainmail, Item::Breastplate, Item::Helmet, Item::Boots, Item::Bracers, Item::Guards, Item::Gloves});
lt.set(Blacksmith, {Item::Helmet, Item::Breastplate, Item::Boots, Item::Bracers, Item::Bracelet, Item::Guards, Item::Gloves, Item::ToolHeadPlaceholder, Item::WeaponHeadPlaceholder, Item::Nail, Item::NailHeader, Item::Peg, Item::Horseshoes, Item::Ring, Item::Rivet, Item::Axle, Item::LargeAxle, Item::Jar, Item::Arrowhead});
lt.set(ParchmentMaker, {Item::Parchment});
lt.set(SteelSmelter, {Item::Ingot});
lt.set(Toolsmith, {Item::ToolHeadPlaceholder, Item::ToolPlaceholder});
lt.set(Weaponsmith, {Item::WeaponHeadPlaceholder, Item::WeaponPlaceholder});
lt.set(CandleMaker, {Item::Wick, Item::Candle});
lt.set(Chandler, {Item::Wick, Item::Candle});
lt.set(Glassblower, {Item::Glass});
lt.set(IronSmelter, {Item::Ingot});
lt.set(LoomWeaver, {Item::Cloth, Item::DyedCloth, Item::DecorativeCloth});
lt.set(OilMaker, {Item::CookingOil, Item::CornOil, Item::TruffleOil, Item::OliveOil});
lt.set(PaperMaker, {Item::Paper});
lt.set(Shipwright, {Buildable::Canoe, Buildable::Sailboat, Buildable::LargeSailboat, Buildable::Longboat, Buildable::LightWarship, Buildable::Cog});
lt.set(Vinter, {Item::Wine, Item::FruitWine});
lt.set(BoatBuilder, {Buildable::Canoe, Buildable::Sailboat, Buildable::LargeSailboat});
lt.set(Bowyer, {Item::Bow, Item::Crossbow, Item::Longbow});
lt.set(Brewer, {Item::Beer, Item::Vinegar, Item::Mead, Item::SugarJuice, Item::Cider});
lt.set(Coppersmith, {Item::Helmet, Item::Breastplate, Item::Boots, Item::Bracers, Item::Bracelet, Item::Guards,  Item::ToolHeadPlaceholder, Item::WeaponHeadPlaceholder, Item::Nail, Item::NailHeader, Item::Peg, Item::Horseshoes, Item::Ring, Item::Rivet, Item::Axle, Item::LargeAxle, Item::Jar, Item::Arrowhead});
lt.set(Fletcher, {Item::Arrow, Item::ArrowShaft, Item::Arrowhead}); //TODO: only bone variants for arrowhead
lt.set(Leathercrafter, {Item::Satchel, Item::LargeSatchel, Item::Gambeson, Item::Coat, Item::Gloves, Item::Boots, Item::Bracers});
lt.set(MudbrickMaker, {Item::Cob});
lt.set(GrainGrinder, {Item::Flour, Item::MilledRice});
lt.set(Miller, {Item::MilledRice, Item::Flour});
lt.set(Cartwright, {Buildable::WheeledCart, Buildable::WheeledWagon, Buildable::WheeledChariot});
lt.set(Cheesemaker, {Item::Cheese, Item::BlueCheese, Item::GoatCheese});
lt.set(Engraver, {Item::Die, Item::EngravedRing, Item::EngravedBracelet});
lt.set(Glassblower, {Item::Bottle, Item::Jar, Item::Earring, Item::Ring, Item::Bracelet, Item::Tube, Item::Pane, Item::Vase});
lt.set(Minter, {Item::Coins});
lt.set(Baker, {Item::Bread, Item::Pastry, Item::Pie});
lt.set(BrickMaker, {Item::Bricks});
lt.set(BronzeSmelter, {Item::Ingot});
	//TODO: differentiate between activities builder can contribute to, and ones he can initiate
	lt.set(Builder, {Buildable::BrickRoad, Buildable::TentSticks, Buildable::WattleWall, Buildable::CobRoof, Buildable::CobWall, Buildable::Wall, Buildable::TallWall,  Buildable::CityWall, Buildable::WallPanel, Buildable::Fence, Buildable::Gate, Buildable::CityGate, Buildable::Arch, Buildable::Aqueduct, Buildable::WoodBridge, Buildable::BrickBridge, Buildable::StoneBridge, Buildable::Dam, Buildable::LargeCanal, Buildable::MiniGate, Buildable::LargeDoor, Buildable::Pillar, Buildable::Watchtower, Buildable::PitFire, Buildable::TentCover, Buildable::WattleRoof, Buildable::RoofBeams, Buildable::Roof, Buildable::Window, Buildable::PaintedWindow, Buildable::Foundation, Buildable::Floor, Buildable::Carpet, Buildable::PlowedDirt, Buildable::Path, Buildable::StoneRoad, Buildable::BrickRoad, Buildable::ConcreteRoad, Buildable::DugCanal, Buildable::Canal, Buildable::Well});
	lt.set(Carpenter, {Item::Wood, Item::Plank, Item::JoinedPlank, Item::Peg, Item::LogBeam, Item::Beam, Item::Timber});
	lt.set(CharcoalMaker, {Item::Charcoal, Item::Ash});
	lt.set(Cook, {Item::DrinkingWater}); // TODO: consumables
	lt.set(Cuirassier, {Item::Satchel, Item::LargeSatchel, Item::Gambeson, Item::Coat, Item::Gloves, Item::Boots, Item::HorseSaddle, Item::OxSaddle, Item::Bracers}); // TODO: more leather items, differentiate with leather crafter
	lt.set(Provisioner, {Item::Salt, Item::Vinegar, Item::PickledFruit, Item::PickledVegetable, Item::SaltedCookedMeat, Item::SaltedRawMeat, Item::SaltedVegetable});
	lt.set(Stonemason, {Item::CurvedStone, Item::ToolHeadPlaceholder, Item::Stone, Item::CrushedStone,  Item::CurvedStone, Item::CutStone, Item::CutStoneSheet, Item::StoneTablet, Item::ToolHeadPlaceholder, Item::SolidWheel});
	lt.set(Wickerworker, {Item::Basket, Item::LargeBasket});
	lt.set(Bronzesmith, {Item::Helmet, Item::Breastplate, Item::Boots, Item::Bracers, Item::Bracelet, Item::Guards, Item::Gloves, Item::ToolHeadPlaceholder, Item::WeaponHeadPlaceholder, Item::Nail, Item::NailHeader, Item::Peg, Item::Horseshoes, Item::Ring, Item::Rivet, Item::Axle, Item::LargeAxle, Item::Jar, Item::Arrowhead});
	lt.set(Chronicler, {Ritual::HistoryText, Ritual::Chronicle, order::Category::Cultural, knowledge::Category::Academic});
	lt.set(Scholar, {Item::Scroll, Item::Book, Ritual::HistoryText, Ritual::LawText, Ritual::PhilosophyText});
	lt.set(Apothecary, {Item::MedicinalSoap, Item::BlueDye, Item::RedDye, Item::YellowDye, Item::Poison, Item::Cyanide, Item::Arsenic, Item::Hemlock, Item::Bandage, Item::Laxative, Item::MedicinalSoap, Item::GileadBalm, Item::Theriac});
	lt.set(Historian, {order::Category::Cultural, knowledge::Category::Academic, Ritual::HistoryText});
	lt.set(Mathematician, {Ritual::MathematicsText, knowledge::Category::Academic}); // TODO: perhaps divide up academics
	lt.set(SiegeEngineer, {Buildable::BatteringLog, Buildable::BatteringRam, Buildable::Trebuchet, Buildable::Ballista, Buildable::Catapult, Buildable::SiegeLadder, Buildable::SiegeTower});
	lt.set(NavalEngineer, {Buildable::Canoe, Buildable::Sailboat, Buildable::LargeSailboat, Buildable::Longboat, Buildable::LightWarship, Buildable::Cog, Buildable::HeavyWarship, Buildable::Freighter});
	lt.set(Priest, {Item::Incense, order::Category::Cultural});
	lt.set(Librarian, {Item::Book, Item::Scroll, Ritual::ReviewTexts, knowledge::Category::Academic, knowledge::Category::Exploration, knowledge::Category::Foreign, knowledge::Category::Units, knowledge::Category::Technology});
	lt.set(Scribe, {Item::Scroll, Item::Book, order::Category::Legal, knowledge::Category::Academic});
	lt.set(MasterWeaver, {Item::Cloth, Item::DyedCloth, Item::DecorativeCloth, Ritual::WeaverBoost});
	lt.set(MasterBaker, {Item::Bread, Item::Pastry, Item::Pie, Ritual::BakerBoost});
	lt.set(MasterBuilder, {Buildable::BrickRoad, Buildable::TentSticks, Buildable::WattleWall, Buildable::CobRoof, Buildable::CobWall, Buildable::Wall, Buildable::TallWall, Buildable::CityWall, Buildable::WallPanel, Buildable::Fence, Buildable::Gate, Buildable::CityGate, Buildable::Arch, Buildable::Aqueduct, Buildable::WoodBridge, Buildable::BrickBridge, Buildable::StoneBridge, Buildable::Dam, Buildable::LargeCanal, Buildable::MiniGate, Buildable::LargeDoor, Buildable::Pillar, Buildable::Watchtower, Buildable::PitFire, Buildable::TentCover, Buildable::WattleRoof, Buildable::RoofBeams, Buildable::Roof, Buildable::Window, Buildable::PaintedWindow, Buildable::Foundation,Buildable::Floor, Buildable::Carpet, Buildable::PlowedDirt, Buildable::Path, Buildable::StoneRoad, Buildable::BrickRoad, Buildable::ConcreteRoad, Buildable::DugCanal, Buildable::Canal, Buildable::Well, Ritual::BuilderBoost});
 	lt.set(MasterCarpenter, {Item::Wood, Item::Plank, Item::JoinedPlank, Item::Peg, Item::LogBeam, Item::Beam, Item::Timber, Ritual::CarpenterBoost});
	lt.set(MasterCraftsman, {Item::PrimitiveRope, Item::PrimitiveString, Item::HandDrill, Item::PrimitiveArrow, Buildable::TentSticks, Ritual::CraftsmanBoost});
	lt.set(MasterCuirassier, {Item::Satchel, Item::LargeSatchel, Item::Gambeson, Item::Coat, Item::Gloves, Item::Boots, Item::HorseSaddle, Item::OxSaddle, Item::Bracers, Ritual::CuraisserBoost});
	lt.set(MasterFletcher, {Item::Arrow, Item::ArrowShaft, Item::Arrowhead, Ritual::FletcherBoost});
	lt.set(MasterMason, {Item::CurvedStone, Item::ToolHeadPlaceholder, Item::Stone, Item::CrushedStone, Item::CurvedStone, Item::CutStone, Item::CutStoneSheet, Item::StoneTablet, Item::ToolHeadPlaceholder, Item::SolidWheel});
	lt.set(Chef, {Item::DrinkingWater}); // TODO
	lt.set(Elder, {knowledge::Category::Technology, knowledge::Category::Units, knowledge::Category::Academic, Ritual::InitiationRitual});
	lt.set(Scout, {knowledge::Category::Exploration, Ritual::Explore});
	lt.set(Negotiator, {Ritual::WarDeclaration, Ritual::PeaceTreaty, Ritual::TradeOffer, Ritual::RequestAid, Ritual::RequestAlliance, Ritual::RequestUnion});
	lt.set(Surveyor, {knowledge::Category::Foreign, Ritual::FindMine});
	lt.set(Spy, {knowledge::Category::Foreign, Ritual::BuildSpyNetwork, Ritual::CounterSpy});
	lt.set(Cartographer, {Item::Map, Ritual::MakeMap});
	lt.set(Diplomat, {knowledge::Category::Foreign, Ritual::WarDeclaration, Ritual::PeaceTreaty, Ritual::TradeOffer, Ritual::RequestAid, Ritual::RequestAlliance, Ritual::RequestUnion, Ritual::CurryFavor, Ritual::EncourageWar, Ritual::GatherSpecificForeignInfo});
	lt.set(Envoy, {knowledge::Category::Foreign, Ritual::WarDeclaration, Ritual::PeaceTreaty, Ritual::TradeOffer, Ritual::RequestAid, Ritual::RequestAlliance, Ritual::RequestUnion, Ritual::CurryFavor});
	lt.set(Explorer, {knowledge::Category::Exploration, Ritual::Explore, Ritual::Chart});
	lt.set(Navigator, {knowledge::Category::Exploration, Ritual::Explore, Ritual::Chart});
	lt.set(Philosopher, {knowledge::Category::Technology, knowledge::Category::Units, knowledge::Category::Academic, order::Category::Cultural, Ritual::Debate, Ritual::PublicTeaching, Ritual::PhilosophyText, Ritual::LawText, Ritual::MathematicsText});
	lt.set(Herder, {Item::Corpse, Item::Milk});
	lt.set(Shepherd, {Item::Corpse, Item::GoatMilk});
	lt.set(StoneMiner, {Item::Stone, Item::Lime});
	lt.set(FishHunter, {Item::Fish, Item::Shellfish}); //TODO: is this right, or animal?
	lt.set(Woodcutter, {Item::Wood});
	lt.set(CottonFarmer, {PlantCategory::Textile});
	lt.set(GemstoneMiner, {Item::Gem, Item::GreaterGem});
	lt.set(Fisherman, {Item::Fish, Item::Shellfish});
	lt.set(IronMiner, {Item::Ore});
	lt.set(OliveGrower, {PlantCategory::Olive});
	lt.set(PapyrusHarvester, {PlantCategory::Textile});
	lt.set(Rancher, {Animal::Cow, Animal::Sheep, Animal::Pig, Animal::Chicken, Animal::Goat, Animal::Camel, Item::Milk, Item::Wool, Item::ChickenEgg});
	lt.set(VineyardWorker, {PlantCategory::Grapevine});
	lt.set(Harvester, {PlantCategory::BerryShrub, PlantCategory::FruitVeggie, PlantCategory::Flowering, PlantCategory::Leafy, PlantCategory::Root, PlantCategory::Reed,  PlantCategory::Bulb, PlantCategory::Grain, PlantCategory::Herb, PlantCategory::Bush, PlantCategory::Citrus, PlantCategory::Stone, PlantCategory::Pome});
	lt.set(Planter, {PlantCategory::BerryShrub, PlantCategory::FruitVeggie, PlantCategory::Flowering, PlantCategory::Leafy, PlantCategory::Root, PlantCategory::Reed,  PlantCategory::Bulb, PlantCategory::Grain, PlantCategory::Herb, PlantCategory::Bush, PlantCategory::Citrus, PlantCategory::Stone, PlantCategory::Pome});
	lt.set(DairyFarmer, {Item::Milk, Item::GoatMilk, Animal::Goat, Animal::Cow});
	lt.set(GoldMiner, {Item::Ore});
	lt.set(LivestockFarmer, {Animal::Cow, Animal::Sheep, Animal::Chicken, Animal::Goat, Animal::Horse, Animal::Camel});
	lt.set(SaltMiner, {Item::Salt});
	lt.set(SilverMiner, {Item::Ore});
	lt.set(Beekeeper, {Item::Honey, Item::Wax});
	lt.set(CerealFarmer, {PlantCategory::Grain});
	lt.set(HerbFarmer, {PlantCategory::Herb});
	lt.set(HorseBreeder, {Animal::Horse});
	lt.set(Horticulturalist, {PlantCategory::FruitVeggie, PlantCategory::Succulent, PlantCategory::Flowering, PlantCategory::Leafy, PlantCategory::Bulb});
	lt.set(OrchardFarmer, {PlantCategory::Citrus, PlantCategory::Stone, PlantCategory::Pome, PlantCategory::BerryShrub});
	lt.set(Herbalist, {PlantCategory::Herb});
	// TODO: Scavenger
	lt.set(Farmer, {PlantCategory::FruitVeggie, PlantCategory::Succulent, PlantCategory::Flowering, PlantCategory::Leafy, PlantCategory::Bulb,  PlantCategory::Herb});
	// TODO: Gatherer
	lt.set(HorseBreeder, {Animal::Horse});
	lt.set(HorseMaster, {Animal::Horse, Ritual::HorseBreederBoost});
	lt.set(MasterFisher, {Item::Fish, Item::Shellfish});
	lt.set(Shaman, {order::Category::Cultural});
	lt.set(Banker, {Ritual::Loan});
	lt.set(HeavyPlower, {Ritual::Plow});
	lt.set(HighPriest, {Item::Incense, order::Category::Cultural, Ritual::PriestBoost});
	lt.set(Bureaucrat, {order::Category::Administrative});
	lt.set(ChariotRacer, {order::Category::Satisfaction});
	lt.set(MoneyLender, {Ritual::Loan});
	lt.set(Plower, {Ritual::Plow});
	lt.set(Porter, {Item::Basket});
	lt.set(Prostitute, {order::Category::Satisfaction});
	lt.set(Administrator, {order::Category::Administrative});
	lt.set(Factor, {Ritual::SingleTradeContract, Ritual::RepeatTradeContract});
	lt.set(FieldSurgeon, {Ritual::Surgery});
	lt.set(Judge, {order::Category::Legal, Ritual::Judgement});
	lt.set(Lawyer, {order::Category::Legal, Ritual::Argument});
	// teamster
	lt.set(TradeBaron, {Ritual::RepeatTradeContract, Ritual::SingleTradeContract});
	lt.set(Veterinarian, {Ritual::AnimalSurgery});
	// carter
	lt.set(ChariotDriver, {Ritual::DriveChariot});
	lt.set(CombatHealer, {Item::Bandage, Item::MedicinalSoap, Ritual::Surgery});
	lt.set(Landowner, {Ritual::CreateTax, Ritual::PayTax});
	lt.set(Trader, {Ritual::PayTax, Ritual::SingleTradeContract});
	lt.set(Merchant, {Ritual::PayTax, Ritual::SingleTradeContract, Ritual::RepeatTradeContract, Ritual::Investment});
	lt.set(Governor, {order::Category::Legal, order::Category::Administrative, Ritual::EnactLaw});
	lt.set(Senator, {order::Category::Legal, order::Category::Administrative, Ritual::ProposeBill, Ritual::PromoteBill});
	lt.set(ShipCaptain, {Ritual::SingleTradeContract, Ritual::Sail});
	lt.set(Gladiator, {Ritual::Tournament});
	lt.set(Mariner, {Ritual::AssistSail, Ritual::Sail});
	lt.set(Sailor, {Ritual::AssistSail, Ritual::Sail});
	lt.set(Curer, {Item::Bandage, Item::MedicinalSoap, Ritual::Surgery, Item::Theriac, Item::GileadBalm});
	lt.set(Apprentice, {Ritual::Apprentice});
	lt.set(Student, {Ritual::Study});
	lt.set(Tutor, {Ritual::Teach});
	lt.set(Matron, {Ritual::Caretake});
	lt.set(Teacher, {Ritual::Teach});
	lt.set(Caretaker, {Ritual::Caretake});
	lt.set(Dyer, {Item::BlueDye, Item::RedDye, Item::YellowDye});
	lt.set(Ropemaker, {Item::Rope});
	lt.set(MasterSpinner, {Item::Thread, Item::Yarn, Item::String});
	//TODO: sewer, caster, tailor
	    return lt;
}();

// inline constexpr RaggedLookupTable<Role, Material, total-element-size, max-enum-size>
// role_to_variants = []
// 	{
// 		using enum Role;

// 		RaggedLookupTable<Role, Material, total-element-size, max-enum-size> lt{};

// 		return lt;
// 	}
