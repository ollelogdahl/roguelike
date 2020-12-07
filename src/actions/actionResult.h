#pragma once

class Action;
class ActionResult {
 public:
  Action *alternate = nullptr;
  bool succeeded = false;

  ActionResult(bool s);
  ActionResult(Action *a);
};