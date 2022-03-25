#include "map.h"
#include "entities/entity.cpp"

Map::Map() {
  vector<Entity*> NewVec(ScreenWidth, nullptr);

  for(int i = 0; i < ScreenHeight; i++) {
    EntitiesMap.push_back(NewVec);
  }
}

void Map::AddEntity(Entity* NewEntity) {
  int x = NewEntity->GetX();
  int y = NewEntity->GetY();

  if (EntitiesMap[y][x] != nullptr) {
    // TODO: do something about it ffs
  }

  EntitiesMap[y][x] = NewEntity;
}

void Map::UpdateEntities(vector<Entity*> Entities) {
  Clear();

  for (Entity* _Entity : Entities) {
    AddEntity(_Entity);
  }
}

Entity* Map::GetEntity(int x, int y) {
  return EntitiesMap[y][x];
}

int Map::HorizontalSize() {
  return EntitiesMap.size();
}

int Map::VerticalSize() {
  return EntitiesMap[0].size();
}

string Map::GetCharAtLocation(int x, int y) {
  Entity* EntityAtLocation = GetEntity(x, y);

  return EntityAtLocation != nullptr ? EntityAtLocation->GetIcon()->Symbol : DEFAULT_SYMBOL;
}

int Map::GetColorAtLocation(int x, int y) {
  Entity* EntityAtLocation = GetEntity(x, y);

  return EntityAtLocation != nullptr ? EntityAtLocation->GetIcon()->Color : DEFAULT_COLOR_PAIR;
}

void Map::Clear() {
  for (int y = 0; y < HorizontalSize(); y++) {
    for (int x = 0; x < VerticalSize(); x++) {
      EntitiesMap[y][x] = nullptr;
    }
  }
}
