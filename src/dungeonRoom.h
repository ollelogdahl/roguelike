#pragma once

#include "math/vec2.h"

namespace WorldGenerator {

// Structure representing one room
struct DungeonRoom {
  Vec2 pos;
  int width;
  int height;

  int connections = 0;

  enum RoomType {
    NORMAL,
    START,
    MAIN,
    RANDOM,
    END
  } type;
};

}