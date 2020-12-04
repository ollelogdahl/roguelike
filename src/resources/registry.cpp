#include "registry.h"

#include <easylogging/easylogging++.h>

template<class T>
void Registry<T>::registerObject(std::shared_ptr<T> object, std::string id) {
  auto entry = std::pair<std::string, std::shared_ptr<T>>(id, object);
  objects.insert(entry);
}

template<class T>
std::shared_ptr<T> Registry<T>::getObject(std::string id) {
  if(objects.count(id) > 0)
    return objects[id];
    
  LOG(WARNING) << "Missing registry entry '" << id << "'.";
  return nullptr;
}

template<class T>
int Registry<T>::getSize() {
  return objects.size();
}