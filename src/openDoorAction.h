#pragma once

#include "action.h"
#include "direction.h"
#include "actionResult.h"

class OpenDoorAction : public Action {
 public:
  OpenDoorAction(Direction direction) {
    dir = direction;
  };

  ActionResult perform(Actor *actor) override;
private:
  Direction dir;
};