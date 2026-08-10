#ifndef PERISHABLES_HPP
#define PERISHABLES_HPP
#include "enum.hpp"
#include <core/data.hpp>
#include <core/tables.hpp>

constexpr float FROZEN_TIME_MULT = 0.005;
constexpr float FRIDGE_TIME_MULT = 0.08;
constexpr float STANDARD_TIME_MULT = 1.00;
constexpr float HOT_TIME_MULT = 1.85;

// @codegen:begin specialization
enum class Perishable {
  Flour,
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

inline void PerishableDatabase::pick_up(EntityID perishableID, Inventory& inventory) {
PerishableEntity perishable = get_entity(index);
Item item = reflect_enum(perishable.specialization);
inventory.add_item(item);
remove_perishable(perishableID);
}

inline void PerishableDatabase::drop(EntityID perishableID, Inventory& inventory) {
add_entity();
}
// @codegen:end specialization


#endif
