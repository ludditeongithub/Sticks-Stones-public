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
#include <systems/search/search.hpp>
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
    size_t size;
    Stack<size_t> free_slots;
    Array<bool> alives;
  SearchGrid& search;
  World& world;
  
  std::vector<EntityID>& no_inertia_buffer; // size is amount of no inertias this loop
  
  std::vector<EntityID>& unassigned_buffer; // size is amount of unassigned this loop
  tile::Database& tiles;
  item::VariantDatabase& variant_items;

    // =========================
    // ENTITY-SPECIFIC MEMBERS
    // =========================
    Array<Animal> animals;
    Array<Health> health;
    Array<Hunger> hunger;
    Array<Sex> sex;
    Array<Time> age;
    Array<size_t> target;
    Array<TargetType> target_type;
    Array<Action> action;
    Array<FrameData> frame_data;
    Array<Frame> inertia;
    Array<Coord> coord;

struct Main {
    Array<Health> health;
    Array<Sex> sex;
    Array<Time> age;
};
struct Target {
    Array<size_t> target;
    Array<TargetType> target_type;
    Array<Action> action;
};


// =========================
// CONSTRUCTOR
// =========================

Database(Arena *arena, size_t capacity
  , World& world
 
  , SearchGrid& search
  , tile::Database& tiles
  , item::VariantDatabase& variant_items
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
return animals[index];
  }
  inline Health& health(size_t index) {
return health[index];
  }
  inline Hunger& hunger(size_t index) {
return hunger[index];
  }
  inline Sex& sex(size_t index) {
return sex[index];
  }
  inline Time& age(size_t index) {
return age[index];
  }
  inline size_t& target(size_t index) {
return target[index];
  }
  inline TargetType& target_type(size_t index) {
return target_type[index];
  }
  inline Action& action(size_t index) {
return action[index];
  }
  inline FrameData& frame_data(size_t index) {
return frame_data[index];
  }
  inline Frame& inertia(size_t index) {
return inertia[index];
  }
  inline Coord& coord(size_t index) {
return coord[index];
  }

    inline Health& health(size_t index) {    
return main[index].health;
    }
    inline Sex& sex(size_t index) {    
return main[index].sex;
    }
    inline Time& age(size_t index) {    
return main[index].age;
    }
    inline size_t& target(size_t index) {    
return target[index].target;
    }
    inline TargetType& target_type(size_t index) {    
return target[index].target_type;
    }
    inline Action& action(size_t index) {    
return target[index].action;
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
 
  bool attempt_spawn(Animal animal, bool newborn, Coord coord  , bool insert_search = true
)
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
            animals(i) = animal;
            health(i) = animal::maxHealths[animal] * INFANT_HEALTH_MODIFIER;
            hunger(i) = animal::maxHungers[animal] * INFANT_HUNGER_MODIFIER;
            sex(i) = random_bool->next();
            age(i) = 0;
            target(i) = std::numeric_limits<size_t>::max();
            target_type(i) = TargetType::NONE;
            action(i) = Action::NONE;
            frame_data(i) = FrameData{ActState::NewPath, Direction::South, Frame::F0};
            inertia(i) = 0;
            coord(i) = coord;
        }
        else
        {
        Time age = random_bool->next();
            animals(i) = animal;
            health(i) = getMaxHealth(animal, age);
            hunger(i) = getMaxHunger(animal, age);
            sex(i) = random_bool->next();
            age(i) = age;
            target(i) = std::numeric_limits<size_t>::max();
            target_type(i) = TargetType::NONE;
            action(i) = Action::NONE;
            frame_data(i) = FrameData{ActState::NewPath, Direction::South, Frame::F0};
            inertia(i) = 0;
            coord(i) = coord;
        }
            if (insert_search) search.insert_entity(animal, {i, coord(i)});
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
        if (!alive(i))
            return false;

        free_slots.push(i);
        alive(i) = false;
        Animal animal = animal(i);
            search.remove_entity(animal, {i, coord(i)});
        return true;
  }

  void free_unused_entity()
  {
    for (size_t i = 0; i < coords.size; i++) {
    if (tiles.tile_status(i).get<VisionStatus>() == VisionStatus::Hidden) remove(i);
    }
  }
    

  // =========================
  // MOVE
  // =========================
  
    inline bool attempt_move_entity(size_t index)
    {
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

    template <class Archive>
    void save(Archive &archive) const
    {
    archive(capacity);
        archive(size);
        archive(free_slots);
        archive(alives);
   

        animals.save(archive);
        health.save(archive);
        hunger.save(archive);
        sex.save(archive);
        age.save(archive);
        target.save(archive);
        target_type.save(archive);
        action.save(archive);
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
        
        animals.load(archive);
        health.load(archive);
        hunger.load(archive);
        sex.load(archive);
        age.load(archive);
        target.load(archive);
        target_type.load(archive);
        action.load(archive);
        frame_data.load(archive);
        inertia.load(archive);
        coord.load(archive);
    }


// =========================
// TRANSFER
// =========================

inline bool transferAnimal(size_t i, AnimalDatabase &old_db, AnimalDatabase &new_db)
  {
  if (new_db.size >= new_db.capacity) return false;
  int index;  
  if (new_db.free_slots.empty())
  {
  index = ++size;
	}
	else
	{
		index = new_db.free_slots.top();
		new_db.free_slots.pop();			
  }
    new_db.animals(index) = old_db.animals(i);
    new_db.health(index) = old_db.health(i);
    new_db.hunger(index) = old_db.hunger(i);
    new_db.sex(index) = old_db.sex(i);
    new_db.age(index) = old_db.age(i);
    new_db.target(index) = old_db.target(i);
    new_db.target_type(index) = old_db.target_type(i);
    new_db.action(index) = old_db.action(i);
    new_db.frame_data(index) = old_db.frame_data(i);
    new_db.inertia(index) = old_db.inertia(i);
    new_db.coord(index) = old_db.coord(i);
  new_db.alive(index) = true;
  old_db.free_slots.push(i);
  old_db.alive(index) = false;
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
