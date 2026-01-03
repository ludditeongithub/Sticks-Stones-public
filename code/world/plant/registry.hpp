#ifndef REGISTRY_HPP
#define REGISTRY_HPP


#include "entity.hpp"
#include "enum.hpp"
#include <basic/coord.hpp>
#include <entt/entt.hpp>
#include <tile/entity.hpp>
#include <regrowth_plant/entity.hpp>
#include <regrowth_plant/enum.hpp>

namespace plant {

class PlantRegistry
{
private:
  entt::registry crops;
public:
  PlantRegistry() {};
  entt::entity addCrop(Type t, Coord p) {
      auto e = crops.create();
      crops.emplace<Type>(e, t);
      crops.emplace<Growth>(e, 0);
      crops.emplace<YieldMisses>(e, 0);
      crops.emplace<CollectedWater>(e, 0.0);
      crops.emplace<Coord>(e, p);
      return e;
  }

  entt::entity addRegrowthCrop(Type t, Coord p) {
    auto e = addCrop(t, p);
    crops.emplace<regrowth::regrowth>(e, 0.0);
    crops.emplace<regrowth::Produce>(e, 0);
    crops.emplace<regrowth::FullyGrownCount>(e, 0);
  }

    void destroyCrop(entt::entity e) {
        if (crops.valid(e)) crops.destroy(e);
    }        
};

};



#endif
