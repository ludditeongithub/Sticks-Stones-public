#ifndef UI_H_
#define UI_H_

#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3/SDL_stdinc.h>
#include <string>

/* Constants */
constexpr int rawScreenWidth = 480;
constexpr int rawScreenHeight = 270;

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

class Button {
    public:
    //Initializes texture variables
    Button();

    //Cleans up texture variables
    ~Button();

    //Remove copy constructor
    Button( const Button& ) = delete;

    //Remove copy assignment
    Button& operator=( const Button& ) = delete;

    //Remove move constructor
    Button( Button&& ) = delete;

    //Remove move assignment
    Button& operator=( Button&& ) = delete;

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

    void setPosition(float x, float y);

protected:
    enum class buttonSprite
        {
            Unpressed = 0,
            Hover = 1,
            Pressed = 2
        };

    SDL_Texture* bTexture;

    //Texture dimensions
    int width;
    int height;

    SDL_FPoint position;
    buttonSprite currentSprite;
};

class TextButton: public Button {
    public:
        typedef Button super;
        TextButton(std::string t, SDL_Color d, SDL_Color h, SDL_Color p){
            text = t; defaultColor = d; hoverColor = h; pressedColor = p;
        };
        std::string getText();
        SDL_Color getColor();
        void setText(std::string text);
        void setTextPallette(SDL_Color defaultC, SDL_Color hoverC, SDL_Color pressedC);
        void render();
    private:
        std::string text;
        SDL_Color defaultColor;
        SDL_Color hoverColor;
        SDL_Color pressedColor;
        Texture renderedText;
};

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
