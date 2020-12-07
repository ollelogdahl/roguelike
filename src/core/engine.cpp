#include "engine.h"

#include <iostream>

#include "action.h"
#include "actionResult.h"
#include <easylogging/easylogging++.h>
#include "monster.h"
#include "sdlHandler.h"
#include "keyboard.h"

#include "renderHelper.h"

void Engine::init() {
  // Initialize keyboard
  Keyboard::init();

  // Create the game
  game = std::unique_ptr<Game>(new Game());
}

void Engine::update() {
  process();
}

// Processes one units turn
void Engine::process() {
  LOG(DEBUG) << "Process actor " << currentActor;

  // Give energy to actor
  game->getActors()[currentActor]->gainEnergy();
  LOG(DEBUG) << "Gain Energy";

  // If the actor has enough energy to make action
  if (game->getActors()[currentActor]->hasEnoughEnergy()) {
    LOG(DEBUG) << "Enough energy. Calculate turn";
    Action *action = game->getActors()[currentActor]->getAction();
    if (action == NULL) return;

    LOG(DEBUG) << "Action available";

    // Consume energy
    game->getActors()[currentActor]->consumeEnergy();

    while (true) {
      auto result = action->perform(game->getActors()[currentActor].get());

      LOG(DEBUG) << "Action performed (" << result.succeeded << ", " << result.alternate << ")";

      // If action succeeded, and didn't give alternate, exit loop
      if (result.alternate == nullptr) { 
        break;
      }
      // If action gave alternate action, perform that action
      else action = result.alternate;
    }

    LOG(DEBUG) << "Actions performed.";
  }

  // Proceed to next actor
  currentActor = (currentActor + 1) % game->getActors().size();
}

void Engine::render(SDL_Renderer* renderer) {
  SDL_RenderClear(renderer);

  // Rendera tilemap
  RenderHelper::renderTilemap(game->getMap());
  
  // Rendera item entities
  for (auto i : game->getItems()) {
    RenderHelper::renderItem(i);
  }

  // Rendera actors
  for (auto &a : game->getActors()) {
    a->render(renderer);
  }

  // Skriv text om item ifall spelare står på item
  ItemEntity *ent = game->itemAt(game->getPlayer()->pos);
  if(ent != NULL)
    RenderHelper::renderText(ent->toString(), 16, Vec2(0, 880-16));

  if(Keyboard::keyPressed(SDL_SCANCODE_ESCAPE)) 
    RenderHelper::renderAtlas();

  SDL_RenderPresent(renderer);
}

void Engine::gameLoop() {
  SDL_Renderer* renderer = SDLHandler::getRenderer();
  RenderHelper::setup(renderer);

  bool quit = false;
  SDL_Event e;

  LOG(INFO) << "Beginning game loop...";
  while (!quit) {
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT) quit = true;
    }

    // Fetches new keyboard inputs.
    Keyboard::update();

    update();
    LOG(DEBUG) << "update done.";
    render(renderer);
    LOG(DEBUG) << "render done.";
  }
}