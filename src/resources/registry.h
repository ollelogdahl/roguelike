#pragma once

#include <map>
#include <string>
#include <iostream>

#include <easylogging/easylogging++.h>

// A object holding a dictionary for parsed items.
template <typename T>
class Registry {
 public:
  Registry() {
    // All registries have a missing type.
    //registerObject(T(), "missing");
    objects = std::map<std::string, T>();
  }

  void registerObject(T object, std::string id) {
    auto entry = std::pair<std::string, T>(id, object);
    objects.insert(entry);
  }

  T getObject(std::string id) {
    if(objects.count(id) > 0)
      return objects[id];
    
    LOG(WARNING) << "Missing registry entry '" << id << "'.";
    return objects["missing"];
  }

  int getSize() {
    return objects.size();
  }

 private:
  std::map<std::string, T> objects;
};