#include "database.hpp"

inline void AnimalDatabase::killAnimal(size_t index)
{
	if (remove(index))
	  makeCorpse(animals[index], coords[index]);
	else
	  {
	    //TODO: error
	  }
}

inline void AnimalDatabase::addAnimals(AnimalSpawnBuffer asb)
{
	for (size_t i = 0; i < asb.size; i++)
	  if (spawn(asb.types[i], asb.coords[i], false)) {}
	  else
	    {
	      //TODO: error
	    }
}

inline void AnimalDatabase::birthAnimal()
{
  
}

// move animal from passively processed list into player bounds.
inline void transferAnimal(uint16_t i, AnimalDatabase &oldDB, AnimalDatabase &newDB)
{
	if (newDB.freeSlots.empty())
	{
		newDB.animals.push(oldDB.animals[i]);
		newDB.coords.push(oldDB.coords[i]);
		newDB.healths.push(oldDB.healths[i]);
		newDB.hungers.push(oldDB.hungers[i]);
		newDB.ages.push(oldDB.ages[i]);
		newDB.animalStatuses.push(oldDB.animalStatuses[i]);
		newDB.sexs.emplace_back(oldDB.sexs[i]);
		newDB.actions.push(oldDB.actions[i]);
		newDB.targets.push(oldDB.targets[i]);
		newDB.targetTypes.push(oldDB.targetTypes[i]);
		oldDB.alive[i] = false;
		oldDB.freeSlots.push(i);
		newDB.alive[newDB.size++] = true;
	}
	else
	{
		uint16_t n = newDB.freeSlots.top();
		newDB.freeSlots.pop();
		newDB.animals[n] = oldDB.animals[i];
		newDB.coords[n] = oldDB.coords[i];
		newDB.healths[n] = oldDB.healths[i];
		newDB.hungers[n] = oldDB.hungers[i];
		newDB.ages[n] = oldDB.ages[i];
		newDB.animalStatuses[n] = oldDB.animalStatuses[i];
		newDB.sexs[n] = oldDB.sexs[i];
		newDB.actions[n] = oldDB.actions[i];
		newDB.targets[n] = oldDB.targets[i];
		newDB.targetTypes[n] = oldDB.targetTypes[i];
		oldDB.alive[i] = false;
		oldDB.freeSlots.push(i);
		newDB.alive[n] = true;
	}
}
