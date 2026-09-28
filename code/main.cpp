#include "display/ui/main/main_menu.hpp"
#include "logic/simulation/world_gen.hpp"
#include <SDL2/SDL_events.h>
#include <display/render/screen.hpp>

int main()
{
		g_window_system.load_sprite_sheet();
		MainMenu main_menu = MainMenu();
		main_menu.active = true;
		while (main_menu.active)
				{
						main_menu.render();
						SDL_Event* e;
						SDL_PollEvent(e);
						main_menu.handle(e);
				}	
}
