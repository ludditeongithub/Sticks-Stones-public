#pragma once
#include "data/types/tile.hpp"
#include <data/types/animal.hpp>
#include <data/types/stats.hpp>
#include <data/types/time.hpp>
#include <data/types/target.hpp>
#include <data/types/action.hpp>
#include <data/const/animal_data.hpp>
#include <data/const/animal_tables.hpp>
#include <data/const/time_data.hpp>
#include <data/run/item_database.hpp>
#include <data/run/world.hpp>
#include <core/containers.hpp>
#include <logic/generic/search/search.hpp>

#include <core/random.hpp>
#include <cstdint>

#include <cereal/types/vector.hpp>
#include <cereal/archives/binary.hpp>
#include <cereal/types/stack.hpp>
struct World;

namespace animal
		{				
struct Database
{
private:
		struct EggFertilizationHandler {
		std::vector<size_t> fertilized_egg_layers;
		std::vector<bool> valid;
		Stack<size_t> free_indices;
		void push_back(size_t index)
		{
			if (free_indices.empty())
					{
				fertilized_egg_layers.push_back(index);
				valid.push_back(true);
					}
					else
							{
									size_t slot = free_indices.top();
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
public:
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
 +  sizeof(Frame) 
 +  sizeof(Coord) 
;

size_t capacity;
    size_t size = 1; // 0 is placeholder
    std::stack<size_t> free_slots;
    Array<bool> alives;
  SearchGrid& search;
  Array<EntityID> no_inertia_buffer; 
  Array<EntityID> unassigned_buffer;
  tile::Database* tiles;
  item::VariantDatabase* variant_items;

    // =========================
    // ENTITY-SPECIFIC MEMBERS
    // =========================
    Array<Animal> animals;
    Array<Health> healths;
    Array<Hunger> hungers;
    Array<Sex> sexs;
    Array<Time> ages;
    Array<size_t> targets;
    Array<TargetType> target_types;
    Array<Action> actions;
    Array<FrameData> frame_datas;
    Array<Frame> inertias;
    Array<Coord> coords;



// =========================
// INIT
// =========================

  void init(Arena* arena, size_t capacity
  , SearchGrid& search
  , tile::Database& tiles
  , item::VariantDatabase& variant_items
) 
{
this->capacity = capacity;
  no_inertia_buffer = arena_make_array<EntityID>(arena, capacity);
  unassigned_buffer = arena_make_array<EntityID>(arena, capacity);
  this->size = 0;
  this->tiles = &tiles;
  this->variant_items = &variant_items;
  fertilization_handler = EggFertilizationHandler(capacity / 20);
 
  animals = arena_make_array<Animal>(arena, capacity);
 
  healths = arena_make_array<Health>(arena, capacity);
 
  hungers = arena_make_array<Hunger>(arena, capacity);
 
  sexs = arena_make_array<Sex>(arena, capacity);
 
  ages = arena_make_array<Time>(arena, capacity);
 
  targets = arena_make_array<size_t>(arena, capacity);
 
  target_types = arena_make_array<TargetType>(arena, capacity);
 
  actions = arena_make_array<Action>(arena, capacity);
 
  frame_datas = arena_make_array<FrameData>(arena, capacity);
 
  inertias = arena_make_array<Frame>(arena, capacity);
 
  coords = arena_make_array<Coord>(arena, capacity);
 

}
    // =========================
    // SERIALIZATION
    // =========================

      template <class Archive>
    void serialize(Archive &archive) const
{
        archive(tiles);
        archive(search);
        archive(size);
        archive(free_slots);
        archive(alives);

           animals.serialize(archive);
           healths.serialize(archive);
           hungers.serialize(archive);
           sexs.serialize(archive);
           ages.serialize(archive);
           targets.serialize(archive);
           target_types.serialize(archive);
           actions.serialize(archive);
           frame_datas.serialize(archive);
           inertias.serialize(archive);
           coords.serialize(archive);
         
    }
         

// =========================
// GETTERS
// =========================

  inline Animal& animal(const EntityID index) {
return animals[index];
  }
  inline Health& health(const EntityID index) {
return healths[index];
  }
  inline Hunger& hunger(const EntityID index) {
return hungers[index];
  }
  inline Sex& sex(const EntityID index) {
return sexs[index];
  }
  inline Time& age(const EntityID index) {
return ages[index];
  }
  inline size_t& target(const EntityID index) {
return targets[index];
  }
  inline TargetType& target_type(const EntityID index) {
return target_types[index];
  }
  inline Action& action(const EntityID index) {
return actions[index];
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
// GENERATION
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

  // =========================
  // SPAWN
  // =========================

bool attempt_spawn(const Animal animal, const Coord coord, const bool newborn  , const bool insert_search = true
)
{
#if !SHIPPING_BUILD
assert(animal != Animal::NONE && animal != Animal::MAX && "Tried to spawn animal as NONE or MAX.");
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
            this->animal(i) = animal;
            this->health(i) = animal::MAX_HEALTHS[animal] * INFANT_HEALTH_MODIFIER;
            this->hunger(i) = animal::MAX_HUNGERS[animal] * INFANT_HUNGER_MODIFIER;
            this->sex(i) = random_bool->next();
            this->age(i) = 0;
            this->target(i) = std::numeric_limits<size_t>::max();
            this->target_type(i) = TargetType::NONE;
            this->action(i) = Action::NONE;
            this->frame_data(i) = FrameData{ActState::NewPath, Direction::South, 0};
            this->inertia(i) = 0;
            this->coord(i) = coord;
        }
        else
        {
        Time age = random_bool->next();
            this->animal(i) = animal;
            this->health(i) = animal::get_max_health(animal, age);
            this->hunger(i) = get_max_hunger(animal, age);
            this->sex(i) = random_bool->next();
            this->age(i) = age;
            this->target(i) = std::numeric_limits<size_t>::max();
            this->target_type(i) = TargetType::NONE;
            this->action(i) = Action::NONE;
            this->frame_data(i) = FrameData{ActState::NewPath, Direction::South, 0};
            this->inertia(i) = 0;
            this->coord(i) = coord;
        }
            if (insert_search) search.insert_entity(animal, {i, this->coord(i)});
        return i;
          }
          
        

          bool spawn(const Animal animal, const Coord origin, const bool newborn
, const bool insert_search = true) {
Coord spawn_point = tiles->get_nearest_empty_tile(origin);
bool result = false;
result = attempt_spawn(animal, spawn_point, newborn
, insert_search  
);
if (!result) {
free_unused_entity();
attempt_spawn(animal, spawn_point, newborn
, insert_search  
);
}
return result;
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
        Animal animal = this->animal(i);
            search.remove_entity(animal, {i, coord(i)});
        return true;
  }

  inline void free_unused_entity()
  {
    for (size_t i = 0; i < coords.capacity; i++) {
    if (tiles->tile_status(i).get<VisionStatus>() == VisionStatus::Hidden) remove(i);
    }
  }
    

  // =========================
  // MOVE
  // =========================
  
    inline bool attempt_move_entity(const EntityID index)
  {
  assert(index <= size);

        Coord& pos = coord(index);
        Coord new_pos = get_pos(frame_data(index).get<Direction>(), pos);
        size_t ti = g_world->get_tile_index_from_coord(new_pos);

    if (tiles->tile_statuss[ti].get<OccupiedStatus>() == OccupiedStatus::Vacant)
        {
            pos = new_pos;
            return true;
        }

        return false;
    }


// =========================
// TRANSFER
// =========================

inline bool transfer(size_t i, animal::Database &old_db)
  {
  assert(i < size);
  
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
    animal(index) = old_db.animal(i);
    health(index) = old_db.health(i);
    hunger(index) = old_db.hunger(i);
    sex(index) = old_db.sex(i);
    age(index) = old_db.age(i);
    target(index) = old_db.target(i);
    target_type(index) = old_db.target_type(i);
    action(index) = old_db.action(i);
    frame_data(index) = old_db.frame_data(i);
    inertia(index) = old_db.inertia(i);
    coord(index) = old_db.coord(i);
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
				
  //                inline void handle_event(Event& event);
		inline void move(size_t i);	
		void make_corpse(const size_t index);
		void kill_animal(const size_t index);
		void lay_egg(Animal animal, Coord coord, bool fertilized);

  // =========================
  // ASSIGN
  // =========================

void assign_unassigned_animals();
};

} // namespace animal
