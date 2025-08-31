#ifndef UI_H_
#define UI_H_

#include <SDL3/SDL_main.h>
#include <SDL3/SDL_rect.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3/SDL_stdinc.h>
#include <string>
#include <variant>
#include <optional>
#include "categories.hpp"

/* Constants */
constexpr int rawScreenWidth = 480;
constexpr int rawScreenHeight = 270;

constexpr SDL_Color textButtonBackground = ;

/* Class Prototypes */

class Texture {
    public:
          //Initializes texture variables
    Texture();

    //Cleans up texture variables
    ~Texture();

    //Remove copy constructor
    Texture( const Texture& ) = delete;

    //Remove copy assignment
    Texture& operator=( const Texture& ) = delete;

    //Remove move constructor
    Texture( Texture&& ) = delete;

    //Remove move assignment
    Texture& operator=( Texture&& ) = delete;

    bool loadFromFile( std::string path);

      #if defined(SDL_TTF_MAJOR_VERSION)
    //Creates texture from text
    bool loadFromRenderedText( std::string textureText, SDL_Color textColor );
    #endif

    //Cleans up texture
    void destroy();

    //Sets color modulation
    void setColor( Uint8 r, Uint8 g, Uint8 b);

    //Sets opacity
    void setAlpha( Uint8 alpha );

    //Sets blend mode
    void setBlending( SDL_BlendMode blendMode );

    //Draws texture
    void render( float x, float y, SDL_FRect* clip = nullptr, float width = 0.0, float height = 0.0, double degrees = 0.0, SDL_FPoint* center = nullptr, SDL_FlipMode flipMode = SDL_FLIP_NONE );

    //Gets texture attributes
    int getWidth();
    int getHeight();
    bool isLoaded();

    private:
    SDL_Texture* texture;

    int width;
    int height;
};

class ButtonUI {
    public:
    //Initializes texture variables
    ButtonUI();
    ButtonUI(SDL_FPoint position, int n);

    //Cleans up texture variables
    ~ButtonUI();

    //Remove copy constructor
    ButtonUI( const ButtonUI& ) = delete;

    //Remove copy assignment
    ButtonUI& operator=( const ButtonUI& ) = delete;

    //Remove move constructor
    ButtonUI( ButtonUI&& ) = delete;

    //Remove move assignment
    ButtonUI& operator=( ButtonUI&& ) = delete;

   //Loads texture from disk
    bool loadFromFile( std::string path );

    //Cleans up texture
    void destroy();

    //Handles mouse event
    void handleEvent( SDL_Event* e );

    //Shows button sprite
    void render();

    //Gets texture attributes
    int getWidth();
    int getHeight();
    bool isLoaded();

    void setPosition(SDL_FPoint position);
    void setButtonUINumber(int n);

protected:
    enum class buttonSprite
        {
            Unpressed = 0,
            Hover = 1,
            Pressed = 2
        };

    SDL_Texture* bTexture;

    //Texture dimensions
    int width = -1;
    int height = -1;

    int buttonNumber;
    SDL_FPoint position;
    buttonSprite currentSprite;
};

class TextButtonUI: public ButtonUI {
    private:
        std::string text;
        SDL_Color defaultColor;
        SDL_Color hoverColor;
        SDL_Color pressedColor;
        SDL_Color textColor;
        SDL_Color textHoverColor;
        SDL_FPoint position;
        int width;
        int height;
        Texture renderedText;
    public:
        typedef ButtonUI super;
        TextButtonUI(std::string textureText, SDL_FPoint position, SDL_Color defaultColor, SDL_Color hoverColor, SDL_Color pressedColor, SDL_Color textColor, SDL_Color textHoverColor);
        std::string getText() { return text; }
        SDL_FPoint getPosition() { return position; }
        SDL_Color getDefaultColor() { return defaultColor; }
        SDL_Color getHoverColor() { return hoverColor; }
        SDL_Color getPressedColor() { return pressedColor; }
        void setText(std::string text);
        void setTextPallette(SDL_Color defaultC, SDL_Color hoverC, SDL_Color pressedC);
        void setPosition(SDL_FPoint position);
        void setSize(int width, int height);
        void render();
};

//TODO: add functionality to right click, and view how many there are, or be linked to that item's page even

struct ItemTextBox {
    std::string text;
    Item item;
};

struct RoleTextBox {
    std::string text;
    Role role;
};

struct AnimalTextBox {
    std::string text;
    Animal animal;
};

struct PlantTextBox {
    std::string text;
    Plant plant;
};

using TextBoxType = std::variant<ItemTextBox, RoleTextBox, AnimalTextBox, PlantTextBox>;

class TextBox {
    private:
        std::variant<TextBoxType> type;
    public:

};

class Menu {
    public:
        void open();
    protected:
};

class TextMenu:Menu {
     private:
        enum class Category {
        Item = 0,
        Occupation = 1,
        Animal = 2,
        Plant = 3
        };
        Category type;
        vector<TextButtonUI> buttonUIs;
        int longestText = 0;
        int fontSize;
    public:
        TextMenu(Category c, int fontSize) {
        };
        //TODO: consider sorting algorithm to sort by age, alphabetically, etc
        void addItem(std::string text, SDL_FPoint position, SDL_Color defaultColor, SDL_Color hoverColor, SDL_Color pressedColor, SDL_Color textColor, SDL_Color textHoverColor);
        void
        void open();
};

class LargeMenu:Menu {
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

class IconUI {
    private:
        Texture image;
        std::string name;
        SDL_FPoint location;
    public:
        IconUI(Texture image, std::string name);
        void render();
};

class IconFunc {
    private:

    public:
        IconFunc();
        void handleEvent(SDL_Event* e);
};

class InfoBox {
    private:
        IconUI& icon;
        std::optional<IconFunc>& iconFunc;
        std::string title;
        std::vector<std::string> fields;
        std::vector<std::string> values;
    public:
        InfoBox(IconUI& icon, std::string name);
        void addIconFunc(IconFunc& iconFunc);
        void render();
};

class ArmorInfoBox:InfoBox {
    private:
    public:
        ArmorInfoBox(IconUI& icon, IconFunc& iconFunc);
        void render();
};

constexpr float iconWidth = 0.0;
constexpr float iconHeight = 0.0;



/* Global Variables */
//The window we'll be rendering to
SDL_Window* gWindow{ nullptr };

//The renderer used to draw to the window
SDL_Renderer* gRenderer{ nullptr };

Texture mainSpriteSheet;
Texture buttonsSpriteSheet;

//if any submenus or menus are open, which tells buttons to leave "pressed" state after another click from the user, closing all menus.
bool menuOpen;
/* Forward Declarations */


#endif // UI_H_
