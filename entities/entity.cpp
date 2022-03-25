#pragma once

#include <math.h>
#include <string>

#include "../definitions.h"

class Entity {

public:
  Entity();

  virtual void Act();

  const Icon* GetIcon() const;

  int GetX() const;
  int GetY() const;

  void MoveUp();
  void MoveDown();
  void MoveLeft();
  void MoveRight();

  void Destroy();
  virtual void OnDestroy();
  bool GetIsMarkedForDestroy() const;

protected:
  int CurrentX = 0;
  int CurrentY = 0;

  Icon* MapIcon;

  virtual void SetupIcon();
  virtual void Reset();

private:
  bool bIsMarkedForDestroy = false;

};

Entity::Entity() {
  MapIcon = new Icon();
  SetupIcon();
}

void Entity::Act() {}

void Entity::Reset() {}

void Entity::SetupIcon() {
  MapIcon->Symbol = std::string("?");
  MapIcon->Color = DEFAULT_COLOR_PAIR;
}

const Icon* Entity::GetIcon() const {
  return MapIcon;
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

void Entity::OnDestroy() {}

void Entity::Destroy() {
  OnDestroy();

  bIsMarkedForDestroy = true;
}

bool Entity::GetIsMarkedForDestroy() const {
  return bIsMarkedForDestroy;
}
