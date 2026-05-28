#ifndef ITEMBULKANDWEIGHT_H_
#define ITEMBULKANDWEIGHT_H_

#include "categories.hpp"

enum class BulkLevel {
Liquid, Fine, SemiFine, Loose, Soft, Solid, Single
};

// the total volume of each bulk category hands can maximally carry.
// where 0.1 is 100mL
// NOTE: idea: consider doing left and right
constexpr float fineBulkMax = 0.3;
constexpr float looseBulkMult = 5.5; // multiplies mid bulk
constexpr float softBulkMult = 2.5; // mulitiplies mid bulk
constexpr float solidBulkMult = 1.0; // mulitiplies mid bulk
constexpr float midBulkMax = 35.0;
constexpr float singleBulkMax = 60.0;

//mas weights pawns can carry
constexpr float childMaxCarry = 30.0;
constexpr float maxCarry = 85.0;

uint8_t humanSight;
uint16_t nearGatherRange = humanSight; // the farthest a pawn will  go to fetch an item
uint16_t midGatherRange = humanSight * 2;

// Fine means that only fine objects can be carried, mid means that loose, soft, or solid objects can be carried, single means
// that only single objects can be carried
enum class BulkStatus {
    NONE, Fine, Mid, Single
};

float currentMaxBulk(BulkStatus bs, bool child) {
    switch(bs) {
        case BulkStatus::Fine:
            return fineBulkMax;
        case BulkStatus::Mid:
            return midBulkMax;
        case BulkStatus::Single:
            return singleBulkMax;
    }
    return 0.0;
}

float maxWeight(bool child) {
    if (child) return childMaxCarry;
    else return maxCarry;
}

enum class ContainerType {
    NONE, Pot, Kettle, Basket, Jar, Keg, Bottle, Waterskin, Satchel, LargeSatchel, Bucket,
};

ContainerType itemToContainer(Item c) {
    switch (c) {
        case Item::Jar:
            return ContainerType::Jar;
        case Item::Pot:
            return ContainerType::Pot;
        case Item::Keg:
            return ContainerType::Keg;
        case Item::Bottle:
            return ContainerType::Bottle;
        case Item::Kettle:
            return ContainerType::Kettle;
        case Item::Waterskin:
            return ContainerType::Waterskin;
        case Item::Satchel:
            return ContainerType::Satchel;
        case Item::LargeSatchel:
            return ContainerType::LargeSatchel;
        case Item::Bucket:
            return ContainerType::Bucket;
        case Item::Basket:
            return ContainerType::Basket;
        default:
            return ContainerType::NONE;
    }
}

float getContainerCapacity(ContainerType c) {
    float capacity;
    switch (c) {
        case ContainerType::Jar:
            capacity = 0.3;
        case ContainerType::Pot:
            capacity = 6.0;
        case ContainerType::Keg:
            capacity = 58.0;
        case ContainerType::Bottle:
            capacity = 2.0;
        case ContainerType::Kettle:
            capacity = 4.5;
        case ContainerType::Waterskin:
            capacity = 1.5;
        case ContainerType::Satchel:
            capacity = 5.0;
        case ContainerType::LargeSatchel:
            capacity = 21.0;
        case ContainerType::Bucket:
            capacity = 19.5;
        case ContainerType::Basket:
            capacity = 8.4;
        default:
            return capacity;
    }
}

struct Container {
    ContainerType containerType;
    float currentBulk = 0;
    float currentWeight = 0;
    bool liquidMode;
    vector<std::pair<Item, uint16_t>> items; //contains all non-variant items
    vector<std::pair<Item, uint16_t>> variantItems; //contains all variant items
    vector<int> variantItemTypes; //the enum relevant number for the enum class
    vector<std::pair<Tool,Material>> tools; //lists tool variants as int
};

SizeData bulkAndWeights[Item::MAX + Container::MAX];

bool validContainer(Container container, Item newItem) {
    switch (bulkAndWeights[static_cast<int>(newItem)].bulklevel) {
        case BulkLevel::Liquid:
            if (!container.liquidMode) return false;
            if (container.containerType == ContainerType::Basket) return false;
        case BulkLevel::Fine:
            if (container.containerType == ContainerType::Basket) return false;
    }
    if (container.currentBulk + bulkAndWeights[static_cast<int>(newItem)].bulk  > getContainerCapacity(container.containerType)) return false;
    return true;
}


struct SizeData {
    float bulk = 0.0;
    float weight = 0.0;
    BulkLevel bulklevel = BulkLevel::Solid;
};

void itemBulksAndWeights() {
    //TODO: LIQUID
    bulkAndWeights[static_cast<int>(Item::Juice)] = {0.4f, 1.5f, BulkLevel::Liquid};
    bulkAndWeights[static_cast<int>(Item::AgedAlcoholicDrink)] = {0.6f, 2.5f, BulkLevel::Liquid};
    bulkAndWeights[static_cast<int>(Item::Milk)] = {0.5f, 1.0f, BulkLevel::Liquid};
bulkAndWeights[static_cast<int>(Item::GoatMilk)] = {0.5f, 1.0f, BulkLevel::Liquid};
bulkAndWeights[static_cast<int>(Item::Milk)] = {0.5f, 1.0f, BulkLevel::Liquid};
bulkAndWeights[static_cast<int>(Item::GoatMilk)] = {0.5f, 1.0f, BulkLevel::Liquid};
bulkAndWeights[static_cast<int>(Item::Bleach)] = {0.02f, 0.015f, BulkLevel::Liquid};
bulkAndWeights[static_cast<int>(Item::Glue)] = {0.02f, 0.015f, BulkLevel::Liquid};
bulkAndWeights[static_cast<int>(Item::Ink)] = {0.02f, 0.015f, BulkLevel::Liquid};
bulkAndWeights[static_cast<int>(Item::Resin)] = {0.03f, 0.025f, BulkLevel::Liquid};
bulkAndWeights[static_cast<int>(Item::Theriac)] = {0.06f, 0.05f, BulkLevel::Liquid};
bulkAndWeights[static_cast<int>(Item::GileadBalm)] = {0.07f, 0.06f, BulkLevel::Liquid};
bulkAndWeights[static_cast<int>(Item::Elactuarium)] = {0.08f, 0.07f, BulkLevel::Liquid};
bulkAndWeights[static_cast<int>(Item::RedDye)] = {0.01f, 0.008f, BulkLevel::Liquid};
bulkAndWeights[static_cast<int>(Item::BlueDye)] = {0.01f, 0.008f, BulkLevel::Liquid};
bulkAndWeights[static_cast<int>(Item::YellowDye)] = {0.01f, 0.008f, BulkLevel::Liquid};
bulkAndWeights[static_cast<int>(Item::Porridge)] = {0.1f, 0.06f, BulkLevel::Liquid};
bulkAndWeights[static_cast<int>(Item::Laxative)] = {0.05f, 0.04f, BulkLevel::Liquid};
bulkAndWeights[static_cast<int>(Item::Tonic)] = {0.10f, 0.08f, BulkLevel::Liquid};
bulkAndWeights[static_cast<int>(Item::TanningAgent)] = {0.06f, 0.05f, BulkLevel::Liquid};
bulkAndWeights[static_cast<int>(Item::Beer)] = {0.10f, 0.09f, BulkLevel::Liquid};
bulkAndWeights[static_cast<int>(Item::Wine)] = {0.10f, 0.09f, BulkLevel::Liquid};
bulkAndWeights[static_cast<int>(Item::FruitWine)] = {0.10f, 0.09f, BulkLevel::Liquid};
bulkAndWeights[static_cast<int>(Item::Mead)] = {0.10f, 0.09f, BulkLevel::Liquid};
bulkAndWeights[static_cast<int>(Item::SugarJuice)] = {0.08f, 0.07f, BulkLevel::Liquid};
bulkAndWeights[static_cast<int>(Item::Arsenic)] = {0.01f, 0.015f, BulkLevel::Liquid};
bulkAndWeights[static_cast<int>(Item::Cyanide)] = {0.01f, 0.01f, BulkLevel::Liquid};

    //TODO: FINE
bulkAndWeights[static_cast<int>(Item::Sand)] = {0.12f, 0.06f, BulkLevel::Fine};
bulkAndWeights[static_cast<int>(Item::Flour)] = {0.04f, 0.025f, BulkLevel::Fine};
bulkAndWeights[static_cast<int>(Item::Grist)] = {0.05f, 0.03f, BulkLevel::Fine};
bulkAndWeights[static_cast<int>(Item::MilledRice)] = {0.05f, 0.028f, BulkLevel::Fine};
bulkAndWeights[static_cast<int>(Item::AnimalFat)] = {0.06f, 0.04f, BulkLevel::Fine};
bulkAndWeights[static_cast<int>(Item::BlackPepper)] = {0.02f, 0.01f, BulkLevel::Fine};
bulkAndWeights[static_cast<int>(Item::Sinew)] = {0.02f, 0.01f, BulkLevel::Fine};
bulkAndWeights[static_cast<int>(Item::Thread)] = {0.005f, 0.003f, BulkLevel::Fine};
bulkAndWeights[static_cast<int>(Item::Needles)] = {0.005f, 0.002f, BulkLevel::Fine};
bulkAndWeights[static_cast<int>(Item::String)] = {0.01f, 0.005f, BulkLevel::Fine};
bulkAndWeights[static_cast<int>(Item::Wick)] = {0.01f, 0.005f, BulkLevel::Fine};
bulkAndWeights[static_cast<int>(Item::AnimalHair)] = {0.01f, 0.005f, BulkLevel::Fine};
bulkAndWeights[static_cast<int>(Item::ChiliPowder)] = {0.015f, 0.007f, BulkLevel::Fine};
bulkAndWeights[static_cast<int>(Item::GroundBlackPepper)] = {0.015f, 0.007f, BulkLevel::Fine};
bulkAndWeights[static_cast<int>(Item::Sugar)] = {0.03f, 0.015f, BulkLevel::Fine};
bulkAndWeights[static_cast<int>(Item::Salt)] = {0.03f, 0.02f, BulkLevel::Fine};
bulkAndWeights[static_cast<int>(Item::Fiber)] = {0.02f, 0.015f, BulkLevel::Fine};
bulkAndWeights[static_cast<int>(Item::Soot)] = {0.01f, 0.005f, BulkLevel::Fine};
bulkAndWeights[static_cast<int>(Item::Hay)] = {0.10f, 0.09f, BulkLevel::Fine};
bulkAndWeights[static_cast<int>(Item::Lime)] = {0.12f, 0.10f, BulkLevel::Fine};
bulkAndWeights[static_cast<int>(Item::Ash)] = {0.04f, 0.03f, BulkLevel::Fine};

//SEMI-FINE
bulkAndWeights[static_cast<int>(Item::LoamSoil)] = {0.4f, 1.6f, BulkLevel::SemiFine};
bulkAndWeights[static_cast<int>(Item::SiltySoil)] = {0.4f, 1.6f, BulkLevel::SemiFine};
bulkAndWeights[static_cast<int>(Item::SandySoil)] = {0.4f, 1.6f, BulkLevel::SemiFine};
bulkAndWeights[static_cast<int>(Item::Podzol)] = {0.4f, 1.6f, BulkLevel::SemiFine};
bulkAndWeights[static_cast<int>(Item::PeatSoil)] = {0.4f, 1.6f, BulkLevel::SemiFine};
bulkAndWeights[static_cast<int>(Item::RockySoil)] = {0.4f, 1.6f, BulkLevel::SemiFine};
bulkAndWeights[static_cast<int>(Item::Oxisol)] = {0.4f, 1.6f, BulkLevel::SemiFine};
bulkAndWeights[static_cast<int>(Item::Peat)] = {0.3f, 0.25f, BulkLevel::SemiFine};
bulkAndWeights[static_cast<int>(Item::Hemlock)] = {0.02f, 0.015f, BulkLevel::SemiFine};
bulkAndWeights[static_cast<int>(Item::Gravel)] = {0.15f, 0.20f, BulkLevel::SemiFine};
bulkAndWeights[static_cast<int>(Item::CrushedStone)] = {0.12f, 0.18f, BulkLevel::SemiFine};
bulkAndWeights[static_cast<int>(Item::Feather)] = {0.01f, 0.005f, BulkLevel::SemiFine};
bulkAndWeights[static_cast<int>(Item::Charcoal)] = {0.08f, 0.07f, BulkLevel::SemiFine};
//NOTE:WET
bulkAndWeights[static_cast<int>(Item::PavingStone)] = {0.15f, 0.18f, BulkLevel::SemiFine};
bulkAndWeights[static_cast<int>(Item::Concrete)] = {0.18f, 0.20f, BulkLevel::SemiFine};

//LOOSE
bulkAndWeights[static_cast<int>(Item::Nail)] = {0.05f, 0.003f, BulkLevel::Loose};
bulkAndWeights[static_cast<int>(Item::ClaySoil)] = {0.4f, 1.6f, BulkLevel::Loose};
bulkAndWeights[static_cast<int>(Item::Ring)] = {0.05f, 0.05f, BulkLevel::Loose};
bulkAndWeights[static_cast<int>(Item::Earring)] = {0.03f, 0.03f, BulkLevel::Loose};
bulkAndWeights[static_cast<int>(Item::Garlic)] = {0.04f, 0.02f, BulkLevel::Loose};
bulkAndWeights[static_cast<int>(Item::DuckEggs)] = {0.07f, 0.02f, BulkLevel::Loose};
bulkAndWeights[static_cast<int>(Item::Cheese)] = {0.06f, 0.03f, BulkLevel::Loose};
bulkAndWeights[static_cast<int>(Item::BlueCheese)] = {0.06f, 0.03f, BulkLevel::Loose};
bulkAndWeights[static_cast<int>(Item::GoatCheese)] = {0.06f, 0.03f, BulkLevel::Loose};
bulkAndWeights[static_cast<int>(Item::Butter)] = {0.05f, 0.03f, BulkLevel::Loose};
bulkAndWeights[static_cast<int>(Item::Shellfish)] = {0.06f, 0.04f, BulkLevel::Loose};
bulkAndWeights[static_cast<int>(Item::Bone)] = {0.065f, 0.02f, BulkLevel::Loose};
bulkAndWeights[static_cast<int>(Item::AnimalHides)] = {0.12f, 0.10f, BulkLevel::Loose};
bulkAndWeights[static_cast<int>(Item::Clips)] = {0.01f, 0.005f, BulkLevel::Loose};
bulkAndWeights[static_cast<int>(Item::Arrowhead)] = {0.02f, 0.015f, BulkLevel::Loose};
bulkAndWeights[static_cast<int>(Item::Lens)] = {0.02f, 0.015f, BulkLevel::Loose};
bulkAndWeights[static_cast<int>(Item::Peg)] = {0.02f, 0.015f, BulkLevel::Loose};
bulkAndWeights[static_cast<int>(Item::Rivet)] = {0.01f, 0.008f, BulkLevel::Loose};
bulkAndWeights[static_cast<int>(Item::Wedge)] = {0.03f, 0.025f, BulkLevel::Loose};
bulkAndWeights[static_cast<int>(Item::Socket)] = {0.02f, 0.015f, BulkLevel::Loose};
bulkAndWeights[static_cast<int>(Item::Trigger)] = {0.03f, 0.025f, BulkLevel::Loose};
bulkAndWeights[static_cast<int>(Item::Straw)] = {0.10f, 0.08f, BulkLevel::Loose};
bulkAndWeights[static_cast<int>(Item::Daub)] = {0.18f, 0.22f, BulkLevel::Loose};
bulkAndWeights[static_cast<int>(Item::Mortar)] = {0.20f, 0.25f, BulkLevel::Loose};
bulkAndWeights[static_cast<int>(Item::PackedEarth)] = {0.25f, 0.30f, BulkLevel::Loose};
bulkAndWeights[static_cast<int>(Item::Plaster)] = {0.16f, 0.18f, BulkLevel::Loose};

//SOFT
bulkAndWeights[static_cast<int>(Item::Scroll)] = {0.08f, 0.1f, BulkLevel::Soft};
bulkAndWeights[static_cast<int>(Item::Airbag)] = {0.3f, 0.2f, BulkLevel::Soft};
bulkAndWeights[static_cast<int>(Item::Linen)] = {0.04f, 0.03f, BulkLevel::Soft};
bulkAndWeights[static_cast<int>(Item::Silk)] = {0.05f, 0.04f, BulkLevel::Soft};
bulkAndWeights[static_cast<int>(Item::Cloth)] = {0.06f, 0.05f, BulkLevel::Soft};
bulkAndWeights[static_cast<int>(Item::Rope)] = {0.5f, 0.07f, BulkLevel::Soft};
bulkAndWeights[static_cast<int>(Item::Bandage)] = {0.04f, 0.03f, BulkLevel::Soft};

//SOLID
bulkAndWeights[static_cast<int>(Item::Book)] = {2.0f, 0.4f, BulkLevel::Solid};
bulkAndWeights[static_cast<int>(Item::Candle)] = {0.7f, 0.1f, BulkLevel::Solid};
bulkAndWeights[static_cast<int>(Item::OilLamp)] = {4.0f, 0.6f, BulkLevel::Solid};
bulkAndWeights[static_cast<int>(Item::SmoothedPebbles)] = {0.3f, 1.0f, BulkLevel::Solid};
bulkAndWeights[static_cast<int>(Item::Javelin)] = {1.2f, 1.8f, BulkLevel::Solid};
bulkAndWeights[static_cast<int>(Item::Arrow)] = {0.2f, 0.2f, BulkLevel::Solid};
bulkAndWeights[static_cast<int>(Item::Horseshoes)] = {0.7f, 1.5f, BulkLevel::Solid};
bulkAndWeights[static_cast<int>(Item::Torch)] = {0.35f, 0.8f, BulkLevel::Solid};

bulkAndWeights[static_cast<int>(Item::Incense)] = {4.2f, 0.025f, BulkLevel::Solid};  // Unusual combo, lightweight but voluminous
bulkAndWeights[static_cast<int>(Item::MedicinalSoap)] = {4.8f, 0.03f, BulkLevel::Solid};  // Again, lightweight but bulky
bulkAndWeights[static_cast<int>(Item::Glass)] = {6.5f, 0.8f, BulkLevel::Solid};
bulkAndWeights[static_cast<int>(Item::Strap)] = {0.05f, 0.04f, BulkLevel::Solid};
//bulkAndWeights[static_cast<int>(Item::HeavyTannedHide)] = {0.20f, 0.22f, BulkLevel::Solid};
bulkAndWeights[static_cast<int>(Item::NailHeader)] = {0.08f, 0.10f, BulkLevel::Solid};

bulkAndWeights[static_cast<int>(Item::Wood)] = {2.3f, 2.8f, BulkLevel::Solid};
bulkAndWeights[static_cast<int>(Item::Plank)] = {1.6f, 2.2f, BulkLevel::Solid};
bulkAndWeights[static_cast<int>(Item::Timber)] = {12.0f, 8.5f, BulkLevel::Solid};
bulkAndWeights[static_cast<int>(Item::Stave)] = {2.1f, 2.2f, BulkLevel::Solid};
bulkAndWeights[static_cast<int>(Item::LongStave)] = {4.6f, 6.5f, BulkLevel::Solid};
bulkAndWeights[static_cast<int>(Item::Beam)] = {2.3f, 3.5f, BulkLevel::Solid};
bulkAndWeights[static_cast<int>(Item::LogBeam)] = {33.5f, 40.0f, BulkLevel::Solid};
bulkAndWeights[static_cast<int>(Item::CutStone)] = {12.0f, 15.0f, BulkLevel::Solid};
bulkAndWeights[static_cast<int>(Item::CutStoneSheet)] = {3.1f, 2.3f, BulkLevel::Solid};
bulkAndWeights[static_cast<int>(Item::CurvedStone)] = {8.2f, 12.0f, BulkLevel::Solid};
bulkAndWeights[static_cast<int>(Item::Cob)] = {0.10f, 0.12f, BulkLevel::Solid};
bulkAndWeights[static_cast<int>(Item::FiredClay)] = {0.14f, 0.16f, BulkLevel::Solid};
bulkAndWeights[static_cast<int>(Item::Bricks)] = {1.8f, 2.3f, BulkLevel::Solid};
bulkAndWeights[static_cast<int>(Item::Pane)] = {6.0f, 0.6f, BulkLevel::Solid};
bulkAndWeights[static_cast<int>(Item::ColoredPane)] = {6.0f, 0.6f, BulkLevel::Solid};
bulkAndWeights[static_cast<int>(Item::Axle)] = {3.8f, 4.0f, BulkLevel::Solid};
bulkAndWeights[static_cast<int>(Item::Gear)] = {0.2f, 0.07f, BulkLevel::Solid};
bulkAndWeights[static_cast<int>(Item::BrickMold)] = {1.10f, 0.8f, BulkLevel::Solid};
bulkAndWeights[static_cast<int>(Item::SmallHandle)] = {1.85f, 1.54f, BulkLevel::Solid};
bulkAndWeights[static_cast<int>(Item::LargeHandle)] = {4.05f, 3.84f, BulkLevel::Solid};
bulkAndWeights[static_cast<int>(Item::StoneTablet)] = {2.30f, 5.25f, BulkLevel::Solid};
bulkAndWeights[static_cast<int>(Item::Glass)] = {2.2f, 0.10f, BulkLevel::Solid};
bulkAndWeights[static_cast<int>(Item::Strap)] = {0.05f, 0.04f, BulkLevel::Solid};
bulkAndWeights[static_cast<int>(Item::NailHeader)] = {0.08f, 0.10f, BulkLevel::Solid};

//NOTE: maybe change
bulkAndWeights[static_cast<int>(Item::Wheel)] = {18.5f, 6.18f, BulkLevel::Solid};
bulkAndWeights[static_cast<int>(Item::LargeAxle)] = {20.15f, 12.18f, BulkLevel::Solid};
bulkAndWeights[static_cast<int>(Item::EmperorsStaff)] = {17.2f, 3.5f, BulkLevel::Solid};
bulkAndWeights[static_cast<int>(Item::HorseSaddle)] = {29.2f, 5.5f, BulkLevel::Solid};
bulkAndWeights[static_cast<int>(Item::OxSaddle)] = {29.5f, 7.0f, BulkLevel::Solid};

//SINGLE
bulkAndWeights[static_cast<int>(Item::ArtificialBeehive)] = {40.0f, 8.0f, BulkLevel::Single};
bulkAndWeights[static_cast<int>(Container::Keg) + static_cast<int>(Item::MAX)] = {48.8f, 14.2f, BulkLevel::Single};
bulkAndWeights[static_cast<int>(Item::SolidWheel)] = {55.70f, 25.5f, BulkLevel::Single};
}

#endif // ITEMBULKANDWEIGHT_H_
