#pragma once

struct Rect2 {
  int x;
  int y;
  int w;
  int h;

  Rect2(int _x, int _y, int _w, int _h)
      : x(_x), y(_y), w(_w), h(_h) {}
};
