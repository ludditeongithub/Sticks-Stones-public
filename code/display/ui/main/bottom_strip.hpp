#pragma once
#include "SDL_FontCache.h"
#include "data/types/entity.hpp"
#include <data/types/item_specialization.hpp>
#include "data/types/ui.hpp"
#include "display/render/screen.hpp"
#include <display/ui/components/button.hpp>
#include <display/ui/fonts.hpp>
#include "data/types/animal.hpp"
#include <display/ui/components/display_frame.hpp>
#include <display/ui/components/status_bar.hpp>
#include <display/ui/components/text_box.hpp>
#include <display/ui/components/element.hpp>
#include <display/render/render.hpp>
#include <display/render/texture.hpp>
#include <variant>
#include <string>
#include <vector>
#include <../extern/magic_enum/magic_enum.hpp>
#include <data/types/item_specialization.hpp>

// this is organized from left to right
// TODO: get clips
namespace bottom_bar
{
inline SDL_Rect VIEWPORT = {0, 305, 640, 55};  

constexpr int width = SCREEN_WIDTH;
constexpr int height = 55;

// =========================
// BARS/DISPLAY
// =========================

namespace bars
  {
    Entity entity;
  constexpr int BAR_Y = 15;
  constexpr int HEALTH_BAR_X = 8;
  constexpr int HEALTH_BAR_Y = 9;
  constexpr int FIRST_BAR_X = 8;
  constexpr int SECOND_BAR_X = 16;
  constexpr int THIRD_BAR_X = 24;

struct BarsUnit
{
  std::vector<status_bar::Bar> bars;

    BarsUnit()
    {
      using enum status_bar::Type;
      using namespace status_bar;
        bars.push_back(
                       Bar(status_bar::Entity::Unit, Health,
            SCoord{HEALTH_BAR_X, HEALTH_BAR_Y},
            true,
            VIEWPORT)
        );

        bars.emplace_back(
                      Bar(status_bar::Entity::Unit, Hunger,
            SCoord{FIRST_BAR_X, BAR_Y},
            false,
            VIEWPORT)
        );

        bars.emplace_back(
                     Bar(status_bar::Entity::Unit, Thirst,
            SCoord{SECOND_BAR_X, BAR_Y},
            false,
            VIEWPORT)
        );

        bars.emplace_back(
                          Bar(status_bar::Entity::Unit, Satisfaction,
            SCoord{THIRD_BAR_X, BAR_Y},
            false,
            VIEWPORT)
        );
    }
};


struct BarsAnimal
{
  std::vector<status_bar::Bar> bars;

    BarsAnimal()
    {
        using enum status_bar::Type;
        using namespace status_bar;
        bars.emplace_back(
            Bar(status_bar::Entity::Animal, Health,
            SCoord{HEALTH_BAR_X, HEALTH_BAR_Y},
            true,
            VIEWPORT)
        );

        bars.emplace_back(
                          Bar(status_bar::Entity::Animal, Hunger,
            SCoord{FIRST_BAR_X, BAR_Y},
            false,
            VIEWPORT)
        );

        bars.emplace_back(
                          Bar(status_bar::Entity::Animal, Thirst,
            SCoord{FIRST_BAR_X, BAR_Y},
            false,
            VIEWPORT)
        );
    }
};


struct BarsPlant
{
  std::vector<status_bar::Bar> bars;

    BarsPlant()
    {
      using enum status_bar::Type;
        using namespace status_bar;
        bars.emplace_back(
                          Bar(status_bar::Entity::Plant, Health,
            SCoord{HEALTH_BAR_X, HEALTH_BAR_Y},
            true,
            VIEWPORT)
        );

        bars.emplace_back(
                          Bar(status_bar::Entity::Plant, Water,
            SCoord{FIRST_BAR_X, BAR_Y},
            false,
            VIEWPORT)
        );

        bars.emplace_back(
                          Bar(status_bar::Entity::Plant, Sunlight,
            SCoord{FIRST_BAR_X, BAR_Y},
            false,
            VIEWPORT)
        );
    }
};

    struct BarsItem {
      std::vector<status_bar::Bar> bars;

    BarsItem()
    {
      using enum status_bar::Type;
      using namespace status_bar;

      bars.emplace_back(
	                Bar(status_bar::Entity::Item, Health, SCoord{HEALTH_BAR_X, HEALTH_BAR_Y},
			true, VIEWPORT)
	);
    }      
    };
    BarsUnit bars_unit = BarsUnit();
    BarsPlant bars_plant = BarsPlant();
    BarsAnimal bars_animal = BarsAnimal();
    BarsItem bars_item = BarsItem();

void render()
{
  if (auto ptr = std::get_if<Unit>(&entity)) {
    for (auto x: bars_unit.bars) x.render(VIEWPORT);    
  }
  else if (auto ptr = std::get_if<Animal>(&entity)) {
    for (auto x: bars_animal.bars) x.render(VIEWPORT);
  }
  else if (auto ptr = std::get_if<Plant>(&entity)) {
    for (auto x: bars_plant.bars) x.render(VIEWPORT);
  }
  else if (auto ptr = std::get_if<Item>(&entity)) {
    for (auto x: bars_item.bars) x.render(VIEWPORT);
  } else assert(true == false && "Tried to use undisplayble entity on bottom bar.");
  
}
  };


namespace display
{
  // TODO: equipment
  TextBox name_tag = TextBox(SCoord{8, 33}, UISprite::WoodTextBox, Text(cagliostro, ""));
  TextBox category_tag = TextBox(SCoord{8, 42}, UISprite::WoodTextBox, Text(cagliostro, ""));
        DisplayFrame display_frame = DisplayFrame(UISprite::EntityDisplayFrame, Unit::BlueEyesBrownHair, {57, 8});

	void render()
	{
		name_tag.render(VIEWPORT);
		category_tag.render(VIEWPORT);
		display_frame.render(VIEWPORT);                
	}

	void change_name_tag(std::string string) { name_tag.text.text = string.c_str(); }

	void change_category_tag(std::string string)
	{
category_tag.text.text = string.c_str();
        }
};

  /* equipment for unit/animal, description and details for plant/item */

// =========================
// EQUIPMENT
// =========================

namespace equipment_display
{
  constexpr int SIZE = 8;
  constexpr ElementTable frame_table{96, 9, 16, 16, 6, 6, 4, 8};
  std::vector<DisplayFrame> frames{};
  ButtonUI view_alternate_button = ButtonUI(ButtonFunctionality::ChangeEquipmentView, ButtonSprite::ChangeEquipmentView, {frame_table.get_end_x() + 1, frame_table.DISPLAY_Y});

  void init()
  {
    frames.reserve(frame_table.FRAME_AMOUNT);    
    for (size_t i = 0; i < frame_table.FRAME_AMOUNT; i++) {
      frames.emplace_back(DoubleDisplayFrame(UISprite::EquipmentFrame, UISprite::EquipmentFrameAlt, NullEntity::Null, NullEntity::Null, frame_table.get_position(i)));
    }
  }
  
  void change_wearable(item::Wearable wearable, int frame_number) {
    assert(frame_number < 6 && frame_number >= 0);
    auto wearable_name = magic_enum::enum_name(wearable);
    Item item = magic_enum::enum_cast<Item>(wearable_name).value();
    frames[frame_number].change_display(item);
  }

  //MTODO: make Container its own type in container.hpp rather than Item
  void change_container(Item container, int frame_number) {
    assert(frame_number < frame_table.FRAME_AMOUNT && frame_number >= 6);
    frames[frame_number].change_display(container);
  }

void render() {
  for (size_t i = 0; i < frame_table.FRAME_AMOUNT; i++) frames[i].render(VIEWPORT);
}

void handle(SDL_Event *e)
  {
    view_alternate_button.handle(e);    
  }

/*
void switch_display(int frame_number) {
  assert(frame_number < frame_table.FRAME_AMOUNT && frame_number >= 0);
  frames[frame_number].switch_display();
}
  */
};

// =========================
// ROLE
// =========================

namespace role_display {
	constexpr ElementTable element_table{186, 7, 45, 7, 4, 2, 4, 8};
	std::array<TextBox, element_table.FRAME_AMOUNT> text_boxes{};
        FC_Font* font = cagliostro;

        void init()
{
	for (size_t i = 0; i < element_table.FRAME_AMOUNT; i++)
	{
          SCoord pos = element_table.get_position(i);
          text_boxes[i] = TextBox(pos, UISprite::WoodTextBox, Text(font, ""));
        }
}

void change_role(size_t i, Role role)
{
    const char* text = magic_enum::enum_name(role).c_str();
    text_boxes[i].text.text = text;
}

void render()
{
for (auto x: text_boxes) {
  x.render();
 }
}

void handle(SDL_Event *e)
{
  //TODO
  }
};

// =========================
// MENU BUTTONS
// =========================

namespace menu_buttons
  {
        constexpr int SIZE = static_cast<int>(CustomButtonDecoration::MENU_MAX) - static_cast<int>(CustomButtonDecoration::MENU_MIN);
	constexpr ElementTable element_table
	{
          297, 19, 23, 25, 2, 0, SIZE, SIZE
	};
        std::vector<ButtonUI> buttons;
	void init()
	{
	  buttons.clear();
    buttons.reserve(SIZE);

    for (size_t i = 0; i < SIZE; i++)
    {
        CustomButtonDecoration decor =
            static_cast<CustomButtonDecoration>(
                static_cast<int>(CustomButtonDecoration::MENU_MIN) + i
            );

        ButtonDecoration bd{decor};

        buttons.emplace_back(
                OpenMenuButtonUI(bd,
            element_table.get_position(i),
            &VIEWPORT)
        );
    }
	}
	void render()
	{
          for (auto x: buttons) {
            x.render();
          }
	}

	void handle(SDL_Event *e)
	  {
            for (auto x: buttons) {
              x.handle(e);
            }
	  }
};

Entity entity = NullEntity::Null;

void init()
{
  equipment_display::init();
  role_display::init();  
  menu_buttons::init();
}

  void render()
    {
	    if (auto ptr = std::get_if<Unit>(&entity))
	      {
                role_display::render();
                equipment_display::render();
	      }
            bars::render();
            menu_buttons::render();
    }

    void handle(SDL_Event *e)
    {
      if (auto ptr = std::get_if<Unit>(&entity))
	      {
                equipment_display::handle(e);
	        role_display::handle(e);
	      }
      menu_buttons::handle(e);	
      }	      
} // namespace bottom_bar
