#pragma once

#include <vector>
#include <string>

using namespace std;

class Map {
public:
  void Clear();
  int HorizontalSize();
  int VerticalSize();

  string GetCharAtLocation(int x, int y);
  void SetCharAtLocation(int x, int y, string str);

private:
  vector<vector<string>> Container;
};

void Map::Clear() {
  Container.clear();

  vector<string> NewVec;
  for(int i = 0; i < ScreenWidth; i++) {
    NewVec.push_back(" ");
  }

  for(int i = 0; i < ScreenHeight; i++) {
    Container.push_back(NewVec);
  }
}

int Map::HorizontalSize() {
  return Container.size();
}

int Map::VerticalSize() {
  return Container[0].size();
}

string Map::GetCharAtLocation(int x, int y) {
  return Container[y][x];
}

void Map::SetCharAtLocation(int x, int y, string str) {
  Container[y][x] = str;
}
