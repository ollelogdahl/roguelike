#pragma once

#include <vector>

#include "actor.h"
#include "gameLevel.h"
#include "hero.h"
#include "itemEntity.h"
#include "map.h"
#include "worldGenerator.h"

class Game {
 private:
  Hero* player;
  GameLevel level;

  Game() :  // player(Hero("core.knight", Vec2(14, 16))),
           level(WorldGenerator::nextLevel()) {
    player = new Hero("core.knight", Vec2(14, 16));
    // addActor(std::make_unique<Hero>("core.knight", Vec2(14, 16)));
    addActor(std::unique_ptr<Actor>{player});

    // move player to entryPoint
    player->pos = level.entryPoint + Vec2(1,0);
  };

 public:
  Game(const Game&) = delete;
  Game& operator=(const Game&) = delete;

  static Game& getInstance() {
    static Game g;
    return g;
  }

  void init();

  // Adds a new actor to the current level
  void addActor(std::unique_ptr<Actor> actor);
  // Adds a new item entity to the current level
  void addItem(ItemEntity* item);

  // Returns the actor on current level at pos. Returns nullptr if none.
  Actor* actorAt(Vec2 pos);
  // Returns the item entity on current level at pos. Returns nullptr if none.
  ItemEntity* itemAt(Vec2 pos);

  // Returns the tile index at pos. Returns -1 if tile outside level.
  int tileAt(Vec2 pos);

  // Helper methods for gameLevel
  const std::vector<ItemEntity*>& getItems();
  const std::vector<std::unique_ptr<Actor>>& getActors();

  Hero* getPlayer();
  Map& getMap();
};
