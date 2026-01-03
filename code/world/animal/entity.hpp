#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <cstdint>
#include "enum.hpp"
#include <basic/percent.hpp>
#include <basic/coord.hpp>


namespace animal { 
  struct Facing { Direction d; };
  struct Sex { bool s; };
  struct Health { Percentage h{100.0f}; };
  struct Hunger { Percentage h{100.0f}; };
  struct Age { float a; };
  struct Movement { MovingStatus m; };  
  struct Mating { MatingStatus m; };
}

#endif
