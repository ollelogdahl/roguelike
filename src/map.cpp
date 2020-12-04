#include "map.h"

#include "easylogging/easylogging++.h"


Map::Map(int width, int height) : mapSize(width,height) {
  tileMap = new int[width * height];
}

Map::~Map() {
  delete[] tileMap;
}

Map::Map(const Map& m) : mapSize(m.mapSize) {
  tileMap = new int[mapSize.x * mapSize.y];
  memcpy(tileMap, m.tileMap, sizeof(int) * mapSize.x * mapSize.y);
}

Map& Map::operator=(const Map& m) {
  mapSize = m.mapSize;
  tileMap = new int[mapSize.x * mapSize.y];
  memcpy(tileMap, m.tileMap, sizeof(int) * mapSize.x * mapSize.y);
  return *this;
}



void Map::fill(int value) {
  for(int i = 0; i < mapSize.x * mapSize.y; i++) {
    tileMap[i] = value;
  }
}

void Map::fill(Rect2 rect, int value) {
  Vec2 start = Vec2(rect.x, rect.y);
  Vec2 end = Vec2(rect.x + rect.w, rect.y + rect.h);
  if(!isValid(start)) return;
  if(!isValid(end)) return;

  for(int i = 0; i < rect.w; ++i) {
    for(int j = 0; j < rect.h; ++j) {
      tileMap[getTileIndex(rect.x + i,rect.y + j)] = value;
    }
  }
}

void Map::setTile(Vec2 pos, int tile) {
  if (!isValid(pos)) return;

  tileMap[getTileIndex(pos)] = tile;
}

int Map::getTile(Vec2 pos) const {
  if (!isValid(pos)) return -1;

  return tileMap[getTileIndex(pos)];
}

bool Map::isValid(Vec2 pos) const {
  if (pos.x >= mapSize.x || pos.y >= mapSize.y || pos.x < 0 || pos.y < 0) {
    LOG(ERROR) << pos.toString() << " outside of tile map bounds.";
    return false;
  }
  return true;
}

// Serialization ------------------------------------------------------------------------

void Map::LoadMap(std::string path) {
}

void Map::SaveMap(std::string path) {
}

Vec2 Map::getSize() const {
  return mapSize;
}