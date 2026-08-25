#pragma once
namespace vehicle {
struct Database {
  	// @codegen:begin database_generation
// =========================
// BASE DATABASE MEMBERS
// =========================

constexpr static uint16_t entity_size = sizeof(Vehicle) +
+ sizeof(bool)
  
 +  sizeof(Vehicle) 
 +  sizeof(Health) 
 +  sizeof(FrameData) 
 +  sizeof(Frame) 
 +  sizeof(Coord) 
;

size_t capacity;
    size_t size = 1; // 0 is placeholder
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
    Array<Vehicle> vehicles;
    Array<Health> health;
    Array<FrameData> frame_data;
    Array<Frame> inertia;
    Array<Coord> coord;



// =========================
// CONSTRUCTOR
// =========================

Database(Arena *arena, size_t capacity
  , World& world
 
  , tile::Database& tiles
) :
  world(world),
  tiles(tiles),
{
this->capacity = capacity;
  no_inertia_list.reserve(capacity);

  this->size = 0;


 vehicles = arena_make_array<Vehicle>(capacity);
 health = arena_make_array<Health>(capacity);
 frame_data = arena_make_array<FrameData>(capacity);
 inertia = arena_make_array<Frame>(capacity);
 coord = arena_make_array<Coord>(capacity);

}

// =========================
// GETTERS
// =========================

  inline Vehicle& vehicles(const EntityID index) {
return vehicles[index];
  }
  inline Health& health(const EntityID index) {
return health[index];
  }
  inline FrameData& frame_data(const EntityID index) {
return frame_data[index];
  }
  inline Frame& inertia(const EntityID index) {
return inertia[index];
  }
  inline Coord& coord(const EntityID index) {
return coord[index];
  }


  
  // =========================
  // SPAWN
  // =========================


bool attempt_spawn(Vehicle vehicle, bool newborn, Coord coord  )
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
            vehicles(i) = vehicle;
            health(i) = vehicle::maxHealths[vehicle] * INFANT_HEALTH_MODIFIER;
            frame_data(i) = FrameData{ActState::NewPath, Direction::South, Frame::F0};
            inertia(i) = 0;
            coord(i) = coord;
        }
        else
        {
        Time age = random_bool->next();
            vehicles(i) = vehicle;
            health(i) = getMaxHealth(vehicle, age);
            frame_data(i) = FrameData{ActState::NewPath, Direction::South, Frame::F0};
            inertia(i) = 0;
            coord(i) = coord;
        }
        return i;
          }
          
        

size_t spawn(const Vehicle vehicle, const bool newborn, const Coord origin
const bool insert_search = true) {
Coord spawn_point = tiles.get_nearest_empty_tile(origin);
size_t result = 0;
while (result == 0) {
result = attempt_spawn(vehicle, newborn, spawn_point
, insert_search);
if (result == 0) free_unused_entity();
}
}        
    

  // =========================
  // REMOVE
  // =========================
  
  inline bool remove(const EntityID i)
  {
        if (!alive(i))
            return false;

        free_slots.push(i);
        alive(i) = false;
        return true;
  }

  inline void free_unused_entity()
  {
    for (size_t i = 0; i < coords.size; i++) {
    if (tiles.tile_status(i).get<VisionStatus>() == VisionStatus::Hidden) remove(i);
    }
  }
    

  // =========================
  // MOVE
  // =========================
  
    inline bool attempt_move_entity(const EntityID index)
  {
  #if !SHIPPING_BUILD
  assert(index < 
  #endif

        Coord& pos = coord(index);
        Coord new_pos = get_pos(frame_data(index).get<Direction>(), pos);
        size_t ti = world.get_tile_index_from_coord(new_pos);

        if (search.tiles.tile_statuses.get<OccupiedStatus>()[ti] == false)
        {
            pos = new_pos;
            return true;
        }

        return false;
    }

    // =========================
    // SERIALIZATION
    // =========================

  // genreal serialization

    template <class Archive>
    void save(Archive &archive) const
    {
    archive(capacity);
        archive(size);
        archive(free_slots);
        archive(alives);
   

        vehicles.save(archive);
        health.save(archive);
        frame_data.save(archive);
        inertia.save(archive);
        coord.save(archive);
    }

    template <class Archive>
    void load(Archive &archive)
    {
        archive(capacity);
        archive(size);
        archive(free_slots);
        archive(alives);
        
        vehicles.load(archive);
        health.load(archive);
        frame_data.load(archive);
        inertia.load(archive);
        coord.load(archive);
    }

// @codegen:end database_generation
};

}
