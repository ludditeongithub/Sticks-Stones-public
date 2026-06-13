#pragma once
#include "enum.hpp"
#include "defaults.hpp"
#include "macros/database.hpp"
#include <core/containers.hpp>
#include <core/data.hpp>
#include <core/random.hpp>
#include <cstdint>
#include <systems/find_nearest.hpp>
#include <world/world.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/archives/binary.hpp>
#include <cereal/types/stack.hpp>
#include <macros/constructors.h>

struct AnimalDatabase
{
public:
	static constexpr uint32_t ENTITY_SIZE =
	    sizeof(Coord) +
	    sizeof(Health) +
	    sizeof(Hunger) +
	    sizeof(Time) +
	    sizeof(Frame) +
	    sizeof(AnimalStatus) +
	    sizeof(Action) +
	    sizeof(uint16_t) +
	    sizeof(TargetType) +
	    sizeof(Animal);

#define ANIMAL_INDEPENDENT_MEMBERS(X) \
X(SearchGrid& search)
  
#define ANIMAL_RUNTIME_ARRAYS(X)                                          \
	X(Health, healths, maxHealths[animal] * INFANT_HEALTH_MODIFIER, maxHealths[animal])        \
	X(Hunger, hungers, maxHungers[animal] * INFANT_HUNGER_MODIFIER, maxHungers[animal])        \
	X(Time, ages, 0, randomAge(animal))                                                        \
	X(Frame, frames, 0, 0)                                                                     \
	X(AnimalStatus, animalStatuses, DEFAULT_ANIMAL_STATUS, DEFAULT_ANIMAL_STATUS)              \
	X(Action, actions, Action::Assign, Action::Assign)                                         \
	X(uint16_t, targets, std::numeric_limits<uint16_t>::max(),                                 \
	  std::numeric_limits<uint16_t>::max())                                                    \
	X(TargetType, targetTypes, TargetType::NONE, TargetType::NONE)                             \
  X(Animal, animals, animal, animal)                                                         \
  X(Sex, sexes, random_bool->next(), random_bool->next())

#define ANIMAL_STD_CONTAINERS(X)

    DEFAULT_DATABASE_CREATION(Animal, animal, ANIMAL);

  inline void addAnimals(AnimalSpawnBuffer asb);
  inline void move(size_t i);
};
