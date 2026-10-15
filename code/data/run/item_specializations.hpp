#pragma once
#include <core/tables.hpp>
#include <core/memory.hpp>
#include <core/containers.hpp>
#include <data/types/stats.hpp>
#include <data/types/item.hpp>
#include <data/types/item_specialization.hpp>
#include <data/run/item_database.hpp>
#include <stack>

namespace item {
// @codegen:begin wearable
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
  Array<Health> healths;
  Array<Quality> qualitys;
  Array<bool> equippeds;

// =========================
// INIT
// =========================

void init(Arena* arena, size_t capacity)
{
  healths = arena_make_array<Health>(arena, capacity);
  qualitys = arena_make_array<Quality>(arena, capacity);
  equippeds = arena_make_array<bool>(arena, capacity);
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
size_t i;
if (free_slots.empty()) {
//TODO: emergency storage
i = size++;
} else i = free_slots.pop();
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

inline bool transfer(size_t i, WearableDatabase &old_db)
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

inline void drop(EntityID wearableID, Inventory& inventory) {
add_entity();
}
// @codegen:end wearable

// @codegen:begin perishable
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
  Array<float> decays;
  Array<PreservationState> preservation_states;

// =========================
// INIT
// =========================

void init(Arena* arena, size_t capacity)
{
  decays = arena_make_array<float>(arena, capacity);
  preservation_states = arena_make_array<PreservationState>(arena, capacity);
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
size_t i;
if (free_slots.empty()) {
//TODO: emergency storage
i = size++;
} else i = free_slots.pop();
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

inline bool transfer(size_t i, PerishableDatabase &old_db)
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

inline void drop(EntityID perishableID, Inventory& inventory) {
add_entity();
}
// @codegen:end perishable

// @codegen:begin container

struct ContainerDatabase {
Database& database;
size_t size = 0;
std::stack<size_t> free_slots;
Array<size_t> indices;

// =========================
// INIT
// =========================

void init(Arena* arena, size_t capacity)
{
}

// =========================
// GETTERS
// =========================


// =========================
// SPAWN
// =========================

void spawn_container_component(Container container, )
{
Item item = item_to_container(container);
size_t i;
if (free_slots.empty()) {
//TODO: emergency storage
i = size++;
} else i = free_slots.pop();
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
     
    }


// =========================
// TRANSFER
// =========================

inline bool transfer(size_t i, ContainerDatabase &old_db)
{
  return database.transfer_item(i, old_db);
}

// =========================
// INVENTORY MANAGEMENT
// =========================

inline void pick_up(EntityID containerID, Inventory& inventory) {
ContainerEntity container = get_entity(index);
Item item = reflect_enum(container.specialization);
inventory.add_item(item);
remove_container(containerID);
}

inline void drop(EntityID containerID, Inventory& inventory) {
add_entity();
}
// @codegen:end container

// @codegen:begin art

struct ArtDatabase {
Database& database;
size_t size = 0;
std::stack<size_t> free_slots;
Array<size_t> indices;

// =========================
// INIT
// =========================

void init(Arena* arena, size_t capacity)
{
}

// =========================
// GETTERS
// =========================


// =========================
// SPAWN
// =========================

void spawn_art_component(Art art, )
{
Item item = item_to_art(art);
size_t i;
if (free_slots.empty()) {
//TODO: emergency storage
i = size++;
} else i = free_slots.pop();
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
     
    }


// =========================
// TRANSFER
// =========================

inline bool transfer(size_t i, ArtDatabase &old_db)
{
  return database.transfer_item(i, old_db);
}

// =========================
// INVENTORY MANAGEMENT
// =========================

inline void pick_up(EntityID artID, Inventory& inventory) {
ArtEntity art = get_entity(index);
Item item = reflect_enum(art.specialization);
inventory.add_item(item);
remove_art(artID);
}

inline void drop(EntityID artID, Inventory& inventory) {
add_entity();
}
// @codegen:end art

// @codegen:begin scavengeable

struct ScavengeableDatabase {
Database& database;
size_t size = 0;
std::stack<size_t> free_slots;
Array<size_t> indices;

// =========================
// INIT
// =========================

void init(Arena* arena, size_t capacity)
{
}

// =========================
// GETTERS
// =========================


// =========================
// SPAWN
// =========================

void spawn_scavengeable_component(Scavengeable scavengeable, )
{
Item item = item_to_scavengeable(scavengeable);
size_t i;
if (free_slots.empty()) {
//TODO: emergency storage
i = size++;
} else i = free_slots.pop();
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
     
    }


// =========================
// TRANSFER
// =========================

inline bool transfer(size_t i, ScavengeableDatabase &old_db)
{
  return database.transfer_item(i, old_db);
}

// =========================
// INVENTORY MANAGEMENT
// =========================

inline void pick_up(EntityID scavengeableID, Inventory& inventory) {
ScavengeableEntity scavengeable = get_entity(index);
Item item = reflect_enum(scavengeable.specialization);
inventory.add_item(item);
remove_scavengeable(scavengeableID);
}

inline void drop(EntityID scavengeableID, Inventory& inventory) {
add_entity();
}
// @codegen:end scavengeable
  
}
