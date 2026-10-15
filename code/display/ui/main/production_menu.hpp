#pragma once
#include <SDL2/SDL_events.h>
#include <../extern/magic_enum/magic_enum.hpp>
#include <display/ui/components/element.hpp>
#include "display/ui/aggregates/info_box.hpp"
#include "display/ui/components/button.hpp"
#include "display/ui/components/button_functionality.hpp"
#include "display/ui/components/display_frame.hpp"
#include "display/ui/components/element.hpp"
#include "data/types/buildable.hpp"
#include <display/ui/aggregates/swipable_menu.hpp>
#include <display/ui/aggregates/info_section.hpp>
#include <world/item/tables.hpp>
#include "large_menu.hpp"

struct ProductionCatalogEntry {
  InfoSection info;
  RequirementsSection reqs;
  RolesSection roles;

    void render()
      {
      info.render();
      reqs.render();
      roles.render();
      }

      void handle(SDL_Event* e)
        {
	  info.handle(e);
	  reqs.handle(e);
	  roles.handle(e);
	}
};

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

  std::variant<Item, Buildable> current_entry;
  std::vector<ProductionCatalogEntry> entries;
  SwipableMenu catalog;

public:
    bool open = false;
  
  ProductionMenu(std::vector<CustomButtonDecoration>& submenu_selection_menu_decs, std::vector<Item>& products)
  {
    production_instance = this;
    current_entry = Item::NONE;
          init_entries(false);
	  init_selection_submenu(submenu_selection_menu_decs);
          init_catalog(products);
  }

  ProductionMenu(std::vector<CustomButtonDecoration>& submenu_selection_menu_decs, std::vector<Buildable>& buildables)
  {
          buildable_instance = this;
          current_entry = Buildable::NONE;
          init_entries(true);
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

void open_entity_info(Entity entity)
{
	if (this == production_instance)
	  {
            if (auto ptr = std::get_if<Item>(&entity))
	      {
		current_entry = *ptr;
	      }
	      else assert(!"Tried to open invalid entity type (not Item) in production menu.");	        
	  }
  	if (this == buildable_instance)
	  {
            if (auto ptr = std::get_if<Buildable>(&entity))
	      {
		current_entry = *ptr;
	      }
	      else assert(!"Tried to open invalid entity type (not Buildable) in buildable menu.");	        
	  }
}

  void init_entries(bool buildable_menu)
  {
	  if (buildable_menu)
	  {
    entries.reserve(static_cast<size_t>(Buildable::MAX));

    for (size_t i = 0; i < static_cast<size_t>(Buildable::MAX); i++)
    {
      Buildable buildable = static_cast<Buildable>(i);
      entries.emplace_back({
	  InfoSection(magic_enum::enum_name(buildable), buildable::descriptions[buildable])
          RequirementsSection()
      });
    }
          } else {
	  // reserve appropriate mem
    int count = 0;
    for (size_t i = 0; i < static_cast<size_t>(Item::MAX); i++)
      if (!(item::TAGS[static_cast<Item>(i)] | item::Tag::Resource)) count++;
    entries.reserve(count);

    for (size_t i = 0; i < static_cast<size_t>(Item::MAX); i++)
    {
      Item item = static_cast<Item>(i);
      entries[i] = InfoSection(magic_enum::enum_name(item), item::descriptions[item]);
    }
          }
  }

void init_catalog(std::vector<Item>& products)
{
    std::vector<std::function<void()>> button_functionalities;
    button_functionalities.reserve(products.size());

    for (size_t i = 0; i < products.size(); i++)
    {
        Entity entity = products[i];

        button_functionalities.emplace_back(
    [this, entity = products[i]]()
    {
        open_entity_info(entity);
    }
);
}

    catalog = SwipableMenu(
        button_functionalities,
        ButtonSprite::ElementFrame,
        products,
        BUTTONS_PER_COLUMN,
        BUTTONS_PER_ROW,
        catalog_background
    );
}
  
  void init_catalog(std::vector<Buildable>& products)
  {
    std::vector<std::function<void()>> button_functionalities;
    button_functionalities.reserve(products.size());

    for (size_t i = 0; i < products.size(); i++)
    {
        Entity entity = products[i];

        button_functionalities.emplace_back(
    [this, entity = products[i]]()
    {
        open_entity_info(entity);
    }
  );
    }
  }

  void render()
  {
    if (open) {
	  submenu_selection_menu.render();
	  catalog.render();
	  bool entry_open = false;
	  if (auto item = std::get_if<Item>(&current_entry))
	    {
		    if (*item != Item::NONE) entries[static_cast<uint16_t>(*item)].render();
	    }
	    else
	      {
		Buildable b = std::get<Buildable>(current_entry);
		if (b != Buildable::NONE) entries[static_cast<uint16_t>(b)].render();
	      }
    }
  }

  void handle(SDL_Event *e)
  {
    if (open) {          
	  submenu_selection_menu.handle(e);
	  catalog.handle(e);
    }
  }
};
