#include "openDoorAction.h"

#include "game.h"

ActionResult OpenDoorAction::perform(Actor *actor) {
    auto &game = Game::getInstance();

    auto tilePos = actor->pos + dir;
    auto tileVal = game.getMap().getTile(tilePos);

    // Door closed, door open indexes
    const int DC = 2;
    const int DO = 3;

    if(tileVal == DC) {
        game.getMap().setTile(tilePos, DO);
        return ActionResult(true);
    }

    return ActionResult(false);
}
