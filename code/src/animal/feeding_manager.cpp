#include <animal/feeding_manager.hpp>
#include <animal/bio_data.hpp>
#include <animal/diets.hpp>


namespace animal {
void FeedingManager::setInitialFeedingTime(entt::registry&reg, entt::entity& e) {
        auto type = reg.get<Type>(e);
	//TODO::calculate feeding time	
}

// TODO: events like these, what happesn to the grass tile is 
bool FeedingManager::eatGrass(entt::registry&reg, entt::entity& e) {
  // objectIndex can be enum class conversion to item, or tile index
    Type t = reg.get<Type>(e);
    uint16_t gf = calcGrassHungerFill(grassLength[tileIndex]);
    if (gf == 0) return false;
    uint16_t mh = maxHunger[type];
    uint16_t& hv = mh * reg.get<Hunger>(e);
    hv = min(mh, hv + gf);    
    return true;
}

void FeedingManager::eatFruit(entt::registry &reg, entt::entity &e, fruit::Type f) {
        Hunger &h = reg.get<Hunger>(e);  
        h = min(h + fruitHungerFill[f], maxHunger[animal]);
}

void FeedingManager::eatPlant(entt::registry &reg, entt::entity &e,
                              plant::Type p) {
  Hunger &h = reg.get<Hunger>(e);
  	h  = min(hunger[index] + plantHungerFill[plant], maxHunger[animal]);
}

  //TODO: perhaps have two levels of scanFood, one for within sight, first triggered, one for a search, like this
void FeedingManager::scanFood(entt::registry& reg, entt::entity& e) {
  const Type t = reg.get<Type>(e);
  auto index = entt::to_entity(e);
  uint16_t lowest = 0;
  //TODO
  auto rt = roamThreshold[t];
  if (carnivores[t]) {
    uint32_t preyIndex;
    BitsetTable bt = food::carnivoreDiets[t];
    for (Type prey : bt) {
      // TODO
      tpi = getNearest(e, prey);      
      //possible improvement/alternate method: do not search for plants and animals in non-native biomes!
      auto d = getDistance(index, tpi);
      if (d < roamThreshold) {
	setHuntTarget(reg, e, tpi);
	return;
      }
      if (d < lowest) {
        lowest = d;
	preyIndex = tpi;
      }
      // END TODO
    }
  }

  if (scavengers[i]) {
    
  }
  
  if (herbivores[t]) {
    uint32_t forageIndex;
    BitsetTable bt = food::getHerbivoreDiet(t);
      for (Type fd : bt) {
      // TODO
      tpi = getNearest(e, fd);
      auto d = getDistance(index, forageIndex);
      if (d < roamThreshold) {
        setForageTarget(reg, e, tfi);
	
	return;
      }
      if (d < lowest) {
        lowest = d;
	forageIndex = tfi;
      }
      // END TODO
      }
      if (carnivores[t]) {
        setHuntTarget(reg, e, preyIndex);
	return;
      } setForageTarget(reg, e, forageIndex);
  }
}

void setForageTarget() {
  
}

void setHuntTarget() {

}

// in ticks
int FeedingManager::calculateTimeTillFeed(int hungerAmount, Animal animal) {
	float maxHunger;
	float tickBurnRate;
	int timeTillFeed;

	int feedingThreshold = maxHunger / 2;
	if (hungerAmount < feedingThreshold) return 0;
	else return static_cast<int>((hungerAmount - feedingThreshold) / burnRate);
}

void FeedingManager::preparePreyFeed(int animalIndex) {
	addEvent(calculateTimeTillFeed(hunger[animalIndex] + futureConsumption, feeder), EventType::PreyFeed, static_cast<int>(feeder), animalIndex);
}

//TODO: if outDistSqr not required, do not do it
void FeedingManager::preparePredatorFeed(int animalIndex) {

	addEvent(calculateTimeTillFeed(hunger[animalIndex] + futureConsumption, feeder), EventType::PredatorFeed, animalType, animalIndex);
}

};
