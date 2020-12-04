#pragma once

#include "action.h"
#include "actionResult.h"
#include "actor.h"
#include "engine.h"

class AttackAction : public Action {
 public:
  AttackAction(Actor *target);

  ActionResult perform(Actor* actor) override;

 private:
  Actor* target;
};