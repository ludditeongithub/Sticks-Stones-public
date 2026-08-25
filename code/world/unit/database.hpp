#pragma once
#include "enum.hpp"
#include <../extern/cereal/archives/binary.hpp>
#include "world/action/enum.hpp"
#include <core/containers.hpp>
#include <core/data.hpp>
#include <core/hash.hpp>
#include <core/math.hpp>
#include <core/random.hpp>
#include <cstdint>
#include <stack>
#include <vector>
#include <unordered_map>
#include <world/item/container.hpp>
#include <world/item/database.hpp>
#include <world/item/enum.hpp>
#include <world/item/stats.hpp>
#include <world/tile/data.hpp>
#include <world/world.hpp>

// TODO: whenever an entity is interacted with, last loop notifies all entities that could have an interaction on that entity (approaching/attacking). combat loop first gets new targets if target is dead.

constexpr uint16_t UNIT_CAP = 1000;
using OverflowHashMap = std::unordered_map<uint32_t, std::vector<HoldableSlot>>;
using OverflowContainerMap = std::unordered_map<uint16_t, std::vector<Container>>;

OverflowHashMap g_overflow_hash_map;
OverflowContainerMap g_overflow_container_map;

// the total volume of each bulk category hands can maximally carry.
// where 0.1 is 100mL
// NOTE: idea: consider doing left and right

// mas weights pawns can carry

constexpr uint16_t CONTAINER_UNDERFLOW_LIMIT = 3;

// Fine means that only fine objects can be carried, mid means that loose, soft, or solid objects
// can be carried, single means that only single objects can be carried

struct Inventory
{
	// TODO
	//  std::variant<ItemSlot, VariantItemSlot, ToolSlot> left_hand;
	//  std::variant<ItemSlot, VariantItemSlot, ToolSlot> right_hand;
	std::array<Container, CONTAINER_UNDERFLOW_LIMIT> containers; // first container is HANDS
	BulkStatus bulk_status = BulkStatus::NONE;		     // for hands
	float weight;
	Inventory()
	{
		containers[0].type = ContainerType::Hands;
		weight = 0;
	}

	bool attempt_hold(Item item) {}
};

struct Skills
{
	Strength strength;
	Athleticism athleticism;
	Dexterity dexterity;
	Intellect intellect;
	Memory memory;
	Perception perception;
	Creativity creativity;
	Charisma charisma;
	Determination determination;

	uint8_t get_random_starting_skill()
	{
		return static_cast<uint8_t>(STARTING_SKILL_MAX * random_chance->next());
	}

	Skills()
	{
		strength = get_random_starting_skill();
		athleticism = get_random_starting_skill();
		dexterity = get_random_starting_skill();
		intellect = get_random_starting_skill();
		perception = get_random_starting_skill();
		creativity = get_random_starting_skill();
		charisma = get_random_starting_skill();
		determination = get_random_starting_skill();
	}
};

constexpr uint8_t MAX_ROLES = 5;
using Roles = std::array<Role, MAX_ROLES>;
using RoleMana = uint8_t;

using Sex = bool;

// places that units own or participate in.
struct Place
{
	Coord pos;
	PlaceType type;
};

using Places = std::array<Place, 3>;

//TODO: container overflow management
namespace unit {
// TODO: differentiate between enemy and friendly databases. make this database several connected
// chunks, so that they can be passed at once to render or other
struct Database
{		
	// @codegen:begin database_generation
// =========================
// BASE DATABASE MEMBERS
// =========================

constexpr static uint16_t entity_size = sizeof(Unit) +
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
 +  sizeof(RoleMana) 
 +  sizeof(std::array<Role, ROLE_MAX>) 
 +  sizeof(SkinData) 
 +  sizeof(Skills) 
 +  sizeof(Inventory) 
 +  sizeof(Place) 
;

size_t capacity;
    size_t size = 1; // 0 is placeholder
    Stack<size_t> free_slots;
    Array<bool> alives;
  SearchGrid& search;
  World& world;
  
  std::vector<EntityID>& no_inertia_buffer; // size is amount of no inertias this loop
  
  std::vector<EntityID>& unassigned_buffer; // size is amount of unassigned this loop
  tile::Database& tiles;

    // =========================
    // ENTITY-SPECIFIC MEMBERS
    // =========================
    Array<Unit> units;
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
    Array<RoleMana> role_mana;
    Array<std::array<Role, ROLE_MAX>> roleLists;
    Array<SkinData> skin_data;
    Array<Skills> skill;
    Array<Inventory> inventory;
    Array<Place> place;

  struct Main {
    Array<Sex> sex;
    Array<Time> age;

  // Serialization
  template <class Archive>
    void save(Archive &archive) const
    {
        sex.save(archive);
        age.save(archive);
     
      }

  template <class Archive>
    void load(Archive &archive)
      {     
        sex.load(archive);
        age.load(archive);
     
    }
};
  struct Targeting {
    Array<size_t> target;
    Array<TargetType> target_type;
    Array<Action> action;

  // Serialization
  template <class Archive>
    void save(Archive &archive) const
    {
        target.save(archive);
        target_type.save(archive);
        action.save(archive);
     
      }

  template <class Archive>
    void load(Archive &archive)
      {     
        target.load(archive);
        target_type.load(archive);
        action.load(archive);
     
    }
};


// =========================
// CONSTRUCTOR
// =========================

Database(Arena *arena, size_t capacity
  , World& world
 
  , SearchGrid& search
  , tile::Database& tiles
) :
  world(world),
  tiles(tiles),
search(search),
{
this->capacity = capacity;
  no_inertia_list.reserve(capacity);

  this->size = 0;

  main.sex = arena_make_array<Sex>(capacity);
  main.age = arena_make_array<Time>(capacity);
  targeting.target = arena_make_array<size_t>(capacity);
  targeting.target_type = arena_make_array<TargetType>(capacity);
  targeting.action = arena_make_array<Action>(capacity);

 units = arena_make_array<Unit>(capacity);
 health = arena_make_array<Health>(capacity);
 hunger = arena_make_array<Hunger>(capacity);
 sex = arena_make_array<Sex>(capacity);
 age = arena_make_array<Time>(capacity);
 target = arena_make_array<size_t>(capacity);
 target_type = arena_make_array<TargetType>(capacity);
 action = arena_make_array<Action>(capacity);
 frame_data = arena_make_array<FrameData>(capacity);
 inertia = arena_make_array<Frame>(capacity);
 coord = arena_make_array<Coord>(capacity);
 role_mana = arena_make_array<RoleMana>(capacity);
 roleLists = arena_make_array<std::array<Role, ROLE_MAX>>(capacity);
 skin_data = arena_make_array<SkinData>(capacity);
 skill = arena_make_array<Skills>(capacity);
 inventory = arena_make_array<Inventory>(capacity);
 place = arena_make_array<Place>(capacity);

}

// =========================
// GETTERS
// =========================

  inline Unit& units(const EntityID index) {
return units[index];
  }
  inline Health& health(const EntityID index) {
return health[index];
  }
  inline Hunger& hunger(const EntityID index) {
return hunger[index];
  }
  inline Sex& sex(const EntityID index) {
return sex[index];
  }
  inline Time& age(const EntityID index) {
return age[index];
  }
  inline size_t& target(const EntityID index) {
return target[index];
  }
  inline TargetType& target_type(const EntityID index) {
return target_type[index];
  }
  inline Action& action(const EntityID index) {
return action[index];
  }
  inline FrameData& frame_data(const EntityID index) {
return frame_data[index];
  }
  inline Frame& inertia(const EntityID index) {
return inertia[index];
  }
  inline Coord& coord(const EntityID index) {
return coord[index];
  }
  inline RoleMana& role_mana(const EntityID index) {
return role_mana[index];
  }
  inline std::array<Role, ROLE_MAX>& roleLists(const EntityID index) {
return roleLists[index];
  }
  inline SkinData& skin_data(const EntityID index) {
return skin_data[index];
  }
  inline Skills& skill(const EntityID index) {
return skill[index];
  }
  inline Inventory& inventory(const EntityID index) {
return inventory[index];
  }
  inline Place& place(const EntityID index) {
return place[index];
  }

    inline Sex& sex(const EntityID index) {    
return main[index].sex;
    }
    inline Time& age(const EntityID index) {    
return main[index].age;
    }
    inline size_t& target(const EntityID index) {    
return targeting[index].target;
    }
    inline TargetType& target_type(const EntityID index) {    
return targeting[index].target_type;
    }
    inline Action& action(const EntityID index) {    
return targeting[index].action;
    }

  
  // =========================
  // SPAWN
  // =========================


bool attempt_spawn(Unit unit, bool newborn, Coord coord  , bool insert_search = true
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
            units(i) = unit;
            health(i) = unit::maxHealths[unit] * INFANT_HEALTH_MODIFIER;
            hunger(i) = unit::maxHungers[unit] * INFANT_HUNGER_MODIFIER;
            sex(i) = random_bool->next();
            age(i) = 0;
            target(i) = std::numeric_limits<size_t>::max();
            target_type(i) = TargetType::NONE;
            action(i) = Action::NONE;
            frame_data(i) = FrameData{ActState::NewPath, Direction::South, Frame::F0};
            inertia(i) = 0;
            coord(i) = coord;
            role_mana(i) = STARTING_ROLE_MANA;
            roleLists(i) = std::array<Role, ROLE_MAX>{};
            skin_data(i) = {'generateMelanin(parent1': None, 'parent2)': None, 'generateSkinWarmth(parent1': None, 0.5: None, 0.0: None};
            skill(i) = Skills{};
            inventory(i) = Inventory{};
            place(i) = Places{};
        }
        else
        {
        Time age = random_bool->next();
            units(i) = unit;
            health(i) = getMaxHealth(unit, age);
            hunger(i) = getMaxHunger(unit, age);
            sex(i) = random_bool->next();
            age(i) = age;
            target(i) = std::numeric_limits<size_t>::max();
            target_type(i) = TargetType::NONE;
            action(i) = Action::NONE;
            frame_data(i) = FrameData{ActState::NewPath, Direction::South, Frame::F0};
            inertia(i) = 0;
            coord(i) = coord;
            role_mana(i) = STARTING_ROLE_MANA;
            roleLists(i) = std::array<Role, ROLE_MAX>{};
            skin_data(i) = {'generateMelanin(world': None, 'coord)': None, 'generateSkinWarmth(world': None, 0.5: None, 0.0: None};
            skill(i) = Skills{};
            inventory(i) = Inventory{};
            place(i) = Places{};
        }
            if (insert_search) search.insert_entity(unit, {i, coord(i)});
        return i;
          }
          
        

size_t spawn(const Unit unit, const bool newborn, const Coord origin
const bool insert_search = true) {
Coord spawn_point = tiles.get_nearest_empty_tile(origin);
size_t result = 0;
while (result == 0) {
result = attempt_spawn(unit, newborn, spawn_point
, insert_search);
if (result == 0) free_unused_entity();
}
}        
    

  // =========================
  // REMOVE
  // =========================
  
  inline bool remove(const EntityID i)
  {
        if (!alive(i))
            return false;

        free_slots.push(i);
        alive(i) = false;
        Unit unit = unit(i);
            search.remove_entity(unit, {i, coord(i)});
        return true;
  }

  inline void free_unused_entity()
  {
    for (size_t i = 0; i < coords.size; i++) {
    if (tiles.tile_status(i).get<VisionStatus>() == VisionStatus::Hidden) remove(i);
    }
  }
    

  // =========================
  // MOVE
  // =========================
  
    inline bool attempt_move_entity(const EntityID index)
  {
  #if !SHIPPING_BUILD
  assert(index < 
  #endif

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

  // genreal serialization

    template <class Archive>
    void save(Archive &archive) const
    {
    archive(capacity);
        archive(size);
        archive(free_slots);
        archive(alives);
   

        units.save(archive);
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
        role_mana.save(archive);
        roleLists.save(archive);
        skin_data.save(archive);
        skill.save(archive);
        inventory.save(archive);
        place.save(archive);
    }

    template <class Archive>
    void load(Archive &archive)
    {
        archive(capacity);
        archive(size);
        archive(free_slots);
        archive(alives);
        
        units.load(archive);
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
        role_mana.load(archive);
        roleLists.load(archive);
        skin_data.load(archive);
        skill.load(archive);
        inventory.load(archive);
        place.load(archive);
    }


// =========================
// TRANSFER
// =========================


inline bool transfer(size_t i, unit::Database &old_db)
  {
  #if !SHIPPING_BUILD
  assert(i < size);
  #endif
  
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
    units(index) = old_db.units(i);
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
    role_mana(index) = old_db.role_mana(i);
    roleLists(index) = old_db.roleLists(i);
    skin_data(index) = old_db.skin_data(i);
    skill(index) = old_db.skill(i);
    inventory(index) = old_db.inventory(i);
    place(index) = old_db.place(i);
  alive(index) = true;

  old_db.free_slots.push(i);
  old_db.alive(index) = false;
  return true;
  }
// @codegen:end database_generation
};
        
}
