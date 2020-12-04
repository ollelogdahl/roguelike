#include "game.h"

Actor* Game::actorAt(Vec2 pos) {
  if(player->pos == pos) {
    return player;
  }

  for(auto &actor : level.actors) {
    if (actor->pos == pos) {
      return actor.get();
    }
  }

  return nullptr;
}

ItemEntity* Game::itemAt(Vec2 pos) {
  for(auto item : level.worldItems) {
    if(item->pos == pos) {
      return item;
    }
  }

  return nullptr;
}

int Game::tileAt(Vec2 pos) {
  return level.map.getTile(pos);
}

Hero* Game::getPlayer() {
    return player;
}

Map &Game::getMap() {
    return level.map;
}

const std::vector<ItemEntity*>& Game::getItems() {
    return level.worldItems;
}

const std::vector<std::unique_ptr<Actor>>& Game::getActors() {
    return level.actors;
}

void Game::addActor(std::unique_ptr<Actor> actor) {
    level.actors.push_back(std::move(actor));
}

void Game::addItem(ItemEntity* item) {
    level.worldItems.push_back(item);
}