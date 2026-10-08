#pragma once
#include <core/coord.hpp>
#include <core/containers.hpp>
#include <data/run/world.hpp>
#include <data/run/tile_database.hpp>
#include <data/const/buildable_data.hpp>
#include <stack>

namespace buildable {
class Database
{
  	// @codegen:begin database_generation
public:
// =========================
// BASE DATABASE MEMBERS
// =========================

constexpr static uint16_t ENTITY_SIZE = sizeof(Buildable) +
+ sizeof(bool)
  
 +  sizeof(Buildable) 
 +  sizeof(Health) 
 +  sizeof(Coord) 
;

size_t capacity;
    size_t size = 1; // 0 is placeholder
    std::stack<size_t> free_slots;
    Array<bool> alives;
  tile::Database* tiles;

    // =========================
    // ENTITY-SPECIFIC MEMBERS
    // =========================
    Array<Buildable> buildables;
    Array<Health> healths;
    Array<Coord> coords;



// =========================
// INIT
// =========================

  void init(Arena* arena, size_t capacity
  , tile::Database& tiles
) 
{
this->capacity = capacity;
  this->size = 0;
  this->tiles = &tiles;
 
  buildables = arena_make_array<Buildable>(arena, capacity);
 
  healths = arena_make_array<Health>(arena, capacity);
 
  coords = arena_make_array<Coord>(arena, capacity);
 

}
    // =========================
    // SERIALIZATION
    // =========================

      template <class Archive>
    void serialize(Archive &archive) const
{
        archive(tiles);
        archive(size);
        archive(free_slots);
        archive(alives);

           buildables.serialize(archive);
           healths.serialize(archive);
           coords.serialize(archive);
         
    }
         

// =========================
// GETTERS
// =========================

  inline Buildable& buildable(const EntityID index) {
return buildables[index];
  }
  inline Health& health(const EntityID index) {
return healths[index];
  }
  inline Coord& coord(const EntityID index) {
return coords[index];
  }


  
// =========================
// GENERATION
// =========================


  // =========================
  // SPAWN
  // =========================

bool attempt_spawn(const Buildable buildable, const Coord coord, const bool newborn  )
{
#if !SHIPPING_BUILD
assert(buildable != Buildable::NONE && buildable != Buildable::MAX && "Tried to spawn buildable as NONE or MAX.");
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
            this->buildable(i) = buildable;
            this->health(i) = buildable::MAX_HEALTHS[buildable] * INFANT_HEALTH_MODIFIER;
            this->coord(i) = coord;
        }
        else
        {
        Time age = random_bool->next();
            this->buildable(i) = buildable;
            this->health(i) = buildable::get_max_health(buildable, age);
            this->coord(i) = coord;
        }
        return i;
          }
          
        

          bool spawn(const Buildable buildable, const Coord origin, const bool newborn
, const bool insert_search = true) {
Coord spawn_point = tiles->get_nearest_empty_tile(origin);
bool result = false;
result = attempt_spawn(buildable, spawn_point, newborn
);
if (!result) {
free_unused_entity();
attempt_spawn(buildable, spawn_point, newborn
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
        return true;
  }

  inline void free_unused_entity()
  {
    for (size_t i = 0; i < coords.capacity; i++) {
    if (tiles->tile_status(i).get<VisionStatus>() == VisionStatus::Hidden) remove(i);
    }
  }
    


// @codegen:end database_generation
};

}
