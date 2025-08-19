#include "resourceUnits.hpp"


Item resourceUnitResources[static_cast<int>(Role::RESOURCEMAX)];

void initializeResourceUnitLists() {
    resourceUnitResources[static_cast<int>(Role::Scavenger)] = {Item::Rock, Item::Pebble, Item::LargeRock, Item::Boulder, Item::Stick, Item::LargeStick, Item::Flint, Item::Gravel, Item::ChickenEgg};
    resourceUnitResources[static_cast<int>(Role::FishHunter)] =  {Item::Fish};
    resourceUnitResources[static_cast<int>(Role::Woodcutter)] =  {Item::Log};
    resourceUnitResources[static_cast<int>(Role::Herder)] =  {Item::Milk};
    resourceUnitResources[static_cast<int>(Role::Shepherd)] =  {Item::Wool, Item::GoatMilk};
    resourceUnitResources[static_cast<int>(Role::Herbalist)] =  {Item::Hemp, Item::Flax, Item::Mint, Item::Thyme, Item::Sage, Item::Ginseng, Item::Senna, Item::Saffron, Item::Lavender};
    resourceUnitResources[static_cast<int>(Role::StoneMiner)] =  {Item::Stone};
    resourceUnitResources[static_cast<int>(Role::Planter)] =  {Item::Wheat, Item::Oat, Item::Corn, Item::Rice, Item::Tomato, Item::Onion, Item::Potato, Item::Cabbage, Item::Pumpkin, Item::Pepper, Item::Carrot, Item::Poppy, Item::Cannabis, Item::Senna, Item::Cotton, Item::Papyrus, Item::Flax, Item::Hemp, Item::Lettuce, Item::Cocoa, Item::Cucumber, Item::Kale, Item::Beets, Item::Madder, Item::Indigo, Item::Saffron, Item::Ginseng, Item::Garlic, Item::Mint, Item::Thyme, Item::Lavender, Item::Rhubarb, Item::Sugarcane, Item::Coconut, Item::Fruit};
    resourceUnitResources[static_cast<int>(Role::Fisherman)] =  {Item::Fish};
    resourceUnitResources[static_cast<int>(Role::CopperMiner)] =  {Item::Ore, Item::Stone};
    resourceUnitResources[static_cast<int>(Role::Beekeeper)] =  {Item::Wax, Item::Honey};
    resourceUnitResources[static_cast<int>(Role::CerealFarmer)] =  {Item::Wheat, Item::Oat, Item::Corn, Item::Rice};
    resourceUnitResources[static_cast<int>(Role::FlaxFarmer)] =  {Item::Flax};
    resourceUnitResources[static_cast<int>(Role::HerbFarmer)] =  {Item::Hemp, Item::Flax, Item::Mint, Item::Thyme, Item::Sage, Item::Ginseng, Item::Senna, Item::Saffron, Item::Lavender, Item::Madder, Item::Indigo};
//NOTE: maybe not resource
resourceUnitResources[static_cast<int>(Role::HorseBreeder)] =
    resourceUnitResources[static_cast<int>(Role::Horticulturalist)] =   {Item::Tomato, Item::Onion, Item::Potato, Item::Cabbage, Item::Pumpkin, Item::Pepper, Item::Carrot, Item::Cucumber, Item::Kale, Item::Beets, Item::Rhubarb};

//no fishmonger
resourceUnitResources[static_cast<int>(Role::IronMiner)] =  {Item::Ore, Item::Stone};
resourceUnitResources[static_cast<int>(Role::OliveGrower)] =  {Item::Olive};
resourceUnitResources[static_cast<int>(Role::PapyrusHarvester)] =  {Item::Papyrus};
resourceUnitResources[static_cast<int>(Role::VineyardWorker)] =  {Item::Grape};
resourceUnitResources[static_cast<int>(Role::DairyFarmer)] =  {Item::Milk, Item::GoatMilk};
resourceUnitResources[static_cast<int>(Role::GoldMiner)] =  {Item::Gold, Item::Silver};
    //quarry worker is just stone miner
resourceUnitResources[static_cast<int>(Role:: SaltMiner)] =  {Item::Salt, Item::Stone};

resourceUnitResources[static_cast<int>(Role::CottonFarmer)] =  {Item::Cotton};
resourceUnitResources[static_cast<int>(Role::GemstoneMiner)] =  {Item::Gem, Item::GreaterGem};
resourceUnitResources[static_cast<int>(Role::OrchardFarmer)] = {Item::Fruit};
}

std::array<vector<Item>, static_cast<int>(Role::PRODUCTSMAX)> producerProducts;

void intializeProducerProducts() {
    // find way to restrict some items to meso age
    producerProducts[static_cast<int>(Role::HideCrafter)] = {Item::Tribalwear, Item::Satchel, Item::LargeSatchel, Item::TentCover, Item::Strap, Item::Whip,};
    producerProducts[static_cast<int>(Role::Knapper)] = {Tools::Hammerstone, Tools::HandKnife, Tools::HandDrill, Tools::HandChisel, Tools::HandAxe, Item::PrimitiveSpearHead, Item::Arrowhead, Item::SmoothedPebbles, Item::PrimitiveAxeHead, Item::SolidWheel,};
    producerProducts[static_cast<int>(Role::Carver)] = {Item::StickSpear, Item::Fiber, Item::Peat, Item::PrimitiveChair, Item::PrimitiveStool, Item::BoneArtifact,};
    producerProducts[static_cast<int>(Role::Firekeeper)] = {Station::PitFire, Item::Torch, Item::Ash, Item::Soot, Item::AnimalHides, Item::AnimalHair, Item::Bone, Item::Sinew, Item::AnimalFat, Item::DrinkingWater, Item::RawMeat, Item::CookedMeat, Item::Charcoal};
    producerProducts[static_cast<int>(Role::Crafter)] = {Item::PrimitiveThread, Item:: PrimitiveString, Item::PrimitiveRope,
    Tools::PrimitiveSpear, Tools::PrimitiveAxe, Tools::Sling, Tools::DiggingStick, Tools::PrimitiveBow, Item::PrimitiveArrow, Item::Javelin,
    Item::BackstrapLoom};

    producerProducts[static_cast<int>(Role::CanoeCarver)] = {Vehicle::Canoe};
    producerProducts[static_cast<int>(Role::BasketWeaver)] = {Container::Basket};
    producerProducts[static_cast<int>(Role::Mixer)] = {Item::PackedEarth, Item::Daub, Item::Fertilizer, Item::FishMeal, Item::BoneMeal, Item::Cob, Item::Plaster, Item::Concrete, Item::Mortar, Item::TanningAgent, Item::Butter};
    producerProducts[static_cast<int>(Role::ShelterBuilder)] = {Buildable::TentSticks, Buildable::WattleRoof, Buildable::WattleWall, Buildable::Wall};
    producerProducts[static_cast<int>(Role::Tanner)] = {Item::CuredHide};
    //artists:
    producerProducts[static_cast<int>(Role::Ornamenter)] = {Item::Earring, Item::Ring, Item::Necklace, Item::WoodCrown};
    producerProducts[static_cast<int>(Role::Carver)] = {Item::WoodArtifact};

    producerProducts[static_cast<int>(Role::Butcher)] = {Item::AnimalHides, Item::AnimalHair, Item::Bone, Item::Sinew, Item::AnimalFat, Item::RawMeat};
        producerProducts[static_cast<int>(Role::Woodworker)] = {Item::Wood, Item::LogBeam, Item::Beam, Item::Timber, Item::Plank};
    producerProducts[static_cast<int>(Role::Spinner)] = {Item::String, Item::Thread};
        producerProducts[static_cast<int>(Role::MudbrickMaker)] = {Item::Mudbrick};
        producerProducts[static_cast<int>(Role::Weaver)] = {Item::Cloth, Item::Silk, Item::Linen};
    producerProducts[static_cast<int>(Role::ClayWorker)] = {Container::ClayPot, Container::ClayJar, Container::ClayBowl};
    producerProducts[static_cast<int>(Role::GrainGrinder)] = {Item::WheatGrain, Item::Grist, Item::Flour, Item::MilledRice};


// CopperSmelter
//     producerProducts[static_cast<int>(Role::StoneWorker)] = {CrushedStone};
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
