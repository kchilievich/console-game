#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>

#include "definitions.h"
#include "map.cpp"
#include "entities/entity.cpp"
#include "entities/enemy.cpp"
#include "entities/player.cpp"

using namespace std;

// A singleton
class Game {
public:
  static Game* GetInstance();

  void Run();
  void Draw();

  Entity* GetPlayer();
  Map* GetMap();

  template<class T>
  T* Spawn();

private:
  void InitializePlayer();
  void ConsumePlayerInput(int ch);

  vector<Entity*> Entities;

  Map* CurrentMap;

  Player* CurrentPlayer;

  //Singleton logic

  Game();

  static Game* Instance;
};

Game* Game::Instance = 0;

Game::Game() {
  CurrentMap = new Map();
  InitializePlayer();
  CurrentMap->UpdateEntities(Entities);
}

Game* Game::GetInstance() {
  if (Instance == 0) {
    Instance = new Game();
  }

  return Instance;
}

template<class T>
T* Game::Spawn() {
  return new T();
}

void Game::InitializePlayer() {
  CurrentPlayer = Spawn<Player>();
  Entities.push_back(CurrentPlayer);
}

void Game::ConsumePlayerInput(int ch) {
  if (ch == KEY_DOWN) {
    CurrentPlayer->MoveDown();
  }
  else if (ch == KEY_UP) {
    CurrentPlayer->MoveUp();
  }
  else if (ch == KEY_LEFT) {
    CurrentPlayer->MoveLeft();
  }
  else if (ch == KEY_RIGHT) {
    CurrentPlayer->MoveRight();
  }
}

void Game::Run() {
  Draw();

  int ch = getch();

  while(ch != 'q' && ch != 'Q') {
    if (ch > 0) {
      // Process input
      ConsumePlayerInput(ch);

      Draw();
    }

    // Read new character
    ch = getch();
  }
};

void Game::Draw() {
  wmove(stdscr, 0, 0);

  for (vector<Entity*>::iterator i = Entities.begin(); i != Entities.end(); ) {
    Entity* entity = *i;

    if (!entity->GetIsMarkedForDestroy()) {
      entity->Act();
      CurrentMap->UpdateEntities(Entities);
      i++;
    } else {
      Entities.erase(i);
    }
  }

  // Draw Map
  for (int y = 0; y < CurrentMap->HorizontalSize(); y++) {
    for (int x = 0; x < CurrentMap->VerticalSize(); x++) {
      int ColorPair = CurrentMap->GetColorAtLocation(x, y);
      attron(COLOR_PAIR(ColorPair));
      printw(CurrentMap->GetCharAtLocation(x, y).c_str());
      attroff(COLOR_PAIR(ColorPair));
    }
    printw(string("\n").c_str());
  }

  // Draw UI
  wmove(stdscr, CurrentMap->HorizontalSize() + 1, 1);
  printw(string("Cool Game").c_str());
};
