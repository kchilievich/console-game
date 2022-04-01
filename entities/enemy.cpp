#pragma once

#include "../utility.cpp"
#include "player.cpp"
#include "actions/attack.cpp"

#include "enemy.h"

Enemy::Enemy() {
  Reset();
  SetupIcon();

  AttackAction = new Attack();
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
  if (Target != nullptr) {
    // Follow target
    int TargetX = Target->GetX();
    int TargetY = Target->GetY();
    Point NextPoint = Bresenham(CurrentX, CurrentY, Target->GetX(), Target->GetY());

    if (NextPoint.X < CurrentX) { MoveLeft(); }
    else if (NextPoint.X > CurrentX) { MoveRight(); }
    else if (NextPoint.Y > CurrentY) { MoveDown(); }
    else if (NextPoint.Y < CurrentY) { MoveUp(); }

    //Attack target
    if (abs(TargetX - CurrentX) + abs(TargetY - CurrentY) <= 1) {
      AttackAction->Perform(this, Target);
    }
  }
}
