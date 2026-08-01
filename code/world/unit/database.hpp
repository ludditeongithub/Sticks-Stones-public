#pragma once
#include "enum.hpp"
#include "world/action/enum.hpp"
#include <macros/database.hpp>
#include <macros/serialization.hpp>
#include <core/containers.hpp>
#include <core/data.hpp>
#include <core/hash.hpp>
#include <core/math.hpp>
#include <core/random.hpp>
#include <macros/database.hpp>
#include <cereal/archives/binary.hpp>
#include <cstdint>
#include <stack>
#include <vector>
#include <unordered_map>
#include <world/defaults.hpp>
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
 +  sizeof(Places) 
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

    // =========================
    // ENTITY-SPECIFIC MEMBERS
    // =========================
    Array<Unit> units;
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
    Array<RoleMana> roleManas;
    Array<std::array<Role, ROLE_MAX>> roleLists;
    Array<SkinData> skinDatas;
    Array<Skills> skills;
    Array<Inventory> inventories;
    Array<Places> places;

    struct main {
    
    
    }
    struct targeting {
    
    
    }


// =========================
// CONSTRUCTOR
// =========================

Database(Arena *arena, size_t capacity
  , World& world
 
  , SearchGrid& search
  , TileDatabase& tiles
) :
  world(world),
  tiles(tiles),
search(search),
{
this->capacity = capacity;
  no_inertia_list.reserve(capacity);

  this->size = 0;

}

// =========================
// GETTERS
// =========================

  inline Unit& units(size_t index) {
return unitss[index];
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
  inline RoleMana& roleManas(size_t index) {
return roleManass[index];
  }
  inline std::array<Role, ROLE_MAX>& roleLists(size_t index) {
return roleListss[index];
  }
  inline SkinData& skinDatas(size_t index) {
return skinDatass[index];
  }
  inline Skills& skills(size_t index) {
return skillss[index];
  }
  inline Inventory& inventories(size_t index) {
return inventoriess[index];
  }
  inline Places& places(size_t index) {
return placess[index];
  }

    inline Sex& sexes(size_t index) {    
return main[index].sexes;
    }
    inline Time& ages(size_t index) {    
return main[index].ages;
    }
    inline size_t& targets(size_t index) {    
return targeting[index].targets;
    }

  // =========================
  // SPAWN
  // =========================


// returns 0 if failed
  size_t attempt_spawn(Unit unit, bool newborn, Coord coord  , bool insert_search = true
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
            healths(i) = unit::maxHealths[unit] * INFANT_HEALTH_MODIFIER;
            hungers(i) = unit::maxHungers[unit] * INFANT_HUNGER_MODIFIER;
            sexes(i) = random_bool->next();
            ages(i) = 0;
            targets(i) = std::numeric_limits<size_t>::max();
            target_types(i) = TargetType::NONE;
            actions(i) = Action::NONE;
            frameDatas(i) = FrameData{ActState::NewPath, Direction::South, Frame::F0};
            inertias(i) = 0;
            coords(i) = coord;
            roleManas(i) = STARTING_ROLE_MANA;
            roleLists(i) = std::array<Role, ROLE_MAX>{};
            skinDatas(i) = {'generateMelanin(parent1': None, 'parent2)': None, 'generateSkinWarmth(parent1': None, 0.5: None, 0.0: None};
            skills(i) = Skills{};
            inventories(i) = Inventory{};
            places(i) = Places{};
        }
        else
        {
        Time age = random_bool->next();
            units(i) = unit;
            healths(i) = getMaxHealth(unit, age);
            hungers(i) = getMaxHunger(unit, age);
            sexes(i) = random_bool->next();
            ages(i) = age;
            targets(i) = std::numeric_limits<size_t>::max();
            target_types(i) = TargetType::NONE;
            actions(i) = Action::NONE;
            frameDatas(i) = FrameData{ActState::NewPath, Direction::South, Frame::F0};
            inertias(i) = 0;
            coords(i) = coord;
            roleManas(i) = STARTING_ROLE_MANA;
            roleLists(i) = std::array<Role, ROLE_MAX>{};
            skinDatas(i) = {'generateMelanin(world': None, 'coord)': None, 'generateSkinWarmth(world': None, 0.5: None, 0.0: None};
            skills(i) = Skills{};
            inventories(i) = Inventory{};
            places(i) = Places{};
        }
            if (insert_search) search.insert_entity(unit, {i, coord(i)});
        return i;
          }
          
          size_t spawn(Unit unit, bool newborn, Coord origin
bool insert_search = true) {
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
  
  inline bool remove(size_t i)
  {
        if (!alives[i])
            return false;

        free_slots.push(i);
        alives[i] = false;
        Unit unit = units[i];
            search.remove_entity(unit, {i, coords[i]});
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
   

        units.save(archive);
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
        roleManas.save(archive);
        roleLists.save(archive);
        skinDatas.save(archive);
        skills.save(archive);
        inventories.save(archive);
        places.save(archive);
    }

    template <class Archive>
    void load(Archive &archive)
    {
        archive(capacity);
        archive(size);
        archive(free_slots);
        archive(alives);
        
        units.load(archive);
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
        roleManas.load(archive);
        roleLists.load(archive);
        skinDatas.load(archive);
        skills.load(archive);
        inventories.load(archive);
        places.load(archive);
    }


// =========================
// TRANSFER
// =========================

inline bool transfer(size_t i, unit::Database &old_db)
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
    units[index] = old_db.units[i];
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
    roleManas[index] = old_db.roleManas[i];
    roleLists[index] = old_db.roleLists[i];
    skinDatas[index] = old_db.skinDatas[i];
    skills[index] = old_db.skills[i];
    inventories[index] = old_db.inventories[i];
    places[index] = old_db.places[i];
  alives[index] = true;
  old_db.free_slots.push(i);
  old_db.alives[index] = false;
  return true;
  }
// @codegen:end database_generation
};
        
}
