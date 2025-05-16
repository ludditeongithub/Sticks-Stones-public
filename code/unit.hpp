#ifndef UNIT_H_
#define UNIT_H_

#include "basic.hpp"
#include "categories.hpp"
#include "itemRecipes.hpp"

// the total volume of each bulk category hands can maximally carry.
// where 0.1 is 100mL
// NOTE: idea: consider doing left and right
const float fineBulkMax = 0.3;
const float looseBulkMult = 5.5;
const float softBulkMult = 2.5;
const float solidBulkMult = 1.0;
const float midBulkMax = 35.0;
const float singleBulk = 60.0;

//mas weights pawns can carry
const float childMaxCarry = 30.0;
const float maxCarry = 85.0;

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
            return;
    }
}

float getContainerCapacity(ContainerType c) {
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
            return;
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
    std::pair<Tool,Material> leftHand;
    std::pair<Tool,Material> rightHand;
    vector<std::pair<Item, uint16_t>> items; //contains all non-variant items
    vector<std::pair<Item, uint16_t>> variantItems; //contains all variant items
    vector<uint16_t> variantItemTypes; //the enum relevant number for the enum class
    float currentBulk = 0.0;// in hands, not in containers
    BulkStatus currentBulkStatus = BulkStatus::NONE;
    float currentWeight = 0; // in hands, not in containers
    float totalBulk = 0.0;
    float totalWeight = 0.0;
};
//ALL
/* inventory cont'd */
vector<Inventory> inventories;
vector<vector<std::pair<Tool,Material>>> tools;
vector<vector<Container>> containers;

/* end */
vector<bool> occupied;
vector<vector<Role>> roles;
vector<bool> sex; //t = male, f = female
vector<std::pair<int,int>> currentCoords;
vector<Direction> currentDirections;
//RESOURCES


//PRODUCERS
using ProductVariant<Item, Vehicle, Buildable>;
vector<ProductVariant> currentProducts;


#endif // UNIT_H_
