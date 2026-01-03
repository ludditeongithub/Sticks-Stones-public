#include "../include/scavengeables.hpp"

void ScavengeableDatabase::addScavengeable(Scavengeable scavengeable, int x,
                                           int y) {
  uint32_t index = getScavengeableIndex();
  scavengeables[index] = scavengeable;
  coords[index] = {x,y};
}

void ScavengeableDatabase::getScavengeableIndex() {
    if (nextIndex.empty()) return scavengeables.size();
    return nextIndex.pop();
}

