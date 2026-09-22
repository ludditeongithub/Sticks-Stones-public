#pragma once
#include "core/mouse.hpp"
#include "display/render/screen.hpp"
#include "display/render/texture.hpp"
#include "display/ui/components/element.hpp"
#include <SDL2/SDL_events.h>
#include <data/types/aliases.hpp>
#include <display/ui/components/button.hpp>
#include <display/render/sprite.hpp>
#include <logic/simulation/game.hpp>

// TODO: load_game_button

struct MainMenu
{
	bool active = false;
	uint16_t user_screen_width;
	uint16_t user_screen_height;
	uint8_t raw_to_user_scalar;
	// Button Positions
	SDL_Rect background;
	static constexpr int button_left_alignment = SCREEN_WIDTH / 2 - (sprite::button[static_cast<int>(ButtonSprite::Main)].w / 2);
	
	static constexpr SCoord new_left_corner = {button_left_alignment, 2 * SCREEN_HEIGHT / 6};
	static constexpr SCoord load_left_corner = {button_left_alignment / 2, 3 * SCREEN_HEIGHT / 6};
	static constexpr SCoord options_left_corner = {button_left_alignment / 2, 4 * SCREEN_HEIGHT / 6};
	static constexpr SCoord about_left_corner = {button_left_alignment / 2, 5 * SCREEN_HEIGHT / 6};
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

	MainMenu()
	{
		  background = sprite::ui[UISprite::Background];
          new_game_button = MainButtonUI(NewGameBF(), new_left_corner);
		  load_game_button = MainButtonUI(LoadMenuBF(), load_left_corner);
          about_button = MainButtonUI(AboutBF(), about_left_corner);
          options_button = MainButtonUI(OptionsBF(), options_left_corner);

          video_left_corner = {button_left_alignment, 2 * SCREEN_HEIGHT / 6};
          audio_left_corner = {button_left_alignment / 2, 3 * SCREEN_HEIGHT / 6};
          //keybindings_left_corner = {button_left_alignment / 2, 4 * SCREEN_HEIGHT / 6};

          video_button = MainButtonUI(VideoBF(), video_left_corner);
          audio_button = MainButtonUI(AudioBF(), audio_left_corner);
          //keybindings_button = MainButtonUI(KeybindingsBF(),keybindings_left_corner);
	}

	void render()
	{
	sprite_sheet_texture.render(g_main_screen_viewport->x, g_main_screen_viewport->y,
									&background, g_main_screen_viewport);
	switch (mode) {
	case Mode::Main:
       	    main_render();
       	    break;
    case Mode::Load:
       	    load_render();
			break;
    case Mode::Options:
       	    options_render();
       	    break;
    case Mode::Video:
			video_render();
			break;
	case Mode::Audio:
       	    audio_render();
			break;
    default:
            
	}
	}

	void main_render()
	{
	new_game_button.render();
	load_game_button.render();
	about_button.render();
	options_button.render();
	video_button.render();
	audio_button.render();
	//keybindings_button.render();
	}

	void audio_render() {}

	void load_render() {}

	void options_render() {}

	void video_render() {}
	
	void handle(SDL_Event *e)
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
		new_game_button.handle(e);
		load_game_button.handle(e);
		about_button.handle(e);
		options_button.handle(e);
		video_button.handle(e);
		audio_button.handle(e);
	}
	void load_handle(SDL_Event *e, SCoord mouse_position);
	void options_handle(SDL_Event *e, SCoord mouse_position);
	void audio_handle(SDL_Event *e, SCoord mouse_position);
	void video_handle(SDL_Event *e, SCoord mouse_position);
};



