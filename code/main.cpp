#include <SDL2/SDL_video.h>
#include <core/memory.hpp>
#include <core/memory_control.hpp>
#include <render/texture.hpp>
#include <render/window.hpp>
#include <render/camera.hpp>
#include <render/draw.hpp>
#include <ui/aggregates/main_menu.hpp>
#include <ui/system.hpp>

int main()
{
	initWindow() ?: printf("Init failed.");

	loadMedia();

	SDL_SetWindowFullscreen(gWindow, 0);

	int userScreenWidth, userScreenHeight;

	SDL_GetRendererOutputSize(gWindow, userScreenWidth, userScreenHeight);
	int factor = std::min((int)(userScreenWidth/SCREEN_WIDTH), (int)(userScreenHeight/SCREEN_HEIGHT));

	SDL_RenderSetScale(gRenderer, factor);

	UISystem* UISystem = new UISystem(userScreenWidth, userScreenHeight);

	MainMenu* mainMenu = new MainMenu(userScreenWidth, userScreenHeight);
}
