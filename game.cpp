#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>

#include "definitions.h"
#include "map.cpp"
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
  const Map& GetMap();

  template<class T>
  T* Spawn();

private:
  void ClearMap();
  void InitializePlayer();
  void ConsumePlayerInput(int ch);

  vector<Entity*> Entities;

  Map CurrentMap;

  Entity* Player;

  const int EnemiesAmount = 15;

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
  CurrentMap.Clear();
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
  ClearMap();

  if (Entities.size() < EnemiesAmount) {
    Entity* entity = Spawn<Enemy>();
    Entities.push_back(entity);
  }

  wmove(stdscr, 0, 0);

  for (vector<Entity*>::iterator i = Entities.begin(); i != Entities.end(); ) {
    Entity* entity = *i;

    if (!entity->GetIsMarkedForDestroy()) {
      entity->Act();
      CurrentMap.SetCharAtLocation(entity->GetX(), entity->GetY(), entity->GetIcon());
      i++;
    } else {
      Entities.erase(i);
    }
  }

  for (int y = 0; y < CurrentMap.HorizontalSize(); y++) {
    for (int x = 0; x < CurrentMap.VerticalSize(); x++) {
      printw(CurrentMap.GetCharAtLocation(x, y).c_str());
    }
    printw(string("\n").c_str());
  }
};
