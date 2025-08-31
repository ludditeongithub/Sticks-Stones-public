#ifndef INVENTORIESANDWORKQUEUES_H_
#define INVENTORIESANDWORKQUEUES_H_
#include "basic.hpp"
#include "categories.hpp"
#include "itemRecipes.hpp"
#include "cropdata.hpp"
#include "unit.hpp"

//TILE DATA
//variantIndex superfluous for non-variant items
void getResourceAction(int pawn, Item item, int sourceIndex, int variantIndex) {
    Resource resource = resources[item];
    Actions action = resource.action[sourceVariantIndex];
    SourceVariant source = resource.source[sourceIndex];
    //see if Object should be removed from tile
    bool removeObject = true;
    if (action == Actions::Collect) {
        if (source == Tile::ShallowWater || source == Tile::FlowingWater || source == Tile::DeepWater || source == Tile::ShallowSaltWater || source == Tile::Sand || source == Scavengeable::Beehive || source == Scavengeable::ArtificialBeehive) {
            removeObject = false;
        }
    }
    if (removeObject) {
    if (action == Actions::Milk) removeObject = false;
    else if (action == Actions::GoatMilk) removeObject = false;
    else if (action == Actions::Fish) removeObject = false;
    else if (action == Actions::Shear) removeObject = false;
    else for (int i = 0; i < regrowthCrops.size(); i++) {
        if (item == regrowthCrops[i]) {
            removeObject = false;
        }
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

//NOTE: this seems a little shifty, tools part
bool checkActionRequisites(Resource resource, int pawn) {
    for (int i = 0; i < resource.action.size(); i++) {
        Actions action = recipe.action;
        if (action == Actions::NONE) continue;
         bool foundRole = false;
         for (int j = 0; j < actionToRoles[static_cast<int>(action)].size(); j++) {
             for (int k = 0; k < roles[pawn].size; k++) {
                 if (actionToRoles[action][j] == roles[pawn][k]) {
                     foundRole = true;
                     break;
                 }
             }
             if (foundRole) break;
         }
         if (!foundRole) continue;
         int toolReplaceableList = actionToToolsReplaceables[static_cast<int>(action)];
         for (int j = 0; j < actionToTools[static_cast<int>(action)].size(); j++) {
             bool foundTool = false;
             if (toolReplaceableList[j] < 0) continue; //optional tools
             for (int k = 0; k < tools[pawn].size; k++) {
                 if (actionToTools[action][j] == tools[pawn][k]) {
                     while (toolReplaceableList[j] == toolReplaceableList[j+1]) j++;
                     foundTool = true;
                 }
             }
             if (!foundTool) continue;
         }
         if (foundTool && foundRole) return true;
    }
    return false;
}

bool checkActionRequisites(Recipe recipe, int pawn) {
    if !(recipe.action == Actions::NONE) {
        //confirm pawn can perform action necessary to produce product
        Actions action = recipe.action;
         bool foundRole = false;
         for (int j = 0; j < actionToRoles[static_cast<int>(action)].size(); j++) {
             for (int k = 0; k < roles[pawn].size; k++) {
                 if (actionToRoles[static_cast<int>(action)][j] == roles[pawn][k]) {
                     foundRole = true;
                     break;
                 }
             }
             if (foundRole) break;
         }
         if (!foundRole) return false;
    }
         int toolReplaceableList = actionToToolsReplaceables[action];
         for (int j = 0; j < actionToTools[static_cast<int>(action)].size(); j++) {
            bool foundTool = false;
             if (toolReplaceableList[j] < 0) continue; //optional tools
             for (int k = 0; k < tools[pawn].size; k++) {
                 if (actionToTools[static_cast<int>(action)][j] == tools[pawn][k]) {
                     while (toolReplaceableList[j] == toolReplaceableList[j+1]) j++;
                     foundTool = true;
                 }
             }
             if (!foundTool) return false;
         }
         return true;
}

bool checkActionRequisites(Resource resource, int pawn) {
    bool foundRole = false;
    for (int i = 0; i = resource.actions.size(); i++) {
        if !(resource.action == Actions::NONE) {
        //confirm pawn can perform action
        Actions action = resource.actions[i];
         for (int j = 0; j < actionToRoles[static_cast<int>(action)].size(); j++) {
             for (int k = 0; k < roles[pawn].size; k++) {
                 if (actionToRoles[static_cast<int>(action)][j] == roles[pawn][k]) {
                     foundRole = true;
                     break;
                 }
             }
             if (foundRole) break;
           }
         if !(foundRole) continue;
         //find tools if role has been found
         int toolReplaceableList = actionToToolsReplaceables[action];
         bool missingTool = false;
         for (int j = 0; j < actionToTools[static_cast<int>(action)].size(); j++) {
            bool foundTool = false;
             if (toolReplaceableList[j] < 0) continue; //optional tools
             for (int k = 0; k < tools[pawn].size; k++) {
                 if (actionToTools[static_cast<int>(action)][j] == tools[pawn][k]) {
                     while (toolReplaceableList[j] == toolReplaceableList[j+1]) j++;
                     foundTool = true;
                 }
             }
             if (!foundTool) {
                 missingTool = true;
                 break;
             }
         }
         if !(missingTool) return true;
        }
    }
    return false;
}

//TODO: check if item or fruit object is removed, if amt 0, remove from objectLocation

//RESOURCE PAWN MANAGEMENT
 void attemptResource(int pawn, Role role) {
     if (role !< Role:RESOURCEMAX) return;
     for (int i = 0; i < resourceUnitResources[static_cat<int>(role)].size(); i++) {
         Item item = resourceUnitResources[static_cast<int>(role)][i];
         Resource resource = resources[static_cast<int>(item)];
         if !(checkActionRequisites(resource, pawn)) return;
        /* TODO: max man dist, nearest search logic for known areas
        currentDests[pawn] = findNearestObjectIndex(item, pawnCoords[pawn].first, pawnCoords[pawn].second);
        */
        //method 2 (unpreferred): prowl for resource
        currentTarget[pawn] = item;
        movingStatus[pawn] = MovingStatus::CheckProwl;
     }
 }


//PRODUCTS PAWN MANAGEMENT
// TODO: have pawns search nearby surroundings for items if not found, if on
// Check inventory to produce new items
void attemptProduction(int pawn, ProductVariant product) {
    //TODO: get type of product variant to deterine itemType
    movingStatus[pawn] = MovingStatus::Production;
    bool attemptAlternateRecipe = false;
    for (int i = 0; i < 2; i++) {
    if (itemType == ItemType::Item) {
        attemptAltenateRecipe ? return : Recipe recipe = products[static_cast<int>(product)] ;
    } else if (itemType == ItemType::Vehicle) {
        attemptAltenateRecipe ? return : VehicleRecipe recipe = vehicles[static_cast<int>(product)] ;
    } else if (itemType == ItemType::Buildable) {
        attemptAlternateRecipe ? BuildableRecipe recipe = buildablesAlternateInterpreter(product) : BuildableRecipe recipe = buildables[static_cast<int>(product)];
    } else if (itemType == ItemType::Tool) {
        attemptAlternateRecipe ? return : ToolRecipe recipe = tools[static_cast<int>(product)];
    } else if (itemType == ItemType::Container) {
        attemptAlternateRecipe ? return : ContainerRecipe recipe = containers[static_cast<int>(product)];
    }

    if (checkActionRequisites(recipe, pawn)) {
        findNecessaryTools(recipe.action, pawn);
    }
        vector<std::pair<int, int>> ingredientsFound;
    vector<std::pair<int, int>> variantIngredientsFound;

    //FOR LIQUIDS
    if (recipe.itemTags.hasTag(itemTags::Liquid)) {
        //TODO: find nearest unprocessing liquid vessel, or get from inventory if none
        bool found = false;
        while (!found) {
            if (filledLiquidContainers.find(findNearestLiquidContainer(currentCoords[pawn].first, currentCoords[pawn]second)) != filledLiquidContainers.end())

        }
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
        } else {
                //try to find nearest ingredient
            //TODO: create nearest with lower man dist, also do for non-alternate recipe
            std::pair<int,int> itemCoord = findNearestObject(recipe.ingredients[i], currentCoords[pawn].first, currentCoords[pawn]second);
            if (itemCoord != {-1, -1} && manDist(currentCoords[pawn], itemCoord) < nearGatherRange) {
                currentDests[pawn] = tileIndices[itemCoord];
                movingStatus[pawn] = MovingStatus::ApproachItem;
                //NOTE: async logic here?
                findPromise[pawn] = std::promise<void>();
                findFuture[pawn] = findPromise[pawn].get_future();
            }
        }

        }
    }
    } else {
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





// when production of item is finished, place if buildable or vehicle or go to inventory if item, variant optional
void productFinish(ProductVariant product, int pawn, uint16_t variant) {
    /* TODO: change this section to be event-based */
        if (std::holds_alternative<Item>(products)) {
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
                        if (remainingSpace > bulksAndWeights[corpse.products[i]].bulk) {
                            if (corpse.products[i] == Item::RawMeat) {
                                uint16_t var = static_cast<uint16_t>(corpse.meat);
                                fullAddVariantItem(pawn, corpse.products[i], productAmount, var);
                            } else if (corpse.products[i] == Item::AnimaHides){
                                uint16_t var = static_cast<uint16_t>(corpse.hide);
                                fullAddVariantItem(pawn, corpse.products[i], productAmount, var);
                            } else fullAddItem(pawn, corpse.products[i], productAmount);
                        }
                }
            }
            //CONTAINER
            else if (recipe.itemTags.hasTag(itemTags::Container)) addContainer(pawn, product, child);
            //TODO: deal with if container doesnt fit
        //BUILDABLE
        } else if (std::holds_alternative<Buildable>(currentProducts[pawn])) {
             std::pair<int,int> itemCoords = coordsFromFacing(currentCoords[pawn], currentDirections[pawn]);
            tileObject[tileIndex[itemCoords]] = currentProducts[pawn];
        //VEHICLE
        } else if (std::holds_alternative<Vehicle>(currentProducts[pawn])) {
            std::pair<int,int> itemCoords = coordsFromFacing(currentCoords[pawn], currentDirections[pawn]);
            tileObject[tileIndex[itemCoords]] = currentProducts[pawn];
    } //OTHER ITEMS
            else {
                 if (static_cast<int>(product) < static_cast<int>(VARIANTSMAX)) {
                   fullAddVariantItem(pawn, product, variant, p.amount);
                } else {
                    fullAddItem(pawn, product, p.amount);
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


void variantItemInterpreter() {

}


//NOTE: bad
void nextRole(int pawn, int roleIndex) {
    std::swap(roles[pawn][roleIndex], roles[pawn][roles[pawn].size()]);
}

#endif // INVENTORIESANDWORKQUEUES_H_
