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
    Stack<size_t> freeSlots;
    Array<bool> alives;
  SearchGrid& search;
  World& world;
  TileDatabase& tiles;

    // =========================
    // ENTITY-SPECIFIC MEMBERS
    // =========================
    Array<Vehicle> vehicles;
    Array<Health> healths;
    Array<FrameData> frameDatas;
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

 
  bool attemptSpawn(Vehicle vehicle, bool newborn, Coord coord, )
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
            vehicles[i] = vehicle;
            healths[i] = vehicle::maxHealths[vehicle] * INFANT_HEALTH_MODIFIER;
            frameDatas[i] = FrameData{ActState::NewPath, Direction::South, Frame::F0};
            coords[i] = coord;
        }
        else
        {
        Time age = random_bool->next();
            vehicles[i] = vehicle;
            healths[i] = getMaxHealth(vehicle, age);
            frameDatas[i] = FrameData{ActState::NewPath, Direction::South, Frame::F0};
            coords[i] = coord;
        }
        return true;
          }
          bool spawn(Vehicle vehicle, bool newborn, Coord origin) {
          Coord spawnPoint = tiles.getNearestEmptyTile(origin);
          while (!attemptSpawn(vehicle, newborn, spawnPoint)) freeUnusedEntity();                 
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
  // MOVE
  // =========================
  
    inline bool attemptMoveEntity(size_t index)
    {
        Coord& pos = coords[index];
        Coord newPos = getPos(frameDatas[index].get<Direction>(), pos);
        size_t ti = world.getTileIndexFromCoord(newPos);

        if (search.tiles.tileStatuses.get<OccupiedStatus>()[ti] == false)
        {
            pos = newPos;
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
        archive(freeSlots);
        archive(alives);
   

        vehicles.save(archive);
        healths.save(archive);
        frameDatas.save(archive);
        coords.save(archive);
    }

    template <class Archive>
    void load(Archive &archive)
    {
        archive(capacity);
        archive(size);
        archive(freeSlots);
        archive(alives);
        
        vehicles.load(archive);
        healths.load(archive);
        frameDatas.load(archive);
        coords.load(archive);
    }

// @codegen:end database_generation
};
