#pragma once

#include <pugixml.hpp>
#include <memory>

#include "math/vec2.h"

struct HeroClass {
public:
  std::string name;

  int baseHp;
  int speed;

  std::string texture;
  int spriteIndex;

  static std::unique_ptr<HeroClass> fromXML(pugi::xml_node node);
};
