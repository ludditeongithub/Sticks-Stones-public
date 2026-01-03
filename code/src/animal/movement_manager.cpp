#include <animal/movement_manager.hpp>
#include <animal/entity.hpp>
#include <error.h>


void MovementManager::processMovement(entt::registry &reg, entt::entity &e) {
  using enum animal::MovingStatus;
  switch (reg.get<MovingStatus>(e)) {
  case Idle:
    return;
  case Wander:
    wander(reg, e);
    return;
  case Prowl:
  case Hunt:
    
  case ApproachFood:
    approachFood(reg, e);
  case Flee:
    flee(reg, e);
  }
}

void MovementManager::approachFood(entt::registry &reg, entt::entity &e) {
  TargetType tt = reg.get<Target>(e).type;
  using enum TargetType;
  if (tt == Forage) {
     
  } else if (tt == Corpse) {
    
  } else {

  }

}



