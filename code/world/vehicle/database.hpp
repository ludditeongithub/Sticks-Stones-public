#pragma once

struct VehicleDatabase {
  	// @codegen:begin database_generation
    // =========================
    // BASE DATABASE MEMBERS
    // =========================

constexpr static uint16_t ENTITY_SIZE = sizeof(bool)

 +  sizeof(Health) 

 +  sizeof(FrameData) 

 +  sizeof(Coord) 

;

size_t capacity;
Array<Vehicle> vehicles;

    size_t size;
    Stack<size_t> freeSlots;
    Array<bool> alives;
  

  SearchGrid& search;


  World& world;


    // =========================
    // ENTITY-SPECIFIC MEMBERS
    // =========================

    Array<Health> healths;

    Array<FrameData> frameDatas;

    Array<Coord> coords;
    


  // =========================
  // SPAWN
  // =========================
  
  bool spawn(Vehicle entity, bool newborn, Coord coord)
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
      
            healths[i] = maxHealths[{{ entity_name }}] * INFANT_HEALTH_MODIFIER;
	  
            frameDatas[i] = FrameData{ActState::NONE, Direction::South, 0};
	  
            coords[i] = coord;
	  
        }
        else
        {
        Time age = random_bool->next();
	  
            healths[i] = getMaxHealth(age);
	  
            frameDatas[i] = FrameData{ActState::NONE, Direction::South, 0};
	  
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

        search.deleteEntity;

        return true;
    }
    


  // =========================
  // MOVE
  // =========================
  
    inline bool attemptMoveEntity(size_t index)
    {
        Coord& pos = coords[index];
        Coord newPos = getPos(directions[index], pos);
        size_t ti = world.getTileIndexFromCoord(newPos);

        if (search.tiles.occupieds[ti] == false)
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

        

        healths.load(archive);

        frameDatas.load(archive);

        coords.load(archive);

    }

    // =========================
    // CONSTRUCTOR
    // =========================

VehicleDatabase(Arena *arena, size_t capacity

  , World& world


)
    {
this->capacity = capacity;

  this->size = 0;
        
    }

// @codegen:end database_generation

};
