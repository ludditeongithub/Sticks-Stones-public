#pragma once
#include "enum.hpp"
#include <macros/database.hpp>
#include <macros/serialization.hpp>
#include <core/containers.hpp>
#include <core/data.hpp>
#include <core/hash.hpp>
#include <core/math.hpp>
#include <core/random.hpp>
#include <macros/database.hpp>
#include <extern/cereal/archives/binary.hpp>
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

using OverflowHashMap = std::unordered_map<uint32_t, std::vector<HoldableSlot>>;

using OverflowContainerMap = std::unordered_map<uint16_t, std::vector<Container>>;

constexpr uint16_t UNIT_CAP = 1000;

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
	//  std::variant<ItemSlot, VariantItemSlot, ToolSlot> leftHand;
	//  std::variant<ItemSlot, VariantItemSlot, ToolSlot> rightHand;
	std::array<Container, CONTAINER_UNDERFLOW_LIMIT> containers; // first container is HANDS
	BulkStatus bulkStatus = BulkStatus::NONE;		     // for hands
	float weight;
	Inventory()
	{
		containers[0].type = ContainerType::Hands;
		weight = 0;
	}

	bool attemptHold(Item item) {}
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

	uint8_t getRandomStartingSkill()
	{
		return static_cast<uint8_t>(STARTING_SKILL_MAX * random_chance->next());
	}

	Skills()
	{
		strength = getRandomStartingSkill();
		athleticism = getRandomStartingSkill();
		dexterity = getRandomStartingSkill();
		intellect = getRandomStartingSkill();
		perception = getRandomStartingSkill();
		creativity = getRandomStartingSkill();
		charisma = getRandomStartingSkill();
		determination = getRandomStartingSkill();
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

// TODO: differentiate between enemy and friendly databases. make this database several connected
// chunks, so that they can be passed at once to render or other
struct UnitDatabase
{		
	// @codegen:begin database_generation
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
 +  sizeof(Coord) 
 +  sizeof(RoleMana) 
										+  sizeof(std::array<Role, Role::MAX>) 
 +  sizeof(SkinData) 
 +  sizeof(Skills{}) 
 +  sizeof(Inventory) 
 +  sizeof(Places) 
;

size_t capacity;
    size_t size;
    Stack<size_t> freeSlots;
    Array<bool> alives;
  SearchGrid& search;
  World& world;
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
    Array<TargetType> targetTypes;
    Array<Action> actions;
    Array<FrameData> frameDatas;
    Array<Coord> coords;
    Array<RoleMana> roleManas;
    Array<std::array<Role, ROLE_MAX>> roleLists;
    Array<SkinData> skinDatas;
    Array<Skills{}> skills;
    Array<Inventory> inventories;
    Array<Places> places;
    

// =========================
    // CONSTRUCTOR
    // =========================

UnitDatabase(Arena *arena, size_t capacity
  , World& world
 
  , SearchGrid& search
  , TileDatabase& tiles
) :
  world(world),
  tiles(tiles),
search(search),
{
this->capacity = capacity;
  this->size = 0;

}

  // =========================
  // SPAWN
  // =========================

 
  bool attemptSpawn(Unit unit, bool newborn, Coord coord, )
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
            units[i] = unit;
            healths[i] = unit::maxHealths[unit] * INFANT_HEALTH_MODIFIER;
            hungers[i] = unit::maxHungers[unit] * INFANT_HUNGER_MODIFIER;
            sexes[i] = random_bool->next();
            ages[i] = 0;
            targets[i] = std::numeric_limits<size_t>::max();
            targetTypes[i] = TargetType::NONE;
            actions[i] = Action::NONE;
            frameDatas[i] = FrameData{ActState::NewPath, Direction::South, Frame::F0};
            coords[i] = coord;
            roleManas[i] = STARTING_ROLE_MANA;
            roleLists[i] = std::array<Role, ROLE_MAX>{};
            skinDatas[i] = {'generateMelanin(parent1': None, 'parent2)': None, 'generateSkinWarmth(parent1': None, 0.5: None, 0.0: None};
            skills[i] = Skills{};
            inventories[i] = Inventory{};
            places[i] = Places{};
        }
        else
        {
        Time age = random_bool->next();
            units[i] = unit;
            healths[i] = getMaxHealth(unit, age);
            hungers[i] = getMaxHunger(unit, age);
            sexes[i] = random_bool->next();
            ages[i] = age;
            targets[i] = std::numeric_limits<size_t>::max();
            targetTypes[i] = TargetType::NONE;
            actions[i] = Action::NONE;
            frameDatas[i] = FrameData{ActState::NewPath, Direction::South, Frame::F0};
            coords[i] = coord;
            roleManas[i] = STARTING_ROLE_MANA;
            roleLists[i] = std::array<Role, ROLE_MAX>{};
            skinDatas[i] = {'generateMelanin(world': None, 'coord)': None, 'generateSkinWarmth(world': None, 0.5: None, 0.0: None};
            skills[i] = Skills{};
            inventories[i] = Inventory{};
            places[i] = Places{};
        }
            search.insertEntity(unit, {i, coords[i]});
        return true;
          }
          bool spawn(Unit unit, bool newborn, Coord origin) {
          Coord spawnPoint = tiles.getNearestEmptyTile(origin);
          while (!attemptSpawn(unit, newborn, spawnPoint)) freeUnusedEntity();                 
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
        Unit unit = units[i];
            search.removeEntity(unit, {i, coords[i]});
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
   

        units.save(archive);
        healths.save(archive);
        hungers.save(archive);
        sexes.save(archive);
        ages.save(archive);
        targets.save(archive);
        targetTypes.save(archive);
        actions.save(archive);
        frameDatas.save(archive);
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
        archive(freeSlots);
        archive(alives);
        
        units.load(archive);
        healths.load(archive);
        hungers.load(archive);
        sexes.load(archive);
        ages.load(archive);
        targets.load(archive);
        targetTypes.load(archive);
        actions.load(archive);
        frameDatas.load(archive);
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

inline bool transferUnit(size_t i, UnitDatabase &oldDB, UnitDatabase &newDB)
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
    newDB.units[index] = oldDB.units[i];
    newDB.healths[index] = oldDB.healths[i];
    newDB.hungers[index] = oldDB.hungers[i];
    newDB.sexes[index] = oldDB.sexes[i];
    newDB.ages[index] = oldDB.ages[i];
    newDB.targets[index] = oldDB.targets[i];
    newDB.targetTypes[index] = oldDB.targetTypes[i];
    newDB.actions[index] = oldDB.actions[i];
    newDB.frameDatas[index] = oldDB.frameDatas[i];
    newDB.coords[index] = oldDB.coords[i];
    newDB.roleManas[index] = oldDB.roleManas[i];
    newDB.roleLists[index] = oldDB.roleLists[i];
    newDB.skinDatas[index] = oldDB.skinDatas[i];
    newDB.skills[index] = oldDB.skills[i];
    newDB.inventories[index] = oldDB.inventories[i];
    newDB.places[index] = oldDB.places[i];
  newDB.alives[index] = true;
  oldDB.freeSlots.push(i);
  oldDB.alives[index] = false;
  return true;
  }
// @codegen:end database_generation

};
