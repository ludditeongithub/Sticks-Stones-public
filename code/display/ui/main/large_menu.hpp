#pragma once
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
  
  void init_selection_submenu(std::vector<CustomButtonDecoration> &submenu_selection_menu_decs)
  {
    std::vector<std::unique_ptr<ButtonFunctionality>> submenu_selection_menu_BFs(submenu_selection_menu_decs.size());
    int i = 0;
    for (auto x : submenu_selection_menu_decs)
    {
            std::string str{magic_enum::enum_name(x)};
            auto type = magic_enum::enum_cast<SubmenuSelectionBF::ProductionSubmenu>(magic_enum::enum_name(x));

            if (type) submenu_selection_menu_BFs[i++] = std::make_unique<SubmenuSelectionBF>(*type);            
    }

submenu_selection_menu = SwipableMenu(submenu_selection_menu_BFs, ButtonSprite::SwipableMenu, submenu_selection_menu_decs, submenu_selection_menu_decs.size(), 1);
  }
};
