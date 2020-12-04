#include "resourceManager.h"

#include <filesystem>
#include <iostream>

#include "easylogging/easylogging++.h"
#include "pugixml.hpp"
#include "textureAtlas.h"

namespace ResourceManager {
Registry<Item> itemRegistry = Registry<Item>();
Registry<Breed> breedRegistry = Registry<Breed>();
Registry<HeroClass> heroClassRegistry = Registry<HeroClass>();

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

  for (pugi::xml_node node = document.child("Item"); node; node = node.next_sibling("Item")) {
    // de-serialiserar ett object av node
    std::string id = node.child_value("id");
    Item object = Item::fromXML(node);

    // Lägger till till itemRegistry
    itemRegistry.registerObject(object, id);
  }

  for (pugi::xml_node node = document.child("Breed"); node; node = node.next_sibling("Breed")) {
    // de-serialiserar ett object av node
    std::string id = node.child_value("id");
    Breed object = Breed::fromXML(node);

    // Lägger till till itemRegistry
    breedRegistry.registerObject(object, id);
  }

  for (pugi::xml_node node = document.child("HeroClass"); node; node = node.next_sibling("HeroClass")) {
    // de-serialiserar ett object av node
    std::string id = node.child_value("id");
    HeroClass object = HeroClass::fromXML(node);

    // Lägger till till itemRegistry
    heroClassRegistry.registerObject(object, id);
  }

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

Item getItem(std::string id) {
  return itemRegistry.getObject(id);
}
Breed getBreed(std::string id) {
  return breedRegistry.getObject(id);
}
HeroClass getHeroClass(std::string id) {
  return heroClassRegistry.getObject(id);
}

}  // namespace ResourceManager