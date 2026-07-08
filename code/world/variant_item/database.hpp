#pragma once

#include <world/item/database.hpp>

struct VariantItemDatabase {
		// @codegen:begin database_generation
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
    size_t size;
    Stack<size_t> freeSlots;
    Array<bool> alives;
  World& world;
  TileDatabase& tiles;

    // =========================
    // ENTITY-SPECIFIC MEMBERS
    // =========================
    Array<Item> items;
    Array<Coord> coords;
    Array<Variant> variants;
    

// =========================
    // CONSTRUCTOR
    // =========================

VariantItemDatabase(Arena *arena, size_t capacity
  , World& world
 
  , TileDatabase& tiles
) :
  world(world),
  tiles(tiles),
{
this->capacity = capacity;
  this->size = 0;

}

  // =========================
  // SPAWN
  // =========================

 
  bool attemptSpawn(Item item, bool newborn, Coord coord,  Variant variant )
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
            variants[i] = variant;
        }
        else
        {
        Time age = random_bool->next();
            items[i] = item;
            coords[i] = coord;
            variants[i] = variant;
        }
        return true;
          }
          bool spawn(Item item, bool newborn, Coord origin) {
          Coord spawnPoint = tiles.getNearestEmptyTile(origin);
          while (!attemptSpawn(item, newborn, spawnPoint)) freeUnusedEntity();                 
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
        return true;
  }

  void freeUnusedEntity()
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
        variants.save(archive);
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
        variants.load(archive);
    }


// =========================
// TRANSFER
// =========================

inline bool transferVariantItem(size_t i, VariantItemDatabase &oldDB, VariantItemDatabase &newDB)
  {
  if (newDB.size >= newDB.capacity) return false;
  int index;  
  if (newDB.freeSlots.empty())
  {
  index = ++size;
	}
	else
	{
		index = newDB.freeSlots.top();
		newDB.freeSlots.pop();			
  }
    newDB.items[index] = oldDB.items[i];
    newDB.coords[index] = oldDB.coords[i];
    newDB.variants[index] = oldDB.variants[i];
  newDB.alives[index] = true;
  oldDB.freeSlots.push(i);
  oldDB.alives[index] = false;
  return true;
  }
// @codegen:end database_generation
};
