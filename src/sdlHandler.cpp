#include "sdlHandler.h"

#include <iostream>

#include "easylogging/easylogging++.h"
#include "textureAtlas.h"

namespace SDLHandler {

SDL_Window* window = NULL;
SDL_Texture* fontAtlas = NULL;
SDL_Renderer* renderer = NULL;

bool initWindow(int SCREEN_WIDTH, int SCREEN_HEIGHT) {
  //Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL2 could not initialize! " << SDL_GetError() << std::endl;
    return 1;
  }

  // Create window
  window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if (window == NULL) {
    std::cerr << "SDL2 window could not be created! " << SDL_GetError() << std::endl;
    return 1;
  }

  // Create SDL Renderer
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (renderer == NULL) {
    std::cerr << "SDL2 renderer could not be created! " << SDL_GetError() << std::endl;
    return 1;
  }

  // Create PNG loader
  int imgFlags = IMG_INIT_PNG;
  if (!(IMG_Init(imgFlags) & imgFlags)) {
    std::cerr << "SDL_image could not initialize!" << IMG_GetError() << std::endl;
  }
  return 0;
}

void close() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);

  renderer = nullptr;
  window = nullptr;

  SDL_Quit();
}

SDL_Renderer* getRenderer() {
  return renderer;
}

}  // namespace SDLHandler