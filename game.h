#pragma once

#include <ncurses.h>
#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>

#include "definitions.h"

class Entity;
class Map;
class Player;

using namespace std;

// A singleton
class Game {
 public:
  static Game* GetInstance();
  void AddMessage(string NewMessage);

  void Run();
  void Draw();

  Player* GetPlayer() const;
  Map* GetMap() const;

  template<class T>
  T* Spawn(int x, int y);

  void Over();

 private:
  void InitializePlayer(int x, int y);
  void ConsumePlayerInput(int ch);

  vector<Entity*> Entities;
  vector<string> Messages;

  Map* CurrentMap;

  Player* CurrentPlayer;

  //Singleton logic

  Game();

  static Game* Instance;
  bool bIsRunning = true;
};

Game* Game::Instance = 0;
