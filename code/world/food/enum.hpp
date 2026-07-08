#pragma once
#include <cstdint>

enum class Category : uint8_t 
{
	Grass,
	Leaves,
	Reeds,
	Fruit,
	Tuber,
	Birds,
	Fish,
	Grain,
	Undeground,
	Stem,
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
