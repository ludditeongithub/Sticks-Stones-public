#pragma once
#include "core/database.hpp"
#include "core/entity.hpp"
#include "render/screen.hpp"
#include "ui/components/button.hpp"
#include "ui/components/button_functionality.hpp"
#include "world/animal/enum.hpp"
#include <ui/components/display_frame.hpp>
#include <ui/components/status_bar.hpp>
#include <ui/components/text_box.hpp>
#include <ui/components/element.hpp>
#include <core/data.hpp>
#include <render/animation.hpp>
#include <render/texture.hpp>
#include <variant>
#include <string>
#include <../extern/magic_enum/magic_enum.hpp>

// this is organized from left to right
// TODO: get clips
namespace bottom_bar
{
constexpr SDL_Rect G_VIEWPORT = {0, 305, 640, 55};  

constexpr int width = screen_width;
constexpr int height = 55;

// =========================
// BARS/DISPLAY
// =========================

  struct Bars {
  static constexpr int BAR_Y = 15;
  static constexpr int HEALTH_BAR_X = 8;
  static constexpr int HEALTH_BAR_Y = 9;
  static constexpr int FIRST_BAR_X = 8;
  static constexpr int SECOND_BAR_X = 16;
  static constexpr int THIRD_BAR_X = 24;

struct BarsUnit
{
	std::vector<StatusBar> bars;

    BarsUnit()
    {
        using enum UnitStatusBar::Value;

        bars.emplace_back(
            UnitStatusBar(Health),
            SCoord{HEALTH_BAR_X, HEALTH_BAR_Y},
            true,
            G_VIEWPORT
        );

        bars.emplace_back(
            UnitStatusBar(Hunger),
            SCoord{FIRST_BAR_X, BAR_Y},
            false,
            G_VIEWPORT
        );

        bars.emplace_back(
            UnitStatusBar(Thirst),
            SCoord{SECOND_BAR_X, BAR_Y},
            false,
            G_VIEWPORT
        );

        bars.emplace_back(
            UnitStatusBar(Satisfaction),
            SCoord{THIRD_BAR_X, BAR_Y},
            false,
            G_VIEWPORT
        );
    }
};


struct BarsAnimal
{
    std::vector<StatusBar> bars;

    BarsAnimal()
    {
        using enum AnimalStatusBar::Value;

        bars.emplace_back(
            AnimalStatusBar(Health),
            SCoord{HEALTH_BAR_X, HEALTH_BAR_Y},
            true,
            G_VIEWPORT
        );

        bars.emplace_back(
            AnimalStatusBar(Hunger),
            SCoord{FIRST_BAR_X, BAR_Y},
            false,
            G_VIEWPORT
        );

        bars.emplace_back(
            AnimalStatusBar(Thirst),
            SCoord{FIRST_BAR_X, BAR_Y},
            false,
            G_VIEWPORT
        );
    }
};


struct BarsPlant
{
    std::vector<StatusBar> bars;

    BarsPlant()
    {
        using enum PlantStatusBar::Value;

        bars.emplace_back(
            PlantStatusBar(Health),
            SCoord{HEALTH_BAR_X, HEALTH_BAR_Y},
            true,
            G_VIEWPORT
        );

        bars.emplace_back(
            PlantStatusBar(Water),
            SCoord{FIRST_BAR_X, BAR_Y},
            false,
            G_VIEWPORT
        );

        bars.emplace_back(
            PlantStatusBar(Sunlight),
            SCoord{FIRST_BAR_X, BAR_Y},
            false,
            G_VIEWPORT
        );
    }
};
  Entity entity = NullEntity::Null;
  BarsUnit bars_unit = BarsUnit();
    BarsPlant bars_plant = BarsPlant();
    BarsAnimal bars_animal = BarsAnimal();

void render()
{
  if (auto ptr = std::get_if<Unit>(entity)) {
    for (auto x: bars_unit.bars) x.render();    
  }
  else if (auto ptr = std::get_if<Animal>(entity)) {
    for (auto x: bars_animal.bars) x.render();
  }
  else if (auto ptr = std::get_if<Plant>(entity)) {
    for (auto x: bars_plant.bars) x.render();
  }
  else if (auto ptr = std::get_if<Item>(entity)) {
    for (auto x: bars_item.bars) x.render();
  }
}
  };


struct Display
{
  // TODO: equipment
public:
	TextBox name_tag = TextBox(SCoord{8, 33}, UISprite::WoodTextBox, "");
	TextBox category_tag = TextBox(SCoord{8, 42}, UISprite::WoodTextBox, "");;
        DisplayFrame display_frame = DisplayFrame(UISprite::EntityDisplayFrame, Unit::Adult, {57, 8});

	void render()
	{
		name_tag.render(G_VIEWPORT);
		category_tag.render(G_VIEWPORT);
		display_frame.render(G_VIEWPORT);                
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

struct EquipmentDisplay
{
  static constexpr ElementTable frame_table{96, 9, 16, 16, 6, 6, 8};
  std::array<DisplayFrame, FRAME_AMOUNT> frames;
  static constexpr ButtonUI view_alternate_button = ButtonUI(ButtonFunctionality::);

  EquipmentDisplay()
  {
    for (size_t i = 0; i < FRAME_AMOUNT; i++) {
      frames[i] = DoubleDisplayFrame(UISprite::EquipmentFrame, UISprite::EquipmentFrameAlt, NullEntity::Null, NullEntity::Null, frame_table.get_position(i));
    }
  }
  
  void change_wearable(Wearable wearable, int frame_number) {
    #if !SHIPPING_BUILD
    assert(frame_number < 6 && frame_number >= 0);
    #endif
    auto wearable_name = magic_enum::enum_name(wearable);    frames[frame_number].change_display(magic_enum::enum_cast<Item>(wearable_name)));
  }

  void change_container(Container container, int frame_number) {
    #if !SHIPPING_BUILD
    assert(frame_number < FRAME_AMOUNT && frame_number >= 6);
    #endif
auto container_name = magic_enum::enum_name(container);    frames[frame_number].change_display(magic_enum::enum_cast<Item>(container_name)));
  }

void render() {
  for (size_t i = 0; i < FRAME_AMOUNT; i++) frames[i].render(G_VIEWPORT);  
}

void switch_display(int frame_number) {
 #if !SHIPPING_BUILD
    assert(frame_number < FRAME_AMOUNT && frame_number >= 0);
    #endif
    frames[frame_number].switch_display();
}
};

// =========================
// ROLE
// =========================

struct RoleDisplay {
	static constexpr ElementTable element_table{186, 7, 45, 7, 4, 2, 4, 8};
  	Array<TextBox, FRAME_AMOUNT> text_boxes;

RoleDisplay()
{        
    for (size_t i = 0; i < FRAME_AMOUNT; i++) text_boxes[i] = TextBox(element_table.get_position(i), UISprite::WoodTextBox);
}

void change_role(size_t i, Role role)
{
    const char* text = magic_enum::enum_name(role).c_str();
    text_boxes[i].text.text = text;
}
};

// =========================
// MENU BUTTONS
// =========================

struct MenuButtons
{
	ElementTable element_table
	{
          297, 19, 23,                   
	};
	Array<ButtonUI, 7> buttons;
  
};


void init_menu_buttons()
{
  for (size_t i = 0; i < 7; i++) {
    menu_buttons.[i] = ButtonUI();
  }
}

} // namespace bottom_bar
