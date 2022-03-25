#pragma once

#include "entity.cpp"

class Player : public Entity {
public:
  Player();

protected:
  virtual void SetupIcon() override;
};

Player::Player() {
  SetupIcon();
}

void Player::SetupIcon() {
  MapIcon->Symbol = std::string("X");
  MapIcon->Color = PLAYER_COLOR_PAIR;
}
