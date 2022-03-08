#pragma once

#include <math.h>
#include <string>

#include "../definitions.h"

class Entity {

public:
  virtual void Act();

  virtual std::string GetIcon() const;

  int GetX() const;
  int GetY() const;

  void MoveUp();
  void MoveDown();
  void MoveLeft();
  void MoveRight();

protected:
  int CurrentX = 0;
  int CurrentY = 0;

  int Size = 1;

};

void Entity::Act() {}

std::string Entity::GetIcon() const {
  return std::string("X");
}

int Entity::GetX() const {
  return CurrentX;
}

int Entity::GetY() const {
  return CurrentY;
}

void Entity::MoveUp() {
  CurrentY = fmax(0, CurrentY - 1);
}

void Entity::MoveDown() {
  CurrentY = fmin(CurrentY + 1, ScreenHeight - 1);
}

void Entity::MoveLeft() {
  CurrentX = fmax(0, CurrentX - 1);
}

void Entity::MoveRight() {
  CurrentX = fmin(CurrentX + 1, ScreenWidth - 1);
}
