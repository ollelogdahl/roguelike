#pragma once

#include <SDL2/SDL.h>

// Class representing a texture contained in a texture atlas.
struct SubTexture {
 public:
  SubTexture();
  SubTexture(SDL_Rect *r);
  ~SubTexture();

  // Creates a SDL_Rect* pointing to sprite index
  SDL_Rect *getSprite(int spriteIndex);

 private:
  SDL_Rect *textureRect;
};