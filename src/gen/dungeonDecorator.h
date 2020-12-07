#pragma once

#include <random>

#include "dungeonLayout.h"
#include "world/map.h"
#include "core/gameLevel.h"

namespace WorldGenerator {
class DungeonDecorator {
public:
  void decorateRooms(GameLevel& level, const DungeonLayout& layout, std::default_random_engine generator);
  void populateRooms(GameLevel& level, const DungeonLayout& layout, std::default_random_engine generator);

  std::string getWeightedItemId(std::default_random_engine generator);
};
}