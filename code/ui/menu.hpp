#include <SDL2/SDL_main.h>
#include <SDL2/SDL_stdinc.h>
#include <string>
#include <vector>
#include "button.hpp"

class Menu {
    public:
        void open();
    protected:
};

class TextMenu : Menu {
     private:
        enum class Category {
        Item = 0,
        Occupation = 1,
        Animal = 2,
        Plant = 3
        };
        Category type;
        std::vector<Button> buttons;
        int longestText = 0;
        int fontSize;
    public:
        TextMenu(Category c, int fontSize) {
        };
        //TODO: consider sorting algorithm to sort by age, alphabetically, etc
        void addItem(std::string text, SDL_FPoint position, SDL_Color defaultColor, SDL_Color hoverColor, SDL_Color pressedColor, SDL_Color textColor, SDL_Color textHoverColor);
        
        void open();
};

class LargeMenu : Menu {
    private:
        enum class MenuType {
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

class MenuButtonFunc {
      private:
        Menu& menu;
        SDL_FPoint& position;
        int& width;
        int& height;
    public:
        MenuButtonFunc(Menu& m, SDL_FPoint& pos, int& w, int& h);
        void handleEvent(SDL_Event* e);
};

class TextMenuButton {
    public:
        TextMenuButton(SDL_FPoint position, int width, int height, std::string text, TextMenu& menu);
    private:
        MenuButtonFunc& func;
        TextButtonUI& ui;
        SDL_FPoint position;
};
