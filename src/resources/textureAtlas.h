#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <string>
#include <vector>

#include "identifiedSurface.h"
#include "math/vec2.h"

namespace TextureAtlas {
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