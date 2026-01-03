#include <animal/breeding_manager.hpp>
#include <cerrno>
#include <system_error>

namespace animal { 

void BreedingManager::layEgg(AnimalRegistry& ar, entt::entity& e) {
  Coord animalCoord = ar.getCoord(e);
	EggManager::addEgg(animalCoord, animal, fertilized);
}

entt::entity& BreedingManager::findBreedingPartner(AnimalRegistry& ar, entt::entity& e) {
  
}

// doubles as carrying fertile egg for egg layers
void BreedingManager::activatePregnancy(AnimalRegistry &ar, entt::entity &e) {
  entt::registry r = ar.get();
        r.get<Mating>(e) = MatingStatus::Pregnant;
	//event which adds timer when hen becomes unfertilized and needs to mate again
	if (isEggLayer[r.get<Type>(e)]) {
		//TODO: change values based on animal
		addEvent(40300, EventType::NotFertilized, 0, animalIndex);
		return;
	}
	//TODO: finish pregnancy timings for all animals
	switch(animals[animalIndex]) {
		default:
			pregnantAnimalTimer.push_back(160000);
	}
}

void BreedingManager::activatePuberty(entt::registry<> &registry, int index) {
  if (auto *ms = registry.try_get<MatingStatus>(index)) {
     ms->MatingStatus::Idle;
  } 
}

void BreedingManager::activateSensenence(entt::registry<>& registry, int index) {	
	if (auto *ms = registry.try_get<MatingStatus>(index)) {
	  ms->MatingStatus::Infertile;
	}
}

}
