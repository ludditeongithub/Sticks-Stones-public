#pragma once
#include "element.hpp"
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_events.h>
#include <string>
#include <core/data.hpp>
#include <core/mouse.hpp>
#include <chrono>
#include <format>
#include "button_functionality.hpp"
#include "render/screen.hpp"
#include "render/sprite_sheet_settings.hpp"
#include "text.hpp"
#include <ui/sound/sound.hpp>

enum class ButtonSprite : uint8_t
{
	MainButton,
	FirstLaunchButton,
	Checkbox,
	SwipableMenuButton,
	MAX
};

enum class ButtonDecoration : uint8_t
{
  ProductionMenu,
  BuildingMenu,  
  NeedsMenu,
        MAX
};

enum class ButtonState
{
	Unpressed,
	Hover,
	Pressed,
};

inline constexpr BitsetTable<ButtonSprite> REQUIRES_DECORATION = []
 {
   BitsetTable<ButtonSprite> t{};
   auto add = [&](ButtonSprite e) { t.bitset.set(static_cast<uint16_t>(e)); };
   using enum ButtonSprite;
   add(SwipableMenuButton);
   return t;
 }();

inline SCoord get_button_sprite_dimensions(ButtonSprite sprite)
{
  return {sprite::button_sprites[static_cast<int>(sprite)].w, sprite::button_sprites[static_cast<int>(sprite)].h / 3};
}

inline SDL_Rect get_button_sprite(ButtonSprite sprite, ButtonState state)
{
   SDL_Rect button_sheet = sprite::button_sprites[static_cast<int>(sprite)];
  switch (state) {
  case ButtonState::Unpressed:
		  return {button_sheet.x, button_sheet.y, button_sheet.w, button_sheet.h / 3};
    break;
  case ButtonState::Hover:
        return {button_sheet.x, button_sheet.y + button_sheet.h / 3, button_sheet.w, button_sheet.h / 3};
    break;
  case ButtonState::Pressed:
    return {button_sheet.x, button_sheet.y + (2 * button_sheet.h) / 3, button_sheet.w, button_sheet.h / 3};
    break;
  default:
    // TODO: error
    break;
  }
}

// MTODO: Possibly changes from ButtonState
inline SDL_Rect get_decoration_sprite(ButtonDecoration decoration)
{


}	

struct ButtonUI
{
      public:
	ButtonFunctionality function;
	ButtonSprite sprite;
        std::optional<ButtonDecoration> decoration;
	SCoord top_left_corner;
	Sound* pressed_sound;
	ButtonState state = ButtonState::Unpressed;

  ButtonUI(ButtonFunctionality function, ButtonSprite sprite, SCoord top_left_corner, std::optional<ButtonDecoration> decoration = std::nullopt,
		 Sound *pressed_sound = nullptr)
    : function(function), sprite(sprite), top_left_corner(top_left_corner), decoration(decoration),
	      pressed_sound(pressed_sound)
	{
	  
	}

	inline void render(const SDL_Rect& viewport)
	{
		SDL_Rect rect;
	        rect = sprite::get_button(sprite, state);
		
		sprite_sheet_texture.render(top_left_corner.x, top_left_corner.y, &rect, viewport);
		//TODO: decoration should appear lower, if button is pressed!
		if (decoration.has_value()) {
		  SDL_Rect dec_rect = get_decoration_sprite(decoration);
		  sprite_sheet_texture.render(top_left_corner.x, top_left_corner.y, &dec_rect, viewport);
		}		
	}

        inline void render()
	{
		SDL_Rect rect;
		rect = get_button_sprite(sprite, state);
		sprite_sheet_texture.render(top_left_corner.x, top_left_corner.y, &rect, g_main_screen_viewport);

		if (decoration.has_value()) {
		  SDL_Rect dec_rect = get_decoration_sprite(decoration);
		  sprite_sheet_texture.render(top_left_corner.x, top_left_corner.y, &dec_rect, g_main_screen_viewport);
		}
	}

	void handle_event(SDL_Event *e)
	{
		if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP )
	{
		//Get mouse position
		int x, y;
		SDL_GetMouseState( &x, &y );

		SCoord dimensions = get_button_sprite_dimensions(sprite);
		bool inside = mouse_inside({x,y}, top_left_corner, dimensions);

		//Mouse is outside button
		if( !inside )
		{
			state = ButtonState::Unpressed;
		}
		//Mouse is inside button
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
				function.trigger();
				if (pressed_sound != NULL) play_sound(*pressed_sound);
				break;
			}
		}
	}
	}
};

struct TextButtonUI : public ButtonUI
{
    Text text;	

  TextButtonUI(Text text, ButtonFunctionality function, ButtonSprite sprite,      
        SCoord top_left_corner,
        Sound* pressed_sound = nullptr)
        : ButtonUI(function, sprite,
            top_left_corner,
            pressed_sound),
          text(text)
  {    
    }

    inline void render(SDL_Rect* viewport)
    {
      ButtonUI::render(viewport);
      SDL_RenderSetViewport(renderer, viewport);
	fc_draw_color(text.font, renderer, top_left_corner.x, top_left_corner.y, text.color, text.text); 
    }

    void handle_event(SDL_Event *e) { ButtonUI::handle_event(e); }
    
};

// TODO: add functionality to right click, and view how many there are, or be linked to that item's
// page even

struct ItemButtonUI : ButtonUI
{
	Item item;
};

//TODO: make a wrapper with it next to text, as well as the functionality.
struct CheckboxUI : public ButtonUI
{
    bool checked = false;

    CheckboxUI(ButtonFunctionality function, ButtonSprite sprite, const SCoord top_left_corner,
	       Sound *sound = nullptr)
	: function(
	      function, sprite(sprite), top_left_corner(top_left_corner),
	      sound(sound) {}

    void render(SDL_Rect *viewport){
      SDL_Rect rect;
        if (checked)
        {
				rect = get_button_sprite(sprite, ButtonState::Pressed);
        }
        else
		{
			rect = get_button_sprite(sprite, state);	
	}
        sprite_sheet_texture.render(top_left_corner.x, top_left_corner.y, &rect, viewport);
    }

    bool handle_event(SDL_Event* e)
    {
        if (e->type != SDL_MOUSEBUTTONUP &&
            e->type != SDL_MOUSEMOTION)
        {
            return false;
        }

        int mx, my;
        SDL_GetMouseState(&mx, &my);

	if (mouse_inside({mx, my}, top_left_corner, dimensions) && !checked)
			{
				state = Button::Hovered;	
			}

        if (hovered &&
            e->type == SDL_MOUSEBUTTONUP &&
            e->button.button == SDL_BUTTON_LEFT)
        {
            checked = !checked;

            // if (click_sound)
            // {
            //     play_sound(click_sound);
            // }		
            return true;
        }

        return false;
    }
};

class SaveButtonUI
{
private:
public:
  SaveButtonUI() {};
  std::chrono::system_clock::time_point last_saved;
  std::string name;
  inline static int max_save_name_size = 24;
  inline static int save_button_size = 8;
  void render() {}

  void change_name(std::string new_name)
  {
	  if (new_name > max_save_name_size)
	    {
	      user_error("Name too long! Keep it 24 or less characters.");
	    }
  }	  
};


