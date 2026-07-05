#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <cereal/archives/binary.hpp>
#include <core/memory.hpp>
#include <core/memory_control.hpp>
#include <render/texture.hpp>
#include <render/camera.hpp>
#include <render/draw.hpp>
#include <ui/aggregates/main_menu.hpp>
#include <cereal/archives/json.hpp>
#include <ui/system.hpp>
#include <ui/first_launch.hpp>
#include <fstream>	

int main()
{
	SDL_Init();
	if (TTF_Init() == -1)
	{
		printf("TTF_Init failed: %s\n", TTF_GetError());
	}

	// SDL_GetRendererOutputSize(window, userScreenWidth, userScreenHeight);
	// int factor = std::min((int)(userScreenWidth/SCREEN_WIDTH), (int)(userScreenHeight/SCREEN_HEIGHT));
        launch();
	// SDL_RenderSetScale(gRenderer, factor);	
}
