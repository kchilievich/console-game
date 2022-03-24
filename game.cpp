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

// A singleton
class Game {
public:
  static Game* GetInstance();

  void Run();
  void Draw();

  Entity* GetPlayer();

  template<class T>
  T* Spawn();

private:
  void ClearMap();
  void InitializePlayer();
  void ConsumePlayerInput(int ch);

  vector<Entity*> Entities;

  vector<vector<string>> Map;

  Entity* Player;

  const int EnemiesAmount = 15;
  atomic<bool> bIsRunning;

  //Singleton logic

  Game();

  static Game* Instance;
};

Game* Game::Instance = 0;

Game::Game() {
  ClearMap();
  InitializePlayer();
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

void Game::ClearMap() {
  Map.clear();

  vector<string> NewVec;
  for(int i = 0; i < ScreenWidth; i++) {
    NewVec.push_back(" ");
  }

  for(int i = 0; i < ScreenHeight; i++) {
    Map.push_back(NewVec);
  }
}

void Game::InitializePlayer() {
  Player = Spawn<Entity>();
  Entities.push_back(Player);
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

    if (Entities.size() < EnemiesAmount) {
      Entity* entity = Spawn<Enemy>();
      Entities.push_back(entity);
    }

    for (vector<Entity*>::iterator i = Entities.begin(); i != Entities.end(); ) {
      Entity* entity = *i;

      if (!entity->GetIsMarkedForDestroy()) {
        entity->Act();
        Map[entity->GetY()][entity->GetX()] = entity->GetIcon();
        i++;
      } else {
        Entities.erase(i);
      }
    }

    for (int i = 0; i < Map.size(); i++) {
      for (int j = 0; j < Map[i].size(); j++) {
        printw(Map[i][j].c_str());
      }
      printw(string("\n").c_str());
    }

    usleep(30000);
  }
};
