#pragma once
#include <core/tables.hpp>
#include <core/memory.hpp>
#include <core/containers.hpp>
#include <data/types/stats.hpp>
#include <data/types/item.hpp>

namespace item {
// @codegen:begin wearable
enum class Wearable {
  PartTribalwear,
  Tribalwear,
  Robe,
  Tunic,
  Pants,
  Dress,
  Sandles,
  Boots,
  Scarf,
  Headwrap,
  Mitts,
  Gloves,
  Apron,
  Helmet,
  Bracers,
  Guards,
  Cape,
  HeavyShirt,
  HeavyPants,
  Gambeson,
  Chainmail,
  Breastplate,
  Plate,
  WoodCrown,
  GoldCrown,
  RoyalCrown,
  Necklace,
  MAX
};

inline constexpr LookupTable<Wearable, Health> healths = [] {
LookupTable<Wearable, Health> lt{};
  using enum Wearable;
return lt;
}();
inline constexpr LookupTable<Wearable, Quality> qualitys = [] {
LookupTable<Wearable, Quality> lt{};
  using enum Wearable;
return lt;
}();
inline constexpr LookupTable<Wearable, bool> equippeds = [] {
LookupTable<Wearable, bool> lt{};
  using enum Wearable;
return lt;
}();

struct WearableDatabase {
Database& database;
size_t size = 0;
std::stack<size_t> free_slots;
Array<size_t> indices;
  Array<Health> health;
  Array<Quality> quality;
  Array<bool> equipped;

// =========================
// INIT
// =========================

void init(Arena* arena, size_t capacity)
{
  health = arena_make_array<Health>(arena, capacity);
  quality = arena_make_array<Quality>(arena, capacity);
  equipped = arena_make_array<bool>(arena, capacity);
}

// =========================
// GETTERS
// =========================

  inline Health& health(size_t index) {
return healths[index];
  }
  inline Quality& quality(size_t index) {
return qualitys[index];
  }
  inline bool& equipped(size_t index) {
return equippeds[index];
  }

// =========================
// SPAWN
// =========================

void spawn_wearable_component(Wearable wearable, , Health health
, Quality quality
, bool equipped
)
{
Item item = item_to_wearable(wearable);
if (free_slots.empty()) {
//TODO: emergency storage
size_t i = size++;
} else size_t i = free_slots.pop();
  health(i) = health;
  quality(i) = quality;
  equipped(i) = equipped;
}

// =========================
// REMOVE
// =========================

inline bool remove(size_t i) {
free_slots.push(i);
database.remove(i);
}

// =========================
// SERIALIZATION
// =========================

    template <class Archive>
    void serialize(Archive &archive) const
    {
      archive(size);
      archive(free_slots);
      archive(indices);
        archive(healths);
        archive(qualitys);
        archive(equippeds);
     
    }


// =========================
// TRANSFER
// =========================

inline bool transfer_Wearable(size_t i, WearableDatabase &old_db)
{
  return database.transfer_item(i, old_db);
  }

// =========================
// INVENTORY MANAGEMENT
// =========================

inline void pick_up(EntityID wearableID, Inventory& inventory) {
WearableEntity wearable = get_entity(index);
Item item = reflect_enum(wearable.specialization);
inventory.add_item(item);
remove_wearable(wearableID);
}

inline void drop(EntityID wearableID, Inventory &inventory) { add_entity(); }
};
// @codegen:end wearable

// @codegen:begin perishable
enum class Perishable {
  Flour,
  MilledRice,
  Bread,
  Pastry,
  Pie,
  Porridge,
  RawMeat,
  CookedMeat,
  AnimalFat,
  Cheese,
  GoatCheese,
  BlueCheese,
  Beer,
  Wine,
  FruitWine,
  Mead,
  Vinegar,
  Butter,
  OliveOil,
  CookingOil,
  Juice,
  CandiedFruit,
  AgedAlcoholicDrink,
  SugarJuice,
  Sugar,
  GroundBlackPepper,
  ChiliPowder,
  AnimalHair,
  TanningAgent,
  Incense,
  BoneMeal,
  FishMeal,
  Fertilizer,
  MAX
};

inline constexpr LookupTable<Perishable, float> decays = [] {
LookupTable<Perishable, float> lt{};
  using enum Perishable;
return lt;
}();
inline constexpr LookupTable<Perishable, PreservationState> preservation_states = [] {
LookupTable<Perishable, PreservationState> lt{};
  using enum Perishable;
return lt;
}();

struct PerishableDatabase {
Database& database;
size_t size = 0;
std::stack<size_t> free_slots;
Array<size_t> indices;
  Array<float> decay;
  Array<PreservationState> preservation_state;

// =========================
// INIT
// =========================

void init(Arena* arena, size_t capacity)
{
  decay = arena_make_array<float>(arena, capacity);
  preservation_state = arena_make_array<PreservationState>(arena, capacity);
}

// =========================
// GETTERS
// =========================

  inline float& decay(size_t index) {
return decays[index];
  }
  inline PreservationState& preservation_state(size_t index) {
return preservation_states[index];
  }

// =========================
// SPAWN
// =========================

void spawn_perishable_component(Perishable perishable, , float decay
, PreservationState preservation_state
)
{
Item item = item_to_perishable(perishable);
if (free_slots.empty()) {
//TODO: emergency storage
size_t i = size++;
} else size_t i = free_slots.pop();
  decay(i) = decay;
  preservation_state(i) = preservation_state;
}

// =========================
// REMOVE
// =========================

inline bool remove(size_t i) {
free_slots.push(i);
database.remove(i);
}

// =========================
// SERIALIZATION
// =========================

    template <class Archive>
    void serialize(Archive &archive) const
    {
      archive(size);
      archive(free_slots);
      archive(indices);
        archive(decays);
        archive(preservation_states);
     
    }


// =========================
// TRANSFER
// =========================

inline bool transfer_Perishable(size_t i, PerishableDatabase &old_db)
{
	return database.transfer_item(i, old_db);
}

// =========================
// INVENTORY MANAGEMENT
// =========================

inline void pick_up(EntityID perishableID, Inventory& inventory) {
PerishableEntity perishable = get_entity(index);
Item item = reflect_enum(perishable.specialization);
inventory.add_item(item);
remove_perishable(perishableID);
}

inline void drop(EntityID perishableID, Inventory &inventory) { add_entity(); }

};
// @codegen:end perishable

// @codegen:begin container
//
// @codegen:end container

// @codegen:begin art
//
// @codegen:end art

// @codegen:begin scavengeable
//
// @codegen:end scavengeable
  
}
