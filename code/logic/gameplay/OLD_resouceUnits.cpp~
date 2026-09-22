#include "../include/basic.hpp"
#include "../include/categories.hpp"

vector<Item> resource_unit_resources[static_cast<int>(Role::RESOURCEMAX)];

void initialize_resource_unit_lists()
{
	resource_unit_resources[static_cast<int>(Role::Scavenger)] = {
	    Item::Rock,	      Item::Pebble, Item::LargeRock, Item::Boulder,   Item::Stick,
	    Item::LargeStick, Item::Flint,  Item::Gravel,    Item::ChickenEgg};
	resource_unit_resources[static_cast<int>(Role::FishHunter)] = {Item::Fish};
	resource_unit_resources[static_cast<int>(Role::Woodcutter)] = {Item::Log};
	resource_unit_resources[static_cast<int>(Role::Herder)] = {Item::Milk};
	resource_unit_resources[static_cast<int>(Role::Shepherd)] = {Item::Wool, Item::GoatMilk};
	resource_unit_resources[static_cast<int>(Role::Herbalist)] = {
	    Item::Hemp,	   Item::Flax,	Item::Mint,    Item::Thyme,   Item::Sage,
	    Item::Ginseng, Item::Senna, Item::Saffron, Item::Lavender};
	resource_unit_resources[static_cast<int>(Role::StoneMiner)] = {Item::Stone};
	resource_unit_resources[static_cast<int>(Role::Planter)] = {
	    Item::Wheat,    Item::Oat,	   Item::Corn,	    Item::Rice,	   Item::Tomato,
	    Item::Onion,    Item::Potato,  Item::Cabbage,   Item::Pumpkin, Item::Pepper,
	    Item::Carrot,   Item::Poppy,   Item::Cannabis,  Item::Senna,   Item::Cotton,
	    Item::Papyrus,  Item::Flax,	   Item::Hemp,	    Item::Lettuce, Item::Cocoa,
	    Item::Cucumber, Item::Kale,	   Item::Beets,	    Item::Madder,  Item::Indigo,
	    Item::Saffron,  Item::Ginseng, Item::Garlic,    Item::Mint,	   Item::Thyme,
	    Item::Lavender, Item::Rhubarb, Item::Sugarcane, Item::Coconut, Item::Fruit};
	resource_unit_resources[static_cast<int>(Role::Fisherman)] = {Item::Fish};
	resource_unit_resources[static_cast<int>(Role::CopperMiner)] = {Item::Ore, Item::Stone};
	resource_unit_resources[static_cast<int>(Role::Beekeeper)] = {Item::Wax, Item::Honey};
	resource_unit_resources[static_cast<int>(Role::CerealFarmer)] = {Item::Wheat, Item::Oat,
								       Item::Corn, Item::Rice};
	resource_unit_resources[static_cast<int>(Role::FlaxFarmer)] = {Item::Flax};
	resource_unit_resources[static_cast<int>(Role::HerbFarmer)] = {
	    Item::Hemp,	 Item::Flax,	Item::Mint,	Item::Thyme,  Item::Sage,  Item::Ginseng,
	    Item::Senna, Item::Saffron, Item::Lavender, Item::Madder, Item::Indigo};
	// NOTE: maybe not resource
	resource_unit_resources[static_cast<int>(Role::HorseBreeder)] =
	    resource_unit_resources[static_cast<int>(Role::Horticulturalist)] = {
		Item::Tomato,  Item::Onion,  Item::Potato, Item::Cabbage,
		Item::Pumpkin, Item::Pepper, Item::Carrot, Item::Cucumber,
		Item::Kale,    Item::Beets,  Item::Rhubarb};

	// no fishmonger
	resource_unit_resources[static_cast<int>(Role::IronMiner)] = {Item::Ore, Item::Stone};
	resource_unit_resources[static_cast<int>(Role::OliveGrower)] = {Item::Olive};
	resource_unit_resources[static_cast<int>(Role::PapyrusHarvester)] = {Item::Papyrus};
	resource_unit_resources[static_cast<int>(Role::VineyardWorker)] = {Item::Grape};
	resource_unit_resources[static_cast<int>(Role::DairyFarmer)] = {Item::Milk, Item::GoatMilk};
	resource_unit_resources[static_cast<int>(Role::GoldMiner)] = {Item::Gold, Item::Silver};
	// quarry worker is just stone miner
	resource_unit_resources[static_cast<int>(Role::SaltMiner)] = {Item::Salt, Item::Stone};

	resource_unit_resources[static_cast<int>(Role::CottonFarmer)] = {Item::Cotton};
	resource_unit_resources[static_cast<int>(Role::GemstoneMiner)] = {Item::Gem,
									Item::GreaterGem};
	resource_unit_resources[static_cast<int>(Role::OrchardFarmer)] = {Item::Fruit};
}

std::array<vector<Item>, static_cast<int>(Role::PRODUCTSMAX)> producer_products;

// TODO: MAP tools to producers who can craft them
void intialize_producer_products()
{
	// find way to restrict some items to meso age
	producer_products[static_cast<int>(Role::HideCrafter)] = {
	    Item::Tribalwear, Item::Satchel, Item::LargeSatchel,
	    Item::TentCover,  Item::Strap,   Item::Whip,
	};
	producer_products[static_cast<int>(Role::Knapper)] = {
	    Tools::Hammerstone, Tools::HandKnife,      Tools::HandDrill,
	    Tools::HandChisel,	Tools::HandAxe,	       Item::PrimitiveSpearHead,
	    Item::Arrowhead,	Item::SmoothedPebbles, Item::PrimitiveAxeHead,
	    Item::SolidWheel,
	};
	producer_products[static_cast<int>(Role::Carver)] = {
	    Item::StickSpear,	  Item::Fiber,		Item::Peat,
	    Item::PrimitiveChair, Item::PrimitiveStool, Item::BoneArtifact,
	};
	producer_products[static_cast<int>(Role::Firekeeper)] = {
	    Station::PitFire, Item::Torch,	Item::Ash,     Item::Soot,	Item::AnimalHides,
	    Item::AnimalHair, Item::Bone,	Item::Sinew,   Item::AnimalFat, Item::DrinkingWater,
	    Item::RawMeat,    Item::CookedMeat, Item::Charcoal};
	producer_products[static_cast<int>(Role::Crafter)] = {
	    Item::PrimitiveThread, Item::PrimitiveString, Item::PrimitiveRope,
	    Tools::PrimitiveSpear, Tools::PrimitiveAxe,	  Tools::Sling,
	    Tools::DiggingStick,   Tools::PrimitiveBow,	  Item::PrimitiveArrow,
	    Item::Javelin,	   Item::BackstrapLoom};

	producer_products[static_cast<int>(Role::CanoeCarver)] = {Vehicle::Canoe};
	producer_products[static_cast<int>(Role::BasketWeaver)] = {Container::Basket};
	producer_products[static_cast<int>(Role::Mixer)] = {
	    Item::PackedEarth, Item::Daub,	   Item::Fertilizer, Item::FishMeal,
	    Item::BoneMeal,    Item::Cob,	   Item::Plaster,    Item::Concrete,
	    Item::Mortar,      Item::TanningAgent, Item::Butter};
	producer_products[static_cast<int>(Role::ShelterBuilder)] = {
	    Buildable::TentSticks, Buildable::WattleRoof, Buildable::WattleWall, Buildable::Wall};
	producer_products[static_cast<int>(Role::Tanner)] = {Item::CuredHide};
	// artists:
	producer_products[static_cast<int>(Role::Ornamenter)] = {Item::Earring, Item::Ring,
								Item::Necklace, Item::WoodCrown};
	producer_products[static_cast<int>(Role::Carver)] = {Item::WoodArtifact};

	producer_products[static_cast<int>(Role::Butcher)] = {Item::AnimalHides, Item::AnimalHair,
							     Item::Bone,	Item::Sinew,
							     Item::AnimalFat,	Item::RawMeat};
	producer_products[static_cast<int>(Role::Woodworker)] = {
	    Item::Wood, Item::LogBeam, Item::Beam, Item::Timber, Item::Plank};
	producer_products[static_cast<int>(Role::Spinner)] = {Item::String, Item::Thread};
	producer_products[static_cast<int>(Role::MudbrickMaker)] = {Item::Mudbrick};
	producer_products[static_cast<int>(Role::Weaver)] = {Item::Cloth, Item::Silk, Item::Linen};
	producer_products[static_cast<int>(Role::ClayWorker)] = {
	    Container::ClayPot, Container::ClayJar, Container::ClayBowl};
	producer_products[static_cast<int>(Role::GrainGrinder)] = {Item::WheatGrain, Item::Grist,
								  Item::Flour, Item::MilledRice};

	// CopperSmelter
	//     producer_products[static_cast<int>(Role::StoneWorker)] = {CrushedStone};
	//     Coppersmith
	//     BoatBuilder
	//     Bowyer
	//     Fletcher
	//     Leathercrafter
	//     Priest
	//     Brewer

	// SilverSmelter
	//     GoldSmelter
	//     Silversmith
	//     Goldsmith
	//     GemCarver
	//    Potter
	//     Engineer
	//     Baker
	//     BrickMaker
	//     BronzeSmelter
	//     Bronzesmith
	//     Builder
	//     CharcoalMaker
	//     Cook
	//     Cuirassier
	//     Wheelwright
	//     Scribe
	//     Philosopher

	//     IronSmelter
	//     Ironsmith
	//     OilMaker
	//     PaperMaker
	//     Apothecary
	//     Glassworker

	//     Glassblower
	//     Engraver
	//     Minter
	//     Shipwright
	//     SiegeEngineer
	//     SteelSmelter
	//     Steelsmith
	//     Founder
	//     Surgeon
	//     Monarch
	//     MilLeader
	//     Miller
	//     Caretaker
	//     Hauler
	//     Dyer
	//     Chandler
	//     Ropemaker
	//     Tailor
	//     Armorer
}
