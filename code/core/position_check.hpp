#include <vector>
#include <cmath>
#include <optional>
#include "data.hpp"
#include "math.hpp"
#include <queue>

float max_alt_change = 2.0;

std::vector<std::pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

template <typename T>
bool is_in_path(const T &map, std::pair<int, int> start, std::pair<int, int> end, const int obstacle)
{
	int dx = abs(end.second - start.second);
	int dy = abs(end.first - start.first);
	int sx = start.second < end.second ? 1 : -1;
	int sy = start.first < end.first ? 1 : -1;
	int err = dx - dy;

	int x = start.second;
	int y = start.first;

	while (true)
	{
		// Check if the current tile matches the condition (e.g., is blocked)
		if (map[y][x] == obstacle)
		{
			return true; // Blocked tile found in the path
		}

		if (x == end.second && y == end.first)
		{
			break; // Reached the end tile
		}

		int e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			x += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y += sy;
		}
	}

	return false; // No blocked tiles in the path
}

bool coords_in_path(std::pair<int, int> start, std::pair<int, int> end, std::pair<int, int> between)
{
	int dx = std::abs(end.second - start.second);
	int dy = std::abs(end.first - start.first);
	int sx = start.second < end.second ? 1 : -1;
	int sy = start.first < end.first ? 1 : -1;
	int err = dx - dy;

	int x = start.second;
	int y = start.first;

	while (true)
	{
		if (y == between.first && x == between.second)
		{
			return true; // Blocked tile found in the path
		}

		if (x == end.second && y == end.first)
		{
			break; // Reached the end tile
		}

		int e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			x += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y += sy;
		}
	}

	return false; // No blocked tiles in the path
}

/* HELPER FUNCTIONS */
bool adj_check(const std::vector<std::vector<int>>& map, int y, int x, int check, int range)
{
	int rows = map.size();	  // height
	int cols = map[0].size(); // width

	for (int r = -range; r <= range; r++)
	{
		for (int c = -range; c <= range; c++)
		{
			if (r == 0 && c == 0)
				continue;

			int nx = x + c;
			int ny = y + r;

			if (abs(r) + abs(c) <= range && nx >= 0 && nx < cols && ny >= 0 &&
			    ny < rows)
			{
				if (map[ny][nx] == check)
				{
					return true;
				}
			}
		}
	}
	return false;
}

template <typename L, typename M, typename T>
bool adj_check(L &reference_map, M &map, int y, int x, T check, int range)
{
	for (int r = -range; r <= range; r++)
	{
		for (int c = -range; c <= range; c++)
		{
			if (r == 0 && c == 0)
				continue;

			int nx = x + c;
			int ny = y + r;
			if (reference_map.find({ny, nx}) != reference_map.end())
			{
				int index = reference_map.at({ny, nx});
				auto item = map[index];

				if (abs(r) + abs(c) <= range && nx >= 0)
				{
					if (item == check)
					{
						return true;
					}
				}
			}
		}
	}
	return false;
}

bool adj_check_object(int first_index, int second_index, bool first_animal, bool second_animal, std::vector<std::pair<int,int>>& animal_coords, std::vector<std::pair<int, int>>& current_coords)
{
	std::pair<int, int> fc, sc;
	if (first_animal)
		fc = animal_coords[first_index];
	else
		fc = current_coords[first_index];
	if (second_animal)
		sc = animal_coords[second_index];
	else
		sc = current_coords[first_index];
	
	if ((abs(fc.first - sc.first) == 1 || abs(fc.first - sc.first) == 0) &&
	    (abs(fc.second - sc.second) == 0 || abs(fc.second - sc.second) == 1))
		return true;
	return false;
}

// TODO: check to see if this makes sense returns nullptr if not adjacent
std::optional<Direction> adj_check_tile(std::pair<int, int> subject, std::pair<int, int> target)
{
	if (manhattan_dist(subject, target) > 1)
		return std::nullopt;
	if (subject.first - target.first == 1)
		return std::make_optional<Direction>(Direction::East);
	if (subject.first - target.first == -1)
		return std::make_optional<Direction>(Direction::West);
	if (subject.second - target.second == 1)
		return std::make_optional<Direction>(Direction::North);
	if (subject.second - target.second == -1)
		return std::make_optional<Direction>(Direction::South);
	return std::nullopt;
}

template <typename L, typename M, typename Container>
bool adj_check_list(L &reference_map, M &map, int y, int x, const Container &check, int range)
{
	for (int r = -range; r <= range; r++)
	{
		for (int c = -range; c <= range; c++)
		{
			if (r == 0 && c == 0)
				continue;

			int nx = x + c;
			int ny = y + r;
			if (reference_map.find({ny, nx}) != reference_map.end())
			{
				int index = reference_map.at({ny, nx});
				auto item = map[index];

				if (abs(r) + abs(c) <= range && nx >= 0)
				{
					for (const auto &check_item : check)
					{
						if (item == check_item)
						{
							return true;
						}
					}
				}
			}
		}
	}
	return false;
}

template <typename L, typename M, typename Container>
int adj_check_list_count(L &reference_map, M &map, int y, int x, const Container &check, int range)
{
	int count = 0;
	for (int r = -range; r <= range; r++)
	{
		for (int c = -range; c <= range; c++)
		{
			if (r == 0 && c == 0)
				continue; // Skip the center tile

			int nx = x + c;
			int ny = y + r;
			if (reference_map.find({ny, nx}) != reference_map.end())
			{
				int index = reference_map.at({ny, nx});
				auto item = map[index];

				if (abs(r) + abs(c) <= range && nx >= 0)
				{
					for (const auto &check_item : check)
					{
						if (item == check_item)
						{
							count++;
						}
					}
				}
			}
		}
	}
	return count;
}

// returns the closest adjacent tile of check type
std::pair<int, int> adj_get(vector<vector<int>> &map, int y, int x, int check, int range)
{
	int rows = map.size();
	int cols = map[0].size();
	std::pair<int, int> adj = {x, y}; // return original coords if none in range

	for (int r = -range; r <= range; r++)
	{
		for (int c = -range; c <= range; c++)
		{
			if (r == 0 && c == 0)
				continue; // Skip the center tile

			int nx = x + c;
			int ny = y + r;

			// Ensure we're checking only directly adjacent tiles within the range
			if (abs(r) + abs(c) <= range && nx >= 0 && nx < rows && ny >= 0 &&
			    ny < cols)
			{
				if (map[ny][nx] == check)
				{
					// cout << adj.first << "," << adj.second << ";";
					adj = {ny, nx};
					return adj;
				}
			}
		}
	}
	return adj;
}

int adj_range(const std::vector<std::vector<int>> &map, int y, int x, int check)
{
	int rows = map.size(), cols = map[0].size();
	std::vector<std::pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
	std::queue<std::pair<int, int>> q;
	std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));
	q.push({y, x});
	visited[y][x] = true;

	while (!q.empty())
	{
		int current_x = q.front().second, current_y = q.front().first;
		q.pop();
		for (const auto &dir : directions)
		{
			int nx = current_x + dir.second, ny = current_y + dir.first;
			if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && !visited[ny][nx])
			{
				visited[ny][nx] = true;
				if (map[ny][nx] == check)
					return abs(ny - y) + abs(nx - x);
				q.push({ny, nx});
			}
		}
	}
	return -1;
}

// returns all adjacent tiles of type, and distance
std::vector<std::tuple<int, int, int>> adj_get_all(vector<vector<int>> &map, int y, int x, int check,
						 int range)
{
	int rows = map.size();
	int cols = map[0].size();
	std::vector<std::tuple<int, int, int>> tiles;

	for (int r = -range; r <= range; r++)
	{
		for (int c = -range; c <= range; c++)
		{
			if (r == 0 && c == 0)
				continue; // Skip the center tile

			int nx = x + c;
			int ny = y + r;

			// Ensure we're checking only directly adjacent tiles within the range
			if (abs(r) + abs(c) <= range && nx >= 0 && nx < rows && ny >= 0 &&
			    ny < cols)
			{
				if (map[ny][nx] == check)
				{
					// cout << adj.first << "," << adj.second << ";";
					tiles.push_back({ny, nx, chebyshev(y, x, ny, nx)});
				}
			}
		}
	}
	return tiles;
}

// adds corner adjacent tiles to adj_check
bool diag_adj_check(std::vector<std::vector<int>> &map, int y, int x, int check, int range)
{
	int rows = map.size();
	int cols = map[0].size();

	for (int r = -range; r <= range; r++)
	{
		for (int c = -range; c <= range; c++)
		{
			if (r == 0 && c == 0)
				continue; // Skip the center tile

			int nx = x + r;
			int ny = y + c;

			// Ensuring only diagonal or directly adjacent tiles are checked
			if (fmax(abs(r), abs(c)) <= range && nx >= 0 && nx < rows && ny >= 0 &&
			    ny < cols)
			{
				if (map[ny][nx] == check)
				{
					return true;
				}
			}
		}
	}
	return false;
}

// gets adjacent tile with lowest value
std::pair<int, int> get_lowest_adj(std::vector<std::vector<int>> &map, int y, int x)
{
	int dx[] = {-1, 0, 1, 0}; // x-direction for up/down
	int dy[] = {0, 1, 0, -1}; // y-direction for left/right
	int lowest = RAND_MAX;
	std::pair<int, int> ret;

	for (int i = 0; i < 4; i++)
	{
		int nx = x + dx[i];
		int ny = y + dy[i];

		// Check if within bounds
		if (nx >= 0 && nx < map.size() && ny >= 0 && ny < map[0].size())
		{
			if (map[ny][nx] < lowest)
			{
				lowest = map[ny][nx];
				ret = {ny, nx};
			}
		}
	}
	return ret;
}

// gets adjacent tile with highest value
std::pair<int, int> get_highest_adj(std::vector<std::vector<int>> &map, int y, int x)
{
	int dx[] = {-1, 0, 1, 0}; // x-direction for up/down
	int dy[] = {0, 1, 0, -1}; // y-direction for left/right
	int highest = -9999999;
	std::pair<int, int> ret;

	for (int i = 0; i < 4; i++)
	{
		int nx = x + dx[i];
		int ny = y + dy[i];
		// Check if within bounds
		if (nx >= 0 && nx < map.size() && ny >= 0 && ny < map[0].size())
		{
			if (map[ny][nx] > highest)
			{
				highest = map[ny][nx];
				ret = {ny, nx};
			}
		}
	}
	return ret;
}

int get_lowest_adj_value(vector<vector<int>> &map, int y, int x)
{
	int dx[] = {-1, 0, 1, 0}; // x-direction for up/down
	int dy[] = {0, 1, 0, -1}; // y-direction for left/right
	int lowest = RAND_MAX;

	for (int i = 0; i < 4; i++)
	{
		int nx = x + dx[i];
		int ny = y + dy[i];

		// Check if within bounds
		if (nx >= 0 && nx < map.size() && ny >= 0 && ny < map[0].size())
		{
			if (map[ny][nx] < lowest)
			{
				lowest = map[ny][nx];
			}
		}
	}
	return lowest;
}

int get_highest_adj_value(vector<vector<int>> &map, int y, int x)
{
	int dx[] = {-1, 0, 1, 0}; // x-direction for up/down
	int dy[] = {0, 1, 0, -1}; // y-direction for left/right
	int highest = -9999999;

	for (int i = 0; i < 4; i++)
	{
		int nx = x + dx[i];
		int ny = y + dy[i];

		// Check if within bounds
		if (nx >= 0 && nx < map.size() && ny >= 0 && ny < map[0].size())
		{
			if (map[ny][nx] > highest)
			{
				highest = map[ny][nx];
			}
		}
	}
	return highest;
}

template <typename T> void transform_adj(T &map, int y, int x, int transform, float chance)
{
	int dx = -1;
	int dy = 0;
	if (rand() / (float)RAND_MAX < chance)
	{
		map[x + dx][y + dy] = transform;
	}
	dx = 1;
	if (rand() / (float)RAND_MAX < chance)
	{
		map[x + dx][y + dy] = transform;
	}
	dy = -1;
	dx = 0;
	if (rand() / (float)RAND_MAX < chance)
	{
		map[x + dx][y + dy] = transform;
	}
	dy = -1;
	if (rand() / (float)RAND_MAX < chance)
	{
		map[x + dx][y + dy] = transform;
	}
}

template <typename T> void adjust_adj(T &map, int y, int x, int adjustment)
{
	int dx = -1;
	int dy = 0;
	map[x + dx][y + dy] += adjustment;
	dx = 1;
	map[x + dx][y + dy] = adjustment;
	dy = -1;
	dx = 0;
	map[x + dx][y + dy] = adjustment;
	dy = -1;
	map[x + dx][y + dy] = adjustment;
}

bool check_empty_tile(int tile_index, int adjacent_tile_index)
{
	if (tile_water[tile_index])
		return false;
	if (tile_alt[tile_index] > tile_alt[adjacent_tile_index] + max_alt_change ||
	    tile_alt[tile_index] < tile_alt[adjacent_tile_index] - max_alt_change)
		return false;
	if (Plant *p_ptr = std::get_if<Plant>(&tile_object[tile_index]))
		if (*p_ptr != Plant::NONE)
			return false;
	if (Scavengeable *s_ptr = std::get_if<Scavengeable>(&tile_object[tile_index]))
		if (*s_ptr != Scavengeable::NONE)
			return false;
	if (Item *i_ptr = std::get_if<Item>(&tile_object[tile_index]))
		if (*i_ptr != Item::NONE)
			return false;
	if (Buildable *b_ptr = std::get_if<Buildable>(&tile_object[tile_index]))
		if (*b_ptr != Buildable::NONE)
			return false;
	if (Animal *a_ptr = std::get_if<Animal>(&tile_object[tile_index]))
		if (*a_ptr != Animal::NONE)
			return false;
	if (Vehicle *v_ptr = std::get_if<Vehicle>(&tile_object[tile_index]))
		if (*v_ptr != Vehicle::NONE)
			return false;
	if (object_to_int(tile_object[tile_index]) != 0)
		return false;
}

std::pair<int, int> get_adjacent_tile(int tile_index, Direction direction)
{
	adjacent_tiles_indices[tile_index];
	if (direction == Direction::North)
		return if (direction == Direction::South) if (direction ==
							      Direction::West) if (direction ==
										   Direction::East)
}

Direction get_random_adj_direction(Direction direction)
{
	if (direction == Direction::North)
	{
		if (rbool())
			return Direction::East;
		return Direction::West;
	}
	if (direction == Direction::South)
	{
		if (rbool())
			return Direction::East;
		return Direction::West;
	}
	if (direction == Direction::West)
	{
		if (rbool())
			return Direction::North;
		return Direction::South;
	}
	if (rbool())
		return Direction::North;
	return Direction::South;
}

void move_in_direction(&std::pair<int, int> coord, Direction direction)
{
	if (direction == Direction::North)
		coord.second += 1;
	else if (direction == Direction::South)
		coord.second -= 1;
	if (direction == Direction::East)
		coord.first += 1;
	else if (direction == Direction::West)
		coord.second -= 1;
}

std::pair<int, int> get_nearest_empty_tile(int start_index)
{
	std::queue<int> q;
	std::unordered_set<int> visited;

	q.push(start_index);
	visited.insert(start_index);

	while (!q.empty())
	{
		int current = q.front();
		q.pop();

		auto [above, right, below, left] = adjacent_tiles_indices[current];
		std::array<int, 4> neighbors = {above, right, below, left};

		for (int neighbor : neighbors)
		{
			if (neighbor < 0 || visited.count(neighbor))
				continue;

			if (check_empty_tile(current, neighbor))
			{
				return tile_coords[neighbor]; // Found nearest empty tile
			}

			visited.insert(neighbor);
			q.push(neighbor);
		}
	}

	return {-1, -1}; // No empty tile found
}

int get_nearest_adjacent_empty_tile_index(int start_index)
{
	std::queue<int> q;
	std::unordered_set<int> visited;

	q.push(start_index);
	visited.insert(start_index);

	while (!q.empty())
	{
		int current = q.front();
		q.pop();

		auto [above, right, below, left] = adjacent_tiles_indices[current];
		std::array<int, 4> neighbors = {above, right, below, left};

		for (int neighbor : neighbors)
		{
			if (neighbor < 0 || visited.count(neighbor))
				continue;

			if (check_empty_tile(current, neighbor))
			{
				return neighbor; // Found nearest empty tile
			}

			visited.insert(neighbor);
			q.push(neighbor);
		}
	}

	return -1; // No empty tile found
}

struct TileBlock()
{
	std::pair<int, int> start_tile;
	uint8_t block_size;
	Direction direction;
}

TileBlock
get_nearest_adjacent_empty_tile_block(int start_index, uint8_t block_size)
{
	std::queue<int> q;
	std::unordered_set<int> visited;
	Direction direction;

	q.push(start_index);
	visited.insert(start_index);

	while (!q.empty())
	{
		int current = q.front();
		q.pop();

		auto [above, right, below, left] = adjacent_tiles_indices[current];
		std::array<int, 4> neighbors = {above, right, below, left};

		for (int neighbor : neighbors)
		{
			if (neighbor < 0 || visited.count(neighbor))
				continue;

			if (check_empty_tile(current, neighbor))
			{
				// Found an empty tile, now check for a block of adjacent empty
				// tiles
				int count = 1; // Start with the current empty tile
				// Check horizontal and vertical directions for contiguous empty
				// tiles

				// Check to the right
				int temp = neighbor;
				while (check_empty_tile(current, temp) && visited.count(temp) == 0)
				{
					count++;
					visited.insert(temp);
					temp = right; // move right
					direction = west;
				}

				// Check to the left
				temp = neighbor;
				while (check_empty_tile(current, temp) && visited.count(temp) == 0)
				{
					count++;
					visited.insert(temp);
					temp = left; // Move left
					direction = east;
				}

				// Check above
				temp = neighbor;
				while (check_empty_tile(current, temp) && visited.count(temp) == 0)
				{
					count++;
					visited.insert(temp);
					temp = above; // Move above
					direction = north;
				}

				// Check below
				temp = neighbor;
				while (check_empty_tile(current, temp) && visited.count(temp) == 0)
				{
					count++;
					visited.insert(temp);
					temp = below; // Move below
					direction = south;
				}

				// If count meets or exceeds required count of adjacent empty tiles
				if (count >= block_size)
				{
					return {tile_coords[neighbor], block_size, direction};
				}
			}
			visited.insert(neighbor);
			q.push(neighbor);
		}
	}
	return {-1, -1}; // No empty tile block found
}

// int get_speed(Animal animal) {
//     switch (animal) {
//         Pig, Cow, Chicken, Duck, Sheep, Goat, Horse, Ox, Donkey, Camel, WaterBuffalo, Rabbit,
//         Antelope, Deer, Moose, Capybara, Turtle, Elephant, Bison, Wolf, Bear, Caribou, Fish,
//     }
// }

int get_seed_index(int y, int x, int length) { return y * length + x; }

int calculate_distance(int y, int x, const std::pair<int, int> &target)
{
	return std::abs(x - target.first) + std::abs(y - target.second);
}

struct Node
{
	int index;
	uint8_t move_cost; // The cost of moving to this node
	uint8_t f_cost;	  // f_cost = g_cost + heuristic
	Node *parent;	  // Parent node for path reconstruction

	Node(int index, uint8_t move_cost, uint8_t f_cost, Node *parent = nullptr)
	    : index(index), move_cost(move_cost), f_cost(f_cost), parent(parent)
	{
	}

	bool operator>(const Node &other) const { return f_cost > other.f_cost; }
};

uint16_t man_dist(int x1, int y1, int x2, int y2) { return std::abs(x1 - x2) + std::abs(y1 - y2); }

uint16_t man_dist(std::pair<int, int> x, std::pair<int, int> y)
{
	return std::abs(x.first - y.first) + std::abs(x.second - y.second);
}

inline bool within(Coord subject, Coord border_top_left_corner, Coord border_dimensions)
{
	if (subject.x <= border_top_left_corner.x + border_dimensions.x && subject.y <= border_top_left_corner.y + border_dimensions.y && subject.x > border_top_left_corner.x && subject.y > border_top_left_corner.y) return true;
	return false;
}	

// returns pair of index, cost to new path vector
// std::vector<std::pair<int, int>> greedy_path(int start_index, int end_index) {
//     int start_x = tile_coords[start_index].first;
//     int start_y = tile_coords[start_index].second;

//     int goal_x = tile_coords[end_index].first;
//     int goal_y = tile_coords[end_index].second;
//     std::priority_queue<Node, std::vector<Node>, std::greater<Node>> open_set;
//     std::unordered_map<int, bool> visited;

//     // Start with the initial node, no parent (null)
//     open_set.push(Node(start_x, start_y, 0, man_distance(start_x, start_y, goal_x, goal_y), nullptr));

//     std::vector<std::pair<std::pair<int, int>, int>> path;

//     while (!open_set.empty()) {
//         Node current = open_set.top();
//         open_set.pop();

//         int index = current.index;
//         int cost = current.move_cost;

//         if (tile_coords[index].first == goal_x && tile_coords[index].second == goal_y) {
//             // reconstruct the path by backtracking from goal to start
//             while (current.parent != nullptr) {
//                 path.push_back(index, cost);
//                 current = *current.parent;
//                 index = current.index
//             }
//             path.push_back(index, 0);
//             std::reverse(path.begin(), path.end()); // Reverse the path to get the correct order
//             break;
//         }

//         if (visited(index)) continue;
//         visited(index) = true;

//         for (int i = 0; i < 4; ++i) {;
//             if (i == 0) std::pair<int,int> mt = get_move_time_and_tile_index(Direction::Up);
//             if (i == 1) std::pair<int,int> mt = get_move_time_and_tile_index(Direction::Down);
//             if (i == 2) std::pair<int,int> mt = get_move_time_and_tile_index(Direction::Left);
//             if (i == 3) std::pair<int,int> mt = get_move_time_and_tile_index(Direction::Right);

//             uint8_t move_cost = mt.first;
//             int new_index = mt.second;

//             if (new_index == -1) continue;
//             if (visited(new_index)) continue;
//             uint8_t new_man_dist = man_dist(tile_coords[index].first, tile_coords[index].second,
//             goal_x, goal_y); open_set.push(Node(new_index, move_cost, move_cost + new_man_dist,
//             &current));
//         }
//     }
//     return path;
// }

// use to estimate when object will arrive at target
//  int time_to_dest_estimator(bool min, int subject_index, int target_index, bool subject_animal, bool
//  target_animal) {
//          if (target_animal) {
//          std::pair<int,int> target_coord = animal_coords[target_index];
//      } else std::pair<int,int> target_coord = current_coords[target_index];

//     if (subject_animal) {
//         std::pair<int,int> subject_coord = animal_coords[subject_index];
//         Animal animal = animals[subject_index];
//     } else std::pair<int,int> subject_coord = current_coords[target_index];

//     int dist = man_dist(subject_coord.first, subject_coord.second, target_coord.first,
//     target_coord.second); if (subject_animal) dist *= get_speed(animal); return dist;
// }

// void move_animal(vector<std::pair<int,int> path, int animal_index) {
//  	std::pair<int,int>& subject_coords = animal_coords[animal_index];
//     Animal animal = animals[animal_index];

//     int next_tile_move_time = 0;
//     for (int i = 0; i < path.size(); i++) {
//         next_tile_move_time += path[i].second * get_speed(animal);
//         add_event(next_tile_move_time, EventType::AnimalMoveTile, animal_index, path[i].first);
//     }
// }

// void move_pawn(vector<std::pair<int,int> path, int pawn_index) {
//  	std::pair<int,int>& subject_coords = current_coords[pawn_index];
//     int next_tile_move_time = 0;
//     for (int i = 0; i < path.size(); i++) {
//         next_tile_move_time += path[i].second;
//         add_event(next_tile_move_time, EventType::PawnMoveTile, pawn_index, path[i].first);
//     }
// }

// void move_animal(int object_index, int dest_coord_index) {
//     std::pair<int, int> ec = animal_coords[object_index];
//     vector<std::pair<std::pair<int,int>, int>> path = greedy_path(ec, dest_coord_index);
//     move_animal(path, object_index);
// }

// void move_pawn(int object_index, int dest_coord_index) {
//     std::pair<int, int> ec = animal_coords[object_index];
//     std::pair<int, int> ec = current_coords[object_index];

//     vector<std::pair<std::pair<int,int>, int>> path = greedy_path(ec, dest_coord_index);
//     move_pawn(path, object_index);
// }

// //TODO: consider making the move tile events directional
// void move_animal(int object_index, int dest_coord_index, DelayedEvent event) {
//     std::pair<int, int> ec = animal_coords[object_index];
//     vector<std::pair<std::pair<int,int>, int>> path = greedy_path(ec, dest_coord_index);
//     Animal animal = animals[animal_index];

//     int next_tile_move_time = 0;
//     for (int i = 0; i < path.size(); i++) {
//         next_tile_move_time += path[i].second * get_speed(animal);
//         add_event(next_tile_move_time, EventType::AnimalMoveTile, object_index, path[i].first);
//     }
//     add_event(next_tile_move_time + 1, event, object_index);
// }

// void move_pawn(int object_index, int dest_coord_index, DelayedEvent event) {
//     std::pair<int, int> ec = animal_coords[object_index];
//     vector<std::pair<std::pair<int,int>, int>> path = greedy_path(ec, dest_coord_index);

//     int next_tile_move_time = 0;
//     for (int i = 0; i < path.size(); i++) {
//         next_tile_move_time += path[i].second;
//         add_event(next_tile_move_time, EventType::PawnMoveTile, object_index, path[i].first);
//     }
//     add_event(next_tile_move_time + 1, event, object_index);
// }

// moves a certain object until it is adjacent with another object and facing it.
//  void meet(int finder_index, int target_index, bool finder_animal, bool target_animal, DelayedEvent
//  meet_type) {
//      if (finder_animal) std::pair<int, int> fc = animal_coords[finder_index];
//      else std::pair<int, int> fc = current_coords[finder_index];
//      if (target_animal) std::pair<int, int> tc = animal_coords[target_index];
//      else std::pair<int, int> tc = current_coords[target_index];

//     //TODO: if hunting, give up if animal is faster and not asleep or injured

//     vector<std::pair<std::pair<int,int>, int>> path = greedy_path(tile_indices(fc),
//     tile_indices(tc)); if (finder_animal) move_animal(path, animal_index); else move_pawn(path,
//     pawn_index);

//     int time = time_to_dest_estimator(finder_index, target_index, finder_animal, target_animal);
//     if (finder_animal) {
//         if (target_animal) {
//             add_event(time, EventType::CheckIfAdjacentAnimals, static_cast<int>(meet_type),
//             finder_index, target_index);
//         } else add_event(time, EventType::CheckIfAdjacentAnimalToPawn, static_cast<int>(meet_type),
//         finder_index, target_index);
//     } else {
//         if (target_animal) {
//             add_event(time, EventType::CheckIfAdjacentPawnToAnimal,
//             static_cast<int>(meet_type),finder_index, target_index);
//         } else add_event(time, EventType::CheckIfAdjacentPawns, static_cast<int>(meet_type),
//         finder_index, target_index);
//     }
//     //TODO:fix and face entities
// }
