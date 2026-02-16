#include "perishables_manager.hpp"
#include <simulation/lifetime_manager.hpp>

void processPerishables(LifetimeManager& lm, Array<size_t>& perishableIndices, Array<Coord>& perishableoords, Array<Temperature>& chunkTemperatures, Array<Item>& perishables, Array<Time>& livingTimes, Time timePassed) {
  for (size_t i = 0; i < livingTimes.capacity; i++) {
    size_t pi = perishableIndices[i];
    size_t c = coordToChunkIndex(perishableCoords[]);
    Temp temp = chunk;
    livingTimes[i] += perishableTime(timePassed, );
    Item p = perishables[i];    
    if (livingTimes[i] > perishableDestructionTimes[p]) lm.markDestroyed(pi);   
  }
}

inline bool checkRotten(Item perishable, Time livingTime);
