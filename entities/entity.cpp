#pragma once

#include <math.h>
#include <string>

#include "../definitions.h"
#include "../game.h"
#include "../map.h"

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

  virtual bool CanBeSteppedUpon() const;

protected:
  int CurrentX = 0;
  int CurrentY = 0;

  Icon* MapIcon;

  virtual void SetupIcon();
  virtual void Reset();

private:
  bool bIsMarkedForDestroy = false;

  bool CheckIntersectionOnMap(int x, int y) const;

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

bool Entity::CanBeSteppedUpon() const {
  return false;
}

int Entity::GetX() const {
  return CurrentX;
}

int Entity::GetY() const {
  return CurrentY;
}

void Entity::MoveUp() {
  int NewY = fmax(0, CurrentY - 1);

  if (CheckIntersectionOnMap(CurrentX, NewY)) {
    CurrentY = NewY;
  }
}

void Entity::MoveDown() {
  int NewY = fmin(CurrentY + 1, ScreenHeight - 1);

  if (CheckIntersectionOnMap(CurrentX, NewY)) {
    CurrentY = NewY;
  }
}

void Entity::MoveLeft() {
  int NewX = fmax(0, CurrentX - 1);

  if (CheckIntersectionOnMap(NewX, CurrentY)) {
    CurrentX = NewX;
  }
}

void Entity::MoveRight() {
  int NewX = fmin(CurrentX + 1, ScreenWidth - 1);

  if (CheckIntersectionOnMap(NewX, CurrentY)) {
    CurrentX = NewX;
  }
}

void Entity::OnDestroy() {}

void Entity::Destroy() {
  OnDestroy();

  bIsMarkedForDestroy = true;
}

bool Entity::GetIsMarkedForDestroy() const {
  return bIsMarkedForDestroy;
}

bool Entity::CheckIntersectionOnMap(int x, int y) const {
  Entity* EntityOnLocation = Game::GetInstance()->GetMap()->GetEntity(x, y);

  if (EntityOnLocation != nullptr) {
    return EntityOnLocation->CanBeSteppedUpon();
  }

  return true;
}
