#include "perishables_manager.hpp"
#include "chunk_manager.hpp"
#include <simulation/lifetime_manager.hpp>
#include <world/chunk/data.hpp>
#include <world/item/perishables.hpp>
#include <world/tile/data.hpp>

void processPerishables(LifetimeManager &lm, ChunkManager &cm, Array<uint16_t> &perishableIndices,
			Array<Item> &perishables, Array<Time> &livingTimes, Time timePassed,
			Array<Coord> &perishableCoords)
{
	for (uint16_t i = 0; i < livingTimes.capacity; i++)
	{
		uint16_t pi = perishableIndices[i];
		uint16_t c = getChunkIndexFromTile(perishableCoords[pi]);
		Temp temp = cm.getChunkTemperature(c);
		livingTimes[i] += getPerishableTime(perishables[i], timePassed, temp);
		Item p = perishables[i];
		if (livingTimes[i] > perishableDestructionTimes[p])
			lm.markDestroyed(pi);
	}
}


