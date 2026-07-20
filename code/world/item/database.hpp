#include <stack>
#include <core/packed_enum.hpp>
#include <macros/database.hpp>

#include "world/tile/database.hpp"
#include <core/hash.hpp>
#include <extern/cereal/binary_archive.hpp>
#include <world/item/enum.hpp>
#include <core/data.hpp>
#include <core/containers.hpp>

// for items in the world, not in inventory
struct ItemDatabase
{

  // @codegen:begin database_generation
    // =========================
    // BASE DATABASE MEMBERS
    // =========================

constexpr static uint16_t ENTITY_SIZE = sizeof(Item) +
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
  TileDatabase& tiles;

    // =========================
    // ENTITY-SPECIFIC MEMBERS
    // =========================
    Array<Item> items;
    Array<Coord> coords;
    

// =========================
    // CONSTRUCTOR
    // =========================

ItemDatabase(Arena *arena, size_t capacity
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
  // SPAWN
  // =========================

 
  bool attempt_spawn(Item item, bool newborn, Coord coord )
  {       
        if (size + 1 > capacity)
            return false;
        size_t i;
        if (freeSlots.empty())
        {
            i = size;
            size++;
        }
        else
        {
            i = freeSlots.top();
            freeSlots.pop();
        }
        alives[i] = true;
        if (newborn)
        {
            items[i] = item;
            coords[i] = coord;
        }
        else
        {
        Time age = random_bool->next();
            items[i] = item;
            coords[i] = coord;
        }
            search.insertEntity(item, {i, coords[i]});
        return true;
          }
          bool spawn(Item item, bool newborn, Coord origin) {
          Coord spawn_point = tiles.getNearestEmptyTile(origin);
          while (!attempt_spawn(item, newborn, spawn_point)) free_unused_entity();                 
          }        
    

  // =========================
  // REMOVE
  // =========================
  
  bool remove(size_t i)
  {
        if (!alives[i])
            return false;

        freeSlots.push(i);
        alives[i] = false;
        Item item = items[i];
            search.removeEntity(item, {i, coords[i]});
        return true;
  }

  void free_unused_entity()
  {
    for (size_t i = 0; i < coords.size; i++) {
    if (tiles.tileStatuses[i].get<VisionStatus>() == VisionStatus::Hidden) remove(i);
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
        archive(freeSlots);
        archive(alives);
   

        items.save(archive);
        coords.save(archive);
    }

    template <class Archive>
    void load(Archive &archive)
    {
        archive(capacity);
        archive(size);
        archive(freeSlots);
        archive(alives);
        
        items.load(archive);
        coords.load(archive);
    }


// =========================
// TRANSFER
// =========================

inline bool transfer_item(size_t i, ItemDatabase &old_db, ItemDatabase &new_db)
  {
  if (new_db.size >= new_db.capacity) return false;
  int index;  
  if (new_db.freeSlots.empty())
  {
  index = ++size;
	}
	else
	{
		index = new_db.freeSlots.top();
		new_db.freeSlots.pop();			
  }
    new_db.items[index] = old_db.items[i];
    new_db.coords[index] = old_db.coords[i];
  new_db.alives[index] = true;
  old_db.freeSlots.push(i);
  old_db.alives[index] = false;
  return true;
  }
// @codegen:end database_generation
  
	inline void add_item(Item item, Coord coord);
	inline void drop_fruit(Plant plant, Coord coord, uint16_t amount);
};

