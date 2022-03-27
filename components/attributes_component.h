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
  float Health = 99;
  float MaxHealthBase = 100;
  float MaxHealthModifier = 1;
};
