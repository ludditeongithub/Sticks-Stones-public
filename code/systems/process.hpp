#pragma once
#include <world/world.hpp>
#include "updates.hpp"
#include <simulation/game.hpp>
#include <simulation/weather.cpp>

void Game::processWorldDaily() { updateDailyInsolations(getDay()); }

void Game::processWorldHourly(World* world)
{
	world->updateChunkTemperature();
	world->updateChunkWeather();
}	

//every tick
void Game::processWorld(World* world)
{
	
	Array<float> cloudCovers; //TODO
	for (size_t i = 0; i < plantDatabases.size(); i++) {		
		updatePlants(world->temperatures, world->dailyInsolations, cloudCovers, 1);
	}

	for (size_t i = 0; i < regrowthPlantDatabases.size(); i++) {
		updateRegrowthPlants(itemDatabase, world, 1);
	}

}	
