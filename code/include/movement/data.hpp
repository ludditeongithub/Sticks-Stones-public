#include <cstdint>
#include <basic/coord.hpp>
#include <tile/data.hpp>
#include <math.h>
#include <vector>

namespace movable {

// CONSTANTS
constexpr int MAX_PATH_SIZE = 256; 
constexpr uint16_t SENTINEL = 65535;
constexpr uint32_t PATH_QUEUE_SIZE = 10000;

// HOT
struct Entity {
  Coord c;
  Direction d;
};

struct PathExecution {
  uint16_t startIndex;
  Coord start;
  uint8_t length;
};

struct Pathfinding {
  std::vector<uint16_t> gCost;
  std::vector<uint16_t> fCost;
  std::vector<uint16_t> parents;
  std::vector<bool> openFlag;
  std::vector<bool> closedFlag;

  std::priority_queue<int> pq;

void initializePathfindingData(uint16_t s) {
  gCost.resize(s);
  fCost.resize(s);
  parents.resize(s);
  openFlag.resize(s);
  closedFlag.resize(s);
}


  

}
