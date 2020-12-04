#pragma once

#include <string>

#include "pugixml.hpp"
#include "math/vec2.h"

struct Breed {
  std::string name;

  int baseHp;
  int speed;

  std::string texture;
  int spriteIndex;

  static Breed fromXML(pugi::xml_node node);
};
