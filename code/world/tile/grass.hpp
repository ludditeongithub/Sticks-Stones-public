#include "enum.hpp"
#include <core/data.hpp>

Hunger GRASS_HUNGER_VALUE = 300;

inline bool tileGrass(TileData tile) { return (tile.second() != Grass::NONE); }

inline void degrassTile(TileData &tile) { tile.second() = Grass::NONE; }
