#pragma once
#include <SDL2/SDL_events.h>
#include <display/ui/components/button.hpp>
#include <display/render/sprite.hpp>
#include <logic/simulation/game.hpp>

// TODO: load_game_button

    const int button_left_alignment = SCREEN_WIDTH / 2 - (sprite::buttons[ButtonSprite::Main].w / 2);
	
	const SCoord new_left_corner = {button_left_alignment, 2 * SCREEN_HEIGHT / 6};
	const SCoord load_left_corner = {button_left_alignment / 2, 3 * SCREEN_HEIGHT / 6};
	const SCoord options_left_corner = {button_left_alignment / 2, 4 * SCREEN_HEIGHT / 6};
	const SCoord about_left_corner = {button_left_alignment / 2, 5 * SCREEN_HEIGHT / 6};

struct MainMenu
{
	bool active = false;
	uint16_t user_screen_width;
	uint16_t user_screen_height;
	uint8_t raw_to_user_scalar;
	// Button Positions
	SDL_Rect background;
	
	MainButtonUI new_game_button;
	MainButtonUI load_game_button;
	MainButtonUI about_button;
	MainButtonUI options_button;
	
	SCoord video_left_corner;	
	SCoord audio_left_corner;
	//SCoord keybindings_left_corner;

	MainButtonUI video_button;
	MainButtonUI audio_button;
	//MainButtonUI keybindings_button;
	SDL_Rect main_menu_viewport;

	enum class Mode
	{
		Main,
		Options,
		Load,
		Video,
		Audio
	};
	
	Mode mode;

	MainMenu();

	void activate();

	void render();

	void main_render();

	void audio_render();

	void load_render();

	void options_render();

	void video_render();
	
	void handle(SDL_Event *e);

	void main_handle(SDL_Event *e, SCoord mouse_position);
		
	void load_handle(SDL_Event *e, SCoord mouse_position);
	void options_handle(SDL_Event *e, SCoord mouse_position);
	void audio_handle(SDL_Event *e, SCoord mouse_position);
	void video_handle(SDL_Event *e, SCoord mouse_position);
};

MainMenu* g_main_menu;
