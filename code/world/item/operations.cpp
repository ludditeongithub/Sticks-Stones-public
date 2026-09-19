#include "database.hpp"

inline void item::Database::drop_fruit(Plant plant, Coord coord, uint16_t amount)
{
	
	Coord select = tiles.get_nearest_empty_tile(coord);
	uint16_t i = free_slots.top();	
}
