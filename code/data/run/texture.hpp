// Load and manage textures (spritesheets / atlases), GPU handles, UVs
#pragma once
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <cstdint>
#include <vector>

extern SDL_Renderer *renderer;

namespace chunk_texture {
  std::vector<SDL_Texture*> textures;
  std::vector<bool> updated; //whether texture matches most recent data
  void init(size_t chunk_size) { textures.reserve(chunk_size); }
  void destroy()
  {
	  for (size_t i = 0; i < textures.size(); i++) SDL_DestroyTexture(textures[i]);            
  }

  void render(uint16_t chunk, SDL_Rect *dest, SDL_Rect *clip);
};

