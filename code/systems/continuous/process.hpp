#pragma once
#include <world/world.hpp>
#include "updates.hpp"
#include <simulation/game.hpp>
#include <simulation/weather.cpp>

void Game::processWorldDaily() { updateDailyInsolations(getDay()); }

void Game::processWorldHourly(World* world)
{
	world->updateChunkTemperature();
	//world->updateChunkWeather();
}	

//every tick
void Game::processWorld(World* world)
{	
	Array<float> cloudCovers; //TODO
	plantDatabase->updatePlants(world->temperatures, world->dailyInsolations, cloudCovers, 1);

	regrowthPlantDatabases->updateRegrowthPlants(itemDatabase, world, tileDatabase.tileWaters, 1);

}	
