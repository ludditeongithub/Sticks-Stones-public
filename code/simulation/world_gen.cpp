#include "world_gen.hpp"
#include <queue>
#include <core/position_check.hpp>

// TO-DO: refactor all code to use adjacent tiles based on nearest Voronoi
// seeds, not square cells

// 1. Generate Ocean on altitude, land, and ocean maps
void WorldSpawner::generate_oceans_on_maps()
{
	for (int x = 0; x < WIDTH; ++x)
	{
		for (int y = 0; y < HEIGHT; ++y)
		{
			if (altitude_map[y][x] > land_threshold)
			{
				ocean_map[y][x] = 1; // Land
				lands_map[y][x] = 2; // Land
			}
			else
			{
				ocean_map[y][x] = 0; // Ocean
				lands_map[y][x] = 0; // Ocean
				altitude_map[y][x] = 0;
			}
		}
	}
}

// Function to mark adjacent tiles to coast as lowlands
void WorldSpawner::mark_coasts()
{
	for (int x = 0; x < WIDTH; ++x)
	{
		for (int y = 0; y < HEIGHT; ++y)
		{
			if (ocean_map[y][x] == 1)
			{ // Land
				if (adj_check(ocean_map, y, x, 0, 1))
				{
					lands_map[y][x] = 1; // Coast
				}
			}
		}
	}
}

// Function to apply user-defined chances for unlikely transitions
void WorldSpawner::apply_extra_highlands_and_mountains()
{
	// Step 1: Transition one tile to other tile
	for (int y = 0; y < HEIGHT; ++y)
	{
		for (int x = 0; x < WIDTH; ++x)
		{
			int lowest = get_lowest_adj_value(lands_map, x, y);
			float threshold;
			switch (lowest)
			{
			case 5:
				threshold = 0.4f;
				break;
			case 4:
				threshold = 0.10f;
				break;
			case 3:
				threshold = 0.04f;
				break;
			case 2:
				threshold = 0.003f;
				break;
			default:
				threshold = -1.0f;
			}
			float rand_val = rand() / (float)RAND_MAX;
			if (rand_val < threshold)
			{
				lands_map[y][x] = 5; // Mountains
			}
		}
	}

	// Step 2: Apply highlands, mountains swaths
	for (int y = 0; y < HEIGHT; ++y)
	{
		for (int x = 0; x < WIDTH; ++x)
		{
			if (lands_map[y][x] == 5)
			{
				int success;
				int backup;
				float chance;
				int l;
				int s;

				if (lands_map[y][x] == 5)
				{
					success = 5;
					int highest = get_highest_adj_value(lands_map, y, x);
					int lowest = get_lowest_adj_value(lands_map, y, x);
					backup = highest;
					switch (lowest)
					{
					case 5:
						chance = 0.6f;
						break;
					case 4:
						chance = 0.2f;
						break;
					case 3:
						chance = 0.03f;
						break;
					case 2:
						chance = 0.005f;
						break;
					default:
						chance = 0.0f;
					}
					l = r1_to5.next();
					s = r1_to2.next();
				}
				else
				{
					success = 4;
					backup = 3;
					chance = 0.3;
					l = r1_to4.next();
					s = r1_to3.next();
				}
				std::pair<int, int> change = get_highest_adj(lands_map, y, x);
				int nx = change.second;
				int ny = change.first;

				// Random chance which determines if highlands range is deleted or
				// expanded
				if (rand() / (float)RAND_MAX < chance)
				{
					for (int i = 0; i < l; i++)
					{
						for (int j = 0; j < s; j++)
						{
							if (nx >= 0 && nx < WIDTH && ny >= 0 &&
							    ny < HEIGHT)
							{
								// Bounds check
								if ((rand() / (float)RAND_MAX) >
								    0.8)
									lands_map[nx][ny] = success;
							}
						}
					}
				}
				else
				{
					lands_map[ny][nx] = backup;
				}
			}
		}
	}

	// Step 3: Apply coastal mountains chance
	for (int y = 0; y < HEIGHT; ++y)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			if (lands_map[y][x] != 0 && lands_map[y][x] != 1)
			{
				std::pair<int, int> near = adj_get(lands_map, y, x, 1, 3);
				std::pair<int, int> current = {y, x};
				if (near != current)
				{
					if (rchance.next() < coastal_range_chance)
					{
						lands_map[y][x] = 5; // Mountain
						int size = r1_to4 + 3;
						for (int i = 0; i < size; i++)
						{
							// get nearest lowlands
							std::pair<int, int> near2 =
							    adj_get(lands_map, y, x, 2, 1);
							int nx = near2.second;
							int ny = near2.first;
							// check to ensure new lowlands tile is
							// close to coast
							if (adj_check(lands_map, ny, nx, 1, 3) ==
								true &&
							    lands_map[nx][ny] != 0 &&
							    lands_map[nx][ny] != 1)
								lands_map[ny][nx] = 5; // Mountain
							y = ny;
							x = nx;
						}
					}
				}
				// increase mt altitude
				if (lands_map[y][x] == 5)
				{
					if (!adj_check(lands_map, y, x, 1, 1) &&
					    !adj_check(lands_map, y, x, 1, 2) &&
					    !adj_check(lands_map, y, x, 1, 3))
					{
						altitude_map[y][x] =
						    30 + (rand() / (float)RAND_MAX) * 30;
					}
					else
					{
						altitude_map[y][x] =
						    20 + (rand() / (float)RAND_MAX) * 20;
					}
				}
			}
		}
	}
}

void WorldSpawner::generate_lands_map()
{
	mark_coasts();
	for (int x = 0; x < WIDTH; ++x)
	{
		for (int y = 0; y < HEIGHT; ++y)
		{
			if (ocean_map[y][x] == 1 && lands_map[y][x] != 1)
			{
				if (altitude_map[y][x] < lowlands_threshold)
				{
					lands_map[y][x] = 2;
				}
				else if (altitude_map[y][x] < midlands_threshold)
				{
					lands_map[y][x] = 3;
				}
				else
				{
					lands_map[y][x] = 4;
				}
			}
		}
	}
	apply_extra_highlands_and_mountains();
}

// TODO: make river
void WorldSpawner::extend_rivers_from_source(uint16_t river_length, int x, int y)
{
	// Base case 1: Hits the edge of the map
	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
	{
		return;
	}

	// Base case 2: Tile is r_visited
	if (r_visited[y][x])
	{
		return;
	}

	r_visited[y][x] = true;

	// Base case 3: Hits an ocean tile
	if (water_map[y][x] == 0 || water_map[y][x] == 4)
	{
		water_map[y][x] = 4;
		return;
	}

	// Base case 4: Chance of stopping if lake condition is met
	if (get_lowest_adj_value(altitude_map, y, x) > altitude_map[y][x])
	{
		water_map[y][x] = 5;
		float random = rand() % 100;
		// 60% chance of stopping when adjacent tiles are not lower, and 20% of no
		// lake
		if ((random < 70))
			return;
		else if ((random < 80))
		{
			water_map[y][x] = 7; // Mark as groundwater river end
			return;
		}
	}

	// Base case 5: stops if natural river end
	if (water_map[y][x] == 7)
	{
		return;
	}

	int dx[] = {-1, 0, 1, 0};
	int dy[] = {0, 1, 0, -1};

	for (int i = 0; i < 4; i++)
	{
		int nx = x + dx[i];
		int ny = y + dy[i];

		if (nx >= 0 && nx < WIDTH && ny >= 0 && ny < HEIGHT)
		{
			// change current tile to river continues
			if (water_map[ny][nx] == 3 || water_map[ny][nx] == 6 ||
			    water_map[ny][nx] == 2 || water_map[ny][nx] == 5)
			{
				// Check river continuation conditions
				if (water_map[y][x] != 2 && water_map[y][x] != 6 &&
				    water_map[y][x] != 5 && lands_map[y][x] != 5)
				{
					if (altitude_map[y][x] < altitude_map[ny][nx])
					{
						water_map[y][x] = 3; // Continue river
						river_length++;
					}
				}
			}
			extend_rivers_from_source(river_length, nx, ny);
		}
	}
}

void WorldSpawner::mark_river_ends()
{
	for (int y = 0; y < HEIGHT; ++y)
	{
		for (int x = 0; x < WIDTH; ++x)
		{
			// Check if any adjacent tile is a river
			int dx[] = {-1, 0, 1, 0};
			int dy[] = {0, 1, 0, -1};
			for (int i = 0; i < 4; ++i)
			{
				int nx = x + dx[i];
				int ny = y + dy[i];
				if (nx >= 0 && nx < WIDTH && ny >= 0 && ny < HEIGHT)
				{
					if (water_map[ny][nx] == 3)
					{
						if (ocean_map[y][x] == 0)
						{
							water_map[y][x] = 4; // River mouth at ocean
							break;
						}
						if ((get_lowest_adj_value(altitude_map, y, x) >
						     altitude_map[y][x]) &&
						    water_map[y][x] != 5)
						{
							water_map[y][x] = 7;
							break;
						}
					}
				}
			}
		}
	}
}

void WorldSpawner::generate_water_map()
{
	water_map = ocean_map;

	// generate river sources
	for (int y = 1; y < HEIGHT + 1; y++)
	{
		for (int x = 1; x < WIDTH + 1; x++)
		{ // Start from 1 to avoid borders
			if (lands_map[y][x] != 0 && lands_map[y][x] != 1)
			{
				// source spawn in high altitude
				if ((lands_map[y][x] == 4) && water_map[y][x] != 3 &&
				    water_map[y][x] != 4)
				{
					if (rand() / float(RAND_MAX) < river_from_highland_chance)
					{
						water_map[y][x] =
						    2; // river Source from highland or mountain
						continue;
					}
				}
				// source spawn from mountain side
				if ((adj_check(water_map, y, x, 5, 1)) && water_map[y][x] != 3 &&
				    water_map[y][x] != 4 && water_map[y][x] != 5 &&
				    lands_map[y][x] != 1)
				{
					if (rand() / float(RAND_MAX) < river_from_mountain_chance)
					{
						water_map[y][x] =
						    2; // river Source from highland or mountain
						continue;
					}
				}
			}

			// check for lake spawns on land
			if (lands_map[y][x] == 2 &&
			    rand() / float(RAND_MAX) < lake_from_lowlands_chance)
			{
				water_map[y][x] = 5;
			}
			if (lands_map[y][x] == 3 &&
			    rand() / float(RAND_MAX) < lake_from_midlands_chance)
			{
				water_map[y][x] = 5;
			}
			// generate river extensions from sources
			// check for river extensions
			std::fill(r_visited.begin(), r_visited.end(),
				  std::vector<bool>(HEIGHT + 1, false));
			if (water_map[y][x] == 2)
				extend_rivers_from_source(y, x, 0);
		}
	}

	for (int y = 1; y < HEIGHT + 1; y++)
	{
		for (int x = 1; x < WIDTH + 1; x++)
		{
			// generate rivers from lakes
			std::fill(r_visited.begin(), r_visited.end(),
				  std::vector<bool>(HEIGHT + 1, false));
			if (water_map[y][x] == 5 && rand() / (float)RAND_MAX < river_from_lake_chance)
				extend_rivers_from_source(y, x, 0);
		}
	}
}

// BFS function to calculate the distance from the ocean
std::vector<std::vector<int>>
WorldSpawner::calculate_ocean_distance(std::vector<std::vector<int>> &water_map, bool lake, bool river)
{
	std::vector<std::vector<int>> distance_map(
	    HEIGHT, std::vector<int>(WIDTH, WIDTH * HEIGHT)); // Initialize with large values

	int water = lake ? 5 : 0;
	water = river ? 3 : water;

	std::queue<std::pair<int, int>> q;

	// Initialize distances and queue
	for (int y = 0; y < HEIGHT; ++y)
	{
		for (int x = 0; x < WIDTH; ++x)
		{
			if (water_map[y][x] == water)
			{ // Check water_map, not lands_map
				distance_map[y][x] = 0;
				q.push({y, x});
			}
		}
	}

	// BFS to calculate distances
	while (!q.empty())
	{
		auto [cy, cx] = q.front();
		q.pop();

		for (auto [dy, dx] : directions)
		{
			int ny = cy + dy, nx = cx + dx;
			if (ny >= 0 && ny < HEIGHT && nx >= 0 && nx < WIDTH)
			{
				if (distance_map[ny][nx] > distance_map[cy][cx] + 1)
				{
					distance_map[ny][nx] = distance_map[cy][cx] + 1;
					q.push({ny, nx});
				}
			}
		}
	}
	return distance_map;
}

std::vector<std::vector<int>>
WorldSpawner::generate_wb_distances(std::vector<std::vector<int>> &water_map)
{
	std::vector<std::vector<int>> ocean_distance =
	    calculate_ocean_distance(water_map, false, false);
	return ocean_distance;
}

void WorldSpawner::generate_temperature_map()
{
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			if (ocean_map[y][x] == 0)
				continue;
			int edist = std::abs(y - EQUATOR);
			int odist = ocean_distance[y][x];
			int temperature = 90;
			// affect temp by latitude
			temperature -= (pow(edist, 1.05) * 94 / HEIGHT);
			// affect temp by altitude
			temperature -= std::min(12, static_cast<int>(altitude_map[y][x] / 3.2f));
			// mountain tiles affect temp relative to the ocean
			int range = adj_range(lands_map, y, x, 5); // find mountain
			if (range < 4 && lands_map[y][x] != 5)
			{
				std::pair ag = adj_get(lands_map, y, x, 5, range + 1);
				int nx = ag.second;
				int ny = ag.first;
				// get and see if mountain is between current tile and coast
				if (adj_range(lands_map, ny, nx, 0) < 3 &&
				    adj_range(lands_map, ny, nx, 0) < range)
				{
					temperature -= r1_to4.next() + 3;
					altitude_map[y][x] -= r1_to4.next() + 2;
					// check if tile is between mountain and coast
				}
				if (adj_range(lands_map, y, x, 0) < adj_range(lands_map, ny, nx, 0) &&
				    range < 3)
				{
					temperature += r1_to5.next() + 2;
				}
			}
			// ocean moderates temp, but less near equator
			int otemp = 80 - (edist / (HEIGHT * 1.3f / HEIGHT));

			if (temperature > 70 && odist >= 1)
			{
				temperature -= (temperature - otemp) * 1.6 / std::max(odist, 1);
			}

			if (temperature < 45 && odist >= 1)
			{
				temperature += (temperature - otemp) * 1.6 / std::max(odist, 1);
			}
			temperature_map[y][x] = temperature;
		}
	}
}

std::vector<std::tuple<float, bool, bool>>
WorldSpawner::humidity_and_rain_shadow_effects(int y, int x, int water, bool biomes)
{
	std::vector<std::tuple<float, bool, bool>> ret;
	bool leeward_effect = false;
	bool windward_effect = false;
	float min;
	float power;
	int wdistance;
	float hincrease;
	int dist;
	// make vector with all nearby tiles of water body type
	std::vector<std::tuple<int, int, int>> ocoords;
	// adjust exponential decrease of humidity gain based on water body type
	if (!biomes)
	{
		if (water == 0)
		{ // ocean
			min = 8.6;
			power = 1.3;
			dist = 7;
		}
		if (water == 5)
		{ // lake
			min = 4.8;
			power = 1.9;
			dist = 5;
		}
		if (water == 3)
		{ // river
			min = 2.8;
			power = 2.5;
			dist = 3;
		}
		ocoords = adj_get_all(water_map, y, x, water, dist);
	}
	else
	{
		if (water == 4)
		{ // wetlands
			min = 3.2;
			power = 1.7;
			dist = 3;
		}
		if (water == 5)
		{ // forest
			min = 1.7;
			power = 3.5;
			dist = 2;
		}
		if (water == 7)
		{ // jungle
			min = 2.6;
			power = 1.9;
			dist = 3;
		}

		ocoords = adj_get_all(biome_map, y, x, water, dist);
	}
	// //eliminate ocean tiles not adjacent to coasts
	for (int i = 0; i < (int)ocoords.size(); i++)
	{
		std::tuple<int, int, int> t = ocoords[i];
		std::pair<int, int> water_body = {get<0>(t), get<1>(t)};

		if (water == 0)
		{
			if (!adj_check(lands_map, water_body.first, water_body.second, 1, 1))
			{
				continue;
			}
		}
		// for all found tiles, calculate added humidity to current tile
		// and if mountain is blocking
		wdistance = std::get<2>(t);
		std::pair<int, int> current = {y, x};
		// increase humidity by distance from water body
		hincrease = fmax(0.0, (min + 1.0 - pow(wdistance, power)));
		// check if mountain is between current tile and water body
		if (is_in_path(lands_map, current, water_body, 5))
			leeward_effect = true;

		// get windward effect
		// get all mountains near water body
		std::vector<std::tuple<int, int, int>> mcoords =
		    adj_get_all(lands_map, water_body.first, water_body.second, 5, 4);
		for (int i = 0; i < (int)mcoords.size(); i++)
		{
			std::tuple<int, int, int> t = mcoords[i];
			std::pair<int, int> mount = {std::get<0>(t), std::get<1>(t)};
			// check if current tile is between waterbody and mountain
			bool result = coords_in_path(mount, water_body, current);
			if (result)
				windward_effect = true;
		}
		// add data to vector
		ret.push_back({hincrease, leeward_effect, windward_effect});
	}
	return ret;
}

float WorldSpawner::total_created_humidity(int y, int x)
{
	float createdhumidity = 0.0;
	int water_body;
	for (int c = 0; c < 3; c++)
	{
		if (c == 0)
			water_body = 0;
		if (c == 1)
			water_body = 5;
		if (c == 2)
			water_body = 3;
		std::vector<std::tuple<float, bool, bool>> water_bodies =
		    humidity_and_rain_shadow_effects(lands_map, y, x, water_body, false);
		for (int i = 0; i < (int)water_bodies.size(); i++)
		{
			std::tuple<float, bool, bool> t = water_bodies[i];
			float ah = std::get<0>(t);
			bool leeward = std::get<1>(t);
			bool windward = std::get<2>(t);
			if (leeward)
				ah *= 0.3;
			if (windward)
				ah *= 1.5;
			createdhumidity += ah;
		}
	}
	return createdhumidity;
}

// generate the humidity map based on distance to ocean and altitude
void WorldSpawner::generate_humidity_map()
{
	for (int x = 0; x < WIDTH; ++x)
	{
		for (int y = 0; y < HEIGHT; ++y)
		{
			if (ocean_map[y][x] == 0)
			{ // Ocean
				humidity_map[y][x] = 0;
			}
			else
			{

				float potentialhumidity = 0.0;
				int humidity;

				// latitudinal humidity effects
				// make measurements relative, no matter HEIGHT
				float adjusted_height = 1.0;
				float adjusted_lat = float(x) / HEIGHT;
				float equator = 0.5;
				float latitude = std::abs(adjusted_lat - equator);
				float lat_effect = 0.0;

				// simulate hadley effect, which lowers humidity at 30 and 90,
				// raises at 0 and 60
				if (latitude <= (1.0 / 3.0))
				{ // Roughly between 0 and 30
					lat_effect = cos((latitude / (1.0 / 3.0)) * M_PI) *
						    1.6; // Peak at 30
				}
				else if (latitude <= (2.0 / 3.0))
				{ // Roughly between 30 and 60
					lat_effect =
					    cos(((latitude - (1.0 / 3.0)) / (1.0 / 3.0)) * M_PI) *
					    1.6; // Peak at 30
				}
				else
				{ // Roughly between 60 and 90
					lat_effect =
					    cos(((latitude - (2.0 / 3.0)) / (1.0 / 3.0)) * M_PI) *
					    0.6; // Peak at 90
				}

				// Safeguard against extreme values
				lat_effect = std::max(1.0f, std::min(lat_effect, 2.0f));
				//
				// calculate created humidity based on nearby water bodies and rain
				// shadow effect
				float evap = ((pow(temperature_map[y][x] / 22, 1.1)) +
					      (altitude_map[y][x] / 12)) /
					     6;
				float created_humidity =
				    ((humidity_mult * total_created_humidity(lands_map, y, x)) * evap);
				// potentialhumidity += fmax(3,((0.6 * (pow((temperature_map[y][x]
				// / 2.4), 1.5) - pow(lands_map[x][y],2.1))) - 30));

				humidity_map[y][x] =
				    fmax(1, fmin(MAX_HUMIDITY, created_humidity - lat_effect));
				// potential_humidity_map[y][x] = potentialhumidity;
				// humidity_map[y][x] = fmax(1, fmin(100, fmin(createdhumidity,
				// potentialhumidity)));
			}
		}
	}
}

void WorldSpawner::factor_wetlands_jungles_and_forests()
{
	for (int x = 0; x < WIDTH; x++)
	{
		for (int y = 0; y < HEIGHT; y++)
		{
			if (ocean_map[y][x] == 0)
				continue;
			float createdhumidity = 0.0;
			int biome;
			for (int c = 0; c < 3; c++)
			{
				if (c == 0)
					biome = 4;
				if (c == 1)
					biome = 5;
				if (c == 2)
					biome = 7;
				std::vector<std::tuple<float, bool, bool>> biomes =
				    humidity_and_rain_shadow_effects(water_map, lands_map, y, x, biome,
								 true);
				for (int i = 0; i < (int)biomes.size(); i++)
				{
					std::tuple<float, bool, bool> t = biomes[i];
					float ah = std::get<0>(t);
					bool leeward = std::get<1>(t);
					bool windward = std::get<2>(t);
					if (leeward)
						ah *= 0.3;
					if (windward)
						ah *= 1.4;
					createdhumidity += ah;
					float evap = ((pow(temperature_map[y][x] / 24, 1.8)) +
						      (altitude_map[y][x] / 12)) /
						     5;
					humidity_map[y][x] +=
					    fmax(0, (humidity_mult * createdhumidity * evap));
					if (humidity_map[y][x] > MAX_HUMIDITY)
						humidity_map[y][x] = MAX_HUMIDITY;
				}
			}
		}
	}
}

// 4. Generate Biomes
// 1. Hot Desert
// 2. Plain/Grassland
// 3. Savannah
// 4. Wetlands
// 5. Temperate Forest
// 6. Boreal Forest
// 7. Rainforest/Jungle
// 8. Rocky/Badlands
// 9. Tundra
// 10. Cold Desert
void WorldSpawner::generate_biomes()
{
	// load data of each biome
	std::tuple<int, int, int, float, float, float, float> biome_data[11];
	int size = 11;
	// humidity, altitude, temp, humidity flexibility, altitude flexibility, temp
	// flexibility, spread chance/size
	biome_data[1] = {10, 7, 90, 1, 4, 2, 0.6};      // Hot Desert
	biome_data[2] = {25, 5, 65, 1.5, 2, 2.5, 0.85}; // Grassland
	biome_data[3] = {35, 3, 78, 2.5, 2, 2.5, 0.7};  // Savanna
	biome_data[4] = {100, 2, 60, 1, 1.5, 3, 0.1};   // Wetland
	biome_data[5] = {66, 6, 60, 2.5, 2, 2.5, 0.8};  // Forest
	biome_data[6] = {50, 8, 43, 3, 3, 2, 0.7};      // Taiga
	biome_data[7] = {90, 4, 88, 1.5, 2, 2, 0.65};   // Jungle
	biome_data[8] = {15, 25, 52, 1, 3, 1.4, 0.4};   // Rocky
	biome_data[9] = {5, 31, 20, 4, 6.0, 1, 0.7};    // Tundra
	biome_data[10] = {10, 8, 40, 0.4, 1, 0.6, 0.5}; // Cold Desert

	for (int s = 0; s < 5; s++)
	{
		for (int x = s; x < WIDTH; x += 5)
		{
			for (int y = s; y < HEIGHT; y++)
			{
				if (biome_map[x][y] != 0)
					continue;
				if (ocean_map[x][y] == 0)
					continue;
				int humidity = humidity_map[x][y];
				int altitude = altitude_map[x][y];
				int temp = temperature_map[x][y];
				float lowest_score = RAND_MAX;
				int biome = 0;

				for (int i = 1; i < size; i++)
				{
					// get how far away stats are from each biome_type
					float hum_distance = abs(humidity - get<0>(biome_data[i])) /
							    get<3>(biome_data[i]);
					float alt_distance = abs(altitude - get<1>(biome_data[i])) *
							    2.3 / get<4>(biome_data[i]);
					float temp_distance =
					    abs(temp - get<2>(biome_data[i])) / get<5>(biome_data[i]);
					if (hum_distance + alt_distance + temp_distance < lowest_score)
					{
						lowest_score =
						    hum_distance + alt_distance + temp_distance;
						biome = i;
					}
					biome_map[x][y] = biome;
				}
			}
		}
		factor_wetlands_jungles_and_forests(temperature_map, ocean_map, lands_map, altitude_map,
						humidity_map, water_map, s);
	}
}

void WorldSpawner::generate_altitude_map()
{
	for (int y = 0; y < HEIGHT; ++y)
	{
		for (int x = 0; x < WIDTH; ++x)
		{
			// Generate noise value in range [-1, 1]
			float noise_value = r_noise.GetNoise((float)y, (float)x);
			// Map the noise value to a HEIGHT range (e.g., 0 to 255)
			int altitude = static_cast<int>(
			    pow((noise_value * 23), 1.2)); // Converts from [-1, 1] to [-100, 100]
			altitude_map[y][x] = altitude;
		}
	}
}

void WorldSpawner::get_rivers_from_groundwater()
{
	for (int y = 0; y < HEIGHT; ++y)
	{
		for (int x = 0; x < WIDTH; ++x)
		{
			// skip tiles that already have water
			if (water_map[y][x] != 1)
				continue;
			if (ocean_map[y][x] == 0)
				continue;
			if (humidity_map[y][x] > ground_water_threshold)
			{
				if (rand() / (float)RAND_MAX > river_from_groundwater_chance)
				{
					water_map[y][x] = 6; // river source from groundwater
					std::fill(r_visited.begin(), r_visited.end(),
						  std::vector<bool>(HEIGHT + 1, false));
					extend_rivers_from_source(y,
							       x);
				}
			}
		}
	}
}

void WorldSpawner::clean_altitude_map()
{
	for (int y = 0; y < HEIGHT; ++y)
	{
		for (int x = 0; x < WIDTH; ++x)
		{
			if (altitude_map[y][x] < land_threshold)
			{
				altitude_map[y][x] = 0;
			}
		}
	}
}

void WorldSpawner::add_depressions()
{
	FastNoiseLite noise_generator;
	noise_generator.SetSeed(43543);
	noise_generator.SetNoiseType(FastNoiseLite::NoiseType_Perlin);

	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			float noise_value = noise_generator.GetNoise((float)y, (float)x);
			float altitude = static_cast<int>(
			    (noise_value) * 100); // Converts from [-1, 1] to [-100, 100]
			if (altitude < depression_threshold && altitude > 0 && ocean_map[x][y] == 1)
			{
				altitude_map[y][x] =
				    fmax(1, (lerp((float)altitude, (float)altitude_map[y][x], 0.2)));
			}
		}
	}
}

// MAKE MICRO MAP

// Assign each tile to the nearest Voronoi site
// int get_cell_idfor_tile(int x, int y) {
//     float min_dist = (float)RAND_MAX;
//     int closest_site = 0;

//     for (int i = 0; i < (int)voronoi_sites.size(); i++) {
//         float dist = std::hypot(y - voronoi_sites[i].first, x -
//         voronoi_sites[i].second); if (dist < min_dist) {
//             min_dist = dist;
//             closest_site = i;
//         }
//     }
//     return closest_site;
// }

// Function to find the next tile to flow to (either towards target (lake or
// river end) or lowest elevation)
void WorldSpawner::apply_river_tiles()
{
	int index = r_tile_index[{y, x}];
	// base case: reached target
	if (y == target.first && x == target.second)
	{
		return;
	}
	// base case: reached lake or ocean tile
	if (r_tile_type[index] == Tile::ShallowWater)
	{
		return;
	}
	int min_elevation = r_tile_alt[index];
	int current_elevation = min_elevation;
	int min_dist = calculate_distance(y, x, target);
	std::std::pair<int, int> next_tile = {y, x};

	// Find the lowest elevation neighboring tile
	std::vector<std::std::pair<int, int>> low_elev_tiles; // To store ties for lowest elevation
	for (const auto &dir : directions)
	{
		int nx = x + dir.second;
		int ny = y + dir.first;

		int dist_to_target = calculate_distance(ny, nx, target);
		int new_index = r_tile_index[{ny, nx}];
		if (tile_alt[new_index] < min_elevation)
		{
			min_elevation = tile_alt[new_index];
			min_dist = dist_to_target;
			next_tile = {nx, ny};
			low_elev_tiles.clear();
			low_elev_tiles.push_back(next_tile);
		}
		else if (tile_alt[new_index] == min_elevation)
		{
			low_elev_tiles.push_back({nx, ny}); // Tie in elevation
		}
	}

	// If there are ties in the lowest elevation, randomly choose one of the tiles
	if (low_elev_tiles.size() > 1)
	{
		next_tile = low_elev_tiles[rand() % low_elev_tiles.size()];
	}

	// If nearby elevation is equal to current tile's elevation, prioritize moving
	// towards target
	if (min_elevation == current_elevation)
	{
		// Check distance to target, if closer to the target, move that way
		for (const auto &dir : directions)
		{
			int nx = x + dir.second;
			int ny = y + dir.first;

			int dist_to_target = calculate_distance(ny, nx, target);
			if (dist_to_target < min_dist)
			{
				next_tile = {ny, nx};
				min_dist = dist_to_target;
			}
		}
	}
	int ty = next_tile.first;
	int tx = next_tile.second;
	// apply next_tile as river_tile
	int next_index = r_tile_index[{ty, tx}];
	r_tile_type[next_index] = Tile::FlowingWater;
	r_tile_alt[next_index] -= 1;
	apply_river_tiles(r_tile_alt, r_tile_type, r_tile_index, ty, tx, target);
}

void WorldSpawner::recursive_lower()
{
	if (decrease_amount < 0)
	{
		return; // Stop recursion if altitude is not decreasing (coast of lake has
			// been reached)
	}

	// Generate a random chance and decide whether to lower the decrease_amount
	if ((rand() / (float)RAND_MAX) > lake_tile_chance)
	{
		decrease_amount -= 1;
	}

	// Lower the elevation by the decrease amount
	int index = r_tile_index[{y, x}];
	r_tile_alt[index] -= decrease_amount;

	// Recursively lower neighboring cells
	for (const auto &delta :
	     std::vector<std::std::pair<int, int>>{{-1, 0}, {1, 0}, {0, -1}, {0, 1}})
	{
		int nx = x + delta.first;
		int ny = y + delta.second;
		if (nx >= 0 && ny >= 0 && nx < WORLD_WIDTH && ny < WORLD_HEIGHT)
		{
			recursive_lower(nx, ny, decrease_amount);
		}
	}
}

void WorldSpawner::recursive_fill()
{
	int index = r_tile_index[{y, x}];
	if (tile_alt[index] > alt_threshold)
	{
		return;
	}
	// fill with water
	r_tile_type[index] = Tile::ShallowWater;
	r_tile_water[index] = true;

	// Recursively lower neighboring cells
	for (const auto &delta :
	     std::vector<std::std::pair<int, int>>{{-1, 0}, {1, 0}, {0, -1}, {0, 1}})
	{
		int nx = x + delta.first;
		int ny = y + delta.second;
		if (nx >= 0 && ny >= 0 && nx < WORLD_WIDTH && ny < WORLD_HEIGHT)
		{
			recursive_lower(nx, ny, alt_threshold);
		}
	}
}

// generates starting tiles based on amount of cells fully generated (loaded
// into memory)

// generate water bodies
// for (int i = 0; i < (int)r_tile_cell_index.size(); i++) {
//         uint32_t index = r_tile_cell_index[i];
//         std::std::pair map_coord = maps_link[index];
//         //get seed of cell
//         std::std::pair seed = voronoi_sites[index];
//         // add river source tiles for those near mountain cells (due to
//         snowmelt)
//             if (water_map[map_coord.first][map_coord.second] == 2) {
//             // goal: put sources close to mountian tiles
//             // 1. get closest adj mountain tile

//             const uint16_t num_results = 5;
//             std::vector<float> query_point = {seed.first, seed.second};
//             uint32_t ret_index[num_results]; // nearest neighbor index
//             float out_dist_sqr[num_results]; //distance between nn and current
//             tree.knn_search(&query_point[0], num_results, &ret_index[0],
//             &out_dist_sqr[0]); bool found_mountain = false; for (int i = 0; i <
//             num_results; i++) {
//                 int cell_index = (int)ret_index[0];
//                 std::std::pair near_cell_coord = maps_link[cell_index];
//                 // if found nearby point is a mountain
//                 if (lands_map[near_cell_coord.first][near_cell_coord.second] == 5)
//                 {
//                     found_mountain = true;
//                     //find good source tiles in between mountain seed tile
//                     and current seed tile std::std::pair mountain_seed =
//                     voronoi_sites[cell_index]; std::std::pair<int,int>
//                     source_tile = {lerp((int) mountain_seed.first,
//                     (int)seed.first, 0.6),
//                     lerp((int)mountain_seed.second,(int) seed.second, 0.6)};
//                     // int width = rint(3,10);
//                     // int length = rint(3,10);
//                     // for (int w = 0; w < width; w++) {
//                     //      for (int l = 0; l < length; l++) {
//                     //          int ti =
//                     r_tile_index[{source_tile.first+w,source_tile.second+l}]; if
//                     (r_tile_index.find({source_tile.first,source_tile.second}) !=
//                     r_tile_index.end()) {
//                          int ti = r_tile_index[{source_tile.first,
//                          source_tile.second}];
//                     r_tile_water[ti] = true;
//                              r_tile_type[ti] = Tile::RiverSource;
//                              river_sources.push_back(source_tile);
//                     }
//                     //     }
//                     // }
//                 }
//                 if (found_mountain == true) break;
//             }
//         }
//         if (water_map[map_coord.first][map_coord.second] == 6) {
//             // put sources from highlands or groundwater in random spot in
//             cell std::std::pair<int,int> random = {(int)seed.first +
//             rint((-CELL_SIZE/2)+10,(CELL_SIZE/2)-10),seed.second +
//             rint((-CELL_SIZE/2)+10,(CELL_SIZE/2)-10)}; if
//             (r_tile_index.find({random.first,random.second}) !=
//             r_tile_index.end()) {
//                         int ti = r_tile_index[{random.first,random.second}];
//                         r_tile_water[ti] = true;
//                         r_tile_alt[ti] -= 2;
//                         r_tile_type[ti] = Tile::RiverSource;
//                         river_sources.push_back(random);
//                     }
//         }
//         // add lakes
//         if (water_map[map_coord.first][map_coord.second] == 5) {
//             //check if lake takes up more than one cell
//             // std::vector<std::tuple<int,int,int>> lake_pieces =
//             adj_get_all(water_map,map_coord.first,map_coord.second,5,1);
//             // while (int i = 0 < lake_pieces.size()) {
//             //     lake_pieces[i];
//             //     i++;
//             // }
//             // create altitude depressions to fill lakes with
//              std::std::pair<int,int> depression_center = {seed.first +
//              rint((-CELL_SIZE/2)+10,(CELL_SIZE/2)-10),seed.second +
//              rint((-CELL_SIZE/2)+10,(CELL_SIZE/2)-10)}; if
//              (r_tile_index.find({depression_center.first,depression_center.second})
//              != r_tile_index.end()) { int ti =
//              r_tile_index[{depression_center.first,depression_center.second}];
//              //add depression_center to lake centers
//              river_ends.push_back(depression_center);
//              lake_or_end[{depression_center.first, depression_center.second}] =
//              true; int alt_threshold = r_tile_alt[ti];
//              recursive_lower(depression_center.first,
//              depression_center.second,rint(1,4));
//              // fill all tiles with water that are lower than the original
//              center tile of the new lake
//              recursive_fill(depression_center.first,
//              depression_center.second,alt_threshold);
//              }
//         }
//         // add river ends
//         if (water_map[map_coord.first][map_coord.second] == 4) { // at ocean
//              river_ends.push_back(seed);
//             lake_or_end[{seed.first, seed.second}] = false;
//         }
//           if (water_map[map_coord.first][map_coord.second] == 7) { // inland
//                 std::std::pair<int,int> center = {(int)seed.first +
//                 rint((-CELL_SIZE/2)+10,(CELL_SIZE/2)-10), (int)seed.second +
//                 rint((-CELL_SIZE/2)+8,(CELL_SIZE/2)-8)};
//              river_ends.push_back(center);
//              lake_or_end[{center.first, center.second}] = false;
//         }
//     }
// // create nearest neighbor lookup for lakes centers
// SeedCloud river_ends_cloud;
// river_ends_cloud.seeds = river_ends;

// using my_kd_tree_t = nanoflann::KDTreeSingleIndexAdaptor<
//     nanoflann::L2_Simple_Adaptor<float, SeedCloud>,
//     SeedCloud, /* Our dataset */
//     2 /* 2D space */
//     >;

// my_kd_tree_t river_ends_tree(2 /*dim*/, river_ends_cloud, {10} /* max leaf size
// */); river_ends_tree.build_index();
// // generate river flow tiles, from source to nearest river_end
// for (int i = 0; i < river_sources.size(); i++) {
//         //get seed of cell
//         std::std::pair<float,float> source = river_sources[i];
//          std::vector<float> query_point = {source.first, source.second};
//         const uint16_t num_results = 1;
//         uint32_t ret_index[num_results]; // nearest neighbor index
//         float out_dist_sqr[num_results]; //distance between nn and current
//         river_ends_tree.knn_search(&query_point[0], num_results, &ret_index[0],
//         &out_dist_sqr[0]);
//         // flow from source to nearest river end
//         apply_river_tiles(source.first, source.second,river_ends[ret_index[0]]);
// }

float range_penalty(float original_value, float min_value, float max_value, float adjusted_value)
{
	if (original_value >= min_value && original_value <= max_value)
	{
		return adjusted_value;
	}
	else
	{
		float distance = 0.0f;

		if (original_value < min_value)
		{
			distance = min_value - original_value;
		}
		else if (original_value > max_value)
		{
			distance = original_value - max_value;
		}

		float penalty = exp(0.5 * distance); // Adjust the factor for more or less penalty
		return adjusted_value - penalty;
	}
}

template <typename T> void WorldSpawner::print_map(T map)
{
	for (int x = 0; x < WIDTH; ++x)
	{
		for (int y = 0; y < HEIGHT; ++y)
		{
			cout << map[x][y] << " ";
		}
		cout << endl;
	}
}

// Function to generate Voronoi sites, and each biome, altitude, avg temperature
// generated before will be assigned to a voronoi site
std::vector<Coord> WorldSpawner::generate_voronoi_sites()
{
	FastNoiseLite noise;
	noise.SetNoiseType(FastNoiseLite::NoiseType_Cellular);
	std::vector<Coord> voronoi_sites(AMOUNT);
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			float vx = (rand() % WORLD_WIDTH);
			float vy = (rand() % WORLD_HEIGHT);
			voronoi_sites[i] = {vy, vx};
		}
	}
	return voronoi_sites;
}

void WorldSpawner::generate_tile_types(std::vector<float> &chances, std::vector<Coord> &voronoi_sites,
				     Array<Alt> &r_altitudes)
{
	SeedCloud cloud;

	cloud.seeds = voronoi_sites;

	using my_kd_tree_t =
	    nanoflann::KDTreeSingleIndexAdaptor<nanoflann::L2_Simple_Adaptor<float, SeedCloud>,
						SeedCloud, /* Our dataset */
						2	   /* 2D space */
						>;

	my_kd_tree_t tree(2 /*dim*/, cloud, {10} /* max leaf size */);
	tree.build_index();

	// CREATE ALL TILES FOR STARTING CELLS
	int tiles = 0;

	// zoom into tile
	int cx = rcx.next();
	int cy = rcy.next();
	// select cell as randomized spawn point
	bool selected = false;
	while (!selected)
	{
		if (biome_map[cy][cx] == 0)
		{
			cx = rcx.next();
			cy = rcy.next();
		}
		else
			selected = true;
	}

	uint32_t seed_index = cy * HEIGHT + cx;
	std::std::pair<float, float> s_vseed = voronoi_sites[seed_index];

	// generate tiles near to randomized spawn point
	current_xmin = s_vseed.second - STARTING_MAP_WIDTH / 2;
	current_xmax = s_vseed.second + STARTING_MAP_WIDTH / 2;
	current_ymin = s_vseed.first - STARTING_MAP_HEIGHT / 2;
	current_ymax = s_vseed.first + STARTING_MAP_HEIGHT / 2;

	int ci = 0;

	for (int y = current_ymin; y < current_ymax; y++)
	{
		for (int x = current_xmin; x < current_xmax; x++)
		{
			std::vector<float> query_point = {(float)y, (float)x};
			// Perform the nearest neighbor search, num_results is # of neighbors
			const uint16_t num_results = 5;
			uint32_t ret_index[num_results]; // nearest neighbor index
			float out_dist_sqr[num_results];  // distance between nn and current

			tree.knn_search(&query_point[0], num_results, &ret_index[0], &out_dist_sqr[0]);
			// check if tile is still part of current cell
			int ti = r_tile_index[{y, x}];

			// TODO: optimize this part
			//  calculate altitude based on weighted average
			float current_alt = 0;
			float strengths[num_results];
			float denominator = 0.0000000001;

			for (int i = 0; i < num_results; i++)
			{
				if (index >= 0 && index < r_maps_link.size())
				{
					std::std::pair<float, float> select = r_maps_link[index];
					// get inversed distances for strengths
					strengths[i] = 1 / (out_dist_sqr[i] + CELL_SIZE / 2);
					float r_tile_alt = altitude_map[select.first][select.second];
					current_alt += strengths[i] * r_tile_alt;
					denominator += strengths[i];
				}
			}

			int calc_alt = (int)current_alt / denominator;

			std::pair<float, float> cell = r_maps_link[ret_index[0]];

			// set r_tile_type based on chance from most common tiles of two closest
			// seeds' biomes
			if (cell.first >= 0 && cell.first < HEIGHT && cell.second >= 0 &&
			    cell.second < WIDTH)
			{
				int biome = biome_map[cell.first][cell.second];
				// int second_biome =
				// biome_map[second_cell.first][second_cell.second];
				int index = y *;
				tile_spawn_buffer.tiles[index] = get_tile_type(biome, chances[ci++]);
				tile_spawn_buffer.altitudes[index] = calc_alt;
			}
		}
	}
}

void WorldSpawner::move_regions_to_chunks(Array<uint8_t> &humidity_table,
				       Array<int8_t> &min_temperature_table,
				       Array<uint8_t> &altitudes)
{
	int idx = 0;
	for (int i = 0; i < LENGTH_CHUNKS; i++)
	{
		for (int j = 0; j < HEIGHT_CHUNKS; j++)
		{
			// for each chunk, count tiles per region slot
			std::unordered_map<uint16_t, uint16_t> region_counts;
			int total_count = 0;
			for (int k = 0; k < CHUNK_SIZE; k++)
			{
				uint16_t region =
				    tile_region_slot[(j * CHUNK_LENGTH) + (k / CHUNK_LENGTH)]
						  [(i * CHUNK_LENGTH) + (k % CHUNK_LENGTH)];
				region_counts[region]++;
				total_count++;
			}

			// calculate values of each chunk based on region counts
			for (const auto &std::pair : region_counts)
			{
				auto key = std::pair.first;
				auto value = std::pair.second;

				humidity_table[idx] += static_cast<float>(
				    humidity_map[key / CHUNK_LENGTH][key % CHUNK_LENGTH] *
				    (value / total_count));

				temperature_table[idx] += static_cast<float>(
				    temperature_map[key / CHUNK_LENGTH][key % CHUNK_LENGTH] *
				    (value / total_count));

	altitudes[idx] += static_cast<float>(            altitude_map[key / CHUNK_LENGTH][key % CHUNK_LENGTH] *
            (value / total_count)))
			}
			idx++;
		}
	}

	WorldSpawner::print_info()
	{
		cout << "Ocean" << endl;
		print_map(ocean_map);
		cout << "Lands" << endl;
		print_map(lands_map);
		cout << "Altitude" << endl;
		print_map(altitude_map);
		cout << "Water Bodies" << endl;
		print_map(water_map);
		cout << "Temperature" << endl;
		print_map(temperature_map);
		cout << "Humidity" << endl;
		print_map(humidity_map);
		cout << "Biomes" << endl;
		print_map(biome_map);
	}

	WorldSpawner::generate_world()
	{
		FastNoiseLite noise_layer;
		noise_layer.SetSeed(1434933);
		noise_layer.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
		noise_layer.SetFrequency(0.05f);
		noise_layer.SetFractalType(FastNoiseLite::FractalType_FBm);
		noise_layer.SetFractalLacunarity(1.8f); // chaos
		noise_layer.SetFractalOctaves(7);       // more detail, extremes appear in cells

		// MAPS
		world.generate_altitude_map(noise_layer);
		world.generate_oceans_on_maps(ocean_map, altitude_map, lands_map, land_threshold);
		world.clean_altitude_map();
		world.generate_lands_map()
                world.generate_water_map();
		world.generate_wbdistances();
		world.generate_temperature_map();
		world.generate_humidity_map();
		world.generate_biomes();
		world.get_rivers_from_groundwater();
		std::vector<float> gtc = ws.generate_tile_chances();
		std::vector<Coord> gvs = ws.generate_voronoi_sites();
		generate_tiles_types(gtc, gvs);
		world.calculate_chunk_temperature_inputs();
		world.calculate_chunk_precipitation_equilibrium();
		spawn_grass_and_first_plants();
		cout << "PLANTS SPAWNED" << endl;
		spawn_first_animals();
		cout << "TILE AMOUNT:" << r_tile_index.size() << endl;
		int cell = r_tile_cell_index[5];
		cout << " Cell: " << cell;
		spawn_scavengeables();
	}
