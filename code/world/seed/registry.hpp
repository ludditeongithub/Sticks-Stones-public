#ifndef SEED_REGISTRY_HPP
#define SEED_REGISTRY_HPP

#include "enum.hpp"
#include "entity.hpp"

namespace seed {
  
class SeedRegistry
{
private:
  entt::registry<> registry;
public:
  SeedRegistry() {};
  entt::entity addSeed(Type type, Position pos) {
    auto e = registry.create();
    registry.emplace<Type>(e, type);
    registry.emplace<Position>(e, pos);
    registry.emplace<Lifespan>(e, 0.0);
    registry.emplace<GrowthMisses>(e, 0);
    return e;
  }
  void deleteSeed() {}
};

}



#endif
