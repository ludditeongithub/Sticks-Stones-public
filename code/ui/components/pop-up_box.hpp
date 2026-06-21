#pragma once
#include <string>
#include <vector>
#include <extern/SDL_FontCache.h>
#include "button.hpp"
#include "render/screen.hpp"
#include "text.hpp"

struct PopUpBox {
  std::string message;
  std::vector<ButtonUI> options;
  Text text;
  uint16_t horizontalPadding;

  void render()
  {
    renderer->render()
  }
};
