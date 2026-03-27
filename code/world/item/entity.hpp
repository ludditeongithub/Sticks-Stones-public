#include "core/packed_enum.hpp"
#include "enum.hpp"
#include "tags.hpp"
#include <array>
#include <core/hash.hpp>
#include <unordered_map>
#include <variant>
#include <vector>
#include <iostream>

constexpr uint16_t HOLDABLE_UNDERFLOW_LIMIT = 6;

struct ItemSlot
{
	Item item; // HOLDING for hands if hands are holding multiple items instead of using item
	uint16_t amount; // doubles as index for container

	ItemSlot(Item item, uint16_t amount) : item(item), amount(amount)
	{
		assert(!hasTag(itemTags::Variant | itemTags::Tool | itemTags::Art, itemTags[item]));
	}

	inline bool isEmpty()
	{
		if (amount == 0)
			return true;
		if (item == Item::NONE)
			return true;
		return false;
	}
	inline Item getType() { return item; }
	inline void operator+=(uint16_t add) { amount += add; }
};

struct VariantItemSlot
{
	Item item;
	uint16_t amount;
	uint8_t variant;

	VariantItemSlot(Item item, uint16_t amount, uint8_t variant)
	    : item(item), amount(amount), variant(variant)
	{
		assert(hasTag(itemTags::Variant, itemTags[item]));
	}

	inline bool isEmpty()
	{
		if (amount == 0)
			return true;
		if (item == Item::NONE)
			return true;
		return false;
	}
	inline Item getType() { return item; }
};

//∇TODO: merge tool with item. since toolslot does not store amount, Tool as type is unnecessary. can have tag checks. possibly merge with ArtSlot
struct ToolSlot
{
	Item item;
	SpecialItemData specialData;

	ToolSlot(Item item, SpecialItemData specialData) : item(item), specialData(specialData)
	{
		assert(hasTag(itemTags::Tool, itemTags[item]));
	}

	inline bool isEmpty()
	{
		if (item == Item::NONE)
			return true;
		return false;
	}
	inline Item getType() { return item; }
};

struct ArtSlot {
	Item item;
	SpecialItemData specialData;

	ArtSlot(Item item, SpecialItemData specialData) : item(item), specialData(specialData)
	{
		assert(hasTag(itemTags::Art, itemTags[item]));
	}

	inline bool isEmpty()
	{
		if (item == Item::NONE)
			return true;
		return false;
	}	
	inline Item getType() { return item; }
};

using HoldableSlot = std::variant<ItemSlot, VariantItemSlot, ToolSlot, ArtSlot>;

enum class ContainerFullTags : uint8_t
{
	Empty,
	HandsOnly,
	InventoryContainersFull,
	NextContainer, // if there is a next container
	ItemOverflow,
	VariantItemOverflow,
	ToolOverflow
};

inline ContainerFullTags operator|(ContainerFullTags a, ContainerFullTags b)
{
	return static_cast<ContainerFullTags>(
	    static_cast<std::underlying_type_t<ContainerFullTags>>(a) |
	    static_cast<std::underlying_type_t<ContainerFullTags>>(b));
}

inline ContainerFullTags &operator|=(ContainerFullTags &a, ContainerFullTags b)
{
	a = a | b;
	return a;
}

inline ContainerFullTags operator&(ContainerFullTags a, ContainerFullTags b)
{
	return static_cast<ContainerFullTags>(
	    static_cast<std::underlying_type_t<ContainerFullTags>>(a) &
	    static_cast<std::underlying_type_t<ContainerFullTags>>(b));
}

inline bool hasTag(ContainerFullTags value, ContainerFullTags tag)
{
	return static_cast<std::underlying_type_t<ContainerFullTags>>(value & tag) != 0;
}

struct Container
{
	Item type;
	ContainerFullTags tags;
	float bulk = 0;
	float weight = 0;

	std::array<HoldableSlot, HOLDABLE_UNDERFLOW_LIMIT> holdables;
	// TODO: can go back and optimize? this into 3 seperate fields
	//  std::array<ItemSlot, 3> items;
	//  VariantItemSlot variantItem;
	//  std::array<ToolSlot, 2> tools;

	Container(Item type, ContainerFullTags tags, float bulk, float weight) : type(type), tags(tags), bulk(bulk), weight(weight)
	{
		assert(hasTag(itemTags::Container, itemTags[type]));
	}		
};

struct ContainerStorageData
{
	float remainingWeight = 0;
	float remainingBulk = 0;
};

using OverflowHashMap = std::unordered_map<uint32_t, std::vector<HoldableSlot>>;

using OverflowContainerMap = std::unordered_map<uint16_t, std::vector<Container>>;

inline uint32_t overflow_hash(uint16_t unitIndex, uint16_t containerIndex)
{
	return hash_pair(unitIndex, containerIndex);
}
