#pragma once

#include <string>
#include <SDL2/SDL.h>

struct IdentifiedSurface {
public:
  SDL_Surface *surface;
  std::string identifier;
};