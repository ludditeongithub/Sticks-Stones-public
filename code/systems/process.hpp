#pragma once
#include <world/world.hpp>
#include "updates.hpp"
#include <simulation/game.hpp>
#include <simulation/weather.cpp>

void Game::process_world_daily() { update_daily_insolations(get_day()); }

void Game::process_world_hourly(World* world)
{
	world->update_chunk_temperature();
	//world->update_chunk_weather();
}	

//every tick
void Game::process_world(World* world)
{	
	Array<float> cloud_covers; //TODO
	plant_database->update_plants(world->temperatures, world->daily_insolations, cloud_covers, 1);

	regrowth_plant_databases->update_regrowth_plants(item_database, world, tile_database.tile_waters, 1);

}	
