#pragma once

#include <string>

#include "resources/resourceManager.h"
#include "item.h"

struct ItemStack {
  Item item;
  int itemCount;

  ItemStack(std::string id, int count) {
    item = ResourceManager::getItem(id);
    if (count > item.stackSize)
      itemCount = item.stackSize;
    else
      itemCount = count;
  }

  ItemStack(std::string id) {
    item = ResourceManager::getItem(id);
    itemCount = item.stackSize;
  }
};