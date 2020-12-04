#include "subTexture.h"

#include <easylogging/easylogging++.h>

SubTexture::SubTexture(SDL_Rect *r) : textureRect(r) {}
SubTexture::SubTexture() {}

SubTexture::~SubTexture() {
  //delete textureRect;
}

SDL_Rect *SubTexture::getSprite(int spriteIndex) {
  SDL_Rect *srcRect = new SDL_Rect();
  srcRect->x = textureRect->x + 8 * (spriteIndex % (textureRect->w/8));
  srcRect->y = textureRect->y + 8 * (spriteIndex / (textureRect->w/8));
  srcRect->w = 8;
  srcRect->h = 8;

  if (srcRect->y >= textureRect->y + textureRect->h) {
    LOG(WARNING) << "Sprite Index " << spriteIndex << " is outside texture!";
    return nullptr;
  }

  return srcRect;
}
