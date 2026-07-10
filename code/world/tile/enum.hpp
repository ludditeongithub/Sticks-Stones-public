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
	MAX
};	    

enum class Grass : uint8_t
{
	NONE,
	Grass,
	SavannahGrass,
	DryGrass,
	MAX
};

using TileData = PackedEnum<Field<Tile, 5>, Field<Grass, 3>>;

// TODO: water and floating
enum class OccupiedStatus : uint8_t
{
	Vacant,
	Item,
	Entity,
	ItemAndEntity,
	Buildable // only buildable can be on tile if true
};

enum class VisionStatus : uint8_t
{
	Hidden,
	Revealed,
	Explored,
	Claimed
};

// NOTE: 2 bits remaining
using TileStatus = PackedEnum<Field<OccupiedStatus, 3>, Field<VisionStatus, 2>>;


bool is_water(Tile tile)
{
  switch (tile) {
  case Tile::DeepWater:
    return true;
    break;
  case 	Tile::ShallowSaltWater:
    return true;
    break;
  case Tile::FlowingWater:
	  return true;
          break;
  case Tile::ShallowWater:
    return true;
    break;
  case Tile::RiverSource:
    return true;
    break;
  default:
    return false;
  }

}
