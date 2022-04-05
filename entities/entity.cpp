#pragma once

#include <math.h>
#include <string>

#include "../definitions.h"
#include "../game.h"
#include "../map.h"

// whatever the fuck it is it works
#include "../components/attributes_component.h"
#include "../components/base_component.h"
#include "../components/base_component.cpp"
#include "../components/attributes_component.cpp"
// -------------------------------

using namespace std;

class Entity {

public:
  Entity();

  virtual void Act();
  void PerformTurn();

  const Icon* GetIcon() const;
  virtual std::string GetName() const { return "Entity"; }

  int GetX() const;
  int GetY() const;

  // returns actual damage received
  float ApplyDamage(float Amount, Entity* Source);

  void MoveUp();
  void MoveDown();
  void MoveLeft();
  void MoveRight();

  void Destroy();
  bool GetIsMarkedForDestroy() const;

  virtual bool CanBeSteppedUpon() const;

  Attributes* GetAttributes() const;

  void SetThisPtr(shared_ptr<Entity> NewThisPtr);
  shared_ptr<Entity> GetThisPtr() const;

protected:
  int CurrentX = 0;
  int CurrentY = 0;

  int ActDelay = 2;

  Icon* MapIcon;

  Attributes* AttributesComponent;
  shared_ptr<Entity> ThisPtr;

  virtual void SetupIcon();
  virtual void Reset();

  virtual void OnDestroy();

private:
  int CurrentActDelay;
  bool bIsMarkedForDestroy = false;

  bool CheckIntersectionOnMap(int x, int y) const;

};

Entity::Entity() {
  MapIcon = new Icon();
  SetupIcon();
  CurrentActDelay = ActDelay;

  AttributesComponent = new Attributes();
  AttributesComponent->SetOwner(ThisPtr);
}

void Entity::PerformTurn() {
  if (--CurrentActDelay <= 0) {
    Act();
    CurrentActDelay = ActDelay;
  }
}

void Entity::Act() {}

void Entity::Reset() {}

void Entity::SetupIcon() {
  MapIcon->Symbol = string("?");
  MapIcon->Color = DEFAULT_COLOR_PAIR;
}

const Icon* Entity::GetIcon() const {
  return MapIcon;
}

Attributes* Entity::GetAttributes() const {
  return AttributesComponent;
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

float Entity::ApplyDamage(float Amount, Entity* Source) {
  AttributesComponent->ModifyHealth(-Amount);

  if (AttributesComponent->GetHealth() <= 0) {
    Destroy();
  }

  return Amount;
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

void Entity::SetThisPtr(shared_ptr<Entity> NewThisPtr) {
  ThisPtr = NewThisPtr;
}

shared_ptr<Entity> Entity::GetThisPtr() const {
  return ThisPtr;
}
