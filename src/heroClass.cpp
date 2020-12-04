#include "heroClass.h"

HeroClass HeroClass::fromXML(pugi::xml_node node) {
    HeroClass heroClass = HeroClass();

    heroClass.name = node.child_value("label");
    
    heroClass.baseHp = node.child("baseHp").text().as_int();
    heroClass.speed = node.child("speed").text().as_int();


    heroClass.baseHp = node.child("baseHp").text().as_int();

    heroClass.texture = node.child_value("texture");
    heroClass.spriteIndex = node.child("spriteIndex").text().as_int();

    return heroClass;
}
