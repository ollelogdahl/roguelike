#pragma once

#include "actor.h"
#include "heroClass.h"

class Hero : public Actor {
public:
  Hero(const std::string heroClassId, Vec2 position);

  void render(SDL_Renderer *renderer) override;
  
  void gainEnergy() override;
  Action *getAction() override;

private:
  HeroClass heroClass;
};
