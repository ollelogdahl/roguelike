#include "resourceManager.h"

#include <filesystem>
#include <iostream>

#include <easylogging/easylogging++.h>
#include "textureAtlas.h"

namespace ResourceManager {

void registerXmlResource(std::string path) {
  // Parsear XML dokumentet
  pugi::xml_document document;
  pugi::xml_parse_result result = document.load_file(path.c_str());

  // Om misslyckades
  if (result.status != pugi::xml_parse_status::status_ok) {
    LOG(INFO) << "Error parsing " << path << " : " << result.description();
    return;
  }

  // Loads all definitions
  LOG(DEBUG) << "Searching " << path;

  // Register
  registerAllOfType(document, itemRegistry, "Item");
  registerAllOfType(document, breedRegistry, "Breed");
  registerAllOfType(document, heroClassRegistry, "HeroClass");

  for (pugi::xml_node node = document.child("Texture"); node; node = node.next_sibling("Texture")) {
    std::string id = node.child_value("id");
    std::string filePath = node.child_value("path");

    int split = path.find_last_of("/");
    std::string globalPath = path.substr(0, split) + "/" + filePath;

    TextureAtlas::addTextureFile(id, globalPath);
  }
}

// Finds all resource files.
std::vector<std::string> getResources(std::string path, std::string ext) {
  std::vector<std::string> resources = std::vector<std::string>();


  // Makes sure the directory given exists.
  if(!std::filesystem::exists(path)) {
    LOG(ERROR) << "Cannot find resources in directory " << path
     << " (doesn't exist)!" << std::endl;
    return resources;
  }

  for (std::filesystem::recursive_directory_iterator it(path), end; it != end; ++it) {
    if (it->path().extension() == ext) {
      resources.insert(resources.end(), it->path().string());
    }
  }

  return resources;
}

template<class T>
void registerAllOfType(pugi::xml_document& document, Registry<T>& reg, const std::string& typeName) {
  
  for (pugi::xml_node node = document.child(typeName.c_str()); node; 
       node = node.next_sibling(typeName.c_str())) {
    // Gets the id of the node.
    std::string id = node.child_value("id");
    // Calls the fromXML function of T, given the current node.
    auto object = T::fromXML(node);

    reg.registerObject(std::move(object), id);
  }
}

void loadAllResources(std::string path) {
  std::vector<std::string> xmlResources;
  std::vector<std::string> pngResources;

  // Fetch xml resources
  xmlResources = getResources(path, ".xml");
  int resourceCount = xmlResources.size();

  LOG(INFO) << "   " << resourceCount << " resources found.";

  // Register XML resources -------------------------------------------------------------
  for (auto resource : xmlResources) {
    registerXmlResource(resource);
  }

  LOG(INFO) << "   " << itemRegistry.getSize() << " items loaded.";
  LOG(INFO) << "   " << breedRegistry.getSize() << " breeds loaded.";
  LOG(INFO) << "   " << breedRegistry.getSize() << " hero classes loaded.";
}
}  // namespace ResourceManager