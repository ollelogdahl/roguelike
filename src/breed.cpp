#include "breed.h"

Breed Breed::fromXML(pugi::xml_node node) {
  Breed breed = Breed();

  // String values
  breed.name = node.child_value("label");

  breed.baseHp = node.child("baseHp").text().as_int();
  breed.speed = node.child("speed").text().as_int();

  breed.texture = node.child_value("texture");
  breed.spriteIndex = node.child("spriteIndex").text().as_int();

  return breed;
}
