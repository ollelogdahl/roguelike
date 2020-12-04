#include "math/vec2.h"



std::string Vec2::toString() {
  return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
}



Vec2 Vec2::fromDir(const Direction& dir) {
    Vec2 n = Vec2();

    switch (dir) {
      case Direction::N:
        n.y -= 1;
        break;
      case Direction::NE:
        n.x += 1;
        n.y -= 1;
        break;
      case Direction::E:
        n.x += 1;
        break;
      case Direction::SE:
        n.x += 1;
        n.y += 1;
        break;
      case Direction::S:
        n.y += 1;
        break;
      case Direction::SW:
        n.x -= 1;
        n.y += 1;
        break;
      case Direction::W:
        n.x -= 1;
        break;
      case Direction::NW:
        n.x -= 1;
        n.y -= 1;
        break;
    }

    return n;
}

Vec2 Vec2::fromDir(const CardinalDirection& dir) {
    Vec2 n = Vec2();

    switch (dir) {
      case CardinalDirection::N:
        n.y -= 1;
        break;
      case CardinalDirection::E:
        n.x += 1;
        break;
      case CardinalDirection::S:
        n.y += 1;
        break;
      case CardinalDirection::W:
        n.x -= 1;
        break;
    }

    return n;
}

Vec2 Vec2::operator+(Vec2 other) {
  return Vec2(x + other.x, y + other.y);
}
Vec2 Vec2::operator-(Vec2 other) {
  return Vec2(x - other.x, y - other.y);
}

Vec2 Vec2::operator+(const Direction& dir) {
  return *this + Vec2::fromDir(dir);
}

Vec2 Vec2::operator*(const int i) const {
  return Vec2(x * i, y * i);
}