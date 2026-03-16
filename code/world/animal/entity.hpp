#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <cstddef>
#include <cstdint>
#include <stack>
#include "enum.hpp"
#include "tables.hpp"
#include "world/world.hpp"
#include <core/data.hpp>
#include <core/containers.hpp>
#include <core/random.hpp>
#include <core/packed_enum.hpp>
#include <world/unit/rolesAndActions.hpp>

// referenced arrays are stored with units to iterate together.
struct AnimalDatabase {
  uint16_t size = 0;
  bool active; //active animalDatabases are ones in player territory; these are processed much more frequently.
  std::stack<uint16_t> freeSlots;
  std::vector<bool> alive;


  // HOT: processing identical to humans
  Array<Coord> coords;
  Array<Health> healths;
  Array<Hunger> hungers;
  Array<Time> ages;
  Array<Frame> frames;

  // WARM:processing identical to humans
  Array<AnimalStatus> animalStatuses;
  std::vector<Sex> sexs;
  Array<Action> actions;
  Array<uint16_t> targets;
  Array<TargetType> targetTypes; // consider packing with animal statuses as
                                 // this is related to movement.

  // processing unique to animals
  Array<Animal> animals;	
	
  void reserve(uint16_t sz) {
    //TODO
  }

  AnimalDatabase(uint16_t sz) {	   
    alive = std::vector<bool>(sz);    
    animals = Array<Animal>(sz);
    coords = Array<Coord>(sz);
    healths = Array<Health>(sz);
    hungers = Array<Hunger>(sz);
    ages = Array<Time>(sz);
    animalStatuses = Array<AnimalStatus>(sz);
    sexs = std::vector<bool>(sz);
    actions = Array<Action>(sz);
    targets = Array<uint16_t>(sz);
    targetTypes = Array<TargetType>(sz);
    frames = Array<Frame>(sz);
  }


inline void birthAnimal(Animal animal, Coord coord, AnimalDatabase &ad,
                        bool sex) {
  if (freeSlots.empty()) {
  ad.animals.push(animal);
  ad.coords.push(coord);
  ad.healths.push(maxHealths[animal]);
  ad.hungers.push(maxHungers[animal] * chance.next());  
  ad.ages.push(maxAges[animal] * chance.next());
  ad.animalStatuses.push(PackedEnum3<Direction, 2, ActionStatus, 4, MatingStatus, 2>(Direction::North,
											     ActionStatus::Idle,MatingStatus::Idle));
  ad.sexs.emplace_back(sex);
  ad.actions.push(Action::Assign);
  ad.targets.push(std::numeric_limits<uint16_t>::max());
  ad.targetTypes.push(TargetType::NONE);
  ad.alive[ad.size++] = true;
  } else {
	  
    uint16_t i = freeSlots.top();
    freeSlots.pop();
    
  ad.animals[i] = animal;
  ad.coords[i] = coord;
  ad.healths[i] = maxHealths[animal];
  ad.hungers[i] = maxHungers[animal] * chance.next();  
  ad.ages[i] = maxAges[animal] * chance.next();
  ad.animalStatuses[i] = PackedEnum3<Direction, 2, ActionStatus, 4, MatingStatus, 2>(Direction::North,
											     ActionStatus::Idle,MatingStatus::Idle);
  ad.sexs[i] = sex;
  ad.actions[i] = Action::Assign;
  ad.targets[i] = std::numeric_limits<uint16_t>::max();
  ad.targetTypes[i] = TargetType::NONE;  
  ad.alive[i] = true;
  }
}

	inline void killAnimal(uint16_t index, AnimalDatabase& ad) {
  ad.alive[index] = false;
  ad.freeSlots.push(index);
  makeCorpse(ad.animals[index], ad.coords[index]);
}

// move animal from passively processed list into player bounds.
inline void transferAnimal(uint16_t i, AnimalDatabase& oldDB, AnimalDatabase& newDB) {
  if (newDB.freeSlots.empty()) {
  newDB.animals.push(oldDB.animals[i]);
  newDB.coords.push(oldDB.coords[i]);
  newDB.healths.push(oldDB.healths[i]);
  newDB.hungers.push(oldDB.hungers[i]);
  newDB.ages.push(oldDB.ages[i]);
  newDB.animalStatuses.push(oldDB.animalStatuses[i]);
  newDB.sexs.emplace_back(oldDB.sexs[i]);
  newDB.actions.push(oldDB.actions[i]);
  newDB.targets.push(oldDB.targets[i]);
  newDB.targetTypes.push(oldDB.targetTypes[i]);
  oldDB.alive[i] = false;
  oldDB.freeSlots.push(i);
  newDB.alive[newDB.size++] = true; 
  } else {
    uint16_t n = newDB.freeSlots.top();
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

};

#endif
