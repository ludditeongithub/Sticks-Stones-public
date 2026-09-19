#include "element.hpp"
#include "button.hpp"
#include "render/screen.hpp"
#include <ui/components/button.hpp>
#include "ui/components/button_functionality.hpp"
#include <SDL2/SDL_events.h>
#include <algorithm>

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
  
  SwipableMenu(std::vector<std::unique_ptr<ButtonFunctionality>>& buttons_functionalities, ButtonSprite button_frame, ButtonDecorations button_decorations, int buttons_per_column, int buttons_per_row, UIElement background); 

  inline int get_slot(int row, int column)
  {
    return (row * buttons_per_row) + column;
  }

  void open() { active = true; current_slide = 0; }

  void render() {
	  if (!active)
		  return;
	  background.render(viewport);
	  for (int i = current_slide * (buttons.size() / slide_amount); i < current_slide + 1 * (buttons.size() / slide_amount); i++) buttons[i].render(viewport);
	  
	  right_arrow.render(viewport);
	  left_arrow.render(viewport);
  }

  void slide_left()
  {
    if (!active || current_slide <= 0) return;	
	  current_slide--;
  }

  void slide_right()
  {
    if (!active || current_slide >= slide_amount) return;
	  current_slide++;
  }

  void handle_event(SDL_Event* event)
  {
	  if (!active)
		  return;
	  for (int i = current_slide * (buttons.size() / slide_amount);
	       i < current_slide + 1 * (buttons.size() / slide_amount); i++) buttons[i].handle_event(event);
	  right_arrow.handle_event(event);
	  left_arrow.handle_event(event);	  
  }
};

