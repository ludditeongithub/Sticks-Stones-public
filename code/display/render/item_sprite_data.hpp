#pragma once
#include <data/types/item.hpp>
#include <core/tables.hpp>


inline constexpr BitsetTable<Item> item_ascending_versions = []
	{
		BitsetTable<Item> t{};
		
		return t;
	}();

inline constexpr LookupTable<Item,uint8_t> item_pixel_translations = [] {
	LookupTable<Item,uint8_t> lt{};
	using enum Item;
	
	return lt;
}();

//items which can be stacked. need multiple layered versions.
inline constexpr LookupTable<Item, Coord> item_sprite_dimensions = []
{
	LookupTable<Item, Coord> lt{};


	for (size_t i = 0; i < static_cast<uint16_t>(Item::MAX); i++)
	{
		lt[static_cast<Item>(i) ] = {1,1};
	}

	using enum Item;

	lt[Log] = {2,2};
	lt[Headdress] = {2,2};

	return lt;
}();


inline constexpr LookupTable<Item, uint8_t> item_sprite_variants = []
{
	LookupTable<Item,uint8_t> lt{};
	using enum Item;
	lt[String] = 2;
	lt[Hay] = 1;
	return lt;
}();

