#pragma once

#include <string>

#include "pugixml.hpp"

#include "math/vec2.h"

struct Item {
public:
  std::string name;
  std::string description;

  std::string pluralName;

  int baseValue;
  int stackSize;

  std::string texture;
  int spriteIndex;

  // Load item definition in XML node representing an item
  static Item fromXML(pugi::xml_node node);
};
