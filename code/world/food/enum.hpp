#pragma once
#include <cstdint>

enum class Category : uint8_t 
{
	Grasses,
	Leaves,
	Reeds,
	Fruits,
	Tubers,
	Birds,
	Fishes,
	Grains,
	Undergrounds,
	Stems,
	SmallMammals,
	MediumMammals,
	LargeMammals,
	SmallReptiles,
	LargeReptiles,
	MAX
};

enum class PreservationState : uint8_t
{
	Plain,
	Refridgerated,
	Frozen,
	Fermented,
	FermentedRefridgerated,
	FermentedFrozen,
	Spoiled,
	SpoiledRefridgerated,
	SpoiledFrozen,
	SpoiledFermented,
	SpoiledFermentedRefridgerated,
	SpoiledFermentedFrozen,
	HiddenDiseased,
	HiddenDiseasedSpoiled,
	MAX
};
