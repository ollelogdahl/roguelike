#pragma once

#include "action.h"
#include "math/direction.h"
#include "actionResult.h"

class PickupItemAction : public Action {
 public:
  PickupItemAction() {};

  ActionResult perform(Actor *actor) override;
};