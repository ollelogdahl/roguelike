#pragma once

#include "map.h"
#include "item.h"

#include "dungeonLayout.h"
#include "dungeonGenerationStyle.h"
#include "gameLevel.h"

namespace WorldGenerator {

  GameLevel generateDungeonLevel(DungeonGenerationStyle genStyle, int seed);

  GameLevel nextLevel();

  Map generateDungeonMap(DungeonLayout layout);
}