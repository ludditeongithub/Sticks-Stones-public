#pragma once
#include <data/types/unit.hpp>
#include <data/types/target.hpp>
#include <data/types/rendering.hpp>
#include <data/types/action.hpp>
#include <data/const/unit_data.hpp>
#include <data/const/unit_tables.hpp>
#include <data/run/unit_helpers.hpp>
#include <cstdint>
#include <stack>
#include <logic/generic/search/search.hpp>

// TODO: whenever an entity is interacted with, last loop notifies all entities that could have an interaction on that entity (approaching/attacking). combat loop first gets new targets if target is dead.

//TODO: container overflow management
namespace unit {
// TODO: differentiate between enemy and friendly databases. make this database several connected
// chunks, so that they can be passed at once to render or other
class Database
{
	// @codegen:begin database_generation
public:
// =========================
// BASE DATABASE MEMBERS
// =========================

constexpr static uint16_t ENTITY_SIZE = sizeof(Unit) +
+ sizeof(bool)
  
 +  sizeof(Unit) 
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
 +  sizeof(SkinData) 
 +  sizeof(RoleMana) 
 +  sizeof(std::array<Role, MAX_ROLES>) 
 +  sizeof(Skills) 
 +  sizeof(Inventory) 
 +  sizeof(Places) 
;

size_t capacity;
    size_t size = 1; // 0 is placeholder
    std::stack<size_t> free_slots;
    Array<bool> alives;
  SearchGrid& search;
  Array<EntityID> no_inertia_buffer; 
  Array<EntityID> unassigned_buffer;
  tile::Database* tiles;

    // =========================
    // ENTITY-SPECIFIC MEMBERS
    // =========================
    Array<Unit> units;
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
    Array<SkinData> skin_datas;
    Array<RoleMana> role_manas;
    Array<std::array<Role, MAX_ROLES>> role_lists;
    Array<Skills> skills;
    Array<Inventory> inventorys;
    Array<Places> places;



// =========================
// INIT
// =========================

  void init(Arena* arena, size_t capacity
  , SearchGrid& search
  , tile::Database& tiles
) 
{
this->capacity = capacity;
  no_inertia_buffer = arena_make_array<EntityID>(arena, capacity);
  unassigned_buffer = arena_make_array<EntityID>(arena, capacity);
  this->size = 0;
  this->tiles = &tiles;
 
  units = arena_make_array<Unit>(arena, capacity);
 
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
 
  skin_datas = arena_make_array<SkinData>(arena, capacity);
 
  role_manas = arena_make_array<RoleMana>(arena, capacity);
 
  role_lists = arena_make_array<std::array<Role, MAX_ROLES>>(arena, capacity);
 
  skills = arena_make_array<Skills>(arena, capacity);
 
  inventorys = arena_make_array<Inventory>(arena, capacity);
 
  places = arena_make_array<Places>(arena, capacity);
 

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

           units.serialize(archive);
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
           skin_datas.serialize(archive);
           role_manas.serialize(archive);
           role_lists.serialize(archive);
           skills.serialize(archive);
           inventorys.serialize(archive);
           places.serialize(archive);
         
    }
         

// =========================
// GETTERS
// =========================

  inline Unit& unit(const EntityID index) {
return units[index];
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
  inline SkinData& skin_data(const EntityID index) {
return skin_datas[index];
  }
  inline RoleMana& role_mana(const EntityID index) {
return role_manas[index];
  }
  inline std::array<Role, MAX_ROLES>& role_list(const EntityID index) {
return role_lists[index];
  }
  inline Skills& skill(const EntityID index) {
return skills[index];
  }
  inline Inventory& inventory(const EntityID index) {
return inventorys[index];
  }
  inline Places& place(const EntityID index) {
return places[index];
  }


  
// =========================
// GENERATION
// =========================


  // =========================
  // SPAWN
  // =========================

bool attempt_spawn(const Unit unit, const Coord coord, const bool newborn  , float parent1, float parent2
, const bool insert_search = true
)
{
#if !SHIPPING_BUILD
assert(unit != Unit::NONE && unit != Unit::MAX && "Tried to spawn unit as NONE or MAX.");
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
            this->unit(i) = unit;
            this->health(i) = unit::MAX_HEALTHS[unit] * INFANT_HEALTH_MODIFIER;
            this->hunger(i) = unit::MAX_HUNGERS[unit] * INFANT_HUNGER_MODIFIER;
            this->sex(i) = random_bool->next();
            this->age(i) = 0;
            this->target(i) = std::numeric_limits<size_t>::max();
            this->target_type(i) = TargetType::NONE;
            this->action(i) = Action::NONE;
            this->frame_data(i) = FrameData{ActState::NewPath, Direction::South, 0};
            this->inertia(i) = 0;
            this->coord(i) = coord;
            this->skin_data(i) = {generate_melanin(parent1, parent2), generate_skin_warmth(parent1, parent2), 0.5, 0.0};
            this->role_mana(i) = STARTING_ROLE_MANA;
            this->role_list(i) = std::array<Role, MAX_ROLES>{};
            this->skill(i) = Skills{};
            this->inventory(i) = Inventory{};
            this->place(i) = Places{};
        }
        else
        {
        Time age = random_bool->next();
            this->unit(i) = unit;
            this->health(i) = unit::get_max_health(unit, age);
            this->hunger(i) = get_max_hunger(unit, age);
            this->sex(i) = random_bool->next();
            this->age(i) = age;
            this->target(i) = std::numeric_limits<size_t>::max();
            this->target_type(i) = TargetType::NONE;
            this->action(i) = Action::NONE;
            this->frame_data(i) = FrameData{ActState::NewPath, Direction::South, 0};
            this->inertia(i) = 0;
            this->coord(i) = coord;
            this->skin_data(i) = {generate_melanin(coord), generate_skin_warmth(coord), 0.5, 0.0};
            this->role_mana(i) = STARTING_ROLE_MANA;
            this->role_list(i) = std::array<Role, MAX_ROLES>{};
            this->skill(i) = Skills{};
            this->inventory(i) = Inventory{};
            this->place(i) = Places{};
        }
            if (insert_search) search.insert_entity(unit, {i, this->coord(i)});
        return i;
          }
          
        

          bool spawn(const Unit unit, const Coord origin, const bool newborn
, float parent1, float parent2
, const bool insert_search = true) {
Coord spawn_point = tiles->get_nearest_empty_tile(origin);
bool result = false;
result = attempt_spawn(unit, spawn_point, newborn
, parent1, parent2
, insert_search  
);
if (!result) {
free_unused_entity();
attempt_spawn(unit, spawn_point, newborn
, parent1, parent2
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
        Unit unit = this->unit(i);
            search.remove_entity(unit, {i, coord(i)});
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

inline bool transfer(size_t i, unit::Database &old_db)
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
    unit(index) = old_db.unit(i);
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
    skin_data(index) = old_db.skin_data(i);
    role_mana(index) = old_db.role_mana(i);
    role_list(index) = old_db.role_list(i);
    skill(index) = old_db.skill(i);
    inventory(index) = old_db.inventory(i);
    place(index) = old_db.place(i);
  alives[index] = true;

  old_db.free_slots.push(i);
  old_db.alives[index] = false;
  return true;
  }
  
// @codegen:end database_generation
};
        
}
