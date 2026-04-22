#include <stack>
#include <core/packed_enum.hpp>
#include "enum.hpp"
#include "systems/find_nearest.hpp"
#include "tags.hpp"
#include "world/tile/database.hpp"
#include <array>
#include <core/hash.hpp>
#include <unordered_map>
#include <variant>
#include <vector>
#include <world/item/enum.hpp>
#include <core/data.hpp>
#include <core/containers.hpp>

constexpr uint16_t HOLDABLE_UNDERFLOW_LIMIT = 6;

struct ItemSlot
{
	Item item; // HOLDING for hands if hands are holding multiple items instead of using item
	uint16_t amount; // doubles as index for container

	ItemSlot(Item item, uint16_t amount) : item(item), amount(amount)
	{
		assert(!hasTag(ItemTags::Variant | ItemTags::Tool | ItemTags::Art, itemTags[item]));
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
		assert(hasTag(ItemTags::Variant, itemTags[item]));
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
		assert(hasTag(ItemTags::Tool, itemTags[item]));
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
		assert(hasTag(ItemTags::Art, itemTags[item]));
	}

	inline bool isEmpty()
	{
		if (item == Item::NONE)
			return true;
		return false;
	}	
	inline Item getType() { return item; }
};

struct MealSlot {
	uint16_t mealIndex;
	Quality quality;
};

using HoldableSlot = std::variant<ItemSlot, VariantItemSlot, ToolSlot, ArtSlot, MealSlot>;

enum class ContainerFullTags : uint8_t
{
	NONE = 0,
	Empty = 1 << 1,
	HandsOnly = 1 << 2,
	InventoryContainersFull = 1 << 3,
	NextContainer = 1 << 4, // if there is a next container
	ItemOverflow = 1 << 5,
	VariantItemOverflow = 1 << 6,
	ToolOverflow = 1 << 7
};

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
		assert(hasTag(ItemTags::Container, itemTags[type]));
	}
};

// for items in the world, not in inventory
struct ItemDatabase
{
	Array<Item> types;
	Array<Coord> coords;
	std::stack<uint16_t> nextIndex;
	TileDatabase *tiles;
	World *world;
	SearchGrid *search;

	inline void addItem(Item item, Coord coord);
	inline void dropFruit();
};

struct VariantItemDatabase {
	Array<Item> types;
	Array<uint8_t> variant;
};

struct ContainerStorageData
{
	float remainingWeight = 0;
	float remainingBulk = 0;
};

inline uint32_t overflow_hash(uint16_t unitIndex, uint16_t containerIndex)
{
	return hash_pair(unitIndex, containerIndex);
}

