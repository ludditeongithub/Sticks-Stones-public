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
#include "text.hpp"
#include <ui/sound/sound.hpp>


enum class ButtonSprite : uint8_t
{
	MainButton,
	FirstLaunchButton,
	Checkbox,
	MAX
};

enum class ButtonState
{
	Unpressed,
	Hover,
	Pressed
};

inline SCoord getButtonSpriteDimensions(ButtonSprite sprite)
{
  return {SpriteSheet::buttonSprites[static_cast<int>(sprite)].w, SpriteSheet::buttonSprites[static_cast<int>(sprite)].h / 3};
}

inline SDL_Rect getButtonSprite(ButtonSprite sprite, ButtonState state)
{
  SDL_Rect buttonSheet = SpriteSheet::buttonSprites[static_cast<int>(sprite)];
  switch (state) {
  case ButtonState::Unpressed:
		  return {buttonSheet.x, buttonSheet.y, buttonSheet.w, buttonSheet.h / 3};
    break;
  case ButtonState::Hover:
        return {buttonSheet.x, buttonSheet.y + buttonSheet.h / 3, buttonSheet.w, buttonSheet.h / 3};
    break;
  case ButtonState::Pressed:
    return {buttonSheet.x, buttonSheet.y + (2 * buttonSheet.h) / 3, buttonSheet.w, buttonSheet.h / 3};
    break;
  default:
    // TODO: error
    break;
  }
}	

struct ButtonUI
{
      public:
	ButtonFunctionality function;
    ButtonSprite sprite;
	SCoord topLeftCorner;
	Sound* pressedSound;
	ButtonState state = ButtonState::Unpressed;

	ButtonUI(ButtonFunctionality function, ButtonSprite sprite, SCoord topLeftCorner,
		 Sound *pressedSound = nullptr)
	    : function(function), sprite(sprite), topLeftCorner(topLeftCorner),
	      pressedSound(pressedSound)
	{	
	}

	inline void render(SDL_Rect *viewport)
	{
		SDL_Rect rect;
		rect = getButtonSprite(sprite, state);
		spriteSheetTexture.render(topLeftCorner.x, topLeftCorner.y, &rect, viewport);
	}

	void handleEvent(SDL_Event *e)
	{
		if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP )
	{
		//Get mouse position
		int x, y;
		SDL_GetMouseState( &x, &y );

		SCoord dimensions = getButtonSpriteDimensions(sprite);
		bool inside = mouseInside({x,y}, topLeftCorner, dimensions);

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
				if (pressedSound != NULL) playSound(*pressedSound);
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
        SCoord topLeftCorner,
        Sound* pressedSound = nullptr)
        : ButtonUI(function, sprite,
            topLeftCorner,
            pressedSound),
          text(text)
  {    
    }

    inline void render(SDL_Rect* viewport)
    {
      ButtonUI::render(viewport);
      SDL_RenderSetViewport(renderer, viewport);
	FC_DrawColor(text.font, renderer, topLeftCorner.x, topLeftCorner.y, text.color, text.text); 
    }

    void handleEvent(SDL_Event *e) { ButtonUI::handleEvent(e); }
    
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

    CheckboxUI(ButtonFunctionality function, ButtonSprite sprite, const SCoord topLeftCorner,
	       Sound *sound = nullptr)
	: function(
	      function, sprite(sprite), topLeftCorner(topLeftCorner),
	      sound(sound) {}

    void render(SDL_Rect *viewport){
      SDL_Rect rect;
        if (checked)
        {
				rect = getButtonSprite(sprite, ButtonState::Pressed);
        }
        else
		{
			rect = getButtonSprite(sprite, state);	
	}
        spriteSheetTexture.render(topLeftCorner.x, topLeftCorner.y, &rect, viewport);
    }

    bool handleEvent(SDL_Event* e)
    {
        if (e->type != SDL_MOUSEBUTTONUP &&
            e->type != SDL_MOUSEMOTION)
        {
            return false;
        }

        int mx, my;
        SDL_GetMouseState(&mx, &my);

	if (mouseInside({mx, my}, topLeftCorner, dimensions) && !checked)
			{
				state = Button::Hovered;	
			}

        if (hovered &&
            e->type == SDL_MOUSEBUTTONUP &&
            e->button.button == SDL_BUTTON_LEFT)
        {
            checked = !checked;

            // if (clickSound)
            // {
            //     playSound(clickSound);
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
  std::chrono::system_clock::time_point lastSaved;
  std::string name;
  inline static int maxSaveNameSize = 24;
  inline static int saveButtonSize = 8;
  void render() {}

  void changeName(std::string newName)
  {
	  if (newName > maxSaveNameSize)
	    {
	      userError("Name too long! Keep it 24 or less characters.");
	    }
  }	  
};


