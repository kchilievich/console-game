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

  // main game cycle
  Game game;
  game.Run();

  //curses cleanup
  endwin();
  return 0;
}
