#pragma once

#include <pugixml.hpp>

#include <string>
#include <vector>

#include "item.h"
#include "breed.h"
#include "heroClass.h"

#include "registry.h"

namespace ResourceManager {

Registry<Item> itemRegistry = Registry<Item>();
Registry<Breed> breedRegistry = Registry<Breed>();
Registry<HeroClass> heroClassRegistry = Registry<HeroClass>();

// Find all datapacks
std::vector<std::string> getDatapacks(std::string datapackFolder);

// Register all type objects in a single xml file to their according registries
void registerXmlResource(std::string path);

// Find all resource files
std::vector<std::string> getResources(std::string path, std::string ext);

// Register all items of type T (parsed from a xml object called 'typeName') inside document,
// and calls it fromXML function.
// NOTE: T requires the fromXML function to be implemented!!!
template<class T>
void registerAllOfType(pugi::xml_document& document, Registry<T>& reg, const std::string& typeName);

// Load all resources from datapack folder
void loadAllResources(std::string datapackPath);
}  // namespace ResourceManager