#include "layoutGenerator.h"

#include "math/math.h"

namespace WorldGenerator {

// generator for all random values
std::default_random_engine generator;

DungeonGenerationStyle genStyle;

DungeonLayout generateDungeonLayout(DungeonGenerationStyle style, std::default_random_engine gen) {
  generator = gen;
  genStyle = style;

  auto layout = DungeonLayout();

  // Creates first room, in center of world
  auto startRoom = randomRoom(Vec2(0, 0));
  startRoom.type = DungeonRoom::RoomType::START;
  layout.rooms.push_back(startRoom);

  // Creates main branch of dungeon
  forcedLayoutBranch(layout, startRoom);

  // Selects a random room and creates a new branch
  for (int i = 0; i < genStyle.BRANCH_COUNT; i++) {
    std::uniform_int_distribution<int> distribution(0, layout.rooms.size());
    int roomIndex = distribution(generator);

    // Create a layout branch
    forcedLayoutBranch(layout, layout.rooms[roomIndex]);

    // Make sure start rooms remain start
    if (layout.rooms[roomIndex].type != DungeonRoom::RoomType::START)
      layout.rooms[roomIndex].type = DungeonRoom::RoomType::MAIN;
  }

  // Tries to add extra rooms to all main rooms
  /*
  for (auto r : layout.rooms) {
    if (r.type == DungeonRoom::RoomType::NORMAL) {
      forceCreateAndConnectRoom(layout, r, DungeonRoom::RoomType::RANDOM);
    }
  }
  */

  // calculate layout bounds
  layout.calculateBounds();

  return layout;
}

void forcedLayoutBranch(DungeonLayout& layout, DungeonRoom root) {
  // Create a reference to what room the branch connects
  DungeonRoom& connectingRoom = root;
  // Loops through the amount of rooms to create
  for (int i = 0; i < genStyle.ROOM_COUNT; ++i) {
    // Create a new corridor and a new room
    auto type = (i == genStyle.ROOM_COUNT - 1)
                    ? DungeonRoom::RoomType::END
                    : DungeonRoom::RoomType::NORMAL;

    auto room = forceCreateAndConnectRoom(layout, root, type);

    // Tries to create a new side room (branch, only 1 room long)
    std::uniform_real_distribution<float> distribution(0, 1);
    if (distribution(generator) < genStyle.RANDOM_BRANCH_CHANCE) {
      forceCreateAndConnectRoom(layout, room, DungeonRoom::RoomType::RANDOM);
    }

    //Updates connectingRoom to new room
    connectingRoom = room;
  }
}

DungeonRoom forceCreateAndConnectRoom(DungeonLayout& layout, DungeonRoom& room, DungeonRoom::RoomType type) {
  bool valid = false;
  int retries = 0;

  DungeonCorridor corridor;
  DungeonRoom newRoom;

  // Picks a random cardinal direction
  CardinalDirection dir = randomCardinal();

  // While new room is not valid
  while (!valid) {
    // Choose a new direction if out of retries
    if (retries % genStyle.CORRIDOR_TRIES == genStyle.CORRIDOR_TRIES - 1) {
      dir = randomCardinal();
    }

    // Creates a corridor somewhere along wall
    corridor = randomCorridorAlongWall(room, dir);

    Vec2 end = corridor.getEnd();

    // Creates a new room, connected to corridor end
    newRoom = randomRoomConnectedTo(end, dir);

    // Tests if room is valid, else, retry
    if (!layoutConflicting(layout, newRoom))
      valid = true;
    else
      retries++;
  }

  room.connections++;
  newRoom.type = type;
  layout.corridors.push_back(corridor);
  layout.rooms.push_back(newRoom);
  return newRoom;
}

void createAndConnectRoom(DungeonLayout layout, DungeonRoom room, DungeonRoom::RoomType roomType) {
  bool valid = false;
  int retries = 0;

  DungeonCorridor corridor;
  DungeonRoom newRoom;

  // Picks a random cardinal direction
  CardinalDirection dir = randomCardinal();

  // While new room is not valid
  while (!valid) {
    // Choose a new direction if out of retries
    if (retries % genStyle.CORRIDOR_TRIES == 0) {
      dir = randomCardinal();
    }

    // Creates a corridor somewhere along wall
    DungeonCorridor corridor = randomCorridorAlongWall(room, dir);

    Vec2 end = corridor.getEnd();

    // Creates a new room, connected to corridor end
    newRoom = randomRoomConnectedTo(end, dir);

    // Tests if room is valid, else, retry
    if (!layoutConflicting(layout, newRoom))
      valid = true;
    else
      retries++;

    if (retries > genStyle.UNFORCED_ROOM_RETRIES) return;
  }

  room.connections++;
  room.type = roomType;
  layout.corridors.push_back(corridor);
  layout.rooms.push_back(newRoom);
}

DungeonRoom randomRoomConnectedTo(Vec2 end, CardinalDirection dir) {
  auto room = DungeonRoom();
  Vec2 roomSize = randomRoomSize();
  room.width = roomSize.x;
  room.height = roomSize.y;

  std::uniform_int_distribution<int> xdistribution(1, room.width - 1);
  int alongWallX = xdistribution(generator);
  std::uniform_int_distribution<int> ydistribution(1, room.height - 1);
  int alongWallY = ydistribution(generator);

  Vec2 pos = Vec2();
  switch (dir) {
    case CardinalDirection::N:
      pos.x = end.x - alongWallX;
      pos.y = end.y - roomSize.y;
      break;
    case CardinalDirection::E:
      pos.x = end.x;
      pos.y = end.y - alongWallY;
      break;
    case CardinalDirection::S:
      pos.x = end.x - alongWallX;
      pos.y = end.y;
      break;
    case CardinalDirection::W:
      pos.x = end.x - roomSize.x;
      pos.y = end.y - alongWallY;
      break;
  }

  room.pos = pos;
  room.connections += 1;
  return room;
}

bool layoutConflicting(DungeonLayout layout, DungeonRoom room) {
  for (auto r : layout.rooms) {
    if (roomsColliding(r, room)) return true;
  }

  for (auto c : layout.corridors) {
    if (roomCorridorColliding(room, c)) return true;
  }

  return false;
}

bool roomsColliding(DungeonRoom& a, DungeonRoom& b) {
  if (a.pos.x < b.pos.x + b.width + genStyle.ROOM_COLLISION_OFFSET &&
      a.pos.x + a.width + genStyle.ROOM_COLLISION_OFFSET > b.pos.x &&
      a.pos.y < b.pos.y + b.height + genStyle.ROOM_COLLISION_OFFSET &&
      a.pos.y + a.height + genStyle.ROOM_COLLISION_OFFSET > b.pos.y)
    return true;
  return false;
}
bool roomCorridorColliding(DungeonRoom& r, DungeonCorridor& c) {
  switch (c.dir) {
    case CardinalDirection::N:
      if (c.pos.x < r.pos.x + r.width &&
          c.pos.x > r.pos.x &&
          c.pos.y > r.pos.y &&
          c.pos.y < r.pos.y + r.height + c.length)
        return true;
      break;
    case CardinalDirection::E:
      if (c.pos.x < r.pos.x + r.width + c.length &&
          c.pos.x > r.pos.x &&
          c.pos.y > r.pos.y &&
          c.pos.y < r.pos.y + r.height)
        return true;
      break;
    case CardinalDirection::S:
      if (c.pos.x < r.pos.x + r.width &&
          c.pos.x > r.pos.x &&
          c.pos.y > r.pos.y - c.length &&
          c.pos.y < r.pos.y + r.height)
        return true;
      break;
    case CardinalDirection::W:
      if (c.pos.x < r.pos.x + r.width &&
          c.pos.x > r.pos.x - c.length &&
          c.pos.y > r.pos.y &&
          c.pos.y < r.pos.y + r.height)
        return true;
      break;
  }

  return false;
}

DungeonCorridor randomCorridorAlongWall(DungeonRoom room, CardinalDirection dir) {
  DungeonCorridor corridor = DungeonCorridor();
  Vec2 pos = Vec2();

  std::uniform_int_distribution<int> xdistribution(1, room.width - 1);
  int alongWallX = xdistribution(generator);
  std::uniform_int_distribution<int> ydistribution(1, room.height - 1);
  int alongWallY = ydistribution(generator);

  switch (dir) {
    case CardinalDirection::N:
      pos.x = room.pos.x + alongWallX;
      pos.y = room.pos.y - 1;
      break;
    case CardinalDirection::E:
      pos.x = room.pos.x + room.width;
      pos.y = room.pos.y + alongWallY;
      break;
    case CardinalDirection::S:
      pos.x = room.pos.x + alongWallX;
      pos.y = room.pos.y + room.height;
      break;
    case CardinalDirection::W:
      pos.x = room.pos.x - 1;
      pos.y = room.pos.y + alongWallY;
      break;
  }

  corridor.dir = dir;
  corridor.pos = pos;

  std::uniform_int_distribution<int> ldistribution(1, 3);
  corridor.length = ldistribution(generator);
  return corridor;
}

CardinalDirection randomCardinal() {
  // Picks a random cardinal direction
  std::uniform_int_distribution<int> distribution(0, 3);
  int intDir = distribution(generator);
  // Create direction object
  CardinalDirection dir = (CardinalDirection)intDir;
  return dir;
}

DungeonRoom randomRoom(Vec2 pos) {
  DungeonRoom room = DungeonRoom();
  Vec2 roomSize = randomRoomSize();

  room.pos = pos;
  room.width = roomSize.x;
  room.height = roomSize.y;
  return room;
}

Vec2 randomRoomSize() {
  Vec2 size = Vec2();

  // Create normal distribution that distributes size.x size.y
  std::normal_distribution<float> ndistribution(genStyle.ROOM_SIZE_MEAN, genStyle.ROOM_SIZE_DEV);
  // Clamps size between min and max
  size.x = Math::clamp(int(ndistribution(generator)), genStyle.ROOM_SIZE_MIN, genStyle.ROOM_SIZE_MAX);
  size.y = Math::clamp(int(ndistribution(generator)), genStyle.ROOM_SIZE_MIN, genStyle.ROOM_SIZE_MAX);

  // Create uniform distribution
  std::uniform_real_distribution<float> distribution(0, 1);
  int rand = distribution(generator);

  // Give chance to force room bigger
  if (rand < genStyle.BIG_ROOM_CHANCE) {
    size = size * genStyle.BIG_ROOM_FACTOR;
  }
  return size;
}

}  // namespace WorldGenerator