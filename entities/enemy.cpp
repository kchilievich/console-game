#pragma once

#include "entity.cpp"

class Enemy : public Entity {
public:
  Enemy();

  virtual void Act() override;

protected:
  virtual void SetupIcon() override;
  virtual void Reset() override;
};

Enemy::Enemy() {
  Reset();
  SetupIcon();
}

void Enemy::SetupIcon() {
  MapIcon->Symbol = std::string("<");
  MapIcon->Color = ENEMY_COLOR_PAIR;
}

void Enemy::Reset() {
  CurrentX = ScreenWidth - 1;
  CurrentY = rand() % (ScreenHeight - 1);
}

void Enemy::Act() {
  if (CurrentX > 0) {
    MoveLeft();
  } else {
    Reset();
  }
}
