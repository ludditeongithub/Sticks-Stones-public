#pragma once
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_events.h>
#include <string>
#include <optional>
#include <chrono>
#include <data/types/entity.hpp>
#include "core/coord.hpp"
#include "data/types/buildable.hpp"
#include <data/types/ui.hpp>
#include "text.hpp"
#include "display/ui/components/text.hpp"
#include <display/ui/sound/sound.hpp>
#include <display/render/sprite.hpp>

constexpr size_t BUTTON_DECORATION_MAX = static_cast<size_t>(CustomButtonDecoration::MAX) + static_cast<size_t>(Buildable::MAX) + static_cast<size_t>(Item::MAX);

inline constexpr BitsetTable<ButtonSprite> REQUIRES_DECORATION = []
 {
   BitsetTable<ButtonSprite> t{};
   auto add = [&](ButtonSprite e) { t.bitset.set(static_cast<uint16_t>(e)); };
   using enum ButtonSprite;
   add(SwipableMenu);
   return t;
 }();

inline SCoord get_button_sprite_dimensions(ButtonSprite sprite)
{
  return {sprite::buttons[sprite].w, sprite::buttons[sprite].h / 3};
}

static_assert(true, "REACHED BUTTONUI");

struct ButtonUI
{
public:	
    ButtonFunctionality function;
    ButtonSprite sprite; 
    SDL_Rect* viewport;
	std::optional<ButtonDecoration> decoration;
	SCoord pos;
	Sound* pressed_sound;
	ButtonState state = ButtonState::Unpressed;

ButtonUI(ButtonFunctionality function, ButtonSprite sprite, SCoord pos, SDL_Rect* viewport = g_main_screen_viewport, std::optional<ButtonDecoration> decoration = std::nullopt, Sound *pressed_sound = nullptr);
		
	void render();

    std::optional<ButtonFunctionality> handle(SDL_Event *e);
};

struct OpenMenuButtonUI : public ButtonUI {
  OpenMenuButtonUI(ButtonDecoration decor, SCoord pos, SDL_Rect* viewport) : ButtonUI(ButtonFunctionality::OpenMenu, ButtonSprite::OpenMenu, pos, viewport, decor)
	{
	}  
};

struct TextButtonUI : public ButtonUI
{
    Text text;	

	TextButtonUI(Text text, ButtonFunctionality function, ButtonSprite sprite, SCoord pos, SDL_Rect& viewport, std::optional<ButtonDecoration> decoration = std::nullopt, Sound* pressed_sound = nullptr);
    inline void render();

    void handle(SDL_Event *e);    
};

// TODO: add functionality to right click, and view how many there are, or be linked to that item's
// page even

struct ItemButtonUI : public ButtonUI
{
	Item item;
};

//TODO: make a wrapper with it next to text, as well as the functionality.
struct CheckboxUI : public ButtonUI
{
    bool checked = false;

    CheckboxUI(ButtonFunctionality function, ButtonSprite sprite, const SCoord pos, SDL_Rect* viewport,
	       Sound *sound = nullptr);

    void render(SDL_Rect& viewport);

    std::optional<ButtonFunctionality> handle(SDL_Event* e);
};

struct SaveButtonUI
{
private:
public:
    using Clock = std::chrono::system_clock;

    Clock::time_point last_saved = Clock::now();

    std::string name;
    constexpr static int MAX_SAVE_NAME_SIZE = 24;
    inline static int SAVE_BUTTON_SIZE = 8;

    SaveButtonUI();

    void render();

    void change_name(std::string new_name);

	
std::string get_last_saved_date();

		void save();			
};

struct MainButtonUI : public ButtonUI {
public:
	MainButtonUI(ButtonFunctionality function, SCoord left_corner);
};

/*
  class KnowledgeButton : public ButtonUI
{
private:
public:
  KnowledgeButton()
  {
    
  };
  
};
*/
