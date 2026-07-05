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

  // @codegen:begin database_generation
    // =========================
    // BASE DATABASE MEMBERS
    // =========================

constexpr static uint16_t ENTITY_SIZE = sizeof(Item) +

+ sizeof(bool)
  

 +  sizeof(Coord) 

;

size_t capacity;
Array<Item> items;

    size_t size;
    Stack<size_t> freeSlots;
    Array<bool> alives;
  

  SearchGrid& search;



    // =========================
    // ENTITY-SPECIFIC MEMBERS
    // =========================

    Array<Coord> coords;
    


  // =========================
  // SPAWN
  // =========================
  
  bool spawn(Item entity, bool newborn, Coord coord)
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
      
            coords[i] = coord;
	  
        }
        else
        {
        Time age = random_bool->next();
	  
            coords[i] = coord;
	  
        }
	  
  
          

        return true;
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

        search.deleteEntity();

        return true;
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
   


        coords.save(archive);

    }

    template <class Archive>
    void load(Archive &archive)
    {
        archive(capacity);

        archive(size);
        archive(freeSlots);
        archive(alives);

        

        coords.load(archive);

    }

    // =========================
    // CONSTRUCTOR
    // =========================

ItemDatabase(Arena *arena, size_t capacity

  , World& world


  , SearchGrid& search

)
    {
this->capacity = capacity;

  this->size = 0;
        
    }

// @codegen:end database_generation
  
	inline void addItem(Item item, Coord coord);
	inline void dropFruit(Plant plant, Coord coord, uint16_t amount);
};

struct VariantItemDatabase : ItemDatabase {
	 Array<uint8_t> variants;
};


