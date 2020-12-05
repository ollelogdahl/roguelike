#pragma once

#include <string>

#include "resources/resourceManager.h"
#include "item.h"

struct ItemStack {
  std::shared_ptr<Item> item;
  int itemCount;

  ItemStack(std::string id, int count) {
    item = ResourceManager::itemRegistry.getObject(id);
    if (count > item->stackSize)
      itemCount = item->stackSize;
    else
      itemCount = count;
  }

  ItemStack(std::string id) {
    item = ResourceManager::itemRegistry.getObject(id);
    itemCount = item->stackSize;
  }
};