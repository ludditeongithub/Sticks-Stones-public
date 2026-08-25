#include <simulation/game.hpp>
#include <systems/continuous/actions.hpp>
#include <world/unit/database.hpp>
#include <world/world.hpp>

void Game::game_loop()
{
	bool quit = false;
	SDL_Event e;
	while( !quit )
	{			
		while( SDL_PollEvent( &e ) != 0 )
		{
			handle_event(&e);
		}
		absolute_time += TIME_PER_FRAME;
		frame_loop();
		if (absolute_time % HOUR_LENGTH) hourly_loop();
		if (absolute_time % DAY_LENGTH) daily_loop();
	}
}	

void Game::frame_loop(World& world)
{
		handle_actions(this);
		// TODO: set new intertias/actions
		// Animations
		draw_entities(world, {0, 0}, tile_database->tiles, animal_database->ages, animal_database->frames, animal_database->statuses, unit_database->frames, unit_database->ages, unit_database->frame_datas, search);		
}

void Game::hourly_loop()
{
		
}
