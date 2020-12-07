#pragma once

#include <vector>

#include "world/actor.h"
#include "world/itemEntity.h"
#include "world/map.h"

// A structure representing a single game level. Contains items and actors and a map.
class GameLevel {
public:
  GameLevel(Map m) : map(m) {}

  std::vector<std::unique_ptr<ItemEntity>> worldItems;
  std::vector<std::unique_ptr<Actor>> actors;

  Vec2 entryPoint;

  Map map;
};