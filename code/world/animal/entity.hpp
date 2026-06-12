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

#define ANIMAL_RUNTIME_ARRAYS(X) \
  X(Coord, coords, coord, coord)		 \
  X(Health, healths, maxHealths[animal] * INFANT_HEALTH_MODIFIER, maxHealths[animal])			 \
  X(Hunger, hungers, maxHungers[animal] * INFANT_HUNGER_MODIFIER, maxHungers[animal])				\
  X(Time, ages, 0, randomAge(animal))							\
  X(Frame, frames, 0, 0)						\
  X(AnimalStatus, animalStatuses, DEFAULT_ANIMAL_STATUS, DEFAULT_ANIMAL_STATUS)		\
  X(Action, actions, Action::Assign, Action::Assign)			\
  X(uint16_t, targets, std::numeric_limits<uint16_t>::max(), std::numeric_limits<uint16_t>::max())	\
  X(TargetType, targetTypes, TargetType::NONE, TargetType::NONE)			\
  X(Animal, animals, animal, animal)

#define ANIMAL_STD_CONTAINERS(X) \
  X(std::vector<Sex>, sexes)

    DEFAULT_DATABASE_CREATION(Animal, animal, ANIMAL);
		
	inline void addAnimals(AnimalSpawnBuffer asb);
};
