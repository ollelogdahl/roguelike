#pragma once

#include <vector>

#include "itemStack.h"

class Inventory {
public:
  void addItem(ItemStack* item);
private:
  std::vector<ItemStack*> items;
};