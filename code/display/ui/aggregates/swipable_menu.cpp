#include "swipable_menu.hpp"

SwipableMenu::SwipableMenu(std::vector<ButtonFunctionality> buttons_functionalities,  ButtonSprite button_frame, ButtonDecorations button_decorations,
	     int buttons_per_column, int buttons_per_row, UIElement background) : buttons_per_column(buttons_per_column), buttons_per_row(buttons_per_row), slide_amount(std::min(1, static_cast<int>(buttons_functionalities.size() / (buttons_per_column * buttons_per_row)))), background(background)
             {
SCoord frame = get_button_sprite_dimensions(button_frame);
          viewport = {background.position.x, background.position.y, frame.x, frame.y};
	  
    int x_spacing = (background.source->w - frame.x) / 2;
    int y_spacing = frame.y / 6;

	  int i = 0;
          while (i < buttons_functionalities.size()) {
	  for (int r = 0; r < buttons_per_column; r++) {
            for (int c = 0; c < buttons_per_row; c++)
		  { 
                    SCoord top_left_corner = {x_spacing + (x_spacing + frame.x) * c, y_spacing + (y_spacing + frame.y) * r};
                    buttons[i] = ButtonUI(std::move(buttons_functionalities[i]), button_frame, top_left_corner, button_decorations[i]);
            if (i++ >= buttons_functionalities.size()) return;
            }   
          }
	  }
          
          SCoord left_arrow_tlc = {x_spacing / 2, (y_spacing + frame.y) * buttons_per_row + y_spacing / 4};
		  left_arrow = ButtonUI(ButtonFunctionality::SlideMenuLeft, ButtonSprite::LeftArrow, left_arrow_tlc);

	  SCoord right_arrow_tlc = {frame.x - x_spacing / 2,
				    (y_spacing + frame.y) * buttons_per_row + y_spacing / 4};
right_arrow = (ButtonFunctionality::SlideMenuRight, ButtonSprite::RightArrow, right_arrow_tlc);
}

void SwipableMenu::handle(SDL_Event* event){
	  if (!active)
		  return;
	  for (int i = current_slide * (buttons.size() / slide_amount);
	       i < current_slide + 1 * (buttons.size() / slide_amount); i++) buttons[i].handle(event);
	  right_arrow.handle(event);
	  left_arrow.handle(event);	  
  }

void SwipableMenu::slide_right(){
    if (!active || current_slide >= slide_amount) return;
	  current_slide++;
  }

void SwipableMenu::slide_left(){
    if (!active || current_slide <= 0) return;	
	  current_slide--;
  }

void SwipableMenu::render(){
	  if (!active)
		  return;
	  background.render();
	  for (int i = current_slide * (buttons.size() / slide_amount); i < current_slide + 1 * (buttons.size() / slide_amount); i++) buttons[i].render();
	  
	  right_arrow.render();
	  left_arrow.render();
  }

void SwipableMenu::open()
{ active = true; current_slide = 0; }

inline int SwipableMenu::get_slot(int row, int column){
    return (row * buttons_per_row) + column;
  }
