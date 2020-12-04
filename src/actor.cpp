#include "actor.h"

const int energyRequiredForTurn = 10;

bool Actor::hasEnoughEnergy() {
  return energy >= energyRequiredForTurn;
}

void Actor::consumeEnergy() {
  energy -= energyRequiredForTurn;
}

bool Actor::canOccupy(int tileIndex) {
  if(tileIndex == 0 || tileIndex == 3) return true;
  return false;
}