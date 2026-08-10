#pragma once
#include <stack>
#include <core/packed_enum.hpp>
#include "world/tile/database.hpp"
#include <core/hash.hpp>
#include <cereal/binary_archive.hpp>
#include <world/item/enum.hpp>
#include <core/data.hpp>
#include <core/containers.hpp>

namespace item {
// for items in the world, not in inventory
struct Database
{

  // @codegen:begin database_generation
// =========================
// BASE DATABASE MEMBERS
// =========================

constexpr static uint16_t entity_size = sizeof(Item) +
+ sizeof(bool)
  
 +  sizeof(Item) 
 +  sizeof(Coord) 
;

size_t capacity;
    size_t size;
    Stack<size_t> free_slots;
    Array<bool> alives;
  SearchGrid& search;
  World& world;
  
  std::vector<EntityID>& no_inertia_buffer; // size is amount of no inertias this loop
  
  std::vector<EntityID>& unassigned_buffer; // size is amount of unassigned this loop
  tile::Database& tiles;

    // =========================
    // ENTITY-SPECIFIC MEMBERS
    // =========================
    Array<Item> items;
    Array<Coord> coord;



// =========================
// CONSTRUCTOR
// =========================

Database(Arena *arena, size_t capacity
  , World& world
 
  , SearchGrid& search
  , tile::Database& tiles
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
return items[index];
  }
  inline Coord& coord(size_t index) {
return coord[index];
  }


  // =========================
  // SPAWN
  // =========================

 
  bool attempt_spawn(Item item, bool newborn, Coord coord  , bool insert_search = true
)
  {       
        if (size + 1 > capacity)
            return false;
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
            coord(i) = coord;
        }
        else
        {
        Time age = random_bool->next();
            items(i) = item;
            coord(i) = coord;
        }
            if (insert_search) search.insert_entity(item, {i, coord(i)});
        return true;
          }
          
          bool spawn(Item item, bool newborn, Coord origin) {
          Coord spawn_point = tiles.get_nearest_empty_tile(origin);
          while (!attempt_spawn(item, newborn, spawn_point)) free_unused_entity();                 
          }        
    

  // =========================
  // REMOVE
  // =========================
  
  bool remove(size_t i)
  {
        if (!alive(i))
            return false;

        free_slots.push(i);
        alive(i) = false;
        Item item = item(i);
            search.remove_entity(item, {i, coord(i)});
        return true;
  }

  void free_unused_entity()
  {
    for (size_t i = 0; i < coords.size; i++) {
    if (tiles.tile_status(i).get<VisionStatus>() == VisionStatus::Hidden) remove(i);
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
        coord.save(archive);
    }

    template <class Archive>
    void load(Archive &archive)
    {
        archive(capacity);
        archive(size);
        archive(free_slots);
        archive(alives);
        
        items.load(archive);
        coord.load(archive);
    }


// =========================
// TRANSFER
// =========================

inline bool transferItem(size_t i, ItemDatabase &old_db, ItemDatabase &new_db)
  {
  if (new_db.size >= new_db.capacity) return false;
  int index;  
  if (new_db.free_slots.empty())
  {
  index = ++size;
	}
	else
	{
		index = new_db.free_slots.top();
		new_db.free_slots.pop();			
  }
    new_db.items(index) = old_db.items(i);
    new_db.coord(index) = old_db.coord(i);
  new_db.alive(index) = true;
  old_db.free_slots.push(i);
  old_db.alive(index) = false;
  return true;
  }
// @codegen:end database_generation
  
	inline void add_item(Item item, Coord coord);
	inline void drop_fruit(Plant plant, Coord coord, uint16_t amount);
};

struct PerishableDatabase
{
	Database database;
              
};
  
}
