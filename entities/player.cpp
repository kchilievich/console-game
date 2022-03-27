#pragma once

#include "entity.cpp"

class Player : public Entity {
public:
  Player();

  void ProcessInput(int Char) {
    if (Char == KEY_DOWN) {
      MoveDown();
    }
    else if (Char == KEY_UP) {
      MoveUp();
    }
    else if (Char == KEY_LEFT) {
      MoveLeft();
    }
    else if (Char == KEY_RIGHT) {
      MoveRight();
    }
    else if (Char == 'A') {
      printw("Attack");
    }
  }

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
