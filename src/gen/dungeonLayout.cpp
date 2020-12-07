#include "dungeonLayout.h"

namespace WorldGenerator {

Rect2 DungeonLayout::getBounds() {
  return bounds;
}

void DungeonLayout::calculateBounds() {
  int minX = INT32_MAX;
  int maxX = INT32_MIN;
  int minY = INT32_MAX;
  int maxY = INT32_MIN;


  for(auto room : rooms) {
    if(room.pos.x < minX) minX = room.pos.x;
    if(room.pos.y < minY) minY = room.pos.y;

    Vec2 roomEnd = room.pos + Vec2(room.width, room.height);
    if(roomEnd.x > maxX) maxX = roomEnd.x;
    if(roomEnd.y > maxY) maxY = roomEnd.y;
  }

  int w = maxX - minX;
  int h = maxY - minY;

  bounds = Rect2(minX, minY, w, h);
}

void DungeonLayout::translateLayoutToOrigin() {
  // Calculate transformed coordinates
  int minX = bounds.x;
  int minY = bounds.y;

  // Move all rooms
  for(auto &room : rooms) {
    room.pos = room.pos - Vec2(minX-1, minY-1);
  }

  // Move all corridors
  for(auto &corridor : corridors) {
    corridor.pos = corridor.pos - Vec2(minX-1, minY-1);
  }
}

}