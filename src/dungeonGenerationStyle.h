#pragma once

#include "dungeonDecorator.h"

namespace WorldGenerator {

struct DungeonGenerationStyle {
  // Layout generation settings ---------------------------------------------------------

  // Room count per branch
  int ROOM_COUNT = 4;
  // Average room size
  int ROOM_SIZE_MEAN = 7;
  // Standard deviation in room size
  float ROOM_SIZE_DEV = 1.4f;
  // Room size minimum
  int ROOM_SIZE_MIN = 4;
  // Room size maximum
  int ROOM_SIZE_MAX = 15;

  // Amount of extra branches
  int BRANCH_COUNT = 4;

  // Chance for a room to turn big
  float BIG_ROOM_CHANCE = 0.15f;
  // Factor to multiply size with
  float BIG_ROOM_FACTOR = 1.6f;

  int MAX_RETRIES = 100;

  // Tries of placing room with same corridor, may force tighter layout. Higher values takes more time to process.
  int CORRIDOR_TRIES = 20;

  int UNFORCED_ROOM_RETRIES = 50;

  // Chance to create a random branch
  float RANDOM_BRANCH_CHANCE = 0.2f;

  float CONNECT_OVERLAP_CHANCE = 0.2f;

  int ROOM_COLLISION_OFFSET = 1;

  // Dungeon populators -----------------------------------------------------------------

  DungeonDecorator decorator;
};

}