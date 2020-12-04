#pragma once

#include "action.h"
#include "direction.h"
#include "actionResult.h"

class WalkAction : public Action {
 public:
  WalkAction(Direction direction);

  ActionResult perform(Actor *actor) override;

 private:
  Direction dir;
};