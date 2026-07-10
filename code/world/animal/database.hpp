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
		std::vector<size_t> fertilized_egg_layers;
		std::vector<bool> valid;
		std::queue<size_t> free_indices;
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
		EggFertilizationHandler fertilization_handler;
	
	// @codegen:begin database_generation
    // =========================
    // BASE DATABASE MEMBERS
    // =========================

constexpr static uint16_t entity_size = sizeof(Animal) +
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
    Stack<size_t> free_slots;
    Array<bool> alives;
  SearchGrid& search;
  World& world;
  TileDatabase& tiles;
  VariantItemDatabase& variant_items;

    // =========================
    // ENTITY-SPECIFIC MEMBERS
    // =========================
    Array<Animal> animals;
    Array<Health> healths;
    Array<Hunger> hungers;
    Array<Sex> sexes;
    Array<Time> ages;
    Array<size_t> targets;
    Array<TargetType> target_types;
    Array<Action> actions;
    Array<FrameData> frame_datas;
    Array<Coord> coords;
    Array<AnimalStatus> animal_statuses;
    

// =========================
    // CONSTRUCTOR
    // =========================

AnimalDatabase(Arena *arena, size_t capacity
  , World& world 
  , SearchGrid& search
  , TileDatabase& tiles
  , VariantItemDatabase& variant_items
) :
  world(world),
  tiles(tiles),
search(search)
{
this->capacity = capacity;
  this->size = 0;
  this->variant_items = variant_items;
  fertilizationHandler = EggFertilizationHandler(capacity / 20);  

}

  // =========================
  // SPAWN
  // =========================

  void add_animals(WorldSpawner::AnimalSpawnBuffer& spawn_buffer)
{
	for (size_t i = 0; i < spawn_buffer.size; i++)
	  if (spawn(spawn_buffer.animals[i], spawn_buffer.coords[i], false)) {}
	  else
	    {
	      //TODO: error
	    }
}
 
  bool attempt_spawn(Animal animal, bool newborn, Coord coord )
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
          Coord spawn_point = tiles.get_nearest_empty_tile(origin);
          while (!attempt_spawn(animal, newborn, spawn_point)) free_unused_entity();                 
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

  void free_unused_entity()
  {
    for (size_t i = 0; i < coords.size; i++) {
    if (tiles.tileStatuses[i].get<VisionStatus>() == VisionStatus::Hidden) remove(i);
    }
  }
    

  // =========================
  // MOVE
  // =========================
  
    inline bool attempt_move_entity(size_t index)
    {
        Coord& pos = coords[index];
        Coord new_pos = getPos(frameDatas[index].get<Direction>(), pos);
        size_t ti = world.get_tile_index_from_coord(new_pos);

        if (search.tiles.tileStatuses.get<OccupiedStatus>()[ti] == false)
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

inline bool transfer_animal(size_t i, AnimalDatabase &old_db, AnimalDatabase &new_db)
  {
  if (new_db.size >= new_db.capacity) return false;
  int index;  
  if (new_db.freeSlots.empty())
  {
  index = ++size;
	}
	else
	{
		index = new_db.freeSlots.top();
		new_db.freeSlots.pop();			
  }
    new_db.animals[index] = old_db.animals[i];
    new_db.healths[index] = old_db.healths[i];
    new_db.hungers[index] = old_db.hungers[i];
    new_db.sexes[index] = old_db.sexes[i];
    new_db.ages[index] = old_db.ages[i];
    new_db.targets[index] = old_db.targets[i];
    new_db.targetTypes[index] = old_db.targetTypes[i];
    new_db.actions[index] = old_db.actions[i];
    new_db.frameDatas[index] = old_db.frameDatas[i];
    new_db.coords[index] = old_db.coords[i];
    new_db.animalStatuses[index] = old_db.animalStatuses[i];
  new_db.alives[index] = true;
  old_db.freeSlots.push(i);
  old_db.alives[index] = false;
  return true;
  }
// @codegen:end database_generation

  // =========================
		// REPRODUCTION
		// =========================

		void birth_animal(Animal animal, size_t mother_index);
		void breed(Animal animal, size_t female_index, size_t male_index);
        void set_track_mate_path(Animal animal, size_t index);
		inline bool get_conception_roll(Animal animal, size_t female_index, size_t male_index);
				
  inline void handle_event(Event& event);
		inline void move(size_t i);
		
		void make_corpse(const size_t index);
		void kill_animal(const size_t index);
		void lay_egg(Animal animal, Coord coord, bool fertilized);
};
