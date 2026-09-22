#pragma once
#include <data/types/action.hpp>

inline const RaggedLookupTable<Action, Role> action_to_roles = []
	    {		    
		    RaggedLookupTable<Action, Role> lt{};
  			using enum Action;   
		    lt.set(Action::Melee, {Role::MeleeSoldier, Role::SpearHunter});
		    lt.set(Action::Mine, {Role::StoneMiner, Role::CopperMiner, Role::IronMiner, Role::GoldMiner, Role::SilverMiner, Role::SaltMiner});
			lt.set(Action::Cut, {Role::Apothecary, Role::Planter});
			lt.set(Action::Chop, {Role::Woodcutter});
			lt.set(Action::FineChop, {Role::Cook, Role::Chef, Role::Apothecary});
			lt.set(Action::Dig, {Role::Planter, Role::Builder});
			lt.set(Action::Light, {Role::NONE});
			lt.set(Action::Butcher, {Role::Butcher});
			lt.set(Action::Paint, {Role::Painter});
			lt.set(Action::Sculpt, {Role::Sculptor, Role::ClayWorker, Role::Potter});
			lt.set(Action::Chisel, {Role::Stoneworker});
			lt.set(Action::Write, {Role::BooksAcademicAny, Role::BooksAcademicHistory, Role::BooksAcademicPhilosophy, Role::BooksAcademicMathematics, Role::BooksAcademicNatural, Role::Scribe, Role::AdvisorKnowledge, Role::AdvisorOrderAdministrative});
			   lt.set(Action::LowPott, {Role::ClayWorker});
			   lt.set(Action::Pott, {Role::Potter});
			   lt.set(Action::Pott, {Role::Potter});
			   lt.set(Action::Smelt, {Role::CopperSmelter, Role::BronzeSmelter, Role::IronSmelter, Role::SteelSmelter, Role::SilverSmelter, Role::GoldSmelter});
			   lt.set(Action::Smith, {Role::Coppersmith, Role::Bronzesmith, Role::Ironsmith,
				   Role::Steelsmith, Role::Silversmith, Role::Goldsmith});
			   lt.set(Action::Perform, {Role::Performer});
			   // TODO: alternate shitty operation tools
			   lt.set(Action::Operate, {Role::Surgeon});
			   lt.set(Action::Administer, {Role::Surgeon, Role::Herbalist, Role::Apothecary});
			   lt.set(Action::Build, {Role::ShelterBuilder, Role::Builder});
			   lt.set(Action::Mould, {Role::Chandler, Role::Potter});
                            lt.set(Action::Woodwork, {Role::Woodworker});
			    lt.set(Action::Stonework, {Role::Stoneworker});
	lt.set(Action::GlassMake, {Role::GlassMaker});
	lt.set(Action::Glasswork, {Role::Glassworker});
	lt.set(Action::Glasswork, {Role::Glassworker});
	lt.set(Action::Saw, {Role::Woodworker, Role::Woodcutter});
	lt.set(Action::Engrave, {Role::Engraver, Role::GemCarver, Role::WoodCarver});
	lt.set(Action::Burn, {Role::Firekeeper});
	// NOTE: figure out who can do fire
	lt.set(Action::Fire, {Role::CharcoalMaker, Role::Potter});
	lt.set(Action::Press, {Role::Planter});
	lt.set(Action::Carve, {Role::Carver});
	lt.set(Action::WoodCarve, {Role::WoodCarver});
	lt.set(Action::Weave, {Role::Weaver});
	lt.set(Action::BasketWeave, {Role::BasketWeaver});
	lt.set(Action::Bless, {Role::Priest});
	lt.set(Action::Cook, {Role::Cook});
	lt.set(Action::Craft, {Role::Crafter});
	lt.set(Action::Explore, {Role::Explorer});
	lt.set(Action::Negotiate, {Role::Negotiator});
	lt.set(Action::Plow, {Role::Plower});
	lt.set(Action::Plant, {Role::Planter});
	lt.set(Action::Weed, {Role::Planter});
	lt.set(Action::Harvest, {Role::Planter});
	lt.set(Action::Milk, {Role::Herder, Role::Shepherd});
	lt.set(Action::Shear, {Role::Herder, Role::Shepherd});
	lt.set(Action::Mill, {Role::GrainGrinder, Role::Miller});
	lt.set(Action::Fish, {Role::Fisherman});
	lt.set(Action::Herd, {Role::Herder, Role::Shepherd});
	lt.set(Action::Trade, {Role::Trader});
	lt.set(Action::Haul, {Role::Hauler});
	lt.set(Action::Bake, {Role::Baker});
	lt.set(Action::Treat, {Role::Dyer, Role::PaperMaker});
	lt.set(Action::Cur, {Role::Butcher, Role::Tanner});
	lt.set(Action::Tan, {Role::Tanner});
	lt.set(Action::Cast, {Role::Founder, Role::Silversmith, Role::Goldsmith});
	lt.set(Action::Mix, {Role::Mixer});
	lt.set(Action::Boil, {Role::Cook, Role::Firekeeper});
	lt.set(Action::Whittle, {Role::Woodworker, Role::Carver});
	lt.set(Action::Knapp, {Role::Knapper, Role::StoneWorker});
	lt.set(Action::Spin, {Role::Spinner});
	lt.set(Action::Grind, {Role::Apothecary});
	lt.set(Action::Preserve, {Role::Preserver});
	// NOTE: maybe change awl to optional
	lt.set(Action::LeatherCraft, {Role::Leathercrafter, Role::Cuirassier});
	lt.set(Action::Dip, {Role::Chandler});
	lt.set(Action::CandleMould, {Role::Chandler});
	lt.set(Action::Lay, {Role::Ropemaker});
	lt.set(Action::WoodCraft, {Role::Woodworker});
	lt.set(Action::WheelCraft, {Role::Wheelwright});
	lt.set(Action::CanoeCarve, {Role::CanoeCarver});
	lt.set(Action::BoatCraft, {Role::BoatBuilder, Role::Shipwright});
	lt.set(Action::SiegeCraft, {Role::SiegeEngineer});
	lt.set(Action::Engineer, {Role::Engineer});
	// NOTE: maybe change awl to optional
	lt.set(Action::BowCraft, {Role::Bowyer});
	lt.set(Action::MudbrickSculpt, {Role::MudbrickMaker});
	lt.set(Action::BrickSculpt, {Role::BrickMaker});
	lt.set(Action::Mash, {Role::Brewer});
	// TODO: make sure this works
	lt.set(Action::Brew, {Role::Brewer});
	lt.set(Action::OilMake, {Role::OilMaker});
	// to do roles
	lt.set(Action::SculptMould, {Role::Sculptor});
	lt.set(Action::Sew, {Role::Tailor});
	lt.set(Action::Cur, {Role::Butcher, Role::Tanner});
	lt.set(Action::CandleCast, {Role::Chandler});
	lt.set(Action::Mint, {Role::Minter});

	// NON PRODUCT/RESOURCE
	lt.set(Action::Tame, {Role::HorseBreeder, Role::Shepherd, Role::Herder});
		    return lt;
	    }();

inline RaggedLookupTable<Action, ActionRequirement> action_to_tools = []
{
	RaggedLookupTable<Action, ActionRequirement> lt{};
	using enum Action;
	lt.set(Action::Pott, {
    {Buildable::Oven, 1},
    {Buildable::Furnace, 1},
    {Buildable::PottersWheel, 0},
    {Item::Scraper, -1},
    {Item::Stylus, -2}
});

	lt.set(Action::Smelt, {{Buildable::Furnace, 0}, {Item::Crucible, 1}});

	lt.set(Action::Smith, {{Buildable::Anvil, 0}, {Item::Hammer, 1}, {Item::Chisel, 2}});

	lt.set(Action::Perform,
	       {{Item::Lyre, -1}, {Item::Drum, -1}, {Item::Lur, -1}, {Item::PanFlute, -1}});

	lt.set(Action::Operate, {{Item::Scalpel, 0}, {Item::Needle, 1}});

	lt.set(Action::Build, {{Item::Hammer, -1}, {Item::Mallet, -1}});

	lt.set(Action::GlassMake, {{Item::HandheldBellows, 0},
				   {Buildable::Bellows, 0},
				   {Buildable::DoubleBellows, 0},
				   {Buildable::RollingMachine, 1},
				   {Buildable::Furnace, 2}});

	lt.set(Action::Burn, {{Item::Candle, 0}, {Item::Flint, 1}, {Item::Torch, 2}});

	lt.set(Action::WoodCarve,
	       {{Item::Chisel, 0}, {Item::Adze, 1}, {Item::Knife, 2}, {Item::Mallet, 0}});

	lt.set(Action::Weave, {{Item::HandheldLoom, 0}, {Buildable::Loom, 1}});

	lt.set(Action::Cook, {{Item::Pot, 0}, {Buildable::Oven, 1}, {Buildable::Tabletop, 2}});

	lt.set(Action::Harvest, {{Item::Sickle, -1}, {Item::Scythe, -1}});

	lt.set(Action::Milk, {{Item::Bucket, 0}, {Item::Pot, 0}, {Item::Jar, 0}});

	lt.set(Action::Trade, {{Item::Bucket, -1}, {Item::Basket, -1}, {Item::Jar, -1}});

	lt.set(Action::Mix, {{Item::Staff, 0},
			     {Item::Stick, 0},
			     {Item::Bucket, 1},
			     {Item::ClayPot, 1},
			     {Item::Pot, 1}});

	lt.set(Action::Churn, {{Item::Staff, 0},
			       {Item::Stick, 0},
			       {Item::Bucket, 1},
			       {Item::ClayPot, 1},
			       {Item::Pot, 1}});

	lt.set(Action::Boil,
	       {{Buildable::PitFire, 0}, {Buildable::Oven, 0}, {Item::Bucket, 1}, {Item::Pot, 1}});

	lt.set(Action::Spin, {{Item::Spindle, 0}, {Item::Distaff, 0}, {Buildable::Spinner, -1}});

	lt.set(Action::LeatherCraft, {{Item::Knife, 0}, {Item::Awl, 1}, {Item::Needle, 2}});

	lt.set(Action::CanoeCarve, {{Item::Saw, 0}, {Item::Axe, 0}, {Item::Adze, 1}});

	lt.set(Action::MudbrickSculpt, {{Item::Trowel, 1}, {Item::BrickMould, -2}});

	lt.set(Action::BrickSculpt, {{Item::Trowel, 1}, {Item::BrickMould, -2}});

	lt.set(Action::Mash, {{Item::Pestle, 1}, {Buildable::Mill, 1}});

	lt.set(Action::StoneCarve, {{Item::Chisel, 0}, {Item::Mallet, 1}, {Item::Scraper, 2}});

	lt.set(Action::Sculpt, {{Item::Scraper, 0}, {Item::Stylus, 1}, {Item::MeasuringItems, -1}});
	return lt;
}();

constexpr uint16_t ROLE_COMMODITY_JOB_AMOUNT = 4000;

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
