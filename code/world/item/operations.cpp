#include "database.hpp"
#include "systems/find_nearest.hpp"

inline void ItemDatabase::addItem(Item item, Coord coord, uint16_t amount = 1)
{
	Coord select = tiles->getNearestEmptyTile(coord);
	uint16_t i = nextIndex.top();
	nextIndex.pop();
	types[i] = item;
	coords[i] = select;	
}

inline void ItemDatabase::dropFruit(Plant plant, Coord coord, uint16_t amount)
{
	
	Coord select = tiles->getNearestEmptyTile(coord);
	uint16_t i = nextIndex.top();	
}
