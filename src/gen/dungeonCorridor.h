#pragma once

#include "math/direction.h"
#include "math/vec2.h"
#include "math/rect2.h"

namespace WorldGenerator {

struct DungeonCorridor {
  Vec2 pos = Vec2(0, 0);
  CardinalDirection dir = CardinalDirection::N;
  int length = 0;

  Vec2 getEnd() {
    Vec2 delta = Vec2::fromDir(dir) * length;
    return delta + pos;
  }

  Rect2 getRect() {
    Rect2 rect = Rect2(0, 0, 0, 0);
    switch (dir) {
      case CardinalDirection::N:
        rect = Rect2(pos.x, pos.y - length, 1, length);
        break;
      case CardinalDirection::E:
        rect = Rect2(pos.x, pos.y, length, 1);
        break;
      case CardinalDirection::S:
        rect = Rect2(pos.x, pos.y, 1, length);
        break;
      case CardinalDirection::W:
        rect = Rect2(pos.x - length, pos.y, length, 1);
        break;
    }
    return rect;
  }
};

}  // namespace WorldGenerator