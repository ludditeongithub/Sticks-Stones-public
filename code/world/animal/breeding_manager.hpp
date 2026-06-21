#ifndef BREEDING_MANAGER_HPP
#define BREEDING_MANAGER_HPP

#include "database.hpp"
#include "registry.hpp"

class BreedingManager : public Manager
{
      public:
	void handleEvent(Event &BirthEvent);
	void handleEvent(Event &ConceptionEvent);
	void handleEvent(Event &SexEvent);
	void handleEvent(Event &MateSearchEvent);
	void handleEvent(Event &PubertyEvent);

      private:
	using Event = std::variant<BirthEvent, ConceptionEvent, SexEvent, MateAttemptEvent,
				   MateSearchEvent, PubertyEvent, SesenenceEvent>;
	struct Fertility
	{
		Percentage Fertility;
	};

	Fertility calculateFertility();
	void searchForMates();

	void layEgg(Animal animal, int animalIndex);
	void birthAnimal(Animal animal, int animalIndex);
	void activatePuberty(entt::registry<> &registry, int index);
	void activatePregnancy(int animalIndex);
	void activateSesenence(entt::registry<> &registry, int index);
	// TODO: make into betset bool eggLayer(Animal animal);
	void setInitialBreedEvent(int i);
};

#endif
