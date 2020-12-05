#include "item.h"

std::unique_ptr<Item> Item::fromXML(pugi::xml_node node) {
  auto item = std::unique_ptr<Item>(new Item());

  // String values
  item->name = node.child_value("label");
  item->description = node.child_value("description");

  // If has no plural name, use same as singular
  item->pluralName = node.child_value("pluralLabel");
  if(item->pluralName == "")
    item->pluralName = item->name;

  // Others
  item->baseValue = node.child("baseValue").text().as_int();
  item->stackSize = node.child("stackSize").text().as_int();

  item->texture = node.child_value("texture");
  item->spriteIndex = node.child("spriteIndex").text().as_int();

  return item;
}
