#pragma once

#include <string>

#include "itemStack.h"
#include "resources/resourceManager.h"
#include "resources/textureAtlas.h"

// NOTE! All item entities should be allocated on heap.
struct ItemEntity {
    ItemStack itemStack;

  Vec2 pos;

  std::string toString() {
    std::string name = (itemStack.itemCount > 1)
                           ? itemStack.item->pluralName
                           : itemStack.item->name;
    return std::to_string(itemStack.itemCount) + " " + name;
  }
};