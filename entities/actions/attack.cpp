#pragma once

#include "action.h"
#include "../../utility.cpp"

class Attack : public Action {
public:
  virtual string GetName() const override { return "Basic Attack"; }

  virtual void Perform(Entity* Source, Entity* Target) override;
};

void Attack::Perform(Entity* Source, Entity* Target) {
  if (Target == nullptr) {
    return;
  }

  float DamageDone = Target->ApplyDamage(20.f, Source);

  std::string Msg = FormatString("%s done %.2f damage to %s",
                                 Source->GetName().c_str(),
                                 DamageDone,
                                 Target->GetName().c_str());

  Game::GetInstance()->AddMessage(Msg);
}
