#include <animal/excretion_manager.hpp>
#include <basic/coord.hpp>


void ExcretionManager::prepareSeedDropping(entt::entity &animal, plant::Type plant) {
  
}

void ExcretionManager::excreteSeed(entt::registry& r, entt::entity& e, plant::Type plant) {
  addCrop(plant, r.get<Coord>(e));
}
