#include "attackAction.h"

AttackAction::AttackAction(Actor* t)
    : target(t) {}

ActionResult AttackAction::perform(Actor*) {
  return ActionResult(true);
}
