#include "closeDoorAction.h"

ActionResult CloseDoorAction::perform(Actor *actor) {
    auto &game = Game::getInstance();

    // tests if any door in cardinal directions could be closed
    // If true, don't try any more doors.
    auto north = actor->pos + Direction::N;
    if(closeOpenedDoor(game, north)) return ActionResult(true);

    auto south = actor->pos + Direction::S;
    if(closeOpenedDoor(game, south)) return ActionResult(true);

    auto east  = actor->pos + Direction::E;
    if(closeOpenedDoor(game, east))  return ActionResult(true);

    auto west  = actor->pos + Direction::W;
    if(closeOpenedDoor(game, west))  return ActionResult(true);

    return ActionResult(false);
}

bool CloseDoorAction::closeOpenedDoor(Game& game, Vec2 tile) {
    // Door closed, door open indexes
    const int DC = 2;
    const int DO = 3;

    auto tileValue = game.getMap().getTile(tile);
    if(tileValue == DO) {
        game.getMap().setTile(tile, DC);
        return true;
    }
    return false;
}