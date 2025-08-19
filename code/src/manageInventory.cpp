#include "manageInventory.hpp"

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

void addContainer(int pawn, Container& container) {
    Inventory &in = inventories[pawn];
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

//returns mean picking up container failed and it is not picked up
void fullAddContainer(int pawn, Container c, bool child) {
    if (child) float maxWeight = childMaxCarry;
    else float maxWeight = maxCarry;

            //drop if container is too heavy
    if (currentWeights[pawn] + containerBulkAndWeight[c].weight > maxWeight) return;

    ContainerType ct = itemToContainer(c);
    Container container;
    container.containerType = ct;
    float capacity = getContainerCapacity(ct);

    Inventory& in = inventories[pawn];
    bool found = false;
    // put Container in left or right hand, removing tool if necessary
            if (in.leftHand.second == Material::CARRYING) {
                if (maxCarry < in.currentWeight) addContainer(pawn, container);
            } else if (in.rightHand.second == Material::CARRYING) {
                if (maxCarry < in.currentWeight) addContainer(pawn, container);
            } else {
                //attempt to put tool into container
                if !(toolToContainer(pawn, container, leftHand.first)) {
                        if !(toolToContainer(pawn, container, rightHand.first)) {
                                //attempt to put tool into other containers pawn already has
                                for (int i = 0; i < containers[pawn].size(); i++) {
                                    if (toolToContainer(pawn, containers[pawn][i], leftHand.first)) {
                                        found = true;
                                        break;
                                    }
                                    if (toolToContainer(pawn, containers[pawn][i], rightHand.first)) {
                                        found = true;
                                        break;
                                    }
                                }
                            }
                    }
            }
            //drop container or tool
            if (!found) {
                dropContainer(pawn, container);
                return;
            }

            if (in.currentBulk == 0) in.currentBulkStatus = BulkStatus::NONE;
            if (in.currentBulkStatus == BulkStatus::NONE) {
                switch (containerBulkAndWeights[c].bulklevel) {
                    case BulkLevel::Single:
                        in.currentBulkStatus = BulkStatus::Single;
                        break;
                    default:
                        in.currentBulkStatus = BulkStatus::Mid;
                }
            }
}

void dropContainer(int pawn, int index) {
    int tileIndex = getNearestAdjacentEmptyTileIndex(tileIndices[currentCoords[pawn]]);
    tileObject[tileIndex] = inventories[pawn].containers[index];
    //TODO: code container on ground with items
    inventories[pawn].containers[index] = Container::NONE;
}

uint16_t addItemToContainer(int pawn, Container& container, Item item, uint16_t amount) {
    SizeData sd = bulkAndWeights[static_cast<int>(item)];
    float remainderBulk = getContainerCapacity(container.containerType) - container.currentBulk;
    if (remainderBulk < sd.bulk || !validContainer(container, item)) return productAmount;
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
    if (remainderBulk < sd.bulk || !validContainer(container, item)) return productAmount;
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
    if (remainderBulk < sd.bulk || !validContainer(container, item)) return productAmount;
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
    uint16_t ret;
    float remainderBulk = getContainerCapacity(container.containerType) - container.currentBulk;
    if (remainderBulk < sd.bulk || !validContainer(container, item)) return amount;
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

//false if didnt work
bool toolToContainer(int pawn, Container& container, uint8_t toolIndex) {
    Tool tool = tools[toolIndex].first;
    Material material = tools[toolIndex].second;
    float bulk = toolBulkAndWeights[static_cast<int>(tool)].bulk;
    float weight = toolBulkAndWeights[static_cast<int>(tool)].weight * weightMultiplier[static_cast<int>(material)];
    float remainderBulk = getContainerCapacity(container.containerType) - container.currentBulk;
    if (remainderBulk < sd.bulk || !validContainer(container, item)) return false;
    Inventory& in = inventories[pawn];
    container.currentBulk += sd.bulk;
    container.curentWeight += sd.weight;
    in.currentBulk -= sd.bulk;
    in.currentWeight -= sd.weight;
    if (currentBulk[pawn] == 0) currentBulkStatus = BulkStatus::NONE;
    in.tools[toolIndex].first == Tools::NONE;
    container.tools.push_back({tool, material});
    return true;
}

uint16_t containerToInventory() {

}

uint16_t variantContainerToInventory() {

}

void dropItem(int tileIndex, Item item, uint16_t amount) {
    tileObject[tileIndex] = {item, amount};
    insertObject(item, et.first, et.second, tileIndex);
}

void dropItem(int pawn, int itemIndex, uint16_t amount) {
    removeItem(pawn, itemIndex, amount);
    int index = nextItemIndex.pop();
    std::pair<int,int> et = getNearestEmptyTile(startIndex);
    insertObject(inventories[pawn].items[itemIndex].first, et.first, et.second, index);
    //TODO: create check if empty, and put on tile if so
}

void dropVariantItem(int pawn, int itemIndex,  uint16_t variant, uint16_t amount) {
    removeVariantItem(pawn, itemIndex, variant, amount);
    variantItemCount++;

}

//does the full mechanism for trying to add items, returns remaining that did not get added
void fullAddItem(int pawn, Item item , uint16_t amount) {
    uint16_t remaining = amount;
    int i = 0;
    while (remaining > 0) {
        if (i >= containers[pawn].size()) break;
        Container& = containers[pawn][i];
        remaining = addItemToContainer(pawn, remaining);
        i++;
    }
    if (remaining > 0) remaining -= addItems();
    if (remaining > 0) dropItem(tileIndices[currentCoords[pawn]], item, remaining);
}
