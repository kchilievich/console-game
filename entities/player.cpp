#pragma once

#include "entity.cpp"
#include "enemy.h"
#include "actions/attack.cpp"

class Player : public Entity {
public:
  Player();

  const vector<Action*> GetActions() const;
  virtual std::string GetName() const override { return "Player"; }
  virtual bool BlocksVision() const override { return false; };

  void ProcessInput(int Char);

protected:
  virtual void SetupIcon() override;
  virtual void OnDestroy() override;
  Enemy* FindClosestEnemy() const;

private:
  Enemy* FindEnemyAtPoint(int X, int Y) const;
  vector<Action*> Actions;
};

Player::Player() {
  SetupIcon();

  Actions = vector<Action*>(3, new Action());
  Actions[0] = new Attack();
  CurrentX = 1;
  CurrentY = 1;
}

const vector<Action*> Player::GetActions() const {
  return Actions;
}

void Player::SetupIcon() {
  MapIcon->Symbol = std::string("X");
  MapIcon->Color = PLAYER_COLOR_PAIR;
}

void Player::ProcessInput(int Char) {
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
    Actions[0]->Perform(this, FindClosestEnemy());
  }
  else if (Char == 'A') {
    Actions[1]->Perform(this, FindClosestEnemy());
  }
}

Enemy* Player::FindClosestEnemy() const {
  Enemy* FoundEnemy = nullptr;

  FoundEnemy = FindEnemyAtPoint(CurrentX + 1, CurrentY);

  if (FoundEnemy != nullptr) {
    return FoundEnemy;
  }

  FoundEnemy = FindEnemyAtPoint(CurrentX - 1, CurrentY);

  if (FoundEnemy != nullptr) {
    return FoundEnemy;
  }

  FoundEnemy = FindEnemyAtPoint(CurrentX, CurrentY + 1);

  if (FoundEnemy != nullptr) {
    return FoundEnemy;
  }

  FoundEnemy = FindEnemyAtPoint(CurrentX, CurrentY - 1);

  return FoundEnemy;
}

Enemy* Player::FindEnemyAtPoint(int X, int Y) const {
  return dynamic_cast<Enemy*>(Game::GetInstance()->GetMap()->GetEntity(X, Y));
}

void Player::OnDestroy() {
  Game::GetInstance()->Over();
}
