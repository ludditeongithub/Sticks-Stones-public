#include "inventory_manager.hpp"
#include "world/item/enum.hpp"
#include "world/item/tags.hpp"
#include "world/unit/entity.hpp"
#include <array>
#include <cstdint>
#include <optional>
#include <variant>
// OPTI: stop runtime dispatch (std::variant)
// TODO: change to work for tools/variants of different weights
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

inline float calculateRemainingWeight(ContainerType type, float weight)
{
	return containerWeightCapacities[type] - weight;
}

inline ContainerStorageData getRemainingStorage(Inventory &inventory, Container &container)
{
	ContainerStorageData csd;
	// OPTI: extra check here
	if (container.type == ContainerType::Hands)
	{
		csd.remainingBulk = calculateRemainingBulk(inventory.bulkStatus, container.bulk);
	}
	else
	{
		csd.remainingBulk = calculateRemainingBulk(container.type, container.bulk);
	}
	csd.remainingWeight = calculateRemainingWeight(container.type, inventory.weight);
	return csd;
}

// TODO: redo all these functions to also work for Tools, VariantItems
inline uint16_t getMaxItemsStored(Item holdable, ContainerStorage storage)
{
	StorageData sd = itemBulkAndWeights[holdable];
	return min(storage.remainingWeight / sd.weight, storage.remainingBulk / sd.bulk);
}

inline uint16_t getMaxWeight(Strength strength) { return 40 + (strength * 30); }

struct InventoryAddBuffer
{
	Item holdable;
	SpecialItemData specialData;
	uint8_t variant;
	uint16_t containerAmount;
	std::array<uint16_t, 8> amountsPerContainer;
	std::array<bool, 8> overflow;
};

template <typename Slots>
void addItemOverflow(OverflowHashMap &overflows, Slots &slots, HoldableSlot holdable,
		     std::optional<uint16_t> unitIndex = std::nullopt,
		     std::optional<uint16_t> containerIndex = std::nullopt)
{
	if constexpr (std::is_same_v<Slots, std::vector<ItemSlot>>)
	{
		slots.push_back(holdable);
	}
	else if constexpr (std::is_same_v<Slots,
					  std::array<ItemSlot, HOLDABLE_UNDERFLOW_LIMIT>>)
	{
		overflows[overflow_hash(unitIndex.value(), containerIndex.value())].push_back(
		    holdable);
	}
}

void addItem(OverflowHashMap &overflows, std::vector<HoldableSlot> &holdables,
	     InventoryAddBuffer &buffer, std::optional<uint8_t> amount = std::nullopt)
{
	Item itemToAdd = buffer.holdable;
	itemTags tags = itemTags[itemToAdd];

	bool found = false;
	if (hasTag(itemTags::Tool, tags))
	{
			for (size_t i = 0; i < holdables.size(); i++)
			{
				if (auto* content = std::get_if<ToolSlot>(&holdables[i]))
				{
				if (content->isEmpty())
				{
					holdables[i] = ToolSlot(itemToAdd,
								       buffer.specialData);
					return;
				}	
				}										
			}
		addItemOverflow(overflows, holdables, ToolSlot(itemToAdd, buffer.specialData));
	}
	else 
	{
		if (hasTag(itemTags::Variant, tags))
		{
			for (size_t i = 0; i < holdables.size(); i++)
			{
				if (found)
					break;

				if (auto* content = std::get_if<VariantItemSlot>(&holdables[i]))
				{
				if (content->isEmpty())
				{
					holdables[i] = VariantItemSlot(itemToAdd, amount.value(),
								       buffer.variant);
					return;
				}	
				if (content->item == itemToAdd && buffer.variant == content->variant) 
				{
					content->amount += amount.value();
					found = true;
				}
				}										
			}
			if (!found)
				addItemOverflow(
				    overflows, holdables,
				    VariantItemSlot(itemToAdd, amount.value(), buffer.variant));
		}
		else
		{
			for (size_t i = 0; i < holdables.size(); i++)
			{
				if (found)
					break;

				if (auto* content = std::get_if<ItemSlot>(&holdables[i]))
				{
				if (content->isEmpty())
				{
					holdables[i] = ItemSlot(itemToAdd, amount.value());
					return;
				}	
				if (content->item == itemToAdd) 
				{
					content->amount += amount.value();
					found = true;
				}
				}
			}
			if (!found)
				addItemOverflow(overflows, holdables,
						ItemSlot(itemToAdd, amount.value()));
		}
	}
}

void addItemsToInventory(OverflowHashMap &holdableOverflows,
			 OverflowContainerMap &overflowContainers, uint16_t unitIndex,
			 Inventory &inventory, InventoryAddBuffer &buffer)
{

	bool isTool = hasTags(itemTags::Tool, itemTags[buffer.holdable]);

	for (size_t i = 0; i < buffer.containerAmount; i++)
	{
		uint16_t amount = buffer.amountsPerContainer[i];
		if (amount == 0)
			continue;

		inventory.weight += itemBulkAndWeights[buffer.holdable].weight;

		if (buffer.overflow[i])
		{
			if (isTool)
				addItem(holdableOverflows,
					holdableOverflows.get(overflow_hash(unitIndex, i)), buffer);
			else
				addItem(holdableOverflows,
					holdableOverflows.get(overflow_hash(unitIndex, i)), buffer,
					std::optional<uint16_t>(amount));
		}
		else
		{
			Container *container;
			if (i < CONTAINER_UNDERFLOW_LIMIT)
				container = inventory.containers[i];
			else
				container = overflowContainers.get(unitIndex)[i];
			if (isTool)
			{
				addItem(holdableOverflows, container->holdables, buffer);
			}
			else
				addItem(holdableOverflows, container->holdables, buffer,
					std::optional<uint16_t>(amount));
		}
	}
}

inline SizeData getBulkAndWeight(Item holdable, uint16_t amount)
{
	SizeData sd = itemBulkAndWeights[holdable];
	sd.bulk *= amount;
	sd.weight *= amount;
	return sd;
}

// adds weight and bulk of items to be added, but does not add them to containers yet
inline void tabulateItemAddContainerData(Inventory &inventory, InventoryAddBuffer &buffer,
					 Container &container, uint16_t &itemAmount,
					 bool &foundSpace, bool &unsearchedInventory,
					 int containerIndex, Item holdable,
					 uint16_t &addedAmount)
{
	ContainerStorageData csd = getRemainingStorage(inventory, container);
	uint16_t storageCapacity = (uint16_t)fmin(itemAmount, getMaxItemsStored(holdable, csd));
	if (storageCapacity > 0)
	{
		buffer.containerAmount += 1;
		itemAmount -= storageCapacity;
		addedAmount += storageCapacity;
		buffer.amountsPerContainer[containerIndex] = storageCapacity;
		// change container stats
		SizeData sd = getBulkAndWeight(holdable, storageCapacity).;
		container.weight += sd.weight;
		container.bulk += sd.bulk;
	}

	// TODO: different checks for different categories
	hasTag(ContainerFullTags::ItemOverflow, container.tags)
	    ? buffer.overflow[containerIndex] = true
	    : buffer.overflow[containerIndex] = false;
	foundSpace = (itemAmount <= 0);
	unsearchedInventory = hasTag(ContainerFullTags::NextContainer, container.tags);
}

void clearNecessarySpace(Inventory &ivnentory, OverflowHashMap &overflows,
			 OverflowContainerMap &overflowContainers, )
{
}

// returns amount of items successfully added
uint16_t addItemsForce(Inventory &inventory, OverflowHashMap &overflows,
		       OverflowContainerMap &overflowContainers, Item holdable,
		       std::variant<uint16_t, Material> itemAmountOrMaterial,
		       std::optional<uint8_t> variant = std::nullopt)
{
	uint16_t amountLeft = 1;
	if (std::holds_alternative<uint16_t>(itemAmountOrMaterial))
		amountLeft = itemAmountOrMaterial;
	if (variant.has_value())
	{
		while (amountLeft >= 0)
		{
			SizeData sd = getBulkAndWeight(holdable, amountLeft);
		}
	}
}

// TODO: add 'ContainerFull' tag to make things easier.
// returns amount of items successfully added
template <typename T>
uint16_t attemptAddItems(OverflowHashMap &overflows, OverflowContainerMap &overflowContainers,
			 Inventory &inventory, uint16_t unitIndex, Strength strength,
			 Item holdable, T itemAmountOrMaterial,
			 std::optional<uint8_t> variant = std::nullopt, bool force)
{
	InventoryAddBuffer buffer;
	bool foundSpace = false;
	bool unsearchedInventory = true;
	uint16_t containerIndex = 0;
	uint16_t addedAmount = 0;

	uint16_t maxAmount =
	    (getMaxWeight(strength) - inventory.weight) / itemBulkAndWeights[holdable].weight;

	if (maxAmount < 1 && !force && getMaxWeight(strength) < itemBulkAndWeights[holdable].weight)
		return 0;

	uint16_t requiredAmount = itemAmountOrMaterial;
	if (std::holds_alternative<Material>(itemAmountOrMaterial))
	{
		requiredAmount = 1;
		buffer.material = std::optional<Material>(itemAmountOrMaterial);
	}

	if (variant.has_value())
		buffer.variant = variant;

	// containers in main inventory
	while (!foundSpace && unsearchedInventory)
	{
		Container &container = inventory.containers[containerIndex];
		tabulateItemAddContainerData(inventory, buffer, container, requiredAmount,
					     foundSpace, unsearchedInventory, containerIndex,
					     holdable, addedAmount);
	}
	// overflow containers
	if (!foundSpace && unsearchedInventory)
		containerIndex = 0;
	while (!foundSpace && unsearchedInventory)
	{
		std::vector<Container> &unitOverflowContainers = overflowContainers[unitIndex];
		Container &container = unitOverflowContainers[containerIndex];
		tabulateItemAddContainerData(inventory, buffer, container, requiredAmount,
					     foundSpace, unsearchedInventory, containerIndex,
					     holdable, addedAmount);
	}

	if (addedAmount > 0)
		addItemsToInventory(overflows, overflowContainers, unitIndex, inventory, buffer);
	if (force && requiredAmount < addedAmount)
	{
		if (std::holds_alternative<Item>(holdable))
		{
			addItemsForce(inventory, overflows, overflowContainers, holdable,
				      requiredAmount - addedAmount, variant);
		}
		else if (std::holds_alternative<Tool>(holdable))
			addItemsForce(inventory, overflows, overflowContainers, holdable,
				      std::get<Material>(itemAmountOrMaterial));
	}
}
return addedAmount;
}

inline bool removeArtOrTool(Inventory& inventory, Item item, SpecialItemData specialData)
{
	for (size_t i = 0; i < inventory.containers.size(); i++)
		{
			for (auto& content : inventory.containers[i])
			{
				if (std::holds_alternative<ArtSlot>(content) || std::holds_alternative<ToolSlot>(content))
				{
					Item item;
					std::visit([&](auto &obj) { item = obj.getType(); },
						   content);
					if (tool == contentTool &&
					    specialData == content.specialData)
					{
						content = nullptr;
						return true;
					}
				}
			}
		}
	return false;
}

inline void removeItem(Inventory& inventory, Item item, uint16_t amount, std::optional<uint8_t> variant = std::nullopt)
{
	uint16_t removedAmount = 0;
	for (size_t i = 0; i < inventory.containers.size(); i++)
		{
			for (auto content : inventory.containers[i])
			{
				if (variant == std::nullopt)
				{
					if (std::holds_alternative<ItemSlot>(content)) {
					Item contentItem;
					std::visit([&](auto &obj) { contentItem = obj.getType(); },
						   content);
					if (item == contentItem)
					{
						removedAmount = min(amount, content.amount);
						content.amount -= removedAmount;
					}
					}
				}
				else
				{
					if (std::holds_alternative<VariantItemSlot>(content)) {
						Item contentItem;
					std::visit([&](auto &obj) { contentItem = obj.getType(); },
						   content);
					if (item == contentItem && content.variant = variant)
					{
						removedAmount = min(amount, content.amount);
						content.amount -= removedAmount;
					}
					}
				}
			}
		}
	return removedAmount;
}

//returns amount removed
uint16_t &removeItem(OverflowHashMap &overflows,
					  OverflowContainerMap &overflowContainers,
					  Inventory &inventory, uint16_t unitIndex,
					  Item holdable,
				      std::variant<uint16_t, Material> itemAmountOrMaterial, std::optional<uint8_t> variant = std::nullopt)
{
	if (hasTags(itemTags::Tool, itemTags[holdable]))
	{
	if (variant == std::nullopt) {
		return removeItem(inventory, item, std::get<uint16_t>(amount));
	} else removeItem(inventory, item, std::get<uint16_t>(amount), variant);
	} else ()
	{
		removeTool(inventory, tool, std::get<Material>(itemAmountOrMaterial)) ? return 1 : return 0;
	}
}

