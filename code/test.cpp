#include "display/render/sprite.hpp"
#include "display/ui/main/main_menu.hpp"
#include "logic/simulation/game.hpp"
#include <display/render/screen.hpp>
#include <logic/simulation/world_gen.hpp>

int main()
{
		sprite::load_sprites();
		g_window_system.init_window();

		*g_main_menu = MainMenu();
		
		g_window_system.close_window();	
}
