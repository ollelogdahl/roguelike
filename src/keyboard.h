#pragma once

#include <SDL2/SDL.h>

namespace Keyboard {
bool keyPressed(SDL_Scancode code);
bool keyJustPressed(SDL_Scancode code);

void init();
void update();
};