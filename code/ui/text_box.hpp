#include <SDL2/SDL_rect.h>
#include <string>
#include <variant>

#include <world/animal/enum.hpp>
#include <world/plant/enum.hpp>
#include <world/item/enum.hpp>
#include <world/unit/enum.hpp>

#include "ui.hpp"

struct TextBox : UIElement {
  std::string text;

  void render(SDL_Rect viewport) {
	  UIElement::render(viewport);
  }
};

struct ItemTextBox : TextBox {
	Item item;
};

struct AnimalTextBox : TextBox {
    Animal animal;
};

struct PlantTextBox : TextBox {
    Plant plant;
};

struct RoleTextBox : TextBox {
	Role role;
};

using TextBoxVariant = std::variant<ItemTextBox, RoleTextBox, AnimalTextBox, PlantTextBox>;
