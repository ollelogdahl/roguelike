#pragma once

#include <map>
#include <string>
#include <iostream>

#include <easylogging/easylogging++.h>

template <typename T>
using pt_map = std::map<std::string, std::shared_ptr<T>>;

// A object holding a dictionary for parsed items.
// Every registry entry owns the object. Objects are only removed when
// The registry is deconstructed.
template <typename T>
class Registry {
public:
  Registry() : objects() {}

  // Add a new object to the registry.
  void registerObject(std::shared_ptr<T> object, std::string id);

  // Gets an object from the registry.
  std::shared_ptr<T> getObject(std::string id);

  // Gets the number of objects in registry.
  int getSize();

private:
  pt_map<T> objects;
};