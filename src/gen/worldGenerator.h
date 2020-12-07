#pragma once

#include "world/map.h"
#include "world/item.h"

#include "dungeonLayout.h"
#include "dungeonGenerationStyle.h"
#include "core/gameLevel.h"

namespace WorldGenerator {

  GameLevel generateDungeonLevel(DungeonGenerationStyle genStyle, int seed);

  GameLevel nextLevel();

  Map generateDungeonMap(DungeonLayout layout);
}