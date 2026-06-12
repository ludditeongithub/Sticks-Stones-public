#include <stack>
#include <core/packed_enum.hpp>
#include <macros/database.hpp>
#include "systems/find_nearest.hpp"
#include "world/tile/database.hpp"
#include <core/hash.hpp>
#include <extern/cereal/binary_archive.hpp>
#include <world/item/enum.hpp>
#include <core/data.hpp>
#include <core/containers.hpp>

// for items in the world, not in inventory
struct ItemDatabase
{
#define ITEM_INDEPENDENT_MEMBERS(X)                                                                     \
	X(TileDatabase*, tiles)                                                                                   \
		X(World*, world)                                                                        

#define ITEM_STD_CONTAINERS(X) \

#define ITEM_RUNTIME_ARRAYS(X)                                                                          \
		X(Item, items, item, item)                                                                             \
		X(Coord, coords, coord, coord)

	DEFAULT_DATABASE_CREATION(Item, item, ITEM);
		
	inline void addItem(Item item, Coord coord);
	inline void dropFruit(Plant plant, Coord coord, uint16_t amount);
};

struct VariantItemDatabase : ItemDatabase {
	 Array<uint8_t> variants;
};


