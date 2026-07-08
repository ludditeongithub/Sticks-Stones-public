#pragma once
#include "enum.hpp"
#include "data.hpp"
#include "macros/database.hpp"
#include <core/containers.hpp>
#include <core/data.hpp>
#include <core/random.hpp>
#include <cstdint>
#include <systems/find_nearest.hpp>
#include <world/world.hpp>
#include <world/variant_item/database.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/archives/binary.hpp>
#include <cereal/types/stack.hpp>
#include <macros/constructors.h>
#include <schedule/event.hpp>
#include <queue>


struct AnimalDatabase
{
public:
struct EggFertilizationHandler {
		std::vector<size_t> fertilizedEggLayers;
		std::vector<bool> valid;
		std::queue<size_t> freeIndices;
		void push_back(size_t index)
		{
			if (freeIndices.empty())
					{
				fertilizedEggLayers.push_back(index);
				valid.push_back(true);
					}
					else
							{
									size_t slot = freeIndices.front();
									freeIndices.pop();
									fertilizedEggLayers[slot] =
											index;
									valid[slot] = true;
							}

		}
		void remove(size_t index)
		{
				valid[index] = false;
				freeIndices.push(index);
		}
		EggFertilizationHandler(size_t size)
		{
				fertilizedEggLayers.reserve(size);
				valid.reserve(size);				
		}
};
		EggFertilizationHandler fertilizationHandler;
	
	// @codegen:begin database_generation
    // =========================
    // BASE DATABASE MEMBERS
    // =========================

constexpr static uint16_t ENTITY_SIZE = sizeof(Animal) +
+ sizeof(bool)
  
 +  sizeof(Animal) 
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
    size_t size;
    Stack<size_t> freeSlots;
    Array<bool> alives;
  SearchGrid& search;
  World& world;
  TileDatabase& tiles;
  VariantItemDatabase& variantItems;

    // =========================
    // ENTITY-SPECIFIC MEMBERS
    // =========================
    Array<Animal> animals;
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
    // CONSTRUCTOR
    // =========================

AnimalDatabase(Arena *arena, size_t capacity
  , World& world 
  , SearchGrid& search
  , TileDatabase& tiles
  , VariantItemDatabase& variantItems
) :
  world(world),
  tiles(tiles),
search(search),
{
this->capacity = capacity;
  this->size = 0;
  this->variantItems = variantItems;
  fertilizationHandler = EggFertilizationHandler(capacity / 20);  

}

  // =========================
  // SPAWN
  // =========================

  void addAnimals(WorldSpawner::AnimalSpawnBuffer& spawnBuffer)
{
	for (size_t i = 0; i < spawnBuffer.size; i++)
	  if (spawn(spawnBuffer.animals[i], spawnBuffer.coords[i], false)) {}
	  else
	    {
	      //TODO: error
	    }
}
 
  bool attemptSpawn(Animal animal, bool newborn, Coord coord, )
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
            animals[i] = animal;
            healths[i] = animal::maxHealths[animal] * INFANT_HEALTH_MODIFIER;
            hungers[i] = animal::maxHungers[animal] * INFANT_HUNGER_MODIFIER;
            sexes[i] = random_bool->next();
            ages[i] = 0;
            targets[i] = std::numeric_limits<size_t>::max();
            targetTypes[i] = TargetType::NONE;
            actions[i] = Action::NONE;
            frameDatas[i] = FrameData{ActState::NewPath, Direction::South, Frame::F0};
            coords[i] = coord;
            animalStatuses[i] = AnimalStatus{Direction::North, ActionStatus::Idle, MatingStatus::Idle};
        }
        else
        {
        Time age = random_bool->next();
            animals[i] = animal;
            healths[i] = getMaxHealth(animal, age);
            hungers[i] = getMaxHunger(animal, age);
            sexes[i] = random_bool->next();
            ages[i] = age;
            targets[i] = std::numeric_limits<size_t>::max();
            targetTypes[i] = TargetType::NONE;
            actions[i] = Action::NONE;
            frameDatas[i] = FrameData{ActState::NewPath, Direction::South, Frame::F0};
            coords[i] = coord;
            animalStatuses[i] = AnimalStatus{Direction::North, ActionStatus::Idle, MatingStatus::Idle};
        }
            search.insertEntity(animal, {i, coords[i]});
        return true;
          }
          bool spawn(Animal animal, bool newborn, Coord origin) {
          Coord spawnPoint = tiles.getNearestEmptyTile(origin);
          while (!attemptSpawn(animal, newborn, spawnPoint)) freeUnusedEntity();                 
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
        Animal animal = animals[i];
            search.removeEntity(animal, {i, coords[i]});
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
   

        animals.save(archive);
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
        
        animals.load(archive);
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
// TRANSFER
// =========================

inline bool transferAnimal(size_t i, AnimalDatabase &oldDB, AnimalDatabase &newDB)
  {
  if (newDB.size >= newDB.capacity) return false;
  int index;  
  if (newDB.freeSlots.empty())
  {
  index = ++size;
	}
	else
	{
		index = newDB.freeSlots.top();
		newDB.freeSlots.pop();			
  }
    newDB.animals[index] = oldDB.animals[i];
    newDB.healths[index] = oldDB.healths[i];
    newDB.hungers[index] = oldDB.hungers[i];
    newDB.sexes[index] = oldDB.sexes[i];
    newDB.ages[index] = oldDB.ages[i];
    newDB.targets[index] = oldDB.targets[i];
    newDB.targetTypes[index] = oldDB.targetTypes[i];
    newDB.actions[index] = oldDB.actions[i];
    newDB.frameDatas[index] = oldDB.frameDatas[i];
    newDB.coords[index] = oldDB.coords[i];
    newDB.animalStatuses[index] = oldDB.animalStatuses[i];
  newDB.alives[index] = true;
  oldDB.freeSlots.push(i);
  oldDB.alives[index] = false;
  return true;
  }
// @codegen:end database_generation

  // =========================
		// REPRODUCTION
		// =========================

		void birthAnimal(Animal animal, size_t motherIndex);
		void breed(Animal animal, size_t femaleIndex, size_t maleIndex);
        void setTrackMatePath(Animal animal, size_t index);
		inline bool getConceptionRoll(Animal animal, size_t femaleIndex, size_t maleIndex);
				
  inline void handleEvent(Event& event);
		inline void move(size_t i);
		
		void makeCorpse(const size_t index);
		void killAnimal(const size_t index);
		void layEgg(Animal animal, Coord coord, bool fertilized);
};
