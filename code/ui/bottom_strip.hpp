#include <core/data.hpp>
#include <render/animation.hpp>
#include <render/texture.hpp>
#include <variant>
#include "ui.hpp"
#include "status_bar.hpp"
#include "text_box.hpp"

//TODO: get clips
namespace bb {
	
constexpr int width = SCREEN_WIDTH;
constexpr int height = 55;
constexpr SCoord display = {57, 8};
constexpr SCoord equipment = {96,9};

using Subject = std::variant<Animal, Unit>;
using SpriteAction = std::variant<ActState, >;
 
//TODO: add animation to subject display
void renderSubjectDisplay(Coord leftCorner, Subject subject, Time age, ) {
  if (std::holds_alternative<Animal>(subject)) {
	  SDL_Rect r = getAnimalRect(ard.animal, s, age, 0);
  } else {
	  
  }
  gSpriteSheetTexture.render(leftCorner.x, leftCorner.y, );
}

enum class UnitStatusBars {
  Health,
  Hunger,
  Thirst,
  Satisfaction,
  MAX
};

class BottomUnitBar {
	StatusBar bars[static_cast<int>(UnitStatusBars::MAX) ];
        TextBox nameTag;
        TextBox clanTag;
	
  BottomUnitBar() {
    bars[static_cast<int>(UnitStatusBars::Health)] =
        StatusBar({8, 314}, , true);
    bars[static_cast<int>(UnitStatusBars::Hunger)] =
        StatusBar({8, 320}, , false);
    bars[static_cast<int>(UnitStatusBars::Thirst)] =
        StatusBar({16, 320}, , false);
    bars[static_cast<int>(UnitStatusBars::Satisfaction)] =
        StatusBar({24, 320}, , false);
//    bars[static_cast<int>(UnitStatusBars::Health)] = StatusBar({32, 320}, , false);

    
  }

  void render() {}

  void renderText() {

   }
}

void instantiateBottomUnit(bool alt) {
  // render status bars
	
  // render nametags
	
  // render unit display
 
  // render equipment buttons / display

  // render text buttons
	
  // render inventory button	
	
}

}
