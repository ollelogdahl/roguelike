#include "hero.h"

#include "direction.h"
#include <easylogging/easylogging++.h>
#include "keyboard.h"
#include "walkAction.h"
#include "closeDoorAction.h"
#include "pickupItemAction.h"

#include "resources/resourceManager.h"
#include "resources/textureAtlas.h"

Hero::Hero(const std::string heroClassId, Vec2 position)
    : Actor(position),
      heroClass(ResourceManager::getHeroClass(heroClassId)) {}

void Hero::render(SDL_Renderer *renderer) {
  TextureAtlas::renderTexture(renderer, heroClass.texture, heroClass.spriteIndex, pos * 16, 16);
}

void Hero::gainEnergy() {
  energy += heroClass.speed;
}

// Handle user input to determine wanted action
Action *Hero::getAction() {
  // Read keystates

  if (Keyboard::keyJustPressed(SDL_SCANCODE_KP_8)) {
    return new WalkAction(Direction::N);
  }
  if (Keyboard::keyJustPressed(SDL_SCANCODE_KP_6)) {
    return new WalkAction(Direction::E);
  }
  if (Keyboard::keyJustPressed(SDL_SCANCODE_KP_2)) {
    return new WalkAction(Direction::S);
  }
  if (Keyboard::keyJustPressed(SDL_SCANCODE_KP_4)) {
    return new WalkAction(Direction::W);
  }

  if (Keyboard::keyJustPressed(SDL_SCANCODE_C)) {
    return new CloseDoorAction();
  }

  if (Keyboard::keyJustPressed(SDL_SCANCODE_COMMA)) {
    return new PickupItemAction();
  }

  return NULL;
}
