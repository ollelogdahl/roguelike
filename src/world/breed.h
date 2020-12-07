#pragma once

#include <pugixml.hpp>
#include <string>
#include <memory>

#include "math/vec2.h"

struct Breed {
  std::string name;

  int baseHp;
  int speed;

  std::string texture;
  int spriteIndex;

  static std::unique_ptr<Breed> fromXML(pugi::xml_node node);
};
