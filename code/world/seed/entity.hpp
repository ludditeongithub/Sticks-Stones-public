#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <plant/enum.hpp>

namespace seed {

struct Type {
  Plant type;
};

   struct Position {
    int x;
    int y;
   };
  
    struct Lifespan {
      uint16_t lifespan;
    };
  
    struct GrowthMisses {
      uint16_t growthMisses;
    };

}


#endif
