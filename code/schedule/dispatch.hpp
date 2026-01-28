#include <world/animal/enum.hpp>
#include <core/containers.hpp>
#include <core/data.hpp>
#include <world/unit/rolesAndActions.hpp>




void dispatchHungryAnimals(Array<Animal>& animals,
                                   Array<Coord>& positions,
                                   Array<Coord>& destinations,
                                   Array<Action>& actions) {
  int count = 0;
  for (int i = 0; i < actions; i++)
    if (actions[i] == Action::AnimalFoodSearch)
      count++;
  Array<Animal> sAnimals(count);
  Array<Coord> sPositions(count);
  Array<Coord> sDestinations(count);
  Array<Action> sActions(count);
  int j = 0;
  for (int i = 0; i < animals; i++) {
    if (actions[i] == Action::AnimalFoodSearch) {
      sAnimals[j++] = animals[i];
      sPositions[j++] = positions[i];
      sDestinations[j++] = destinations[i];
      sActions[j++] = actions[i];
    }
  }
  scanFood(sAnimals, sPositions, sDestinations, sActions);
}




