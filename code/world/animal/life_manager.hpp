#ifndef LIFEMANAGER_HPP
#define LIFEMANAGER_HPP

#include "entity.hpp"

class LifeManager {
  Age calculateLifespan(Age originalLifespan);
  void planDeathTime() {}; // sends death event to event manager  
};


#endif
