#pragma once
#include <data/types/ui.hpp>
#include <display/ui/components/element.hpp>
#include <display/ui/components/button.hpp>
#include <SDL2/SDL_events.h>

// TODO: make rows and columns work, for production and inventory menus.
struct SwipableMenu
{
  SDL_Rect viewport;
  bool active = false; 
  std::vector<ButtonUI> buttons;
  ButtonUI left_arrow;
  ButtonUI right_arrow;
  //TODO: arrows unpressable state
  int current_slide = 0;
  int buttons_per_column;
  int buttons_per_row;
  int slide_amount;
  UIElement background;
  using ButtonDecorations = std::variant<std::vector<ButtonDecoration>&, std::vector<Item>>&;
  
  SwipableMenu(std::vector<ButtonFunctionality>& buttons_functionalities, ButtonSprite button_frame, ButtonDecorations button_decorations, int buttons_per_column, int buttons_per_row, UIElement background); 

  inline int get_slot(int row, int column);

  void open();

  void render();

  void slide_left();

  void slide_right();

  void handle(SDL_Event* event);
};

