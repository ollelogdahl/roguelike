#include "walkAction.h"

#include "attackAction.h"
#include "openDoorAction.h"

WalkAction::WalkAction(Direction direction) {
  dir = direction;
}

ActionResult WalkAction::perform(Actor *actor) {
  auto nextPos = actor->pos + dir;

  auto &game = Game::getInstance();

  // Test if an actor is in the way
  auto target = game.actorAt(nextPos);
  // Return new AttackAction instead
  if (target != NULL) return ActionResult(new AttackAction(target));

  // see if tile is a door
  auto tile = game.tileAt(nextPos);
  if(tile == 2) return ActionResult(new OpenDoorAction(dir));

  // see if actor can walk to nextPos
  if(!actor->canOccupy(tile)) return ActionResult(false);

  actor->pos = nextPos;

  return ActionResult(true);
}