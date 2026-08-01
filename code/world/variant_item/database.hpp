#pragma once

#include <world/item/database.hpp>
namespace variant_item {
struct Database {
		// @codegen:begin database_generation
// =========================
// BASE DATABASE MEMBERS
// =========================

constexpr static uint16_t entity_size = sizeof(Item) +
+ sizeof(bool)
  
 +  sizeof(Item) 
 +  sizeof(Coord) 
 +  sizeof(Variant) 
;

size_t capacity;
    size_t size = 1; // 0 is placeholder
    Stack<size_t> free_slots;
    Array<bool> alives;
  SearchGrid& search;
  World& world;
  
  std::vector<EntityID>& no_inertia_buffer; // size is amount of no inertias this loop
  
  std::vector<EntityID>& unassigned_buffer; // size is amount of unassigned this loop

  TileDatabase& tiles;

    // =========================
    // ENTITY-SPECIFIC MEMBERS
    // =========================
    Array<Item> items;
    Array<Coord> coords;
    Array<Variant> variants;

    struct main {
    
    
    }


// =========================
// CONSTRUCTOR
// =========================

Database(Arena *arena, size_t capacity
  , World& world
 
  , SearchGrid& search
  , TileDatabase& tiles
) :
  world(world),
  tiles(tiles),
search(search),
{
this->capacity = capacity;

  this->size = 0;

}

// =========================
// GETTERS
// =========================

  inline Item& items(size_t index) {
return itemss[index];
  }
  inline Coord& coords(size_t index) {
return coordss[index];
  }
  inline Variant& variants(size_t index) {
return variantss[index];
  }

    inline Coord& coords(size_t index) {    
return main[index].coords;
    }
    inline Variant& variants(size_t index) {    
return main[index].variants;
    }

  // =========================
  // SPAWN
  // =========================


// returns 0 if failed
  size_t attempt_spawn(Item item, bool newborn, Coord coord  , Variant variant  , bool insert_search = true
)
  {       
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
            items(i) = item;
            coords(i) = coord;
            variants(i) = variant;
        }
        else
        {
        Time age = random_bool->next();
            items(i) = item;
            coords(i) = coord;
            variants(i) = variant;
        }
            if (insert_search) search.insert_entity(item, {i, coord(i)});
        return i;
          }
          
          size_t spawn(Item item, bool newborn, Coord origin
  ,Variant variant
bool insert_search = true) {
Coord spawn_point = tiles.get_nearest_empty_tile(origin);
size_t result = 0;
while (result == 0) {
result = attempt_spawn(item, newborn, spawn_point
  , Variant variant
, insert_search);
if (result == 0) free_unused_entity();
}
}        
    

  // =========================
  // REMOVE
  // =========================
  
  inline bool remove(size_t i)
  {
        if (!alives[i])
            return false;

        free_slots.push(i);
        alives[i] = false;
        Item item = items[i];
            search.remove_entity(item, {i, coords[i]});
        return true;
  }

  inline void free_unused_entity()
  {
    for (size_t i = 0; i < coords.size; i++) {
    if (tiles.tile_statuses[i].get<VisionStatus>() == VisionStatus::Hidden) remove(i);
    }
  }
    


    // =========================
    // SERIALIZATION
    // =========================

    template <class Archive>
    void save(Archive &archive) const
    {
    archive(capacity);
        archive(size);
        archive(free_slots);
        archive(alives);
   

        items.save(archive);
        coords.save(archive);
        variants.save(archive);
    }

    template <class Archive>
    void load(Archive &archive)
    {
        archive(capacity);
        archive(size);
        archive(free_slots);
        archive(alives);
        
        items.load(archive);
        coords.load(archive);
        variants.load(archive);
    }


// =========================
// TRANSFER
// =========================

inline bool transfer(size_t i, item::Database &old_db)
  {
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
    items[index] = old_db.items[i];
    coords[index] = old_db.coords[i];
    variants[index] = old_db.variants[i];
  alives[index] = true;
  old_db.free_slots.push(i);
  old_db.alives[index] = false;
  return true;
  }
// @codegen:end database_generation
};
}
