#pragma once

#include <string>

#include "itemStack.h"
#include "resources/resourceManager.h"
#include "resources/textureAtlas.h"

// NOTE! All item entities should be allocated on heap.
struct ItemEntity {
    ItemStack itemStack;
    Vec2 pos;

    // Coverts the itementity to a string (to be printed).
    std::string toString();
};