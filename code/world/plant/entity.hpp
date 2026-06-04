#pragma once

#include "enum.hpp"
#include <core/containers.hpp>
#include <stack>
#include <stdint.h>
#include <systems/find_nearest.hpp>
#include <world/plant/tables.hpp>
#include <world/animal/entity.hpp>
#include <simulation/world_gen.hpp>
#include <core/>

struct PlantDatabase
{
	static constexpr uint32_t ENTITY_SIZE =
	    sizeof(Plant) + sizeof(float) + sizeof(Coord) + sizeof(float) + sizeof(Time);

	SearchGrid& search;
	std::stack<uint16_t> nextPlantIndex;
	int size = 0;
	Array<Plant> plantList;
	Array<Time> growths; //also substitutes for age, as non-regrowth plants just die, regardless of age.
	Array<Coord> coords;
	Array<uint16_t> tileWaters;
	Array<Time> lastFullyWatered;
	Array<bool> alive;

	// Seed Data
	Array<Plant> seeds;
	Array<Coord> seedCoords;

	PlantDatabase(Arena* arena, SearchGrid& sg, uint32_t size) : search(sg) {
		plantList = arena_make_array<Plant>(arena, size);
		growths = arena_make_array<Time>(arena, size);
		coords = arena_make_array<Coord>(arena, size);
		tileWaters = arena_make_array<uint16_t>(arena, size);
		lastFullyWatered = arena_make_array<Time>(arena, size);
		alive = arena_make_array<bool>(arena, size);
	}

	void load(Arena* arena)
	{
		plantList = arena_make_array<Plant>(arena, size);
		growths = arena_make_array<Time>(arena, size);
		coords = arena_make_array<Coord>(arena, size);
		tileWaters = arena_make_array<uint16_t>(arena, size);
		lastFullyWatered = arena_make_array<Time>(arena, size);
		alive = arena_make_array<bool>(arena, size);
	}		

	inline void destroyPlant(uint16_t i);
	inline uint32_t getPlantIndex();
	inline bool viableHarvest(int plantIndex);
	inline void setGerminationTime(int seedIndex);
	inline void germinate(int seedIndex, bool randomGrowth, SearchGrid &searchGrid);
	inline void spawnSeed(Plant plant, Coord position);
	inline void prepareSeedDropping(int animalIndex, int plantIndex, bool regrowth);
	inline void attemptPlantGrowth(int plant, int time, int biomeIndex);
	inline void excreteSeed(AnimalDatabase& database, int animalIndex, Plant plant);
	inline void plant(int unitIndex, Plant plant);
	inline void killTree(int plantIndex);
	inline void killPlant(int plantIndex);

	void updatePlants(World& world, Time timePassed);
};

struct RegrowthPlantDatabase
{
	PlantDatabase plantDatabase;
	Array<Time> regrowths;
	Array<Time> ages;
	Array<uint16_t> produces;
	
	inline void germinate(int seedIndex, bool randomGrowth, SearchGrid &searchGrid);
	inline void attemptPlantGrowth(int plant, int time, int biomeIndex);
	
};

