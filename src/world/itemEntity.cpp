#include "itemEntity.h"

std::string ItemEntity::toString() {
    std::string name = (itemStack.itemCount > 1)
                        ? itemStack.item->pluralName
                        : itemStack.item->name;
    return std::to_string(itemStack.itemCount) + " " + name;
}