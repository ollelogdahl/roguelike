#pragma once

class Engine;
class Actor;
class ActionResult;
class Action {
 public:
  virtual ActionResult perform(Actor *actor) = 0;
};