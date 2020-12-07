#include "renderHelper.h"
#include "resources/textureAtlas.h"

namespace RenderHelper {

SDL_Renderer *renderer = nullptr;

void setup(SDL_Renderer *rend) {
  renderer = rend;
}

void renderText(std::string text, int scale, Vec2 pos) {
  int charCounter = 0;
  int line = 0;
  for (auto c : text) {

    if(c == '\n') {
      line++;
      continue;
    }

    int ascii = int(c);

    Vec2 charPos = pos + Vec2(charCounter, line)*scale;
    TextureAtlas::renderTexture(renderer, "core.font", ascii, charPos, scale);

    charCounter++;
  }
}

void renderItem(const ItemEntity *entity) {
  Vec2 pos = entity->pos * 16;
  TextureAtlas::renderTexture(renderer, entity->itemStack.item->texture,
                              entity->itemStack.item->spriteIndex, pos, 16);
}

void renderTilemap(const Map &map) {
  auto dimensions = map.getSize();

  for (int i = 0; i < dimensions.x; ++i) {
    for (int j = 0; j < dimensions.y; ++j) {
      // Render tile
      Vec2 pos = Vec2(i, j);
      int tile = map.getTile(pos);
      TextureAtlas::renderTexture(renderer, "core.tileset", tile, pos * 16, 16);
    }
  }
}

void renderAtlas() {
  // Query atlas size
  int w, h;
  SDL_QueryTexture(TextureAtlas::getAtlas(), nullptr, nullptr, &w, &h);

  // Create destination rectangle
  SDL_Rect dest;
  dest.x = 0;
  dest.y = 0;
  dest.w = w;
  dest.h = h;

  // renders whole texture atlas to dest
  TextureAtlas::renderCopy(renderer, nullptr, &dest);
}
}  // namespace RenderHelper