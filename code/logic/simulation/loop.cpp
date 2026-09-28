#include <logic/simulation/game.hpp>
#include <data/const/time_data.hpp>
#include <display/render/main.hpp>
#include <logic/simulation/simulation.hpp>

void Game::game_loop()
{
	    SDL_Event e;	
		while( SDL_PollEvent( &e ) != 0 )
		{
			handle_event(&e);
		}
		absolute_time += TIME_PER_FRAME;
		frame_loop();
		if (absolute_time % HOUR_LENGTH) hourly_loop();
		if (absolute_time % DAY_LENGTH) daily_loop();
}	

void Game::frame_loop()
{
		handle_player_actions();
		process_simulation(TIME_PER_FRAME);
		render(*this);	
}

void Game::hourly_loop() {}

void Game::daily_loop() {}
