#pragma once

#include "entity.cpp"
#include "actions/action.h"

class Player : public Entity {
public:
  Player();

  const vector<Action*> GetActions() const;

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
    else if (Char == 'a') {
      Actions[0]->Perform();
    }
    else if (Char == 'A') {
      Actions[1]->Perform();
    }
  }

protected:
  virtual void SetupIcon() override;
  virtual void OnDestroy() override;

  vector<Action*> Actions;
};

Player::Player() {
  SetupIcon();
  Actions = vector<Action*>(3, new Action());
}

const vector<Action*> Player::GetActions() const {
  return Actions;
}

void Player::SetupIcon() {
  MapIcon->Symbol = std::string("X");
  MapIcon->Color = PLAYER_COLOR_PAIR;
}

void Player::OnDestroy() {
  Game::GetInstance()->Over();
}
