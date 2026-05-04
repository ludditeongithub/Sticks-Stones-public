#include <SDL2/SDL_video.h>
#include <core/memory.hpp>
#include <core/memory_control.hpp>
#include <render/texture.hpp>
#include <render/window.hpp>
#include <render/camera.hpp>
#include <render/draw.hpp>
#include <ui/aggregates/main_menu.hpp>

int main()
{
	initWindow() ?: printf("Init failed.");

	loadMedia();

	SDL_SetWindowFullscreen(gWindow, 0);

	int screenWidth, screenHeight;

	SDL_GetRendererOutputSize(gWindow, screenWidth, screenHeight);
	int factor = std::min((int)(screenWidth/RAW_SCREEN_WIDTH), (int)(screenHeight/RAW_SCREEN_HEIGHT));

	SDL_RenderSetScale(gRenderer, factor);

	MainMenu* mainMenu = new MainMenu({screenWidth, screenHeight});
}
