#include "button.hpp"
#include "display/render/sprite.hpp"
#include "data/game/screen.hpp"
#include "SDL_FontCache.h"
#include <stdexcept>
#include <core/mouse.hpp>

ButtonUI::ButtonUI(std::function<void()> function, ButtonSprite sprite, SCoord pos, SDL_Rect* viewport, std::optional<ButtonDecoration> decoration, Sound *pressed_sound)
		:  function(function), sprite(sprite), viewport(viewport), decoration(decoration), pos(pos), pressed_sound(pressed_sound){
	}

void ButtonUI::render(){
		SDL_Rect rect;
	    rect = sprite::get_button(sprite, state);
		
		sprite_sheet_texture.render(pos.x, pos.y, &rect, viewport);
		//TODO: decoration should appear lower, if button is pressed!
		if (decoration.has_value()) {
			SDL_Rect dec_rect = sprite::get_decoration(decoration.value());
			//TODO: the dec should lower by one pixel if the state is PRESSED.
		  sprite_sheet_texture.render(pos.x, pos.y, &dec_rect, viewport);
		}		
	}

// OPTI: consider handle mouse which takes coords already
std::optional<ButtonFunctionality> ButtonUI::handle(SDL_Event *e){
		if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP )
	{
		int x, y;
		SDL_GetMouseState( &x, &y );

		SCoord dimensions = get_button_sprite_dimensions(sprite);
		bool inside = mouse_inside(viewport, {x,y}, pos, dimensions);

		if( !inside )
		{
			state = ButtonState::Unpressed;
		}
		else
		{
			//Set mouse over sprite
			switch( e->type )
			{
				case SDL_MOUSEMOTION:
					state = ButtonState::Hover;
				break;

			case SDL_MOUSEBUTTONDOWN:
			case SDL_MOUSEBUTTONUP:
				state = ButtonState::Pressed;
				if (pressed_sound != NULL) play_sound(*pressed_sound);
				return function;
				break;
			}
		}
	}
		return std::nullopt;		
	}

MainButtonUI::MainButtonUI(std::function<void()> function, SCoord left_corner) : ButtonUI(function, ButtonSprite::Main, left_corner, g_main_screen_viewport){}

void SaveButtonUI::save(){ last_saved = Clock::now(); }

std::string SaveButtonUI::get_last_saved_date(){
    std::time_t time = Clock::to_time_t(last_saved);
    std::tm local_time = *std::localtime(&time);

    std::ostringstream oss;
    oss << std::put_time(&local_time, "%m/%d/%Y %H:%M");

    return oss.str();
}

void SaveButtonUI::change_name(std::string new_name){
        if (new_name.length() > MAX_SAVE_NAME_SIZE)
        {
            throw std::invalid_argument(
                "Name too long! Keep it 24 or less characters."
            );
        }
    }

void SaveButtonUI::render(){
			
    }

SaveButtonUI::SaveButtonUI(){}

std::optional<ButtonFunctionality> CheckboxUI::handle(SDL_Event* e){
        if (e->type != SDL_MOUSEBUTTONUP &&
            e->type != SDL_MOUSEMOTION)
        {
            return std::nullopt;
        }

        int mx, my;
        SDL_GetMouseState(&mx, &my);

		SDL_Rect rect = sprite::get_button(sprite, ButtonState::Unpressed);
		if (mouse_inside({mx, my}, rect) && !checked)
			{
				state = ButtonState::Hover;	
			}

        if (state == ButtonState::Hover &&
            e->type == SDL_MOUSEBUTTONUP &&
            e->button.button == SDL_BUTTON_LEFT)
        {
			checked = !checked;				
            // if (click_sound)
            // {
            //     play_sound(click_sound);
            // }		
            return function;
        }

        return std::nullopt;
    }

void CheckboxUI::render(SDL_Rect& viewport){
      SDL_Rect rect;
        if (checked)
        {
				rect = sprite::get_button(sprite, ButtonState::Pressed);
        }
        else
		{
				rect = sprite::get_button(sprite, state);	
	}
        sprite_sheet_texture.render(pos.x, pos.y, &rect, &viewport);
    }

CheckboxUI::CheckboxUI(ButtonFunctionality function, ButtonSprite sprite, const SCoord pos, SDL_Rect* viewport,
	       Sound *sound)
	: ButtonUI(function, sprite, pos, viewport, std::nullopt, sound){}

void TextButtonUI::handle(SDL_Event *e){ ButtonUI::handle(e); }

inline void TextButtonUI::render() {
	  ButtonUI::render();
      SDL_RenderSetViewport(renderer, viewport);
	  FC_DrawColor(text.font, renderer, pos.x, pos.y, text.effect.color, text.text);
    }

TextButtonUI::TextButtonUI(Text text, ButtonFunctionality function, ButtonSprite sprite, SCoord pos, SDL_Rect& viewport, std::optional<ButtonDecoration> decoration, Sound* pressed_sound)
    : ButtonUI(function, sprite, pos, &viewport, decoration, pressed_sound),
          text(text){    
    }

