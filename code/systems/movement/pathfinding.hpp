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
#include <world/unit/roles_and_actions.hpp>

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

// RIGHT NOW: PATHS BUFFER currently holds ALL current paths being executed, maintained across frames. however it is fed a NEW 1-1 from new_paths right now. this should not be the case. new_paths should only add NEW things to the path buffer (small subset). path buffer cannot be global. must be same size (and probably owned) by databases. also ensure and consider: a_star is not finding the FINAL destination, but only an intermittent one (unless it happens to be final). the MAX_PATH_SIZE may need to be reduced. checks for final destination need to be done too!
struct PathsBuffer
{
static constexpr size_t ELEMENT_SIZE = sizeof(uint8_t) + sizeof(uint8_t) + sizeof(Coord) + sizeof(PathData);
	size_t size;
	Array<uint8_t> currents; // current index in path
	Array<uint8_t> ends; // index end to intermittent path
//	Array<Coord> destinations; taken from targets in database
	Array<PathData> datas; // currently processed paths up to this point

	Coord pop(size_t i)
	{
		int c = currents[i];
		currents[i]++;
		
		#if !SHIPPING_BUILD
			assert(datas.end < c)
        #endif
		return datas[i].data[c];
	}

		PathsBuffer(Arena* arena, size_t size)
	{
			currents = arena_make_array<uint8_t>(arena, size);
			ends = arena_make_array<uint8_t>(arena, size);
			destinations = arena_make_array<Coord>(arena, size);
			datas = arena_make_array<PathData>(arena, size);
	}
};

struct PathExecution
{
	size_t start_index;
	Coord start;
	uint8_t length;
};

struct NodeData
{
	float g_cost = FLT_MAX;
	float f_cost = FLT_MAX;

	Direction came_direction = Direction::North;
	uint32_t search_id = 0;
	bool closed_flag = false;
};

std::vector<NodeData> node_data;
std::vector<float> tile_move_costs;

float heuristic(Coord a, Coord b) { return std::abs(a.x - b.x) + std::abs(a.y - b.y); }

struct PathDispatchData {
	   
};

struct PathData
{
	Coord start;
	Coord end;

	std::vector<Direction> directions;
};

struct NodeData
{
	float g_cost = FLT_MAX;
	float f_cost = FLT_MAX;

	Direction came_direction;

	uint32_t search_id = 0;
	bool closed_flag = false;
};

PathData a_star(Coord start, Coord goal, int width, int height);

PathData reconstruct_path(int start_index, int goal_index);

std::vector<EntityID> mark_new_path_entities(std::vector<EntityID> &acting_entities,
								Array<FrameData> &frame_datas);

void set_new_paths(std::vector<EntityID>& path_dispatch_buffer, Array<Coord>& coords, Array<Target>& targets, PathsBuffer& pb);
