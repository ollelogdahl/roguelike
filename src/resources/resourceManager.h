#pragma once

#include <string>
#include <vector>

#include "item.h"
#include "breed.h"
#include "heroClass.h"

#include "registry.h"

namespace ResourceManager {

Item getItem(std::string id);
Breed getBreed(std::string id);
HeroClass getHeroClass(std::string id);

// Find all datapacks
std::vector<std::string> getDatapacks(std::string datapackFolder);

// Register all type objects in a single xml file to their according registries
void registerXmlResource(std::string path);

// Find all resource files
std::vector<std::string> getResources(std::string path, std::string ext);

// Load all resources from datapack folder
void loadAllResources(std::string datapackPath);
}  // namespace ResourceManager