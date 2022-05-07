
#include "wall.h"

Wall::Wall() {
  SetupIcon();
}

void Wall::SetupIcon() {
  MapIcon->Symbol = string("=");
  MapIcon->Color = WALL_COLOR_PAIR;
}
