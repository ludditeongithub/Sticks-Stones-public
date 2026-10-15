#pragma once
#include "data/types/ui.hpp"
#include "display/ui/components/button_functionality.hpp~"
#include <vector>
#include <string>
#include <memory>
#include <magic_enum/magic_enum.hpp>
#include <display/ui/components/button.hpp>
#include <display/ui/components/button_functionality.hpp>
#include <display/ui/aggregates/swipable_menu.hpp>

class LargeMenu
{
public:
  SwipableMenu submenu_selection_menu;
  
void init_selection_submenu(
    std::vector<CustomButtonDecoration>& submenu_selection_menu_decorations)
{
    std::vector<Submenu> submenu_selection_menus;
    submenu_selection_menus.reserve(submenu_selection_menu_decorations.size());

    for (auto x : submenu_selection_menu_decorations)
    {
        auto name = magic_enum::enum_name(x);
        auto type = magic_enum::enum_cast<Submenu>(name);

        if (type)
            submenu_selection_menus.push_back(*type);
    }

    submenu_selection_menu = SwipableMenu(
        submenu_selection_menus,
        ButtonSprite::SwipableMenu,
        submenu_selection_menu_decorations,
        submenu_selection_menu_decorations.size(),
        1
    );
}
  
};
