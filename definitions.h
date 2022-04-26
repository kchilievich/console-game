#pragma once

#include <string>

#define DEFAULT_COLOR_PAIR 1
#define PLAYER_COLOR_PAIR 2
#define ENEMY_COLOR_PAIR 3
#define WALL_COLOR_PAIR 4

#define DEFAULT_SYMBOL string(" ")

const int ScreenHeight = 51;
const int ScreenWidth = 151;

struct Icon {
  int Color;
  std::string Symbol;
};

struct Point {
  int X;
  int Y;
};
