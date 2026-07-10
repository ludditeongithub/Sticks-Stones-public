#pragma once
#include <core/data.hpp>
#include <world/tile/database.hpp>
// =========================
// CONTINUOUS
// =========================



// =========================
// EVENT
// =========================

template <typename DB> inline void move(DB &database, EntityID i, const Direction direction);
template<typename DB> inline void setNextMoveInertia(DB& database, TileDatabase& tiles, EntityID i, const Coord coord);
void setNextMovementInertia();

