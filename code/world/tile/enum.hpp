#pragma once
#include <core/packed_enum.hpp>
#include <cstdint>
#include <world/chunk/enum.hpp>

enum class Tile : uint8_t
{
	EMPTY,
	DeepWater,
	ShallowSaltWater,
	RiverSource,
	FlowingWater,
	ShallowWater,
	Gravel,
	FrozenSoil,
	Snow,
	Ice,
	Stone,
	Ore,
	GemOre,
	RockSalt,
	Sand,
	Podzol,
	PlowedPodzol,
	LoamSoil,
	PlowedLoamSoil,
	PeatSoil,
	PlowedPeatSoil,
	SandySoil,
	PlowedSandySoil,
	ClaySoil,
	PlowedClaySoil,
	SiltySoil,
	PlowedSiltySoil,
	RockySoil,
	PlowedRockySoil,
	AridSoil,
	Oxisol,
	PlowedOxisol,
	Gleysol,
	Hardpan,
	Path,
	DirtRoad,
	StoneRoad,
	BrickRoad,
	PavedRoad,
	ConcreteRoad,
	WoodFloor,
	Carpet,
	StoneFloor,
	BrickFloor,
	MAX,
};

enum class Grass : uint8_t
{
	NONE,
	Grass,
	SavannahGrass,
	DryGrass,
	MAX
};

using TileData = PackedEnum2<Tile, 5, Grass, 3>;
