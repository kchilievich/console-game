#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>
#include <atomic>
#include <thread>

#include "definitions.h"
#include "entities/entity.cpp"
#include "entities/enemy.cpp"

using namespace std;

class Game {
  vector<Entity*> Entities;

  vector<vector<string>> Map;

  Entity* Player;

public:
  Game();

  void Run();
  void Draw();
  atomic<bool> bIsRunning;

private:
  void ClearMap();
  void InitializePlayer();
  void InitializeEnemies();
  void ConsumePlayerInput(int ch);

  const int EnemiesAmount = 4;

};

Game::Game() {
  ClearMap();
  InitializeEnemies();
  InitializePlayer();
}

void Game::ClearMap() {
  Map.clear();

  vector<string> NewVec;
  for(int i = 0; i < ScreenWidth; i++) {
    NewVec.push_back(".");
  }

  for(int i = 0; i < ScreenHeight; i++) {
    Map.push_back(NewVec);
  }
}

void Game::InitializePlayer() {
  Player = new Entity();
  Entities.push_back(Player);
}

void Game::InitializeEnemies() {
  Entities.reserve(EnemiesAmount);

  for (int i = 0; i <= EnemiesAmount; i++) {
    Entity* NewEnemy = new Enemy();
    Entities.emplace_back(std::move(NewEnemy));
  }
}

void Game::ConsumePlayerInput(int ch) {
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
}

void Game::Run() {
  int ch = getch();

  bIsRunning = true;
  thread Drawing(&Game::Draw, this);

  while(ch != 'q') {
    // Process input
    ConsumePlayerInput(ch);

    // Read new character
    ch = getch();
  }

  bIsRunning = false;
  Drawing.join();
};

void Game::Draw() {
  while(bIsRunning) {
    ClearMap();
    wmove(stdscr, 0, 0);

    for (Entity* entity : Entities) {
      entity->Act();
      Map[entity->GetY()][entity->GetX()] = entity->GetIcon();
    }

    for (int i = 0; i < Map.size(); i++) {
      for (int j = 0; j < Map[i].size(); j++) {
        printw(Map[i][j].c_str());
      }
      printw(string("\n").c_str());
    }

    usleep(50000);
  }
};
