#pragma once

struct VehicleDatabase {
  	// @codegen:begin database_generation
    // =========================
    // BASE DATABASE MEMBERS
    // =========================

constexpr static uint16_t ENTITY_SIZE = sizeof(Vehicle) +
+ sizeof(bool)
  
 +  sizeof(Vehicle) 
 +  sizeof(Health) 
 +  sizeof(FrameData) 
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
    Array<Vehicle> vehicles;
    Array<Health> healths;
    Array<FrameData> frame_datas;
    Array<Coord> coords;
    

// =========================
    // CONSTRUCTOR
    // =========================

VehicleDatabase(Arena *arena, size_t capacity
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

 
  bool attempt_spawn(Vehicle vehicle, bool newborn, Coord coord, )
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
            vehicles[i] = vehicle;
            healths[i] = vehicle::max_healths[vehicle] * INFANT_HEALTH_MODIFIER;
            frame_datas[i] = FrameData{ActState::NewPath, Direction::South, Frame::F0};
            coords[i] = coord;
        }
        else
        {
        Time age = random_bool->next();
            vehicles[i] = vehicle;
            healths[i] = get_max_health(vehicle, age);
            frame_datas[i] = FrameData{ActState::NewPath, Direction::South, Frame::F0};
            coords[i] = coord;
        }
        return true;
          }
          bool spawn(Vehicle vehicle, bool newborn, Coord origin) {
          Coord spawn_point = tiles.get_nearest_empty_tile(origin);
          while (!attempt_spawn(vehicle, newborn, spawn_point)) free_unused_entity();                 
          }        
    

  // =========================
  // REMOVE
  // =========================
  
  bool remove(size_t i)
  {
        if (!alives[i])
            return false;

        free_slots.push(i);
        alives[i] = false;
        return true;
  }

  void free_unused_entity()
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
        frame_datas.save(archive);
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
        coords.load(archive);
    }

// @codegen:end database_generation
};
