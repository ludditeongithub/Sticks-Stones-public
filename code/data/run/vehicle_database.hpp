#pragma once
#include <cstdint>
#include <vector>
#include <core/containers.hpp>
#include <logic/generic/search/search.hpp>


namespace vehicle {
class Database {
  	// @codegen:begin database_generation
public:
// =========================
// BASE DATABASE MEMBERS
// =========================

constexpr static uint16_t ENTITY_SIZE = sizeof(Vehicle) +
+ sizeof(bool)
  
 +  sizeof(Vehicle) 
 +  sizeof(Health) 
 +  sizeof(FrameData) 
 +  sizeof(Frame) 
 +  sizeof(Coord) 
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
    Array<Vehicle> vehicles;
    Array<Health> healths;
    Array<FrameData> frame_datas;
    Array<Frame> inertias;
    Array<Coord> coords;



// =========================
// INIT
// =========================

  void init(Arena* arena, size_t capacity
  , tile::Database& tiles
) 
{
this->capacity = capacity;
  no_inertia_buffer = arena_make_array<EntityID>(arena, capacity);
  unassigned_buffer = arena_make_array<EntityID>(arena, capacity);
  this->size = 0;
  this->tiles = &tiles;
 
  vehicles = arena_make_array<Vehicle>(arena, capacity);
 
  healths = arena_make_array<Health>(arena, capacity);
 
  frame_datas = arena_make_array<FrameData>(arena, capacity);
 
  inertias = arena_make_array<Frame>(arena, capacity);
 
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

           vehicles.serialize(archive);
           healths.serialize(archive);
           frame_datas.serialize(archive);
           inertias.serialize(archive);
           coords.serialize(archive);
         
    }
         

// =========================
// GETTERS
// =========================

  inline Vehicle& vehicle(const EntityID index) {
return vehicles[index];
  }
  inline Health& health(const EntityID index) {
return healths[index];
  }
  inline FrameData& frame_data(const EntityID index) {
return frame_datas[index];
  }
  inline Frame& inertia(const EntityID index) {
return inertias[index];
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

bool attempt_spawn(const Vehicle vehicle, const Coord coord, const bool newborn  )
{
#if !SHIPPING_BUILD
assert(vehicle != Vehicle::NONE && vehicle != Vehicle::MAX && "Tried to spawn vehicle as NONE or MAX.");
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
            this->vehicle(i) = vehicle;
            this->health(i) = vehicle::MAX_HEALTHS[vehicle] * INFANT_HEALTH_MODIFIER;
            this->frame_data(i) = FrameData{ActState::NewPath, Direction::South, 0};
            this->inertia(i) = 0;
            this->coord(i) = coord;
        }
        else
        {
        Time age = random_bool->next();
            this->vehicle(i) = vehicle;
            this->health(i) = vehicle::get_max_health(vehicle, age);
            this->frame_data(i) = FrameData{ActState::NewPath, Direction::South, 0};
            this->inertia(i) = 0;
            this->coord(i) = coord;
        }
        return i;
          }
          
        

          bool spawn(const Vehicle vehicle, const Coord origin, const bool newborn
, const bool insert_search = true) {
Coord spawn_point = tiles->get_nearest_empty_tile(origin);
bool result = false;
result = attempt_spawn(vehicle, spawn_point, newborn
);
if (!result) {
free_unused_entity();
attempt_spawn(vehicle, spawn_point, newborn
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
    

  // =========================
  // MOVE
  // =========================
  
    inline bool attempt_move_entity(const EntityID index)
  {
  assert(index <= size);

        Coord& pos = coord(index);
        Coord new_pos = get_pos(frame_data(index).get<Direction>(), pos);
        size_t ti = g_world->get_tile_index_from_coord(new_pos);

    if (tiles->tile_statuss[ti].get<OccupiedStatus>() == OccupiedStatus::Vacant)
        {
            pos = new_pos;
            return true;
        }

        return false;
    }

// @codegen:end database_generation
};

}
