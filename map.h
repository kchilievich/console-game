#pragma once

#include "definitions.h"
#include <vector>
#include <string>

class Entity;

using namespace std;

class Map {
 public:
  Map();
  void AddEntity(Entity* NewEntity);
  void UpdateEntities(vector<Entity*> Entities);

  int HorizontalSize();
  int VerticalSize();

  Entity* GetEntity(int x, int y);

  string GetCharAtLocation(int x, int y);
  int GetColorAtLocation(int x, int y);

 private:
  void Clear();

  vector<vector<Entity*>> EntitiesMap;
};
