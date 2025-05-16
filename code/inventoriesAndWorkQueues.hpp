#ifndef INVENTORIESANDWORKQUEUES_H_
#define INVENTORIESANDWORKQUEUES_H_
#include "basic.hpp"
#include "categories.hpp"
#include "itemRecipes.hpp"
#include "cropdata.hpp"
#include "unit.hpp"

//TILE DATA
uint16_t addItems(int pawn, Item item, uint16_t productAmount) {
    float remainingSpace = min(currentMaxBulk(inventories[pawn].currentBulkStatus, false) - inventories[pawn].totalBulk, 0);
    uint16_t amount = (uint16_t) min((productAmount, (int)(remainingSpace / bulkAndWeights[item].bulk)));
    if (remainingSpace > bulksAndWeights[static_cast<int>(item)].bulk) {
    if (amount > 0) {
        for (int i = 0; i < inventories[pawn].items.size(); i++) {
            if (inventories[pawn].items[i].first == item) {
                inventories[pawn].items[i].second += amount;
                return productAmount - amount;
            }
        }
        inventories[pawn].items.push_back(item, amount);
    }
    }
    return productAmount - amount;
}

uint16_t addVariantItems(int pawn, Item item, uint16_t productAmount, int variant) {
    float remainingSpace = min(currentMaxBulk(inventories[pawn].currentBulkStatus, false) - inventories[pawn].totalBulk, 0);
        uint16_t amount = (uint16_t) min((productAmount, (int)(remainingSpace / bulkAndWeights[item].bulk)));
    if (remainingSpace > bulksAndWeights[static_cast<int>(item)].bulk) {
    if (amount > 0) {
        for (int i = 0; i < inventories[pawn].variantItems.size(); i++) {
            if (inventories[pawn].variantItems[i].first == item && inventories[pawn].variantItemTypes[i] == variant) {
                inventories[pawn].variantItems[i].second += amount;
                return productAmount - amount;
            }
        }
        inventories[pawn].variantItems.push_back(item, amount);
        inventories[pawn].variantItemTypes.push_back(variant);
    }
    }
    return productAmount - amount;
}

void removeItem(int pawn, int index, uint16_t amount) {
    inventories[pawn].items[index].second -= amount;
}

void removeVariantItem(int pawn, int index, uint16_t amount) {
    inventories[pawn].variantItems[index].second -= amount;
}

void dropContainer(int pawn, int index) {
    //TODO: code container on ground with items
    inventories[pawn].containers[index] = ContainerType::NONE;
}

uint16_t addItemToContainer(int pawn, Container& container, Item item, uint16_t amount) {
    SizeData sd = bulkAndWeights[static_cast<int>(item)];
    float remainderBulk = getContainerCapacity(container.containerType) - container.currentBulk;
    if (remainderBulk < sd.bulk || validContainer(container, item) return productAmount;
    Inventory& in = inventories[pawn];
    uint16_t amount = (uint16_t) min(min((productAmount, (int)(remainderBulk / bulkAndWeights[item].bulk))), in.items[itemIndex].second);
    container.currentBulk += sd.bulk * amount;
    container.curentWeight += sd.weight * amount;
    for (int i = 0; i < container.items.size(); i++) {
        if (container.items[i].first == item) container.items[i].second += amount;
        return productAmount - amount;
    }
    container.items.push_back(item, amount);
    return productAmount - amount;
}

uint16_t inventoryToContainer(int pawn, Container& container, int itemIndex, uint16_t productAmount) {
    SizeData sd = bulkAndWeights[static_cast<int>(item)];
    float remainderBulk = getContainerCapacity(container.containerType) - container.currentBulk;
    if (remainderBulk < sd.bulk || validContainer(container, item)) return productAmount;
    Inventory& in = inventories[pawn];
    uint16_t amount = (uint16_t) min(min((productAmount, (int)(remainderBulk / bulkAndWeights[item].bulk))), in.items[itemIndex].second);
    Item item = in.items[itemIndex].first;
    container.currentBulk += sd.bulk * amount;
    container.curentWeight += sd.weight * amount;
    in.currentBulk -= sd.bulk * amount;
    in.currentWeight -= sd.weight * amount;
    if (currentBulk[pawn] == 0) currentBulkStatus = BulkStatus::NONE;
    in.items[itemIndex].second -= amount;
    if (in.items[itemIndex].second == 0) in.items[itemIndex].first == Item::NONE;
    for (int i = 0; i < container.items.size(); i++) {
        if (container.items[i].first == item) container.items[i].second += amount;
        return productAmount - amount;
    }
    container.items.push_back(item, amount);
    return productAmount - amount;
}

void moveItemBetweenContainers(int pawn, Container& from, Container& to, Item item) {

}


uint16_t addVariantItemToContainer(int pawn, Container& container, Item item, uint16_t variant, uint16_t productAmount) {
    SizeData sd = bulkAndWeights[static_cast<int>(item)];
    float remainderBulk = getContainerCapacity(container.containerType) - container.currentBulk;
    if (remainderBulk < sd.bulk || validContainer(container, item)) return productAmount;
    Inventory& in = inventories[pawn];
    uint16_t amount = (uint16_t) min(min((productAmount, (int)(remainderBulk / bulkAndWeights[item].bulk))), in.variantItems[itemIndex].second);
    container.currentBulk += sd.bulk * amount;
    container.curentWeight += sd.weight * amount;
    for (int i = 0; i < container.variantItems.size(); i++) {
        if (container.variantItems[i].first == item) container.variantItems[i].second += amount;
        return productAmount - amount;
    }
    container.variantItems.push_back(item, amount);
    container.variantItemTypes.push_back(variant);
    return productAmount - amount;
}

uint16_t variantInventoryToContainer(int pawn, Container& container, int itemIndex, uint16_t amount) {
    SizeData sd = bulkAndWeights[static_cast<int>(item)];
    float remainderBulk = getContainerCapacity(container.containerType) - container.currentBulk;
    if (remainderBulk < sd.bulk || validContainer(container, item)) return productAmount;
    Inventory& in = inventories[pawn];
    uint16_t amount = (uint16_t) min(min((productAmount, (int)(remainderBulk / bulkAndWeights[item].bulk))), in.variantItems[itemIndex].second);
    Item item = in.variantItems[itemIndex].first;
    container.currentBulk += sd.bulk * amount;
    container.curentWeight += sd.weight * amount;
    in.currentBulk -= sd.bulk * amount;
    in.currentWeight -= sd.weight * amount;
    if (currentBulk[pawn] == 0) currentBulkStatus = BulkStatus::NONE;
    in.variantItems[itemIndex].second -= amount;
    if (in.variantItems[itemIndex].second == 0) in.variantItems[itemIndex].first == Item::NONE;
    for (int i = 0; i < container.variantItems.size(); i++) {
        if (container.variantItems[i].first == item) container.variantItems[i].second += amount;
        return productAmount - amount;
    }
    container.variantItems.push_back(item, amount);
    container.variantItemTypes.push_back(variant);
    return productAmount - amount;
}

uint16_t containerToInventory() {

}

uint16_t variantContainerToInventory() {

}

//
void dropItem(int pawn, int itemIndex, uint16_t amount) {
    std::pair<int,int> tile = currentCoords[pawn];
    //TODO: create check if empty, and put on tile if so


}

void dropVariantItem(int pawn, int itemIndex,  uint16_t variant, uint16_t amount) {

}


//variantIndex superfluous for non-variant items
void getResourceAction(int pawn, Item item, int sourceIndex, int variantIndex) {
    Resource resource = resources[item];
    Action action = resource.action[sourceVariantIndex];
    SourceVariant source = resource.source[sourceIndex];
    //see if Object should be removed from tile
    bool removeObject = true;
    if (action == Action::Collect) {
        if (source == Tile::ShallowWater || source == Tile::FlowingWater || source == Tile::DeepWater || source == Tile::ShallowSaltWater || source == Tile::Sand || source == Scavengeable::Beehive || source == Scavengeable::ArtificialBeehive) {
            removeObject = false;
        }
    }
    if (removeObject)
    if (action == Action::Milk) removeObject = false;
    else if (action == Action::GoatMilk) removeObject = false;
    else if (action == Action::Fish) removeObject = false;
    else if (action == Action::Shear) removeObject = false;
    else for (int i = 0; i < regrowthCrops.size(); i++) {
        if (item == regrowthCrops[i]) {
            removeObject = false;
        }
    }
    // Get amount of item to put into inventory
    if (action == Action::Lift) {
        Inventories[pawn].leftHand == Tool::Log;
        Inventories[pawn].rightHand == Tool::Log;
    } else {
        int amt = resources[item].amount[sourceIndex];
        // if item in question is an item with variants
        if (static_cast<int>(item) < static_cast<int>(Item::VARIANTSMAX)) {
            Inventories[pawn].variantItems.push_back({item, amt});
            Inventories[pawn].variantItemTypes.push_back(variantIndex);
        } else {
            Inventories[pawn].items.push_back({item, amt});
        }
    }
}

//FIND COORDS OF NEAREST OF ANY SOURCE VARIANT
std::pair<int,int> findNearestSource(SourceVariant source, std::pair<float,float> queryPoint) {
    int numResults = 1;
    uint32_t retIndex[numResults];
    float outDistSqr[numResults];
    switch(source) {
        case Tile::FlowingWater:
        case Tile::ShallowWater:
        case Tile::DeepWater:
            water.knnSearch(&queryPoint[0], numResults, &retIndex[0], &outDistSqr[0]);
            return nearestWaterTiles[retIndex[0]];
        case Scavengeable::Log:
            log.knnSearch(&queryPoint[0], numResults, &retIndex[0], &outDistSqr[0]);
            return nearestLog[retIndex[0]];
        case Scavengeable::Pebble:
        case Scavengeable::Rock:
        case Scavengeable::LargeRock:
            rock.knnSearch(&queryPoint[0], numResults, &retIndex[0], &outDistSqr[0]);
            return nearestRocks[retIndex[0]];
        case Tile::Sand:
        case Tile::SandySoil:
            sand.knnSearch(&queryPoint[0], numResults, &retIndex[0], &outDistSqr[0]);
            return nearestSand[retIndex[0]];
        case Tile::Clay:
        case Tile::ClaySoil:
            clay.knnSearch(&queryPoint[0], numResults, &retIndex[0], &outDistSqr[0]);
            return nearestClay[retIndex[0]];
        case Tile::Podzol:
        case Tile::LoamSoil:
        case Tile::PeatSoil:
        case Tile::SiltySoil:
        case Tile::RockySoil:
        case Tile::Oxisol:
            dirt.knnSearch(&queryPoint[0], numResults, &retIndex[0], &outDistSqr[0]);
            return nearestDirt[retIndex[0]];
        case Tile::Stone:
            stone.knnSearch(&queryPoint[0], numResults, &retIndex[0], &outDistSqr[0]);
            return nearestStone[retIndex[0]];
        case Scavengeable::Flint:
            flint.knnSearch(&queryPoint[0], numResults, &retIndex[0], &outDistSqr[0]);
            return nearestFlint[retIndex[0]];
        case Tile::RockSalt:
            salt.knnSearch(&queryPoint[0], numResults, &retIndex[0], &outDistSqr[0]);
            return nearestSalt[retIndex[0]];
        case Animal::Goat:
        case Animal::Cow:
            milk.knnSearch(&queryPoint[0], numResults, &retIndex[0], &outDistSqr[0]);
            return nearestMilks[retIndex[0]];
        case Scavengeable::Beehive:
        case Scavengeable::ArtificialBeehive:
            beehive.knnSearch(&queryPoint[0], numResults, &retIndex[0], &outDistSqr[0]);
            return nearestBeehive[retIndex[0]];
        case Animal::Sheep:
            sheep.knnSearch(&queryPoint[0], numResults, &retIndex[0], &outDistSqr[0]);
            return nearestSheep[retIndex[0]];
        case Plant::OrangeTree:
        case Plant::LemonTree:
        case Plant::LimeTree:
        case Plant::PeachTree:
        case Plant::PlumTree:
        case Plant::CherryTree:
        case Plant::ApricotTree:
        case Plant::AppleTree:
        case Plant::PearTree:
        case Plant::BlueberryShrub:
        case Plant::StrawberryShrub:
        case Plant::Grapevine:
            fruit.knnSearch(&queryPoint[0], numResults, &retIndex[0], &outDistSqr[0]);
            return nearestFruits[retIndex[0]];
        case Plant::Wheat:
        case Plant::Oat:
        case Plant::Rice:
        case Plant::Corn:
            grain.knnSearch(&queryPoint[0], numResults, &retIndex[0], &outDistSqr[0]);
            return nearestGrains[retIndex[0]];
        case Plant::Broccoli:
        case Plant::Tomato:
        case Plant::Pepper:
        case Plant::Lettuce:
        case Plant::Onion:
        case Plant::Garlic:
        case Plant::Potato:
        case Plant::Carrot:
        case Plant::Beets:
        case Plant::Kale:
        case Plant::Corn:
        case Plant::Cucumber:
        case Plant::Cabbage:
            vegetable.knnSearch(&queryPoint[0], numResults, &retIndex[0], &outDistSqr[0]);
            return nearestVegetables[retIndex[0]];
        case Plant::Senna:
        case Plant::Woad:
        case Plant::Indigo:
        case Plant::Poppies:
        case Plant::Ginseng:
        case Plant::Lavendar:
        case Plant::Hemp:
        case Plant::Sage:
        case Plant::Madder:
        case Plant::Mint:
        case Plant::Thyme:
            herb.knnSearch(&queryPoint[0], numResults, &retIndex[0], &outDistSqr[0]);
            return nearestHerbs[retIndex[0]];
        case Plant::Hemp:
        case Plant::Cotton:
        case Plant::Flax:
            textile.knnSearch(&queryPoint[0], numResults, &retIndex[0], &outDistSqr[0]);
            return nearestTextiles[retIndex[0]];
    }
}

//RESOURCES PAWN MANAGEMENT

// gets resource at certain tile, when pawn is adjacent to it, by confirming action.
void getResource(Item item) {
    if (item < Item::RESOURCEMAX) return;
    Source resource = resources[item];
    //find available pawns who can perform actions (On^3)
    bool foundPawn = false;
    int pawnIndex;
    int actionIndex;
    Role role;
    for (int i = 0; i < occupied.size(); i++) { // check each pawn
        if (occupied[i] <= 0) {
            for (int j = 0; j < roles[i].size(); j++) {
                for (int k = 0; k < resources.action.size(); k++) {
                    if (actionToRoles[resources.action[k]] == roles[i][j]) {
                        pawnIndex = i;
                        actionIndex = k;
                        role = roles[i][j];
                        foundPawn = true;
                    }
                    if (foundPawn) break;
            }
            if (foundPawn) break;
        }
        if (foundPawn) break;
    }
    //get compatible SourceVariant (Tile, Plant, Animal, Scavengeable, or Item)
    SourceVariant source = resource.source[actionIndex];
    std::pair<int,int> coords = findNearestSource(source);
    //SHORTEST PATH ALGORITHM

    }
}



// void attemptResource(int pawn, Role role) {
//     //TODO: add queued actions for each that trigger once destination is reached.
//     //TODO: specific metal hints, specific crops, DairyFarmer, Papyrus
//     std::vector<float> queryPoint = currentCoords[pawn];
//     int index = tileIndex[currentCoords[pawn]];
//     size_t numResults = 1;
//     uint32_t retIndex[numResults]; // nearest neighbor index
//     float outDistSqr[numResults]; //distance between nn and current
//     float radius = 200;
//     switch(role) {
//         case Role::Scavenger:
//         case Role::Gatherer:
//             //TODO: if inventory is full, unload
//             // if not, scavenge
//             scavengeables.knnSearch(&queryPoint[0], numResults, &retIndex[0], &outDistSqr[0]);
//             int nearestIndex = retIndex[0];
//             //TODO: if digging stick in inventory, then diggables are valid too.
//             break;
//         case Role::EarthGatherer:

//         case Role::FishHunter:
//         case Role::Fisherman:
//             water.knnSearch(&queryPoint[0], numResults, &retIndex[0], &outDistSqr[0]);
//             int nearestIndex = retIndex[0];
//             break;
//         case Role::Woodcutter:
//             tree.knnSearch(&queryPoint[0], numResults, &retIndex[0], &outDistSqr[0]);
//             int nearestIndex = retIndex[0];
//             break;
//         case Role::SpearHunter:
//         case Role::BowHunter:
//         case Role::Herder:
//         case Role::Shepherd:
//         case Role::PoultryFarmer:
//         case Role::DraftMaster:
//         case Role::HorseBreeder:
//             //TODO: make algorithm to find nearest animal last known locations, and then based on sight when reached

//             //TODO: only find animals if less than max animals
//             boolean found = false; float maxRadius = 1000;
//             int nearestIndex;
//             while (!found && radius < maxRadius) {
//             std::vector<std::pair<size_t, float>> resultSet;
//                  animal.radiusSearch(&queryPoint[0], radius, resultSet, nanoflann::SearchParams());
//             for (int i = 0; i < checkNumResults; i++) {
//                 if (role == Role::SpearHunter || role == Role::BowHunter) {
//                      for (int j = 0; j < draft.size(); j++) {
//                     if (animals[nextIndex] == !draft[j]) {
//                         nearestIndex = resultSet[i].first;
//                         found = true;
//                         break;
//                     }
//                     }
//                 } else if (role == Role::Shepherd) {
//                     for (int j = 0; j < shepherdables.size(); j++) {
//                     if (animals[nextIndex] == shepherdables[j]) {
//                         nearestIndex = resultSet[i].first;
//                         found = true;
//                         break;
//                     }
//                     }
//                 } else if (role == Role::Herder){
//                        for (int j = 0; j < herdables.size(); j++) {
//                     if (animals[nextIndex] == herdables[j]) {
//                         nearestIndex = resultSet[i].first;
//                         found = true;
//                         break;
//                     }
//                 }
//                 } else if (role == Role::PoultryFarmer){
//                     for (int j = 0; j < poultry.size(); j++) {
//                     if (animals[nextIndex] == poultry[j]) {
//                         nearestIndex = resultSet[i].first;
//                         found = true;
//                         break;
//                     }
//                 }
//                 } else if (role == Role::DraftMaster){
//                    for (int j = 0; j < draft.size(); j++) {
//                     if (animals[nextIndex] == draft[j]) {
//                         nearestIndex = resultSet[i].first;
//                         found = true;
//                         break;
//                     }
//                 }
//             } else if (role == Role::HorseBreeder) {
//                     if (animals[nextIndex] == Animal::Horse) {
//                         nearestIndex = resultSet[i].first;
//                         found = true;
//                     }
//                 }
//             }
//             radius *= 2;
//             }
//             break;
//         case Role::DairyFarmer:
//             std::vector<std::pair<size_t, float>> resultSet;
//                  animal.radiusSearch(&queryPoint[0], radius, resultSet, nanoflann::SearchParams());
//             for (int j = 0; j < milkable.size(); j++) {
//                     if (animals[nextIndex] == milkable[j]) {
//                         nearestIndex = resultSet[i].first;
//                         found = true;
//                         break;
//                     }
//                 }
//             if (found) break;
//             }
//             break;
//         case Role::StoneMiner:
//         case Role::CopperMiner:
//         case Role::IronMiner:
//         case Role::GoldMiner:
//         case Role::QuarryMiner:
//         case Role::SilverMiner:
//         case Role::GemstoneMiner:
//         case Role::SaltMiner:
//             stone.knnSearch(&queryPoint[0], numResults, &retIndex[0], &outDistSqr[0]);
//             int nearestIndex = retIndex[0];
//             break;
//         case Role::Herbalist:
//             herb.knnSearch(&queryPoint[0], numResults, &retIndex[0], &outDistSqr[0]);
//             break;
//         case Role::CerealFarmer:
//         case Role::FlaxFarmer:
//         case Role::HerbFarmer:
//         case Role::Horticultarlist:
//         case Role::VineyardWorker:
//         case Role::OrchardFarmer:
//         case Role::CottonFarmer:
//             vector<Plant> harvest = plantRoleMap(role);
//             bool found = false;
//             //here only harvesting is settled-- planting and weeding is a support class
//         while (!found) {
//             harvestable.radiusSearch(&queryPoint[0], radius, resultSet, nanoflann::SearchParams());
//                 int nextIndex = retIndex[i];
//                 for (int i = 0; i < harvest.size(); i++) {
//                      if (tilePlant[nextIndex] == harvest[i]) {
//                          int nearestIndex = nextIndex;
//                          found = true;
//                          break;
//                      }
//                 }
//             radius *= 2;
//         }
//             break;
//         case Role::Herbalist:
//             herb.knnSearch(&queryPoint[0], numResults, &retIndex[0], &outDistSqr[0]);
//                 int nearestIndex = retIndex[0];
//                 break;
//         case Role::CopperMiner:
//             //TODO: first search for copper hints
//             //then just mine stone
//             break;
//         case Role::Beekeeper:
//             //get honey
//             beehive.knnSearch(&queryPoint[0], numResults, &retIndex[0], &outDistSqr[0]);
//             int nearestIndex = retIndex[0];
//             break;
//     }
//     std::pair<int,int> targetTile = tileCoords[nearestIndex];
//     //TODO: trigger moveto then get resource at target tile, search again for animals or moving target

// }

bool checkActionRequisites(Recipe recipe, int pawn) {
    if !(recipe.action == Actions::NONE) {
        //confirm pawn can perform action necessary to produce product
        Actions action = recipe.action;
         bool foundRole = false;
         for (int j = 0; j < actionToRoles[action].size(); j++) {
             for (int k = 0; k < roles[pawn].size; k++) {
                 if (actionToRoles[action][j] == roles[pawn][k]) {
                     foundRole = true;
                     break;
                 }
             }
         }
         if (!foundAction) return false;
    }
         bool foundTools = true;
         int toolReplaceableList = actionToToolsReplaceables[action];
         for (int j = 0; j < actionToTools[action].size(); j++) {
             if (toolReplaceableList[j] < 0) continue; //optional tools
             for (int k = 0; k < Tools[pawn].size; k++) {
                 if (actionToTools[action][j] == tools[pawn][k]) {
                     while (toolReplaceableList[j] == toolReplaceableList[j+1]) j++;
                 } else {
                     foundTools = false;
                     break;
                 }
                 if (!foundTools) break;
             }
         }
         if (!foundTools) return false;
         return true;
}

//PRODUCTS PAWN MANAGEMENT
// TODO: have pawns search nearby surroundings for items if not found, if on
// Check inventory to produce new items
void attemptProduction(int pawn, ProductVariant product, ItemType itemType) {
    bool attemptAlternateRecipe = false;
    for (int i = 0; i < 2; i++) {
    if (itemType == 0) {
        attemptAltenateRecipe ? return : Recipe recipe = products[static_cast<int>(product)] ;
    } else if (itemType == 1) {
        attemptAltenateRecipe ? return : VehicleRecipe recipe = vehicles[static_cast<int>(product)] ;
    } else if (itemType == 2) {
        attemptAlternateRecipe ? BuildableRecipe recipe = buildablesAlternateInterpreter(product) : BuildableRecipe recipe = buildables[static_cast<int>(product)];
    } else if (itemType == 3) {
        attemptAlternateRecipe ? return : ToolRecipe recipe = tools[static_cast<int>(product)];
    } else if (itemType == 4) {
        attemptAlternateRecipe ? return : ConatainerRecipe recipe = containers[static_cast<int>(product)];
    }

    if (!checkActionRequisites(recipe, pawn)) {
        vector<std::pair<int, int>> ingredientsFound;
    vector<std::pair<int, int>> variantIngredientsFound;

    //FOR LIQUIDS
    if (recipe.itemTags.hasTag(itemTags::Liquid)) {
        //TODO: find nearest unprocessing liquid vessel, or get from inventory if none

        int maxAmount = 99999;
        for (int i = 0; i < recipe.ingredients.size(); i++) {
            // TODO: get amount of liquid in found vessel
                for (int j = 0; j < inventories[pawn].items.size(); j++) {
            if (inventories[pawn].items[i].first == recipe.ingredients[i] && inventories[pawn].items[j].second >= recipe.amounts[i]) {
                //find which recipe item is the bottleneck for mixing the liquid, or if the amount of water in container is the factor
                if (maxAmount > (int)(inventories[pawn]recipe.amounts[j] / recipe.ingredients[i])) maxAmount = (int)(inventories[pawn]recipe.amounts[j] / recipe.ingredients[i]);

                //add the right amount of the type of item in inventory
                ingredientsFound.push_back({i, recipe.amounts[i]});
                foundIngredient = true;
                while (recipe.replaceables[i] == recipe.replaceables[i+1]) i++;
                break;
            }
        }
            for (int j = 0; j < inventories[pawn].variantItems.size(); j++) {
                    if (inventories[pawn].variantItems[j].first == recipe.ingredients[i] && inventories[pawn].variantItems[j].second >= recipe.amounts[i]) {
                                //find which recipe item is the bottleneck for mixing the liquid, or if the amount of water in container is the factor
                if (maxAmount > (int)(inventories[pawn]recipe.amounts[j] / recipe.ingredients[i])) maxAmount = (int)(inventories[pawn]recipe.amounts[j] / recipe.ingredients[i]);

                //add the right amount of the type of item in inventory
                variantIngredientsFound.push_back({i, recipe.amounts[i]});
                foundIngredient = true;
                break;
                    }
        } if (!foundIngredient) {
        if (!attemptAlternateRecipe) {
            attemptAlternateRecipe = true;
        } else return; //item not craftable
    } else {
        //start crafting
        occupied[pawn] = true;
        addEvent(products[static_cast<int>(product)].time, EventType::ProductComplete, product, pawn);
        for (int i = 0; i < ingredientsFound.size(); i++) {
            removeItem(pawn, ingredientsFound.first, ingredientsFound.second);
        }
        for (int i = 0; i < variantIngredientsFound.size(); i++) {
            removeItem(pawn, variantIngredientsFound.first, variantIngredientsFound.second);
        }
    }
    }
    }
    //CORPSE
    else if (recipe.itemTags.hasTag(itemTags::Corpse)) {
        //TODO: determine how pawn focuses on station, on when it lets go, go find corpse if needed
    }
    //NORMAL ITEMS
    else {
        for (int i = 0; i < recipe.ingredients.size(); i++) {
        if (recipe.replaceables[i] == 0) { //optional ingredient
            //TODO: optional ingredient interpreter
        }
        if (recipe.ingredients[i] == Item::EMPTY) continue;
        bool foundIngredient = false;
         //loop through non-variant items
    for (int j = 0; j < inventories[pawn].items.size(); j++) {
            if (inventories[pawn].items[i].first == recipe.ingredients[i] && inventories[pawn].items[j].second >= recipe.amounts[i]) {
                //add the right amount of the type of item in inventory
                ingredientsFound.push_back({i, recipe.amounts[i]});
                foundIngredient = true;
                while (recipe.replaceables[i] == recipe.replaceables[i+1]) i++;
        }
        if (foundIngredient) break;
    }
    //loop through variant items
    for (int j = 0; j < inventories[pawn].variantItems.size(); j++) {
        if (inventories[pawn].variantItems[j].first == recipe.ingredients[i] && inventories[pawn].variantItems[j].second >= recipe.amounts[i]) {
                //add the right amount of the type of item in inventory
                variantIngredientsFound.push_back({i, recipe.amounts[i]});
                foundIngredient = true;}
        if (foundIngredient) break;
    }
    if (!foundIngredient) {
        if (!attemptAlternateRecipe) {
            attemptAlternateRecipe = true;
        } else return; //item not craftable
    } else {
        //TODO: start crafting, send event
        occupied[pawn] = true;
        addEvent(products[static_cast<int>(product)].time, EventType::ProductComplete, product, pawn);
        for (int i = 0; i < ingredientsFound.size(); i++) {
            removeItem(pawn, ingredientsFound.first, ingredientsFound.second);
        }
        for (int i = 0; i < variantIngredientsFound.size(); i++) {
            removeItem(pawn, variantIngredientsFound.first, variantIngredientsFound.second);
        }
    }
    }
    }
    }
    }
}

//returns mean picking up container failed and it is not picked up
void addContainer(int pawn, Item c, bool child) {
    if (child) float maxWeight = childMaxCarry;
    else float maxWeight = maxCarry;

            //drop if container is too heavy
    if (currentWeights[pawn] + bulkAndWeight[c].weight > maxWeight) return;

    ContainerType ct = itemToContainer(c);
    Container container;
    container.containerType = ct;
    float capacity = getContainerCapacity(ct);

    Inventory& in = inventories[pawn];
    // put Container in left or right hand, removing tool if necessary
            if (in.leftHand == Tool::None || in.leftHand == Tool::CARRYING) {
                in.leftHand = Tool::CARRYING;
            } else if (in.rightHand == Tool::None || inrightHand == Tool::CARRYING) {
                in.rightHand = Tool::CARRYING;
            } else {
                //attempt to put tool into container
                if (toolBulkAndWeight[static_cast<int>(in.leftHand)].bulk < capacity) {
                    container.tools.push_back(leftHand);
                    in.leftHand = Tool::CARRYING;
                    in.currentBulk -= toolBulkAndWeight[static_cast<int>(in.leftHand)].bulk;
                    in.currentWeight[pawn] -= toolBulkAndWeight[static_cast<int>(leftHand)].weight;
                } else if (toolBulkAndWeight[static_cast<int>(in.rightHand)].bulk < capacity) {
                    container.tools.push_back(rightHand);
                    in.currentBulk -= toolBulkAndWeight[static_cast<int>(in.rightHand)].bulk;
                    in.currentWeight -= toolBulkAndWeight[static_cast<int>(in.rightHand)].weight;
                    in.rightHand = Tool::CARRYING;
                } else {
                  //TODO: drop tool or drop container (container currently being made and reset tool)
                }
            }

            if (in.currentBulk == 0) in.currentBulkStatus = BulkStatus::NONE;
            if (in.currentBulkStatus == BulkStatus::NONE) {
                switch (bulkAndWeights[c].bulklevel) {
                    case BulkLevel::Single:
                        in.currentBulkStatus = BulkStatus::Single;
                        break;
                    default:
                        in.currentBulkStatus = BulkStatus::Mid;
                }
            }
            // Add bulk, weight of container, and then put items into container if necessary
                in.currentBulk += bulkAndWeights[c].bulk;
                in.currentWeight += bulkAndWeights[c].weight;

            // if single mode, put into container or drop all items
            if (in.currentBulkStatus == BulkStatus::Single) {
                for (int i = 0; i < in.items.size(); i++) {
                    if (in.items[i].second > 0) {
                        if (bulkAndWeight[in.items[i].first].bulk + container.currentBulk <= capacity) {
                            uint16_t amount = (uint16_t)min((int)in.items[i].second, (int)(capacity / bulkAndWeight[in.items[i].first].bulk));
                            addItemtoContainer(pawn, container, i, amount);
                        } else dropItem(pawn, in.items[i].first, in.items[i].second);
                    }
                    for (int i = 0; i < in.variantItems.size(); i++) {
                        if (in.variantItems[i].second > 0 && bulkAndWeight[in.variantItems[i].first].bulk + container.currentBulk <= capacity) {
                            uint16_t amount = (uint16_t)min((int)in.variantItems[i].second, (int)(capacity / bulkAndWeight[in.variantItems[i].first].bulk));
                            addVariantItemtoContainer(pawn, container, i, amount);
                        }
                    }
                }
            }

            //if mid mode, only put bulk over limit into container
            if (in.currentBulkStatus == BulkStatus::Mid) {
                while (in.currentBulk > midBulkMax) {
                    for (int i = 0; i < in.items.size(); i++) {
                    if (in.items[i].second > 0) {
                        if (bulkAndWeight[in.items[i].first].bulk + container.currentBulk <= capacity) {
                            uint16_t amount = (uint16_t) (fmin(in.currentBulk - midBulkMax) / bulkAndWeight[in.items[i].first].bulk) + 1;
                            addItemtoContainer(pawn, container, i, amount);
                        } else dropItem(pawn, in.items[i].first, in.items[i].second);
                        if (in.currentBulk <= midBulkMax) break;
                    }
                      if (in.currentBulk <= midBulkMaxx) break;
                    for (int i = 0; i < in.variantItems.size(); i++) {
                        if (in.variantItems[i].second > 0) {
                            if (&& bulkAndWeight[in.variantItems[i].first].bulk + container.currentBulk <= capacity) {
                            uint16_t amount = (uint16_t)min((int)in.variantItems[i].second, (int)(capacity / bulkAndWeight[in.variantItems[i].first].bulk));
                            addVariantItemtoContainer(pawn, container, i, amount);
                            if (in.currentBulk <= midBulkMax) break;
                        } else dropItem(pawn, in.items[i].first, in.items[i].second);
                            if (in.currentBulk <= midBulkMax) break;
                        }
                    }
                }
            }
    }

    // Add constructed container to containers vector, linked to pawn index
    containers[pawn].push_back(conatiner);
}


// when production of item is finished, place if buildable or vehicle or go to inventory if item
void productFinish(Item product, int pawn) {
    /* TODO: change this section to be event-based */
        std::pair<int,int> itemCoords = coordsFromFacing(currentCoords[pawn], currentDirections[pawn]);
        if (std::holds_alternative<Item>(currentProducts[pawn])) {
            Recipe p = products[static_cast<int>(product)];
            bool child = childStatus[pawn];
            // CORPSE
            if (p.tags.hasTag(itemTags::Corpse)) {
                CorpseData corpse = corpseInterpreter(inventories[pawn].focusStation);
                for (int i = 0; i < corpse.products.size(); i++) {
                    //for each of the products made by butchering corpse, check if it fits in inventory, then containers
                    // if (currentBulk + bulkAndWeights[static_cast<int>(currentProducts[pawn])].bulk > currentMaxBulk(currentBulkStatus, false) || currentWeight +  bulkAndWeights[static_cast<int>(currentProducts[pawn])].weight  > maxWeight(false))  {
                    float productAmount = corpse.amounts[i];
                        float remainingSpace = min(currentMaxBulk(inventories[pawn].currentBulkStatus, child) - inventories[pawn].totalBulk, 0);
                        int productsToComplete = productAmount;
                        if (remainingSpace > bulksAndWeights[corpse.products[i]].bulk) {
                            if (corpse.products[i] == Item::RawMeat) {
                                uint16_t variant = static_cast<int>(corpse.meat);
                                productsToComplete = addVariantItem(pawn, corpse.products[i], variant, productAmount);
                            } else if (corpse.products[i] == Item::AnimaHides){
                                uint16_t variant = static_cast<int>(corpse.hide);
                                productsToComplete = addVariantItem(pawn, corpse.products[i], variant, productAmount);
                            } else productsToComplete = addItem(pawn, corpse.products[i], productAmount);
                            if (productsToComplete == 0) continue;
                        }
                        for (int j = 0; j < inventories[pawn].containers.size(); j++) {
                        Container& container = inventories[pawn].containers[j];
                        //add to containers if there are viable ones
                            if (corpse.products[i] == Item::RawMeat) {
                                uint16_t variant = static_cast<int>(corpse.meat);
                                addVariantItemToContainer(pawn, container, corpse.products[i], variant, amount);
                            } else if (corpse.products[i] == Item::AnimaHides){
                                uint16_t variant = static_cast<int>(corpse.hide);
                                addVariantItemToContainer(pawn, container, corpse.products[i], variant, amount);
                            } else addItemToContainer(pawn, container, corpse.products[i], amount);
                            // if there are no items remaining for current product, try to fit new items
                            if (productAmount <= amount) {
                                break;
                            } else productAmount -= amount;
                }
            }
            }
            //CONTAINER
            else if (recipe.itemTags.hasTag(itemTags::Container)) addContainer(pawn, product, child);
            //TODO: deal with if container doesnt fit
            //OTHER ITEMS
            //TODO: if pawn can't fit in inventory, leave on floor
            else if (inventories[pawn].currentBulk + bulkAndWeights[static_cast<int>(currentProducts[pawn])].bulk > currentMaxBulk(inventories[pawn].currentBulkStatus, child) || inventories[pawn]currentWeight + bulkAndWeights[static_cast<int>(currentProducts[pawn])].weight > maxWeight(child))  {
                // if item is variant:
                if (static_cast<int>(product) < static_cast<int>(VARIANTSMAX)) {
                    tileObject[tileIndex[itemCoords]] = currentProducts[pawn];
                } else {
                    tileObject[tileIndex[itemCoords]] = currentProducts[pawn];
                }
            } else {
                // if item is variant:
                if (static_cast<int>(product) < static_cast<int>(VARIANTSMAX)) {
                    tileObject[tileIndex[itemCoords]] = currentProducts[pawn];
                }
                int remainder = addItem(pawn, currentProducts[pawn], 1);
                for (int i = 0; i < inventories[pawn].containers.size(); i++) {
                    if (remainder > 0) addItemToContainer(pawn, container, )
                }
            }
        //BUILDABLE
        } else if (std::holds_alternative<Buildable>(currentProducts[pawn])) {
            tileObject[tileIndex[itemCoords]] = currentProducts[pawn];
        //VEHICLE
        } else {
            tileObject[tileIndex[itemCoords]] = currentProducts[pawn];
        }
    }
}

//SUPPORT (means they do not gain items from their action), but also don't do damage
void attemptSupport(int pawn, Role role) {
    switch(role) {
        case Role::Plower:
            //TODO: switch between plowing,planting, and harvesting modes for farmer
            bool plowable;
            for (int j = 0; j < plowables.size(); j++) {
                if (tileCoords[index] == plowables[j]) {
                    plowable = true;
                    break;
                }
            }
            if (!plowable) {
                //TODO: wander to new tile

            }
            break;
        case Role::Planter:
            if (&outDistSqr[i] > threshold) {
                //second plant in plowed soil
                plowedSoil.knnSearch(&queryPoint[0], numResults, &retIndex[0], &outDistSqr[0]);
                nearestIndex = retIndex[i];
                break;
                //third plant in unplowed but exposed soil
                if (&outDistSqr[i] > threshold) {
                    soil.knnSearch(&queryPoint[0], numResults, &retIndex[0], &outDistSqr[0]);
                    nearestIndex = retIndex[i];
                    break;
                    //fourth search for weeds
                    if (&outDistSqr[i] > threshold) {
                        weed.knnSearch(&queryPoint[0], numResults, &retIndex[0], &outDistSqr[0]);
                        nearestIndex = retIndex[i];
                        break;
                    }
                }
            }
        break;
    }
}


void variantItemInterpreter() {

}


#endif // INVENTORIESANDWORKQUEUES_H_
