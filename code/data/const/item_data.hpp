#ifndef ITEMBULKANDWEIGHT_H_
#define ITEMBULKANDWEIGHT_H_

#include <cstdint>
#include <core/tables.hpp>
#include <data/types/item.hpp>

// the total volume of each bulk category hands can maximally carry.
// where 0.1 is 100mL
// NOTE: idea: consider doing left and right
constexpr float FINE_BULK_MAX = 0.3;
constexpr float LOOSE_BULK_MULT = 5.5; // multiplies mid bulk
constexpr float SOFT_BULK_MULT = 2.5;  // mulitiplies mid bulk
constexpr float SOLID_BULK_MULT = 1.0; // mulitiplies mid bulk
constexpr float MID_BULK_MAX = 35.0;
constexpr float SINGLE_BULK_MAX = 60.0;

constexpr float MAX_CARRY = 250.0;

constexpr uint8_t HUMAN_SIGHT = 50;
constexpr uint16_t NEAR_GATHER_RANGE = HUMAN_SIGHT; // the farthest a pawn will  go to fetch an item
constexpr uint16_t MID_GATHER_RANGE = HUMAN_SIGHT * 2;

constexpr uint16_t PRODUCT_MAX_INGREDIENTS = 5;

// Fine means that only fine objects can be carried, mid means that loose, soft, or solid objects
// can be carried, single means that only single objects can be carried

float current_max_bulk(BulkStatus bs, Strength str)
{
	switch (bs)
	{
	case BulkStatus::Fine:
		return FINE_BULK_MAX * str;
	case BulkStatus::Mid:
		return MID_BULK_MAX * str;
	case BulkStatus::Single:
		return SINGLE_BULK_MAX * str;
	}
	return 0.0;
}

float max_weight(Strength str) { return str / STAT_MAX * MAX_CARRY; }

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

SizeData bulk_and_weights[Item::MAX + Container::MAX];

bool valid_container(Container container, Item new_item)
{
	switch (bulk_and_weights[static_cast<int>(new_item)].bulklevel)
	{
	case BulkLevel::Liquid:
		if (!container.liquid_mode)
			return false;
		if (container.container_type == ContainerType::Basket)
			return false;
	case BulkLevel::Fine:
		if (container.container_type == ContainerType::Basket)
			return false;
	}
	if (container.current_bulk + bulk_and_weights[static_cast<int>(new_item)].bulk >
	    get_container_capacity(container.container_type))
		return false;
	return true;
}

struct SizeData
{
	float bulk = 0.0;
	float weight = 0.0;
	BulkLevel bulklevel = BulkLevel::Solid;
};

#endif // ITEMBULKANDWEIGHT_H_
