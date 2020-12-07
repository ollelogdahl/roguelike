#pragma once

#include <string>

#include <SDL2/SDL.h>

#include "math/vec2.h"
#include "world/itemEntity.h"
#include "world/actor.h"
#include "world/map.h"

namespace RenderHelper {
  void setup(SDL_Renderer* renderer);
  
  void renderText(std::string text, int scale, Vec2 pos);
  void renderTextureFromAtlas(std::string textureId, int spriteIndex, Vec2 dest, int scale);

  void renderItem(const ItemEntity *entity);
  void renderActorBasic(const Actor &actor);
  void renderTilemap(const Map &map);

  // debug: Renders atlas texture to screen.
  void renderAtlas();
}