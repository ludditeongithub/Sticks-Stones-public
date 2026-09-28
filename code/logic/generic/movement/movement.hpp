#pragma once

#include "data/types/entity.hpp"
#include "logic/gameplay/action/action.hpp"
#include <data/run/tile_database.hpp>
#include <logic/generic/movement/pathfinding.hpp>

// =========================
// CONTINUOUS
// =========================

void update_positions(PathsBuffer& paths_buffer, Array<Coord> &positions, Array<Frame>& inertias, Array<Action> &actions, Array<EntityID> &require_new_path_indices);

// =========================
// EVENT
// =========================

template <typename DB> inline void move(DB &database, EntityID i, const Direction direction);
template<typename DB> inline void set_next_move_inertia(DB& database, tile::Database& tiles, EntityID i, const Coord coord);
void set_next_movement_inertia();

// =========================
// ACTION MOVEMENT (prowling, approaching)
// =========================

// =========================
// MAIN
// =========================

void process_movement();
