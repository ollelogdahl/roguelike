#pragma once

#include <string>
#include <memory>

#include "resources/resourceManager.h"
#include "item.h"

struct ItemStack {
  std::unique_ptr<Item> item;
  int itemCount;
};