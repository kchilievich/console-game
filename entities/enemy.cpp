#pragma once

#include "entity.cpp"

class Enemy : public Entity {
public:
  Enemy();

  virtual void Act() override;
  virtual std::string GetIcon() const override;
};

Enemy::Enemy() {
  CurrentX = ScreenWidth - 1;
  CurrentY = rand() % (ScreenHeight - 1);
}

void Enemy::Act() {
  MoveLeft();
}

std::string Enemy::GetIcon() const {
  return std::string("<");
}
