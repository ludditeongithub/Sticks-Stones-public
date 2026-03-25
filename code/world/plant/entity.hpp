#pragma once

#include "enum.hpp"
#include <core/containers.hpp>
#include <stack>
#include <stdint.h>
#include <systems/find_nearest.hpp>
#include <world/plant/tables.hpp>
#include <simulation/world_gen.hpp>

struct PlantDatabase
{
	static constexpr uint32_t ENTITY_SIZE =
	    sizeof(Plant) + sizeof(float) + sizeof(Coord) + sizeof(float) + sizeof(Time);

	SearchGrid& search;
	std::stack<uint16_t> nextPlantIndex;
	int size = 0;
	Array<Plant> plantList;
	Array<float> nextGrowth;
	Array<Coord> coords;
	Array<float> tileWater;
	Array<Time> lastFullyWatered;

	PlantDatabase(Arena* arena, SearchGrid& sg, uint16_t size) : search(sg) {
		plantList = arena_make_array<Plant>(arena, size);
		nextGrowth = arena_make_array<float>(arena, size);
		coords = arena_make_array<Coord>(arena, size);
		tileWater = arena_make_array<float>(arena, size);
		lastFullyWatered = arena_make_array<Time>(arena, size);
	}

	inline void destroyPlant(uint16_t i);
	inline uint32_t getPlantIndex();
	void releasePlantSource(std::vector<Object> &rTileObject,
				std::vector<std::pair<int, int>> &rTileCoords, int tileIndex);
	inline bool viableHarvest(int plantIndex);
	inline void setGerminationTime(int seedIndex);
	inline void germinate(int seedIndex, bool randomGrowth, ObjectDatabase &od);
	inline void prepareSeedDropping(int animalIndex, int plantIndex, bool regrowth);
	void attemptPlantGrowth(int plant, int time, int biomeIndex);
	inline void excreteSeed(int animalIndex, Plant plant);
	inline void plant(int unitIndex, Plant plant);
	inline void killTree(int plantIndex);
	inline void killPlant(int plantIndex);
};

struct RegrowthPlantDatabase : PlantDatabase
{
	void destroyPlant(uint16_t i) { PlantDatabase::destroyPlant(i); }
};
