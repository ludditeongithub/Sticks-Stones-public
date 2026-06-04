#include "element.hpp"
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_events.h>
#include <string>
#include <core/data.hpp>
#include <core/mouse.hpp>
#include "button_functionality.hpp"
#include "text.hpp"
enum class ButtonSprite : uint8_t
{
	MainButton,
	FirstLaunchButton,
	Checkbox,
	
	MAX
};

struct ButtonSpriteData {
	SCoord dimensions;
	SCoord unpressed;
	SCoord hover;
	SCoord pressed;
};

enum class ButtonState
{
	Unpressed,
	Hover,
	Pressed
};

struct ButtonUI
{
      public:
	ButtonFunctionality function;
	SCoord topLeftCorner;
	SCoord dimensions;
	SCoord unpressed;
	SCoord hover;
	SCoord pressed;
	Sound pressedSound = NULL;
	ButtonState state = ButtonState::Unpressed;

	ButtonUI(ButtonFunctionality function, SCoord topLeftCorner, SCoord dimensions, SCoord unpressed, SCoord hover, SCoord pressed, Sound pressedSound)
	:  function(function), topLeftCorner(topLeftCorner), dimensions(dimensions), unpressed(unpressed), hover(hover),   pressed(pressed), pressedSound(pressedSound)  {
	}

	inline void render(SDL_Rect *viewport)
	{
		SDL_Rect r;
		switch (state)
		{
		case ButtonState::Unpressed:
			r = {unpressed.x, unpressed.y, dimensions.x, dimensions.y};
			break;
		case ButtonState::Pressed:
			r = {pressed.x, pressed.y, dimensions.x, dimensions.y};
			break;
		case ButtonState::Hover:
			r = {hover.x, hover.y, dimensions.x, dimensions.y};
			break;
		default:
		}
		spriteSheetTexture.render(topLeftCorner.x, topLeftCorner.y, &r, viewport);
	}

	void handleEvent(SDL_Event *e)
	{
		if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP )
	{
		//Get mouse position
		int x, y;
		SDL_GetMouseState( &x, &y );

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
				function->trigger();
				if (pressedSound != NULL) playSound(pressedSound);
				break;
			}
		}
	}
	}
};

struct TextButtonUI : ButtonUI
{
    Text text;	

    TextButtonUI(ButtonFunctionality function,
        Text text,
        SCoord topLeftCorner,
        SCoord dimensions,
        SCoord unpressed,
        SCoord hover,
        SCoord pressed,
        Sound pressedSound = NULL)
        : ButtonUI(text, function,
            topLeftCorner,
            dimensions,
            unpressed,
            hover,
            pressed,
            pressedSound),
          text(text)
    {
    }

    inline void render(SDL_Rect* viewport)
    {
        ButtonUI::render(viewport);
	SDL_Surface* surfaceMessage =
TTF_RenderText_Solid(text.font, text.text, text.color); 
    }

    void handleEvent(SDL_Event *e) { ButtonUI::handleEvent(e); }
    
};

// TODO: add functionality to right click, and view how many there are, or be linked to that item's
// page even

struct ItemButtonUI : ButtonUI
{
	Item item;
};

struct CheckboxUI
{
    SCoord topLeftCorner;
    SCoord dimensions;

    SCoord uncheckedSprite;
    SCoord checkedSprite;

    Sound clickSound = nullptr;

    bool checked = false;
    bool hovered = false;

    CheckboxUI(
        const SCoord topLeftCorner,
        const SCoord dimensions,
        const SCoord uncheckedSprite,
        const SCoord checkedSprite,
        const Sound clickSound = nullptr)
        : topLeftCorner(topLeftCorner),
          dimensions(dimensions),
          uncheckedSprite(uncheckedSprite),
          checkedSprite(checkedSprite),
          clickSound(clickSound)
    {
    }

    void render(SDL_Rect* viewport)
    {
        SDL_Rect src;

        if (checked)
        {
            src = {
                checkedSprite.x,
                checkedSprite.y,
                dimensions.x,
                dimensions.y
            };
        }
        else
        {
            src = {
                uncheckedSprite.x,
                uncheckedSprite.y,
                dimensions.x,
                dimensions.y
            };
        }

        spriteSheetTexture.render(
            topLeftCorner.x,
            topLeftCorner.y,
            &src,
            viewport);
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

        hovered = mouseInside(
            {mx, my},
            topLeftCorner,
            dimensions);

        if (hovered &&
            e->type == SDL_MOUSEBUTTONUP &&
            e->button.button == SDL_BUTTON_LEFT)
        {
            checked = !checked;

            if (clickSound)
            {
                playSound(clickSound);
            }

            return true;
        }

        return false;
    }
};
