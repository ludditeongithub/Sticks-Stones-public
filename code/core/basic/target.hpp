#include <cstdint>

enum class TargetType {
  NONE,
  Animal,
  Forage,
  Unit,
  Tile,
  Structure,
  Station
};

struct Target {
  TargetType type;
  uint32_t index;
};


