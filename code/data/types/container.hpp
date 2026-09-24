#pragma once
#include <array>
#include <variant>
#include <core/hash.hpp>
#include <core/packed_enum.hpp>
#include <data/types/item.hpp>
#include <data/const/tags.hpp>

// @codegen:begin specialization
//
// @codegen:end specialization

constexpr uint16_t HOLDABLE_UNDERFLOW_LIMIT = 6;

// Fine means that only fine objects can be carried, mid means that loose, soft, or solid objects
// can be carried, single means that only single objects can be carried
enum class BulkStatus : uint8_t
{
	NONE,
	Liquid,
	Fine,
	Mid,
	Single
};


struct ContainerData
{
    BulkStatus bulk_status;
	float bulk;
	float weight;
    bool liquid;
};

struct ItemSlot
{
	Item item; // HOLDING for hands if hands are holding multiple items instead of using item
	uint16_t amount; // doubles as index for container

	ItemSlot(Item item, uint16_t amount) : item(item), amount(amount)
	{
			assert(!has_tag(item::Tag::Variant | item::Tag::OneHandedTool | item::Tag::TwoHandedTool | item::Tag::Art, item::TAGS[item]));
	}

	inline bool is_empty()
	{
		if (amount == 0)
			return true;
		if (item == Item::NONE)
			return true;
		return false;
	}
	inline Item get_type() { return item; }
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
		assert(has_tag(item::Tag::Variant, item::TAGS[item]));
	}

	inline bool is_empty()
	{
		if (amount == 0)
			return true;
		if (item == Item::NONE)
			return true;
		return false;
	}
	inline Item get_type() { return item; }
};

//∇TODO: merge tool with item. since toolslot does not store amount, Tool as type is unnecessary. can have tag checks. possibly merge with ArtSlot
struct ToolSlot
{
	Item item;
	SpecialItemData special_data;

	ToolSlot(Item item, SpecialItemData special_data) : item(item), special_data(special_data)
	{
		assert(has_tag(item::Tag::OneHandedTool, item::TAGS[item]));
	}

	inline bool is_empty()
	{
		if (item == Item::NONE)
			return true;
		return false;
	}
	inline Item get_type() { return item; }
};

struct ArtSlot {
	Item item;
	SpecialItemData special_data;

	ArtSlot(Item item, SpecialItemData special_data) : item(item), special_data(special_data)
	{
		assert(has_tag(item::Tag::Art, item::TAGS[item]));
	}

	inline bool is_empty()
	{
		if (item == Item::NONE)
			return true;
		return false;
	}	
	inline Item get_type() { return item; }
};

struct MealSlot {
	uint16_t meal_index;
	Quality quality;
};

struct NullSlot {
  
};

using HoldableSlot = std::variant<NullSlot, ItemSlot, VariantItemSlot, ToolSlot, ArtSlot, MealSlot>;

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
	ContainerType type = ContainerType::NONE;
	ContainerFullTags tags = ContainerFullTags::NONE;
	float bulk = 0;
	float weight = 0;

	std::array<HoldableSlot, HOLDABLE_UNDERFLOW_LIMIT> holdables;
	// OPTI: can go back and optimize? this into 3 seperate fields
	//  std::array<ItemSlot, 3> items;
	//  VariantItemSlot variant_item;
	//  std::array<ToolSlot, 2> tools;

	Container(ContainerType type, ContainerFullTags tags, float bulk, float weight) : type(type), tags(tags), bulk(bulk), weight(weight)
	{
			//	assert(has_tag(item::Tag::Container, item::TAGS[type]));
			for (auto x: holdables) x = NullSlot();
	}


		Container() = default;
};

struct ContainerStorageData
{
	float remaining_weight = 0.0;
	float remaining_bulk = 0.0;
};

inline uint32_t overflow_hash(uint16_t unit_index, uint16_t container_index)
{
	return hash_pair(unit_index, container_index);
}

ContainerType item_to_container(Item c)
{
	switch (c)
	{
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

float get_container_capacity(ContainerType c)
{
	float capacity;
	switch (c)
	{
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

ContainerData bulk_and_weights[static_cast<int>(Item::MAX) + static_cast<int>(ContainerType::MAX)];

