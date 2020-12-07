#pragma once

#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "math/vec2.h"

namespace SDLHandler {
    bool initWindow(int SCREEN_WIDTH, int SCREEN_HEIGHT);
    void loadTextureAtlas(std::string path);
    void close();

    SDL_Renderer* getRenderer();
}