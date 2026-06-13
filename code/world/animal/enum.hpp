#pragma once

#include <core/data.hpp>
#include <core/packed_enum.hpp>
#include <cstdint>

// HOT

// Moving, Mating, Direction are packed

enum class ActionStatus
{
	Idle,
	NewPath,
	Prowl, // looking for targets, but don't know where
	Flee,
	// PursuitX means sprinting to visible target
	Pursuit,
	// ApproachX means walking to known/visible target
	Approach,
	PerformAction,
	ReturnHome,
};

// TODO: make pack animals work, will search for needs using pack logic
enum class ActionDecisionStatus
{
	AnimalFoodSearch,
	AnimalBreedSearch,
	AnimalDrinkSearch,
	AnimalRejoinPack, // wanders if animal is not a pack animal, possibly change
			  // to wander
	AnimalMigration,
	Assign,
	Idle
};

enum class MatingStatus
{
	Idle,
	Searching,
	Pregnant, // equivalent of fertilized for egg layers
	Infertile
};

using AnimalStatus = PackedEnum<EnumField<Direction, 2>, EnumField<ActionStatus, 4>, EnumField<MatingStatus, 2>>;

// COLD

enum class Animal : uint8_t
{    NONE,
	Pig,
	Cow,
	Chicken,
	Duck,
	Sheep,
	Goat,
	Horse,
	Ox,
	Donkey,
	Camel,
	WaterBuffalo,
	Rabbit,
	Antelope,
	Deer,
	Moose,
	Capybara,
	Turtle,
	Elephant,
	Bison,
	Wolf,
	Bear,
	Caribou,
	// TODO: fish
	// lizard
	// frog
	// snake
	// rat
	// chipmunk
	// mole
	// hawk
	// owl
	// eagle
	// crocodile
	// rhino
	// hippo
	// giraffe
	MAX
};

enum class Diet
{
	Herbivore,
	Omnivore,
	Carnivore,
	Scavenger
};
