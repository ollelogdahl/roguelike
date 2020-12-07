#pragma once

#include "math/direction.h"
#include "pugixml.hpp"

struct Vec2 {
  int x;
  int y;

  Vec2(int _x, int _y) : x(_x), y(_y) {}
  Vec2() : x(0), y(0) {}

  bool operator==(const Vec2& other) {
    if (x == other.x && y == other.y) return true;
    return false;
  }

  static Vec2 fromXML(pugi::xml_node node) {
    Vec2 vec = Vec2();
    vec.x = node.child("x").text().as_int();
    vec.y = node.child("y").text().as_int();
    return vec;
  }

  static Vec2 fromDir(const Direction& dir);
  static Vec2 fromDir(const CardinalDirection& dir);

  std::string toString();

  Vec2 operator+(Vec2 other);
  Vec2 operator-(Vec2 other);
  Vec2 operator+(const Direction& dir);

  Vec2 operator*(const int other) const;
};
