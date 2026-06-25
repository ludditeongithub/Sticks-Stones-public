#pragma once

#include "world/world.hpp"
void Game::gameLoop()
{
	bool quit = false;
	SDL_Event e;
	while( !quit )
	{			
		while( SDL_PollEvent( &e ) != 0 )
		{
			handleEvent(&e);
		}
		absoluteTime += TIME_PER_FRAME;
		frameLoop();
		if (absoluteTime % HOUR_LENGTH) hourlyLoop();
		if (absoluteTime % DAY_LENGTH) dailyLoop();
	}
}	

void Game::frameLoop(World& world)
{
		// Positions
		
		// Animations
		drawEntities(world, {0, 0}, tileDatabase->tiles, animalDatabase->ages, animalDatabase->frames, animalDatabase->statuses, unitDatabase->frames, unitDatabase->ages, unitDatabase->frameDatas, search);		
}

void Game::hourlyLoop()
{
		
}
