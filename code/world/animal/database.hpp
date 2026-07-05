#pragma once
#include "enum.hpp"
#include "defaults.hpp"
#include "macros/database.hpp"
#include <core/containers.hpp>
#include <core/data.hpp>
#include <core/random.hpp>
#include <cstdint>
#include <systems/find_nearest.hpp>
#include <world/world.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/archives/binary.hpp>
#include <cereal/types/stack.hpp>
#include <macros/constructors.h>

struct AnimalDatabase
{
public:
  //TODO: calculate entity size in templates

	// @codegen:begin database_generation
    // =========================
    // BASE DATABASE MEMBERS
    // =========================

constexpr static uint16_t ENTITY_SIZE = sizeof(Animal) +

+ sizeof(bool)
  

 +  sizeof(Health) 

 +  sizeof(Hunger) 

 +  sizeof(Sex) 

 +  sizeof(Time) 

 +  sizeof(size_t) 

 +  sizeof(TargetType) 

 +  sizeof(Action) 

 +  sizeof(FrameData) 

 +  sizeof(Coord) 

 +  sizeof(AnimalStatus) 

;

size_t capacity;
Array<Animal> animals;

    size_t size;
    Stack<size_t> freeSlots;
    Array<bool> alives;
  

  SearchGrid& search;


  World& world;


    // =========================
    // ENTITY-SPECIFIC MEMBERS
    // =========================

    Array<Health> healths;

    Array<Hunger> hungers;

    Array<Sex> sexes;

    Array<Time> ages;

    Array<size_t> targets;

    Array<TargetType> targetTypes;

    Array<Action> actions;

    Array<FrameData> frameDatas;

    Array<Coord> coords;

    Array<AnimalStatus> animalStatuses;
    


  // =========================
  // SPAWN
  // =========================
  
  bool spawn(Animal entity, bool newborn, Coord coord)
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
	  
            hungers[i] = maxHungers[{{ entity_name }}] * INFANT_HUNGER_MODIFIER;
	  
            sexes[i] = random_bool->next();
	  
            ages[i] = 0;
	  
            targets[i] = std::numeric_limits<size_t>::max();
	  
            targetTypes[i] = TargetType::NONE;
	  
            actions[i] = Action::NONE;
	  
            frameDatas[i] = FrameData{ActState::NONE, Direction::South, 0};
	  
            coords[i] = coord;
	  
            animalStatuses[i] = AnimalStatus{Direction::North, ActionStatus::Idle, MatingStatus::Idle};
	  
        }
        else
        {
        Time age = random_bool->next();
	  
            healths[i] = getMaxHealth(age);
	  
            hungers[i] = getMaxHunger(age);
	  
            sexes[i] = random_bool->next();
	  
            ages[i] = age;
	  
            targets[i] = std::numeric_limits<size_t>::max();
	  
            targetTypes[i] = TargetType::NONE;
	  
            actions[i] = Action::NONE;
	  
            frameDatas[i] = FrameData{ActState::NONE, Direction::South, 0};
	  
            coords[i] = coord;
	  
            animalStatuses[i] = AnimalStatus{Direction::North, ActionStatus::Idle, MatingStatus::Idle};
	  
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

        hungers.save(archive);

        sexes.save(archive);

        ages.save(archive);

        targets.save(archive);

        targetTypes.save(archive);

        actions.save(archive);

        frameDatas.save(archive);

        coords.save(archive);

        animalStatuses.save(archive);

    }

    template <class Archive>
    void load(Archive &archive)
    {
        archive(capacity);

        archive(size);
        archive(freeSlots);
        archive(alives);

        

        healths.load(archive);

        hungers.load(archive);

        sexes.load(archive);

        ages.load(archive);

        targets.load(archive);

        targetTypes.load(archive);

        actions.load(archive);

        frameDatas.load(archive);

        coords.load(archive);

        animalStatuses.load(archive);

    }

    // =========================
    // CONSTRUCTOR
    // =========================

AnimalDatabase(Arena *arena, size_t capacity

  , World& world


  , SearchGrid& search

)
    {
this->capacity = capacity;

  this->size = 0;
        
    }

// @codegen:end database_generation
  
  inline void addAnimals(AnimalSpawnBuffer asb);
  inline void move(size_t i);
  
};
