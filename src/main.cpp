#include <iostream>

#include "resourceManager.h"
#include "sdlHandler.h"
#include "engine.h"

#include <easylogging/easylogging++.h>

#include "textureAtlas.h"

#include "cmake_config.h"

// Screen dimension constants
const int SCREEN_WIDTH = 1400;
const int SCREEN_HEIGHT = 880;

// Initialize logger
INITIALIZE_EASYLOGGINGPP

#define NDEBUG

int main() {

  // Load easylogging config
  el::Configurations conf("loggerConfig.conf");
  el::Loggers::reconfigureAllLoggers(conf);

  // info i dbg
  std::cout << " Roguelike " << app_VERSION << std::endl;
  std::cout << "------------------" << std::endl;

  // Initiera SDL och fönster
  if (SDLHandler::initWindow(SCREEN_WIDTH, SCREEN_HEIGHT) == 1) return 1;
  SDL_Renderer *renderer = SDLHandler::getRenderer();

  // Load all resources, and compile a texture atlas.
  ResourceManager::loadAllResources("resources/core");
  LOG(INFO) << "Resources loaded!";

  TextureAtlas::createAtlas(renderer);
  LOG(INFO) << "Texture Atlas created!";

  // Initiera engine
  Engine engine = Engine();
  engine.init();
  LOG(INFO) << "Engine initialized.";

  engine.gameLoop();

  SDLHandler::close();

  LOG(INFO) << "SDL Components closed.";

  return 0;
}