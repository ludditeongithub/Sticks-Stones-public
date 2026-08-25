#pragma once
#include "core/mouse.hpp"
#include "render/screen.hpp"
#include <SDL2/SDL_events.h>
#include <core/data.hpp>
#include <ui/components/button.hpp>
#include <render/sprite_sheet_settings.hpp>
#include <simulation/game.hpp>

// TODO: load_game_button

struct MainMenu
{
	uint16_t user_screen_width;
	uint16_t user_screen_height;
	uint8_t raw_to_user_scalar;
	// Button Positions
	SCoord background = {}; //TODO
	int button_left_alignment = SCREEN_WIDTH / 2 - (sprite::button[static_cast<int>(ButtonSprite::Main)].w / 2);
	
	SCoord new_left_corner = {button_left_alignment, 2 * SCREEN_HEIGHT / 6};
	SCoord load_left_corner = {button_left_alignment / 2, 3 * SCREEN_HEIGHT / 6};
	SCoord options_left_corner = {button_left_alignment / 2, 4 * SCREEN_HEIGHT / 6};
	SCoord about_left_corner = {button_left_alignment / 2, 5 * SCREEN_HEIGHT / 6};
	MainButtonUI new_game_button;
	MainButtonUI load_game_button;
	MainButtonUI about_button;
	MainButtonUI options_button;
	
	SCoord video_left_corner;	
	SCoord audio_left_corner;
	SCoord keybindings_left_corner;

	MainButtonUI video_button;
	MainButtonUI audio_button;
	MainButtonUI keybindings_button;
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

	MainMenu() 
	{		
          new_game_button = MainButtonUI(NewGameBF(this), new_left_corner);
          load_game_button = MainButtonUI(LoadMenuBF(), load_left_corner);
          about_button = MainButtonUI(AboutBF(), about_left_corner);
          options_button = MainButtonUI(OptionsBF(), options_left_corner);

          video_left_corner = {button_left_alignment, 2 * SCREEN_HEIGHT / 6};
          audio_left_corner = {button_left_alignment / 2, 3 * SCREEN_HEIGHT / 6};
          keybindings_left_corner = {button_left_alignment / 2, 4 * SCREEN_HEIGHT / 6};

          video_button = ButtonUI(VideoBF(), video_left_corner);
          audio_button = ButtonUI(AudioBF(), audio_left_corner);
          keybindings_button = ButtonUI(KeybindingsBF(),keybindings_left_corner);
	}

	void render()
	{
        new_game_button.render();
	load_game_button.render();
	about_button.render();
	options_button.render();
	video_button.render();
	audio_button.render();
	keybindings_button.render();
	}	
	
	void handle_event(SDL_Event *e)
	{
		SCoord mouse_position;
		SDL_GetMouseState(&mouse_position.x, &mouse_position.y);
		switch (mode)
		{
		case Mode::Main:
			main_handle(e, mouse_position);
			break;
		case Mode::Load:
			load_handle(e, mouse_position);
			break;
		case Mode::Options:
			options_handle(e, mouse_position);
			break;
		case Mode::Video:
			video_handle(e, mouse_position);
			break;
		case Mode::Audio:
			audio_handle(e, mouse_position);
			break;
		}
	}

	void main_handle(SDL_Event *e, SCoord mouse_position)
	{
		
	}

	void load_handle(SDL_Event *e, SCoord mouse_position)
	{
		//TODO: finish UI element ScrollableList. saves are ScrollableList.
		if (e->type == SDL_MOUSEBUTTONUP) {
			if (mouse_inside(mouse_position, new_left_corner, button_dimensions)) {
				start_game();
			}
			else if (mouse_inside(mouse_position, load_left_corner, button_dimensions))
			{
				mode = Mode::Load;
			} else if (mouse_inside(mouse_position, options_left_corner, button_dimensions)) mode = Mode::Options;
		}
	}		

	void options_handle(SDL_Event *e, SCoord mouse_position)
	{
		if (e->type == SDL_MOUSEBUTTONUP) {
			if (mouse_inside(mouse_position, audio_left_corner, button_dimensions)) mode = Mode::Audio;
			else if (mouse_inside(mouse_position, video_left_corner, button_dimensions)) mode = Mode::Video;
		}
	}
	void audio_handle(SDL_Event *e, SCoord mouse_position);
	void video_handle(SDL_Event *e, SCoord mouse_position);
};	
