#pragma once
#include <vector>
#include "data/run/tile_database.hpp"
#include <core/hash.hpp>
#include <../extern/cereal/archives/binary.hpp>
#include <data/types/item.hpp>

#include <core/containers.hpp>
#include <logic/generic/search/search.hpp>

namespace item {
// for items in the world, not in inventory
class Database
{

  // @codegen:begin database_generation
public:
// =========================
// BASE DATABASE MEMBERS
// =========================

constexpr static uint16_t ENTITY_SIZE = sizeof(Item) +
+ sizeof(bool)
  
 +  sizeof(Item) 
 +  sizeof(Coord) 
;

size_t capacity;
    size_t size = 1; // 0 is placeholder
    std::stack<size_t> free_slots;
    std::vector<bool> alives;
  SearchGrid& search;
  std::vector<EntityID> no_inertia_buffer; 
  std::vector<EntityID> unassigned_buffer;
  tile::Database& tiles;

    // =========================
    // ENTITY-SPECIFIC MEMBERS
    // =========================
    std::vector<Item> items;
    std::vector<Coord> coords;



// =========================
// CONSTRUCTOR
// =========================

  Database(size_t capacity
  , SearchGrid& search
  , tile::Database& tiles
) 
    : tiles(tiles),
search(search)
  
{
this->capacity = capacity;
  no_inertia_buffer.reserve(capacity);
  unassigned_buffer.reserve(capacity);

  this->size = 0;


 
  items.reserve(capacity);
  items.resize(capacity);
 
  coords.reserve(capacity);
  coords.resize(capacity);
 
}

// =========================
// GETTERS
// =========================

  inline Item& item(const EntityID index) {
return items[index];
  }
  inline Coord& coord(const EntityID index) {
return coords[index];
  }


  
  // =========================
  // SPAWN
  // =========================


bool attempt_spawn(const Item item, const Coord coord, const bool newborn  , const bool insert_search = true
)
{
#if !SHIPPING_BUILD
assert(item != Item::NONE && item != Item::MAX && "Tried to spawn item as NONE or MAX.");
#endif


        if (size + 1 > capacity)
            return 0;
        size_t i;
        if (free_slots.empty())
        {
            i = size;
            size++;
        }
        else
        {
            i = free_slots.top();
            free_slots.pop();
        }
        alives[i] = true;
        if (newborn)
        {
            this->item(i) = item;
            this->coord(i) = coord;
        }
        else
        {
        Time age = random_bool->next();
            this->item(i) = item;
            this->coord(i) = coord;
        }
            if (insert_search) search.insert_entity(item, {i, this->coord(i)});
        return i;
          }
          
        

          bool spawn(const Item item, const Coord origin, const bool newborn
, const bool insert_search = true) {
Coord spawn_point = tiles.get_nearest_empty_tile(origin);
bool result = false;
result = attempt_spawn(item, spawn_point, newborn
, insert_search  
);
if (!result) {
free_unused_entity();
attempt_spawn(item, spawn_point, newborn
, insert_search  
);
}
}        
    

  // =========================
  // REMOVE
  // =========================
  
  inline bool remove(const EntityID i)
  {
        if (!alives[i])
            return false;

        free_slots.push(i);
        alives[i] = false;
        Item item = this->item(i);
            search.remove_entity(item, {i, coord(i)});
        return true;
  }

  inline void free_unused_entity()
  {
    for (size_t i = 0; i < coords.size(); i++) {
    if (tiles.tile_status(i).get<VisionStatus>() == VisionStatus::Hidden) remove(i);
    }
  }
    


    // =========================
    // SERIALIZATION
    // =========================

  // genreal serialization

      template <class Archive>
    void serialize(Archive &archive) const
  {
         archive(tiles,
search,
size,
free_slots,
alives,
items,
coords);
    }


// =========================
// TRANSFER
// =========================


inline bool transfer(size_t i, item::Database &old_db)
  {
  #if !SHIPPING_BUILD
  assert(i < size);
  #endif
  
  if (size >= capacity) return false;
  int index;  
  if (free_slots.empty())
  {
  index = ++size;
	}
	else
	{
		index = free_slots.top();
		free_slots.pop();			
  }
    item(index) = old_db.item(i);
    coord(index) = old_db.coord(i);
  alives[index] = true;

  old_db.free_slots.push(i);
  old_db.alives[index] = false;
  return true;
  }
// @codegen:end database_generation
  
	inline void add_item(Item item, Coord coord);
	inline void drop_fruit(Plant plant, Coord coord, uint16_t amount);
};

struct PerishableDatabase
{
		Database &database;
		
};

struct VariantDatabase {
		Database &database;
		Array<Variant> variants;
};
  
}
