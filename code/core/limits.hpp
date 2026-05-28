#ifndef LIMITS_HPP
#define LIMITS_HPP
#include "data.hpp"
#include "entity.hpp"
#include <cstddef>
#include <cstdint>
#include <limits>

constexpr int INT_MAX = std::numeric_limits<int>::max();
constexpr int INT_MIN = std::numeric_limits<int>::min();
constexpr float FLOAT_MAX = std::numeric_limits<float>::max();
constexpr float FLOAT_MIN = std::numeric_limits<float>::min();
constexpr Coord COORD_MAX = {UINT32_MAX, UINT32_MAX};

constexpr EntitySearchData ENTITY_SEARCH_MAX = {SIZE_MAX, COORD_MAX};

#endif
