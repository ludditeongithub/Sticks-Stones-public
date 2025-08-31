#ifndef UNIT_H_
#define UNIT_H_

#include "basic.hpp"
#include "categories.hpp"
#include "itemRecipes.hpp"

// contains basic info that appplies to all units

constexpr int startingRoleMana = 10;

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
