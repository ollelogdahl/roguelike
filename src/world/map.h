#pragma once

#include <string>

#include "math/vec2.h"
#include "math/rect2.h"

class Map {
 public:
  Map(int width, int height);
  Map(const Map& m);
  Map& operator=(const Map& m);

  ~Map();
  // Loads map from file 'path'
  void LoadMap(std::string path);
  // Save map to file 'path'
  void SaveMap(std::string path);

  void setTile(Vec2 pos, int tile);
  int getTile(Vec2 pos) const;

  // Fills whole map with value
  void fill(int value);
  // Fills rectangle with value
  void fill(Rect2 rect, int value);

  Vec2 getSize() const;

 private:

  bool isValid(Vec2 point) const;
  int getTileIndex(int x, int y) const {
    return x + y * mapSize.x;
  }
  int getTileIndex(Vec2 pos) const {
    return pos.x + pos.y * mapSize.x;
  }

  int* tileMap;
  Vec2 mapSize;
};