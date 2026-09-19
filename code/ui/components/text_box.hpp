#include <SDL2/SDL_events.h>
#include <SDL2/SDL_rect.h>
#include <string>
#include <variant>
#include <world/animal/enum.hpp>
#include <world/item/enum.hpp>
#include <world/plant/enum.hpp>
#include <world/unit/enum.hpp>
#include "core/data.hpp"
#include "element.hpp"
#include "render/sprite.hpp"
#include "ui/components/text.hpp"


struct TextBox : UIElement
{
  static constexpr int INDENT_RATIO_DENOM = 7;
  Text text;
  Alignment alignment;
  SCoord relative_text_pos;
  
  TextBox(SCoord position, UISprite sprite, const Text& text, Alignment alignment = Alignment::Left) : UIElement(sprite, position), text(text), alignment(alignment)
   {     
        source = sprite::ui[sprite];
    }

    void render(const SDL_Rect& viewport)
    {
            UIElement::render(viewport);         
	    text.render(viewport, {relative_text_pos.x, relative_text_pos.y, source.w, source.h}, alignment);
    }

    void handle(SDL_Event event) {}

  void switch_alignment(Alignment alignment) {
    this->alignment = alignment;
    relative_text_pos = get_text_alignment_pos({source.w, source.h}, alignment);
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
