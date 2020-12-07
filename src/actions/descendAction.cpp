#include "descendAction.h"

#include "game.h"

ActionResult DescendAction::perform(Actor *actor) {
  auto &game = Game::getInstance();

  // Test if standing on a hole
  return ActionResult(false);
}
