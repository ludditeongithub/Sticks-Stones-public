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
  
  std::vector<EntityID>& no_inertia_buffer; // size is amount of no inertias this loop
  
  std::vector<EntityID>& unassigned_buffer; // size is amount of unassigned this loop
  World& world;
  tile::Database& tiles;

    // =========================
    // ENTITY-SPECIFIC MEMBERS
    // =========================
    Array<Vehicle> vehicles;
    Array<Health> healths;
    Array<FrameData> frame_datas;
    Array<Frame> inertias;
    Array<Coord> coords;



// =========================
// CONSTRUCTOR
// =========================

Database(Arena& arena, size_t capacity
  , World& world
 
  , tile::Database& tiles
) :
  world(world),
  tiles(tiles),
{
this->capacity = capacity;
  no_inertia_buffer.reserve(capacity);

  this->size = 0;


 
 vehicles = arena_make_array<Vehicle>(arena, capacity); 
 
 healths = arena_make_array<Health>(arena, capacity); 
 
 frame_datas = arena_make_array<FrameData>(arena, capacity); 
 
 inertias = arena_make_array<Frame>(arena, capacity); 
 
 coords = arena_make_array<Coord>(arena, capacity); 
 

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
  // SPAWN
  // =========================


bool attempt_spawn(const Vehicle vehicle, const bool newborn, const Coord coord  )
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
            this->health(i) = get_max_health(vehicle, age);
            this->frame_data(i) = FrameData{ActState::NewPath, Direction::South, 0};
            this->inertia(i) = 0;
            this->coord(i) = coord;
        }
        return i;
          }
          
        

size_t spawn(const Vehicle vehicle, const bool newborn, const Coord origin
, const bool insert_search = true) {
Coord spawn_point = tiles.get_nearest_empty_tile(origin);
size_t result = 0;
while (result == 0) {
result = attempt_spawn(vehicle, newborn, spawn_point
);
if (result == 0) free_unused_entity();
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
  assert(index <= size);
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
        healths.save(archive);
        frame_datas.save(archive);
        inertias.save(archive);
        coords.save(archive);
    }

    template <class Archive>
    void load(Archive &archive)
    {
        archive(capacity);
        archive(size);
        archive(free_slots);
        archive(alives);
        
        vehicles.load(archive);
        healths.load(archive);
        frame_datas.load(archive);
        inertias.load(archive);
        coords.load(archive);
    }

// @codegen:end database_generation
};

}
