#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "definitions.h"
#include "entity.cpp"

using namespace std;

class Game {
  vector<Entity*> Entities;

  vector<vector<string>> Map;

  Entity* Player;

public:
  Game();

  void Run();
  void Draw();
  void ClearMap();

};

Game::Game() {
  ClearMap();
}

void Game::ClearMap() {
  vector<string> NewVec;
  const string x = "_";

  Map.clear();

  for(int i = 0; i < ScreenWidth; i++) {
    NewVec.push_back("_");
  }

  for(int i = 0; i < ScreenHeight; i++) {
    Map.push_back(NewVec);
  }
}

void Game::Run() {
  int ch = getch();

  Player = new Entity();
  Entities.push_back(Player);

  while(ch != 'q') {
    // Draw scene
    wmove(stdscr, 0, 0);
    Draw();

    if (ch == KEY_DOWN) {
      Player->MoveDown();
    }
    else if (ch == KEY_UP) {
      Player->MoveUp();
    }
    else if (ch == KEY_LEFT) {
      Player->MoveLeft();
    }
    else if (ch == KEY_RIGHT) {
      Player->MoveRight();
    }

    // Read new character
    ch = getch();
  }
};

void Game::Draw() {
  ClearMap();

  for (Entity* entity : Entities) {
    Map[entity->GetY()][entity->GetX()] = string("X");
  }

  for (int i = 0; i < Map.size(); i++) {
    for (int j = 0; j < Map[i].size(); j++) {
      printw(Map[i][j].c_str());
    }
    printw(string("\n").c_str());
  }
};
