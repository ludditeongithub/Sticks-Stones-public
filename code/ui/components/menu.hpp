#include "button.hpp"
#include <SDL2/SDL_main.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_events.h>
#include <string>
#include <vector>

class Menu
{
      public:
	void open();

      protected:
};

class TextMenu : Menu
{
      private:
	enum class Category
	{
		Item = 0,
		Occupation = 1,
		Animal = 2,
		Plant = 3
	};
	Category type;
	std::vector<Button> buttons;
	int longest_text = 0;
	int font_size;

      public:
	TextMenu(Category c, int font_size) {};
	// TODO: consider sorting algorithm to sort by age, alphabetically, etc
	void add_item(std::string text, SDL_FPoint position, SDL_Color default_color,
		     SDL_Color hover_color, SDL_Color pressed_color, SDL_Color text_color,
		     SDL_Color text_hover_color);

	void open();
};

class LargeMenu : Menu
{
      private:
	enum class MenuType
	{
		Production = 0,
		Buildables = 1,
		Needs = 2,
		Military = 3,
		Order = 4,
		Knowledge = 5,
		Culture = 6
	};

      public:
	LargeMenu(MenuType m) {};
};

class MenuButtonFunc
{
      private:
	Menu &menu;
	SDL_FPoint &position;
	int &width;
	int &height;

      public:
	MenuButtonFunc(Menu &m, SDL_FPoint &pos, int &w, int &h);
	void handle_event(SDL_Event *e);
};

class TextMenuButton
{
      public:
	TextMenuButton(SDL_FPoint position, int width, int height, std::string text,
		       TextMenu &menu);

      private:
	MenuButtonFunc &func;
	TextButtonUI &ui;
	SDL_FPoint position;
};
