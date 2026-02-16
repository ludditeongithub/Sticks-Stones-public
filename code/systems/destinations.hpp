#include <core/data.hpp>
#include <core/containers.hpp>
#include <schedule/dispatch.hpp>
#include <world/food/categories.hpp>
#include <world/animal/enum.hpp>
#include <world/animal/tables.hpp>

//TODO: possible optimization: separate herbivores and carnivores into separate loops, to improve cache efficiency
void setHungryDestinations(DispatchData<Animal> &dispatch) {
  Array<Animal> &animals = dispatch.types;
  Array<Coord> &positions = dispatch.positions;
  Array<Coord> &destinations = dispatch.destinations;

  
  enum class Type { Herbivore, Carnivore, Scavenger };
  for (int i = 0; i < animals.size; i++) {
    Animal a = animals[i];
    uint16_t lowest = 0;
    Coord nearest;
      auto rt = roamThreshold[a];
      auto pos = positions[i];
      Coord loc;
      bool found = false;      
      Type t = Type::Herbivore;
        if (herbivores[a]) {
          BitsetTable bt = herbivoreDiets[a];
          for (Food fd : bt) {
            loc = getNearestFood(fd);
            auto d = getDistance(pos, loc);
            if (d < rt) {
              setForageTarget(loc, destinations);
              continue;
            }
            if (d < lowest) {
              lowest = d;
              nearest = loc;
              t = Type::Herbivore;
            }
          }          
        }

      if (carnivores[a]) {
	uint32_t preyIndex;
	BitsetTable bt = carnivoreDiets[a];
	for (Animal prey : bt) {
	  loc = getNearestAnimal(prey);      
      //possible improvement/alternate method: do not search for plants and animals in non-native biomes!
          auto d = getDistance(pos, loc);
	  auto rt = roamThreshold[a];
	  if (d < rt) {
	    setHuntTarget(loc, destinations);
	    continue;
	  }
	  if (d < lowest) {
	    lowest = d;
            nearest = loc;
	    t = Type::Carnivore;
	  }
	}
      }

      if (scavengers[i]) {
      }

      // TODO: SET action to SEARCH if not in roamThreshold
      switch (t) {
      case Type::Herbivore:
        setForageTarget(loc, destinations);
        break;
      case Type::Carnivore:
        setHuntTarget(loc, destinations);
	break;
      case Type::Scavenger:
        setScavengeTarget(loc, destinations);
	break;
      }        
  }
}


void scanDrink(DispatchData dispatch);

void scanMigration(DispatchData dispatch);

