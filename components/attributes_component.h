#pragma once

#include "base_component.h"

class Attributes : public BaseComponent {
public:
  float GetHealth() const;
  float GetMaxHealth() const;

  void ModifyHealth(float Delta);

protected:
  virtual void TurnInternal() override;

private:
  float Health = 100.f;
  float MaxHealthBase = 100.f;
  float MaxHealthModifier = 1.f;
};
