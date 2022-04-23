
#include "wall.h"

Wall::Wall() {
  SetupIcon();
}

void Wall::SetupIcon() {
  MapIcon->Symbol = string("=");
  MapIcon->Color = WALL_COLOR_PAIR;
}

void Wall::SetPosition(int x, int y) {
  CurrentX = x;
  CurrentY = y;
}
