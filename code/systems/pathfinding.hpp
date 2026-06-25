#include "core/data.hpp"
#include "core/memory.hpp"
#include "schedule/dispatch.hpp"
#include <core/containers.hpp>
#include <core/math.hpp>
#include <cstdint>
#include <limits>
#include <math.h>
#include <stdexcept>
#include <vector>
#include <world/tile/data.hpp>
#include <world/unit/rolesAndActions.hpp>

// CONSTANTS
constexpr int MAX_PATH_SIZE = 45;
constexpr int NEW_PATH_DIST = 3;
constexpr uint32_t PATH_QUEUE_SIZE = 10000;

// HOT
struct Entity
{
	Coord c;
	Direction d;
};

struct PathsBuffer
{
	static constexpr size_t elementSize = (sizeof(uint8_t) * 2 + sizeof(Coord) * 2);
	size_t size;
	Array<uint8_t> currents;
	Array<uint8_t> ends;
	Array<Coord> destinations;
	Array2D<Coord> datas;

	Coord pop(size_t i)
	{
		int c = currents[i];
		currents[i]++;
		return datas[i][c];
	}

	PathsBuffer(Arena& arena, size_t size)
	{
			currents = arena_make_array<uint8_t>(arena, size);
			ends = arena_make_array<uint8_t>(arena, size);
			destinations = arena_make_array<Coord>(arena, size);
			datas = arena_make_2d_array<Coord>(arena, MAX_PATH_SIZE, size);
	}
};

struct PathExecution
{
	size_t startIndex;
	Coord start;
	uint8_t length;
};

struct NodeData
{
	float gCost = std::numeric_limits<float>(max);
	float fCost = std::numeric_limits<float>(max);
	int cameFrom = -1;
	bool closedFlag = false;
};

std::vector<NodeData> nodeData;
std::vector<float> tileMoveCosts;

int toIndex(int x, int y, int width) { return y * width + x; }

float heuristic(Coord a, Coord b) { return std::abs(a.x - b.x) + std::abs(a.y - b.y); }

struct PathData
{
	Array<Coord> data;
	uint8_t end;
};

PathData aStar(Coord start, Coord goal, int width, int height);

Array<Coord> reconstructPath(int startIndex, int goalIndex);

PathsBuffer getAnimalNewPaths(PathDispatchData &pdd);
