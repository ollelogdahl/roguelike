cmake_minimum_required(VERSION 3.18)
project(roguelike VERSION 0.2.2)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "-Wfatal-errors")

set(CMAKE_BUILD_TYPE Debug)

# Provide custom FindSDL2 and FindSDL2_image scripts.
# This may be removed when/if cmake adds it by default. 
# Derived from findSDL_image.cmake
# https://github.com/aminosbh/sdl2-cmake-modules
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

# Suppress dev warnings (Some weird warning from FindSDL2_image).
if(NOT DEFINED CMAKE_SUPPRESS_DEVELOPER_WARNINGS)
     set(CMAKE_SUPPRESS_DEVELOPER_WARNINGS 1 CACHE INTERNAL "No dev warnings")
endif()

# Imports all needed packages.
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(pugixml REQUIRED)

# Creates a included header file for current version.
configure_file(src/cmake_config.h.in cmake_config.h)


# Copies the easylogging++ configure file to build directory.
configure_file(loggerConfig.conf "${PROJECT_BINARY_DIR}/loggerConfig.conf" COPYONLY)
# Copies resources to build directory.
file(COPY resources DESTINATION ${PROJECT_BINARY_DIR})

# Include dirs.
include_directories(
    ${PROJECT_BINARY_DIR}
    src/
    libs/
)

add_executable(roguelike 
    # compile libraries
    libs/easylogging/easylogging++.cpp
    
    # rougelike code
    src/math/vec2.cpp

    src/resources/registry.cpp
    src/resources/resourceManager.cpp
    src/resources/textureAtlas.cpp

    src/actions/walkAction.cpp
    src/actions/actionResult.cpp
    src/actions/attackAction.cpp
    src/actions/closeDoorAction.cpp
    src/actions/descendAction.cpp
    src/actions/openDoorAction.cpp
    src/actions/pickupItemAction.cpp

    src/world/actor.cpp
    src/world/breed.cpp
    src/world/hero.cpp
    src/world/hero.cpp
    src/world/map.cpp
    src/world/monster.cpp
    src/world/heroClass.cpp

    src/core/engine.cpp
    src/core/game.cpp
    src/core/inventory.cpp
    src/core/keyboard.cpp

    src/gen/dungeonDecorator.cpp
    src/gen/dungeonLayout.cpp
    src/gen/layoutGenerator.cpp
    src/gen/worldGenerator.cpp

    src/gfx/renderHelper.cpp
    src/gfx/sdlHandler.cpp

    src/main.cpp
)

target_precompile_headers(roguelike PRIVATE src/pch.h)
target_link_libraries(roguelike SDL2::Main SDL2::Image pugixml)