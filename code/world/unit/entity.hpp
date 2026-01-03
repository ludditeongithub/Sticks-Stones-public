#pragma once

namespace Unit {

  #include <basic/coord.hpp>
  #include <basic/target.hpp>

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
    vector<ItemSlot> items; //contains all non-variant items
    vector<VariantItemSlot> variantItems; //contains all variant items  
    float bulk = 0.0;// in hands, not in containers
    BulkStatus bulkStatus = BulkStatus::NONE;
    float weight = 0.0; // in hands, not in containers

    struct Tools { vector<std::pair<Tool,Material>> tools; };
    struct Containers {
      vector<Container> containers;
    };
};

struct Strength {
  uint8_t strength = rint(STAT_MIN,STAT_MAX);;
};
  
struct Athleticism {
  uint8_t athleticism = rint(STAT_MIN,STAT_MAX);
};

struct Dexterity {
  uintt8_t dexterity = rint(STAT_MIN,STAT_MAX);
};

struct Intellect {
  uint8_t intellect = rint(STAT_MIN,STAT_MAX);
};

struct Perception {
  uint8_t perception = rint(STAT_MIN, STAT_MAX);
};

struct Creativity {
  uint8_t creativity = rint(STAT_MIN,STAT_MAX);
};

struct Charisma {
  uint8_t charisma = rint(STAT_MIN,STAT_MAX);
};

struct Determination {
  uint8_t determination = rint(STAT_MIN,STAT_MAX);
};

struct Stats {
  Strength strength;
  Athleticism athleticism;
  Dexterity dexterity;
  Intellect intellect;
  Perception perception;
  Creativity creativity;
  Charisma charisma;
  Determination determination;
};
  
struct Roles { vector<Role> roles; };
struct Sex { bool sex; };
struct Movement { MovingStatus::movingStatus; };
struct Health { uint8_t health; };
vector<uint16_t> inertias;
struct RoleMana {
  uint8_t remainingRoleMana;
};  
  
struct Place {
  Coord pos;
  PlaceType type;
};
  
struct Places {
  vector<Place> places;
};

  constexpr RoleMana STARTING_ROLE_MANA = 10;
  constexpr Health MAX_HEALTH = 100;
  
}
