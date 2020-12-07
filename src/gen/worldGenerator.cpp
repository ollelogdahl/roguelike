#include "worldGenerator.h"

#include <map>
#include <random>

#include "layoutGenerator.h"
#include "math/rect2.h"

#include <easylogging/easylogging++.h>

namespace WorldGenerator {

GameLevel generateDungeonLevel(DungeonGenerationStyle genStyle, int seed) {
  // Create random generator
  std::default_random_engine generator;
  generator.seed(seed);

  // Generate layout
  DungeonLayout layout = generateDungeonLayout(genStyle, generator);
  LOG(INFO) << "Dungeon layout created.";

  // Perform translation to move -minX to 0
  layout.translateLayoutToOrigin();

  // Create map object
  GameLevel level = GameLevel(generateDungeonMap(layout));
  LOG(INFO) << "Dungeon tilemap created.";

  // Room populators
  genStyle.decorator.decorateRooms(level, layout, generator);
  LOG(INFO) << "Dungeon tilemap decorated.";
  genStyle.decorator.populateRooms(level, layout, generator);
  LOG(INFO) << "Dungeon populated.";

  // Spawn actors

  // Spawn items
  return level;
}

GameLevel nextLevel() {
  // Generates the next dungeon level
  return generateDungeonLevel(DungeonGenerationStyle(), (int)time(NULL));
}

Map generateDungeonMap(DungeonLayout layout) {
  // Get layout bounds
  Rect2 bounds = layout.getBounds();

  // Calculate dungeon size
  int sizeX = bounds.w;
  int sizeY = bounds.h;

  // Initialize tilemap as filled with walls
  Map map = Map(sizeX + 2, sizeY + 2);
  map.fill(1);

  // For every room, clear area
  for (auto room : layout.rooms) {
    Rect2 rect = Rect2(room.pos.x, room.pos.y, room.width, room.height);
    map.fill(rect, 0);
  }

  // For every corridor, clear
  for (auto corridor : layout.corridors) {
    Rect2 rect = corridor.getRect();

    map.fill(rect, 0);
    // Create doors at start and end points of corridors
    map.setTile(corridor.pos, 2);
    //map.setTile(corridor.pos + Vec2::fromDir(corridor.dir)*(corridor.length-1), 2);
  }

  return map;
}

}  // namespace WorldGenerator