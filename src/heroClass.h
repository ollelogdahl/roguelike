#pragma once

#include "pugixml.hpp"

#include "math/vec2.h"

struct HeroClass {
public:
  std::string name;

  int baseHp;
  int speed;

  std::string texture;
  int spriteIndex;

  static HeroClass fromXML(pugi::xml_node node);
};
