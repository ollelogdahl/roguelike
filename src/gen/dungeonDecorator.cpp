#include "dungeonDecorator.h"

namespace WorldGenerator {
void DungeonDecorator::decorateRooms(GameLevel& level, const DungeonLayout& layout, std::default_random_engine generator) {
  bool hasEnd = false;
  for (auto room : layout.rooms) {
    // select random tile within room
    std::uniform_int_distribution<int> xdist(1, room.width - 2);
    std::uniform_int_distribution<int> ydist(1, room.height - 2);
    Vec2 tile = room.pos + Vec2(xdist(generator), ydist(generator));

    // If starting room
    if (room.type == DungeonRoom::RoomType::START) {
      level.map.setTile(tile, 5);
      level.entryPoint = tile;
      continue;
    }

    // If ending room
    if (room.type == DungeonRoom::RoomType::END && !hasEnd) {
      level.map.setTile(tile, 4);
      hasEnd = true;
      continue;
    }

    std::uniform_real_distribution<float> distribution(0, 1);
    if (distribution(generator) < 0.99) {
      if (room.type == DungeonRoom::RoomType::MAIN) {
        level.map.setTile(tile, 6);
        continue;
      }
      if (room.type == DungeonRoom::RoomType::RANDOM) {
        level.map.setTile(tile, 7);
        continue;
      }
    }
  }
}

void DungeonDecorator::populateRooms(GameLevel& level, const DungeonLayout& layout, std::default_random_engine generator) {
  for (auto room : layout.rooms) {
    // allow at most 3 items per normal room
    for (int i = 0; i < 3; i++) {
      // Chance to spawn item
      std::uniform_real_distribution<float> spawnDist(0, 1);
      if(spawnDist(generator) > 0.1f) continue;
      // select random tile within room
      std::uniform_int_distribution<int> xdist(0, room.width - 1);
      std::uniform_int_distribution<int> ydist(0, room.height - 1);
      Vec2 tile = room.pos + Vec2(xdist(generator), ydist(generator));

      // If tile is not floor, continue to next room
      if (level.map.getTile(tile) != 0) continue;

      // Select new item
      std::string id = getWeightedItemId(generator);

      // Create item pointer
      ItemEntity *entity = new ItemEntity(id, 7, tile.x, tile.y);

      // Add new item to level
      level.worldItems.push_back(entity);
    }
  }
}

std::string DungeonDecorator::getWeightedItemId(std::default_random_engine generator) {
  std::uniform_int_distribution<int> dist(0, 5);
  switch(dist(generator)) {
    case 0: return "core.gold";
    case 1: return "core.bow_wood";
    case 2: return "core.scroll_identify";
    case 3: return "core.tunic_leather";
    case 4: return "core.sword_steel";
    case 5: return "core.arrow";
  }
  return "core.gold";
}

}  // namespace WorldGenerator
