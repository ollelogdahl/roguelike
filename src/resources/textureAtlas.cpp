#include "textureAtlas.h"

#include <easylogging/easylogging++.h>
#include "registry.h"

namespace TextureAtlas {
// List of textures not yet baked
std::vector<IdentifiedSurface> surfacesToBake = std::vector<IdentifiedSurface>();

SDL_Texture* atlasTexture = nullptr;                        // Final baked texture
Registry<SubTexture> textureRegistry = Registry<SubTexture>();  // Registry of baked textures

bool atlasCreated;               // If atlas has been created
const int MIN_ATLAS_SIZE = 512;  // Minimum atlas size (on both axies)

void addTextureFile(std::string id, std::string path) {
  if (atlasCreated) {
    LOG(WARNING) << "Atlas already created. Cannot add new textures.";
    return;
  }

  SDL_Surface* surf = details::loadSurface(path);
  IdentifiedSurface s = IdentifiedSurface();
  s.surface = surf;
  s.identifier = id;

  if (surf != nullptr)
    surfacesToBake.push_back(s);
  else
    LOG(ERROR) << "File " << path << " couldn't be loaded.";
}

SDL_Texture* getAtlas() {
  return atlasTexture;
}

void createAtlas(SDL_Renderer* renderer) {
  // Default
  int maxAtlasSize = MIN_ATLAS_SIZE;

  LOG(INFO) << surfacesToBake.size() << " textures in atlas.";

  // Sort PNGs by size, largest to smallest
  std::sort(surfacesToBake.begin(), surfacesToBake.end(), details::surfaceCompareSize);

  // Create atlas surface, 32 bit depth with default bitmasks
  SDL_Surface* atlas = SDL_CreateRGBSurface(
      0, maxAtlasSize, maxAtlasSize, 32,
      0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);

  if (atlas == nullptr) {
    LOG(ERROR) << "Creating Atlas Texture failed: " << SDL_GetError();
    return;
  }

  // ALGORITHM --------------------------------------------------------------------------

  int offsetX = 0;
  int offsetY = 0;
  std::vector<SDL_Rect> occupiedRects;
  for (unsigned int i = 0; i < surfacesToBake.size(); i++) {
    // repeat
    bool placed = false;
    while (!placed) {
      // Create new rectangle.
      SDL_Rect* r = new SDL_Rect();
      r->x = offsetX;
      r->y = offsetY;
      r->w = surfacesToBake[i].surface->w;
      r->h = surfacesToBake[i].surface->h;

      // Test if it collides with any existing rectangle.
      if (!details::rectCollide(occupiedRects, *r)) {
        occupiedRects.push_back(*r);
        SDL_BlitSurface(surfacesToBake[i].surface, NULL, atlas, r);

        // Allocates a new sub texture on the heap, and registers it.
        auto subTex = std::unique_ptr<SubTexture>(new SubTexture(r));
        textureRegistry.registerObject(std::move(subTex), surfacesToBake[i].identifier);

        placed = true;
      }

      // Move texture over
      offsetX++;
      if (offsetX == maxAtlasSize) {
        offsetX = 0;
        offsetY++;
      }

      // If reached end of file, make bigger and restart
      if (offsetY == maxAtlasSize) {
        offsetX = 0;
        offsetY = 0;
        maxAtlasSize *= 2;
      }
    }
  }

  // Create Texture from Surface (Hardware acceleration)
  SDL_Surface* optimizedAtlas = SDL_ConvertSurface(atlas, atlas->format, 0);
  atlasTexture = SDL_CreateTextureFromSurface(renderer, optimizedAtlas);

  // Turn both renderer and alpha texture transparent
  SDL_SetTextureBlendMode(atlasTexture, SDL_BlendMode::SDL_BLENDMODE_BLEND);
  SDL_SetRenderDrawBlendMode(renderer, SDL_BlendMode::SDL_BLENDMODE_BLEND);

  atlasCreated = true;

  // Debug: save texture to file
  IMG_SavePNG(optimizedAtlas, "atlas.png");

  // Cleanup ----------------------------------------------------------------------------

  SDL_FreeSurface(atlas);
  SDL_FreeSurface(optimizedAtlas);

  // Free all sub surfaces
  for (auto surf : surfacesToBake) {
    SDL_FreeSurface(surf.surface);
  }
}  // createAtlas

// Rendering ----------------------------------------------------------------------------

void renderTexture(SDL_Renderer* renderer, std::string textureId, int spriteIndex, Vec2 dest, int scale) {
  auto subTex = textureRegistry.getObject(textureId);
  SDL_Rect* srcRect = subTex->getSpriteRect(spriteIndex);
  if (srcRect == nullptr) return;

  SDL_Rect destRect;
  destRect.x = dest.x;
  destRect.y = dest.y;
  destRect.w = scale;
  destRect.h = scale;

  renderCopy(renderer, srcRect, &destRect);
}

void renderCopy(SDL_Renderer* renderer, SDL_Rect* source, SDL_Rect* dest) {
  if (!atlasCreated) {
    LOG(WARNING) << "Atlas not created yet. Cannot render.";
    return;
  }

  SDL_RenderCopy(renderer, atlasTexture, source, dest);
}

SubTexture::SubTexture(SDL_Rect *r) : textureRect(r) {}
SubTexture::SubTexture() : textureRect(nullptr) {}

SubTexture::~SubTexture() {
  delete textureRect;
}

SDL_Rect *SubTexture::getSpriteRect(int spriteIndex) {
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

namespace details {

SDL_Surface* loadSurface(std::string path) {
  std::string ext = path.substr(path.length() - 4);
  if (ext != ".png")
    LOG(WARNING) << "Texture " << path << " should be in .png format!";

  SDL_Surface* image = IMG_Load(path.c_str());
  if (image == nullptr) return nullptr;
  SDL_Surface* optimizedSurface = SDL_ConvertSurface(image, image->format, 0);

  // Free temp surface
  SDL_FreeSurface(image);

  return optimizedSurface;
}

bool surfaceCompareSize(IdentifiedSurface a, IdentifiedSurface b) {
  return (a.surface->w + a.surface->h) > (b.surface->w + b.surface->h);
}

bool rectCollide(std::vector<SDL_Rect> rects, SDL_Rect r1) {
  for (auto r2 : rects) {
    if (r1.x < r2.x + r2.w &&
        r1.x + r1.w > r2.x &&
        r1.y < r2.y + r2.h &&
        r1.y + r1.h > r2.y)
      return true;
  }
  return false;
}

}  // namespace details
}  // namespace TextureAtlas