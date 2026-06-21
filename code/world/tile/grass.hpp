#pragma once
#include "enum.hpp"
#include <core/data.hpp>
#include <core/tables.hpp>
#include <world/chunk/enum.hpp>

// TODO: natural grass reproduction
Hunger GRASS_HUNGER_VALUE = 300;

inline bool tileGrass(TileData tile) { return (tile.second() != Grass::NONE); }

inline void degrassTile(TileData &tile) { tile.second() = Grass::NONE; }

namespace grass
{
inline constexpr LookupTable<Biome, float> coverages = []
{
	LookupTable<Biome, float> lt{};
	using enum Biome;
	lt[HotDesert] = 0.03;
	lt[Grassland] = 0.97;
	lt[Savanna] = 0.75;
	lt[Wetland] = 0.35;
	lt[Temperate] = 0.08;
	lt[Boreal] = 0.05;
	lt[Jungle] = 0.04;
	lt[Rocky] = 0.1;
	lt[Tundra] = 0.075;
	lt[ColdDesert] = 0.04;
	return lt;
}();


  float optimal = 1.0;
		float great = 0.5;
		float good = 0.25;
		float poorly = 0.125;
		float rarely = 0.6325;
  
inline constexpr LookupTable2D<Grass, Tile, float> tileSpawnMultipliers = []
{
                       	
	LookupTable2D<Grass, Tile, float> lt{};
        using enum Tile;
        lt[Grass::Grass][Podzol] = good;
        lt[Grass::Grass][LoamSoil] = optimal;
        lt[Grass::Grass][PeatSoil] = rarely;
        lt[Grass::Grass][SandySoil] = great;
        lt[Grass::Grass][ClaySoil] = poorly;
        lt[Grass::Grass][SiltySoil] = optimal;
        lt[Grass::Grass][RockySoil] = rarely;
        lt[Grass::Grass][AridSoil] = good;
        lt[Grass::Grass][Oxisol] = poorly;
        lt[Grass::Grass][Gleysol] = poorly;
        lt[Grass::SavannahGrass][Podzol] = poorly;
        lt[Grass::SavannahGrass][LoamSoil] = great;
        lt[Grass::SavannahGrass][PeatSoil] = rarely;
        lt[Grass::SavannahGrass][SandySoil] = optimal;
        lt[Grass::SavannahGrass][ClaySoil] = good;
        lt[Grass::SavannahGrass][SiltySoil] = great;
        lt[Grass::SavannahGrass][RockySoil] = rarely;
        lt[Grass::SavannahGrass][AridSoil] = good;
        lt[Grass::SavannahGrass][Oxisol] = good;
        lt[Grass::SavannahGrass][Gleysol] = poorly;
	return lt;
}();

inline constexpr LookupTable<Grass, Coord> temperaturePenaltyRanges = []
{
	LookupTable<Grass, Coord> lt{};
	using enum Grass;
	lt[Grass] = {41, 86};
        lt[SavannahGrass] = {64, 95};
	return lt;
}();


inline constexpr LookupTable<Grass, Coord> humidityPenaltyRanges = []
{
	LookupTable<Grass, Coord> lt{};
	using enum Grass;
	lt[Grass] = {30, 80};
        lt[SavannahGrass] = {20, 60};
	return lt;
}();
