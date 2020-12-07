#pragma once

#include <vector>

#include "world/itemStack.h"

class Inventory {
public:
  void addItem(ItemStack* item);
private:
  std::vector<ItemStack*> items;
};