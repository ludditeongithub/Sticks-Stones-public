#pragma once

#include "core/tables.hpp"
#include "ui/components/button.hpp"
#include "large_menu.hpp"
#include "ui/components/button_functionality.hpp"
#include "world/progression/knowledge.hpp"
#include "world/progression/tables.hpp"
#include "world/unit/roles_commodities.hpp"
#include <world/progression/tables.hpp>
#include <magic_enum/magic_enum.hpp>

class KnowledgeMenu : public LargeMenu
{
private:
  inline static KnowledgeMenu *instance = nullptr;
  std::vector<KnowledgeButton> academic_nodes;
  static constexpr int SUBMENU_SELECTION_MENU_SIZE = 4;
  static constexpr int BUTTONS_PER_ROW = 4;
  static constexpr int BUTTONS_PER_COLUMN = 4;
  inline static SCoord left_corner = {100, 100};
  inline static UIElement catalog_background = UIElement(UISprite::MenuCatalogFrame, left_corner);
  SwipableMenu academic_catalog;
  SwipableMenu technology_catalog;
  std::vector<InfoSection> infos;
  
  public:
  KnowledgeMenu(std::vector<CustomButtonDecoration> submenu_selection_menu_decs)
  {
	  instance = this;
           init_selection_submenu(submenu_selection_menu_decs);
      }
  
  KnowledgeMenu(const KnowledgeMenu&) = delete;
  KnowledgeMenu& operator=(const KnowledgeMenu&) = delete;

  static KnowledgeMenu& get_instance()
  {
    assert(instance != nullptr);
    return *instance;
  }

  void init_catalog(std::vector<knowledge::Academic>& knowledge)
  {
	  std::vector<std::unique_ptr<ButtonFunctionality>> button_functionalities(knowledge.size());
    for (size_t i = 0; i < knowledge.size(); i++)
    {
            knowledge::Academic academic = knowledge[i];
	    button_functionalities[i] = std::make_unique<CatalogSelectionBF>(academic);
    }
    academic_catalog = SwipableMenu(button_functionalities, ButtonSprite::ElementFrame, knowledge, BUTTONS_PER_COLUMN,  BUTTONS_PER_ROW, catalog_background);
  }

  void init_catalog(std::vector<knowledge::Technology>& knowledge)
  {
	  std::vector<std::unique_ptr<ButtonFunctionality>> button_functionalities(knowledge.size());
    for (size_t i = 0; i < knowledge.size(); i++)
    {
            knowledge::Technology technology = knowledge[i];
	    button_functionalities[i] = std::make_unique<CatalogSelectionBF>(technology);
    }
    technology_catalog = SwipableMenu(button_functionalities, ButtonSprite::ElementFrame, knowledge, BUTTONS_PER_COLUMN,  BUTTONS_PER_ROW, catalog_background);
  }

  void init_info_sections(bool technology_menu)
  {
    using namespace knowledge;
    if (!technology_menu) {
    // reserve appropriate mem
    infos.reserve(Academic::MAX);

    for (size_t i = 0; i < static_cast<size_t>(Academic::MAX); i++)
    {
      Academic a = static_cast<Academic>(i);
      infos[i] = InfoSection(magic_enum::enum_name(a), ACADEMIC_DESCRIPTIONS[a]);
    }
    }
    else
    {
      // reserve appropriate mem
    infos.reserve(Technology::MAX);

    for (size_t i = 0; i < static_cast<size_t>(Technology::MAX); i++)
    {
      Technology t = static_cast<knowledge::Technology>(i);
      infos[i] = InfoSection(magic_enum::enum_name(t), TECHNOLOGY_DESCRIPTIONS[t]);
    }
    }
  }

  
  // inline void draw_connection(KnowledgeButton knowledge_node_source, KnowledgeButton knowledge_node_dest)
  // {
    
  // }

  // template<typename K>
  // void init_web(RaggedLookupTable<K, K>& table)
  // {
  //   using namespace knowledge;
  //   for (int i = 0; i < static_cast<int>(K::MAX); i++)
  //   {
  //           K k = static_cast<K>(i);
  //           KnowledgeButton* kb;
  //     if (typeid(k) == knowledge::Academic)
  //     {
  //       kb = academic_nodes[i];
  //     } else if (typeid(k) == knowledge::Technology) {
  //       kb = technology_nodes[i];
  //     } 
  //     std::span<K> prereq = table.get(k);     
  //     for (auto x: prereq) {
        
  //     }
  //   }
  // }
};
