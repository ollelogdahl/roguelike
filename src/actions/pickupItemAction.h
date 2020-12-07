#pragma once

#include "action.h"
#include "direction.h"
#include "actionResult.h"

class PickupItemAction : public Action {
 public:
  PickupItemAction() {};

  ActionResult perform(Actor *actor) override;
};