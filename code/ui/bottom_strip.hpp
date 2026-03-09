#include "core/data.hpp"
#include "render/animation.hpp"
#include "ui.hpp"
#include <render/texture.hpp>
#include <variant>
//TODO: get clips

constexpr int bottomBarWidth = SCREEN_WIDTH;
constexpr int bottomBarHeight = 55;

void renderBottom() {
  gSpriteSheetTexture.render(0, 0, &bricks, bottomBarViewport);
}

using Subject = std::variant<Animal, Unit>;
 
//TODO: add animation to subject display
void renderSubjectDisplay(Coord leftCorner, Subject subject, Time age) {
  if (std::holds_alternative<Animal>(subject)) {
	  SDL_Rect r = getAnimalRect(ard.animal, s, ages[ai], f);
  } else {
	  
  }
  gSpriteSheetTexture.render(leftCorner.x, leftCorner.y, );
}  

void renderBottomUnit(bool alt) {
  // render status bars
	Coord 
	
  // render nametags
  
  // render unit display
  Coord ublc = {57, 8};
  SDL_Rect ubs = {};
  gSpriteSheetTexture.render(ublc.x, ublc.y, &ubs, bottomBarViewport);
  
  // render equipment buttons / display
  Coord eblc = {96, 314};
  SDL_Rect ebs = {};
  SDL_Rect ebsAlt = {};
  uint32_t ebhg = 3;
  uint32_t ebwg = 3;
  for (uint16_t j = 0; j < 2; j++) {
    for (uint16_t i = 0; i < 4; i++) {
      if (alt)
        gSpriteSheetTexture.render(eblc.x + (j * (ebs.w + ebwg)),
                                   eblc.y + (i * (ebs.h + ebhg)), &ebsAlt);
      else gSpriteSheetTexture.render(eblc.x + (j * (ebs.w + ebwg)),
								   eblc.y + (i * (ebs.h + ebhg)), &ebs);				   
      }
  }
  
  // render text buttons
  Coord tblc = {190, 314};
  SDL_Rect tbs = {};
  uint32_t tbhg = 2;
  uint32_t tbwg = 4;
  for (uint16_t j = 0; j < 2; j++) {
      for (uint16_t i = 0; i < 4; i++) {
	gSpriteSheetTexture.render(tblc.x + (j * tbs.w + tbwg), tblc.y + (i * (tbs.h + tbhg)), &tbs);
      }
  }

  // render inventory button	
  
}
