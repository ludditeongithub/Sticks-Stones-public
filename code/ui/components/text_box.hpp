#include <SDL2/SDL_events.h>
#include <SDL2/SDL_rect.h>
#include <string>
#include <variant>
#include <world/animal/enum.hpp>
#include <world/item/enum.hpp>
#include <world/plant/enum.hpp>
#include <world/unit/enum.hpp>
#include "element.hpp"
#include "render/sprite_sheet_settings.hpp"

struct TextBox : UIElement
{
	Text text;
  
TextBox(
        SCoord position,
        UISprite sprite,
        const Text& text
    )
        : text(text)
   {
     #if !SHIPPING_BUILD
	   assert(text.position.x >= position.x);
           assert(text.position.y >= position.y);
     #endif

        this->position = position;
        source = sprite::ui_sprites[sprite];
    }

    void render(const SDL_Rect& viewport)
    {
	    UIElement::render(viewport);
	    text.render(viewport);            
    }
	
	void handle(SDL_Event event)
	{
		
	}		
};

struct ItemTextBox : TextBox
{
	Item item;
};

struct AnimalTextBox : TextBox
{
	Animal animal;
};

struct PlantTextBox : TextBox
{
	Plant plant;
};

struct RoleTextBox : TextBox
{
	Role role;
};

using TextBoxVariant = std::variant<ItemTextBox, RoleTextBox, AnimalTextBox, PlantTextBox>;
