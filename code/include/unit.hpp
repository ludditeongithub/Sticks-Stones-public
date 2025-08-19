#ifndef UNIT_H_
#define UNIT_H_

#include "basic.hpp"
#include "categories.hpp"
#include "itemRecipes.hpp"

// contains basic info that appplies to all units

constexpr int startingRoleMana = 10;

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

struct Inventory {
    std::pair<uint8_t, Material> leftHand; //if Material == NONE, then it it CARRYING
    std::pair<uint8_t, Material> rightHand; //if Material == NONE, then it it CARRYING
    vector<std::pair<Item, uint16_t>> items; //contains all non-variant items
    vector<std::pair<Item, uint16_t>> variantItems; //contains all variant items
    vector<uint16_t> variantItemTypes; //the enum relevant number for the enum class
    float currentBulk = 0.0;// in hands, not in containers
    BulkStatus currentBulkStatus = BulkStatus::NONE;
    float currentWeight = 0.0; // in hands, not in containers
};
//ALL
/* inventory cont'd */
vector<Inventory> inventories;
vector<vector<std::pair<Tool,Material>>> tools;
vector<vector<Container>> containers;

/* end */

vector<vector<Role>> roles; //roles at front are prioritized in queue
vector<int> currentRoleIndex;
vector<bool> sex; //t = male, f = female
vector<std::pair<int,int>> currentCoords;
vector<Object> currentTargets;
vector<int> currentDest; //indices, can function as animal indices/human indices or tile indices depending on moving context
vector<Direction> currentDirections;
vector<MovingStatus> movingStatus;
vector<uint16_t> health;
vector<uint16_t> inertias;
vector<uint16_t> remainingRoleMana;

//TODO: work on future/consolidated futures
std::vector<std::promise<void>> findPromise;
std::vector<std::future<void>> findFuture;
//RESOURCES


//PRODUCERS
using ProductVariant<Item, Container, Vehicle, Buildable>;
vector<ProductVariant> currentProducts;

#endif // UNIT_H_
