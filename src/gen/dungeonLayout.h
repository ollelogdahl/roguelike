#pragma once

#include <vector>
#include "dungeonRoom.h"
#include "dungeonCorridor.h"

#include "math/rect2.h"

namespace WorldGenerator {

struct DungeonLayout {
  std::vector<DungeonRoom> rooms;
  std::vector<DungeonCorridor> corridors;

  DungeonLayout() : bounds(0, 0, 0, 0) {}

  // Returns a rectangle containing whole layout
  Rect2 getBounds();

  // Calculate the layout bounds
  void calculateBounds();

  // Translates the layout minX,minY to 1,1
  void translateLayoutToOrigin();

private:
  Rect2 bounds;
};

}