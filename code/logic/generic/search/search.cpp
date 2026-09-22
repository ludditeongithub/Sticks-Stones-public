#include "search.hpp"
#include "core/database.hpp"
#include "data/types/animal.hpp"
#include "data/const/tile_data.hpp"
#include "data/run/tile_database.hpp"
#include <core/limits.hpp>
#include <data/types/entity.hpp>
#include <core/math.hpp>
#include <cstdint>
#include <limits>
#include <variant>
#include <data/types/unit.hpp>
#include <data/run/world.hpp>

SearchGrid::SearchGrid(World& world, tile::Database& tiles) :  world(world), tiles(tiles)
{	
	uint16_t chunk_amount = world.CHUNK_AMOUNT;
	chunk_bucket_arena = new Arena((chunk_amount * NATURAL_CHUNK_SEARCH_SIZE));

	active_bucket_arena =
	    new Arena((chunk_amount * NATURAL_CHUNK_SEARCH_SIZE) +
		      (estimated_active_chunk_amount(chunk_amount) * ACTIVE_CHUNK_SEARCH_SIZE));

	for (uint16_t i = 0; i < chunk_amount; i++)
	{
		chunk_buckets[i] =
		   arena_make_array<ChunkBucket*>(chunk_bucket_arena, NATURAL_CHUNK_SEARCH_SIZE);
		active_chunks[i] = false;
	}
    
}

inline GridInfo SearchGrid::get_nth_nearest_chunk(Coord c, uint16_t n)
{
		const uint16_t center = get_chunk_index_from_tile(c);
	const int ha = c.x % chunk_size;
	const int va = c.y % chunk_size;
	const int dist_n = va;
	const int dist_s = chunk_size - va;
	const int dist_w = ha;
	const int dist_e = chunk_size - ha;

	struct Entry
	{
		uint16_t dist;
		int16_t offset;
	};

	const int row = world.LENGTH_CHUNKS;

	Entry neighbors[8] = {{static_cast<uint16_t>(dist_n), -row},
			      {static_cast<uint16_t>(dist_s), row},
			      {static_cast<uint16_t>(dist_w), -1},
			      {static_cast<uint16_t>(dist_e), 1},
			      {static_cast<uint16_t>(dist_n + dist_e), -row + 1},
			      {static_cast<uint16_t>(dist_n + dist_w), -row - 1},
			      {static_cast<uint16_t>(dist_s + dist_e), row + 1},
			      {static_cast<uint16_t>(dist_s + dist_w), row - 1}};

	const uint16_t idx = n & 7;

	std::nth_element(std::begin(neighbors), std::begin(neighbors) + idx, std::end(neighbors),
			 [](const Entry &a, const Entry &b) { return a.dist < b.dist; });

	const int target = int(center) + neighbors[idx].offset;

	GridInfo result;
	result.index =
	    (target >= 0 && target < world->CHUNK_AMOUNT) ? static_cast<uint16_t>(target) : center;
	result.distance = neighbors[idx].dist;

	return result;
}

void SearchGrid::add_active_chunk(uint16_t index)
{
	active_chunks[index] = true;
	uint16_t active_index;
	if (free_indices.empty())
		active_index = active_count;
	else
	{
		active_index = free_indices.top();
		free_indices.pop();
	}
	active_chunk_buckets[active_index] = chunk_buckets[index];
	chunk_to_active_chunks[index] = active_index;
}

inline void SearchGrid::insert_entity(Entity type, EntitySearchData data)
{
	uint16_t gc = get_chunk_index_from_tile(data.position);
	uint16_t i = get_tile_index_chunk_relative(data.position);
	if (!(tiles.occupied_tiles[gc])[i])
	{
		if (active_chunks[gc])
		{			active_chunk_buckets[gc]->at(type).push_back(data);
		}
		else
		{
			chunk_buckets[gc]->at(type).push_back(data);
		}
	} // TODO: error
}

inline void SearchGrid::remove_entity(Entity type, EntitySearchData data)
{
  
}

inline bool SearchGrid::check_collision(Coord tile_coord)
{	
	return tiles->occupieds[world.get_tile_index_from_coord(tile_coord)];
}

inline EntitySearchData SearchGrid::get_nearest(Entity e, Coord c)
{
	// search per chunk, starting with nearest
	uint16_t ci = get_chunk_index_from_tile(c);
	Array<SearchGrid::ChunkBucket *> &buckets = active_chunks[ci] ? active_chunk_buckets : chunk_buckets;
	uint16_t cbi = active_chunks[ci] ? chunk_to_active_chunks[ci] : ci;
	auto &&es = buckets[cbi]->find(e);

	if (es != buckets[cbi]->end())
	{
		Coord nc;
		uint16_t si = SIZE_MAX;
		uint16_t ld = UINT16_MAX;
		for (uint16_t i = 0; i < es->second.size(); i++)
		{
			Coord tc = es->second[i].position;
			uint32_t td = manhattan_dist(c, tc);
			if (td < ld)
			{
				ld = td;
				si = i;
			}
		}
		return es->second[si];
	}
	else
	{
		return {std::numeric_limits<uint16_t>::max(), {std::numeric_limits<uint16_t>::max(), std::numeric_limits<uint16_t>::max()}};
	}
}

inline bool check_adjacent(Entity entity, Coord coord)
{

}

inline EntitySearchData SearchGrid::get_nth_nearest(uint16_t nearest, Entity e, Coord c)
{
	uint16_t ci = get_chunk_index_from_tile(c);
	Array<SearchGrid::ChunkBucket *> &buckets =
		active_chunks[ci] ? active_chunk_buckets : chunk_buckets;

	uint16_t cbi = active_chunks[ci] ? chunk_to_active_chunks[ci] : ci;
	auto &&es = buckets[cbi]->find(e);

	if (es == buckets[cbi]->end())
	{
		return {
			std::numeric_limits<uint16_t>::max(),
			{
				std::numeric_limits<uint16_t>::max(),
				std::numeric_limits<uint16_t>::max()
			}
		};
	}

	const auto &list = es->second;
	const uint16_t n = list.size();

	if (nearest >= n)
	{
		return {
			std::numeric_limits<uint16_t>::max(),
			{
				std::numeric_limits<uint16_t>::max(),
				std::numeric_limits<uint16_t>::max()
			}
		};
	}

	std::vector<bool> used(n, false);

	uint16_t best_index = 0;
	uint32_t best_dist = 0;

	for (uint16_t k = 0; k <= nearest; k++)
	{
		bool found = false;

		for (uint16_t i = 0; i < n; i++)
		{
			if (used[i]) continue;

			uint32_t d = manhattan_dist(c, list[i].position);

			if (!found || d < best_dist)
			{
				best_dist = d;
				best_index = i;
				found = true;
			}
		}

		used[best_index] = true;
	}

	return list[best_index];
}

EntityRenderBuffer SearchGrid::get_all_in_range(Coord origin, Coord dimensions)
{
	EntityRenderBuffer erd;
	std::vector<uint16_t> chunks_on_screen = get_chunks_from_area(origin, dimensions);
	for (auto i: chunks_on_screen) {
			Array<SearchGrid::ChunkBucket *> &cb = active_chunks[i] ? active_chunk_buckets : chunk_buckets;
	uint16_t cbi = active_chunks[i] ? chunk_to_active_chunks[i] : i;
	// iterate through unordered map, get all entities
	for (auto x : *cb[cbi])
	{
std::visit([&](auto&& arg) {
    using T = std::decay_t<decltype(arg)>;
    std::vector<EntitySearchData>& objects = x.second;
    if constexpr (std::is_same_v<T, Plant>)
    {
	    for (size_t j = 0; j < objects.size(); j++) {
		            erd.plants[erd.plant_amount++] = {objects[j].index, objects[j].position, std::move(arg)};
	    }
    }
    else if constexpr (std::is_same_v<T, Animal>)
    {
	    for (size_t j = 0; j < objects.size(); j++) {
		            erd.animals[erd.animal_amount++] = {objects[j].index, objects[j].position, std::move(arg)};
	    }        
    }
    else if constexpr (std::is_same_v<T, Item>) {
	    for (size_t j = 0; j < objects.size(); j++) {
		            erd.items[erd.item_amount++] = {objects[j].index, objects[j].position, std::move(arg)};
	    }
    }
    else if constexpr (std::is_same_v<T, Unit>) {
	    for (size_t j = 0; j < objects.size(); j++) {
		            erd.items[erd.item_amount++] = {objects[j].index, objects[j].position, std::move(arg)};
	    }
    }
    else if constexpr (std::is_same_v<T, Tool>) {
	    for (size_t j = 0; j < objects.size(); j++) {
		            erd.tools[erd.tool_amount++] = {objects[j].index, objects[j].position, std::move(arg)};
	    }
    } 
}, x.first);
	}
	}
	return erd;
}


std::pair<int, int> ObjectDatabase::find_nearest_liquid_container(int x, int y)
{
	std::pair<int, int> subject = {x, y};
	std::pair<int, int> closest = find_nearest_object(Container::Pot, x, y);
	if (man_dist(subject, closest) <
	    man_dist(find_nearest_object(subject, Container::Bucket, x, y)))
		closest = find_nearest_object(subject, Container::Bucket, x, y);
	if (man_dist(subject, closest) <
	    man_dist(find_nearest_object(subject, Container::LargePot, x, y)))
		closest = find_nearest_object(subject, Container::LargePot, x, y);
	if (man_dist(subject, closest) <
	    man_dist(find_nearest_object(subject, Container::Kettle, x, y)))
		closest = find_nearest_object(subject, Container::Kettle, x, y);
	if (man_dist(subject, closest) < man_dist(find_nearest_object(subject, Container::Keg, x, y)))
		closest = find_nearest_object(subject, Container::Keg, x, y);
	if (man_dist(subject, closest) < man_dist(find_nearest_object(subject, Container::Jar, x, y)))
		closest = find_nearest_object(subject, Container::Jar, x, y);
	return closest;
}
