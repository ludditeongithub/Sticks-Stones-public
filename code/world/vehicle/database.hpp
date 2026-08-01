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

  TileDatabase& tiles;

    // =========================
    // ENTITY-SPECIFIC MEMBERS
    // =========================
    Array<Vehicle> vehicles;
    Array<Health> healths;
    Array<FrameData> frameDatas;
    Array<Frame> inertias;
    Array<Coord> coords;



// =========================
// CONSTRUCTOR
// =========================

Database(Arena *arena, size_t capacity
  , World& world
 
  , TileDatabase& tiles
) :
  world(world),
  tiles(tiles),
{
this->capacity = capacity;
  no_inertia_list.reserve(capacity);

  this->size = 0;

}

// =========================
// GETTERS
// =========================

  inline Vehicle& vehicles(size_t index) {
return vehicless[index];
  }
  inline Health& healths(size_t index) {
return healthss[index];
  }
  inline FrameData& frameDatas(size_t index) {
return frameDatass[index];
  }
  inline Frame& inertias(size_t index) {
return inertiass[index];
  }
  inline Coord& coords(size_t index) {
return coordss[index];
  }


  // =========================
  // SPAWN
  // =========================


// returns 0 if failed
  size_t attempt_spawn(Vehicle vehicle, bool newborn, Coord coord  )
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
            healths(i) = vehicle::maxHealths[vehicle] * INFANT_HEALTH_MODIFIER;
            frameDatas(i) = FrameData{ActState::NewPath, Direction::South, Frame::F0};
            inertias(i) = 0;
            coords(i) = coord;
        }
        else
        {
        Time age = random_bool->next();
            vehicles(i) = vehicle;
            healths(i) = getMaxHealth(vehicle, age);
            frameDatas(i) = FrameData{ActState::NewPath, Direction::South, Frame::F0};
            inertias(i) = 0;
            coords(i) = coord;
        }
        return i;
          }
          
          size_t spawn(Vehicle vehicle, bool newborn, Coord origin
bool insert_search = true) {
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
  
  inline bool remove(size_t i)
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
    if (tiles.tile_statuses[i].get<VisionStatus>() == VisionStatus::Hidden) remove(i);
    }
  }
    

  // =========================
  // MOVE
  // =========================
  
    inline bool attempt_move_entity(size_t index)
    {
        Coord& pos = coords[index];
        Coord new_pos = get_pos(frame_datas[index].get<Direction>(), pos);
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

    template <class Archive>
    void save(Archive &archive) const
    {
    archive(capacity);
        archive(size);
        archive(free_slots);
        archive(alives);
   

        vehicles.save(archive);
        healths.save(archive);
        frameDatas.save(archive);
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
        frameDatas.load(archive);
        inertias.load(archive);
        coords.load(archive);
    }

// @codegen:end database_generation
};

}
