#pragma once

#include <vector>

#include "actor.h"
#include "itemEntity.h"
#include "map.h"

class GameLevel {
public:
  GameLevel(Map m) : map(m) {}

  std::vector<ItemEntity*> worldItems;
  std::vector<std::unique_ptr<Actor>> actors;

  Vec2 entryPoint;

  Map map;
};