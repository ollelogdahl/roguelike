#pragma once

#include "action.h"
#include "actionResult.h"
#include "math/direction.h"
#include "game.h"
#include "math/vec2.h"

class CloseDoorAction : public Action {
 public:
  CloseDoorAction(){};

  ActionResult perform(Actor *actor) override;

 private:
  // Returns true if there is a door at tile and it is closeable.
  bool closeOpenedDoor(Game& game, Vec2 tile);
};