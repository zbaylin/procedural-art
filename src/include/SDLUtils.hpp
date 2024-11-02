#pragma once

#include "spdlog/spdlog.h"
#include <SDL2/SDL.h>

struct SDLWindowDeleter {
  inline void operator()(SDL_Window *window) { SDL_DestroyWindow(window); }
};

struct SDLRendererDeleter {
  inline void operator()(SDL_Renderer *renderer) {
    SDL_DestroyRenderer(renderer);
  }
};

struct SDLTextureDeleter {
  inline void operator()(SDL_Texture *texture) { SDL_DestroyTexture(texture); }
};
