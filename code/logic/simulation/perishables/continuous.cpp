#include "perishables_manager.hpp"
#include "chunk_manager.hpp"
#include <logic/simulation/lifetime_manager.hpp>
#include <data/const/chunk_data.hpp>
#include <world/item/perishables.hpp>
#include <data/const/tile_data.hpp>

void process_perishables(LifetimeManager &lm, ChunkManager &cm, Array<uint16_t> &perishable_indices,
			Array<Item> &perishables, Array<Time> &living_times, Time time_passed,
			Array<Coord> &perishable_coords)
{
	for (uint16_t i = 0; i < living_times.capacity; i++)
	{
		uint16_t pi = perishable_indices[i];
		uint16_t c = get_chunk_index_from_tile(perishable_coords[pi]);
		Temp temp = cm.get_chunk_temperature(c);
		living_times[i] += get_perishable_time(perishables[i], time_passed, temp);
		Item p = perishables[i];
		if (living_times[i] > perishable_destruction_times[p])
			lm.mark_destroyed(pi);
	}
}


