#include "inventory_manager.hpp"
#include <array>
#include <cstdint>
#include <world/unit/entity.hpp>
inline float calculateRemainingBulk(BulkStatus bulkStatus, float bulk)
{
	switch (bulkStatus)
	{
	case BulkStatus::Fine:
		return FINE_BULK_MAX - bulk;
		break;
	case BulkStatus::Mid:
		return MID_BULK_MAX - bulk;
		break;
	case BulkStatus::Single:
		return SINGLE_BULK_MAX - bulk;
		break;
	default:
		// TODO: error handling
		std::cerr << "Invalid Bulk Status." << std::endl;
	}
}

inline float calculateRemainingBulk(ContainerType type, float bulk)
{
	return containerBulkCapacities[type] - bulk;
}

inline ContainerStorageData getRemainingStorage(Inventory &inventory, Container &container)
{
	ContainerStorageData csd;
	// OPTI: extra check here
	if (container.type == ContainerType::Hands)
	{
		csd.remainingBulk = calculateRemainingBulk(inventory.bulkStatus, inventory.bulk);
		csd.remainingWeight =
		    calculateRemainingWeight(inventory.bulkStatus, inventory.weight);
	}
	else
	{
		csd.remainingBulk = calculateRemainingBulk(container.type, inventory.bulk);
		csd.remainingWeight = calculateRemainingWeight(container.type, inventory.weight);
	}
	return csd;
}

// TODO: redo all these functions to also work for Tools, VariantItems
inline uint16_t getMaxItemsStored(Item item, ContainerStorage storage)
{
	StorageData sd = itemBulkAndWeights[item];
	return min(storage.remainingWeight / sd.weight, storage.remainingBulk / sd.bulk);
}

struct InventoryAddBuffer
{
	HoldableSlot holdable;
	uint16_t containerAmount;
	std::array<uint16_t, 8> amountsPerContainer;
	std::array<bool, 8> overflow;

	InventoryAddBuffer(uint16_t containerAmount, std::array<uint16_t, 8> &amountsPerContainer,
			   std::array<bool, 8> overflow)
	    : containerAmount(containerAmount), amountsPerContainer(amountsPerContainer),
	      overflow(overflow)
	{
	}
};

inline uint16_t getMaxWeight(Strength strength) { return 40 + (strength * 30); }

inline void addItemsToInventory(Inventory &inventory, InventoryAddBuffer &buffer, )
{
	for (size_t i = 0; i < buffer.containerAmount; i++)
	{
		uint16_t amount = buffer.amountsPerContainer[i];
		if (amount == 0)
			continue;
		if (buffer.overflow[i])
		{
			addItem(holdableOverflows.get(overflow_hash(unitIndex, i)), buffer.holdable,
				amount);
		}
		else
		{
			Container & container;
			if (i < CONTAINER_UNDERFLOW_LIMIT)
				container = inventory.containers[i];
			else
				container = overflowContainers.get(unitIndex)[i];
			addItem(container, buffer.holdable, amount);
		}
	}
}

inline void tabulateItemAddContainerData(InventoryAddBuffer &buffer, Container &container,
					 uint16_t &itemAmount, bool &foundSpace,
					 bool &unsearchedInventory)
{
	ContainerStorageData csd = getRemainingStorage(inventory, container);
	uint16_t storageCapacity = (uint16_t)min(itemAmount, getMaxItemsStored(item, csd));
	buffer.containerAmount += storageCapacity;
	itemAmount -= storageCapacity;
	buffer.amountsPerContainer[containerIndex] = storageCapacity;
	containers[buffer.containerAmount++] = container;

	// TODO: different checks for different categories
	  hasTag(ContainerFullTags::ItemOverflow, container.tags) ? buffer.overflow[containerIndex] = true : overflow[containerIndex = false;
	  
          foundSpace = (itemAmount <= 0);
	  unsearchedInventory = hasTags(ContainerFullTags::NextContainer, container.tags);
}

// TODO: add 'ContainerFull' tag to make things easier.
uint16_t attemptAddItems(uint16_t unitIndex, Strength strength, Inventory &inventory, Item item,
			 uint16_t itemAmount)
{
	InventoryAddBuffer buffer;
	bool foundSpace = false;
	bool unsearchedInventory = true;
	uint16_t amount;
	uint16_t containerIndex = 0;

	uint16_t maxAmount =
	    (getMaxWeight(strength) - inventory.weight) / itemBulkAndWeights[item].weight;
	if (maxAmount < 1)
		return 0;

	// containers in main inventory
	while (!foundSpace && unSearchedInventory)
	{
		Container &container = inventory.containers[containerIndex];
		tabulateItemAddContainerData(buffer, container, itemAmount, foundSpace,
					     unsearchedInventory);
	}
	// overflow containers
	if (!foundSpace && unsearchedInventory)
	{
		std::vector<Container> &unitOverflowContainers = overflowContainers[unitIndex];
		containerIndex = 0;
	}
	while (!foundSpace && unsearchedInventory)
	{
		Container &container = unitOverflowContainers[containerIndex];
		tabulateItemAddContainerData(buffer, container, itemAmount, foundSpace,
					     unsearchedInventory);
	}
	if (amount > 0)
		addToInventory(buffer);
	return itemAmount - buffer.containerAmount;
}

uint16_t InventoryManager::addVariantItems(int pawn, Item item, uint16_t itemAmount, int variant)
{
	float remainingSpace = min(
	    currentMaxBulk(inventories[pawn].bulkStatus, false) - inventories[pawn].totalBulk, 0);
	uint16_t amount =
	    (uint16_t)min((itemAmount, (int)(remainingSpace / bulkAndWeights[item].bulk)));
	if (remainingSpace > bulksAndWeights[static_cast<int>(item)].bulk)
	{
		if (amount > 0)
		{
			for (int i = 0; i < inventories[pawn].variantItems.size(); i++)
			{
				if (inventories[pawn].variantItems[i].first == item &&
				    inventories[pawn].variantItemTypes[i] == variant)
				{
					inventories[pawn].variantItems[i].second += amount;
					return itemAmount - amount;
				}
			}
			inventories[pawn].variantItems.push_back(item, amount);
			inventories[pawn].variantItemTypes.push_back(variant);
		}
	}
	return itemAmount - amount;
}

void removeItem(int pawn, int index, uint16_t amount)
{
	inventories[pawn].items[index].second -= amount;
}

void removeVariantItem(int pawn, int index, uint16_t amount)
{
	inventories[pawn].variantItems[index].second -= amount;
}

void addContainer(int pawn, Container &container)
{
	Inventory &in = inventories[pawn];
	// Add bulk, weight of container, and then put items into container if
	// necessary
	in.bulk += bulkAndWeights[c].bulk;
	in.weight += bulkAndWeights[c].weight;

	// if single mode, put into container or drop all items
	if (in.bulkStatus == BulkStatus::Single)
	{
		for (int i = 0; i < in.items.size(); i++)
		{
			if (in.items[i].second > 0)
			{
				if (bulkAndWeight[in.items[i].first].bulk + container.bulk <=
				    capacity)
				{
					uint16_t amount = (uint16_t)min(
					    (int)in.items[i].second,
					    (int)(capacity /
						  bulkAndWeight[in.items[i].first].bulk));
					addItemtoContainer(pawn, container, i, amount);
				}
				else
					dropItem(pawn, in.items[i].first, in.items[i].second);
			}
			for (int i = 0; i < in.variantItems.size(); i++)
			{
				if (in.variantItems[i].second > 0 &&
				    bulkAndWeight[in.variantItems[i].first].bulk + container.bulk <=
					capacity)
				{
					uint16_t amount = (uint16_t)min(
					    (int)in.variantItems[i].second,
					    (int)(capacity /
						  bulkAndWeight[in.variantItems[i].first].bulk));
					addVariantItemtoContainer(pawn, container, i, amount);
				}
			}
		}
	}

	// if mid mode, only put bulk over limit into container
	if (in.bulkStatus == BulkStatus::Mid)
	{
		while (in.bulk > midBulkMax)
		{
			for (int i = 0; i < in.items.size(); i++)
			{
				if (in.items[i].second > 0)
				{
					if (bulkAndWeight[in.items[i].first].bulk +
						container.bulk <=
					    capacity)
					{
						uint16_t amount =
						    (uint16_t)(fmin(in.bulk - midBulkMax) /
							       bulkAndWeight[in.items[i].first]
								   .bulk) +
						    1;
						addItemtoContainer(pawn, container, i, amount);
					}
					else
						dropItem(pawn, in.items[i].first,
							 in.items[i].second);
					if (in.bulk <= midBulkMax)
						break;
				}
				if (in.bulk <= midBulkMaxx)
					break;
				for (int i = 0; i < in.variantItems.size(); i++)
				{
					if (in.variantItems[i].second > 0)
					{
						if (&&bulkAndWeight[in.variantItems[i].first].bulk +
							container.bulk <=
						    capacity)
						{
							uint16_t amount = (uint16_t)min(
							    (int)in.variantItems[i].second,
							    (int)(capacity /
								  bulkAndWeight[in.variantItems[i]
										    .first]
								      .bulk));
							addVariantItemtoContainer(pawn, container,
										  i, amount);
							if (in.bulk <= midBulkMax)
								break;
						}
						else
							dropItem(pawn, in.items[i].first,
								 in.items[i].second);
						if (in.bulk <= midBulkMax)
							break;
					}
				}
			}
		}
	}

	// Add constructed container to containers vector, linked to pawn index
	containers[pawn].push_back(conatiner);
}

// returns mean picking up container failed and it is not picked up
void fullAddContainer(int pawn, Container c, bool child)
{
	if (child)
		float maxWeight = childMaxCarry;
	else
		float maxWeight = maxCarry;

	// drop if container is too heavy
	if (weights[pawn] + containerBulkAndWeight[c].weight > maxWeight)
		return;

	ContainerType ct = itemToContainer(c);
	Container container;
	container.containerType = ct;
	float capacity = getContainerCapacity(ct);

	Inventory &in = inventories[pawn];
	bool found = false;
	// put Container in left or right hand, removing tool if necessary
	if (in.leftHand.second == Material::CARRYING)
	{
		if (maxCarry < in.weight)
			addContainer(pawn, container);
	}
	else if (in.rightHand.second == Material::CARRYING)
	{
		if (maxCarry < in.weight)
			addContainer(pawn, container);
	}
	else
	{
		// attempt to put tool into container
		if !(toolToContainer(pawn, container, leftHand.first))
		{
			if !(toolToContainer(pawn, container, rightHand.first))
			{
				// attempt to put tool into other containers pawn already has
				for (int i = 0; i < containers[pawn].size(); i++)
				{
					if (toolToContainer(pawn, containers[pawn][i],
							    leftHand.first))
					{
						found = true;
						break;
					}
					if (toolToContainer(pawn, containers[pawn][i],
							    rightHand.first))
					{
						found = true;
						break;
					}
				}
			}
		}
	}
	// drop container or tool
	if (!found)
	{
		dropContainer(pawn, container);
		return;
	}

	if (in.bulk == 0)
		in.bulkStatus = BulkStatus::NONE;
	if (in.bulkStatus == BulkStatus::NONE)
	{
		switch (containerBulkAndWeights[c].bulklevel)
		{
		case BulkLevel::Single:
			in.bulkStatus = BulkStatus::Single;
			break;
		default:
			in.bulkStatus = BulkStatus::Mid;
		}
	}
}

void dropContainer(int pawn, int index)
{
	int tileIndex = getNearestAdjacentEmptyTileIndex(tileIndices[currentCoords[pawn]]);
	tileObject[tileIndex] = inventories[pawn].containers[index];
	// TODO: code container on ground with items
	inventories[pawn].containers[index] = Container::NONE;
}

uint16_t addItemToContainer(int pawn, Container &container, Item item, uint16_t amount)
{
	SizeData sd = bulkAndWeights[static_cast<int>(item)];
	float remainderBulk = getContainerCapacity(container.containerType) - container.bulk;
	if (remainderBulk < sd.bulk || !validContainer(container, item))
		return itemAmount;
	uint16_t amount =
	    (uint16_t)min(min((itemAmount, (int)(remainderBulk / bulkAndWeights[item].bulk))),
			  in.items[itemIndex].second);
	container.bulk += sd.bulk * amount;
	container.curentWeight += sd.weight * amount;
	for (int i = 0; i < container.items.size(); i++)
	{
		if (container.items[i].first == item)
			container.items[i].second += amount;
		return itemAmount - amount;
	}
	container.items.push_back(item, amount);
	return itemAmount - amount;
}

uint16_t inventoryToContainer(int pawn, Container &container, int itemIndex, uint16_t itemAmount)
{
	SizeData sd = bulkAndWeights[static_cast<int>(item)];
	float remainderBulk = getContainerCapacity(container.containerType) - container.bulk;
	if (remainderBulk < sd.bulk || !validContainer(container, item))
		return itemAmount;
	Inventory &in = inventories[pawn];
	uint16_t amount =
	    (uint16_t)min(min((itemAmount, (int)(remainderBulk / bulkAndWeights[item].bulk))),
			  in.items[itemIndex].second);
	Item item = in.items[itemIndex].first;
	container.bulk += sd.bulk * amount;
	container.curentWeight += sd.weight * amount;
	in.bulk -= sd.bulk * amount;
	in.weight -= sd.weight * amount;
	if (bulk[pawn] == 0)
		bulkStatus = BulkStatus::NONE;
	in.items[itemIndex].second -= amount;
	if (in.items[itemIndex].second == 0)
		in.items[itemIndex].first == Item::NONE;
	for (int i = 0; i < container.items.size(); i++)
	{
		if (container.items[i].first == item)
			container.items[i].second += amount;
		return itemAmount - amount;
	}
	container.items.push_back(item, amount);
	return itemAmount - amount;
}

void moveItemBetweenContainers(int pawn, Container &from, Container &to, Item item) {}

uint16_t addVariantItemToContainer(int pawn, Container &container, Item item, uint16_t variant,
				   uint16_t itemAmount)
{
	SizeData sd = bulkAndWeights[static_cast<int>(item)];
	float remainderBulk = getContainerCapacity(container.containerType) - container.bulk;
	if (remainderBulk < sd.bulk || !validContainer(container, item))
		return itemAmount;
	Inventory &in = inventories[pawn];
	uint16_t amount =
	    (uint16_t)min(min((itemAmount, (int)(remainderBulk / bulkAndWeights[item].bulk))),
			  in.variantItems[itemIndex].second);
	container.bulk += sd.bulk * amount;
	container.curentWeight += sd.weight * amount;
	for (int i = 0; i < container.variantItems.size(); i++)
	{
		if (container.variantItems[i].first == item)
			container.variantItems[i].second += amount;
		return itemAmount - amount;
	}
	container.variantItems.push_back(item, amount);
	container.variantItemTypes.push_back(variant);
	return itemAmount - amount;
}

uint16_t variantInventoryToContainer(int pawn, Container &container, int itemIndex, uint16_t amount)
{
	SizeData sd = bulkAndWeights[static_cast<int>(item)];
	uint16_t ret;
	float remainderBulk = getContainerCapacity(container.containerType) - container.bulk;
	if (remainderBulk < sd.bulk || !validContainer(container, item))
		return amount;
	Inventory &in = inventories[pawn];
	uint16_t amount =
	    (uint16_t)min(min((itemAmount, (int)(remainderBulk / bulkAndWeights[item].bulk))),
			  in.variantItems[itemIndex].second);
	Item item = in.variantItems[itemIndex].first;
	container.bulk += sd.bulk * amount;
	container.curentWeight += sd.weight * amount;
	in.bulk -= sd.bulk * amount;
	in.weight -= sd.weight * amount;
	if (bulk[pawn] == 0)
		bulkStatus = BulkStatus::NONE;
	in.variantItems[itemIndex].second -= amount;
	if (in.variantItems[itemIndex].second == 0)
		in.variantItems[itemIndex].first == Item::NONE;
	for (int i = 0; i < container.variantItems.size(); i++)
	{
		if (container.variantItems[i].first == item)
			container.variantItems[i].second += amount;
		return itemAmount - amount;
	}
	container.variantItems.push_back(item, amount);
	container.variantItemTypes.push_back(variant);
	return itemAmount - amount;
}

// false if didnt work
bool toolToContainer(int pawn, Container &container, uint8_t toolIndex)
{
	Tool tool = tools[toolIndex].first;
	Material material = tools[toolIndex].second;
	float bulk = toolBulkAndWeights[static_cast<int>(tool)].bulk;
	float weight = toolBulkAndWeights[static_cast<int>(tool)].weight *
		       weightMultiplier[static_cast<int>(material)];
	float remainderBulk = getContainerCapacity(container.containerType) - container.bulk;
	if (remainderBulk < sd.bulk || !validContainer(container, item))
		return false;
	Inventory &in = inventories[pawn];
	container.bulk += sd.bulk;
	container.curentWeight += sd.weight;
	in.bulk -= sd.bulk;
	in.weight -= sd.weight;
	if (bulk[pawn] == 0)
		bulkStatus = BulkStatus::NONE;
	in.tools[toolIndex].first == Tools::NONE;
	container.tools.push_back({tool, material});
	return true;
}

uint16_t containerToInventory() {}

uint16_t variantContainerToInventory() {}

void dropItem(int tileIndex, Item item, uint16_t amount)
{
	tileObject[tileIndex] = {item, amount};
	insertObject(item, et.first, et.second, tileIndex);
}

void dropItem(int pawn, int itemIndex, uint16_t amount)
{
	removeItem(pawn, itemIndex, amount);
	int index = nextItemIndex.pop();
	std::pair<int, int> et = getNearestEmptyTile(startIndex);
	insertObject(inventories[pawn].items[itemIndex].first, et.first, et.second, index);
	// TODO: create check if empty, and put on tile if so
}

void dropVariantItem(int pawn, int itemIndex, uint16_t variant, uint16_t amount)
{
	removeVariantItem(pawn, itemIndex, variant, amount);
	variantItemCount++;
}

// does the full mechanism for trying to add items, returns remaining that did
// not get added
void fullAddItem(int pawn, Item item, uint16_t amount)
{
	uint16_t remaining = amount;
	int i = 0;
	while (remaining > 0)
	{
		if (i >= containers[pawn].size())
			break;
		Container & = containers[pawn][i];
		remaining = addItemToContainer(pawn, remaining);
		i++;
	}
	if (remaining > 0)
		remaining -= addItems();
	if (remaining > 0)
		dropItem(tileIndices[currentCoords[pawn]], item, remaining);
}
