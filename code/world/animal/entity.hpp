#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <cstdint>
#include <stack>
#include "enum.hpp"
#include <core/data.hpp>
#include <core/containers.hpp>
#include <core/packed_enum.hpp>
#include <world/unit/rolesAndActions.hpp>

// referenced arrays are stored with units to iterate together.
struct AnimalDatabase {
  uint16_t size = 0;
  bool active; //active animalDatabases are ones in player territory; these are processed much more frequently.
  std::stack<size_t> freeSlots;
  std::vector<bool> alive;

  Array<Animal> animals;
  Array<Coord> coords;
  Array<Health> healths;
  Array<Hunger> hungers;
  Array<Time> ages;
  Array<AnimalStatus> animalStatuses;
  std::vector<bool> sexs;
  Array<Action> actions;
  Array<uint32_t> targets;
  Array<TargetType> targetTypes; //consider packing with animal statuses as this is related to movement.
};

inline void spawnAnimal(Animal animal, Coord coord, AnimalDatabase& ad, bool sex) {
  ad.animals.emplace_back(animal);
  ad.coords.emplace_back(coord);
  ad.healths.emplace_back(maxHealths[animal]);
  ad.hungers.emplace_back(maxHungers[animal] * nextRandomPropFrac());  
  ad.ages.emplace_back(maxAges[animal] * nextRandomPropFrac());
  ad.animalStatuses.emplace_back(PackedEnum3<Direction, 2, MovingStatus, 4, MatingStatus, 2>(Direction::North,
											     MovingStatus::Idle, MatingStatus::Idle));
  ad.sexs.emplace_back(sex);
  ad.actions.emplace_back(Action::Assign);
  ad.targets.emplace_back(std::numeric_limits<uint32_t>::max);
  ad.targetTypes.emplace_back(TargetType::NONE);
}

inline void birthAnimal(Animal animal, Coord coord, AnimalDatabase& ad, bool sex) {
  ad.animals.emplace_back(animal);
  ad.coords.emplace_back(coord);
  ad.healths.emplace_back(maxHealths[animal]);
  ad.hungers.emplace_back(maxHungers[animal] * nextRandomPropFrac());  
  ad.ages.emplace_back(0);
  ad.animalStatuses.emplace_back(PackedEnum3(Direction::North,
 MovingStatus::Idle, MatingStatus::Idle));
  ad.sexs.emplace_back(sex);
  ad.actions.emplace_back(Action::Assign);
  ad.targets.emplace_back(std::numeric_limits<uint32_t>::max);
  ad.targetTypes.emplace_back(TargetType::NONE);  
  ad.alive[ad.size++] = true;
}

inline void killAnimal(uint16_t index, AnimalDatabase& ad) {
  ad.alive[index] = false;
  ad.freeSlots.push(index);
}

// move animal from passively processed list into player bounds.
inline void transferAnimal(size_t i, AnimalDatabase& oldDB, AnimalDatabase& newDB) {
  if (newDB.freeSlots.empty()) {
  newDB.animals.emplace_back(oldDB.animals[i]);
  newDB.coords.emplace_back(oldDB.coords[i]);
  newDB.healths.emplace_back(oldDB.healths[i]);
  newDB.hungers.emplace_back(oldDB.hungers[i]);
  newDB.ages.emplace_back(oldDB.ages[i]);
  newDB.animalStatuses.emplace_back(oldDB.animalStatuses[i]);
  newDB.sexs.emplace_back(oldDB.sexs[i]);
  newDB.actions.emplace_back(oldDB.actions[i]);
  newDB.targets.emplace_back(oldDB.targets[i]);
  newDB.targetTypes.emplace_back(oldDB.targetTypes[i]);
  oldDB.alive[i] = false;
  oldDB.freeSlots.push(i);
  newDB.alive[newDB.size++] = true; 
  } else {
    size_t n = newDB.freeSlots.top();
    newDB.freeSlots.pop();
  newDB.animals[n] = oldDB.animals[i];
  newDB.coords[n] = oldDB.coords[i];
  newDB.healths[n] = oldDB.healths[i];
  newDB.hungers[n] = oldDB.hungers[i];
  newDB.ages[n] = oldDB.ages[i];
  newDB.animalStatuses[n] = oldDB.animalStatuses[i];
  newDB.sexs[n] = oldDB.sexs[i];
  newDB.actions[n] = oldDB.actions[i];
  newDB.targets[n] = oldDB.targets[i];
  newDB.targetTypes[n] = oldDB.targetTypes[i];
  oldDB.alive[i] = false;
  oldDB.freeSlots.push(i);
  newDB.alive[n] = true;   
  } 
}

#endif
