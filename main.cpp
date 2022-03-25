#include <ncurses.h>
#include "definitions.h"
#include "game.cpp"

using namespace std;

int main(void) {
  //setlocale(LC_TYPE, "");
  initscr();
  noecho();
  keypad(stdscr, TRUE);
  nodelay(stdscr, TRUE);
  curs_set(0);
  start_color();
  use_default_colors();

  init_pair(DEFAULT_COLOR_PAIR, COLOR_YELLOW, COLOR_GREEN);
  init_pair(PLAYER_COLOR_PAIR, COLOR_WHITE, COLOR_GREEN);
  init_pair(ENEMY_COLOR_PAIR, COLOR_RED, COLOR_GREEN);

  // main game cycle
  Game::GetInstance()->Run();

  //curses cleanup
  endwin();
  return 0;
}
