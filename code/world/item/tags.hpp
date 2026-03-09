#ifndef TAGS_HPP
#define TAGS_HPP
#include <core/fbitset.hpp>
#include <cstdint>

//TODO:: sieve, which can separte sand and clay in, liquids and soil, etc
enum class itemTags : uint16_t {
  NONE = 0,
  Alternate = 1 << 1,
  Liquid = 1 << 2,
  VariableAmountProduced = 1 << 3,
  VariableAmountsRequired = 1 << 4,
  FromCorpse = 1 << 5,
  RequiresUniqueVariant = 1 << 6,
  OptionalIngredient = 1 << 7,
  Mould = 1 << 8,
  Container = 1 << 9,
  // TODO: add flammable tags
  NonFlammable = 1 << 10,
  Wearable = 1 << 11,
  Perishable = 1 << 12,
  WaterDamage = 1 << 13,
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
