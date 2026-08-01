#include "database.hpp"


inline void item::Database::add_item(Item item, Coord coord, uint16_t amount = 1)
{
	Coord select = tiles->get_nearest_empty_tile(coord);
	uint16_t i = next_index.top();
	next_index.pop();
	types[i] = item;
	coords[i] = select;	
}

inline void item::Database::drop_fruit(Plant plant, Coord coord, uint16_t amount)
{
	
	Coord select = tiles->get_nearest_empty_tile(coord);
	uint16_t i = next_index.top();	
}
