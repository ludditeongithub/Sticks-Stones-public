#include "database.hpp"


inline void ItemDatabase::add_item(Item item, Coord coord, uint16_t amount = 1)
{
	Coord select = tiles->getNearestEmptyTile(coord);
	uint16_t i = nextIndex.top();
	nextIndex.pop();
	types[i] = item;
	coords[i] = select;	
}

inline void ItemDatabase::drop_fruit(Plant plant, Coord coord, uint16_t amount)
{
	
	Coord select = tiles->getNearestEmptyTile(coord);
	uint16_t i = nextIndex.top();	
}
