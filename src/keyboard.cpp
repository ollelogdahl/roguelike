#include "keyboard.h"

#include "easylogging/easylogging++.h"

namespace Keyboard {

Uint8 keystates[SDL_NUM_SCANCODES];
Uint8 lastKeystates[SDL_NUM_SCANCODES];

bool keyPressed(SDL_Scancode code) {
  if (keystates[code] == 1)
    return true;
  else
    return false;
}

bool keyJustPressed(SDL_Scancode code) {
  // Used to be false, now true
  if (!lastKeystates[code] && keystates[code])
    return true;
  
  return false;
}

void init() {
  // Sets keystates and lastKeystates to nothing
  memset(keystates, 0, sizeof(keystates));
  memset(lastKeystates, 0, sizeof(keystates));
}

void update() {
  memcpy(lastKeystates, keystates, sizeof(keystates));
  memcpy(keystates, SDL_GetKeyboardState(NULL), sizeof(keystates));
}

}