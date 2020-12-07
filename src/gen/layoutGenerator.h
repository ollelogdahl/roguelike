#pragma once

#include <algorithm>
#include <random>
#include <vector>

#include "math/direction.h"
#include "dungeonCorridor.h"
#include "dungeonLayout.h"
#include "dungeonRoom.h"
#include "world/map.h"
#include "math/rect2.h"
#include "math/vec2.h"

#include "dungeonGenerationStyle.h"

namespace WorldGenerator {

DungeonLayout generateDungeonLayout(DungeonGenerationStyle genStyle, std::default_random_engine generator);

// Force-create a brach from room 'root'
void forcedLayoutBranch(DungeonLayout &layout, DungeonRoom root);
// Force-create a connected room from room 'room'
DungeonRoom forceCreateAndConnectRoom(DungeonLayout &layout, DungeonRoom &room, DungeonRoom::RoomType type);
// Try create a connected room from room 'room'
void createAndConnectRoom(DungeonLayout layout, DungeonRoom room, DungeonRoom::RoomType type);

// Create a random corridor somewhere along wall in direction 'dir'
DungeonCorridor randomCorridorAlongWall(DungeonRoom room, CardinalDirection dir);

// Returns a random room, connected on the opposite side of 'dir' to point 'end'
DungeonRoom randomRoomConnectedTo(Vec2 end, CardinalDirection dir);

//Returns true if 'room' collides with some other room in layout
bool layoutConflicting(DungeonLayout layout, DungeonRoom room);

bool roomsColliding(DungeonRoom& a, DungeonRoom& b);
bool roomCorridorColliding(DungeonRoom& a, DungeonCorridor& c);

// Generates a random dimensioned room at pos
DungeonRoom randomRoom(Vec2 pos);

// Generates a random size for a room
Vec2 randomRoomSize();

// Create random cardinal direction
CardinalDirection randomCardinal();
}  // namespace WorldGenerator