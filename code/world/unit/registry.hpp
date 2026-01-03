#ifndef UNIT_H_
#define UNIT_H_

#include "enum.hpp"
#include "entity.hpp"
#include <entt/entt.hpp>

namespace unit {
// contains basic info that appplies to all units
 
class UnitRegistry
{
private:
  entt::registry<> registry;
public:
  UnitRegistry() {};
  void addUnit(Sex s) {
    auto e = registry.create();
    //TODO: inventory
    registry.emplace<Inventory>(e);
    registry.emplace<Roles>(e);
    registry.emplace<Sex>(e, s);
    registry.emplace<Movement>(e, MovingStatus::Idle);
    registry.emplace<Health>(e, Unit::MAX_HEALTH);
    registry.emplace<RoleMana>(e, Unit::STARTING_ROLE_MANA);
    registry.emplace<Places>(e);
  };
};


};

//PRODUCERS
using ProductVariant<Item, Container, Vehicle, Buildable>;
vector<ProductVariant> currentProducts;

#endif // UNIT_H_
