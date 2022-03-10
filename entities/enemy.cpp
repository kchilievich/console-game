#pragma once

#include "entity.cpp"

class Enemy : public Entity {
public:
  Enemy();

  virtual void Act() override;
  virtual std::string GetIcon() const override;

protected:
  virtual void Reset() override;
};

Enemy::Enemy() {
  Reset();
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

std::string Enemy::GetIcon() const {
  return std::string("<");
}
