#include "pickupItemAction.h"

#include "game.h"

ActionResult PickupItemAction::perform(Actor *actor) {
  auto &game = Game::getInstance();

  // Get item at actor position
  auto i = game.itemAt(actor->pos);

  // Add item to inventory
  actor->inventory.addItem(&(i->itemStack));

  // Remove item from world
  return ActionResult(true);
}
