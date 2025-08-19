#include <string>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

constexpr int SCREEN_HEIGHT = 270;
constexpr int SCREEN_WIDTH = 480;

/* Global Variables */
//The window we'll be rendering to
SDL_Window* gWindow{ nullptr };

//The surface contained by the window
SDL_Surface* gScreenSurface{ nullptr };

//The image we will load and show on the screen
SDL_Surface* uiBackground{ nullptr };

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Current displayed texture
SDL_Texture* gTexture = NULL;

SDL_Texture* loadTexture( std::string path );
/*
 GAME LOOP NOTES

 A: USER ENTERS MAIN MENU
 1. Display main menu screen with buttons New Game, Continue, Load Game, Settings, About
 a) If New Game then go to 2.
 b) If Continue then go to B.
 c) If Load Game then go to 3.
 d) If Settings then go to 4.

 B: USER ENTERS GAME IN PROGRESS
 1. Main Display contains camera which can scroll
 a) area where pawns currently are remains visible
 b) area where no pawns are and has been explored remains visible
 c) area where no pawns are and has not been explored is covered by fog
 d) pawns are clickable. If pawn clicked go to

 2. Menu button 1: PRODUCTION OVERVIEW
 a) Main page shows from King/overview perspective, how many recorded items there are, and how many should be produced. Products are divided into rows of T Topics, which each contain a number of I items, with a Q current queued items, a C current quantity already produced, and a U amount to always be produced (keep producing until U >= C no matter what Q is). Divided into categories:
 i: Crops
 ii: Animal Products
 iii: Surface
 iv: Earth Materials
 v: Foodstuffs
 vi: Building and Crafting Materials
 vii: Medicine and Poison
 viii: Other

 b) Main page also links to regional administrative pages, where more micro assignment can be done, as well as reports of how much the local workers are expected to produce, with also number in brackets showing the overall production from the main page. This can also link to individual units which can be adjusted. See C1.

 3. Menu button 2: POLICIES/CULTURE OVERVIEW
 a) Main page shows Policy slots and chosen policies.

 4. Menu button 3: KNOWLEDGE OVERVIEW
 The four pages can be cycled between, or just opened up with a hotkey separately
 a) First page shows progress on academic research and the relevant boosts, as well as what books (training) are available (maybe link to this, or just link to teachers). Ruler can possibly fund or encourage research.
 b) Second page shows which units and technology have been unlocked, and allows you to view a desc of them (they are categorized and also there is a search bar). Also links to researchers who are thinking about any units or tech in progress.
 c) Third page shows map of explored land, which can also be toggled on in the map mode with a highlight, as well as the current exploration knowledge boost. (consider animated glow). Ruler can commission/force explorers to explore new land
 d) Fourth page shows benefits of foreign connections; alternatively just opens up foreign overview

 5. Menu button 4: MILITARY OVERVIEW
 Shows your commanders, unit numbers and categories if you have relevant recording officers, and squads. Can sort by unit, category, training, etc, and click on units to change squads and training from here.

 6. Menu button 5: NEEDS OVERVIEW
 Shows amalgamated needs of all pawns, how many are below critical, how many are unknown, and below that amount that can be supplied in next time period, if known
 a) Hunger - links to pallette in-depth overview
 b) Thirst - links to pallette in-depth overview
 c) Social/Sanity - links to cultural in-depth overview
 d) Temperature (too hot, too cold, normal)
 e) Sick/Healthy
 f) (for later) aridity

 7. Menu button 6: ORDER OVERVIEW
 Shows the health of society
 a) Legal
 b) Administrative
 c) Cultural
 d) Satisfaction
 e) Force

8. Menu button 7: BUILDABLES OVERVIEW
Shows what can be built, broken down into categories, with search bar. option to only display currently buildable items (have materials). hover over item to see ingredients list.
a) Walls
b) Roofs
c) Roads
d) Production Facilities/Beds

9. Menu button 8: FOREIGN OVERVIEW
a) Shows foreign nations, their whereabouts, relationship, and other information, allows you to send delegates if available.

10. DYNAMIC DISPLAY
Broken down into several different possibilities:
I: Human Unit Selected
a) View in mini-screen
b) Gear - 8 boxes, head, torso, legs, arms, four boxes for tools and containers. grey X for none. Can tell unit to equip possible gear. Right click to select under-gear if applicable
c) Health bar
d) Roles, which can be dragged to re-ordered
e) Current Task/item which is linked to roles. Can be manually re-selected.
f) Button for more info about pawn. Alternative to Right clicking pawn, or pressing hotkey
g) Name
h) Squads they are apart of

II: Enemy Human Unit Selected
a) View in mini-screen
b) Health bar
c) Name
d) Tribe

III: Animal Selected
a) View in mini-screen (sized to animal size)
b) Health bar
c) Animal Name
d) Info about how much food and other materials, if killed
e) Icon about whether it is domesticated or not

IV: Plant selected

V: Squad selected
Double/right click a unit to select for that kind of unit, then drag a square to select all units of that type, which makes a temporary squad. default is human unit. can save/call squads with FX and Ctrl+X.
a)

11. TOP DISPLAY
a)

12. EVENTS
Type of Events that can pop up:

C. SUBMENUS
1. Product/ Regional Menu
From production menu, can double click/right click on a product and be brought to a menu which shows all pawns producing that product, total number of pawns who can produce it, all recorded, and all regions which produce it, all regions recording it and how many they have, and also regions that might have some but have not recorded it.


 */

// 1. render to back screen (invisible)
// 2. upscale
// 3. render to screen

bool success;

//starts up sdl and creates window

bool init()
{
    //Initialization flag
    bool success{ true };

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) == false )
    {
        SDL_Log( "SDL could not initialize! SDL error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        //Create window
        if( gWindow = SDL_CreateWindow( "Main Window", SCREEN_WIDTH, SCREEN_HEIGHT, 0 ); gWindow == nullptr )
        {
            SDL_Log( "Window could not be created! SDL error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            //Get window surface
            gScreenSurface = SDL_GetWindowSurface( gWindow );
        }
    }

    return success;
}

bool loadPNG(std::string imagePath) {
     bool success{ true };
    if( uiBackground = IMG_Load( imagePath.c_str() ); uiBackground == nullptr )
    {
        SDL_Log( "Unable to load UI image %s! SDL Error: %s\n", imagePath.c_str(), SDL_GetError() );
        success = false;
    }
    return success;
}

bool loadUI()
{
    bool success{ true };

   if (!loadPNG("../assets/ui-background.png")) return false;

    return success;
}

void close()
{
    //Clean up surface
    SDL_DestroySurface( uiBackground );
    uiBackground = nullptr;

    //Destroy window
    SDL_DestroyWindow( gWindow );
    gWindow = nullptr;
    gScreenSurface = nullptr;

    //Quit SDL subsystems
    SDL_Quit();
}

int main( int argc, char* args[] )
{
    //Final exit code
    int exitCode{ 0 };

    //Initialize
    if( init() == false )
    {
        SDL_Log( "Unable to initialize program!\n" );
        exitCode = 1;
    } else {
        if( loadUI() == false )
        {
            SDL_Log( "Unable to load UI!\n" );
            exitCode = 2;
        } else {
            bool quit{ false };

            //The event data
            SDL_Event e;
            SDL_zero( e );


          //The main loop
            while( quit == false ) {
                //Get event data
                while( SDL_PollEvent( &e ) == true ) {
                    //If event is quit type
                    if( e.type == SDL_EVENT_QUIT ) {
                        //End the main loop
                        quit = true;
                    }
                }
  //Fill the surface white
                SDL_FillSurfaceRect( gScreenSurface, nullptr, SDL_MapSurfaceRGB( gScreenSurface, 0xFF, 0xFF, 0xFF ) );

                //Render image on screen
                SDL_BlitSurface( uiBackground, nullptr, gScreenSurface, nullptr );

                //Update the surface
                SDL_UpdateWindowSurface( gWindow );
            }
        }
    }

    close();

    return exitCode;
}
