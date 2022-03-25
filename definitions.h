#pragma once

#include <string>

#define DEFAULT_COLOR_PAIR 1
#define PLAYER_COLOR_PAIR 2
#define ENEMY_COLOR_PAIR 3

#define DEFAULT_SYMBOL string(".")

const int ScreenHeight = 20;
const int ScreenWidth = 40;

struct Icon {
  int Color;
  std::string Symbol;
};
