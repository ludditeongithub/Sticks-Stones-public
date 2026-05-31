#include "element.hpp"
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_events.h>
#include <string>
#include <core/data.hpp>
#include <core/mouse.hpp>
#include "button_functionality.hpp"

enum class ButtonSprite : uint8_t
{
	MainButton,
	FirstLaunchButton,
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
	SCoord topLeftCorner;
	SCoord dimensions;
	SCoord unpressed;
	SCoord hover;
	SCoord pressed;
	Sound pressedSound = NULL;
	ButtonState state = ButtonState::Unpressed;
	ButtonFunctionality function = NULL;

	ButtonUI(SCoord topLeftCorner, SCoord dimensions, SCoord unpressed, SCoord hover, SCoord pressed, Sound pressedSound)
	:  topLeftCorner(topLeftCorner), dimensions(dimensions), unpressed(unpressed), hover(hover),   pressed(pressed), pressedSound(pressedSound)  {
	}

	void render(SDL_Rect *viewport)
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
    std::string text;

    TextButtonUI(
        std::string& text,
        SCoord topLeftCorner,
        SCoord dimensions,
        SCoord unpressed,
        SCoord hover,
        SCoord pressed,
        Sound pressedSound = NULL)
        : ButtonUI(
            topLeftCorner,
            dimensions,
            unpressed,
            hover,
            pressed,
            pressedSound),
          text(text)
    {
    }

    void render(SDL_Rect* viewport)
    {
        ButtonUI::render(viewport);

        // Draw text here
        // renderText(text, topLeftCorner.x, topLeftCorner.y);
    }

    void handleEvent(SDL_Event* e)
    {
	    ButtonUI::handleEvent(e);
    }	    
};

// TODO: add functionality to right click, and view how many there are, or be linked to that item's
// page even

struct ItemButtonUI : ButtonUI
{
	Item item;
};
