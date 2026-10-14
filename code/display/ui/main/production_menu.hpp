#pragma once
#include <SDL2/SDL_events.h>
#include <../extern/magic_enum/magic_enum.hpp>
#include <display/ui/components/element.hpp>
#include "display/ui/components/button.hpp"
#include "display/ui/components/button_functionality.hpp"
#include "display/ui/components/display_frame.hpp"
#include "display/ui/components/element.hpp"
#include "data/types/buildable.hpp"
#include <display/ui/aggregates/swipable_menu.hpp>
#include <display/ui/aggregates/info_section.hpp>
#include <world/item/tables.hpp>
#include "large_menu.hpp"

// serves for both 'item production' and 'buildables.' one singleton instance for each
class ProductionMenu : public LargeMenu
{
private:
  inline static ProductionMenu *production_instance = nullptr;
  inline static ProductionMenu *buildable_instance = nullptr;
  static constexpr int SUBMENU_SELECTION_MENU_SIZE = 6;
  static constexpr int BUTTONS_PER_ROW = 4;
  static constexpr int BUTTONS_PER_COLUMN = 4;
  inline static SCoord left_corner = {100, 100};
  inline static UIElement catalog_background = UIElement(UISprite::MenuCatalogFrame, left_corner);

  bool open = false;
  Item current_item = Item::NONE;
  std::vector<InfoSection> infos;
  SwipableMenu catalog;
  public:
  ProductionMenu(std::vector<CustomButtonDecoration>& submenu_selection_menu_decs, std::vector<Item>& products)
  {
          production_instance = this;
          init_info_sections(false);
	  init_selection_submenu(submenu_selection_menu_decs);
          init_catalog(products);
  }

  ProductionMenu(std::vector<CustomButtonDecoration>& submenu_selection_menu_decs, std::vector<Buildable>& buildables)
  {
          production_instance = this;
          init_info_sections(true);
	  init_selection_submenu(submenu_selection_menu_decs);
          init_catalog(buildables);
  }
  
    ProductionMenu(const ProductionMenu&) = delete;
    ProductionMenu& operator=(const ProductionMenu&) = delete;

    static ProductionMenu& get_production_instance()
    {
        assert(buildable_instance != nullptr);
        return *buildable_instance;
    }

    static ProductionMenu& get_buildable_instance()
    {
        assert(production_instance != nullptr);
        return *production_instance;
    }

  void init_info_sections(bool buildable_menu)
  {
	  if (buildable_menu)
	  {
    infos.reserve(static_cast<size_t>(Buildable::MAX));

    for (size_t i = 0; i < static_cast<size_t>(Buildable::MAX); i++)
    {
      Buildable buildable = static_cast<Buildable>(i);
      infos[i] = InfoSection(magic_enum::enum_name(buildable), buildable::descriptions[buildable]);
    }
          } else {
	  // reserve appropriate mem
    int count = 0;
    for (size_t i = 0; i < static_cast<size_t>(Item::MAX); i++)
      if (!(item::TAGS[static_cast<Item>(i)] | item::Tag::Resource)) count++;
    infos.reserve(count);

    for (size_t i = 0; i < static_cast<size_t>(Item::MAX); i++)
    {
      Item item = static_cast<Item>(i);
      infos[i] = InfoSection(magic_enum::enum_name(item), item::descriptions[item]);
    }
          }
  }

    void init_catalog(std::vector<Item>& products)
  {
	  std::vector<std::unique_ptr<ButtonFunctionality>> button_functionalities(products.size());
    for (size_t i = 0; i < products.size(); i++)
    {
            Entity entity = products[i];
	    button_functionalities[i] = std::make_unique<CatalogSelectionBF>(entity);
    }
    catalog = SwipableMenu(button_functionalities, ButtonSprite::ElementFrame, products, BUTTONS_PER_COLUMN,  BUTTONS_PER_ROW, catalog_background);
  }

  void init_catalog(std::vector<Buildable>& products)
  {
	  std::vector<std::unique_ptr<ButtonFunctionality>> button_functionalities(products.size());
    for (size_t i = 0; i < products.size(); i++)
    {
            Entity entity = products[i];
	    button_functionalities[i] = std::make_unique<CatalogSelectionBF>(entity);
    }
    catalog = SwipableMenu(button_functionalities, ButtonSprite::ElementFrame, products, BUTTONS_PER_COLUMN,  BUTTONS_PER_ROW, catalog_background);
  }

  void render()
  {
    if (open) {
	  infos[static_cast<uint16_t>(current_item)].render();
	  submenu_selection_menu.render();
	  catalog.render();
    }
  }

  void handle(SDL_Event *e)
  {
    if (open) {
	  infos.handle(e);
	  submenu_selection_menu.handle(e);
	  catalog.handle(e);
    }
  }
};
