#pragma once

#include "../utility.cpp"
#include "entity.cpp"
#include "player.cpp"

class Enemy : public Entity {
public:
  Enemy();

  virtual void Act() override;

  void SetTarget(Entity* NewPlayer);

protected:
  virtual void SetupIcon() override;
  virtual void Reset() override;

private:
  Entity* Target = nullptr;
};

Enemy::Enemy() {
  Reset();
  SetupIcon();
}

void Enemy::SetupIcon() {
  MapIcon->Symbol = string("x");
  MapIcon->Color = ENEMY_COLOR_PAIR;
}

void Enemy::Reset() {
  CurrentX = rand() % (ScreenWidth - 1);
  CurrentY = rand() % (ScreenHeight - 1);
}

void Enemy::SetTarget(Entity* NewTarget) {
  Target = NewTarget;
}

void Enemy::Act() {
  Point NextPoint = Bresenham(CurrentX, CurrentY, Target->GetX(), Target->GetY());

  if (NextPoint.X < CurrentX) { MoveLeft(); }
  else if (NextPoint.X > CurrentX) { MoveRight(); }
  else if (NextPoint.Y > CurrentY) { MoveDown(); }
  else if (NextPoint.Y < CurrentY) { MoveUp(); }

  // if sees player
  // go to player
  // else
  // move around
}
