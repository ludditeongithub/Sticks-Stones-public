#pragma once
#include "enum.hpp"
#include "data.hpp"
#include "macros/database.hpp"
#include "systems/action/action.hpp"
#include <core/containers.hpp>
#include <core/data.hpp>
#include <core/random.hpp>
#include <cstdint>

#include <world/world.hpp>
#include <world/variant_item/database.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/archives/binary.hpp>
#include <cereal/types/stack.hpp>
#include <macros/constructors.h>
#include <schedule/event.hpp>
#include <queue>

namespace animal {
struct Database
{
public:
struct EggFertilizationHandler {
		std::vector<size_t> fertilized_egg_layers;
		std::vector<bool> valid;
		std::queue<size_t> free_indices;
		void push_back(size_t index)
		{
			if (free_indices.empty())
					{
				fertilized_egg_layers.push_back(index);
				valid.push_back(true);
					}
					else
							{
									size_t slot = free_indices.front();
									free_indices.pop();
									fertilized_egg_layers[slot] =
											index;
									valid[slot] = true;
							}

		}
		void remove(size_t index)
		{
				valid[index] = false;
				free_indices.push(index);
		}
		EggFertilizationHandler(size_t size)
		{
				fertilized_egg_layers.reserve(size);
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
    Array<FrameData> frameDatas;
    Array<Frame> inertias;
    Array<Coord> coords;

    struct main {
    
    
    }
    struct target {
    
    
    }


// =========================
// CONSTRUCTOR
// =========================

Database(Arena *arena, size_t capacity
  , World& world
 
  , SearchGrid& search
  , TileDatabase& tiles
  , VariantItemDatabase& variant_items
) :
  world(world),
  tiles(tiles),
search(search),
{
this->capacity = capacity;
  no_inertia_list.reserve(capacity);

  this->size = 0;
  this->variant_items = variant_items;
  fertilization_handler = EggFertilizationHandler(capacity / 20);  

}

// =========================
// GETTERS
// =========================

  inline Animal& animals(size_t index) {
return animalss[index];
  }
  inline Health& healths(size_t index) {
return healthss[index];
  }
  inline Hunger& hungers(size_t index) {
return hungerss[index];
  }
  inline Sex& sexes(size_t index) {
return sexess[index];
  }
  inline Time& ages(size_t index) {
return agess[index];
  }
  inline size_t& targets(size_t index) {
return targetss[index];
  }
  inline TargetType& target_types(size_t index) {
return target_typess[index];
  }
  inline Action& actions(size_t index) {
return actionss[index];
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

    inline Health& healths(size_t index) {    
return main[index].healths;
    }
    inline Sex& sexes(size_t index) {    
return main[index].sexes;
    }
    inline Time& ages(size_t index) {    
return main[index].ages;
    }
    inline size_t& targets(size_t index) {    
return target[index].targets;
    }

  // =========================
  // SPAWN
  // =========================

  void add_animals(WorldSpawner::AnimalSpawnBuffer& spawn_buffer)
{
	for (size_t i = 0; i < spawn_buffer.size; i++)
	  if (spawn(spawn_buffer.animal(i), spawn_buffer.coord(i), false)) {}
	  else
	    {
	      //TODO: error
	    }
}

// returns 0 if failed
  size_t attempt_spawn(Animal animal, bool newborn, Coord coord  , bool insert_search = true
)
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
            animals(i) = animal;
            healths(i) = animal::maxHealths[animal] * INFANT_HEALTH_MODIFIER;
            hungers(i) = animal::maxHungers[animal] * INFANT_HUNGER_MODIFIER;
            sexes(i) = random_bool->next();
            ages(i) = 0;
            targets(i) = std::numeric_limits<size_t>::max();
            target_types(i) = TargetType::NONE;
            actions(i) = Action::NONE;
            frameDatas(i) = FrameData{ActState::NewPath, Direction::South, Frame::F0};
            inertias(i) = 0;
            coords(i) = coord;
        }
        else
        {
        Time age = random_bool->next();
            animals(i) = animal;
            healths(i) = getMaxHealth(animal, age);
            hungers(i) = getMaxHunger(animal, age);
            sexes(i) = random_bool->next();
            ages(i) = age;
            targets(i) = std::numeric_limits<size_t>::max();
            target_types(i) = TargetType::NONE;
            actions(i) = Action::NONE;
            frameDatas(i) = FrameData{ActState::NewPath, Direction::South, Frame::F0};
            inertias(i) = 0;
            coords(i) = coord;
        }
            if (insert_search) search.insert_entity(animal, {i, coord(i)});
        return i;
          }
          
          size_t spawn(Animal animal, bool newborn, Coord origin
bool insert_search = true) {
Coord spawn_point = tiles.get_nearest_empty_tile(origin);
size_t result = 0;
while (result == 0) {
result = attempt_spawn(animal, newborn, spawn_point
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
        Animal animal = animals[i];
            search.remove_entity(animal, {i, coords[i]});
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
   

        animals.save(archive);
        healths.save(archive);
        hungers.save(archive);
        sexes.save(archive);
        ages.save(archive);
        targets.save(archive);
        target_types.save(archive);
        actions.save(archive);
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
        
        animals.load(archive);
        healths.load(archive);
        hungers.load(archive);
        sexes.load(archive);
        ages.load(archive);
        targets.load(archive);
        target_types.load(archive);
        actions.load(archive);
        frameDatas.load(archive);
        inertias.load(archive);
        coords.load(archive);
    }


// =========================
// TRANSFER
// =========================

inline bool transfer(size_t i, animal::Database &old_db)
  {
  if (size >= capacity) return false;
  int index;  
  if (free_slots.empty())
  {
  index = ++size;
	}
	else
	{
		index = free_slots.top();
		free_slots.pop();			
  }
    animals[index] = old_db.animals[i];
    healths[index] = old_db.healths[i];
    hungers[index] = old_db.hungers[i];
    sexes[index] = old_db.sexes[i];
    ages[index] = old_db.ages[i];
    targets[index] = old_db.targets[i];
    target_types[index] = old_db.target_types[i];
    actions[index] = old_db.actions[i];
    frameDatas[index] = old_db.frameDatas[i];
    inertias[index] = old_db.inertias[i];
    coords[index] = old_db.coords[i];
  alives[index] = true;
  old_db.free_slots.push(i);
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

  // =========================
  // ASSIGN
  // =========================

void assign_unassigned_animals();
};
}
