#include "element.hpp"
#include "button.hpp"
#include "render/screen.hpp"
#include "ui/components/button.hpp"
#include "ui/components/button_functionality.hpp"
#include <SDL2/SDL_events.h>
struct SwipableMenu
{
  bool active = false; 
  std::vector<ButtonUI> buttons;
  ButtonUI left_arrow;
  ButtonUI right_arrow;
  //TODO: arrows unpressable state
  size_t slide_amount;
  size_t current_slide = 0;
  size_t buttons_per_slide;
  UIElement background;
  SwipableMenu(std::vector<ButtonFunctionality> buttons_functionalities, ButtonSprite button_frame, std::vector<ButtonDecoration> button_decorations, ButtonUI left_arrow, ButtonUI right_arrow, size_t slide_amount, UIElement background) : left_arrow(left_arrow), right_arrow(right_arrow), slide_amount(slide_amount), buttons_per_slide(buttons.size() / slide_amount), background(background)
  {
    int x_spacing = (background.source->w - get_button_sprite_dimensions(button_frame).x) / 2;
	  int y_spacing = get_button_sprite_dimensions(button_frame).y / 6;
	  
	  for (size_t i = 0; i < buttons_functionalities.size(); i++)
	  {
	    size_t slot = i % buttons_per_slide;
	    SCoord top_left_corner = {x_spacing, (int)(y_spacing * ((slot + 1))) + (int)(slot * get_button_sprite_dimensions(button_frame).y)};
	    buttons[i] = ButtonUI(buttons_functionalities[i], button_frame, top_left_corner, button_decorations[i]);
	    
    }
  }

  void open() { active = true; current_slide = 0; }

  void render() {
	  if (!active)
		  return;
	  background.render();
	  for (size_t i = current_slide * (buttons.size() / slide_amount); i < current_slide + 1 * (buttons.size() / slide_amount); i++) buttons[i].render();
	  
	  right_arrow.render();
	  left_arrow.render();
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
	  for (size_t i = current_slide * (buttons.size() / slide_amount);
	       i < current_slide + 1 * (buttons.size() / slide_amount); i++) buttons[i].handle_event(event);
	  right_arrow.handle_event(event);
	  left_arrow.handle_event(event);	  
  }
};
