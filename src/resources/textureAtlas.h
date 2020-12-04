#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <string>
#include <vector>

#include "math/vec2.h"

namespace TextureAtlas {

  // A structure for a surface with an identifier.
  struct IdentifiedSurface {
  public:
    SDL_Surface *surface;
    std::string identifier;
  };

  // Class representing a texture contained in a texture atlas.
  struct SubTexture {
  public:
    SubTexture();
    SubTexture(SDL_Rect *r);
    ~SubTexture();

    // Creates a SDL_Rect* pointing to sprite index
    SDL_Rect *getSpriteRect(int spriteIndex);

  private:
    SDL_Rect *textureRect;
};

  // Returns the texture atlas.
  SDL_Texture *getAtlas();

  // Adds a texture (.png) to be baked into texture atlas.
  void addTextureFile(std::string id, std::string path);

  // Bakes all linked files into texture atlas. (Procedural size)
  void createAtlas(SDL_Renderer *renderer);

  // Renders a part of the atlas to the renderers buffer.
  void renderCopy(SDL_Renderer *renderer, SDL_Rect *source, SDL_Rect *dest);

  // Renders a sub-texture of texture atlas to the renderers buffer.
  void renderTexture(SDL_Renderer *renderer, std::string textureId, int spriteIndex, Vec2 dest, int scale);

  namespace details {
  SDL_Surface *loadSurface(std::string path);
  bool surfaceCompareSize(IdentifiedSurface a, IdentifiedSurface b);
  bool rectCollide(std::vector<SDL_Rect> rects, SDL_Rect r);
  };  // namespace details
};  // namespace TextureAtlas