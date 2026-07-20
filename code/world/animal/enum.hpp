#pragma once
#include <core/data.hpp>
#include <core/packed_enum.hpp>
#include <cstdint>

// HOT

// Moving, Mating, Direction are packed

enum class MatingStatus
{
	Idle,
	Searching,
	Pregnant, // equivalent of fertilized for egg layers
	Infertile
};

using AnimalStatus = PackedEnum<Field<Direction, 2>, Field<MatingStatus, 2>>;

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
