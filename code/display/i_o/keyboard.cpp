#include <SDL2/SDL_events.h>
#include <display/ui/main/main_menu.hpp>
#include <display/ui/main/bottom_strip.hpp>
namespace ui
{
void handle_events(SDL_Event& e)
  {
    
  }	  
};

void handle_inputs()
{
		SDL_Event e;
		SDL_zero(e);
		while (SDL_PollEvent(&e)) {
		  ui::handle_events(e);
		}		    
}
