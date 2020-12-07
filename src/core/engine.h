#pragma once

#include <vector>
#include <memory>
#include <SDL2/SDL.h>

#include "world/actor.h"
#include "resources/registry.h"
#include "game.h"

class Engine {
public:
  Engine() = default;
  ~Engine() {}

  void init();
  void update();
  void render(SDL_Renderer* renderer);

  void process();

  void gameLoop();

  // Registries
  Registry<Item> itemRegistry = Registry<Item>();
  Registry<Breed> breedRegistry = Registry<Breed>();
  Registry<HeroClass> heroClassRegistry = Registry<HeroClass>();

private:
  // Unique reference to the game.
  std::unique_ptr<Game> game = nullptr;
  int currentActor = 0;

  // enum representing the current game state.
  enum GameState {
    startup,
    idle,
    newturn
  } gameState = GameState::startup;
};
extern Engine engine;