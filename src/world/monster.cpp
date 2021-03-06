#include "monster.h"

#include "resources/resourceManager.h"
#include "resources/textureAtlas.h"

#include "walkAction.h"

Monster::Monster(std::string breedId, Vec2 position) : Actor(position) {
  breed = ResourceParser::breedRegistry.getObject(breedId);
  health = breed->baseHp;
}

void Monster::render(SDL_Renderer *renderer) {
  TextureAtlas::renderTexture(renderer, breed->texture, breed->spriteIndex, pos * 16, 16);
}

void Monster::gainEnergy() {
  energy += breed->speed;
}

Action *Monster::getAction() {
  // Moves in a random direction
  return new WalkAction((Direction)(std::rand() % 8));
}