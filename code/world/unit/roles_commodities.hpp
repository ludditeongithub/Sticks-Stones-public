#pragma once
#include "core/tables.hpp"
#include "world/plant/enum.hpp"
#include <world/animal/enum.hpp>
#include "world/unit/enum.hpp"
#include <world/buildable/enum.hpp>
#include <world/item/enum.hpp>
#include <world/progression/enum.hpp>
#include <core/combo_enum.hpp>

using Commodity = ConcatEnum<Item, Buildable, Knowledge, Order, Ritual, PlantCategory, Animal>;  

constexpr uint16_t ROLE_COMMODITY_JOB_AMOUNT = 4000;

template<typename... Cs>
constexpr auto mkv_commodity(Cs... cs) -> std::array<Commodity::underlying, sizeof...(Cs)> {
    return { Commodity::cast(cs)... };
}

//consider putting Material into commodity, which will determine possible material variants for all items if applicable. alternatively, pairs which include item and variant int8_t cast from material
// important: must be initialized in enum order!
inline constexpr RaggedLookupTable<Role, Commodity::underlying, ROLE_COMMODITY_JOB_AMOUNT, Commodity::MAX> rolesToCommodities = []
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
	lt.set(AdvisorTrade, mkv_commodity(Ritual::SingleTradeContract, Ritual::RepeatTradeContract, Ritual::CreateTariff, Order::Administrative));
	lt.set(Bureaucrat, mkv_commodity(Order::Legal, Order::Administrative, Knowledge::Units));
	// TODO: advisor medical
	lt.set(AdvisorForeign, mkv_commodity(Knowledge::Foreign, Ritual::PeaceTreaty, Ritual::RequestAid, Ritual::TradeOffer, Ritual::WarDeclaration, Ritual::FriendlyLetter));
	lt.set(MiningEngineer, mkv_commodity(Buildable::Pulley, Buildable::BucketPump, Buildable::HydraulicPump, Buildable::Siphon, Buildable::Waterwheel, Ritual::MinerBoost));
	lt.set(WagonMaster, mkv_commodity(Ritual::TeamsterBoost));
	lt.set(AdvisorOrderCulturalPerformer, mkv_commodity(Order::Cultural, Ritual::Song, Ritual::InstrumentalSong, Ritual::Poem));
	lt.set(AdvisorOrderCulturalArtifact, mkv_commodity(Order::Cultural, Item::CanvasPainting, Buildable::LargeSculpture, Buildable::MediumSculpture, Item::SmallSculpture));
	lt.set(Chieftan, mkv_commodity(Order::Cultural, Order::Administrative, Order::Legal, Ritual::Decree, Ritual::LeaderSpeech));
	lt.set(Engineer, mkv_commodity(Buildable::CityGate, Buildable::StoneRoad, Buildable::ConcreteRoad, Buildable::BrickRoad, Buildable::Canal, Buildable::TallWall, Buildable::LargeDoor, Buildable::MiniGate, Buildable::Waterwheel, Buildable::Well, Buildable::Watchtower));
	lt.set(CivilEngineer, mkv_commodity(Buildable::StoneRoad, Buildable::ConcreteRoad, Buildable::BrickRoad, Buildable::Canal, Buildable::TallWall, Buildable::Waterwheel, Buildable::Well, Buildable::Watchtower, Buildable::Aqueduct, Buildable::WoodBridge, Buildable::StoneBridge, Buildable::BrickBridge, Buildable::CityGate, Buildable::CityWall));
// check if primitive rope, primitive sting should be paleo, TODO: more tools
	lt.set(Crafter, mkv_commodity(Item::PrimitiveRope, Item::PrimitiveString, Item::HandDrill, Item::PrimitiveArrow, Buildable::TentSticks));
//TODO: cooking
	lt.set(Firekeeper, mkv_commodity(Item::Soot, Buildable::PitFire, Item::Bone, Item::Sinew, Item::AnimalHair, Item::AnimalFat, Item::AnimalHides, Item::RawMeat;));
	lt.set(Carver, mkv_commodity(Item::StickSpear, Item::HandDrill, Item::SmallHandle, Item::LargeHandle, Buildable::TentSticks));
	lt.set(Knapper, mkv_commodity(Item::HandKnife, Item::HandChisel, Item::HandAxe, Item::Arrowhead, Item::SharpStone, Item::Hammerstone, Item::StickSpear, PrimitiveNeedle));
	lt.set(HideCrafter, mkv_commodity(Item::Tribalwear, Buildable::TentCover, Item::PrimitiveSack, Item::Arrowhead));
	lt.set(Butcher, mkv_commodity(Item::Bone, Item::Sinew, Item::AnimalHair, Item::AnimalFat, Item::AnimalHides, Item::RawMeat));
	lt.set(Preserver, mkv_commodity(Item::Salt, Item::Vinegar, Item::PickledFruit, Item::PickledVegetable, Item::SaltedCookedMeat, Item::SaltedRawMeat, Item::SaltedVegetable));
	lt.set(StoneWorker, mkv_commodity(Item::Stone, Item::CrushedStone, Item::StoneTablet, Item::ToolHeadPlaceholder, Item::SolidWheel));
	lt.set(Weaver, mkv_commodity(Item::Cloth, Item::DyedCloth, Item::DecorativeCloth));
	lt.set(Woodworker, mkv_commodity(Item::Wood, Item::Plank, Item::LogBeam, Item::Beam));
	lt.set(Spinner, mkv_commodity(Item::Thread, Item::Yarn, Item::String));
	lt.set(BasketWeaver, mkv_commodity(Item::Basket, Item::LargeBasket));
	lt.set(CanoeCarver, mkv_commodity(Buildable::Canoe));
	lt.set(ShelterBuilder, mkv_commodity(Buildable::TentSticks, Buildable::WattleWall, Buildable::WattleRoof, Buildable::CobWall, Buildable::CobRoof));
	lt.set(Tanner, mkv_commodity(Item::CuredHide, Item::TannedHide));
	lt.set(Armorer, mkv_commodity(Item::Chainmail, Item::Breastplate, Item::Helmet, Item::Boots, Item::Bracers, Item::Guards, Item::Gloves));
	lt.set(Blacksmith, mkv_commodity(Item::Helmet, Item::Breastplate, Item::Boots, Item::Bracers, Item::Bracelet, Item::Guards, Item::Gloves, Item::ToolHeadPlaceholder, Item::WeaponHeadPlaceholder, Item::Nail, Item::NailHeader, Item::Peg, Item::Horseshoes, Item::Ring, Item::Rivet, Item::Axle, Item::LargeAxle, Item::Jar, Item::Arrowhead));
	lt.set(ParchmentMaker, mkv_commodity(Item::Parchment));
	lt.set(SteelSmelter, mkv_commodity(Item::Ingot));
	lt.set(Toolsmith, mkv_commodity(Item::ToolHeadPlaceholder, Item::ToolPlaceholder));
	lt.set(Weaponsmith, mkv_commodity(Item::WeaponHeadPlaceholder, Item::WeaponPlaceholder));
	lt.set(CandleMaker, mkv_commodity(Item::Wick, Item::Candle));
	lt.set(Chandler, mkv_commodity(Item::Wick, Item::Candle));
	lt.set(Glassblower, mkv_commodity(Item::Glass));
	lt.set(IronSmelter, mkv_commodity(Item::Ingot));
	lt.set(LoomWeaver, mkv_commodity(Item::Cloth, Item::DyedCloth, Item::DecorativeCloth));
	lt.set(OilMaker, mkv_commodity(Item::CookingOil, Item::CornOil, Item::TruffleOil, Item::OliveOil));
	lt.set(PaperMaker, mkv_commodity(Item::Paper));
	lt.set(Shipwright, mkv_commodity(Buildable::Canoe, Buildable::Sailboat, Buildable::LargeSailboat, Buildable::Longboat, Buildable::LightWarship, Buildable::Cog));
	lt.set(Vinter, mkv_commodity(Item::Wine, Item::FruitWine));
	lt.set(BoatBuilder, mkv_commodity(Buildable::Canoe, Buildable::Sailboat, Buildable::LargeSailboat));
	lt.set(Bowyer, mkv_commodity(Item::Bow, Item::Crossbow, Item::Longbow));
	lt.set(Brewer, mkv_commodity(Item::Beer, Item::Vinegar, Item::Mead, Item::SugarJuice, Item::Cider));
	lt.set(Coppersmith, mkv_commodity(Item::Helmet, Item::Breastplate, Item::Boots, Item::Bracers, Item::Bracelet, Item::Guards,  Item::ToolHeadPlaceholder, Item::WeaponHeadPlaceholder, Item::Nail, Item::NailHeader, Item::Peg, Item::Horseshoes, Item::Ring, Item::Rivet, Item::Axle, Item::LargeAxle, Item::Jar, Item::Arrowhead));
	lt.set(Fletcher, mkv_commodity(Item::Arrow, Item::ArrowShaft, Item::Arrowhead)); //TODO: only bone variants for arrowhead
	lt.set(Leathercrafter, mkv_commodity(Item::Satchel, Item::LargeSatchel, Item::Gambeson, Item::Coat, Item::Gloves, Item::Boots, Item::Bracers));
	lt.set(MudbrickMaker, mkv_commodity(Item::Cob));
 	lt.set(GrainGrinder, mkv_commodity(Item::Flour, Item::MilledRice));
	lt.set(Miller, mkv_commodity(Item::MilledRice, Item::Flour));
	lt.set(Cartwright, mkv_commodity(Buildable::WheeledCart, Buildable::WheeledWagon, Buildable::WheeledChariot));
	lt.set(Cheesemaker, mkv_commodity(Item::Cheese, Item::BlueCheese, Item::GoatCheese));
	lt.set(Engraver, mkv_commodity(Item::Die, Item::EngravedRing, Item::EngravedBracelet));
	lt.set(Glassblower, mkv_commodity(Item::Bottle, Item::Jar, Item::Earring, Item::Ring, Item::Bracelet, Item::Tube, Item::Pane, Item::Vase));
	lt.set(Minter, mkv_commodity(Item::Coins));
	lt.set(Baker, mkv_commodity(Item::Bread, Item::Pastry, Item::Pie));
	lt.set(BrickMaker, mkv_commodity(Item::Bricks));
	lt.set(BronzeSmelter, mkv_commodity(Item::Ingot));
	//TODO: differentiate between activities builder can contribute to, and ones he can initiate
	lt.set(Builder, mkv_commodity(Buildable::BrickRoad, Buildable::TentSticks, Buildable::WattleWall, Buildable::CobRoof, Buildable::CobWall, Buildable::Wall, Buildable::TallWall,  Buildable::CityWall, Buildable::WallPanel, Buildable::Fence, Buildable::Gate, Buildable::CityGate, Buildable::Arch, Buildable::Aqueduct, Buildable::WoodBridge, Buildable::BrickBridge, Buildable::StoneBridge, Buildable::Dam, Buildable::LargeCanal, Buildable::MiniGate, Buildable::LargeDoor, Buildable::Pillar, Buildable::Watchtower, Buildable::PitFire, Buildable::TentCover, Buildable::WattleRoof, Buildable::RoofBeams, Buildable::Roof, Buildable::Window, Buildable::PaintedWindow, Buildable::Foundation, Buildable::Floor, Buildable::Carpet, Buildable::PlowedDirt, Buildable::Path, Buildable::StoneRoad, Buildable::BrickRoad, Buildable::ConcreteRoad, Buildable::DugCanal, Buildable::Canal, Buildable::Well));
	lt.set(Carpenter, mkv_commodity(Item::Wood, Item::Plank, Item::JoinedPlank, Item::Peg, Item::LogBeam, Item::Beam, Item::Timber));
	lt.set(CharcoalMaker, mkv_commodity(Item::Charcoal, Item::Ash));
	lt.set(Cook, mkv_commodity(Item::DrinkingWater)); // TODO: consumables
	lt.set(Cuirassier, mkv_commodity(Item::Satchel, Item::LargeSatchel, Item::Gambeson, Item::Coat, Item::Gloves, Item::Boots, Item::HorseSaddle, Item::OxSaddle, Item::Bracers)); // TODO: more leather items, differentiate with leather crafter
	lt.set(Provisioner, mkv_commodity(Item::Salt, Item::Vinegar, Item::PickledFruit, Item::PickledVegetable, Item::SaltedCookedMeat, Item::SaltedRawMeat, Item::SaltedVegetable));
	lt.set(Stonemason, mkv_commodity(Item::CurvedStone, Item::ToolHeadPlaceholder, Item::Stone, Item::CrushedStone,  Item::CurvedStone, Item::CutStone, Item::CutStoneSheet, Item::StoneTablet, Item::ToolHeadPlaceholder, Item::SolidWheel));
	lt.set(Wickerworker, mkv_commodity(Item::Basket, Item::LargeBasket));
	lt.set(Bronzesmith, mkv_commodity(Item::Helmet, Item::Breastplate, Item::Boots, Item::Bracers, Item::Bracelet, Item::Guards, Item::Gloves, Item::ToolHeadPlaceholder, Item::WeaponHeadPlaceholder, Item::Nail, Item::NailHeader, Item::Peg, Item::Horseshoes, Item::Ring, Item::Rivet, Item::Axle, Item::LargeAxle, Item::Jar, Item::Arrowhead));
	lt.set(Chronicler, mkv_commodity(Ritual::HistoryText, Ritual::Chronicle, Order::Cultural, Knowledge::Academic));
	lt.set(Scholar, mkv_commodity(Item::Scroll, Item::Book, Ritual::HistoryText, Ritual::LawText, Ritual::PhilosophyText));
	lt.set(Apothecary, mkv_commodity(Item::MedicinalSoap, Item::BlueDye, Item::RedDye, Item::YellowDye, Item::Poison, Item::Cyanide, Item::Arsenic, Item::Hemlock, Item::Bandage, Item::Laxative, Item::MedicinalSoap, Item::GileadBalm, Item::Theriac));
	lt.set(Historian, mkv_commodity(Order::Cultural, Knowledge::Academic, Ritual::HistoryText));
	lt.set(Mathematician, mkv_commodity(Ritual::MathematicsText, Knowledge::Academic)); // TODO: perhaps divide up academics
	lt.set(SiegeEngineer, mkv_commodity(Buildable::BatteringLog, Buildable::BatteringRam, Buildable::Trebuchet, Buildable::Ballista, Buildable::Catapult, Buildable::SiegeLadder, Buildable::SiegeTower));
	lt.set(NavalEngineer, mkv_commodity(Buildable::Canoe, Buildable::Sailboat, Buildable::LargeSailboat, Buildable::Longboat, Buildable::LightWarship, Buildable::Cog, Buildable::HeavyWarship, Buildable::Freighter));
	lt.set(Priest, mkv_commodity(Item::Incense, Order::Cultural));
	lt.set(Librarian, mkv_commodity(Item::Book, Item::Scroll, Ritual::ReviewTexts, Knowledge::Academic, Knowledge::Exploration, Knowledge::Foreign, Knowledge::Units, Knowledge::Technology));
	lt.set(Scribe, mkv_commodity(Item::Scroll, Item::Book, Order::Legal, Knowledge::Academic));
	lt.set(MasterWeaver, mkv_commodity(Item::Cloth, Item::DyedCloth, Item::DecorativeCloth, Ritual::WeaverBoost));
	lt.set(MasterBaker, mkv_commodity(Item::Bread, Item::Pastry, Item::Pie, Ritual::BakerBoost));
	lt.set(MasterBuilder, mkv_commodity(Buildable::BrickRoad, Buildable::TentSticks, Buildable::WattleWall, Buildable::CobRoof, Buildable::CobWall, Buildable::Wall, Buildable::TallWall, Buildable::CityWall, Buildable::WallPanel, Buildable::Fence, Buildable::Gate, Buildable::CityGate, Buildable::Arch, Buildable::Aqueduct, Buildable::WoodBridge, Buildable::BrickBridge, Buildable::StoneBridge, Buildable::Dam, Buildable::LargeCanal, Buildable::MiniGate, Buildable::LargeDoor, Buildable::Pillar, Buildable::Watchtower, Buildable::PitFire, Buildable::TentCover, Buildable::WattleRoof, Buildable::RoofBeams, Buildable::Roof, Buildable::Window, Buildable::PaintedWindow, Buildable::Foundation,Buildable::Floor, Buildable::Carpet, Buildable::PlowedDirt, Buildable::Path, Buildable::StoneRoad, Buildable::BrickRoad, Buildable::ConcreteRoad, Buildable::DugCanal, Buildable::Canal, Buildable::Well, Ritual::BuilderBoost));
 	lt.set(MasterCarpenter, mkv_commodity(Item::Wood, Item::Plank, Item::JoinedPlank, Item::Peg, Item::LogBeam, Item::Beam, Item::Timber, Ritual::CarpenterBoost));
	lt.set(MasterCraftsman, mkv_commodity(Item::PrimitiveRope, Item::PrimitiveString, Item::HandDrill, Item::PrimitiveArrow, Buildable::TentSticks, Ritual::CraftsmanBoost));
	lt.set(MasterCuirassier, mkv_commodity(Item::Satchel, Item::LargeSatchel, Item::Gambeson, Item::Coat, Item::Gloves, Item::Boots, Item::HorseSaddle, Item::OxSaddle, Item::Bracers, Ritual::CuraisserBoost));
	lt.set(MasterFletcher, mkv_commodity(Item::Arrow, Item::ArrowShaft, Item::Arrowhead, Ritual::FletcherBoost));
	lt.set(MasterMason, mkv_commodity(Item::CurvedStone, Item::ToolHeadPlaceholder, Item::Stone, Item::CrushedStone, Item::CurvedStone, Item::CutStone, Item::CutStoneSheet, Item::StoneTablet, Item::ToolHeadPlaceholder, Item::SolidWheel));
	lt.set(Chef, mkv_commodity(Item::DrinkingWater)); // TODO
	lt.set(Elder, mkv_commodity(Knowledge::Technology, Knowledge::Units, Knowledge::Academic, Ritual::InitiationRitual));
	lt.set(Scout, mkv_commodity(Knowledge::Exploration, Ritual::Explore));
	lt.set(Negotiator, mkv_commodity(Ritual::WarDeclaration, Ritual::PeaceTreaty, Ritual::TradeOffer, Ritual::RequestAid, Ritual::RequestAlliance, Ritual::RequestUnion));
	lt.set(Surveyor, mkv_commodity(Knowledge::Foreign, Ritual::FindMine));
	lt.set(Spy, mkv_commodity(Knowledge::Foreign, Ritual::BuildSpyNetwork, Ritual::CounterSpy));
	lt.set(Cartographer, mkv_commodity(Item::Map, Ritual::MakeMap));
	lt.set(Diplomat, mkv_commodity(Knowledge::Foreign, Ritual::WarDeclaration, Ritual::PeaceTreaty, Ritual::TradeOffer, Ritual::RequestAid, Ritual::RequestAlliance, Ritual::RequestUnion, Ritual::CurryFavor, Ritual::EncourageWar, Ritual::GatherSpecificForeignInfo));
	lt.set(Envoy, mkv_commodity(Knowledge::Foreign, Ritual::WarDeclaration, Ritual::PeaceTreaty, Ritual::TradeOffer, Ritual::RequestAid, Ritual::RequestAlliance, Ritual::RequestUnion, Ritual::CurryFavor));
	lt.set(Explorer, mkv_commodity(Knowledge::Exploration, Ritual::Explore, Ritual::Chart));
	lt.set(Navigator, mkv_commodity(Knowledge::Exploration, Ritual::Explore, Ritual::Chart));
	lt.set(Philosopher, mkv_commodity(Knowledge::Technology, Knowledge::Units, Knowledge::Academic, Order::Cultural, Ritual::Debate, Ritual::PublicTeaching, Ritual::PhilosophyText, Ritual::LawText, Ritual::MathematicsText));
	lt.set(Herder, mkv_commodity(Item::Corpse, Item::Milk));
	lt.set(Shepherd, mkv_commodity(Item::Corpse, Item::GoatMilk));
	lt.set(StoneMiner, mkv_commodity(Item::Stone, Item::Lime));
	lt.set(FishHunter, mkv_commodity(Item::Fish, Item::Shellfish)); //TODO: is this right, or animal?
	lt.set(Woodcutter, mkv_commodity(Item::Wood));
	lt.set(CottonFarmer, mkv_commodity(PlantCategory::Textile));
	lt.set(GemstoneMiner, mkv_commodity(Item::Gem, Item::GreaterGem));
	lt.set(Fisherman, mkv_commodity(Item::Fish, Item::Shellfish));
	lt.set(IronMiner, mkv_commodity(Item::Ore));
	lt.set(OliveGrower, mkv_commodity(Plant::Olive));
	lt.set(PapyrusHarvester, mkv_commodity(PlantCategory::Textile));
	lt.set(Rancher, mkv_commodity(Animal::Cow, Animal::Sheep, Animal::Pig, Animal::Chicken, Animal::Goat, Animal::Camel, Item::Milk, Item::Wool, Item::Egg));
	lt.set(VineyardWorker, mkv_commodity(PlantCategory::Grapevine));
	lt.set(Harvester, mkv_commodity(PlantCategory::BerryShrub, PlantCategory::FruitVeggie, PlantCategory::Flowering, PlantCategory::Leafy, PlantCategory::Root, PlantCategory::Reed, PlantCategory::Tuber, PlantCategory::Bulb, PlantCategory::Grain, PlantCategory::Herb, PlantCategory::Bush, PlantCategory::Citrus, PlantCategory::Stone, PlantCategory::Pome));
	lt.set(Planter, mkv_commodity(PlantCategory::BerryShrub, PlantCategory::FruitVeggie, PlantCategory::Flowering, PlantCategory::Leafy, PlantCategory::Root, PlantCategory::Reed, PlantCategory::Tuber, PlantCategory::Bulb, PlantCategory::Grain, PlantCategory::Herb, PlantCategory::Bush, PlantCategory::Citrus, PlantCategory::Stone, PlantCategory::Pome));
	lt.set(DairyFarmer, mkv_commodity(Item::Milk, Item::GoatMilk, Animal::Goat, Animal::Cow));
	lt.set(GoldMiner, mkv_commodity(Item::Ore));
	lt.set(LivestockFarmer, mkv_commodity(Animal::Cow, Animal::Sheep, Animal::Chicken, Animal::Goat, Animal::Horse, Animal::Camel));
	lt.set(SaltMiner, mkv_commodity(Item::Salt));
	lt.set(SilverMiner, mkv_commodity(Item::Ore));
	lt.set(Beekeeper, mkv_commodity(Item::Honey, Item::Wax));
	lt.set(CerealFarmer, mkv_commodity(PlantCategory::Grain));
	lt.set(HerbFarmer, mkv_commodity(PlantCategory::Herb));
	lt.set(HorseBreeder, mkv_commodity(Animal::Horse));
	lt.set(Horticulturalist, mkv_commodity(PlantCategory::FruitVeggie, PlantCategory::Succulent, PlantCategory::Flowering, PlantCategory::Leafy, PlantCategory::Bulb, PlantCategory::Tuber));
	lt.set(OrchardFarmer, mkv_commodity(PlantCategory::Citrus, PlantCategory::Stone, PlantCategory::Pome, PlantCategory::BerryShrub));
	lt.set(Herbalist, mkv_commodity(PlantCategory::Herb));
	// TODO: Scavenger
	lt.set(Farmer, mkv_commodity(PlantCategory::FruitVeggie, PlantCategory::Succulent, PlantCategory::Flowering, PlantCategory::Leafy, PlantCategory::Bulb, PlantCategory::Tuber, PlantCategory::Herb));
	// TODO: Gatherer
	lt.set(HorseBreeder, mkv_commodity(Animal::Horse));
	lt.set(HorseMaster, mkv_commodity(Animal::Horse, Ritual::HorseBreederBoost));
	lt.set(MasterFisher, mkv_commodity(Item::Fish, Item::Shellfish));
	lt.set(Shaman, mkv_commodity(Order::Cultural));
	lt.set(Banker, mkv_commodity(Ritual::Loan));
	lt.set(HeavyPlower, mkv_commodity(Ritual::Plow));
	lt.set(HighPriest, mkv_commodity(Item::Incense, Order::Cultural, Ritual::PriestBoost));
	lt.set(Bureaucrat, mkv_commodity(Order::Administrative));
	lt.set(ChariotRacer, mkv_commodity(Order::Satisfaction));
	lt.set(MoneyLender, mkv_commodity(Ritual::Loan));
	lt.set(Plower, mkv_commodity(Ritual::Plow));
	lt.set(Porter, mkv_commodity(Item::Basket));
	lt.set(Prostitute, mkv_commodity(Order::Satisfaction));
	lt.set(Administrator, mkv_commodity(Order::Administrative));
	lt.set(Factor, mkv_commodity(Ritual::SingleTradeContract, Ritual::RepeatTradeContract));
	lt.set(FieldSurgeon, mkv_commodity(Ritual::Surgery));
	lt.set(Judge, mkv_commodity(Order::Legal, Ritual::Judgement));
	lt.set(Lawyer, mkv_commodity(Order::Legal, Ritual::Argument));
	// teamster
	lt.set(TradeBaron, mkv_commodity(Ritual::RepeatTradeContract, Ritual::SingleTradeContract));
	lt.set(Veterinarian, mkv_commodity(Ritual::AnimalSurgery));
	// carter
	lt.set(ChariotDriver, mkv_commodity(Ritual::DriveChariot));
	lt.set(CombatHealer, mkv_commodity(Item::Bandage, Item::MedicinalSoap, Ritual::Surgery));
	lt.set(Landowner, mkv_commodity(Ritual::CreateTax, Ritual::PayTax));
	lt.set(Trader, mkv_commodity(Ritual::PayTax, Ritual::SingleTradeContract));
	lt.set(Merchant, mkv_commodity(Ritual::PayTax, Ritual::SingleTradeContract, Ritual::RepeatTradeContract, Ritual::Investment));
	lt.set(Governor, mkv_commodity(Order::Legal, Order::Administrative, Ritual::EnactLaw));
	lt.set(Senator, mkv_commodity(Order::Legal, Order::Administrative, Ritual::ProposeBill, Ritual::PromoteBill));
	lt.set(ShipCaptain, mkv_commodity(Ritual::SingleTradeContract, Ritual::Sail));
	lt.set(Gladiator, mkv_commodity(Ritual::Tournament));
	lt.set(Mariner, mkv_commodity(Ritual::AssistSail, Ritual::Sail));
	lt.set(Sailor, mkv_commodity(Ritual::AssistSail, Ritual::Sail));
	lt.set(Curer, mkv_commodity(Item::Bandage, Item::MedicinalSoap, Ritual::Surgery, Item::Theriac, Item::GileadBalm));
	lt.set(Apprentice, mkv_commodity(Ritual::Apprentice));
	lt.set(Student, mkv_commodity(Ritual::Study));
	lt.set(Tutor, mkv_commodity(Ritual::Teach));
	lt.set(Matron, mkv_commodity(Ritual::Caretake));
	lt.set(Teacher, mkv_commodity(Ritual::Teach));
	lt.set(Caretaker, mkv_commodity(Ritual::Caretake));
	lt.set(Dyer, mkv_commodity(Item::BlueDye, Item::RedDye, Item::YellowDye));
	lt.set(Ropemaker, mkv_commodity(Item::Rope));
	lt.set(MasterSpinner, mkv_commodity(Item::Thread, Item::Yarn, Item::String));
	//TODO: sewer, caster, tailor
	    return lt;
}();

// inline constexpr RaggedLookupTable<Role, Material, total-element-size, max-enum-size>
// roleToVariants = []
// 	{
// 		using enum Role;

// 		RaggedLookupTable<Role, Material, total-element-size, max-enum-size> lt{};

// 		return lt;
// 	}
