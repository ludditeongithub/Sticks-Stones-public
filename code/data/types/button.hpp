#pragma once
#include <cstdint>
#include <variant>
#include <data/types/entity.hpp>

enum class ButtonSprite : uint8_t
{
	// @codegen:begin button_sprite
	//
	// @codegen:end button_sprite
	Main,
	FirstLaunch,
	Checkbox,
	SwipableMenu,
	ChangeEquipmentView,
	OpenMenu,
	LeftArrow,
	RightArrow,
    ElementFrame,
	MAX
};

enum class CustomButtonDecoration : uint8_t
{
	MENU_MIN,
	ProductionMenu,
	BuildingMenu,
	NeedsMenu,
	CombatMenu,
	OrderMenu,
	KnowledgeMenu,
	CultureMenu,
	MENU_MAX,
	MAX
};

enum class ButtonState : uint8_t
{
	Unpressed,
	Hover,
	Pressed,
};

using ButtonDecoration = std::variant<CustomButtonDecoration, Entity>;
