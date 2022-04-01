#pragma once

#include "action.h"

class Attack : public Action {
public:
  virtual void Perform(Entity* Source, Entity* Target);

protected:
  string Name = "Attack";
};

void Attack::Perform(Entity* Source, Entity* Target) {
  if (Target == nullptr) {
    return;
  }

  float DamageDone = Target->ApplyDamage(20.f, Source);

  //TODO: add interpolation somehow
  Game::GetInstance()->AddMessage("attack by 20.f");
}
