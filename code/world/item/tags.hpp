#ifndef TAGS_HPP
#define TAGS_HPP
#include <core/fbitset.hpp>
#include <cstdint>

//TODO:: sieve, which can separte sand and clay in, liquids and soil, etc
enum class itemTags : uint16_t {
  NONE = 0,
  Resource = 1 << 0,
  Variant = 1 << 1,
  AlternateRecipes = 1 << 2,
  Liquid = 1 << 3,
  VariableAmountProduced = 1 << 4,
  VariableAmountsRequired = 1 << 5,
  FromCorpse = 1 << 6,
  RequiresUniqueVariant = 1 << 7,
  OptionalIngredient = 1 << 8,
  Mould = 1 << 9,
  Container = 1 << 10,
  // TODO: add flammable tags
  NonFlammable = 1 << 11,
  Wearable = 1 << 12,
  Perishable = 1 << 13,
  WaterDamage = 1 << 14,
};

inline itemTags operator|(itemTags a, itemTags b) {
    return static_cast<itemTags>(
        static_cast<std::underlying_type_t<itemTags>>(a) |
        static_cast<std::underlying_type_t<itemTags>>(b)
    );
}

inline itemTags& operator|=(itemTags& a, itemTags b) {
    a = a | b;
    return a;
}

inline itemTags operator&(itemTags a, itemTags b) {
    return static_cast<itemTags>(
        static_cast<std::underlying_type_t<itemTags>>(a) &
        static_cast<std::underlying_type_t<itemTags>>(b)
    );
}

inline bool hasTag(itemTags value, itemTags tag) {
    return static_cast<std::underlying_type_t<itemTags>>(value & tag) != 0;
}

#endif
