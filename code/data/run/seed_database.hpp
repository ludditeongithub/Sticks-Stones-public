#pragma once
#include <vector>

namespace seed {
class Database {
	// @codegen:begin database_generation
public:
// =========================
// BASE DATABASE MEMBERS
// =========================

constexpr static uint16_t ENTITY_SIZE = sizeof(Plant) +
+ sizeof(bool)!
  
 +  sizeof(Plant) 
 +  sizeof(Coord) 
 +  sizeof(Time) 
;

size_t capacity;
    size_t size = 1; // 0 is placeholder
    std::stack<size_t> free_slots;
    Array<bool> alives;
  tile::Database& tiles;

    // =========================
    // ENTITY-SPECIFIC MEMBERS
    // =========================
    Array<Plant> plants;
    Array<Coord> coords;
    Array<Time> ages;



// =========================
// CONSTRUCTOR
// =========================

  Database(Arena* arena, size_t capacity
  , tile::Database& tiles
) 
    : tiles(tiles)
  
{
this->capacity = capacity;

  this->size = 0;


 
  plants = arena_make_array<Plant>(arena, capacity);
 
  coords = arena_make_array<Coord>(arena, capacity);
 
  ages = arena_make_array<Time>(arena, capacity);
 

}
    // =========================
    // SERIALIZATION
    // =========================

      template <class Archive>
    void serialize(Archive &archive) const
  {
         archive(tiles,
size,
free_slots,
alives,
plants,
coords,
ages);
    }


// =========================
// GETTERS
// =========================

  inline Plant& plant(const EntityID index) {
return plants[index];
  }
  inline Coord& coord(const EntityID index) {
return coords[index];
  }
  inline Time& age(const EntityID index) {
return ages[index];
  }


  
  // =========================
  // SPAWN
  // =========================


bool attempt_spawn(const Plant plant, const Coord coord, const bool newborn  )
{
#if !SHIPPING_BUILD
assert(plant != Plant::NONE && plant != Plant::MAX && "Tried to spawn plant as NONE or MAX.");
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
            this->plant(i) = plant;
            this->coord(i) = coord;
            this->age(i) = 0;
        }
        else
        {
        Time age = random_bool->next();
            this->plant(i) = plant;
            this->coord(i) = coord;
            this->age(i) = age;
        }
        return i;
          }
          
        

          bool spawn(const Plant plant, const Coord origin, const bool newborn
, const bool insert_search = true) {
Coord spawn_point = tiles.get_nearest_empty_tile(origin);
bool result = false;
result = attempt_spawn(plant, spawn_point, newborn
);
if (!result) {
free_unused_entity();
attempt_spawn(plant, spawn_point, newborn
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
        return true;
  }

  inline void free_unused_entity()
  {
    for (size_t i = 0; i < coords.size(); i++) {
    if (tiles.tile_status(i).get<VisionStatus>() == VisionStatus::Hidden) remove(i);
    }
  }
    


// @codegen:end database_generation
};

}
