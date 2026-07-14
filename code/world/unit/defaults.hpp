#pragma once
#include <cmath>
#include <core/random.hpp>
#include <core/data.hpp>
#include <world/world.hpp>
#include <world/chunk/data.hpp>

constexpr Frame BASE_WALKING_FRAMES = 8;
constexpr Frame BASE_RUNNING_FRAMES = 8;

float generateSkinWarmth(float parent1, float parent2)
{
	float crossedValue = std::lerp(parent1, parent2, 0.5);
	return std::lerp(crossedValue, random_chance->next(), 0.08);
}

float generateSkinWarmth(World &world, Coord coord)
{
  uint16_t chunk = getChunkIndexFromTile(coord);
	uint16_t longitude = world.getChunkTimeZone(chunk);
	return std::lerp(longitude, random_chance->next(), 0.3);
}

float generateMelanin(World& world, Coord coord) {
    uint16_t chunk = getChunkIndexFromTile(coord);
	uint16_t latitude = world.getChunkTimeZone(chunk);
	return std::lerp(latitude, random_chance->next(), 0.3);
}

float generateMelanin(float parent1, float parent2) {
        float crossedValue = std::lerp(parent1, parent2, 0.5);
	return std::lerp(crossedValue, random_chance->next(), 0.08);
}
