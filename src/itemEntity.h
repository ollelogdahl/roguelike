#pragma once

#include <string>

#include "itemStack.h"
#include "resources/resourceManager.h"
#include "resources/textureAtlas.h"

struct ItemEntity {
  ItemStack itemStack;

  Vec2 pos;

  std::string toString() {
    std::string name = (itemStack.itemCount > 1)
                           ? itemStack.item.pluralName
                           : itemStack.item.name;
    return std::to_string(itemStack.itemCount) + " " + name;
  }

  ItemEntity(std::string id, int count, int x, int y)
   : itemStack(id, count), pos(x, y) {}
};