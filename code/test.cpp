#include "display/render/sprite.hpp"
#include <display/render/screen.hpp>
#include <logic/simulation/world_gen.hpp>
#include <data/run/world.hpp>

int main()
{
		sprite::load_sprites();
		g_window_system.init_window();
		WorldSpawner ws = WorldSpawner(500, 500);
		g_world->load_chunk_data(ws);
		bool open = true;
		while (open)
				{
						
				}
		g_window_system.close_window();	
}
