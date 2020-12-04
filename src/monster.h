#pragma once

#include "actor.h"
#include "breed.h"

class Monster : public Actor {
public:
  Monster(std::string breedId, Vec2 position);

  void render(SDL_Renderer *renderer) override;
  
  void gainEnergy() override;
  Action *getAction() override;

private:
  Breed breed;
};