#pragma once

#include "action.h"
#include "actionResult.h"

class DescendAction : public Action {
 public:
  DescendAction(){};
  ActionResult perform(Actor *actor) override;
};