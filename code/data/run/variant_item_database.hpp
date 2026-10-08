#pragma once
#include <cstdint>
#include <vector>

#include <core/containers.hpp>
#include <logic/generic/search/search.hpp>
#include <data/run/tile_database.hpp>
#include <data/types/item.hpp>

namespace variant_item
{
class Database {
		// @codegen:begin database_generation
public:
// =========================
// BASE DATABASE MEMBERS
// =========================

constexpr static uint16_t ENTITY_SIZE = sizeof(Item) +
+ sizeof(bool)
  
 +  sizeof(Item) 
 +  sizeof(Coord) 
 +  sizeof(Variant) 
;

size_t capacity;
    size_t size = 1; // 0 is placeholder
    std::stack<size_t> free_slots;
    Array<bool> alives;
  SearchGrid& search;
  Array<EntityID> no_inertia_buffer; 
  Array<EntityID> unassigned_buffer;
  tile::Database* tiles;

    // =========================
    // ENTITY-SPECIFIC MEMBERS
    // =========================
    Array<Item> items;
    Array<Coord> coords;
    Array<Variant> variants;



// =========================
// INIT
// =========================

  void init(Arena* arena, size_t capacity
  , SearchGrid& search
  , tile::Database& tiles
) 
{
this->capacity = capacity;
  no_inertia_buffer = arena_make_array<EntityID>(arena, capacity);
  unassigned_buffer = arena_make_array<EntityID>(arena, capacity);
  this->size = 0;
  this->tiles = &tiles;
 
  items = arena_make_array<Item>(arena, capacity);
 
  coords = arena_make_array<Coord>(arena, capacity);
 
  variants = arena_make_array<Variant>(arena, capacity);
 

}
    // =========================
    // SERIALIZATION
    // =========================

      template <class Archive>
    void serialize(Archive &archive) const
{
        archive(tiles);
        archive(search);
        archive(size);
        archive(free_slots);
        archive(alives);

           items.serialize(archive);
           coords.serialize(archive);
           variants.serialize(archive);
         
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
  inline Variant& variant(const EntityID index) {
return variants[index];
  }


  
// =========================
// GENERATION
// =========================


  // =========================
  // SPAWN
  // =========================

bool attempt_spawn(const Item item, const Coord coord, const bool newborn  , const Variant variant  , const bool insert_search = true
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
            this->variant(i) = variant;
        }
        else
        {
        Time age = random_bool->next();
            this->item(i) = item;
            this->coord(i) = coord;
            this->variant(i) = variant;
        }
            if (insert_search) search.insert_entity(item, {i, this->coord(i)});
        return i;
          }
          
        

          bool spawn(const Item item, const Coord origin, const bool newborn
  , const Variant variant
, const bool insert_search = true) {
Coord spawn_point = tiles->get_nearest_empty_tile(origin);
bool result = false;
result = attempt_spawn(item, spawn_point, newborn
  , variant
, insert_search  
);
if (!result) {
free_unused_entity();
attempt_spawn(item, spawn_point, newborn
  , variant
, insert_search  
);
}
return result;
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
    for (size_t i = 0; i < coords.capacity; i++) {
    if (tiles->tile_status(i).get<VisionStatus>() == VisionStatus::Hidden) remove(i);
    }
  }
    



// =========================
// TRANSFER
// =========================

inline bool transfer(size_t i, item::Database &old_db)
  {
  assert(i < size);
  
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
    variant(index) = old_db.variant(i);
  alives[index] = true;

  old_db.free_slots.push(i);
  old_db.alives[index] = false;
  return true;
  }
  
// @codegen:end database_generation

};
		
}
