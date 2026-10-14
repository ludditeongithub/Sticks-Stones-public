#include <cstdint>
#include <SDL2/SDL_render.h>
#include <data/run/texture.hpp>

namespace chunk_texture {
  void render(uint16_t chunk, SDL_Rect *clip, SDL_Rect* dst)
  {
    SDL_Texture* t = chunk_texture::textures[chunk];
  SDL_SetRenderTarget(renderer, t);
  SDL_RenderCopy(renderer, t, clip, dst);
  }
};

