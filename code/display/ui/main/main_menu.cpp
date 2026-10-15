#include "main_menu.hpp"
#include <data/types/ui.hpp>
#include <logic/simulation/game.hpp>

MainMenu::MainMenu()
: new_game_button(
	          MainButtonUI([]() {g_game->new_game();}, new_left_corner)),
  load_game_button(MainButtonUI([this]() {change_mode(Mode::Load);}, load_left_corner)),
  about_button(MainButtonUI([this](){change_mode(Mode::About);}, about_left_corner)),
  options_button(MainButtonUI([this](){change_mode(Mode::Options);}, options_left_corner)),
	      video_left_corner({button_left_alignment, 2 * SCREEN_HEIGHT / 6}),
	      audio_left_corner(button_left_alignment / 2, 3 * SCREEN_HEIGHT / 6),
	      video_button(MainButtonUI([this](){change_mode(Mode::Video);}, video_left_corner)),
              audio_button(MainButtonUI([this](){change_mode(Mode::Audio);}, audio_left_corner)){
          background = sprite::uis[UISprite::Background];
	  // keybindings_left_corner = {button_left_alignment / 2, 4 * SCREEN_HEIGHT / 6};
	  // keybindings_button = MainButtonUI(Keybindings(),keybindings_left_corner);  
}

void MainMenu::main_handle(SDL_Event *e){
		new_game_button.handle(e);
		load_game_button.handle(e);
		about_button.handle(e);
		options_button.handle(e);
		video_button.handle(e);
		audio_button.handle(e);
}

void MainMenu::load_handle(SDL_Event *e)
{
  
}

	void options_handle(SDL_Event *e);
	void audio_handle(SDL_Event *e);
	void video_handle(SDL_Event *e);

void MainMenu::handle(SDL_Event *e){
		switch (mode)
		{
		case Mode::Main:
			main_handle(e);
			break;
		case Mode::Load:
			load_handle(e);
			break;
		case Mode::Options:
			options_handle(e);
			break;
		case Mode::Video:
			video_handle(e);
			break;
		case Mode::Audio:
			audio_handle(e);
			break;
		}
	}

void MainMenu::video_render(){}

void MainMenu::options_render(){}

void MainMenu::load_render(){}

void MainMenu::audio_render(){}

void MainMenu::main_render(){
	new_game_button.render();
	load_game_button.render();
	about_button.render();
	options_button.render();
	video_button.render();
	audio_button.render();
	//keybindings_button.render();
	}

void MainMenu::render(){
  sprite_sheet_texture::render(g_main_screen_viewport->x, g_main_screen_viewport->y, background);
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

void MainMenu::activate(){
			active = true;
			while (active)
					{
							SDL_Event e;
							while (SDL_PollEvent(&e))
									{
											handle(&e);
									}
							render();
							SDL_RenderPresent(renderer);
					}
	}

