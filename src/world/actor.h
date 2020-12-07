#pragma once

#include <SDL2/SDL.h>

#include "math/vec2.h"
#include "core/inventory.h"

class Action;
class Actor {
 public:
  Vec2 pos;
  int health = 0;
  int energy = 0;

  Inventory inventory;

  explicit Actor(Vec2 p) : pos(p) {};

  virtual ~Actor() {};

  virtual void render(SDL_Renderer *renderer) = 0;

  virtual void gainEnergy() = 0;
  bool hasEnoughEnergy();
  void consumeEnergy();

  virtual bool canOccupy(int tileIndex);

  virtual Action *getAction() = 0;
};
