#pragma once

#include <stack>
#include "enum.hpp"
#include "core/containers.hpp"
#include <core/data.hpp>
#include <core/math.hpp>
#include <world/world.hpp>
#include <world/item/enum.hpp>
#include <world/item/stats.hpp>
#include <world/tile/data.hpp>

struct ItemSlot {
  Item item;
  uint16_t amount;
};

struct VariantItemSlot : ItemSlot {
  uint8_t variant; 
};

using ItemPointer = std::variant<ItemSlot *, VariantItemSlot *>;
  
struct Inventory {
    ItemPointer leftHand;
    ItemPointer rightHand;
    std::vector<ItemSlot> items; //contains all non-variant items
    std::vector<VariantItemSlot> variantItems; //contains all variant items  
    float bulk = 0.0;// in hands, not in containers
    BulkStatus bulkStatus = BulkStatus::NONE;
    float weight = 0.0; // in hands, not in containers

    std::vector<std::pair<Tool,Material>> tools;
    std::vector<Container> containers;    
};

//TODO: possibly pack these
using Strength = uint8_t;
using Athleticism = uint8_t;
using Dexterity = uint8_t;
using Intellect = uint8_t;
using Perception = uint8_t;
using Creativity = uint8_t;
using Charisma = uint8_t;
using Determination = uint8_t;

constexpr uint8_t SKILL_MAX = 50;
constexpr uint8_t STARTING_SKILL_MAX = 25;

struct Skills {
  Strength strength;
  Athleticism athleticism;
  Dexterity dexterity;
  Intellect intellect;
  Perception perception;
  Creativity creativity;
  Charisma charisma;
  Determination determination;

  uint8_t getRandomStartingSkill() {
	  return static_cast<uint8_t>(STARTING_SKILL_MAX * rper());
  }
	
  Skills() {
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
struct Place {
  Coord pos;
  PlaceType type;
};
  
using Places = std::vector<Place>;

  constexpr RoleMana STARTING_ROLE_MANA = 10;
  constexpr Health MAX_HEALTH = 100;
  constexpr Health INFANT_STARTING_HEALTH_MAX = 50;
  constexpr Health INFANT_STARTING_HEALTH_MIN = 38;
  constexpr Hunger INFANT_HUNGER_MAX = 850;

  struct UnitDatabase {
	  uint16_t cap;
	  uint16_t size;
	  std::stack<uint16_t> freeSlots;
	  std::vector<bool> alive;
	  
	  // processing done with animals
	  Array<Coord> coords;
          Array<Direction> directions;
  Array<Health> healths;
  Array<Hunger> hungers;
  Array<Time> ages;
  Array<Action> actions;
  Array<uint16_t> targets;
  Array<TargetType> targetTypes; // consider packing with animal statuses as
                                 // this is related to movement.
  Array<Frame> frames;
	  // processing unique to units
	  Array<Inventory> inventories;
          std::vector<Sex> sexs;
          Array<Roles> roles;
          Array<RoleMana> roleManas;
          Array<Skills> skills;
          Array<Places> places;

          UnitDatabase(uint16_t s) {
            size = 0;
	    cap = s;
		  alive = std::vector<bool>(s);
		  coords = Array<Coord>(s);
		  directions = Array<Direction>(s);
		  healths = Array<Health>(s);
		  hungers = Array<Hunger>(s);
		  ages = Array<Time>(s);
		  actions = Array<Action>(s);
		  targets = Array<uint16_t>(s);
		  targetTypes = Array<TargetType>(s);
		  frames = Array<Frame>(s);
		  inventories = Array<Inventory>(s);
		  sexs = std::vector<Sex>(s);
		  roles = Array<Roles>(s);
		  roleManas = Array<RoleMana>(s);
		  skills = Array<Skills>(s);
		  places = Array<Places>(s);
	  }

          bool birthUnit(Coord c) {
            if (size + 1 > cap)
              return false;
	    size++;
            if (freeSlots.empty()) {
            alive.emplace_back(true);
            coords.push(c);
            directions.push(random_enum<Direction>());
            healths.push(rfloat() * (INFANT_STARTING_HEALTH_MAX - INFANT_STARTING_HEALTH_MIN));
            hungers.push(INFANT_HUNGER_MAX);
            ages.push(0);
            actions.push(Action::NONE);
            targets.push(std::numeric_limits<uint16_t>::max());
            targetTypes.push(TargetType::NONE);
            frames.push(0);
	    inventories.push(Inventory());
            sexs.emplace_back(rbool());
            roles.push({});
	    roleManas.push(STARTING_ROLE_MANA);
            skills.push(Skills());
            places.push({});
                  } else {
                    uint16_t i = freeSlots.top();
                    freeSlots.pop();
		    
            coords[i] = c;
            directions[i] = random_enum<Direction>();
            healths[i] = rfloat() *(INFANT_STARTING_HEALTH_MAX - INFANT_STARTING_HEALTH_MIN);
            hungers[i] = INFANT_HUNGER_MAX;
            ages[i] = 0;
            actions[i] = Action::NONE;
            targets[i] = std::numeric_limits<uint16_t>::max();
            targetTypes[i] = TargetType::NONE;
            frames[i] = 0;
	    inventories[i] = Inventory();
            sexs[i] = rbool();
            roles[i] = {};
	    roleManas[i] = STARTING_ROLE_MANA;
            skills[i] = Skills();
            places[i] = {};
		  }
          }

          void killUnit(uint16_t i) {
            if (alive[i] == false) 
	  }
  };

